/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "descr-data.hpp"

#include <iostream>

#include <hparser/classes/string-input.hpp>
#include <hparser/classes/string-output.hpp>

//DescrData function bodies=====================================================
	DescrData::DescrData(const Descr &dDesc) :
	SectionDescriptor(dDesc)
	{
	//display descriptor information
	std::cout << "DATA: ('" << SectionDescriptor.GetTitle() << "', "
	          << SectionDescriptor.GetSize() << "B) ";
	}

	//From 'storage_section'------------------------------------------------
	section_releaser DescrData::copy() const
	{ return section_releaser(new DescrData(*this)); }
	//----------------------------------------------------------------------

	//From 'input_receiver'-------------------------------------------------
	input_receiver *DescrData::receive_data(data_input *iInput)
	{
	//check for a NULL input source
	if (!iInput) return 0 /*NULL*/;

	//if the section is full, return parent
	if (Data.size() >= SectionDescriptor.GetSize()) return this->parent();

	//calculate amount of data needed
	int ToGet = SectionDescriptor.GetSize() - Data.size();

	if ((signed) iInput->receive_input().size() < ToGet)
	//reduce to what's available if necessary
	 {
	ToGet = iInput->receive_input().size();

	//if there isn't any more left, that means an error
	if (iInput->end_of_data()) return 0 /*NULL*/;
	 }

	//extract the required input
	input_section Add = iInput->receive_input().substr(0, ToGet);

	//display the extracted input
	std::cout << Add << "\n";

	//add the input to the element data
	Data += Add;

	//remove the input from the buffer
	iInput->next_input(ToGet);

	return this;
	}
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	const output_sender *DescrData::send_data(data_output *oOutput) const
	{
	//check for a NULL output destination
	if (!oOutput) return 0 /*NULL*/;

	//filter the output (adds indentation)
	output_section Filtered;
	if (!this->output_filter(Filtered)) return 0 /*NULL*/;
	if (!oOutput->send_output(Filtered)) return 0 /*NULL*/;

	//send the descriptor
	if (!oOutput->send_output( SectionDescriptor.send_descriptor() )) return 0 /*NULL*/;
	if (!oOutput->send_output(Data + "\n")) return 0 /*NULL*/;

	//process the next element if available
	if (this->next()) return this->next();
	else              return this->parent();
	}
	//----------------------------------------------------------------------

	//From 'triggered_update'-----------------------------------------------
	bool DescrData::local_update()
	{
	SectionDescriptor.SetSize(Data.size());
	return true;
	}
	//----------------------------------------------------------------------
//==============================================================================
