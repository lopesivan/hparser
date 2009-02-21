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

#ifndef MULTI_OUTPUT_HPP
#define MULTI_OUTPUT_HPP

#include "data-output.hpp"

//Class multi_output------------------------------------------------------------
//Allows multiple output interfaces for a single object

	/*! \class multi_output
	    \brief Interchangable output interface.
	    \ingroup input_group
	    \ingroup user_group

	    This class provides an abstract interface for objects with
	    interchangable output interfaces.  The means of interface changing
	    is up to the derived class.  This class polls an abstract
	    function for the current interface.
	 */

class multi_output :
	virtual public output_sender
{
public:
	//From 'output_sender'==================================================
	virtual
		const output_sender
	*send_data(data_output*) const;
	//Send data, return element to send next output

	virtual
		bool
	collect_data(composite_data&) const;
	//Collect data from elements
	//======================================================================

	virtual inline
	~multi_output() {};

private:
	//Current sender========================================================
	/** Obtain the current output interface. */
	virtual
		const output_sender
	*current_sender() const = 0;
	//Obtain the current output sender
	//======================================================================
}; //END------------------------------------------------------------------------

#endif
