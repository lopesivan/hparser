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

#ifndef FILE_MANAGER_CPP
#define FILE_MANAGER_CPP

#include "file-manager.hpp"

//Function load_file------------------------------------------------------------
//Automatically manages importation of data from a file
bool load_file(data_importer *rRec, file_input *iIn)
{
	if (!iIn || !rRec) return false;

	bool WasOpen = iIn->is_open();

	if (!WasOpen && !iIn->open_file(true, false)) return false;

	//Forces data to be read (in case it needs to be blindly skipped.)
	iIn->receive_input();

	if (!import_data(rRec, iIn))
	{
	if (!WasOpen) iIn->close_file();
	return false;
	}

	if (!WasOpen && !iIn->close_file()) return false;

	return true;
} //END-------------------------------------------------------------------------

//Function save_file------------------------------------------------------------
//Automatically manages exportation of data to a file
bool save_file(const data_exporter *sSend, file_output *oOut)
{
	if (!oOut || !sSend) return false;

	bool WasOpen = oOut->is_open();

	if (!WasOpen && !oOut->open_file(false, true))  return false;

	if (!export_data(sSend, oOut))
	{
	if (!WasOpen) oOut->close_file();
	return false;
	}

	if (!WasOpen && !oOut->close_file()) return false;

	return true;
} //END-------------------------------------------------------------------------

#endif
