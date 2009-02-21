/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <string>

#include <hparser/linked-section.hpp>

#include "section-filter.hpp"
#include "table-descr.hpp"

//Class TableData---------------------------------------------------------------
//Data element for tree example
class TableData :
	public SectionFilter
{
public:
	TableData(const TableDescr&);

	//From 'storage_section'------------------------------------------------
	section_releaser copy() const;
	//----------------------------------------------------------------------

	//Table parsing/exportation=============================================
	//From 'input_receiver'-------------------------------------------------
	input_receiver *receive_data(data_input*);
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	const output_sender *send_data(data_output*) const;
	//----------------------------------------------------------------------
	//======================================================================

	//Data content exportation==============================================
	//From 'output_sender'--------------------------------------------------
	bool collect_data(composite_data&) const;
	//----------------------------------------------------------------------
	//======================================================================

	//From 'parent_storage'-------------------------------------------------
	location_count next_location() const;
	//----------------------------------------------------------------------

	//From 'triggered_update'-----------------------------------------------
	bool local_update();
	//----------------------------------------------------------------------

private:
	TableDescr SectionDescriptor;
	//element descriptor

	std::string Data;
	//Element data
}; //END------------------------------------------------------------------------
