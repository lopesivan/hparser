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

#ifndef STORAGE_SECTION_CPP
#define STORAGE_SECTION_CPP

#include "storage-section.hpp"

//storage_section function bodies===============================================
	//Previous element in hierarchy=========================================
	storage_section *storage_section::set_previous(storage_section *eElement,
	storage_section *pPrevious)
	{ return eElement? eElement->set_previous(pPrevious) : 0 /*NULL*/; }
	//======================================================================

	//Counting elements=====================================================
	element_count storage_section::count_previous() const
	//Count number of elements before this one
	{
	element_count Count = 0;
	const storage_section *Current = this;
	while ((Current = Current->previous())) Count++;
	return Count;
	}

	element_count storage_section::count_next() const
	//Count number of elements after this one
	{
	element_count Count = 0;
	const storage_section *Current = this;
	while ((Current = Current->next())) Count++;
	return Count;
	}

	element_count storage_section::count_children() const
	//Count number of children
	{ return this->child()? (1 + this->child()->count_next()) : 0; }

	element_count storage_section::count_depth() const
	//Count depth of object
	{ return this->parent()? (1 + this->parent()->count_depth()) : 0; }
	//======================================================================
//==============================================================================

#endif
