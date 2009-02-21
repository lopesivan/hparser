/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "tagged-data.hpp"

#include <iostream>

#include <hparser/classes/string-all.hpp>

//TaggedData function bodies====================================================
	//From 'storage_section'------------------------------------------------
	section_releaser TaggedData::copy() const
	{ return section_releaser(new TaggedData(*this)); }
	//----------------------------------------------------------------------

	//From 'input_receiver'-------------------------------------------------
	input_receiver *TaggedData::receive_data(data_input *iInput)
	{
	//check for a NULL input source
	if (!iInput) return 0 /*NULL*/;

	//copy the current buffer data
	Data = iInput->receive_input() + "\n";

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
	const output_sender *TaggedData::send_data(data_output *oOutput) const
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
//==============================================================================
