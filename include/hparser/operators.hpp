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

#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include "storage-section.hpp"

//storage_section functions-----------------------------------------------------

	/*! \ingroup element_group

	    Swap 2 elements in the hierarchy structure.  Elements do not need
	    to be in the same hierarchy to be swapped.  The only requirement
	    is that all reconnections are allowed by the implementations of
	    the connection_control interfaces of the effected elements.
	 */

	bool
swap_elements(storage_section*, storage_section*);
//Swap element positions

	/*! \ingroup element_group

	    Check for direct and indirect parent/child or previous/next
	    ownership of two elements.
	 */

	bool
operator >> (const storage_section&, const storage_section&);
//Left element laterally/vertically owns the right

	/*! \ingroup element_group

	    Check for direct and indirect child/parent or next/previous
	    ownership of two elements.
	 */

	bool
operator << (const storage_section&, const storage_section&);
//Right element laterally/vertically owns the left

	/*! \ingroup element_group

	    Check for direct and indirect parent/child ownership of two
	    elements.
	 */

	bool
operator > (const storage_section&, const storage_section&);
//Left element vertically owns the right

	/*! \ingroup element_group

	    Check for direct and indirect child/parent ownership of two
	    elements.
	 */

	bool
operator < (const storage_section&, const storage_section&);
//Right element vertically owns the left

	/*! \ingroup element_group

	    Check for parent/child ownership independence, or equality, of
	    two elements.
	 */

	bool
operator == (const storage_section&, const storage_section&);
//Neither element vertically owns the other

	/*! \ingroup element_group

	    Check for parent/child ownership dependence, or inequality, of
	    two elements.
	 */

	bool
operator != (const storage_section&, const storage_section&);
//One element vertically owns the other

	/*! \ingroup element_group

	    Check for direct and indirect previous/next ownership of two
	    elements.
	 */

	bool
operator >= (const storage_section&, const storage_section&);
//Left element laterally owns the right

	/*! \ingroup element_group

	    Check for direct and indirect next/previous ownership of two
	    elements.
	 */

	bool
operator <= (const storage_section&, const storage_section&);
//Right element laterally owns the left

	/*! \ingroup element_group

	    Check that two elements are peers on the same branch of the
	    same hierarchy.
	 */

	bool
operator && (const storage_section&, const storage_section&);
//Two elements are on the same lateral path

	/*! \ingroup element_group

	    Check that two elements aren't peers on the same branch of the
	    same hierarchy.
	 */

	bool
operator ^ (const storage_section&, const storage_section&);
//Two elements are not on the same lateral path

	/*! \ingroup element_group

	    Check that two elements are on completely independent hierarchies.
	 */

	bool
operator || (const storage_section&, const storage_section&);
//Two elements are on completely independent trees
//END---------------------------------------------------------------------------

#endif
