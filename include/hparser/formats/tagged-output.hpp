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

#ifndef TAGGED_OUTPUT_HPP
#define TAGGED_OUTPUT_HPP

#include "../data-output.hpp"
#include "managed-output.hpp"

//Class tagged_output-----------------------------------------------------------
//Manages tag-formatted output

	/*! \class tagged_output
	    \brief Output interface for tag-formated sections.
	    \ingroup tagged_group
	    \ingroup output_group
	    \ingroup user_group

	    This class provides a simple interface for exporting data that uses
	    a tagged (e.g. XML) format.  This interface must be combined
	    virtually with an element class in order to be useful.
	 */

class tagged_output :
	virtual public output_sender,
	public managed_ouput
{
public:
	//Output entry point====================================================

	/*! \brief Sequential output request.

	    This function is implemented to send the section's open tag and
	    its own data, then pass control to its first sub-section.  After all
	    sub-sections have passed their data it sends the close tag and
	    control goes to the next section, and finally to its parent.
	 */

	virtual
		const output_sender
	*send_data(data_output*) const;
	//Send data, return element to send next output
	//======================================================================

	virtual inline
	~tagged_output() {};

protected:
	//Output functions======================================================

	/*! \brief Send section open tag.

	    This function should send the opening tag for the section, e.g.
	    "<section>".
	 */

	virtual
		bool
	send_open_tag(data_output*) const = 0;
	//Send the open tag


	/*! \brief Send section close tag.

	    This function should send the closing tag for the section, e.g.
	    "</section>".
	 */

	virtual
		bool
	send_close_tag(data_output*) const = 0;
	//Send the close tag
	//======================================================================
}; //END------------------------------------------------------------------------

#endif
