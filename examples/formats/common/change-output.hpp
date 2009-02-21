/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

//The 'ChangeOutput' class provides automatic output mode management.

#ifndef CHANGE_OUTPUT
#define CHANGE_OUTPUT

#include <hparser/comm-line.hpp>

//Class ChangeOutput------------------------------------------------------------
//Output mode manager
class ChangeOutput :
	virtual public comm_line
{
public:
	ChangeOutput();

	//Output mode management------------------------------------------------
	bool ChangeMode(comm_message&);
	//----------------------------------------------------------------------

protected:
	bool OutputMode;
	//Output mode flag
}; //END------------------------------------------------------------------------

#endif
