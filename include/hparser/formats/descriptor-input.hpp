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

#ifndef DESCRIPTOR_INPUT_HPP
#define DESCRIPTOR_INPUT_HPP

#include "../data-input.hpp"
#include "managed-input.hpp"

//Class descriptor_input--------------------------------------------------------
//Manages descriptor-formatted input

	/*! \class descriptor_input
	    \brief Input interface for descriptor-formated sections.
	    \ingroup descriptor_group
	    \ingroup input_group
	    \ingroup user_group

	    This class provides a simple interface for parsing data that uses
	    a descriptor-style format (where each section's header contains all
	    information pertaining to the section's size.)  This interface must
	    be combined virtually with an element class in order to be useful.
	 */

struct descriptor_input :
	virtual public input_receiver,
	public managed_input
{
public:
	//Input entry point=====================================================

	/*! \brief Sequential input request.

	    This function is implemented to parse a section of data.  It calls
	    the functions of managed_input to determine whether or not a portion
	    of data contains a sub-section and creates a new one if necessary.
	    This process is repeated until the section is completely filled as
	    indicated by section_complete.
	 */

	virtual
		input_receiver
	*receive_data(data_input*);
	//Receive data, return element to receive next input
	//======================================================================

	virtual inline
	~descriptor_input() {};

protected:
	//Input functions=======================================================

	/*! \brief Section end determination.

	    This function is called internally to check to see if all data has
	    been parsed for this section.  The determination should be based on
	    how much data has been parsed vs. how much data the descriptor
	    indicated is in the section.
	 */

	virtual
		bool
	section_complete(data_input*) const = 0;
	//Check for completion of section
	//======================================================================
}; //END------------------------------------------------------------------------

#endif
