/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "tagged-section.hpp"

#include <hparser/classes/string-all.hpp>

#include "tagged-data.hpp"

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

//TaggedSection function bodies=================================================
	TaggedSection::TaggedSection(data_tag pProps, bool mMain) :
	IsMainSection(mMain)
	{
	//set the data separator for output filtering
	Separator = "\t";

	//extract section properties
	extract_properties(pProps, Properties);

	if (IsMainSection)
	//set tag type for subsections__________________________________________
	 {
	TAG_TYPE  = get_property_value(Properties, SECTION_TYPE);
	OPEN_TAG  = construct_open(TAG_TYPE);
	CLOSE_TAG = construct_close(TAG_TYPE);
	 }
	//______________________________________________________________________
	}

	//From 'storage_section'------------------------------------------------
	section_releaser TaggedSection::copy() const
	{ return section_releaser(new TaggedSection(*this)); }
	//----------------------------------------------------------------------

	//From 'tagged_input'---------------------------------------------------
	bool TaggedSection::makes_sense(data_input *iInput) const
	{ return !is_partial_tag(iInput->receive_input()); }


	bool TaggedSection::is_close_tag(data_input *iInput) const
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


	bool TaggedSection::is_subsection(data_input *iInput) const
	{
	//anything that isn't a close tag is a subsection
	return !tag_compare(iInput->receive_input(), CLOSE_TAG) &&
	       iInput->receive_input().size();
	}


	input_receiver *TaggedSection::new_subsection(data_input *iInput)
	{
	//a complete tag other than an open tag means an error
	if ( !tag_compare(iInput->receive_input(), OPEN_TAG) &&
	     is_whole_tag(iInput->receive_input()) )
	return 0 /*NULL*/;

	storage_section *Return = 0 /*NULL*/;

	//other than an open tag means a data section
	if (!tag_compare(iInput->receive_input(), OPEN_TAG))
	 {
	this->add_child(Return = new TaggedData);
	return Return;
	 }

	//otherwise, add a new subsection
	this->add_child( Return = new TaggedSection(iInput->receive_input()) );

	//clear the open tag from the buffer
	iInput->next_input();

	//return the last element added
	return Return;
	}


	input_receiver *TaggedSection::apply_input(data_input *iInput)
	{ return (this->section_open() && iInput->end_of_data())? 0 /*NULL*/ : this; }

	input_receiver *TaggedSection::get_in_parent() const
	{ return this->parent(); }
	//----------------------------------------------------------------------

	//From 'tagged_output'--------------------------------------------------
	bool TaggedSection::send_open_tag(data_output *oOutput) const
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


	bool TaggedSection::send_content(data_output *oOutput) const
	{ return true; }


	bool TaggedSection::send_close_tag(data_output *oOutput) const
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


	const output_sender *TaggedSection::get_subsection() const
	{ return this->child(); }

	const output_sender *TaggedSection::get_next() const
	{ return this->next(); }

	const output_sender *TaggedSection::get_out_parent() const
	{ return this->parent(); }
	//======================================================================
//==============================================================================
