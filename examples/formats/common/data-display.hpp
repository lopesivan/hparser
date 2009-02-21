/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

//The 'DataDisplay' class displays output on standard output.  This is the most
//basic data output class.

#include <hparser/data-output.hpp>

//Struct DataDisplay------------------------------------------------------------
//Generic data tree display class
struct DataDisplay :
	public data_output
{
	//From 'data_output'----------------------------------------------------
	bool send_output(const output_section&);
	bool is_closed() const;
	//----------------------------------------------------------------------
}; //END------------------------------------------------------------------------
