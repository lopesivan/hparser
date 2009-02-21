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

#ifndef DATA_INPUT_HPP
#define DATA_INPUT_HPP

#include "impl-defined.hpp"
#include "input-resource.hpp"

/*! \defgroup input_group Input and Parsing
*/

/*! \defgroup system_group Interfaces for External Systems
*/

//Function import_data----------------------------------------------------------
//Automatically imports data from an input source
struct data_input;
struct data_importer;

	/*! \brief Data importation request.
	    \ingroup automation_group
	    \ingroup input_group

	    This function imports data from a data_input and sends it to the
	    data_importer.

	    @see export_data provides complimentary output functionality.

	    @see load_file provides corresponding file import functionality.
	 */

	bool
import_data(data_importer*, data_input*);
//Data destination, data source

//Input Sources~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Typdef input_count------------------------------------------------------------
//Unit of input measurement
typedef long long input_count; //END--------------------------------------------

//Struct data_input-------------------------------------------------------------
//Abstract input source

	/*! \class data_input
	    \brief Data input source.
	    \ingroup system_group
	    \ingroup input_group

	    This class serves as a generic input interface for data being
	    parsed.  It provides minimal functionality which can be used in
	    various combinations to handle nearly all imaginable formats of
	    information.

	    The functions themselves are arbitrary in terms of the library and
	    are provided so that the user has a built-in API to handle data
	    input.

	    \attention This class uses the input_section class which is entirely
	    implementation-defined by the using program.  An optional definition
	    is available for simple text input.
	    input.

	    \attention This class uses the composite_data class which is entirely
	    implementation-defined by the using program.  An optional definition
	    is available for simple text processing.

	    @see data_output provides complimentary output functionality.
	 */

struct data_input :
	virtual public input_resource_owner
{

	/*! \brief Data input request.

	    This function should return the next section of input data.  The
	    size isn't specified so that text parsers can feed lines, tags,
	    "significant sections" of data, etc.  Data remains in the buffer
	    until advanced by next_input.
	 */

	virtual
		const input_section
	&receive_input() = 0;
	//Obtain the next input section
	//A reference is used because the section should be held until the
	//function below is called

	/*! \brief Buffer advance request.

	    This function advances the buffer to the next section of input.
	    Until this function is called, receive_input should return the same
	    data on every call.  The argument provided is for implementation-
	    defined behavior.
	 */

	virtual
		bool
	next_input(input_count = 0) = 0;
	//Increment the input index

	/*! \brief End of data check.

	    This function should return true if the end of data has been
	    reached or if an input error has occured.  Returning true when an
	    error occurs is important for preventing endless input loops.
	 */

	virtual
		bool
	end_of_data() const = 0;
	//Find out if this is the end of the data

	/*! \brief Literal end of data check.

	    This function checks for the literal end of data, whereas, the
	    end_of_data function returns true even in an underrun situation.  By
	    default, this returns end_of_data.
	 */

	virtual
		bool
	is_terminated() const;
	//Find out if this is the REAL end of the data

	/*! \brief Buffer replacement request.

	    This function replaces the data currently in the buffer.  The
	    argument should be used to indicate how much data from the end of
	    the buffer should be replaced.
	 */

	virtual
		bool
	replace_buffer(input_count = 0);
	//Replace data currently in buffer
	//Non-abstract, but functionless by default

	/*! \brief Input mode change request.

	    This function should be used to change the data input mode if more
	    than one mode is needed.  For example, to switch from a tagged text
	    format to a binary format.
	 */

	virtual
		bool
	set_input_mode(unsigned int);
	//Set the current input mode
	//Non-abstract, but functionless by default

	virtual inline
	~data_input() {};
}; //END------------------------------------------------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Input Destinations~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Struct input_receiver---------------------------------------------------------
//Abstract single input receiver

	/*! \class input_receiver
	    \brief Data input interface.
	    \ingroup interfaces_group
	    \ingroup input_group

	    This class serves as the input interface of tree elements.  The
	    functions provided are for receiving and processing input data for
	    self-assembling trees.  This is the significant base object for
	    input parsing and deals with data pertaining to its own element and
	    any direct sub-elements.  Input objects are implementation defined.

	    @see string-input.hpp is provided to mirror a std::string.
	    @see string-composite.hpp is provided to mirror a std::string.

	    @see output_sender provides complimentary output functionality.
	 */

struct input_receiver
{

	/*! \brief Sequential input request.

	    This function takes a data_input object so that the input_receiver can
	    extract the applicable data.  Normally the data index is right after
	    the element's declaration.  For example, an element denoted by a
	    \<element\> tag might be created by another element, then input
	    control would be passed to it via the receive_data function and the
	    data_input index would be immediately after \<element\>.

	    The return value is the next input_receiver to take control of the
	    data_input.  Normally this should return 'this' until the end of the
	    element's section.  If the element encounters a sub-element, it
	    should create it and add it as a child, advance the index past the
	    data indicator of that sub-element, and return the child element.
	    As this function uses data for itself, it should advance the input
	    index using next_input.

	    Once the element is done (when its data section has ended,) it
	    should return its parent element.  This way when an element passes
	    control to a child element it regains control when the child
	    element's data section ends.  Incidentally, the element should keep
	    track of if it has received all expected data, and if so, return its
	    parent element to allow it to create another child element if
	    needed.
	 */

	virtual
		input_receiver
	*receive_data(data_input*);
	//Receive data, return element to receive next input
	//Non-abstract, but functionless by default

	/*! \brief Recursive input request.

	    This function takes composite data and expands it using a series of
	    recursive function calls.  The provided data should contain all data
	    to be used by the owning element, to include its sub-elements.

	    The beginning of the composite data should be right after the
	    indication that this element should be created (much like the
	    receive_data function.)  It should create sub-elements as needed and
	    pass them their own composite data based on how much they will need.

	    This function is intended for formats which specify the length of a
	    data section up front.  This allows the parser to parse the exact
 	    amount of data needed and pass it to the element.

	    The return value should indicate success of the input operation.
	    If the element can have sub-elements, this function should have a
	    loop that checks for indicators of those elements and creates them
	    when necessary.
	 */

	virtual
		bool
	expand_data(composite_data&);
	//Expand data into elements
	//Non-abstract, but functionless by default

	/*! \brief Input filtering.

	    This function is provided as an arbitrary filtering interface.  This
	    allows the element to pass its context-less data to a parent element
	    for it to add context to it, or to send empty data to its parent to
	    gain awareness of its element's context in general.  This can also
	    be used to format data being logged during input parsing.
	 */

	virtual
		bool
	input_filter(input_section&);
	//Filter input data
	//Non-abstract, but functionless by default

	virtual inline
	~input_receiver() {};
}; //END------------------------------------------------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Input Automation~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Struct data_importer----------------------------------------------------------
//Abstract data set importer

	/*! \class data_importer
	    \brief Data importation manager.
	    \ingroup automation_group
	    \ingroup input_group
	    \ingroup base_group

	    This class is to manage the importation of an entire set of data.
	    This should serve as a part of the base of a tree and should receive
	    initial control of data_input.  Depending on the implementation, it
	    should create the highest element (which should contain all other
	    elements) and should allow the rest of the tree to self assemble
	    using the input_receiver functions receive_data and expand_data.

	    @see data_exporter provides complimentary output functionality.
	 */

struct data_importer
{

	/*! \brief Data importation entry point.

	    This will be the initial parsing call at the base of the tree.  This
	    function should initiate the assembly of the tree.
	 */

	virtual
		input_receiver
	*import_data(data_input*) = 0;
	//Import data, return element to receive next input

	virtual inline
	~data_importer() {};
}; //END------------------------------------------------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif
