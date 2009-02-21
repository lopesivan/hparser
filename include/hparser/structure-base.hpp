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

#ifndef STRUCTURE_BASE_HPP
#define STRUCTURE_BASE_HPP

#include "parent-storage.hpp"

//Class structure_base----------------------------------------------------------
//Base class for structure bases

	/*! \class structure_base
	    \brief Hierarchy base container.
	    \ingroup storage_group
	    \ingroup base_group
	    \ingroup user_group

	    This class serves as a simple base object for a hierarchy.  It is
	    the parent of the base element of the tree, and is therefore the
	    base of the tree.
	 */

class structure_base :
	virtual public parent_storage
{
public:
	structure_base();
	//Constructor

	structure_base(const structure_base&);
	//Copy constructor

		structure_base
	&operator = (const structure_base&);
	//Assignment operator

	//From 'CommLine'=======================================================
	virtual
		bool
	send_message(comm_message&);
	//Send a message
	//======================================================================

	//From 'triggered_update'===============================================
	virtual
		bool
	global_update();
	//Update object data globally
	//======================================================================

	//From 'parent_storage'=================================================
	virtual
		section_releaser
	set_child(section_releaser);
	//Sets the first child element
	//======================================================================

	virtual
	~structure_base();
	//Destructor

protected:
	//Tree branch management================================================
	/** Obtain the first branch of the tree. */
		storage_section
	*first_branch() const;
	//Provides a pointer to the first branch

	/** Add a new branch to the tree. */
		section_releaser
	add_branch(section_releaser);
	//Adds a new branch to the tree and returns it
	//======================================================================

	//Helpers---------------------------------------------------------------
	inline section_releaser add_branch(storage_section *eElement)
	{ return this->add_branch( section_releaser(eElement) ); }
	//----------------------------------------------------------------------

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

private:
		tree_number
	*owning_tree;
	//Reference to the owning tree

		storage_section
	*first_element;
	//First element (branch) of the tree
}; //END------------------------------------------------------------------------

#endif
