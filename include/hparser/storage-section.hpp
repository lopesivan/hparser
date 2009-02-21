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

#ifndef STORAGE_SECTION_HPP
#define STORAGE_SECTION_HPP

#include "parent-storage.hpp"

/*! \defgroup element_group Structural Elements
*/

/*! \defgroup storage_group Storage Components
*/

//Struct storage_section--------------------------------------------------------
//Abstract data section for hierarchical assembly

	/*! \class storage_section
	    \brief Abstract tree element class.
	    \ingroup interfaces_group
	    \ingroup element_group
	    \ingroup storage_group

	    This is the basic structural element of the tree.  It connects to
	    sub-elements and elements following it.  This class provides the
	    complete interface required for all operations on the tree elements.
	    This class relies on several implementation-defined classes to
	    extend the tree's interface to interfaces external-to and unknown-to
	    this library.

	    \attention The function notes here define assumed behavior of
	    further-derived classes.  Do not override these functions in ways
	    contrary to these notes!

	    \attention Never create objects derived from this class using other
	    than singular 'new'.  This library expects to be able to delete any
	    pointer to an object of this type.
	 */

struct storage_section :
	virtual public parent_storage
{
	//Element updating======================================================
    /** @name Update Functions
     *
     */
    //@{
	/** Update this element and all sub-elements. */
	virtual
		bool
	branch_update() = 0;
	//Update object data in branch only

	/** Start at the base of the tree and update the entire tree. */
	virtual
		bool
	hierarchy_update() = 0;
	//Update object data in entire hierarchy
    //@}
	//======================================================================

    /** @name Next Element Functions
     *
     */
    //@{
	//Last element in hierarchy=============================================
	/** Obtain the last peer element. */
	virtual
		storage_section
	*last() const = 0;
	//Obtain the last data element
	//======================================================================

	//Next element in hierarchy=============================================
	/** Obtain the next peer element. */
	virtual
		storage_section
	*next() const = 0;
	//Obtain the next data element

	/** Add a peer element at the end.  The added element is returned. */
	virtual
		section_releaser
	add_next(section_releaser) = 0;
	//Add a data element to the chain

	/** Add a peer element directly after this element.  The added element
	    is returned. */
	virtual
		section_releaser
	insert_next(section_releaser) = 0;
	//Insert a data element to the chain

	/** Replace the next element with that provided.  The next element stays
	    connected to all elements past it, breaking the row of peer
	    elements in two, replacing the second part with a new part.  If
	    successful the part which was broken off is returned.  If
	    unsuccessful the argument is returned. \attention The broken-off
	    return will have no owner if the operation is successful. */
	virtual
		section_releaser
	set_next(section_releaser) = 0;
	//Sets the next data element
	//======================================================================
    //@}

    /** @name In-place Functions
     *
     */
    //@{
	//Cut hierarchy here and replace========================================
	/** Replace this element with that provided.  This element stays
	    connected to all elements past it, breaking the row of peer
	    elements in two, replacing the second part with a new part.  If
	    successful the part which was broken off is returned.  If
	    unsuccessful the argument is returned. \attention The broken-off
	    return will have no owner if the operation is successful. */
	virtual
		section_releaser
	splice_here(section_releaser) = 0;
	//Removes this and all following elements and replaces
	//======================================================================

	//Remove from hierarchy=================================================
	/** Remove this element.  If successful the gap is closed between peer
	    elements and this element is returned.  If unsuccessful NULL is
	    returned. \attention The broken-off return will have no owner if the
	    operation is successful. */
	virtual
		section_releaser
	remove_self() = 0;
	//Remove self from the tree
	//======================================================================

	//Replace this element==================================================
	/** Replace this element with that provided.  This element does not stay
	    connected to the elements past it.  If successful this element is
	    returned with no peers.  If unsuccessful the argument is returned.
	    \attention The broken-off return will have no owner if the operation
	    is successful. */
	virtual
		section_releaser
	replace_self(section_releaser) = 0;
	//Replaces this element with another
	//======================================================================

	//Insert element========================================================
	/** Add a peer element directly before this element.  The added element
	    is returned. */
	virtual
		section_releaser
	insert_here(section_releaser) = 0;
	//Insert element in this current position
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  ``ELEMENT ADDING FUNCTION``
	  This moves 'this' forward to insert the new element.
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//======================================================================

	//Remove element and promote children===================================
	/** Remove this element.  If successful the sub-elements are promoted
	    to fill the gap where this element used to be and this element is
	    returned with no peers or sub-elements.  If unsuccessful NULL is
	    returned. \attention The broken-off return will have no owner if the
	    operation is successful. */
	virtual
		section_releaser
	promote_children() = 0;
	//Removes 'this' and promotes children
	//======================================================================

	//Demote element and insert=============================================
	/** Add a peer element where this element is and demote this element as
	    the last sub-element to that which is inserted.  The added element
	    is returned. */
	virtual
		section_releaser
	demote_self(section_releaser) = 0;
	//Insert new element by moving 'this' down
	//======================================================================
    //@}

    /** @name Previous Element Functions
     *
     */
    //@{
	//Previous element in hierarchy=========================================
	/** Obtain the previous peer element. */
	virtual
		storage_section
	*previous() const = 0;
	//Obtain the previous data element

    protected:
	/** Set the previous element.  This should always return this
	    element. */
	virtual
		storage_section
	*set_previous(storage_section*) = 0;
	//Set the previous data element

	static
		storage_section
	*set_previous(storage_section*, storage_section*);
	//======================================================================

    public:
	//First element in hierarchy============================================
	/** Obtain the first peer element. */
	virtual
		storage_section
	*first() const = 0;
	//Obtain the first data element
	//======================================================================
    //@}

    /** @name Sub-element Functions
     *
     */
    //@{
	//Sub-element in hierarchy==============================================
	/** Obtain the first sub-element. */
	virtual
		storage_section
	*child() const = 0;
	//Obtain the first child element

	/** Add a sub-element to the end.  The added element is returned. */
	virtual
		section_releaser
	add_child(section_releaser) = 0;
	//Add a child element

	/** Add a sub-element at the beginning.  The added element is
	    returned. */
	virtual
		section_releaser
	insert_child(section_releaser) = 0;
	//Insert a child element

	//	virtual
	//		section_releaser
	//	set_child(section_releaser) = 0;
	//Sets the first child element
	//======================================================================
    //@}

	//Parent element in hierarchy===========================================
	//	virtual
	//		parent_storage
	//	*parent() const;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  (Inherited from 'parent_storage'.)
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    protected:
	/** Set the parent element.  This should always return this element. */
	virtual
		parent_storage
	*set_parent(parent_storage*) = 0;
	//Set the parent element

	//	static
	//		parent_storage
	//	*set_parent(storage_section*, parent_storage*);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  (Inherited from 'parent_storage'.)
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//======================================================================

    public:
	//Determine ownership of element========================================
	/** Obtain the object responsible for deleting this element. */
	virtual
		parent_storage
	*owner() const = 0;
	//Determine who will delete this element
	//======================================================================

	//Element locating======================================================
	/** Obtain the location of this element relative to the start of the
	    first peer. */
	virtual
		location_count
	self_location() const = 0;
	//Location of this element
	//======================================================================

    /** @name Duplication Functions
     *
     */
    //@{
	//Create a copy of this element=========================================
	/** Create a copy of this element.  This should be implemented in the
	    most-derived class, and should return a section_releaser
	    constructed with a dynamically-allocated copy of that object.
	    \attention The return will have no owner if the operation is
	    successful.*/
	virtual
		section_releaser
	copy() const = 0;
	//Copy this element
	//======================================================================

	//Create a copy of this element, nexts, children========================
    protected:
	/** Create a copy of this element and every element following it.  This
	    is used internally to copy all sub-elements of an element.
	    \attention The return will have no owner if the operation is
	    successful.*/
	virtual
		section_releaser
	copy_all() const = 0;
	//Copy this element plus things connected downward

	//	static
	//		storage_section
	//	*copy_all(const storage_section*);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  (Inherited from 'parent_storage'.)
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//======================================================================
    //@}

    /** @name Counting Functions
     *
     */
    //@{
    public:
	//Counting elements=====================================================
	/** Count the number of peers previous to this element. */
	virtual
		element_count
	count_previous() const;
	//Count number of elements before this one

	/** Count the number of peers after to this element. */
	virtual
		element_count
	count_next() const;
	//Count number of elements after this one

	/** Count the sub-elements. */
	virtual
		element_count
	count_children() const;
	//Count number of children

	/** Count the number of containing objects. */
	virtual
		element_count
	count_depth() const;
	//Count depth of object
	//Override from 'parent_storage'
	//======================================================================
    //@}

    public:

	/*! \brief Destructor.

	    The derived destructor should trigger all sub-elements' deletion
	    under all circumstances.  If this element has no owner it should
	    also trigger the deletion of the following element.  This
	    functionality should be implemented in the next-derived class, so if
	    you don't derive directly from this class you don't need to worry
	    about this.
	 */

	virtual inline
	~storage_section() {};

	friend class parent_storage;
	//For 'SetParent' and 'copy_all' static functions

private:
	//Reference counter control---------------------------------------------
	virtual
		bool
	add_reference_counter(section_releaser&) = 0;
	//Start tracking a 'section_releaser'

	virtual
		void
	remove_reference_counter(section_releaser&) = 0;
	//Stop tracking a 'section_releaser'

	friend class section_releaser;
	//For 'add_reference_counter' and 'remove_reference_counter'
	//----------------------------------------------------------------------
}; //END------------------------------------------------------------------------

#endif
