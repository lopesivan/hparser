/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "descr-base.hpp"

#include "modes.hpp"
#include "descr-table.hpp"
#include "descr.hpp"

//DescrBase function bodies=====================================================
	//From 'input_receiver'-------------------------------------------------
	input_receiver *DescrBase::receive_data(data_input *iInput)
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
	this->add_branch( NewSection = new DescrTable(New) );

	//clear the descriptor from the input buffer
	iInput->next_input(NewSize);

	return NewSection;
	}
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	const output_sender *DescrBase::send_data(data_output*) const
	{ return this->first_branch(); }
	//----------------------------------------------------------------------
//==============================================================================
