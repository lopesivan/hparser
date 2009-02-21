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

#ifndef MULTI_DESTINATION_HPP
#define MULTI_DESTINATION_HPP

#include "data-output.hpp"

//Class multi_destination-------------------------------------------------------
//Allows multiple output interfaces for a single object

	/*! \class multi_destination
	    \brief Multiple-destination data output.
	    \ingroup system_group
	    \ingroup output_group

	    This class serves as an output source selector.  The deriving class
	    will generally have more than one data_output built in and will
	    select one of the destinations for a particular input operation
	    based on that class' own criteria.
	 */

class multi_destination :
	virtual public data_output
{
public:
	//From 'data_output'====================================================
	virtual
		bool
	send_output(const output_section&);
	//Send the next output section

	virtual
		bool
	is_closed() const;
	//Find out if the destination is closed

	virtual
		bool
	set_output_mode(unsigned int);
	//Set the current output mode

	virtual
		bool
	synchronize();
	//Force all output to be sent or written
	//======================================================================

	virtual inline
	~multi_destination() {};

private:
	//Current destination===================================================
	/** Obtain the current output destination. */
	virtual
		data_output
	*current_destination() const = 0;
	//Obtain the current output destination
	//======================================================================
}; //END------------------------------------------------------------------------

#endif
