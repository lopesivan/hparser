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

#ifndef FILO_SCOPE_CPP
#define FILO_SCOPE_CPP

#include "filo-scope.hpp"

//scope_identifier function bodies==============================================
	scope_identifier &scope_identifier::enter_scope(const scope_layer &sScope)
	{
	this->push_front(sScope);
	return *this;
	}

	scope_identifier &scope_identifier::leave_scope(unsigned int lLayers)
	{
	while (lLayers-- && this->size()) this->pop_front();
	return *this;
	}

	scope_identifier &scope_identifier::globalize_scope(const scope_layer &sScope)
	{
	this->push_back(sScope);
	return *this;
	}

	scope_identifier &scope_identifier::localize_scope(unsigned int lLayers)
	{
	while (lLayers-- && this->size()) this->pop_back();
	return *this;
	}

	scope_identifier &scope_identifier::clear_scope()
	{
	this->clear();
	return *this;
	}

	scope_layer scope_identifier::composite_scope(const char *sSeparate) const
	{
	scope_layer Composite;

	for (int I = this->size() - 1; I > -1; I--)
	 {
	Composite += this->at(I);
	if (I > 0) Composite += sSeparate;
	 }

	return Composite;
	}

	bool scope_identifier::operator == (const scope_layer &sScope) const
	{
	if (!this->size()) return sScope == "";
	return sScope == this->front();
	}

	bool scope_identifier::operator != (const scope_layer &sScope) const
	{
	if (!this->size()) return sScope != "";
	return sScope != this->front();
	}

	scope_identifier &scope_identifier::operator >> (const scope_layer &sScope)
	{ return this->enter_scope(sScope); }

	scope_identifier &scope_identifier::operator << (unsigned int lLayers)
	{ return this->leave_scope(lLayers); }

	scope_identifier &scope_identifier::operator << (const scope_layer &sScope)
	{ return this->globalize_scope(sScope); }

	scope_identifier &scope_identifier::operator >> (unsigned int lLayers)
	{ return this->localize_scope(lLayers); }
//==============================================================================

#endif
