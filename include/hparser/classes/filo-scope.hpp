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

#ifndef FILO_SCOPE_HPP
#define FILO_SCOPE_HPP

#include <string>
#include <deque>

#include "../impl-defined.hpp"

typedef std::string scope_layer;

	/*! \class scope_identifier
	    \brief FILO implementation of scope identifers.
	    \ingroup implementation_group

	    This is an optional class definition for scope_identifier.  This
	    class may be defined by the user instead of using this definition.
	    Make sure to include the same class definition in all communicating
	    units of your program!  This definition treats the identifier as a
	    stack of scopes.  Layers are added and removed from the bottom and
	    comparison to a reference layer is done with the bottom layer.  This
	    class is derived from std::deque.

	    @see impl-defined.hpp shows all implementation-defined classes.
	 */

struct scope_identifier : public std::deque <scope_layer>
{
    /** @name Inner Scope Functions
     *  Functions to manipulate the lowest-level scope
     */
    //@{
	/** Enter the scope of a sub-section. */
	scope_identifier &enter_scope(const scope_layer&);
	/** Enter the scope of a sub-section. */
	scope_identifier &operator >> (const scope_layer&);

	/** Leave the scope of a sub-section or sub-sections. */
	scope_identifier &leave_scope(unsigned int = 1);
	/** Leave the scope of a sub-section or sub-sections. */
	scope_identifier &operator << (unsigned int);
    //@}

    /** @name Outer Scope Functions
     *  Functions to manipulate the highest-level scope
     */
    //@{
	/** Specify an additional outer scope. */
	scope_identifier &globalize_scope(const scope_layer&);
	/** Specify an additional outer scope. */
	scope_identifier &operator << (const scope_layer&);

	/** Remove the outermost scope or scopes. */
	scope_identifier &localize_scope(unsigned int = 1);
	/** Remove the outermost scope or scopes. */
	scope_identifier &operator >> (unsigned int);
    //@}

	/*! Clear the entire scope.
	 */

	scope_identifier &clear_scope();

	/*! Return a composite of the current scope.
	 */

	scope_layer composite_scope(const char* = ":") const;

	/*! Determine if the innermost scope matches that provided.
	 */

	bool operator == (const scope_layer&) const;

	/*! Determine if the innermost scope doesn't match that provided.
	 */

	bool operator != (const scope_layer&) const;
};

#endif
