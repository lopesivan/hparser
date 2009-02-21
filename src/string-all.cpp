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

#ifndef STRING_ALL_CPP
#define STRING_ALL_CPP

#include "string-all.hpp"

//input_section function bodies=================================================
	input_section::input_section() {}
	input_section::input_section(const char *sString) : std::string(sString) {}
	input_section::input_section(const std::string &sString) : std::string(sString) {}

	input_section &input_section::operator = (const char *sString)
	{
	this->std::string::operator = (sString);
	return *this;
	}

	input_section &input_section::operator = (const std::string &sString)
	{
	this->std::string::operator = (sString);
	return *this;
	}
//==============================================================================

//output_section function bodies================================================
	output_section::output_section() {}
	output_section::output_section(const char *sString) : std::string(sString) {}
	output_section::output_section(const std::string &sString) : std::string(sString) {}

	output_section &output_section::operator = (const char *sString)
	{
	this->std::string::operator = (sString);
	return *this;
	}

	output_section &output_section::operator = (const std::string &sString)
	{
	this->std::string::operator = (sString);
	return *this;
	}
//==============================================================================

//composite_data function bodies================================================
	composite_data::composite_data() {}
	composite_data::composite_data(const char *sString) : std::string(sString) {}
	composite_data::composite_data(const std::string &sString) : std::string(sString) {}

	composite_data &composite_data::operator = (const char *sString)
	{
	this->std::string::operator = (sString);
	return *this;
	}

	composite_data &composite_data::operator = (const std::string &sString)
	{
	this->std::string::operator = (sString);
	return *this;
	}
//==============================================================================

//comm_message function bodies==================================================
	comm_message::comm_message() {}
	comm_message::comm_message(const char *sString) : std::string(sString) {}
	comm_message::comm_message(const std::string &sString) : std::string(sString) {}

	comm_message &comm_message::operator = (const char *sString)
	{
	this->std::string::operator = (sString);
	return *this;
	}

	comm_message &comm_message::operator = (const std::string &sString)
	{
	this->std::string::operator = (sString);
	return *this;
	}
//==============================================================================

std::ostream &operator << (std::ostream &sStream, const input_section &oOut)
{ return sStream << static_cast <const std::string&> (oOut); }

std::ostream &operator << (std::ostream &sStream, const output_section &oOut)
{ return sStream << static_cast <const std::string&> (oOut); }

std::ostream &operator << (std::ostream &sStream, const composite_data &oOut)
{ return sStream << static_cast <const std::string&> (oOut); }

std::ostream &operator << (std::ostream &sStream, const comm_message &oOut)
{ return sStream << static_cast <const std::string&> (oOut); }

#endif
