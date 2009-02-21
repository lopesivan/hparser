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

#ifndef STRUCTURE_BASE_CPP
#define STRUCTURE_BASE_CPP

#include "structure-base.hpp"
#include "storage-section.hpp"

//structure_base function bodies================================================
	structure_base::structure_base() :
	owning_tree(0 /*NULL*/),
	first_element(0 /*NULL*/) {}
	//Constructor

	structure_base::structure_base(const structure_base &eEqual) :
	owning_tree(0 /*NULL*/),
	first_element(0 /*NULL*/)
	{ this->add_branch( parent_storage::copy_all(eEqual.first_branch()) ); }
	//Copy constructor

	structure_base &structure_base::operator = (const structure_base &eEqual)
	//Assignment operator
	{
	if (&eEqual == this) return *this;
	this->set_child( parent_storage::copy_all(eEqual.first_branch()) );
	return *this;
	}

	//From 'CommLine'=======================================================
	bool structure_base::send_message(comm_message &mMessage)
	//Send a message
	{
	//Apply the message locally
	this->local_message(mMessage);

	//Apply the message to the tree
	if (this->first_branch())
	return this->first_branch()->send_message(mMessage);

	return true;
	}
	//======================================================================

	//From 'triggered_update'===============================================
	bool structure_base::global_update()
	//Update object data globally
	{
	//Update the base
	if (!this->local_update()) return false;

	//Update the tree
	if (this->first_branch() && !this->first_branch()->global_update())
	return false;

	return true;
	}
	//======================================================================

	//From 'parent_storage'=================================================
	section_releaser structure_base::set_child(section_releaser cChild)
	//Sets the first child element
	{
	//This function is modeled after 'linked_section' behavior; the current
	//first child is replaced by the argument, and the displaced child is
	//returned with everything past it still left attached.  This detaches
	//the entire tree and replaces it.

	//check for ownership first
	if (cChild && cChild->owner()) return section_releaser(0 /*NULL*/);

	//replace child
	storage_section *OldChild = first_element;
	if (OldChild)
	 {
	OldChild->disconnect();
	parent_storage::set_parent(OldChild, 0 /*NULL*/);
	 }

	//This saves a lot of time since branch removal results in the base
	//being isoloated
	this->switch_trees(0 /*NULL*/);

	this->merge_to_tree( parent_storage::borrow_section(cChild) );
	first_element = parent_storage::borrow_section(cChild);

	//set new child's parent to 'this'
	parent_storage::set_parent(first_element, this);

	//set old child's parent to 0 /*NULL*/ making it ownerless
	parent_storage::set_parent(OldChild, 0 /*NULL*/);

	if (first_element) first_element->connect();

	//return old child
	return section_releaser(OldChild);
	}
	//======================================================================

	structure_base::~structure_base()
	//Destructor
	{ this->set_child(section_releaser(0 /*NULL*/)); }

	//Tree branch management================================================
	storage_section *structure_base::first_branch() const
	//Provides a pointer to the first branch
	{ return first_element; }

	section_releaser structure_base::add_branch(section_releaser nNew)
	//Adds a new branch to the tree and returns it
	{
	if (this->first_branch()) this->first_branch()->add_next(nNew);
	else                     this->set_child(nNew);

	if (this->first_branch()) return section_releaser( this->first_branch()->last() );
	else                     return section_releaser(0 /*NULL*/);
	}
	//======================================================================

	//tree_number control===================================================
	verified_element *structure_base::tree_base()
	//Determine the base of the tree
	{ return this; }

	void structure_base::change_tree(tree_number *tTree)
	//Recursively change trees
	{
	if (this->get_tree_number() == tTree) return;
	this->switch_trees(tTree);
	verified_element::change_tree(this->first_branch(), tTree);
	}

	void structure_base::set_tree_number(tree_number *nNumber)
	//Set the tree number of this element
	{ owning_tree = nNumber; }

	tree_number *structure_base::get_tree_number() const
	//Get the tree number of this element
	{ return owning_tree; }
	//======================================================================
//==============================================================================

#endif
