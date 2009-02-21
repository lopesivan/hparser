/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

//The 'SectionFilter' is a base class for tree elements which can hold other
//elements.  This class provides output filtering via the 'OutputFiler'
//function.

#ifndef SECTION_FILTER
#define SECTION_FILTER

#include <string>

#include <hparser/linked-section.hpp>

#include "change-output.hpp"

//Class SectionFilter-----------------------------------------------------------
//Base class for parent elements
class SectionFilter :
	public linked_section,
	public ChangeOutput
{
public:
	//From 'output_sender'--------------------------------------------------
	bool output_filter(output_section&) const;
	//----------------------------------------------------------------------

	//From 'comm_line'------------------------------------------------------
	bool local_message(comm_message&);
	//----------------------------------------------------------------------

protected:
	std::string Separator;
	//Data output separator
}; //END------------------------------------------------------------------------

#endif
