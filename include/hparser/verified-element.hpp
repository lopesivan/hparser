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

#ifndef VERIFIED_ELEMENT_HPP
#define VERIFIED_ELEMENT_HPP

//Typedef tree_number-----------------------------------------------------------
//Number of elements in a tree
typedef long long tree_number; //END--------------------------------------------

//Class verified_element--------------------------------------------------------
//Abstract data storage class which is intended to contain others

	/*! \class verified_element
	    \brief Prevents circular ownership.
	    \ingroup interfaces_group

	    This class is used to enumerate hierarchies to make pre-insertion
	    checking more reliable.  Elements are checked against their
	    insertion points to make sure the insertion points aren't indirectly
	    owned by the element being inserted.
	 */

class verified_element
{
	//tree_number control===================================================
    protected:
	virtual
		bool
	merge_to_tree(verified_element*);
	//Merge tree numbers (before merge)

	static
		bool
	split_from_tree(verified_element*);
	//Split tree numbers (after split)

	virtual
		bool
	same_tree(const verified_element*) const;
	//Compare trees

	virtual
		bool
	switch_trees(tree_number*);
	//Switch tree references

	static
		void
	change_tree(verified_element*, tree_number*);
	//Recursively change trees

    private:
	virtual
		verified_element
	*tree_base() = 0;
	//Determine the base of the tree

	virtual
		void
	change_tree(tree_number*) = 0;
	//Recursively change trees

	virtual
		void
	set_tree_number(tree_number*) = 0;
	//Set the tree number of this element

	virtual
		tree_number
	*get_tree_number() const = 0;
	//Get the tree number of this element
	//======================================================================

protected:
	virtual inline
	~verified_element() {};
}; //END------------------------------------------------------------------------

#endif
