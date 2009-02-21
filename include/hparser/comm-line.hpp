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

#ifndef COMM_LINE_HPP
#define COMM_LINE_HPP

#include "impl-defined.hpp"

//Struct comm_line--------------------------------------------------------------
//Message interface between objects

	/*! \class comm_line
	    \brief Communication interface.
	    \ingroup interfaces_group

	    This class provides a generic interface to library objects for
	    receiving messages.  The messages are arbitrary, and this interface
	    is provided to make the library more expandable.  Intended purposes
	    include requesting information, changing modes/settings, passing
	    errors up the tree, etc.  The message type is implementation-
	    defined, however.

	    \attention This class uses the comm_message class which is entirely
	    implementation-defined by the using program.  An optional definition
	    is available for simple text processing.

	    @see string-message.hpp is provided to mirror a std::string.
	 */

struct comm_line
{

	/*! \brief Message conduit function.

	    This function should pass the message on to other tree elements in
	    the appropriate direction, and send to local_message if applicable.
	 */

	virtual
		bool
	send_message(comm_message&);
	//Send a message

	/*! \brief Local application of message.

	    This function applies the message information locally and does not
	    pass the message on.
	 */

	virtual
		bool
	local_message(comm_message&);
	//Apply the message locally
	//Non-abstract, but functionless by default

	virtual inline
	~comm_line() {};
}; //END------------------------------------------------------------------------

#endif
