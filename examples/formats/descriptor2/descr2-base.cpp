/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "descr2-base.hpp"

#include <hparser/classes/string-input.hpp>
#include <hparser/classes/string-output.hpp>
#include <hparser/classes/string-composite.hpp>

#include "modes.hpp"
#include "descr2-table.hpp"
#include "descr.hpp"

//Descr2Base function bodies====================================================
	//From 'data_importer'--------------------------------------------------
	input_receiver *Descr2Base::import_data(data_input *iInput)
	{
	//check for a NULL input source
	if (!iInput) return 0 /*NULL*/;

	//set the input mode to 'other' (non-tag format)
	if (!iInput->set_input_mode(Other)) return 0 /*NULL*/;

	//for the new element
	storage_section *NewSection = 0 /*NULL*/;

	//working descriptor
	Descr New;

	//parse the descriptor and take its size
	unsigned int NewSize = New.TakeDescriptor(iInput->receive_input());

	//if it isn't valid or isn't a table then return an error
	if (!New.IsValid() || !New.IsTable()) return 0 /*NULL*/;

	//add a new branch using the descriptor
	this->add_branch( NewSection = new Descr2Table(New) );

	//clear the descriptor from the input buffer
	iInput->next_input(NewSize);

	//for entire first table data
	composite_data Input;

	while (Input.size() < New.GetSize())
	//read input until entire first table is read___________________________
	 {
	Input += iInput->receive_input();

	//check for end of data
	if (iInput->end_of_data()) break;

	//clear buffer
	iInput->next_input();
	 }
	//______________________________________________________________________

	if (Input.size() > New.GetSize())
	//replace buffer if there's anything left_______________________________
	 {
	iInput->replace_buffer(Input.size() - New.GetSize());
	Input.erase(Input.begin() + New.GetSize(), Input.end());
	 }
	//______________________________________________________________________

	//expand the table data
	if (this->first_branch() && this->first_branch()->expand_data(Input)) return this;

	return 0 /*NULL*/;
	}
	//----------------------------------------------------------------------

	//From 'data_exporter'--------------------------------------------------
	const output_sender *Descr2Base::export_data(data_output *oOutput) const
	{
	//check for a NULL output destination
	if (!oOutput) return 0 /*NULL*/;

	//for entire first table data
	composite_data Output;

	//collect the table data
	if (this->first_branch() && !this->first_branch()->collect_data(Output)) return NULL;

	//send the table data to output
	if (oOutput->send_output(Output)) return this;

	return 0 /*NULL*/;
	}
	//----------------------------------------------------------------------
//==============================================================================
