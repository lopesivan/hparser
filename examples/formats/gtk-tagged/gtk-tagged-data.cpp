/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006,2008 Kevin P. Barry (ta0kira@users.sourceforge.net)      *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "gtk-tagged-data.hpp"

#include <iostream>

#include <hparser/classes/string-all.hpp>
#include <hparser/classes/filo-scope.hpp>

//GTKTaggedData function bodies=================================================
static char DataSection[] = "data(a)";

	GTKTaggedData::GTKTaggedData() : Scope(DataSection), Text(NULL),
	Partial(NULL), Button(NULL)
	{
	this->RegenerateGUI();
	DataSection[5]++;
	if (DataSection[5] > 'z') DataSection[5] = 'A';
	}

	//From 'storage_section'------------------------------------------------
	section_releaser GTKTaggedData::copy() const
	{ return section_releaser( new GTKTaggedData(*this) ); }
	//----------------------------------------------------------------------

	//From 'input_receiver'-------------------------------------------------
	input_receiver *GTKTaggedData::receive_data(data_input *iInput)
	{
	//check for a NULL input source
	if (!iInput) return 0 /*NULL*/;

	//copy the current buffer data
	Data = iInput->receive_input();

	//GTK setup%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//make the text field reflect the data
	if (Text)
	gtk_entry_set_text(GTK_ENTRY(Text), Data.c_str());
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	Data += "\n";

	//filter the input (adds indentation)
	output_section Filtered;
	if (this->parent() && !this->parent()->output_filter(Filtered)) return false;

	//display the input
	std::cout << Filtered << iInput->receive_input() << "\n";

	//remove the input from the buffer
	iInput->next_input();

	return this->parent();
	}
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	const output_sender *GTKTaggedData::send_data(data_output *oOutput) const
	{
	//check for a NULL output destination
	if (!oOutput) return 0 /*NULL*/;

	//filter the output (adds indentation)
	output_section Filtered;
	if (this->parent() && !this->parent()->output_filter(Filtered)) return false;

	//replace the last indent with spaces (formatting)
	Filtered.erase(Filtered.end() - 1);
	Filtered.insert(Filtered.size(), "  ");

	//send the element data
	if (!oOutput->send_output(Filtered + Data)) return false;

	//process the next element if available
	if (this->next()) return this->next();
	else              return this->parent();
	}
	//----------------------------------------------------------------------

	//From 'interface_user'-------------------------------------------------
	element_interface *GTKTaggedData::extract_interface()
	{ return this; }

	const element_interface *GTKTaggedData::extract_interface() const
	{ return this; }
	//----------------------------------------------------------------------

	//From 'ConnectionControl'----------------------------------------------
	bool GTKTaggedData::connect()
	{
	//GTK setup%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	if (!this->parent()) return false;

	element_interface *Interface = this->extract_interface();
	if (!Interface) return false;

	element_interface *ParentInterface = this->parent()->extract_interface();
	if (!ParentInterface || !ParentInterface->GUIContainer()) return false;

	if (!Interface->RegenerateGUI()) return false;

	gtk_box_pack_start(GTK_BOX(ParentInterface->GUIContainer()),
	  Interface->CurrentGUI(), TRUE, TRUE, 5);

	gtk_box_reorder_child(GTK_BOX(ParentInterface->GUIContainer()),
	  Interface->CurrentGUI(), this->count_previous());
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	//'Next' is also disconnected by any removal function
	return (this->next()? this->next()->connect() : true);
	}

	bool GTKTaggedData::disconnect()
	{
	//GTK setup%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	if (!this->parent()) return false;

	element_interface *Interface = this->extract_interface();
	if (!Interface) return false;

	element_interface *ParentInterface = this->parent()->extract_interface();
	if (!ParentInterface || !ParentInterface->GUIContainer()) return false;

	gtk_container_remove(GTK_CONTAINER(ParentInterface->GUIContainer()),
	  Interface->CurrentGUI());

	Interface->ClearGUI();
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	//'Next' is also disconnected by any removal function
	return (this->next()? this->next()->disconnect() : true);
	}

	bool GTKTaggedData::allow_child(const storage_section*) const
	{ return false; }
	//----------------------------------------------------------------------

	//From 'scope_locator'--------------------------------------------------
	scope_locator *GTKTaggedData::locate_scope(const scope_identifier &iIdent)
	{
	if (iIdent != Scope) return 0 /*NULL*/;
	scope_identifier Temp = iIdent;
	return this->linked_section::locate_scope(Temp << 1);
	}

	bool GTKTaggedData::current_scope(scope_identifier &iIdent, scope_locator *sScope) const
	{
	iIdent << Scope;
	return this->linked_section::current_scope(iIdent, sScope);
	}
	//----------------------------------------------------------------------

	//GUI components%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	GtkWidget *GTKTaggedData::CurrentGUI() const
	{ return Partial; }

	GtkWidget *GTKTaggedData::RegenerateGUI()
	{
	//no point recreating the GUI if the parent doesn't have one
	if ( !this->parent() || !this->parent()->extract_interface() ||
	     !this->parent()->extract_interface()->GUIContainer() )
	return NULL;

	//remove the newline for GUI display
	std::string TempData = Data;
	if (Data.size()) TempData.erase(TempData.end() - 1);

	//this function must reconstruct the entire GUI for the element

	Partial = gtk_hbox_new(FALSE, 5);
	Button = gtk_button_new_with_label("->");
	Text = gtk_entry_new();

	//partial -> [button] text

	gtk_box_pack_start(GTK_BOX(Partial), Button, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(Partial), Text, TRUE, TRUE, 5);

	//a "copy" action sends this element to the swap function, a "paste"
	//action clears the swap function
	g_signal_connect(G_OBJECT(Button), "clicked", G_CALLBACK(SwitchFunction),
	  (storage_section*) this);

	//set up the text field
	gtk_entry_set_text(GTK_ENTRY(Text), TempData.c_str());
	gtk_entry_set_editable (GTK_ENTRY(Text), FALSE);

	gtk_widget_show(Partial);
	gtk_widget_show(Button);
	gtk_widget_show(Text);

	return this->CurrentGUI();
	}

	GtkWidget *GTKTaggedData::GUIContainer() const
	{ return NULL; }

	void GTKTaggedData::ClearGUI()
	{ Text = Partial = Button = NULL; }
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//==============================================================================
