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

#ifndef DESCRIPTOR_OUTPUT_HPP
#define DESCRIPTOR_OUTPUT_HPP

#include "../data-output.hpp"
#include "managed-output.hpp"

//Class descriptor_output-------------------------------------------------------
//Manages descriptor-formatted output

	/*! \class descriptor_output
	    \brief Output interface for descriptor-formated sections.
	    \ingroup descriptor_group
	    \ingroup output_group
	    \ingroup user_group

	    This class provides a simple interface for exporting data that uses
	    a descriptor-style format (where each section's header contains all
	    information pertaining to the section's size.)  This interface must
	    be combined virtually with an element class in order to be useful.
	 */

class descriptor_output :
	virtual public output_sender,
	public managed_ouput
{
public:
	//Output entry point====================================================

	/*! \brief Sequential output request.

	    This function is implemented to send the section's descriptor,
	    send its own content, then pass control to its first sub-section.
	    After all sub-sections have passed their data, control goes to the
	    next section, and finally to its parent.
	 */

	virtual
		const output_sender
	*send_data(data_output*) const;
	//Send data, return element to send next output
	//======================================================================

	virtual inline
	~descriptor_output() {};

protected:
	//Output functions======================================================

	/*! \brief Output section descriptor.

	    This function is called to send the section's descriptor to output.
	 */

	virtual
		bool
	send_descriptor(data_output*) const = 0;
	//Send the descriptor
	//======================================================================
}; //END------------------------------------------------------------------------

#endif
