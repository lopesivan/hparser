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

#ifndef GENERIC_FILE_HPP
#define GENERIC_FILE_HPP

#include <fstream>
#include <string>

#include "../file-input.hpp"
#include "../file-output.hpp"

//Typedef file_position---------------------------------------------------------
//Denotes position in a file
typedef long long file_position; //END------------------------------------------

//Typedef file_name-------------------------------------------------------------
//Stores name of a file
typedef std::string file_name; //END--------------------------------------------

//Class generic_file------------------------------------------------------------
//Basic file input/output interface

	/*! \class generic_file
	    \brief Generic file input/output interface.
	    \ingroup files_group

	    This class provides a shell for implementing a file input and output
	    interface.  This class implements most of the required file
	    functions and provides a std::fstream to derived classes so they can
	    only need to worry about extracting input and sending output.
	 */

class generic_file :
	public file_input,
	public file_output
{
public:
	generic_file();

	/*! Retrieve the current file name.
	 */

    /** @name File Name Functions
     *
     */
    //@{
		const file_name
	&file() const;
	//get current file name

	/*! Set the current file name.
	 */

		bool
	set_file(const file_name&);
	//change file name
    //@}

	//From 'file_user'======================================================
    /** @name Implemented from file_user
     *
     */
    //@{
	/*! Determine if the file is open.
	 */

		bool
	is_open();
	//Determine if the file is open

	/*! Close the file.
	 */

		bool
	close_file();
	//Close the file
    //@}
	//======================================================================

	//From 'data_input'=====================================================
    /** @name Implemented from data_input
     *
     */
    //@{
	/*! End-of-data determination.
	 */

		bool
	end_of_data() const;
	//Find out if this is the end of the data
    //@}
	//======================================================================

	//From 'data_output'====================================================
    /** @name Implemented from data_output
     *
     */
    //@{
	/*! Closed file determination.
	 */

		bool
	is_closed() const;
	//Find out if the destination is closed
    //@}
	//======================================================================

	//File input============================================================
    /** @name Read-related Functions
     *
     */
    //@{
	/*! Obtain the current read position.
	 */

		file_position
	read_position();
	//Obtain the current read position

	/*! Set the current read position.
	 */

		bool
	set_read_position(file_position);
	//Set the read position

	/*! Obtain the current file's size.
	 */

		file_position
	file_size();
	//Obtain the file size
    //@}
	//======================================================================

	//File output===========================================================
    /** @name Write-related Functions
     *
     */
    //@{
	/*! Obtain the current write position.
	 */

		file_position
	write_position();
	//Obtain the current write position

	/*! Set the current write position.
	 */

		bool
	set_write_position(file_position);
	//Set the write position
    //@}
	//======================================================================

protected:

	/*! File stream for use by implementing class.
	 */

		std::fstream
	file_stream;
	//File stream interface

	/*! Name of the current file.
	 */

		file_name
	current_file;
	//Name of the current file

	/*! State of being open.
	 */

		unsigned char
	open_state;
	//State of open-ness
}; //END------------------------------------------------------------------------

//Struct text_file--------------------------------------------------------------
//Opens files in text mode

	/*! \class text_file
	    \brief Text input/output file interface.
	    \ingroup files_group

	    This class implements the open_file function of generic_file to open
	    files in text mode.
	 */

struct text_file :
	public generic_file
{
	//From 'file_user'======================================================
    /** @name Implemented from file_user
     *
     */
    //@{
	/*! Open the current file.
	 */

		bool
	open_file(bool, bool);
	//Open the file (open read, open write)
    //@}
	//======================================================================
}; //END------------------------------------------------------------------------

//Struct bin_file---------------------------------------------------------------
//Opens files in binary mode

	/*! \class bin_file
	    \brief Binary input/output file interface.
	    \ingroup files_group
	    \ingroup user_group

	    This class implements the open_file function of generic_file to open
	    files in binary mode.
	 */

struct bin_file :
	public generic_file
{
	//From 'file_user'======================================================
    /** @name Implemented from file_user
     *
     */
    //@{
	/*! Open the current file.
	 */

		bool
	open_file(bool, bool);
	//Open the file (open read, open write)
    //@}
	//======================================================================
}; //END------------------------------------------------------------------------

#endif
