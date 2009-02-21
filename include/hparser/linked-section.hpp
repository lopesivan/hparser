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

#ifndef LINKED_SECTION_HPP
#define LINKED_SECTION_HPP

#include "storage-section.hpp"

#include <list>

/*! \defgroup user_group User-intended Classes
*/

//Struct linked_section---------------------------------------------------------
//Memory-managed hierarchically-assembled data section element

	/*! \class linked_section
	    \brief Partially-abstract tree element class.
	    \ingroup element_group
	    \ingroup storage_group
	    \ingroup user_group

	    This class provides linking functionality for storage_section.  This
	    class owns the element following it and its first child element.
	    This means that upon its own deletion it deletes its child elements
	    and the following element if this element has no owner itself.  Some
	    functions are overridden or implemented with specific functionality
	    unique to a linked element.

	    \attention Never create objects derived from this class using other
	    than singular 'new'.  This library expects to be able to delete any
	    pointer to an object of this type.
	 */

struct linked_section :
	virtual public storage_section
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  See 'storage_section' for function notes.
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//Message sending interface=============================================
    /** @name Implemented from CommLine
     *
     */
    //@{
	/*! \brief Message conduit function.

	    This function is implemented to apply the message locally with the
	    CommLine function local_message, to pass the message on to its
	    sub-elements, and then to the element following it.  To reimplement
	    this function you should check the message to determine the type of
	    path it should take.  If you need the default functionality in
	    certain cases call 'this->linked_section::send_message'.  To apply the
	    message to this element only reimplement the local_message function.
	 */
	virtual
		bool
	send_message(comm_message&);
	//Send a message
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  This function doesn't accept the message, however passes
	  it on to 'Child' then to 'Next'.  To reimplement this
	  function, override and perform the desired action with the
	  message, then call 'this->linked_section::send_message' to
	  pass the message on to everyone else.
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    //@}
	//======================================================================

	//Data filters==========================================================
    /** @name Data Filtering
     *
     */
    //@{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  These functions don't perform any actions on the data
	  other than passing them to 'Parent'.
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/** Filter input through all parent objects from bottom to top. */
	virtual
		bool
	input_filter(input_section&);
	//Filter input data

	/** Filter output through all parent objects from bottom to top. */
	virtual
		bool
	output_filter(output_section&) const;
	//Filter output data
    //@}
	//======================================================================

	//Element updating======================================================
    /** @name Element Updating Functions
     *
     */
    //@{
	/** Update this element, sub-elements, and the following element. */
	virtual
		bool
	global_update();
	//Update object data globally

	//	virtual
	//		bool
	//	local_update();
	//Update object data locally
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  (Inherited from 'triggered_update'.)
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/** Update this element, and sub-elements. */
	virtual
		bool
	branch_update();
	//Update object data in branch only

	/** Update all objects starting with the top-most object. */
	virtual
		bool
	hierarchy_update();
	//Update object data in entire hierarchy
    //@}
	//======================================================================

protected:
	linked_section();
	//Constructor
	//Created ownerless

	/** Copies all children in addition to this element. */
	linked_section(const linked_section&);
	//Copy constructor
	//Created ownerless, only copies children

	/** Copies all children in addition to this element and deletes all
	    previous children. */
		linked_section
	&operator = (const linked_section&);
	//Assignment operator
	//Deletes old children and copies new children

public:
    /** @name Implemented from storage_section
     *
     */
    //@{
	//Last element in hierarchy=============================================
	virtual
		storage_section
	*last() const;
	//Obtain the last data element
	//======================================================================

	//Next element in hierarchy=============================================
	/** Returns the next peer element in the hierarchichy. */
	virtual
		storage_section
	*next() const;
	//Obtain the next data element

	/** Adds a peer element to the end of this chain of elements. */
	virtual
		section_releaser
	add_next(section_releaser);
	//Add a data element to the chain

	/** Inserts a peer element immediately ahead of this element. */
	virtual
		section_releaser
	insert_next(section_releaser);
	//Insert a data element to the chain

	/** Breaks off the next element, leaving everything following it and
	    below those elements attached to the detached element and returns
	    it.  It's then replaced by the argument given. */
	virtual
		section_releaser
	set_next(section_releaser);
	//Sets the next data element
	//======================================================================

	//Cut hierarchy here and replace========================================

	/** Breaks off this element, leaving everything following it and
	    below this and all following elements attached and returns it.
	    It's then replaced by the argument given. */
	virtual
		section_releaser
	splice_here(section_releaser);
	//Removes this and all following elements and replaces
	//======================================================================

	//Remove from hierarchy=================================================
	/** Removes this element and moves the next element up into its place.
	    Will not work if this element has no owner. */
	virtual
		section_releaser
	remove_self();
	//Remove self from the tree
	//======================================================================

	//Replace this element==================================================
	/** Removes this element and replaces it with the provided argument.
	    Will not work if this element has no owner. */
	virtual
		section_releaser
	replace_self(section_releaser);
	//Replaces this element with another
	//======================================================================

	//Insert element========================================================
	/** Inserts a new element in this element's place, moving it forward.
	    This element becomes the next element of that inserted. */
	virtual
		section_releaser
	insert_here(section_releaser);
	//Insert element in this current position
	//======================================================================

	//Remove element and promote children===================================
	/** Removes this element and moves all elements below up to its level.
	    The promoted elements fill in the space where this element was,
	    becoming peers of this element's. */
	virtual
		section_releaser
	promote_children();
	//Removes 'this' and promotes children
	//======================================================================

	//Demote element and insert=============================================
	/** Inserts an element in this element place and makes this element the
	    last child element of that inserted. */
	virtual
		section_releaser
	demote_self(section_releaser);
	//Insert new element by moving 'this' down
	//======================================================================

	//Previous element in hierarchy=========================================
	/** Returns the previous element in the hierarchy. */
	virtual
		storage_section
	*previous() const;
	//Obtain the previous data element

    protected:
	/** Sets this element's reference to the element preceding it in the
	    hierarchy.  This is protected since it effects memory management.
	    Do not use this function unless you are deriving a new element
	    class which will provide memory management! */
	virtual
		storage_section
	*set_previous(storage_section*);
	//Set the previous data element
	//======================================================================

    public:
	//First element in hierarchy============================================
	/** Returns the first peer element in the hierarchy. */
	virtual
		storage_section
	*first() const;
	//Obtain the first data element
	//======================================================================

	//Sub-element in hierarchy==============================================
	/** Returns the child element in the hierarchy. */
	virtual
		storage_section
	*child() const;
	//Obtain the first child element

	/** Adds a child element to the end of the chain of sub-elements. */
	virtual
		section_releaser
	add_child(section_releaser);
	//Add a child element

	/** Inserts a child element at the beginning of the chain of
	    sub-elements. */
	virtual
		section_releaser
	insert_child(section_releaser);
	//Insert a child element


	/** Breaks off the first sub-element, leaving everything following it
	    and below those elements attached to the detached element and
	    returns it.  It's then replaced by the argument given. */
	virtual
		section_releaser
	set_child(section_releaser);
	//Sets the first child element
	//======================================================================
    //@}

    /** @name Implemented from parent_storage
     *
     */
    //@{
    public:
	//Parent element in hierarchy===========================================
	/** Returns the parent element in the hierarchy.   Not necessarily an
	    element itself. */
	virtual
		parent_storage
	*parent() const;
	//Obtain the parent element

	/** Returns the base element in the hierarchy.  This is the first
	    peer of the top-most parent of the current element. */
	virtual
		parent_storage
	*hierarchy_base() const;
	//Find the top of the hierarchy

	/** Returns the base element in the current branch.  This is the first
	    top-most parent of the current element. */
	virtual
		parent_storage
	*branch_base() const;
	//Find the base of the branch
    //@}

    /** @name Implemented from storage_section
     *
     */
    //@{
    protected:
	/** Sets this element's reference to the element above it in the
	    hierarchy.  This is protected since it effects memory management.
	    Do not use this function unless you are deriving a new element
	    class which will provide memory management! */
	virtual
		parent_storage
	*set_parent(parent_storage*);
	//Set the parent element
	//======================================================================

    public:
	//Determine ownership of element========================================
	/** Returns the owning object.  This is not necessarily another
	    element and not necessarily the element's parent.  It is the
	    object responsible for deleting this element; therefore, if the
	    object returned by this function destructs, so does this object. */
	virtual
		parent_storage
	*owner() const;
	//Determine who will delete this element
	//======================================================================

	//Create a copy of this element=========================================
	/** Reiterated from storage_section.  This function *must* be
	    implemented in the most-derived class and should return a new copy
	    of this element. */
	virtual
		section_releaser
	copy() const = 0;
	//Copy this element
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  (Inherited from 'storage_section'.)
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//======================================================================
    //@}

	//Element locating======================================================
	/** Returns the location counter for this element in the structure as
	    a whole.  This is necessary for writing to a file or global data
	    structure in order to place this element's data in the correct
	    location.  Implement the next_location and child_location functions
	    in all elements to indicate where each element's data ends in
	    relation to the return of self_location. */
	virtual
		location_count
	self_location() const;
	//Location of this element
	//Override from 'parent_storage'

    /** @name Implemented from parent_storage
     *
     */
    //@{
	/** Returns the inferred size of this element's data.  This does not
	    need to be overridden; override the next_location and
	    child_location functions. */
	virtual
		location_count
	storage_size() const;
	//Size of storage
	//Override from 'parent_storage'
    //@}
	//======================================================================

    /** @name Implemented from scope_locator
     *
     */
    //@{
	//Scope locating========================================================
	virtual
		scope_locator
	*locate_scope(const scope_identifier&);
	//Locate a scope within this scope
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  This checks all children against the 'scope_identifier' and
	  returns the first one that matches.  If none match, NULL
	  is returned.  To reimplement this function, check this
	  element against the identifier.  If it matches the bottom
	  of the identifier, remove that portion of the identifier
	  and call 'this->linked_section::locate_scope' with the
	  remaining scope.  Return NULL if it doesn't match.
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	virtual
		bool
	current_scope(scope_identifier&, const scope_locator*) const;
	//Identify this scope
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  This passes the call upward until either a match for the
	  'scope_locator' is found or until the top of the tree is
	  reached.  If the top is reached and the locator is NULL
	  or a match is found, 'true' is returned, otherwise 'false'
	  is returned.  To reimplement this function, add the
	  current scope to the top of the 'scope_identifier' and
	  return the value of 'this->linked_section::current_scope'.
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	virtual
		bool
	base_current_scope(const scope_locator*) const;
	//Identify this scope
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  This passes the call upward until something else stops the
          chain of calls.  The base should contain a 'scope_locator'
          and should call 'current_scope' on the argument given.
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//======================================================================
    //@}

    /** @name Implemented from ConnectionControl
     *
     */
    //@{
	//Connection control====================================================
	/** Returns true if this element may have elements connected in front
	    of it.  Override this to gain control over which elements may be
	    connected after this element, or to exclude elements in front of
	    this element altogether. */
	virtual
		bool
	allow_next(const storage_section*) const;
	//Check allowance of element as next
	//Override from 'parent_storage'

	/** Returns true if this element may be replaced by another element.
	    This should not be overridden.  It checks AllowNext and AllowChild
	    for the owning object as applicable. */
	virtual
		bool
	allow_here(const storage_section*) const;
	//Check allowance of element here
	//Override from 'parent_storage'
	//======================================================================
    //@}

    /** @name Implemented from storage_section
     *
     */
    //@{
	//Create a copy of this element, nexts, children========================
    protected:
	/** Copies this element, all peer elements following it, and all
	    elements below each.  This is protected because it isn't intended
	    for normal use.  It's used by the copy constructor. */
	virtual
		section_releaser
	copy_all() const;
	//Copy this element plus things connected downward
	//======================================================================
    //@}

	//Resource management===================================================
    /** @name Implemented from input_resource_owner
     *
     */
    //@{
	/** Returns the input resource for this element.  This is generally a
	    data buffer or a wrapper for file input. */
	virtual
		input_resource
	*get_input_resource();
	//Obtain an input resource
    //@}

    /** @name Implemented from output_resource_owner
     *
     */
    //@{
	/** Returns the output resource for this element.  This is generally a
	    data buffer or a wrapper for file output. */
	virtual
		output_resource
	*get_output_resource();
	//Obtain an output resource
    //@}
	//======================================================================

	//tree_number control===================================================
    private:
	virtual
		verified_element
	*tree_base();
	//Determine the base of the tree

	virtual
		void
	change_tree(tree_number*);
	//Recursively change trees

	virtual
		void
	set_tree_number(tree_number*);
	//Set the tree number of this element

	virtual
		tree_number
	*get_tree_number() const;
	//Get the tree number of this element
	//======================================================================

public:
	/** The destructor has 2 distinct behaviors.  If this element is
	    owned by another element, destruction will result in this element
	    being removed from the hierarchy using a remove_self-type operation
	    and this element will destruct along with all sub-elements.  If
	    this element has no owner, and is therefore the base of the
	    hierarchy, *all* peer elements after this element will be
	    destructed.  This is necessary for memory management. */
	virtual
	~linked_section();
	//Implemented to remove self if necessary

private:
	//Reference counter control---------------------------------------------
	virtual
		bool
	add_reference_counter(section_releaser&);
	//Start tracking a 'section_releaser'

	virtual
		void
	remove_reference_counter(section_releaser&);
	//Stop tracking a 'section_releaser'

		void
	clear_counters();
	//Clear references to this element

		std::list <section_releaser*>
	reference_counters;
	//Tracked reference counters
	//----------------------------------------------------------------------

	static
		storage_section
	*set_free(storage_section*);
	//Remove ownership from an element

		bool
	lineage_check(const storage_section*) const;
	//Check the lineage of an element to be added

		tree_number
	*owning_tree;
	//Reference to the owning tree

		storage_section
	*next_element, *child_element;
	//Next element, first child element
	//These are deleted when this is deleted

		storage_section
	*previous_element;
	//Pointer to the previous element

		parent_storage
	*parent_element;
	//Pointer to the parent element
}; //END------------------------------------------------------------------------

#endif
