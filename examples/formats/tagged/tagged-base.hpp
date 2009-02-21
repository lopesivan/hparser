/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <hparser/data-manager.hpp>
#include <hparser/storage-section.hpp>

#include "base-filter.hpp"

//Struct TaggedBase-------------------------------------------------------------
//Tree base for tagged example
struct TaggedBase :
	public BaseFilter,
	public data_manager
{
	//From 'input_receiver'-------------------------------------------------
	input_receiver *receive_data(data_input*);
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	const output_sender *send_data(data_output*) const;
	//----------------------------------------------------------------------
}; //END------------------------------------------------------------------------
