/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007-2008 Kevin P. Barry (ta0kira@users.sourceforge.net)      *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "gtk-tagged-base.hpp"

#include <hparser/classes/string-all.hpp>
#include <hparser/classes/filo-scope.hpp>
#include <hparser/formats/tag-properties.hpp>

#include "modes.hpp"
#include "gtk-tagged-section.hpp"
#include "gtk-proxy.hpp"

//Open tag for the main section
extern const data_tag OPEN_MAIN;

//GTKTaggedBase function bodies=================================================
	//From 'input_receiver'-------------------------------------------------
	input_receiver *GTKTaggedBase::receive_data(data_input *iInput)
	{
	//check for a NULL input source
	if (!iInput) return 0 /*NULL*/;

	//set the input mode to 'tagged' (tag format)
	if (!iInput->set_input_mode(Tagged)) return 0 /*NULL*/;

	//for the new element
	GTKTaggedSection *NewSection = 0 /*NULL*/;

	//if data starts with a valid tag, add a new branch
	if (tag_compare(iInput->receive_input(), OPEN_MAIN))
	this->add_branch( NewSection = new GTKTaggedSection(iInput->receive_input(), true) );

	//clear the open tag from the input buffer
	iInput->next_input();

	//GTK setup%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	GlobalView.Viewport = gtk_scrolled_window_new(NULL, NULL);
	GlobalView.Container = gtk_vbox_new(FALSE, 5);

	//main window -> viewport -> container -> main element

	gtk_container_add(GTK_CONTAINER(GlobalView.Window), GlobalView.Viewport);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(GlobalView.Viewport),
	  GlobalView.Container);
	gtk_box_pack_start(GTK_BOX(GlobalView.Container), NewSection->
	  extract_interface()->CurrentGUI(), TRUE, FALSE, 5);

	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(GlobalView.Viewport),
	  GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

	//show all of the components
	gtk_widget_show(GlobalView.Viewport);
	gtk_widget_show(GlobalView.Container);
	gtk_widget_show(NewSection->extract_interface()->CurrentGUI());
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	return NewSection;
	}
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	const output_sender *GTKTaggedBase::send_data(data_output *oOutput) const
	{ return this->first_branch(); }
	//----------------------------------------------------------------------

	//From 'interface_user'-------------------------------------------------
	element_interface *GTKTaggedBase::extract_interface()
	{ return this; }

	const element_interface *GTKTaggedBase::extract_interface() const
	{ return this; }
	//----------------------------------------------------------------------

	//From 'scope_locator'--------------------------------------------------
	scope_locator *GTKTaggedBase::locate_scope(const scope_identifier &iIdent)
	{
	if (iIdent == "base") return this;
	else                  return 0 /*NULL*/;
	}

	bool GTKTaggedBase::current_scope(scope_identifier &iIdent, scope_locator *sScope) const
	{
	if (sScope && sScope != this) return false;
	iIdent << "base";
	return true;
	}
	//----------------------------------------------------------------------

	//GUI components%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	GtkWidget *GTKTaggedBase::CurrentGUI() const
	{ return NULL; }

	GtkWidget *GTKTaggedBase::RegenerateGUI()
	{ return NULL; }

	GtkWidget *GTKTaggedBase::GUIContainer() const
	{ return GlobalView.Window; }

	void GTKTaggedBase::ClearGUI() {}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//==============================================================================
