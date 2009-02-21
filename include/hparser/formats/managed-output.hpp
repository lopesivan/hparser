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

#ifndef MANAGED_OUTPUT_HPP
#define MANAGED_OUTPUT_HPP

#include "../data-output.hpp"
#include "../output-control.hpp"

//Class managed_ouput-----------------------------------------------------------
//Common managed output functions

	/*! \class managed_ouput
	    \brief Common formatted-output functions.
	    \ingroup output_group
	    \ingroup user_group

	    This class provides the basic functions required for format
	    classes to automatically export output.  This is the minimum
	    interface required by all format classes provided.
	 */

class managed_ouput :
	virtual public output_control
{
public:
	virtual inline
	~managed_ouput() {};

protected:
	//Output functions======================================================
	/** Send the actual content of this element. */
	virtual
		bool
	send_content(data_output*) const = 0;
	//Send the section's content

	/** Return the first sub-element of this element. */
	virtual
		const output_sender
	*get_subsection() const = 0;
	//Obtain the first subsection

	/** Return the first peer element following this element. */
	virtual
		const output_sender
	*get_next() const = 0;
	//Obtain the next section

	/** Return the parent of this element. */
	virtual
		const output_sender
	*get_out_parent() const = 0;
	//Obtain the next section up
	//======================================================================
}; //END------------------------------------------------------------------------

#endif
