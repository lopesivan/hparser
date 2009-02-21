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

#ifndef PARENT_STORAGE_CPP
#define PARENT_STORAGE_CPP

#include "parent-storage.hpp"
#include "storage-section.hpp"

//section_releaser function bodies==============================================
	section_releaser::section_releaser(storage_section *sSection, bool rResult) :
	section_pointer(sSection), function_result(rResult),
	counter(new short(1))
	{ if (section_pointer) section_pointer->add_reference_counter(*this); }

	section_releaser::section_releaser(const section_releaser &eEqual) :
	section_pointer(eEqual.section_pointer), function_result(eEqual.function_result),
	counter(eEqual.counter)
	{
	if (section_pointer) section_pointer->add_reference_counter(*this);
	if (counter) (*counter)++;
	}

	section_releaser &section_releaser::operator = (const section_releaser &eEqual)
	{
	if (&eEqual == this) return *this;

	this->clear_pointer();

	section_pointer = eEqual.section_pointer;
	if (section_pointer) section_pointer->add_reference_counter(*this);

	function_result = eEqual.function_result;
	counter        = eEqual.counter;

	if (counter) (*counter)++;

	return *this;
	}

	section_releaser::~section_releaser()
	{ this->clear_pointer(); }

	bool section_releaser::result() const
	{ return function_result; }

	section_releaser &section_releaser::set_result(bool rResult)
	{
	function_result = rResult;
	return *this;
	}

	const storage_section &section_releaser::operator * () const
	{ return *section_pointer; }

	storage_section *section_releaser::operator -> ()
	{ return section_pointer; }

	const storage_section *section_releaser::operator -> () const
	{ return section_pointer; }

	bool section_releaser::operator ! () const
	{ return !section_pointer; }

	section_releaser::operator bool() const
	{ return section_pointer; }

	section_releaser::operator const storage_section*() const
	{ return section_pointer; }

	storage_section *section_releaser::borrow_section() const
	{ return section_pointer; }

	void section_releaser::cancel_section()
	{
	if (section_pointer) section_pointer->remove_reference_counter(*this);
	this->cancel_final();
	}

	void section_releaser::cancel_final()
	{
	section_pointer = 0 /*NULL*/;

	short *Holding = counter;
	counter = 0 /*NULL*/;

	if (Holding && --(*Holding) <= 0) delete Holding;
	}

	void section_releaser::clear_pointer()
	{
	if (section_pointer) section_pointer->remove_reference_counter(*this);

	storage_section *Holding1 = section_pointer;
	section_pointer = 0 /*NULL*/;

	short *Holding2 = counter;
	counter = 0 /*NULL*/;

	if (Holding2 && --(*Holding2) <= 0)
	 {
	if (Holding1 && !Holding1->owner()) delete Holding1;
	delete Holding2;
	 }
	}
//==============================================================================

//parent_storage function bodies================================================
	//Parent element in hierarchy===========================================
	parent_storage *parent_storage::set_parent(storage_section *eElement,
	parent_storage *pParent)
	{ return eElement? eElement->set_parent(pParent) : 0 /*NULL*/; }

	parent_storage *parent_storage::hierarchy_base() const
	//Find the base of the hierarchy
	{ return const_cast <parent_storage*> (this); }

	parent_storage *parent_storage::branch_base() const
	//Find the base of the branch
	{ return const_cast <parent_storage*> (this); }
	//======================================================================

	//Parent element in hierarchy===========================================
	parent_storage *parent_storage::parent() const
	//Obtain the parent element
	{ return 0 /*NULL*/; }
	//======================================================================

	//Counting elements=====================================================
	element_count parent_storage::count_depth() const
	//Count depth of object
	{ return 0; }
	//======================================================================

	//Element locating======================================================
	location_count parent_storage::next_location() const
	//Location of next element
	{ return 0; }

	location_count parent_storage::child_location() const
	//Location of first child element
	{ return 0; }

	location_count parent_storage::storage_size() const
	//Size of storage
	{ return 0; }
	//======================================================================

	//Scope locating========================================================
	scope_locator *parent_storage::locate_scope(const scope_identifier&)
	//Locate a scope within this scope
	{ return this; }

	bool parent_storage::current_scope(scope_identifier&, const scope_locator *sScope) const
	//Identify this scope
	{ return sScope == this || !sScope; }

	bool parent_storage::base_current_scope(const scope_locator*) const
	//Identify this scope
	{ return false; }
	//======================================================================

	//Connection control====================================================
	bool parent_storage::connect()
	{ return true; }
	//Connect this element

	bool parent_storage::disconnect()
	{ return true; }
	//Disconnect this element

	bool parent_storage::allow_next(const storage_section*) const
	{ return false; }
	//Check allowance of element as next

	bool parent_storage::allow_child(const storage_section*) const
	{ return true; }
	//Check allowance of element as child

	bool parent_storage::allow_here(const storage_section*) const
	{ return false; }
	//Check allowance of element here
	//======================================================================

	//Create a copy of this element, nexts, children========================
	section_releaser parent_storage::copy_all(const storage_section *eElement)
	{ return eElement? eElement->copy_all() : section_releaser(0 /*NULL*/); }
	//======================================================================

	//section_releaser access===============================================
	storage_section *parent_storage::borrow_section(const section_releaser &bBorrow)
	{ return bBorrow.borrow_section(); }
	//Borrow a pointer from 'section_releaser'

	void parent_storage::cancel_section(section_releaser &rRelease)
	{ rRelease.cancel_section(); }
	//Cancel deletion of a pointer by 'section_releaser'

	void parent_storage::cancel_final(section_releaser &rRelease)
	{ rRelease.cancel_final(); }
	//Cancel deletion of a pointer by 'section_releaser'
	//======================================================================

	parent_storage::~parent_storage() {}
//==============================================================================

#endif
