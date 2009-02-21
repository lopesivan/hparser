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

#ifndef TAGGED_STORAGE_CPP
#define TAGGED_STORAGE_CPP

#include "tagged-storage.hpp"

//tagged_input function bodies==================================================
	//Input entry point=====================================================
	input_receiver *tagged_input::receive_data(data_input *iInput)
	//Receive data, return element to receive next input
	{
	//Make sure the source exists
	if (!iInput) return 0 /*NULL*/;

	//Make sure the input makes sense
	if (!this->makes_sense(iInput)) return 0 /*NULL*/;

	//If the section is closed, return its parent section.
	if (!this->section_open()) return this->get_in_parent();

	if (this->is_close_tag(iInput))
	//Check for section close-----------------------------------------------
	 {
	//Close the section and return the parent section.
	this->set_section_open(false);
	return this->get_in_parent();
	 }
	//----------------------------------------------------------------------

	//If the input calls for a subsection, create one and return it.
	if (this->is_subsection(iInput)) return this->new_subsection(iInput);

	//If nothing else, apply the data to this section.
	//(Counts on 'apply_input' calling 'next_input'; allows for multiple input
	//operations from a single input application.)
	return this->apply_input(iInput);
	}
	//======================================================================
//==============================================================================

//tagged_output function bodies=================================================
	//Output entry point====================================================
	const output_sender *tagged_output::send_data(data_output *oOutput) const
	//Send data, return element to send next output
	{
	//Make sure the destination exists
	if (!oOutput) return 0 /*NULL*/;

	if (!this->sending_subs())
	//Send open tag and section content
	 {
	if (!this->send_open_tag(oOutput)) return 0 /*NULL*/;
	if (!this->send_content(oOutput)) return 0 /*NULL*/;
	 }

	if (!this->sending_subs() && this->get_subsection())
	//If there are subsections which haven't been sent, send them...
	 {
	this->set_sending_subs(true);
	return this->get_subsection();
	 }

	else
	//...otherwise send the close tag, return the next section, or return
	//the parent section if there isn't a next section.
	 {
	this->set_sending_subs(false);
	if (!this->send_close_tag(oOutput)) return 0 /*NULL*/;
	if (this->get_next()) return this->get_next();
	else                 return this->get_out_parent();
	 }
	}
	//======================================================================
//==============================================================================

#endif
