/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "table-table.hpp"

#include <iostream>

#include <hparser/classes/string-input.hpp>
#include <hparser/classes/string-output.hpp>
#include <hparser/classes/string-composite.hpp>

#include "table-data.hpp"

//TableTable function bodies====================================================
	TableTable::TableTable(const TableDescr &dDesc) :
	SectionDescriptor(dDesc)
	{
	//set the data separator for output filtering
	Separator = "\t";

	//display descriptor information
	std::cout << "TABLE: starts at " << SectionDescriptor.GetBegin() << ", "
	          << SectionDescriptor.GetSize() << "B (+ "
	          << SectionDescriptor.GetElements() << " elements)\n";
	}

	//From 'storage_section'------------------------------------------------
	section_releaser TableTable::copy() const
	{ return section_releaser(new TableTable(*this)); }
	//----------------------------------------------------------------------

	//From 'parent_storage'-------------------------------------------------
	location_count TableTable::next_location() const
	{
	if (!SectionDescriptor.IsValid()) return 0;
	return this->child()? this->child()->last()->next_location() :
	  this->self_location() + SectionDescriptor.GetSize();
	}

	location_count TableTable::child_location() const
	{
	if (!SectionDescriptor.IsValid()) return 0;
	return this->self_location() + SectionDescriptor.GetSize();
	}
	//----------------------------------------------------------------------

	//Table exportation=====================================================
	//From 'output_sender'--------------------------------------------------
	const output_sender *TableTable::send_data(data_output *oOutput) const
	{
	//check for a NULL output destination
	if (!oOutput) return 0 /*NULL*/;

	if (!this->sending_subs())
	 {
	//recursion control
	this->set_sending_subs(true);

	//filter the output (adds indentation)
	output_section Filtered;
	if (!this->output_filter(Filtered)) return 0 /*NULL*/;
	if (!oOutput->send_output(Filtered)) return 0 /*NULL*/;

	//send the descriptor
	if (!oOutput->send_output( SectionDescriptor.send_descriptor() )) return 0 /*NULL*/;

	//send data when displaying on screen
	if (OutputMode && !oOutput->send_output(" "))  return false;
	if (OutputMode && !oOutput->send_output(Data)) return false;

	if (!oOutput->send_output("\n")) return 0 /*NULL*/;

	//process the child element if available
	if (this->child()) return this->child();
	 }

	else this->set_sending_subs(false);

	//process the next element if available
	if (this->next()) return this->next();
	else              return this->parent();
	}
	//----------------------------------------------------------------------
	//======================================================================

	//Data content exportation==============================================
	//From 'output_sender'--------------------------------------------------
	bool TableTable::collect_data(composite_data &oOutput) const
	{
	if (OutputMode)
	//add indentation if in display mode____________________________________
	 {
	output_section Filtered;
	if (this->parent() && !this->parent()->output_filter(Filtered)) return false;
	oOutput += Filtered;
	 }
	//______________________________________________________________________

	//add the element data
	oOutput += Data;

	//formatting
	if (OutputMode) oOutput += "\n";

	//collect data from children
	if (this->child() && !this->child()->collect_data(oOutput)) return false;

	//collect data from next element if necessary
	if (this->next() && !this->next()->collect_data(oOutput)) return false;

	return true;
	}
	//----------------------------------------------------------------------
	//======================================================================

	//From 'triggered_update'-----------------------------------------------
	bool TableTable::local_update()
	{
	//data is loaded on update rather than at parse time

	if (this->get_input_resource())
	Data = this->get_input_resource()->get_input(SectionDescriptor.GetBegin(),
						  SectionDescriptor.GetSize());

	SectionDescriptor.SetElements(this->count_children());
	SectionDescriptor.SetBegin(this->self_location());
	SectionDescriptor.SetSize(Data.size());
	return true;
	}
	//----------------------------------------------------------------------

	//From 'descriptor_input'-----------------------------------------------
	bool TableTable::section_complete(data_input *iInput) const
	{
	//if the subsection count hasn't been met, return
	if (this->count_children() < SectionDescriptor.GetElements()) return false;

	//replace what's still in the buffer if finished
	iInput->replace_buffer();

	return true;
	}


	bool TableTable::makes_sense(data_input *iInput) const
	{
	//check for a valid descriptor
	TableDescr Test;
	Test.TakeDescriptor(iInput->receive_input());
	return Test.IsValid();
	}


	bool TableTable::is_subsection(data_input*) const
	{ return true; }


	input_receiver *TableTable::new_subsection(data_input *iInput)
	{
	//create a new descriptor
	TableDescr New;
	unsigned int NewSize = New.TakeDescriptor(iInput->receive_input());
	if (!New.IsValid()) return 0 /*NULL*/;

	//remove the descriptor from the buffer
	iInput->next_input(NewSize);

	storage_section *Return = 0 /*NULL*/;

	//create a new element based on the descriptor type
	if (New.IsTable()) this->add_child( Return = new TableTable(New) );
	else               this->add_child( Return = new TableData(New)  );

	return Return;
	}


	input_receiver *TableTable::apply_input(data_input *iInput)
	{
	//no input is taken, but if the section isn't completed and there's no
	//data left, that means an error
	if (this->section_complete(iInput) || !iInput->end_of_data()) return this;
	return 0 /*NULL*/;
	}


	input_receiver *TableTable::get_in_parent() const
	{ return this->parent(); }
	//----------------------------------------------------------------------
//==============================================================================
