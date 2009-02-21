/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <hparser/linked-section.hpp>

#include "descr.hpp"
#include "change-output.hpp"

//Class Descr2Data--------------------------------------------------------------
//Data element for second descriptor example
class Descr2Data :
	public linked_section,
	public ChangeOutput
{
public:
	Descr2Data(const Descr&);

	//From 'storage_section'------------------------------------------------
	section_releaser copy() const;
	//----------------------------------------------------------------------

	//From 'input_receiver'-------------------------------------------------
	bool expand_data(composite_data&);
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	bool collect_data(composite_data&) const;
	//----------------------------------------------------------------------

	//From 'comm_line'------------------------------------------------------
	bool local_message(comm_message&);
	//----------------------------------------------------------------------

	//From 'triggered_update'-----------------------------------------------
	bool local_update();
	//----------------------------------------------------------------------

	//From 'parent_storage'-------------------------------------------------
	location_count storage_size() const;
	//----------------------------------------------------------------------

private:
	Descr SectionDescriptor;
	//element descriptor

	std::string Data;
	//Element data
}; //END------------------------------------------------------------------------
