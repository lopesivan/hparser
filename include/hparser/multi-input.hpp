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

#ifndef MULTI_INPUT_HPP
#define MULTI_INPUT_HPP

#include "data-input.hpp"

//Class multi_input-------------------------------------------------------------
//Allows multiple input interfaces for a single object

	/*! \class multi_input
	    \brief Interchangable input interface.
	    \ingroup input_group
	    \ingroup user_group

	    This class provides an abstract interface for objects with
	    interchangable input interfaces.  The means of interface changing
	    is up to the derived class.  This class polls an abstract
	    function for the current interface.
	 */

class multi_input :
	virtual public input_receiver
{
public:
	//From 'input_receiver'=================================================
	virtual
		input_receiver
	*receive_data(data_input*);
	//Receive data, return element to receive next input

	virtual
		bool
	expand_data(composite_data&);
	//Expand data into elements
	//======================================================================

	virtual inline
	~multi_input() {};

private:
	//Current receiver======================================================
	/** Obtain the current input interface. */
	virtual
		input_receiver
	*current_receiver() const = 0;
	//Obtain the current input receiver
	//======================================================================
}; //END------------------------------------------------------------------------

#endif
