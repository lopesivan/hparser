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

#ifndef MULTI_SOURCE_CPP
#define MULTI_SOURCE_CPP

#include "multi-source.hpp"

//multi_source function bodies==================================================
	//From 'data_input'=====================================================
	const input_section &multi_source::receive_input()
	//Obtain the next input section
	{
	data_input *Current = this->current_source();
	if (!Current) return this->default_input();
	return Current->receive_input();
	}

	bool multi_source::next_input(input_count cCount)
	//Increment the input index
	{
	data_input *Current = this->current_source();
	if (!Current) return false;
	return Current->next_input(cCount);
	}

	bool multi_source::end_of_data() const
	//Find out if this is the end of the data
	{
	data_input *Current = this->current_source();
	if (!Current) return true;
	return Current->end_of_data();
	}

	bool multi_source::is_terminated() const
	//Find out if this is the REAL end of the data
	{
	data_input *Current = this->current_source();
	if (!Current) return true;
	return Current->is_terminated();
	}

	bool multi_source::replace_buffer(input_count cCount)
	//Replace data currently in buffer
	{
	data_input *Current = this->current_source();
	if (!Current) return false;
	return Current->replace_buffer(cCount);
	}

	bool multi_source::set_input_mode(unsigned int mMode)
	//Set the current input mode
	{
	data_input *Current = this->current_source();
	if (!Current) return false;
	return Current->set_input_mode(mMode);
	}
	//======================================================================
//==============================================================================

#endif
