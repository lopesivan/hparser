/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "tagged-base.hpp"

#include <hparser/classes/string-all.hpp>
#include <hparser/formats/tag-properties.hpp>

#include "modes.hpp"
#include "tagged-section.hpp"

//Open tag for the main section
extern const data_tag OPEN_MAIN;

//TaggedBase function bodies====================================================
	//From 'input_receiver'-------------------------------------------------
	input_receiver *TaggedBase::receive_data(data_input *iInput)
	{
	//check for a NULL input source
	if (!iInput) return 0 /*NULL*/;

	//set the input mode to 'tagged' (tag format)
	if (!iInput->set_input_mode(Tagged)) return 0 /*NULL*/;

	//for the new element
	storage_section *NewSection = 0 /*NULL*/;

	//if data starts with a valid tag, add a new branch
	if (tag_compare(iInput->receive_input(), OPEN_MAIN))
	this->add_branch( NewSection = new TaggedSection(iInput->receive_input(), true) );

	//clear the open tag from the input buffer
	iInput->next_input();

	return NewSection;
	}
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	const output_sender *TaggedBase::send_data(data_output *oOutput) const
	{ return this->first_branch(); }
	//----------------------------------------------------------------------
//==============================================================================
