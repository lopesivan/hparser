/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "table-base.hpp"

#include <hparser/classes/string-input.hpp>
#include <hparser/classes/string-output.hpp>
#include <hparser/classes/string-composite.hpp>

#include "modes.hpp"
#include "table-table.hpp"
#include "table-descr.hpp"

//TableBase function bodies=====================================================
	TableBase::TableBase() : Resources(0 /*NULL*/) {}

	//From 'data_importer'--------------------------------------------------
	input_receiver *TableBase::import_data(data_input *iInput)
	{
	//check for a NULL input source
	if (!iInput) return 0 /*NULL*/;

	//set the input mode to 'other' (non-tag format)
	if (!iInput->set_input_mode(Other)) return 0 /*NULL*/;

	//for the new element
	storage_section *NewSection = 0 /*NULL*/;

	//working descriptor
	TableDescr New;

	//parse the descriptor and take its size
	unsigned int NewSize = New.TakeDescriptor(iInput->receive_input());

	//if it isn't valid or isn't a table then return an error
	if (!New.IsValid() || !New.IsTable()) return 0 /*NULL*/;

	//add a new branch using the descriptor
	this->add_branch( NewSection = new TableTable(New) );

	//clear the descriptor from the input buffer
	iInput->next_input(NewSize);

	//copied from 'input_manager'
	input_receiver *Current = this->first_branch();
	while (Current && Current != this) Current = Current->receive_data(iInput);

	if (!Current)
	 {
	iInput->replace_buffer();
	return 0 /*NULL*/;
	 }

	//set resources for the tree
	Resources = input_resource_owner::get_input_resource(iInput);
	if (Resources) Resources->set_input_index();

	return Current;
	}
	//----------------------------------------------------------------------

	//From 'data_exporter'--------------------------------------------------
	const output_sender *TableBase::export_data(data_output *oOutput) const
	{
	//check for a NULL output destination
	if (!oOutput) return 0 /*NULL*/;

	//Stage 1: table exportation============================================
	//copied from 'data_exporter'
	const output_sender *Current = this->first_branch();
	while (Current && Current != this) Current = Current->send_data(oOutput);
	//======================================================================

	//Skip the next part when displaying on screen
	if (OutputMode) return this;

	//Stage 2: data collection==============================================
	//for entire first table data
	composite_data Output;

	//collect the table data
	if (this->first_branch() && !this->first_branch()->collect_data(Output)) return NULL;

	//send the table data to output
	if (oOutput->send_output(Output)) return this;
	//======================================================================

	return 0 /*NULL*/;
	}
	//----------------------------------------------------------------------

	//From 'input_resource_owner'-------------------------------------------
	input_resource *TableBase::get_input_resource()
	{ return Resources; }
	//----------------------------------------------------------------------
//==============================================================================
