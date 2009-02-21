/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <string>

#include <hparser/formats/tagged-storage.hpp>
#include <hparser/formats/tag-properties.hpp>

#include "section-filter.hpp"

//Class TaggedSection-----------------------------------------------------------
//Section element for tagged example
class TaggedSection :
	public SectionFilter,
	public tagged_storage
{
public:
	TaggedSection(data_tag = "", bool = false);

	//From 'storage_section'------------------------------------------------
	section_releaser copy() const;
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

	property_list Properties;
	//List of tag properties

	bool IsMainSection;
	//Flag to tell if this is the main section or not
}; //END------------------------------------------------------------------------
