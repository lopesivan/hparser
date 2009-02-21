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

#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include "file-input.hpp"
#include "file-output.hpp"

/*! \defgroup files_group File Interfaces and Functions
*/

//Function load_file------------------------------------------------------------
//Automatically manages importation of data from a file

	/*! \brief File importation function.
	    \ingroup automation_group
	    \ingroup files_group

	    This function imports file data using a file_input and provides
	    control to the data_importer given.  If the file_input is not open
	    then the function opens it.  If it is already open then it leaves it
	    open after importation is done with the index left where it was the
	    last operation.
	 */

	bool
load_file(data_importer*, file_input*);
//Data destination, data source

//Function save_file------------------------------------------------------------
//Automatically manages exportation of data to a file

	/*! \brief File exportation function.
	    \ingroup automation_group
	    \ingroup files_group

	    This function exports file data using a file_output and provides
	    control to the data_exporter given.  If it is already open then it
	    leaves it open after importation is done with the index left where
	    it was the last operation.
	 */

	bool
save_file(const data_exporter*, file_output*);
//Data source, data destination

#endif
