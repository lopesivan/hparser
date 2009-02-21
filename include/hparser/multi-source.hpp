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

#ifndef MULTI_SOURCE_HPP
#define MULTI_SOURCE_HPP

#include "data-input.hpp"

//Class multi_source------------------------------------------------------------
//Allows multiple input sources for a single object

	/*! \class multi_source
	    \brief Multiple-source data input.
	    \ingroup system_group
	    \ingroup input_group

	    This class serves as an input source selector.  The deriving class
	    will generally have more than one data_input built in and will select
	    one of the sources for a particular input operation based on that
	    class' own criteria.
	 */

class multi_source :
	virtual public data_input
{
public:
	//From 'data_input'=====================================================
	virtual
		const input_section
	&receive_input();
	//Obtain the next input section

	virtual
		bool
	next_input(input_count = 0);
	//Increment the input index

	virtual
		bool
	end_of_data() const;
	//Find out if this is the end of the data

	virtual
		bool
	is_terminated() const;
	//Find out if this is the REAL end of the data

	virtual
		bool
	replace_buffer(input_count = 0);
	//Replace data currently in buffer

	virtual
		bool
	set_input_mode(unsigned int);
	//Set the current input mode
	//======================================================================

	virtual inline
	~multi_source() {};

private:
	//Current source========================================================
	/** Obtain the current input source. */
	virtual
		data_input
	*current_source() const = 0;
	//Obtain the current input receiver

	/** Default input reference in case of a NULL input source. */
	virtual
		const input_section
	&default_input() const = 0;
	//Obtain the default input in case of error
	//======================================================================
}; //END------------------------------------------------------------------------

#endif
