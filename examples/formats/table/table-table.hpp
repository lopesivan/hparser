/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <string>

#include <hparser/output-control.hpp>
#include <hparser/formats/descriptor-storage.hpp>

#include "section-filter.hpp"
#include "table-descr.hpp"

//Class TableTable--------------------------------------------------------------
//Table element for table example
class TableTable :
	public SectionFilter,
	public descriptor_input,
	public output_control
{
public:
	TableTable(const TableDescr&);

	//From 'storage_section'------------------------------------------------
	section_releaser copy() const;
	//----------------------------------------------------------------------

	//From 'parent_storage'-------------------------------------------------
	location_count next_location() const;
	location_count child_location() const;
	//----------------------------------------------------------------------

	//Table exportation=====================================================
	//From 'output_sender'--------------------------------------------------
	const output_sender *send_data(data_output*) const;
	//----------------------------------------------------------------------
	//======================================================================

	//Data content exportation==============================================
	//From 'output_sender'--------------------------------------------------
	bool collect_data(composite_data&) const;
	//----------------------------------------------------------------------
	//======================================================================

	//From 'triggered_update'-----------------------------------------------
	bool local_update();
	//----------------------------------------------------------------------

private:
	//From 'descriptor_input'-----------------------------------------------
	bool section_complete(data_input*) const;
	bool makes_sense(data_input*) const;
	bool is_subsection(data_input*) const;
	input_receiver *new_subsection(data_input*);
	input_receiver *apply_input(data_input*);
	input_receiver *get_in_parent() const;
	//----------------------------------------------------------------------

	TableDescr SectionDescriptor;
	//element descriptor

	std::string Data;
	//Element data
}; //END------------------------------------------------------------------------
