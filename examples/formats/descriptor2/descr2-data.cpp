/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "descr2-data.hpp"

#include <iostream>

#include <hparser/classes/string-output.hpp>
#include <hparser/classes/string-composite.hpp>

//Descr2Data function bodies====================================================
	Descr2Data::Descr2Data(const Descr &dDesc) :
	SectionDescriptor(dDesc)
	{
	//display descriptor information
	std::cout << "DATA: ('" << SectionDescriptor.GetTitle() << "', "
	          << SectionDescriptor.GetSize() << "B) ";
	}

	//From 'storage_section'------------------------------------------------
	section_releaser Descr2Data::copy() const
	{ return section_releaser(new Descr2Data(*this)); }
	//----------------------------------------------------------------------

	//From 'input_receiver'-------------------------------------------------
	bool Descr2Data::expand_data(composite_data &iInput)
	{
	//calculate amount of data needed
	int ToGet = SectionDescriptor.GetSize() - Data.size();

	if (ToGet <= 0)
	//if nothing is needed, return
	 {
	//formatting
	std::cout << "\n";
	return true;
	 }

	if ((signed) iInput.size() < ToGet)
	//if not enough is left, return
	 {
	//formatting
	std::cout << "\n";
	return false;
	 }

	//extract the required input
	composite_data Add = iInput.substr(0, ToGet);

	//display the extracted input
	std::cout << Add << "\n";

	//add the input to the element data
	Data += Add;

	//remove the input which was copied
	iInput.erase(iInput.begin(), iInput.begin() + ToGet);

	return true;
	}
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	bool Descr2Data::collect_data(composite_data &oOutput) const
	{
	if (OutputMode)
	//add indentation if in display mode____________________________________
	 {
	output_section Filtered;
	if (!this->output_filter(Filtered)) return false;
	oOutput += Filtered;
	 }
	//______________________________________________________________________

	//send the descriptor
	oOutput += SectionDescriptor.send_descriptor();

	//add the element data
	oOutput += Data;

	//formatting
	if (OutputMode) oOutput += "\n";

	//collect data from the next element if necessary
	if (this->next() && !this->next()->collect_data(oOutput)) return false;

	return true;
	}
	//----------------------------------------------------------------------

	//From 'comm_line'------------------------------------------------------
	bool Descr2Data::local_message(comm_message &mMessage)
	{
	this->ChangeMode(mMessage);
	return true;
	}
	//----------------------------------------------------------------------

	//From 'triggered_update'-----------------------------------------------
	bool Descr2Data::local_update()
	{
	SectionDescriptor.SetSize(Data.size());
	return true;
	}
	//----------------------------------------------------------------------

	//From 'parent_storage'-------------------------------------------------
	location_count Descr2Data::storage_size() const
	{
	return SectionDescriptor.GetSize() +
	  SectionDescriptor.send_descriptor().size();
	}
	//----------------------------------------------------------------------
//==============================================================================
