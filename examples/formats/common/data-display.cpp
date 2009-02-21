/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "data-display.hpp"

#include <iostream>

#include <hparser/classes/string-output.hpp>

//DataDisplay function bodies===================================================
	//From 'data_output'----------------------------------------------------
	bool DataDisplay::send_output(const output_section &oOutput)
	{ std::cout << oOutput; return true; }

	bool DataDisplay::is_closed() const
	{ return false; }
	//----------------------------------------------------------------------
//==============================================================================
