/* This software is released under the BSD License.
 |
 | Copyright (c) 2008, Kevin P. Barry [the hparser project]
 | All rights reserved.
 |
 | Redistribution  and  use  in  source  and   binary  forms,  with  or  without
 | modification, are permitted provided that the following conditions are met:
 |
 | - Redistributions of source code must retain the above copyright notice, this
 |   list of conditions and the following disclaimer.
 |
 | - Redistributions in binary  form must reproduce the  above copyright notice,
 |   this list  of conditions and the following disclaimer in  the documentation
 |   and/or other materials provided with the distribution.
 |
 | - Neither the  name  of  the  Resourcerver  Project  nor  the  names  of  its
 |   contributors may be  used to endorse or promote products  derived from this
 |   software without specific prior written permission.
 |
 | THIS SOFTWARE IS  PROVIDED BY THE COPYRIGHT HOLDERS AND  CONTRIBUTORS "AS IS"
 | AND ANY  EXPRESS OR IMPLIED  WARRANTIES,  INCLUDING, BUT  NOT LIMITED TO, THE
 | IMPLIED WARRANTIES OF  MERCHANTABILITY  AND FITNESS FOR A  PARTICULAR PURPOSE
 | ARE DISCLAIMED.  IN  NO EVENT SHALL  THE COPYRIGHT  OWNER  OR CONTRIBUTORS BE
 | LIABLE  FOR  ANY  DIRECT,   INDIRECT,  INCIDENTAL,   SPECIAL,  EXEMPLARY,  OR
 | CONSEQUENTIAL   DAMAGES  (INCLUDING,  BUT  NOT  LIMITED  TO,  PROCUREMENT  OF
 | SUBSTITUTE GOODS OR SERVICES;  LOSS  OF USE,  DATA,  OR PROFITS;  OR BUSINESS
 | INTERRUPTION)  HOWEVER  CAUSED  AND ON  ANY  THEORY OF LIABILITY,  WHETHER IN
 | CONTRACT,  STRICT  LIABILITY, OR  TORT (INCLUDING  NEGLIGENCE  OR  OTHERWISE)
 | ARISING IN ANY  WAY OUT OF  THE USE OF THIS SOFTWARE, EVEN  IF ADVISED OF THE
 | POSSIBILITY OF SUCH DAMAGE.
 +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef OPERATORS_CPP
#define OPERATORS_CPP

#include "operators.hpp"

//storage_section functions-----------------------------------------------------
bool swap_elements(storage_section *lLeft, storage_section *rRight)
//Swap element positions
{
	//vertical ownership is a problem, but lateral is not

	if (!lLeft || !rRight) return false;
	if (lLeft == rRight)   return false;
	if (*lLeft != *rRight) return false;

	bool Lateral = false;
	storage_section *Upper = 0 /*NULL*/;
	storage_section *Lower = 0 /*NULL*/;

	if (lLeft->owner() && rRight->owner())
	//both are owned========================================================
	{
	if (*lLeft >= *rRight)
	//forward ownership-----------------------------------------------------
	 {
	Lateral = true;
	Upper   = lLeft;
	Lower   = rRight;
	 }
	//----------------------------------------------------------------------

	else if (*lLeft <= *rRight)
	//reverse ownership-----------------------------------------------------
	 {
	Lateral = true;
	Upper   = rRight;
	Lower   = lLeft;
	 }
	//----------------------------------------------------------------------

	if (Lateral && Upper && Lower)
	//Lateral ownership-----------------------------------------------------
	 {
	if (Lower != Upper->next())
	  {
	if (!Lower->allow_next(Upper->next())) return false;
	  }
	else
	  {
	if (!Lower->allow_next(Upper)) return false;
	  }

	if (!Upper->allow_next(Lower->next())) return false;
	if (!Lower->allow_here(Upper)) return false;
	if (!Upper->allow_here(Lower)) return false;

	section_releaser Right( Lower->splice_here(0 /*NULL*/) );
	section_releaser Left( Upper->splice_here(Right) );
	section_releaser Left2( Upper->set_next(0 /*NULL*/) );
	section_releaser Right2( Lower->set_next(Left2) );
	Upper->add_next(Right2);
	Lower->add_next(Upper);

	return true;
	 }
	//----------------------------------------------------------------------

	else
	//no ownership related--------------------------------------------------
	 {
	if (!rRight->allow_next(lLeft->next())) return false;
	if (!lLeft->allow_next(rRight->next())) return false;
	if (!rRight->allow_here(lLeft)) return false;
	if (!lLeft->allow_here(rRight)) return false;

	storage_section *Previous = 0 /*NULL*/;
	parent_storage  *Owner    = 0 /*NULL*/;
	bool FirstChild = false;

	Owner = lLeft->owner();
	FirstChild = Owner != lLeft->previous();
	if (!FirstChild) Previous = lLeft->previous();
	if (!Owner) return false;

	section_releaser Left( lLeft->splice_here(0 /*NULL*/) );
	section_releaser Right( rRight->set_next(0 /*NULL*/) );
	section_releaser Left2( lLeft->set_next(Right) );
	section_releaser Right2( rRight->splice_here(Left) );
	section_releaser Right3( rRight->add_next(Left2) );

	if (FirstChild || !Previous) rRight->add_next( Owner->set_child(rRight) );
	else                         Previous->add_next(rRight);

	return true;
	 }
	//----------------------------------------------------------------------
	}
	//======================================================================

	else if (!lLeft->owner() && !rRight->owner())
	//neither are owned=====================================================
	{
	if (!rRight->allow_next(lLeft->next())) return false;
	if (!lLeft->allow_next(rRight->next())) return false;

	section_releaser Left( lLeft->set_next(0 /*NULL*/) );
	section_releaser Right( rRight->set_next(Left) );
	lLeft->add_next(Right);

	return true;
	}
	//======================================================================

	//default for one is owned and other isn't is an error
	else return false;
}

bool operator >> (const storage_section &lLeft, const storage_section &rRight)
//Left element laterally/vertically owns the right
{
	if (&lLeft == &rRight) return false;
	const parent_storage *Current = &rRight;

	while (Current && Current != &lLeft)
	{
	const storage_section *Inner = &lLeft;
	while (Inner && Inner != Current) Inner = Inner->next();
	if (Inner == Current) return true;

	Current = Current->parent();
	}

	return Current == &lLeft;
}

bool operator << (const storage_section &lLeft, const storage_section &rRight)
//Right element laterally/vertically owns the left
{
	if (&lLeft == &rRight) return false;
	const parent_storage *Current = &lLeft;

	while (Current && Current != &rRight)
	{
	const storage_section *Inner = &rRight;
	while (Inner && Inner != Current) Inner = Inner->next();
	if (Inner == Current) return true;

	Current = Current->parent();
	}

	return Current == &rRight;
}

bool operator > (const storage_section &lLeft, const storage_section &rRight)
//Left element vertically owns the right
{
	if (&lLeft == &rRight) return false;
	const parent_storage *Current = &rRight;
	while (Current && Current != &lLeft) Current = Current->parent();
	return Current == &lLeft;
}

bool operator < (const storage_section &lLeft, const storage_section &rRight)
//Right element vertically owns the left
{
	if (&lLeft == &rRight) return false;
	const parent_storage *Current = &lLeft;
	while (Current && Current != &rRight) Current = Current->parent();
	return Current == &rRight;
}

bool operator == (const storage_section &lLeft, const storage_section &rRight)
{ return !(lLeft < rRight || lLeft > rRight); }
//Neither element vertically owns the other

bool operator != (const storage_section &lLeft, const storage_section &rRight)
{ return lLeft < rRight || lLeft > rRight; }
//One element vertically owns the other

bool operator >= (const storage_section &lLeft, const storage_section &rRight)
//Left element laterally owns the right
{
	if (&lLeft == &rRight) return false;
	const storage_section *Current = &lLeft;
	while (Current && Current != &rRight) Current = Current->next();
	return Current == &rRight;
}

bool operator <= (const storage_section &lLeft, const storage_section &rRight)
//Right element laterally owns the left
{
	if (&lLeft == &rRight) return false;
	const storage_section *Current = &rRight;
	while (Current && Current != &lLeft) Current = Current->next();
	return Current == &lLeft;
}

bool operator && (const storage_section &lLeft, const storage_section &rRight)
//Two elements are on the same lateral path
{
	return lLeft.parent() == rRight.parent() ||
	       lLeft >= rRight || lLeft <= rRight;
}

bool operator ^ (const storage_section &lLeft, const storage_section &rRight)
//Two elements are not on the same lateral path
{
	return !( lLeft.parent() == rRight.parent() ||
	          lLeft >= rRight || lLeft <= rRight );
}

bool operator || (const storage_section &lLeft, const storage_section &rRight)
{ return !(lLeft << rRight || lLeft >> rRight); }
//Two elements are on completely independent trees
//END---------------------------------------------------------------------------

#endif
