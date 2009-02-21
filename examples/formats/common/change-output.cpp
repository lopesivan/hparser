/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "change-output.hpp"

#include <hparser/classes/string-message.hpp>

//ChangeOutput function bodies==================================================
	ChangeOutput::ChangeOutput() : OutputMode(true) {}

	//Output mode management------------------------------------------------
	bool ChangeOutput::ChangeMode(comm_message &mMessage)
	{
	if (mMessage == "DISPLAY")     OutputMode = true;
	else if (mMessage == "OUTPUT") OutputMode = false;
	else                           return false;

	return true;
	}
	//----------------------------------------------------------------------
//==============================================================================
