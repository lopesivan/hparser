/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006,2008 Kevin P. Barry (ta0kira@users.sourceforge.net)      *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "gtk-tagged-section.hpp"

#include <hparser/classes/string-all.hpp>
#include <hparser/classes/filo-scope.hpp>

#include "gtk-tagged-data.hpp"

//Tag Variables-----------------------------------------------------------------
extern const data_tag OPEN_MAIN;

//Main section
const data_tag MAIN_SECTION = "main";
const data_tag OPEN_MAIN    = construct_open(MAIN_SECTION);
const data_tag CLOSE_MAIN   = construct_close(MAIN_SECTION);

//Property to denote section type
const data_tag SECTION_TYPE = "type";

//Section tags, determined by main section
data_tag TAG_TYPE;
data_tag OPEN_TAG;
data_tag CLOSE_TAG;
//------------------------------------------------------------------------------

//GTKTaggedSection function bodies==============================================
static char SectionSection[] = "section(a)";

	GTKTaggedSection::GTKTaggedSection(data_tag pProps, bool mMain) :
	Scope(mMain? "main" : SectionSection), IsMainSection(mMain),
	Frame(NULL), Layout(NULL), Partial(NULL), Button(NULL)
	{
	if (!IsMainSection) SectionSection[8]++;
	if (SectionSection[5] > 'z') SectionSection[5] = 'A';

	//set the data separator for output filtering
	Separator = "\t";

	//extract section properties
	extract_properties(pProps, Properties);

	this->RegenerateGUI();

	if (IsMainSection)
	//set tag type for subsections__________________________________________
	 {
	TAG_TYPE  = get_property_value(Properties, SECTION_TYPE);
	OPEN_TAG  = construct_open(TAG_TYPE);
	CLOSE_TAG = construct_close(TAG_TYPE);

	//GTK setup%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//set the frame label to the tag
	  {
	if (Frame)
	gtk_frame_set_label(GTK_FRAME(Frame), insert_properties(OPEN_MAIN, Properties).c_str());
	  }
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	 }
	//______________________________________________________________________

	else
	//GTK setup%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//set the frame label to the tag
	 {
	if (Frame)
	gtk_frame_set_label(GTK_FRAME(Frame), insert_properties(OPEN_TAG, Properties).c_str());
	 }
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	}

	//From 'storage_section'------------------------------------------------
	section_releaser GTKTaggedSection::copy() const
	{ return section_releaser( new GTKTaggedSection(*this) ); }
	//----------------------------------------------------------------------

	//From 'interface_user'-------------------------------------------------
	element_interface *GTKTaggedSection::extract_interface()
	{ return this; }

	const element_interface *GTKTaggedSection::extract_interface() const
	{ return this; }
	//----------------------------------------------------------------------

	//From 'ConnectionControl'----------------------------------------------
	bool GTKTaggedSection::connect()
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

	bool GTKTaggedSection::disconnect()
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
	//----------------------------------------------------------------------

	//From 'scope_locator'--------------------------------------------------
	scope_locator *GTKTaggedSection::locate_scope(const scope_identifier &iIdent)
	{
	if (iIdent != Scope) return 0 /*NULL*/;
	scope_identifier Temp = iIdent;
	return this->linked_section::locate_scope(Temp << 1);
	}

	bool GTKTaggedSection::current_scope(scope_identifier &iIdent, scope_locator *sScope) const
	{
	iIdent << Scope;
	return this->linked_section::current_scope(iIdent, sScope);
	}
	//----------------------------------------------------------------------

	//From 'tagged_input'---------------------------------------------------
	bool GTKTaggedSection::makes_sense(data_input *iInput) const
	{ return !is_partial_tag(iInput->receive_input()); }


	bool GTKTaggedSection::is_close_tag(data_input *iInput) const
	{
	//compare to main closing tag if the main section
	if (IsMainSection && !tag_compare(iInput->receive_input(), CLOSE_MAIN))
	return false;

	//compare to subsection closing tag if not the main section
	if (!IsMainSection && !tag_compare(iInput->receive_input(), CLOSE_TAG))
	return false;

	iInput->next_input();
	return true;
	}


	bool GTKTaggedSection::is_subsection(data_input *iInput) const
	{
	//anything that isn't a close tag is a subsection
	return !tag_compare(iInput->receive_input(), CLOSE_TAG) &&
	       iInput->receive_input().size();
	}


	input_receiver *GTKTaggedSection::new_subsection(data_input *iInput)
	{
	//a complete tag other than an open tag means an error
	if ( !tag_compare(iInput->receive_input(), OPEN_TAG) &&
	     is_whole_tag(iInput->receive_input()) )
	return 0 /*NULL*/;

	//other than an open tag means a data section
	if (!tag_compare(iInput->receive_input(), OPEN_TAG))
         {
        GTKTaggedData *NewChild = new GTKTaggedData;

	if (!this->add_child(NewChild).result()) return 0 /*NULL*/;
	return this->child()? this->child()->last() : 0 /*NULL*/;
         }

	//otherwise, add a new subsection
        GTKTaggedSection *NewChild = new GTKTaggedSection(iInput->receive_input());

	if (!this->add_child(NewChild).result()) return 0 /*NULL*/;

	//clear the open tag from the buffer
	iInput->next_input();

	//return the last element added
	return this->child()? this->child()->last() : 0 /*NULL*/;
	}


	input_receiver *GTKTaggedSection::apply_input(data_input *iInput)
	{ return (this->section_open() && iInput->end_of_data())? 0 /*NULL*/ : this; }

	input_receiver *GTKTaggedSection::get_in_parent() const
	{ return this->parent(); }
	//----------------------------------------------------------------------

	//From 'tagged_output'--------------------------------------------------
	bool GTKTaggedSection::send_open_tag(data_output *oOutput) const
	{
	//filter the output (adds indentation)
	output_section Filtered;
	if (this->parent() && !this->parent()->output_filter(Filtered)) return false;
	if (!oOutput->send_output(Filtered)) return false;

	if (IsMainSection)
	//send a main open tag...
	 {
	if (!oOutput->send_output( insert_properties(OPEN_MAIN, Properties) ))
	return false;
	 }

	else
	//...or send a subsection open tag
	 {
	if (!oOutput->send_output( insert_properties(OPEN_TAG, Properties) ))
	return false;
	 }

	//formatting
	return oOutput->send_output("\n");
	}


	bool GTKTaggedSection::send_content(data_output *oOutput) const
	{ return true; }


	bool GTKTaggedSection::send_close_tag(data_output *oOutput) const
	{
	//filter the output (adds indentation)
	output_section Filtered;
	if (this->parent() && !this->parent()->output_filter(Filtered)) return false;

	if (IsMainSection)
	//send a main close tag...
	return oOutput->send_output(Filtered + CLOSE_MAIN + "\n");

	else
	//...or send a subsection close tag
	return oOutput->send_output(Filtered + CLOSE_TAG + "\n");
	}


	const output_sender *GTKTaggedSection::get_subsection() const
	{ return this->child(); }

	const output_sender *GTKTaggedSection::get_next() const
	{ return this->next(); }

	const output_sender *GTKTaggedSection::get_out_parent() const
	{ return this->parent(); }
	//======================================================================

	//GUI components%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	GtkWidget *GTKTaggedSection::CurrentGUI() const
	{ return Frame; }

	GtkWidget *GTKTaggedSection::RegenerateGUI()
	{
	//no point recreating the GUI if the parent doesn't have one
	if ( !this->parent() || !this->parent()->extract_interface() ||
	     !this->parent()->extract_interface()->GUIContainer() )
	return NULL;

	//this function must reconstruct the entire GUI for the element

	Frame = gtk_frame_new("");
	Partial = gtk_hbox_new(FALSE, 5);
	Layout = gtk_vbox_new(FALSE, 5);
	Button = gtk_button_new_with_label("Select");

	if (IsMainSection)
	gtk_frame_set_label(GTK_FRAME(Frame), insert_properties(OPEN_MAIN, Properties).c_str());

	else
	gtk_frame_set_label(GTK_FRAME(Frame), insert_properties(OPEN_TAG, Properties).c_str());

	//frame -> partial -> [button] layout -> child elements

	gtk_container_add(GTK_CONTAINER(Frame), Partial);
	gtk_box_pack_start(GTK_BOX(Partial), Button, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(Partial), Layout, FALSE, FALSE, 5);

	//A "clicked" action sends a pointer to this element to the swap
	//function.  If it's the same as the previous then the swap function is
	//reset
	g_signal_connect(G_OBJECT(Button), "clicked", G_CALLBACK(SwitchFunction),
	  (storage_section*) this);

	//recursively request regeneration from children------------------------
	storage_section *Current = this->child();
	while (Current)
	 {
	gtk_box_pack_start(GTK_BOX(Layout), Current->extract_interface()->RegenerateGUI(),
	  TRUE, TRUE, 5);
	Current = Current->next();
	 }
	//----------------------------------------------------------------------

	gtk_widget_show(Frame);
	gtk_widget_show(Partial);
	gtk_widget_show(Layout);
	gtk_widget_show(Button);

	return this->CurrentGUI();
	}

	GtkWidget *GTKTaggedSection::GUIContainer() const
	{ return Layout; }

	void GTKTaggedSection::ClearGUI()
	{
	//this must be recursive because GUI deletion is

	Frame = Layout = Partial = Button = NULL;

	storage_section *Current = this->child();
	while (Current)
	 {
	if (Current->extract_interface()) Current->extract_interface()->ClearGUI();
	Current = Current->next();
	 }
	}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//==============================================================================
