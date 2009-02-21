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

#ifndef TAG_PROPERTIES_HPP
#define TAG_PROPERTIES_HPP

#include <string>
#include <map>

//Typedef general_data----------------------------------------------------------
//General text data
typedef std::string general_data; //END-----------------------------------------

//Typedef property_data---------------------------------------------------------
//General raw tag property data
typedef general_data property_data; //END---------------------------------------

//Typedef property_value--------------------------------------------------------
//Value of a given tag property
typedef general_data property_value; //END--------------------------------------

//Typedef data_tag--------------------------------------------------------------
//Name of a data tag or property
typedef general_data data_tag; //END--------------------------------------------

//Typedef property_list---------------------------------------------------------
//A list of properties and their values
typedef std::map <data_tag, property_value> property_list; //END----------------

//Tag Functions=================================================================
//Function remove_extra---------------------------------------------------------
//Removes leading and trailing whitespace
	void
remove_extra(general_data&);
//Data to process

//Function construct_open-------------------------------------------------------
//Create an open tag from a tag name
	void
construct_open(const data_tag&, data_tag&);
//Name of tag type, tag variable

//Function construct_partial_open-----------------------------------------------
//Create a partial open tag from a tag name
	void
construct_partial_open(const data_tag&, data_tag&);
//Name of tag type, tag variable

//Function construct_close------------------------------------------------------
//Create a close tag from a tag name
	void
construct_close(const data_tag&, data_tag&);
//Name of tag type, tag variable

//Function construct_partial_close----------------------------------------------
//Create a partial close tag from a tag name
	void
construct_partial_close(const data_tag&, data_tag&);
//Name of tag type, tag variable

//Function extract_tag_type-----------------------------------------------------
//Create a close tag from a tag type
	bool
extract_tag_type(const data_tag&, data_tag&);
//Complete tag, tag variable

//Function extract_properties---------------------------------------------------
//Extract tag properties embedded in the tag
	void
extract_properties(const data_tag&, property_list&);
//Complete tag, property list to insert properties into

//Function insert_properties----------------------------------------------------
//Embed tag properties into the tag
	bool
insert_properties(data_tag&, const property_list&);
//Basic tag (nothing embedded), list of properties to insert

//Function insert_set_properties------------------------------------------------
//Embed tag properties with set values into the tag
	bool
insert_set_properties(data_tag&, const property_list&);
//Basic tag (nothing embedded), list of properties to insert

//Function get_property_value---------------------------------------------------
//Determine the value of a given property
	bool
get_property_value(const property_list&, const data_tag&, property_value&);
//List of properties, property name, property variable

//Function set_property_value---------------------------------------------------
//Set the value of a given property
	bool
set_property_value(property_list&, const data_tag&, const property_value&);
//List of properties, property name, property value

//Function set_property---------------------------------------------------------
//Set a given property
	bool
set_property(property_list&, const data_tag&);
//List of properties, property name

//Function is_property_set------------------------------------------------------
//Check if a property is set
	bool
is_property_set(const property_list&, const data_tag&);
//List of properties, property name

//Function remove_property------------------------------------------------------
//Remove a property from a list
	bool
remove_property(property_list&, const data_tag&);
//List of properties, property name

//Function is_partial_tag-------------------------------------------------------
//Determines if a tag is incomplete
	bool
is_partial_tag(const property_data&);
//Data to test

//Function is_whole_tag---------------------------------------------------------
//Determines if a tag is complete
	bool
is_whole_tag(const property_data&);
//Data to test

//Function is_open_tag----------------------------------------------------------
//Determines if a tag is an open tag
	bool
is_open_tag(const property_data&);
//Data to test

//Function is_close_tag---------------------------------------------------------
//Determines if a tag is a close tag
	bool
is_close_tag(const property_data&);
//Data to test

//Function tag_compare----------------------------------------------------------
//Determines if two tags match
	bool
tag_compare(const property_data&, const property_data&);
//Data to test, basic tag (nothing embedded)

//Function tag_compare_open-----------------------------------------------------
//Determines if a tag is an open tag and matches a type
	bool
tag_compare_open(const property_data&, const data_tag&);
//Data to test, tag type

//Function tag_compare_close----------------------------------------------------
//Determines if a tag is a close tag and matches a type
	bool
tag_compare_close(const property_data&, const data_tag&);
//Data to test, tag type

//Function tag_compare_pair-----------------------------------------------------
//Determines if two tags make an open/close pair
	bool
tag_compare_pair(const property_data&, const property_data&);
//Potential open tag, potential close tag

//Function ExtractNext----------------------------------------------------------
//Extracts next tag or non-tag from set of data
	bool
extract_next(general_data&, general_data&);
//Input data, output variable
//==============================================================================

#endif
