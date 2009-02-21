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

#ifndef VERIFIED_ELEMENT_CPP
#define VERIFIED_ELEMENT_CPP

#include "verified-element.hpp"

//verified_element function bodies==============================================
	//tree_number control===================================================
	bool verified_element::merge_to_tree(verified_element *eElement)
	//Merge tree numbers (before merge)
	{
	if (!eElement) return true;

	verified_element *Left  = this->tree_base(),
		        *Right = eElement->tree_base();

	if (!Left->get_tree_number() && !Right->get_tree_number())
	//Create a new tree
	 {
	tree_number *NewTree = new tree_number(0);
	if (!NewTree) return false;
	Left->change_tree(NewTree);
	Right->change_tree(NewTree);
	 }

	else if (!Left->get_tree_number())
	//Copy this tree reference
	Left->change_tree( Right->get_tree_number() );

	else if (!Right->get_tree_number())
	//Copy the other tree reference
	Right->change_tree( Left->get_tree_number() );

	else
	//Determine the smallest tree and use the other reference
	 {
	if (*Left->get_tree_number() < *Right->get_tree_number())
	Left->change_tree( Right->get_tree_number() );

	else
	Right->change_tree( Left->get_tree_number() );
	 }

	return true;
	}

	bool verified_element::split_from_tree(verified_element *eElement)
	//Split tree numbers (after split)
	{
	if (!eElement) return true;

	//No need to go to the top of the tree for this call
	tree_number *NewTree = new tree_number(0);
	if (!NewTree) return false;
	eElement->change_tree(NewTree);

	return true;
	}

	bool verified_element::same_tree(const verified_element *eElement) const
	//Compare trees
	{
	//Two NULL trees aren't equal
	return eElement && this->get_tree_number() &&
	  this->get_tree_number() == eElement->get_tree_number();
	}

	bool verified_element::switch_trees(tree_number *nNumber)
	//Switch tree references
	{
	if (nNumber) ++(*nNumber);

	if (this->get_tree_number())
	if (--(*this->get_tree_number()) == 0) delete this->get_tree_number();

	this->set_tree_number(nNumber);

	return true;
	}

	void verified_element::change_tree(verified_element *eElement,
	tree_number *tTree)
	//Recursively change trees
	{ if (eElement) eElement->change_tree(tTree); }
	//======================================================================
//==============================================================================

#endif
