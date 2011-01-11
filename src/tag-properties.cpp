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

#ifndef TAG_PROPERTIES_CPP
#define TAG_PROPERTIES_CPP

#include "tag-properties.hpp"
#include "tag-constants.hpp"
#include <string.h>


//Internal Data=================================================================
static const std::string TStart(tag_start);
static const std::string TStop(tag_stop);
static const std::string TEnd(tag_name_end);
static const std::string CloseMod(close_modifier);
static const std::string PropSep(property_separator);
static const std::string PropAssn(property_assign);
//==============================================================================

//Internal Functions============================================================
static void remove_separators(property_data &iInput)
{
	//This removes excess separators from the ends of a string (e.g. ";")

	if (!iInput.size()) return;

	remove_extra(iInput);
	bool RemFirst, RemLast;
	int First, Last;

	do
	{
	if (iInput.size() >= 1)
	 {
	First = iInput.find(PropSep);

	if ((RemFirst = (First == 0)))
	iInput.erase(iInput.begin(), iInput.begin() + PropSep.size());
	 }
	else RemFirst = false;

	if (iInput.size() >= PropSep.size())
	 {
	Last = iInput.rfind(PropSep);

	if ((RemLast = (Last + PropSep.size() == iInput.size())))
	iInput.erase(iInput.begin() + Last, iInput.end());
	 }
	else RemLast = false;

	remove_extra(iInput);
	}
	while (RemFirst || RemLast);
}

static bool raw_properties(const data_tag &iInput, property_data &pProps)
{
	//This extracts properties embedded in a tag (e.g. '<a href="#1">' ->
	//'href="#1"')

	if (!is_whole_tag(iInput)) return false;

	pProps = iInput;
	remove_extra(pProps);

	int Start = pProps.find(TEnd);
	int End   = pProps.size() - TStop.size();

	if (End > Start && Start >= 0)
	{
	pProps.erase(pProps.begin() + End, pProps.end());

	pProps.erase( pProps.begin(), pProps.begin() + Start +
	                                TEnd.size() );

	return true;
	}

	return false;
}
//==============================================================================

//Tag Functions=================================================================
//Function remove_extra---------------------------------------------------------
//Removes leading and trailing whitespace
void remove_extra(general_data &iInput)
{
	if (!iInput.size()) return;

	iInput.resize(strlen(&iInput[0]));

	while ( iInput.size() && (iInput[0] == ' ' || iInput[0] == '\t' ||
	          iInput[0] == '\n' || iInput[0] == '\r') )
	iInput.erase(0, 1);

	while ( iInput.size() && (iInput[iInput.size() - 1] == ' ' ||
	          iInput[iInput.size() - 1] == '\t' ||
	          iInput[iInput.size() - 1] == '\n' ||
	          iInput[iInput.size() - 1] == '\r') )
	iInput.erase(iInput.size() - 1, 1);
} //END-------------------------------------------------------------------------

//Function construct_open-------------------------------------------------------
//Create an open tag from a tag name
void construct_open(const data_tag &tTag, data_tag &vValue)
{
	vValue = TStart;
	vValue += tTag;
	vValue += TStop;
}
//END---------------------------------------------------------------------------

//Function construct_partial_open-----------------------------------------------
//Create a partial open tag from a tag name
void construct_partial_open(const data_tag &tTag, data_tag &vValue)
{
	vValue = TStart;
	vValue += tTag;
}
//END---------------------------------------------------------------------------

//Function construct_close------------------------------------------------------
//Create a close tag from a tag name
void construct_close(const data_tag &tTag, data_tag &vValue)
{
	vValue = TStart;
	vValue += CloseMod;
	vValue += tTag;
	vValue += TStop;
}
//END---------------------------------------------------------------------------

//Function construct_partial_close----------------------------------------------
//Create a partial close tag from a tag name
void construct_partial_close(const data_tag &tTag, data_tag &vValue)
{
	vValue = TStart;
	vValue += CloseMod;
	vValue += tTag;
}
//END---------------------------------------------------------------------------

//Function extract_tag_type-----------------------------------------------------
//Create a close tag from a tag type
bool extract_tag_type(const data_tag &tTag, data_tag &vValue)
{
	if (!is_whole_tag(tTag)) return false;

	int Start   = tTag.find(TStart);
	int NameEnd = tTag.find(TEnd);
	int End     = tTag.find(TStop);

	if (NameEnd >= 0 && NameEnd < End) End = NameEnd;

	if (End <= Start) return false;

	vValue.insert(vValue.size(), tTag, Start + 1, End - Start - 1);
	return true;
}
//END---------------------------------------------------------------------------

//Function extract_properties---------------------------------------------------
//Extract tag properties embedded in the tag
void extract_properties(const data_tag &iInput, property_list &pProps)
{
	//This takes a tag and parses its properties (e.g. '<tag one=1;two=2>'
	//-> {one,1} {two,2})

	if (!iInput.size()) return;

	//Copy, remove extra whitespace and separators, then copy again
	property_data Working;
	if (!raw_properties(iInput, Working)) return;
	remove_separators(Working);
	property_data Search = Working;

	bool Quote = false;

	//The loop below processes a parallel string to ignore separators and
	//assignments contained within quotations

	for (unsigned int I = 0; I < Search.size(); I++)
	{
	if (Search[I] == quote_character) Quote = !Quote;
	else if (Quote)
	 {
	if (Search[I] == PropSep[0]) Search[I] = safe_character;
	else if (Search[I] == PropAssn[0]) Search[I] = safe_character;
	 }
	}

	//The loop below pulls properties from the front of the string one at a
	//time and loads them into the list

	int Next = -1;

	while (Working.size())
	{
	remove_separators(Working);
	remove_separators(Search);
	property_data WorkingTemp = Working, SearchTemp = Search;
	if (Next < 0) Next = Search.find(TEnd);
	else          Next = Search.find(PropSep);

	if (Next < 0)
	//Last property...
	 {
	Working = "";
	Search = "";
	 }

	else
	//...not the last property
	 {
	WorkingTemp.erase(WorkingTemp.begin() + Next, WorkingTemp.end());
	SearchTemp.erase(SearchTemp.begin() + Next, SearchTemp.end());

	Working.erase( Working.begin(), Working.begin() + Next +
	                                  PropSep.size() );

	Search.erase( Search.begin(), Search.begin() + Next +
	                                PropSep.size() );
	 }

	//Find the assignment operator
	int Assign = SearchTemp.find(PropAssn);

	//No value...
	if (Assign < 0) pProps[WorkingTemp] = "";

	else
	//...yes value
	 {
	property_data PropName = WorkingTemp, PropValue = WorkingTemp;
	PropName.erase(PropName.begin() + Assign, PropName.end());

	PropValue.erase( PropValue.begin(), PropValue.begin() + Assign +
	                                      PropSep.size() );

	remove_extra(PropName);
	remove_extra(PropValue);

	pProps[PropName] = PropValue;
	 }
	}
} //END-------------------------------------------------------------------------

//Function insert_properties_common---------------------------------------------
//Embed tag properties into the tag
static bool insert_properties_common(data_tag &oOutput,
const property_list &pProps, bool sSet)
{
	if (!is_whole_tag(oOutput)) return false;
	if (!pProps.size())       return false;

	oOutput = oOutput;

	int Close = oOutput.size() - oOutput.find(TStop);

	oOutput.insert(oOutput.size() - Close, TEnd);

	//The loop below inserts the properties into a tag in order

	property_list::const_iterator Current = pProps.begin(),
	                             End     = pProps.end();

	while (true)
	{
	if (!sSet || Current->second.size())
	 {
	if (Current->first.size())
	oOutput.insert(oOutput.size() - Close, Current->first);

	if (Current->second.size())
	  {
	oOutput.insert(oOutput.size() - Close, PropAssn);
	oOutput.insert(oOutput.size() - Close, Current->second);
	  }
	 }

	if (++Current == End) break;

	if (!sSet || Current->second.size())
	oOutput.insert(oOutput.size() - Close, PropSep);
	}

	return true;
} //END-------------------------------------------------------------------------

//Function insert_properties----------------------------------------------------
//Embed tag properties into the tag
bool insert_properties(data_tag &oOutput, const property_list &pProps)
{ return insert_properties_common(oOutput, pProps, false); }
//END---------------------------------------------------------------------------

//Function insert_set_properties------------------------------------------------
//Embed tag properties with set values into the tag
bool insert_set_properties(data_tag &oOutput, const property_list &pProps)
{ return insert_properties_common(oOutput, pProps, true); }
//END---------------------------------------------------------------------------

//Function get_property_value---------------------------------------------------
//Determine the value of a given property
bool get_property_value(const property_list &pProps, const data_tag &nName,
property_value &vValue)
{
	property_list::const_iterator Location = pProps.find(nName);
	if (Location == pProps.end()) return false;
	vValue = Location->second;
	return true;
}
//END---------------------------------------------------------------------------

//Function set_property_value---------------------------------------------------
//Set the value of a given property
bool set_property_value(property_list &pProps, const data_tag &nName,
const property_value &vValue)
{
	pProps[nName] = vValue;
	return true;
} //END-------------------------------------------------------------------------

//Function set_property---------------------------------------------------------
//Set a given property
bool set_property(property_list &pProps, const data_tag &nName)
{
	pProps[nName] = "";
	return true;
} //END-------------------------------------------------------------------------

//Function is_property_set------------------------------------------------------
//Check if a property is set
bool is_property_set(const property_list &pProps, const data_tag &nName)
{ return pProps.find(nName) != pProps.end(); } //END----------------------------

//Function remove_property------------------------------------------------------
//Remove a property from a list
bool
remove_property(property_list &pProps, const data_tag &nName)
{
	pProps.erase(nName);
	return true;
} //END-------------------------------------------------------------------------

//Function is_partial_tag-------------------------------------------------------
//Determines if a tag is incomplete
bool is_partial_tag(const property_data &iInput)
{
	property_data Working = iInput;
	remove_extra(Working);

	int Open  = Working.find(TStart);
	int Close = Working.rfind(TStop);

	if (Open < 0 && Close < 0) return false;
	if (Open == 0 && Close + TStop.size() == Working.size()) return false;
	return true;
} //END-------------------------------------------------------------------------

//Function is_whole_tag---------------------------------------------------------
//Determines if a tag is complete
bool is_whole_tag(const property_data &iInput)
{
	int Open  = iInput.find(TStart);
	int Open2 = iInput.rfind(TStart);
	int Close = iInput.rfind(TStop);

	return Open == 0 && Close + TStop.size() == iInput.size() &&
	       Open == Open2;
} //END-------------------------------------------------------------------------

//Function is_open_tag----------------------------------------------------------
//Determines if a tag is an open tag
bool is_open_tag(const property_data &iInput)
{ return is_whole_tag(iInput) && !is_close_tag(iInput); } //END-----------------

//Function is_close_tag---------------------------------------------------------
//Determines if a tag is a close tag
bool is_close_tag(const property_data &iInput)
{
	if (!is_whole_tag(iInput)) return false;

	int Close = iInput.find(CloseMod);

	return Close == (signed int) TStart.size();
} //END-------------------------------------------------------------------------

//Function tag_compare----------------------------------------------------------
//Determines if two tags match
bool tag_compare(const property_data &iInput, const property_data &tTag)
{
	if (!is_whole_tag(iInput)) return false;
	if (!is_whole_tag(tTag))   return false;

	int Separator1 = iInput.find(PropSep);
	if (Separator1 < 0) Separator1 = iInput.size() - TStop.size();

	int Separator2 = tTag.find(PropSep);
	if (Separator2 < 0) Separator2 = tTag.size() - TStop.size();

	return iInput.compare(0, Separator1, tTag, 0, Separator2) == 0;
} //END-------------------------------------------------------------------------

//Function tag_compare_open-----------------------------------------------------
//Determines if a tag is an open tag and matches a type
bool tag_compare_open(const property_data &iInput, const data_tag &tType)
{
	if (!is_whole_tag(iInput))                      return false;
	if (is_whole_tag(tType) || is_partial_tag(tType)) return false;

	if (iInput.find(tType) != TStart.size()) return false;

	int Separator = iInput.find(PropSep);
	if (Separator < 0) Separator = iInput.size() - TStop.size();

	return Separator == (signed) (TStart.size() + tType.size());
} //END-------------------------------------------------------------------------

//Function tag_compare_close----------------------------------------------------
//Determines if a tag is a close tag and matches a type
bool tag_compare_close(const property_data &iInput, const data_tag &tType)
{
	if (!is_whole_tag(iInput))                      return false;
	if (is_whole_tag(tType) || is_partial_tag(tType)) return false;

	if (iInput.find(CloseMod) != TStart.size()) return false;
	if (iInput.find(tType) != TStart.size() + CloseMod.size())
	return false;

	int Separator = iInput.find(PropSep);
	if (Separator < 0) Separator = iInput.size() - TStop.size();

	return Separator == (signed) (TStart.size() + CloseMod.size() +
	  tType.size());
} //END-------------------------------------------------------------------------

//Function tag_compare_pair-----------------------------------------------------
//Determines if two tags make an open/close pair
bool tag_compare_pair(const property_data &oOpen, const property_data &cClose)
{
	if (!is_whole_tag(oOpen))  return false;
	if (!is_whole_tag(cClose)) return false;

	if (oOpen.find(CloseMod) >= 0) return false;
	int Separator1 = oOpen.find(PropSep);
	if (Separator1 < 0) Separator1 = oOpen.size() - TStop.size();

	if (cClose.find(CloseMod) != TStart.size()) return false;
	int Separator2 = cClose.find(PropSep);
	if (Separator2 < 0) Separator2 = cClose.size() - TStop.size();

	return oOpen.compare(TStart.size(), Separator1, cClose,
	  TStart.size() + CloseMod.size(), Separator2);
} //END-------------------------------------------------------------------------

//Function ExtractNext----------------------------------------------------------
//Extracts next tag or non-tag from set of data
bool extract_next(general_data &iInput, general_data &oOutput)
{
	remove_extra(iInput);
	oOutput = iInput;

	//Find where the next tag starts or stops
	int Open  = oOutput.find(TStart);
	int Close = oOutput.find(TStop);
	int Newline = oOutput.find("\n");

	if ((Open < 0 || Close < 0) && Newline < 0) iInput = "";

	else if (Open == 0)
	{
	if (Newline >= 0 && Newline < Close)
	 {
	iInput.erase(iInput.begin(), iInput.begin() + Newline + 1);
	oOutput.erase(oOutput.begin() + Newline, oOutput.end());
	 }

	else
	 {
	iInput.erase(iInput.begin(), iInput.begin() + Close + TStop.size());
	oOutput.erase(oOutput.begin() + Close + TStop.size(), oOutput.end());
	 }
	}

	else
	{
	if (Newline >= 0 && (Newline < Open || Open < 0))
	 {
	iInput.erase(iInput.begin(), iInput.begin() + Newline + 1);
	oOutput.erase(oOutput.begin() + Newline, oOutput.end());
	 }

	else
	 {
	iInput.erase(iInput.begin(), iInput.begin() + Open);
	oOutput.erase(oOutput.begin() + Open, oOutput.end());
	 }
	}

	remove_extra(oOutput);
	remove_extra(iInput);
	return true;
}
//END---------------------------------------------------------------------------
//==============================================================================

#endif
