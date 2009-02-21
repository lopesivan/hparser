/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "base-filter.hpp"

#include <hparser/storage-section.hpp>
#include <hparser/classes/string-output.hpp>

//BaseFilter function bodies====================================================
	//From 'output_sender'--------------------------------------------------
	bool BaseFilter::output_filter(output_section &oOutput) const
	{
	//add a line prefix when in display mode
	if (OutputMode) oOutput.insert(0, "-> ");
	return true;
	}
	//----------------------------------------------------------------------

	//From 'comm_line'------------------------------------------------------
	bool BaseFilter::local_message(comm_message &mMessage)
	{
	this->ChangeMode(mMessage);
	return true;
	}
	//----------------------------------------------------------------------
//==============================================================================
