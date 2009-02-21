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

#ifndef OUTPUT_RESOURCE_HPP
#define OUTPUT_RESOURCE_HPP

#include "impl-defined.hpp"

//Typedef output_resource_count-------------------------------------------------
//Count of output resource units
typedef int output_resource_count; //END----------------------------------------

//Struct output_resource--------------------------------------------------------
//Controls a random-access output resource

	/*! \class output_resource
	    \brief Random-access output resource.
	    \ingroup output_group
	    \ingroup resource_group
	    \ingroup user_group

	    This class provides a random-access output interface.
	 */

struct output_resource
{

	/*! Send output using an index.
	 */

	virtual
		bool
	set_output(output_resource_count, const output_section&) = 0;
	//Transmit output data using an index

	/*! Set the current output index offset.  This will be added to all
	    output indexes used in set_output.
	 */

	virtual
		bool
	set_output_index(output_resource_count = 0) = 0;
	//Set base index using an offset

	virtual inline
	~output_resource() {};
}; //END------------------------------------------------------------------------

//Class output_resource_owner---------------------------------------------------
//Owner of an output resource

	/*! \class output_resource_owner
	    \brief Random-access output resource owner.
	    \ingroup output_group
	    \ingroup resource_group
	    \ingroup user_group

	    This class provides an interface for providing an output resource.
	 */

class output_resource_owner
{
protected:

	/*! Obtain the output resource.
	 */

	virtual
		output_resource
	*get_output_resource();
	//Obtain an output resource
	//Non-abstract, but functionless by default

	/*! Obtain the output resource from another owner.
	 */

	static
		output_resource
	*get_output_resource(output_resource_owner*);
	//Obtain an output resource

public:
	virtual inline
	~output_resource_owner() {};
}; //END------------------------------------------------------------------------

#endif
