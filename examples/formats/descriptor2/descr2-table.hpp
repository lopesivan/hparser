/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "section-filter.hpp"
#include "descr.hpp"


//Class Descr2Table-------------------------------------------------------------
//Table element for second descriptor example
class Descr2Table :
	public SectionFilter
{
public:
	Descr2Table(const Descr&);

	//From 'storage_section'------------------------------------------------
	section_releaser copy() const;
	//----------------------------------------------------------------------

	//From 'input_receiver'-------------------------------------------------
	bool expand_data(composite_data&);
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	bool collect_data(composite_data&) const;
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
}; //END------------------------------------------------------------------------
