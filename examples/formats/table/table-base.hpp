/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <hparser/data-input.hpp>
#include <hparser/data-output.hpp>

#include "base-filter.hpp"

//Class TableBase---------------------------------------------------------------
//Tree base for table example
class TableBase :
	public BaseFilter,
	public data_importer,
	public data_exporter
{
public:
	TableBase();

	//From 'data_importer'--------------------------------------------------
	input_receiver *import_data(data_input*);
	//----------------------------------------------------------------------

	//From 'data_exporter'--------------------------------------------------
	const output_sender *export_data(data_output*) const;
	//----------------------------------------------------------------------

protected:
	//From 'input_resource_owner'-------------------------------------------
	input_resource *get_input_resource();
	//----------------------------------------------------------------------

private:
	input_resource *Resources;
}; //END------------------------------------------------------------------------
