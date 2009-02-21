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

#ifndef SCOPE_LOCATOR_HPP
#define SCOPE_LOCATOR_HPP

#include "data-input.hpp"
#include "data-output.hpp"
#include "impl-defined.hpp"

//Struct scope_locator----------------------------------------------------------
//Interface for tracking scope of tree elements

	/*! \class scope_locator
	    \brief Scope-controllable object.
	    \ingroup input_group
	    \ingroup resource_group

	    This class provides basic functionality to manage parsing scopes
	    for a hierarchy.
	 */

struct scope_locator :
	virtual public input_receiver,
	virtual public output_sender
{
	/** Finds a matching element for the provided scope and returns it.
	    This recursively searches the hierarchy based on the given stack
	    of scope identifiers and returns the first element matching that
	    specific scope.  This is used to reset a parsing or exporting
	    position after an error.  The scope normally will come from the
	    current_scope function. */
	virtual
		scope_locator
	*locate_scope(const scope_identifier&) = 0;
	//Locate a scope within this scope

	/** Compiles a stack of scope identifiers, upward until the element
	    provided as the second element is reached, to indicate this
	    element's location in the hierarchy.  This is used to return to
	    this element when a parsing or exportation error occurs using the
	    locate_scope function. */
	virtual
		bool
	current_scope(scope_identifier&, const scope_locator*) const = 0;
	//Identify this scope

	/** Sends message to the hierarchy base to extract scope.  Intended to
            find the base and the base is intended to call the current_scope
            function with a scope_identifier it retains. */
	virtual
		bool
	base_current_scope(const scope_locator*) const = 0;
	//Identify this scope

	virtual inline
	~scope_locator() {};
}; //END------------------------------------------------------------------------

#endif
