/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "descr2-table.hpp"

#include <iostream>

#include <hparser/classes/string-input.hpp>
#include <hparser/classes/string-output.hpp>
#include <hparser/classes/string-composite.hpp>

#include "descr2-data.hpp"

//Descr2Table function bodies===================================================
	Descr2Table::Descr2Table(const Descr &dDesc) :
	SectionDescriptor(dDesc)
	{
	//display descriptor information
	std::cout << "TABLE: '" << SectionDescriptor.GetTitle() << "' ("
	          << SectionDescriptor.GetSize() << "B)\n";
	}

	//From 'storage_section'------------------------------------------------
	section_releaser Descr2Table::copy() const
	{ return section_releaser(new Descr2Table(*this)); }
	//----------------------------------------------------------------------

	//From 'input_receiver'-------------------------------------------------
	bool Descr2Table::expand_data(composite_data &iInput)
	{
	while (iInput.size())
	//input processing loop_________________________________________________
	 {
	//create a new descriptor
	Descr New;
	unsigned int NewSize = New.TakeDescriptor(iInput);
	if (!New.IsValid()) return false;

	//for storage of the new element
	storage_section *NewElement = 0 /*NULL*/;

	//create a new element based on the descriptor type
	if (New.IsTable()) this->add_child( NewElement = new Descr2Table(New) );
	else               this->add_child( NewElement = new Descr2Data(New)  );

	//remove the descriptor from the input data
	iInput.erase(iInput.begin(), iInput.begin() + NewSize);

	//extract the input data for the new element
	composite_data NewInput = iInput.substr(0, New.GetSize());

	//remove the data copied for the new element
	iInput.erase(iInput.begin(), iInput.begin() + NewInput.size());

	//expand the input data
	if (!NewElement->expand_data(NewInput)) return false;
	 }
	//______________________________________________________________________

	return true;
	}
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	bool Descr2Table::collect_data(composite_data &oOutput) const
	{
	if (OutputMode)
	//add indentation if in display mode____________________________________
	 {
	output_section Filtered;
	if (this->parent() && !this->parent()->output_filter(Filtered)) return false;
	oOutput += Filtered;
	 }
	//______________________________________________________________________

	//send the descriptor
	oOutput += SectionDescriptor.send_descriptor();

	//formatting
	if (OutputMode) oOutput += "\n";

	//collect data from children
	if (this->child() && !this->child()->collect_data(oOutput)) return false;

	//collect data from next element if necessary
	if (this->next() && !this->next()->collect_data(oOutput)) return false;

	return true;
	}
	//----------------------------------------------------------------------

	//From 'triggered_update'-----------------------------------------------
	bool Descr2Table::local_update()
	{
	location_count Total = 0;

	storage_section *Current = this->child();
	while (Current)
	 {
	Total += Current->storage_size();
	Current = Current->next();
	 }

	SectionDescriptor.SetSize(Total);
	return true;
	}
	//----------------------------------------------------------------------

	//From 'parent_storage'-------------------------------------------------
	location_count Descr2Table::storage_size() const
	{
	return SectionDescriptor.GetSize() +
	  SectionDescriptor.send_descriptor().size();
	}
	//----------------------------------------------------------------------
//==============================================================================
