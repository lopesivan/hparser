/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006,2008 Kevin P. Barry (ta0kira@users.sourceforge.net)      *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <string>

#include <hparser/linked-section.hpp>

#include "gtk-proxy.hpp"

//Class GTKTaggedData-----------------------------------------------------------
//Data element for tagged example
class GTKTaggedData :
	public linked_section,
	private element_interface
{
public:
	GTKTaggedData();

	//From 'storage_section'------------------------------------------------
	section_releaser copy() const;
	//----------------------------------------------------------------------

	//From 'input_receiver'-------------------------------------------------
	input_receiver *receive_data(data_input*);
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	const output_sender *send_data(data_output*) const;
	//----------------------------------------------------------------------

	//From 'interface_user'-------------------------------------------------
	element_interface *extract_interface();
	const element_interface *extract_interface() const;
	//----------------------------------------------------------------------

	//From 'ConnectionControl'----------------------------------------------
	bool connect();
	bool disconnect();
	bool allow_child(const storage_section*) const;
	//----------------------------------------------------------------------

	//From 'scope_locator'--------------------------------------------------
	scope_locator *locate_scope(const scope_identifier&);
	bool current_scope(scope_identifier&, scope_locator*) const;
	//----------------------------------------------------------------------

private:
	std::string Data, Scope;
	//Element data, element scope

	//GUI components%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	GtkWidget *CurrentGUI() const;
	GtkWidget *RegenerateGUI();
	GtkWidget *GUIContainer() const;
	void       ClearGUI();

	GtkWidget *Text;
	GtkWidget *Partial;
	GtkWidget *Button;
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
}; //END------------------------------------------------------------------------
