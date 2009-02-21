/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "descr-table.hpp"

#include <iostream>

#include <hparser/classes/string-output.hpp>

#include "descr-data.hpp"

//DescrTable function bodies====================================================
	DescrTable::DescrTable(const Descr &dDesc) :
	SectionDescriptor(dDesc)
	{
	//set the data separator for output filtering
	Separator = "\t";

	//display descriptor information
	std::cout << "TABLE: '" << SectionDescriptor.GetTitle() << "' ("
	          << SectionDescriptor.GetSize() << " elements)\n";
	}

	//From 'storage_section'------------------------------------------------
	section_releaser DescrTable::copy() const
	{ return section_releaser(new DescrTable(*this)); }
	//----------------------------------------------------------------------

	//From 'triggered_update'-----------------------------------------------
	bool DescrTable::local_update()
	{
	SectionDescriptor.SetSize( this->count_children() );
	return true;
	}
	//----------------------------------------------------------------------

	//From 'descriptor_input'-----------------------------------------------
	bool DescrTable::section_complete(data_input *iInput) const
	{
	//if the subsection count hasn't been met, return
	if (this->count_children() < SectionDescriptor.GetSize()) return false;

	//replace what's still in the buffer if finished
	iInput->replace_buffer();

	return true;
	}


	bool DescrTable::makes_sense(data_input *iInput) const
	{
	//check for a valid descriptor
	Descr Test;
	Test.TakeDescriptor(iInput->receive_input());
	return Test.IsValid();
	}


	bool DescrTable::is_subsection(data_input*) const
	{ return true; }


	input_receiver *DescrTable::new_subsection(data_input *iInput)
	{
	//create a new descriptor
	Descr New;
	unsigned int NewSize = New.TakeDescriptor(iInput->receive_input());
	if (!New.IsValid()) return 0 /*NULL*/;

	//remove the descriptor from the buffer
	iInput->next_input(NewSize);

	storage_section *Return = 0 /*NULL*/;

	//create a new element based on the descriptor type
	if (New.IsTable()) this->add_child( Return = new DescrTable(New) );
	else               this->add_child( Return = new DescrData(New)  );

	return Return;
	}


	input_receiver *DescrTable::apply_input(data_input *iInput)
	{
	//no input is taken, but if the section isn't completed and there's no
	//data left, that means an error
	if (this->section_complete(iInput) || !iInput->end_of_data()) return this;
	return 0 /*NULL*/;
	}


	input_receiver *DescrTable::get_in_parent() const
	{ return this->parent(); }
	//----------------------------------------------------------------------

	//From 'descriptor_output'----------------------------------------------
	bool DescrTable::send_descriptor(data_output *oOutput) const
	{
	//filter the output (adds indentation)
	//we skip our own filter and go straight to our parent's to reduce the
	//indentaion by one
	output_section Filtered;
	if (this->parent() && !this->parent()->output_filter(Filtered)) return false;
	if (!oOutput->send_output(Filtered)) return false;

	//send the descriptor
	return oOutput->send_output( SectionDescriptor.send_descriptor() );
	}


	bool DescrTable::send_content(data_output *oOutput) const
	{ return oOutput->send_output("\n"); }

	const output_sender *DescrTable::get_subsection() const
	{ return this->child(); }

	const output_sender *DescrTable::get_next() const
	{ return this->next(); }

	const output_sender *DescrTable::get_out_parent() const
	{ return this->parent(); }
	//----------------------------------------------------------------------
//==============================================================================
