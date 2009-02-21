/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "table-data.hpp"

#include <iostream>

#include <hparser/classes/string-input.hpp>
#include <hparser/classes/string-output.hpp>
#include <hparser/classes/string-composite.hpp>

//TableData function bodies=====================================================
	TableData::TableData(const TableDescr &dDesc) :
	SectionDescriptor(dDesc)
	{
	//set the data separator for output filtering
	Separator = "\t";

	//display descriptor information
	std::cout << "DATA: starts at " << SectionDescriptor.GetBegin() << ", "
	          << SectionDescriptor.GetSize() << "B\n";
	}

	//From 'storage_section'------------------------------------------------
	section_releaser TableData::copy() const
	{ return section_releaser(new TableData(*this)); }
	//----------------------------------------------------------------------

	//Table parsing/exportation=============================================
	//From 'input_receiver'-------------------------------------------------
	input_receiver *TableData::receive_data(data_input*)
	{ return this->parent(); }
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	const output_sender *TableData::send_data(data_output *oOutput) const
	{
	//check for a NULL output destination
	if (!oOutput) return 0 /*NULL*/;

	//filter the output (adds indentation)
	output_section Filtered;
	if (!this->output_filter(Filtered)) return 0 /*NULL*/;
	if (!oOutput->send_output(Filtered)) return 0 /*NULL*/;

	//send the descriptor
	if (!oOutput->send_output( SectionDescriptor.send_descriptor() )) return 0 /*NULL*/;

	//send data when displaying on screen
	if (OutputMode && !oOutput->send_output(" ")) return false;
	if (OutputMode && !oOutput->send_output(Data)) return false;

	if (!oOutput->send_output("\n")) return 0 /*NULL*/;

	//process the next element if available
	if (this->next()) return this->next();
	else              return this->parent();
	}
	//----------------------------------------------------------------------
	//======================================================================

	//Data content exportation==============================================
	//From 'output_sender'--------------------------------------------------
	bool TableData::collect_data(composite_data &oOutput) const
	{
	if (OutputMode)
	//add indentation if in display mode____________________________________
	 {
	output_section Filtered;
	if (!this->output_filter(Filtered)) return false;
	oOutput += Filtered;
	 }
	//______________________________________________________________________

	//add the element data
	oOutput += Data;

	//formatting
	if (OutputMode) oOutput += "\n";

	//collect data from the next element if necessary
	if (this->next() && !this->next()->collect_data(oOutput)) return false;

	return true;
	}
	//----------------------------------------------------------------------
	//======================================================================

	//From parent storage---------------------------------------------------
	location_count TableData::next_location() const
	{
	if (!SectionDescriptor.IsValid()) return 0;
	return this->self_location() + SectionDescriptor.GetSize();
	}
	//----------------------------------------------------------------------

	//From 'triggered_update'-----------------------------------------------
	bool TableData::local_update()
	{
	//data is loaded on update rather than at parse time

	if (this->get_input_resource())
	Data = this->get_input_resource()->get_input(SectionDescriptor.GetBegin(),
						  SectionDescriptor.GetSize());

	SectionDescriptor.SetBegin(this->self_location());
	SectionDescriptor.SetSize(Data.size());
	return true;
	}
	//----------------------------------------------------------------------
//==============================================================================
