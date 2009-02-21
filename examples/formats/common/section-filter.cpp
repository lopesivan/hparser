/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "section-filter.hpp"

#include <hparser/classes/string-output.hpp>

//SectionFilter function bodies=================================================
	//From 'output_sender'--------------------------------------------------
	bool SectionFilter::output_filter(output_section &oOutput) const
	{
	//insert spaces if displaying, otherwise use the dynamic separator
	if (OutputMode) oOutput.insert(0, "  ");
	else            oOutput.insert(0, Separator);

	//execute the default filter action
	return this->linked_section::output_filter(oOutput);
	}
	//----------------------------------------------------------------------

	//From 'comm_line'------------------------------------------------------
	bool SectionFilter::local_message(comm_message &mMessage)
	{
	this->ChangeMode(mMessage);
	return true;
	}
	//----------------------------------------------------------------------
//==============================================================================
