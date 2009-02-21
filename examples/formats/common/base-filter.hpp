/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

//The 'BaseFilter' class provides basic output filtering for all of the example
//tree bases.  This class also handles ownership and deletion of the base
//element of the tree it contains.  Filtering is done via the 'output_filter'
//function.  This class provides a few basic functions to allow the derived
//classes to add tree branches.

#include <string>

#include <hparser/structure-base.hpp>

#include "change-output.hpp"

//Struct BaseFilter-------------------------------------------------------------
//Base class for tree bases
struct BaseFilter :
	public structure_base,
	public ChangeOutput
{
	//From 'output_sender'--------------------------------------------------
	bool output_filter(output_section&) const;
	//----------------------------------------------------------------------

	//From 'comm_line'------------------------------------------------------
	bool local_message(comm_message&);
	//----------------------------------------------------------------------
}; //END------------------------------------------------------------------------
