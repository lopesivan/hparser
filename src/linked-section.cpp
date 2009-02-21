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

#ifndef LINKED_SECTION_CPP
#define LINKED_SECTION_CPP

#include "linked-section.hpp"

//linked_section function bodies================================================
	//Message sending interface=============================================
	bool linked_section::send_message(comm_message &mMessage)
	//Send a message
	{
	//Apply the message locally
	this->local_message(mMessage);

	//Send the message to children
	if (this->child() && !this->child()->send_message(mMessage))
	return false;

	//Send the message to peers
	if (this->next() && !this->next()->send_message(mMessage))
	return false;

	return true;
	}
	//======================================================================

	//Data filters==========================================================
	bool linked_section::input_filter(input_section &iInput)
	//Filter input data
	{ return this->parent()? this->parent()->input_filter(iInput) : true; }

	bool linked_section::output_filter(output_section &oOutput) const
	//Filter output data
	{ return this->parent()? this->parent()->output_filter(oOutput) : true; }
	//======================================================================

	//Element updating======================================================
	bool linked_section::global_update()
	//Update object data globally
	{
	//Update branch
	if (!this->branch_update()) return false;

	//Update peers
	if (this->next() && !this->next()->global_update()) return false;

	return true;
	}

	bool linked_section::branch_update()
	//Update object data in branch only
	{
	//Update children
	if (this->child() && !this->child()->global_update()) return false;

	//Update this element
	if (!this->local_update()) return false;

	return true;
	}

	bool linked_section::hierarchy_update()
	//Update object data in entire hierarchy
	{
	parent_storage *Base = this->hierarchy_base();
	if (Base) return Base->global_update();
	else      return false;
	}
	//======================================================================

	linked_section::linked_section() :
	owning_tree(0 /*NULL*/),
	next_element(0 /*NULL*/),
	child_element(0 /*NULL*/),
	previous_element(0 /*NULL*/),
	parent_element(0 /*NULL*/) { }
	//Constructor

	linked_section::linked_section(const linked_section &eEqual) :
	owning_tree(0 /*NULL*/),
	next_element(0 /*NULL*/),
	child_element(0 /*NULL*/),
	previous_element(0 /*NULL*/),
	parent_element(0 /*NULL*/)
	//Copy constructor
	{ this->add_child( parent_storage::copy_all(eEqual.child()) ); }

	linked_section &linked_section::operator = (const linked_section &eEqual)
	//Assignment operator
	{
	if (&eEqual == this) return *this;

	this->set_child( parent_storage::copy_all(eEqual.child()) );

	return *this;
	}

	//Last element in hierarchy=============================================
	storage_section *linked_section::last() const
	//Obtain the last data element
	{
	if (this->next()) return this->next()->last();
	else              return const_cast <linked_section*> (this);
	}
	//======================================================================

	//Next element in hierarchy=============================================
	storage_section *linked_section::next() const
	{ return next_element; }
	//Obtain the next data element

	section_releaser linked_section::add_next(section_releaser nNext)
	//Add a data element to the chain
	{
	if (!nNext && this->allow_next(nNext)) return nNext.set_result(true);
	if (nNext == this)           return nNext.set_result(false);
	if (nNext && nNext->owner()) return nNext.set_result(false);

	if (this->next()) return this->next()->add_next(nNext);

	section_releaser Holding( this->set_next(nNext) );
	return Holding.result()? section_releaser(this->next()) : Holding;
	}

	section_releaser linked_section::insert_next(section_releaser nNext)
	//Insert a data element to the chain
	{
	if (nNext == this)           return nNext.set_result(false);
	if (nNext && nNext->owner()) return nNext.set_result(false);

	if (this->next()) return this->next()->insert_here(nNext);
	else              return this->add_next(nNext);
	}

	section_releaser linked_section::set_next(section_releaser nNext)
	//Sets the next data element
	{
	if (nNext == this)           return nNext.set_result(false);
	if (nNext && nNext->owner()) return nNext.set_result(false);
	if (!this->lineage_check(nNext)) return nNext.set_result(false);
	if (!this->allow_next(nNext))    return nNext.set_result(false);

	storage_section *OldNext = next_element;
	next_element = 0 /*NULL*/;
	if (OldNext)
	 {
	OldNext->disconnect();
	parent_storage::set_parent(OldNext, 0 /*NULL*/);

	//Tree number set to NULL during destruction
	if (this->get_tree_number())
	  {
	if (!this->child() && !this->parent())
	this->switch_trees(0 /*NULL*/);

	else
	verified_element::split_from_tree(OldNext);
	  }
	 }

	this->merge_to_tree( parent_storage::borrow_section(nNext) );

	next_element = parent_storage::borrow_section(nNext);
	storage_section::set_previous(this->next(), this);
	parent_storage::set_parent(this->next(), this->parent());
	if (this->next()) this->next()->connect();

	return section_releaser( linked_section::set_free(OldNext), true );
	}
	//======================================================================

	//Cut hierarchy here and replace========================================
	section_releaser linked_section::splice_here(section_releaser hHere)
	//Removes this and all following elements and replaces
	{
	if (hHere == this)           return hHere.set_result(false);
	if (hHere && hHere->owner()) return hHere.set_result(false);
	if (!this->owner())          return hHere.set_result(false);

	if (this->previous())    return this->previous()->set_next(hHere);
	else if (this->parent()) return this->parent()->set_child(hHere);
	else                     return hHere.set_result(false);
	}
	//======================================================================

	//Remove from hierarchy=================================================
	section_releaser linked_section::remove_self()
	//Remove self from the tree
	{
	if (!this->owner()) return section_releaser(0 /*NULL*/, false);

	section_releaser Holding( this->set_next( section_releaser(0 /*NULL*/) ) );
	if (!Holding.result()) return Holding;

	return this->splice_here(Holding);
	}
	//======================================================================

	//Replace this element==================================================
	section_releaser linked_section::replace_self(section_releaser hHere)
	//Replaces this element with another
	{
	if (!hHere)                  return hHere.set_result(false);
	if (hHere == this)           return hHere.set_result(false);
	if (hHere && hHere->owner()) return hHere.set_result(false);
	if (!this->owner())          return hHere.set_result(false);

	section_releaser Holding( this->set_next( section_releaser(0 /*NULL*/) ) );
	if (!Holding.result()) return hHere.set_result(false);

	section_releaser Holding2( hHere->add_next(Holding) );
	if (!Holding2.result())
	//reconnect self to repair if there is an error
	 {
	this->set_next(Holding2);
	return hHere.set_result(false);
	 }

	return this->splice_here(Holding2);
	}
	//======================================================================

	//Insert element========================================================
	section_releaser linked_section::insert_here(section_releaser hHere)
	//Insert element in this current position
	{
	if (!hHere)                                      return hHere.set_result(false);
	if (hHere == this)                               return hHere.set_result(false);
	if (!hHere || (hHere->owner() && this->owner())) return hHere.set_result(false);

	if (!this->owner()) return hHere->add_next(this);

	section_releaser Holding( this->splice_here(hHere) );
	if (!Holding.result()) return Holding;

	return hHere->add_next(Holding);
	}
	//======================================================================

	//Remove element and promote children===================================
	section_releaser linked_section::promote_children()
	//Removes 'this' and promotes children
	{
	if (!this->owner()) return section_releaser(0 /*NULL*/, false);

	section_releaser Holding( this->set_child( section_releaser(0 /*NULL*/) ) );
	if (!Holding.result()) return Holding;
	return this->replace_self(Holding);
	}
	//======================================================================

	//Demote element and insert=============================================
	section_releaser linked_section::demote_self(section_releaser hHere)
	//Insert new element by moving 'this' down
	{
	if (!hHere)                                      return hHere.set_result(false);
	if (hHere == this)                               return hHere.set_result(false);
	if (!hHere || (hHere->owner() && this->owner())) return hHere.set_result(false);

	if (this->owner())
	 {
	section_releaser Holding( this->replace_self(hHere) );
	if (!Holding.result()) return Holding;
	return Holding? Holding->add_child(this) : Holding.set_result(false);
	 }

	else return hHere->add_child(this);
	}
	//======================================================================

	//Previous element in hierarchy=========================================
	storage_section *linked_section::previous() const
	{ return previous_element; }
	//Obtain the previous data element

	storage_section *linked_section::set_previous(storage_section *pPrev)
	//Set the previous data element
	{
	if (pPrev == this) return 0 /*NULL*/;

	previous_element = pPrev;
	return this;
	}
	//======================================================================

	//First element in hierarchy============================================
	storage_section *linked_section::first() const
	//Obtain the first data element
	{
	if (this->previous()) return this->previous()->first();
	else                  return const_cast <linked_section*> (this);
	}
	//======================================================================

	//Sub-element in hierarchy==============================================
	storage_section *linked_section::child() const
	{ return child_element; }
	//Obtain the first child element

	section_releaser linked_section::add_child(section_releaser cChild)
	//Add a child element
	{
	if (!cChild && this->allow_child(cChild)) return cChild.set_result(true);
	if (cChild == this)            return cChild.set_result(false);
	if (cChild && cChild->owner()) return cChild.set_result(false);

	if (this->child()) return this->child()->add_next(cChild);

	section_releaser Holding( this->set_child(cChild) );
	return Holding.result()? section_releaser(this->child()) : Holding;
	}

	section_releaser linked_section::insert_child(section_releaser cChild)
	//Insert a child element
	{
	if (cChild == this)            return cChild.set_result(false);
	if (cChild && cChild->owner()) return cChild.set_result(false);

	if (this->child()) return this->child()->insert_here(cChild);
	else               return this->add_child(cChild);
	}

	section_releaser linked_section::set_child(section_releaser cChild)
	//Sets the first child element
	{
	if (cChild == this)            return cChild.set_result(false);
	if (cChild && cChild->owner()) return cChild.set_result(false);
	if (!this->lineage_check(cChild)) return cChild.set_result(false);
	if (!this->allow_child(cChild))   return cChild.set_result(false);

	storage_section *OldChild = child_element;
	child_element = 0 /*NULL*/;
	if (OldChild)
	 {
	OldChild->disconnect();
	storage_section::set_previous(OldChild, 0 /*NULL*/);

	//Tree number set to NULL during destruction
	if (this->get_tree_number())
	  {
	if (!this->next() && !this->parent())
	this->switch_trees(0 /*NULL*/);

	else
	verified_element::split_from_tree(OldChild);
	  }
	 }

	this->merge_to_tree( parent_storage::borrow_section(cChild) );

	child_element = parent_storage::borrow_section(cChild);
	parent_storage::set_parent(this->child(), this);
	if (this->child()) this->child()->connect();

	return section_releaser( linked_section::set_free(OldChild), true );
	}
	//======================================================================

	//Parent element in hierarchy===========================================
	parent_storage *linked_section::parent() const
	{ return parent_element; }
	//Obtain the parent element

	parent_storage *linked_section::hierarchy_base() const
	//Find the base of the hierarchy
	{
	if (this->parent())        return this->parent()->hierarchy_base();
	else if (this->previous()) return this->previous()->hierarchy_base();
	else                       return const_cast <linked_section*> (this);
	}

	parent_storage *linked_section::branch_base() const
	//Find the base of the branch
	{
	if (this->parent()) return this->parent()->branch_base();
	else                return const_cast <linked_section*> (this);
	}

	parent_storage *linked_section::set_parent(parent_storage *pParent)
	//Set the parent element
	{
	if (pParent == this) return 0 /*NULL*/;

	parent_element = pParent;
	parent_storage *Return = this;

	if (this->next() && this->next()->parent() != this->parent())
	 {
	Return = parent_storage::set_parent(this->next(), this->parent());
	if (Return == this->next()) Return = this;
	 }

	return Return;
	}
	//======================================================================

	//Determine ownership of element========================================
	parent_storage *linked_section::owner() const
	//Determine who will delete this element
	{
	if (this->previous())    return this->previous();
	else if (this->parent()) return this->parent();
	else                     return 0 /*NULL*/;
	}
	//======================================================================

	//Element locating======================================================
	location_count linked_section::self_location() const
	//Location of this element
	{
	if (this->previous())    return this->previous()->next_location();
	else if (this->parent()) return this->parent()->child_location();
	else                     return 0 /*NULL*/;
	}

	location_count linked_section::storage_size() const
	//Size of storage
	{ return this->self_location() - this->next_location(); }
	//======================================================================

	//Scope locating========================================================
	scope_locator *linked_section::locate_scope(const scope_identifier &sScope)
	//Locate a scope within this scope
	{
	if (!this->child()) return 0 /*NULL*/;

	storage_section *Current = this->child();
	scope_locator *Result = 0 /*NULL*/;

	while (Current && !Result)
	//Check all children to see if they match
	 {
	Result = Current->locate_scope(sScope);
	Current = Current->next();
	 }

	return Result;
	}

	bool linked_section::current_scope(scope_identifier &iIdent,
	const scope_locator *sScope) const
	//Identify this scope
	{
	//Stop here if this is the upper limit
	if (sScope == this) return true;

	else if (!this->parent())
	//Stop here if there isn't anything above here
	 {
	if (!sScope) return true;
	else         return false;
	 }

	//Pass on to parent
	else return this->parent()->current_scope(iIdent, sScope);
	}

	bool linked_section::base_current_scope(const scope_locator *sScope) const
	//Identify this scope
	{ return this->parent()->base_current_scope(sScope); }
	//======================================================================

	//Connection control====================================================
	bool linked_section::allow_next(const storage_section *nNext) const
	{ return this->parent()? this->parent()->allow_child(nNext) : true; }
	//Check allowance of element as next

	bool linked_section::allow_here(const storage_section *hHere) const
	//Check allowance of element as next
	{
	if (this->parent()   && !this->parent()->allow_child(hHere))  return false;
	if (this->previous() && !this->previous()->allow_next(hHere)) return false;
	return this->owner();
	}
	//======================================================================

	//Create a copy of this element, nexts, children========================
	section_releaser linked_section::copy_all() const
	//Copy this element plus things connected downward
	{
	section_releaser Created( this->copy() );

	if (Created && this->next())
	Created->add_next( parent_storage::copy_all(this->next()) );

	return Created;
	}
	//======================================================================

	//Resource management===================================================
	input_resource *linked_section::get_input_resource()
	//Obtain an input resource
	{
	return this->parent()?
	  input_resource_owner::get_input_resource( this->parent() ) : 0 /*NULL*/;
	}

	output_resource *linked_section::get_output_resource()
	//Obtain an output resource
	{
	return this->parent()?
	  output_resource_owner::get_output_resource( this->parent() ) : 0 /*NULL*/;
	}
	//======================================================================

	//tree_number control===================================================
	verified_element *linked_section::tree_base()
	//Determine the base of the tree
	{ return this->hierarchy_base(); }

	void linked_section::change_tree(tree_number *tTree)
	//Recursively change trees
	{
	if (this->get_tree_number() == tTree) return;
	this->switch_trees(tTree);
	verified_element::change_tree(this->next(), tTree);
	verified_element::change_tree(this->child(), tTree);
	}

	void linked_section::set_tree_number(tree_number *nNumber)
	//Set the tree number of this element
	{ owning_tree = nNumber; }

	tree_number *linked_section::get_tree_number() const
	//Get the tree number of this element
	{ return owning_tree; }
	//======================================================================

	linked_section::~linked_section()
	{
	//The destructor first detaches the branch if it has an owner.  This
	//prevents 'Next' from being deleted.  If the element is the base of the
	//hierarchy, 'Next' is deleted.  To ensure that all nodes following
	//nodes deleted by this destructor (i.e. 'Next' and 'Child'), those
	//elements are spliced off so that they have no owner.  This forces them
	//to delete their own 'Next', etc.

	//(Rather than have a dedicated destruction function, this allows the
	//user to have their own infrastructure delete nodes as they see fit.)

	//This modifies all 'section_releaser' so that they don't try to check or
	//delete this element later.
	this->clear_counters();

	//This prevents unnecessary tree switching
	//(This needs to be before 'remove_self' so that the owned elements
	//aren't given a new tree, then given the old tree back.)
	this->switch_trees(0 /*NULL*/);

	//This detaches the element from the tree if it's attached
	if (this->owner())
	 {
	section_releaser Self( this->linked_section::remove_self() );
	parent_storage::cancel_section(Self);
	 }

	this->set_child( section_releaser(0 /*NULL*/) );

	//If this is the base of a tree, the below is meaningful.  If this is a
	//branch within another tree, the below will be meaningless since the
	//branch was removed.
	this->set_next( section_releaser(0 /*NULL*/) );
	}

	//Reference counter control---------------------------------------------
	bool linked_section::add_reference_counter(section_releaser &cCounter)
	//Start tracking a 'section_releaser'
	{
	std::list <section_releaser*> ::const_iterator
	  begin = reference_counters.begin(),
	  end   = reference_counters.end();

	while (begin != end) if (*begin++ == &cCounter) return false;

	reference_counters.push_back(&cCounter);

	return true;
	}

	void linked_section::remove_reference_counter(section_releaser &cCounter)
	//Stop tracking a 'section_releaser'
	{
	std::list <section_releaser*> ::iterator
	  begin = reference_counters.begin(),
	  end   = reference_counters.end();

	while (begin != end)
	if (*begin != &cCounter) ++begin;
	else
	 {
	reference_counters.erase(begin);
	//The iterators are invalidated at this point;
	begin = reference_counters.begin();
	end   = reference_counters.end();
	 }
	}

	void linked_section::clear_counters()
	//Clear references to this element
	{
	std::list <section_releaser*> ::const_iterator
	  begin = reference_counters.begin(),
	  end   = reference_counters.end();

	while (begin != end)
	 {
	if (*begin) parent_storage::cancel_final(**begin);
	++begin;
	 }
	}
	//----------------------------------------------------------------------

	storage_section *linked_section::set_free(storage_section *eElement)
	//Remove ownership from an element
	{
	storage_section::set_previous(eElement, 0 /*NULL*/);
	parent_storage::set_parent(eElement, 0 /*NULL*/);
	return eElement;
	}

	bool linked_section::lineage_check(const storage_section *cCheck) const
	//Check the lineage of an element to be added

	{ return !this->same_tree(cCheck); }
//==============================================================================

#endif
