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

#ifndef GENERIC_FILE_CPP
#define GENERIC_FILE_CPP

#include "generic-file.hpp"

//generic_file function bodies==================================================
	generic_file::generic_file() :
	open_state(false)
	{ }

	const file_name &generic_file::file() const
	//get current file name
	{ return current_file; }

	bool generic_file::set_file(const file_name &fFile)
	//change file name
	{
	if (this->is_open()) return false;
	current_file = fFile;
	return true;
	}

	//From 'file_user'======================================================
	bool generic_file::is_open()
	//Determine if the file is open
	{ return (this->open_state = file_stream.is_open()); }

	bool generic_file::close_file()
	//Close the file
	{
	file_stream.close();
	return true;
	}
	//======================================================================

	//From 'data_input'=====================================================
	bool generic_file::end_of_data() const
	//Find out if this is the end of the data
	{ return !file_stream || file_stream.eof() || !this->open_state; }
	//======================================================================

	//From 'data_output'====================================================
	bool generic_file::is_closed() const
	//Find out if the destination is closed
	{ return !file_stream || !this->open_state; }
	//======================================================================

	//File input============================================================
	file_position generic_file::read_position()
	//Obtain the current read position
	{ return file_stream.tellg(); }

	bool generic_file::set_read_position(file_position pPos)
	//Set the read position
	{
	if (!this->is_open()) return false;
	file_stream.seekg(pPos);
	return this->read_position() == pPos;
	}

	file_position generic_file::file_size()
	//Obtain the file size
	{
	if (!this->is_open()) return false;
	file_position Current = this->read_position();
	file_stream.seekg(0, std::ios::end);
	file_position End = this->read_position();
	this->set_read_position(Current);
	return End;
	}
	//======================================================================

	//File output===========================================================
	file_position generic_file::write_position()
	//Obtain the current write position
	{ return file_stream.tellp(); }

	bool generic_file::set_write_position(file_position pPos)
	//Set the write position
	{
	if (!this->is_open()) return false;
	file_stream.seekp(pPos);
	return this->write_position() == pPos;
	}
	//======================================================================
//==============================================================================

//text_file function bodies=====================================================
	//From 'file_user'======================================================
	bool text_file::open_file(bool rRead, bool wWrite)
	//Open the file (open read, open write)
	{
	if (this->is_open()) return false;

	if (rRead && wWrite)
	file_stream.open(current_file.c_str(), std::ios::in | std::ios::out);

	else if (rRead)
	file_stream.open(current_file.c_str(), std::ios::in);

	else if (wWrite)
	file_stream.open(current_file.c_str(), std::ios::out);

	else return false;

	file_stream.clear();
	file_stream.flush();

	open_state = !(!file_stream || file_stream.eof());

	return this->is_open();
	}
	//======================================================================
//==============================================================================

//bin_file function bodies======================================================
	//From 'file_user'======================================================
	bool bin_file::open_file(bool rRead, bool wWrite)
	//Open the file (open read, open write)
	{
	if (this->is_open()) return false;

	if (rRead && wWrite)
	file_stream.open(current_file.c_str(), std::ios::in | std::ios::out | std::ios::binary);

	else if (rRead)
	file_stream.open(current_file.c_str(), std::ios::in | std::ios::binary);

	else if (wWrite)
	file_stream.open(current_file.c_str(), std::ios::out | std::ios::binary);

	else return false;

	file_stream.clear();
	file_stream.flush();

	open_state = !(!file_stream || file_stream.eof());

	return this->is_open();
	}
	//======================================================================
//==============================================================================

#endif
