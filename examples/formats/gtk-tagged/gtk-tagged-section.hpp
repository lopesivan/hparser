/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006,2008 Kevin P. Barry (ta0kira@users.sourceforge.net)      *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <string>

#include <hparser/formats/tagged-storage.hpp>
#include <hparser/formats/tag-properties.hpp>

#include "section-filter.hpp"
#include "gtk-proxy.hpp"

//Class GTKTaggedSection--------------------------------------------------------
//Section element for tagged example
class GTKTaggedSection :
	public SectionFilter,
	public tagged_storage,
	private element_interface
{
public:
	GTKTaggedSection(data_tag = "", bool = false);

	//From 'storage_section'------------------------------------------------
	section_releaser copy() const;
	//----------------------------------------------------------------------

	//From 'interface_user'-------------------------------------------------
	element_interface *extract_interface();
	const element_interface *extract_interface() const;
	//----------------------------------------------------------------------

	//From 'ConnectionControl'----------------------------------------------
	bool connect();
	bool disconnect();
	//----------------------------------------------------------------------

	//From 'scope_locator'--------------------------------------------------
	scope_locator *locate_scope(const scope_identifier&);
	bool current_scope(scope_identifier&, scope_locator*) const;
	//----------------------------------------------------------------------

private:
	//From 'tagged_input'---------------------------------------------------
	bool makes_sense(data_input*) const;
	bool is_close_tag(data_input*) const;
	bool is_subsection(data_input*) const;
	input_receiver *new_subsection(data_input*);
	input_receiver *apply_input(data_input*);
	input_receiver *get_in_parent() const;
	//----------------------------------------------------------------------

	//From 'tagged_output'--------------------------------------------------
	bool send_open_tag(data_output*) const;
	bool send_content(data_output*) const;
	bool send_close_tag(data_output*) const;
	const output_sender *get_subsection() const;
	const output_sender *get_next() const;
	const output_sender *get_out_parent() const;
	//----------------------------------------------------------------------

	std::string Scope;
	//Element scope

	property_list Properties;
	//List of tag properties

	bool IsMainSection;
	//Flag to tell if this is the main section or not

	//GUI components%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	GtkWidget *CurrentGUI() const;
	GtkWidget *RegenerateGUI();
	GtkWidget *GUIContainer() const;
	void       ClearGUI();

	GtkWidget *Frame;
	GtkWidget *Layout, *Partial;
	GtkWidget *Button;
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
}; //END------------------------------------------------------------------------
