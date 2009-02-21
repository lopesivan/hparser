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

#ifndef INPUT_RESOURCE_HPP
#define INPUT_RESOURCE_HPP

#include "impl-defined.hpp"

/*! \defgroup resource_group Random-access Resources
*/

//Typedef input_resource_count--------------------------------------------------
//Count of input resource units
typedef int input_resource_count; //END-----------------------------------------

//Struct input_resource---------------------------------------------------------
//Controls a random-access input resource

	/*! \class input_resource
	    \brief Random-access input resource.
	    \ingroup input_group
	    \ingroup resource_group
	    \ingroup user_group

	    This class provides a random-access input interface.
	 */

struct input_resource
{

	/*! Obtain input using an index and an input size.
	 */

	virtual
		const input_section
	&get_input(input_resource_count, input_resource_count) = 0;
	//Obtain input data using index and size

	/*! Set the input index offset.
	 */

	virtual
		bool
	set_input_index(input_resource_count = 0) = 0;
	//Set base index using an offset

	virtual inline
	~input_resource() {};
}; //END------------------------------------------------------------------------

//Class input_resource_owner----------------------------------------------------
//Owner of an input resource

	/*! \class input_resource_owner
	    \brief Random-access input resource owner.
	    \ingroup input_group
	    \ingroup resource_group
	    \ingroup user_group

	    This class provides an interface for providing an input resource.
	 */

class input_resource_owner
{
protected:

	/*! Obtain the input resource.
	 */

	virtual
		input_resource
	*get_input_resource();
	//Obtain an input resource
	//Non-abstract, but functionless by default

	/*! Obtain the input resource from another owner.
	 */

	static
		input_resource
	*get_input_resource(input_resource_owner*);
	//Obtain an input resource

public:
	virtual inline
	~input_resource_owner() {};
}; //END------------------------------------------------------------------------

#endif
