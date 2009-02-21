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

#ifndef MANAGED_INPUT_HPP
#define MANAGED_INPUT_HPP

#include "../data-input.hpp"
#include "../input-control.hpp"

//Class managed_input-----------------------------------------------------------
//Common managed input functions

	/*! \class managed_input
	    \brief Common formatted-input functions.
	    \ingroup input_group
	    \ingroup user_group

	    This class provides the basic functions required for format
	    classes to automatically parse input.  This is the minimum
	    interface required by all format classes provided.
	 */

class managed_input :
	virtual public input_control
{
public:
	virtual inline
	~managed_input() {};

protected:
	//Input functions=======================================================
	/** Determine if the current data makes sense as input for the desired
	    type of input.  For example: Is it a complete tag, descriptor, or
	    text section? */
	virtual
		bool
	makes_sense(data_input*) const = 0;
	//Ensure the section makes sense

	/** Determine if the current data indicates a new sub-element to this
	    section or element. */
	virtual
		bool
	is_subsection(data_input*) const = 0;
	//Check for a subsection

	/** Based on a true return from is_subsection, create a sub-element to
	    be added as a child to this element.  This normally will have the
	    same data index as is_subsection to allow parsing for the correct
	    element type.  This function should increment input so that the
	    sub-element starts parsing with the next input index.  The new
	    element must be added as a child with AddChild before returning
	    it. */
	virtual
		input_receiver
	*new_subsection(data_input*) = 0;
	//Create a new subsection

	/** If the data is valid and does not indicate a sub-element, this
	    function is called to apply the input.  This should parse and
	    store input data until the section this element contains is
	    complete, as denoted by a fixed size or a closing tag.  This
	    function should return *this* after each input operation for each
	    new section of data so that it goes through the evaluation
	    process.  Once input is applied, increment the input counter. */
	virtual
		input_receiver
	*apply_input(data_input*) = 0;
	//Apply the input data to this section

	/** Return the parent of this element. */
	virtual
		input_receiver
	*get_in_parent() const = 0;
	//Obtain the next section up
	//======================================================================
}; //END------------------------------------------------------------------------

#endif
