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

#ifndef PARENT_STORAGE_HPP
#define PARENT_STORAGE_HPP

#include "data-input.hpp"
#include "data-output.hpp"
#include "comm-line.hpp"
#include "triggered-update.hpp"
#include "input-resource.hpp"
#include "output-resource.hpp"
#include "scope-locator.hpp"
#include "connection-control.hpp"
#include "interface-user.hpp"
#include "verified-element.hpp"

/*! \defgroup memory_group Memory Management
*/

//Typedef element_count---------------------------------------------------------
//Quantity of elements
typedef unsigned int element_count; //END---------------------------------------

//Typedef location_count--------------------------------------------------------
//Location of elements
typedef long long location_count; //END-----------------------------------------

//Class section_releaser--------------------------------------------------------
//Automatic storage_section-releasing object

	/*! \class section_releaser
	    \brief Consumable memory management wrapper.
	    \ingroup memory_group
	    \ingroup storage_group

	    This class is a wrapper for dynamic pointer returns from
	    storage_section functions.  This is the primary memory management
	    class for elements not currently owned by another element.

	    \attention This is a reference-counting object.  It will delete the
	    stored pointer upon its own destruction if it's the last
	    section_releaser holding a pointer and that pointer isn't owned by
	    something else ("owned" means part of a hierarchy but not the base.)
	    For this reason, you should always immediately pass new elements to
	    a section_releaser to avoid multiple groups storing pointers to the
	    same element.
	 */

class section_releaser
{
public:
	/** Constructor takes an optional argument to denote a result value. */
	section_releaser(storage_section*, bool = true);

	section_releaser(const section_releaser&);
	section_releaser &operator = (const section_releaser&);

	~section_releaser();

	/** Returns a result value to denote success or failure of a returning
	    function. */
	bool result() const;

	/** Set the value returned by Result. */
	section_releaser &set_result(bool);

    /** @name Pointer Functions
     *
     */
    //@{
	const storage_section &operator * () const;
	storage_section *operator -> ();
	const storage_section *operator -> () const;
	bool operator ! () const;
	operator bool() const;
	operator const storage_section*() const;
    //@}

protected:
	storage_section *borrow_section() const;
	void cancel_section();
	void cancel_final();

private:
	void clear_pointer();

	storage_section *section_pointer;
	unsigned char   function_result;
	short          *counter;

	friend class parent_storage;
}; //END------------------------------------------------------------------------

//Struct parent_storage---------------------------------------------------------
//Abstract data storage class which is intended to contain others
struct storage_section;
struct section_releaser;

	/*! \class parent_storage
	    \brief Container class for hierarchy elements.
	    \ingroup element_group
	    \ingroup storage_group

	    This class is the basic container class for the hierarchy.  It's
	    the base class for all hierarchy elements and hierarchy bases.  It
	    provides the necessary interfaces for the hierarchy to function.
	 */

struct parent_storage :
	virtual public input_receiver,
	virtual public output_sender,
	virtual public comm_line,
	virtual public triggered_update,
	virtual public input_resource_owner,
	virtual public output_resource_owner,
	virtual public scope_locator,
	virtual public connection_control,
	virtual public interface_user,
	virtual public verified_element
{
	//Sub-element in hierarchy==============================================
	/** Remove all sub-elements and replace them with the argument
	    provided. */
	virtual
		section_releaser
	set_child(section_releaser) = 0;
	//Sets the first child element
	//======================================================================

	//Parent element in hierarchy===========================================
	/** Return the parent object in the hierarchy.  Returns NULL by
	    default. */
	virtual
		parent_storage
	*parent() const;
	//Obtain the parent element
	//======================================================================

	//Counting elements=====================================================
	/** Count the number of objects directly superior to this object. */
	virtual
		element_count
	count_depth() const;
	//Count depth of object
	//======================================================================

	//Element locating======================================================
	/** Determine the storage location of the next element.  This is used
	    when exporting to a centralized data location where each part of
	    the hierarchy must know where to place its data.  If necessary,
	    override this function to denote the position following the last
	    unit of data from this object and it's sub-objects.  This should
	    take into account the size of the data from this object plus the
	    size of all child elements.  Recommended return is the return of
	    the next_location function called on the last sub-object. */
	virtual
		location_count
	next_location() const;
	//Location of next element

	/** Determine the storage location of the first sub-object.
	    Recommended return value is the location of this object's data +
	    the size of this object's data.

	    @see next_location provides further guidance. */
	virtual
		location_count
	child_location() const;
	//Location of first child element

	/** Determine the storage size of this object's data.

	    @see next_location provides further guidance. */
	virtual
		location_count
	storage_size() const;
	//Size of storage
	//======================================================================

	//Scope locating========================================================
	virtual
		scope_locator
	*locate_scope(const scope_identifier&);
	//Locate a scope within this scope

	virtual
		bool
	current_scope(scope_identifier&, const scope_locator*) const;
	//Identify this scope

	virtual
		bool
	base_current_scope(const scope_locator*) const;
	//Identify this scope
	//======================================================================

	//Connection control====================================================
	virtual
		bool
	connect();
	//Connect this element

	virtual
		bool
	disconnect();
	//Disconnect this element

	virtual
		bool
	allow_next(const storage_section*) const;
	//Check allowance of element as next

	virtual
		bool
	allow_child(const storage_section*) const;
	//Check allowance of element as child

	virtual
		bool
	allow_here(const storage_section*) const;
	//Check allowance of element here
	//======================================================================

	//Parent element in hierarchy===========================================
    protected:
	/** Sets this element's reference to the element above it in the
	    hierarchy.  This is protected since it effects memory management.
	    Do not use this function unless you are deriving a new element
	    class which will provide memory management! */
	static
		parent_storage
	*set_parent(storage_section*, parent_storage*);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  This allows derived classes to call the 'SetParent'
	  function on 'storage_section' it contains (should be called
	  twice from 'SetChild'; once to release the old child by
	  making its parent NULL, and again to make the new child's
	  parent 'this'.)
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    public:
	virtual
		parent_storage
	*hierarchy_base() const;
	//Find the base of the hierarchy

	virtual
		parent_storage
	*branch_base() const;
	//Find the base of the branch
	//======================================================================

	//Create a copy of this element, nexts, children========================
    protected:
	static
		section_releaser
	copy_all(const storage_section*);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  This allows derived classes to call the member function on
	  their children.
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//======================================================================

protected:
	//section_releaser access===============================================
	static
		storage_section
	*borrow_section(const section_releaser&);
	//Borrow a pointer from 'section_releaser'

	static
		void
	cancel_section(section_releaser&);
	//Cancel deletion of a pointer by 'section_releaser'

	static
		void
	cancel_final(section_releaser&);
	//Cancel deletion of a pointer by 'section_releaser'
	//======================================================================

	virtual
	~parent_storage();
}; //END------------------------------------------------------------------------

#endif
