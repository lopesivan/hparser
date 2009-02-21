/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <hparser/parent-storage.hpp>
#include <hparser/data-input.hpp>
#include <hparser/data-output.hpp>

#include "base-filter.hpp"

//Struct Descr2Base-------------------------------------------------------------
//Tree base for second descriptor example
struct Descr2Base :
	public BaseFilter,
	public data_importer,
	public data_exporter
{
	//From 'data_importer'--------------------------------------------------
	input_receiver *import_data(data_input*);
	//----------------------------------------------------------------------

	//From 'data_exporter'--------------------------------------------------
	const output_sender *export_data(data_output*) const;
	//----------------------------------------------------------------------
}; //END------------------------------------------------------------------------
