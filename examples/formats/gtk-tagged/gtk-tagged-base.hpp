/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006,2008 Kevin P. Barry (ta0kira@users.sourceforge.net)      *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <hparser/data-manager.hpp>
#include <hparser/storage-section.hpp>

#include "base-filter.hpp"
#include "gtk-proxy.hpp"

//Class GTKTaggedBase-----------------------------------------------------------
//Tree base for tagged example
class GTKTaggedBase :
	public BaseFilter,
	public DataManager,
	private element_interface
{
public:
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

	//From 'scope_locator'--------------------------------------------------
	scope_locator *locate_scope(const scope_identifier&);
	bool current_scope(scope_identifier&, scope_locator*) const;
	//----------------------------------------------------------------------

private:
	//GUI components%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	GtkWidget *CurrentGUI() const;
	GtkWidget *RegenerateGUI();
	GtkWidget *GUIContainer() const;
	void       ClearGUI();
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
}; //END------------------------------------------------------------------------
