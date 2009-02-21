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

#ifndef DATA_OUTPUT_HPP
#define DATA_OUTPUT_HPP

#include "impl-defined.hpp"
#include "output-resource.hpp"

/*! \defgroup output_group Output and Exportation
*/

//Function export_data----------------------------------------------------------
//Automatically exports data to an output destination
struct data_output;
struct data_exporter;

	/*! \brief Data exportation request.
	    \ingroup automation_group
	    \ingroup output_group

	    This function exports data from a data_output and sends it to the
	    data_exporter.

	    @see import_data provides complimentary input functionality.

	    @see save_file provides corresponding file export functionality.
	 */

	bool
export_data(const data_exporter*, data_output*);
//Data source, data destination

//Output Destinations~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Struct data_output------------------------------------------------------------
//Abstract output destination

	/*! \class data_output
	    \brief Data output destination.
	    \ingroup system_group
	    \ingroup output_group

	    This class serves as a generic output interface for data being
	    exported from the tree.  This interface receives the output data
	    from various components of the tree.

	    The functions themselves are arbitrary in terms of the library and
	    are provided so that the user has a built-in API to handle data
	    output.

	    \attention This class uses the output_section class which is entirely
	    implementation-defined by the using program.  An optional definition
	    is available for simple text output.
	    input.

	    \attention This class uses the composite_data class which is entirely
	    implementation-defined by the using program.  An optional definition
	    is available for simple text processing.

	    @see data_input provides complimentary input functionality.
	 */

struct data_output :
	virtual public output_resource_owner
{

	/*! \brief Data output request.

	    This function receives the next sequential section of data.
	    Normally this data will be written to a file or sent to an output
	    location as a linear representation of the data in the tree.
	 */

	virtual
		bool
	send_output(const output_section&) = 0;
	//Send the next output section

	/*! \brief Closed output check.

	    This function checks to see if the data destination is closed.
	 */

	virtual
		bool
	is_closed() const = 0;
	//Find out if the destination is closed

	/*! \brief Output mode change request.

	    This function should be used to change the data output mode if more
	    than one mode is needed.  For example, to switch from a text display
	    format to a file export format.
	 */

	virtual
		bool
	set_output_mode(unsigned int);
	//Set the current output mode
	//Non-abstract, but functionless by default

	/*! \brief Output synchronization.

	    This function should force writing or sending of buffered data.
	 */

	virtual
		bool
	synchronize();
	//Force all output to be sent or written
	//Non-abstract, but functionless by default

	virtual inline
	~data_output() {};
}; //END------------------------------------------------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Output Sources~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Struct output_sender----------------------------------------------------------
//Abstract single output sender

	/*! \class output_sender
	    \brief Data output interface.
	    \ingroup interfaces_group
	    \ingroup output_group

	    This class serves as the output interface of tree elements.  This
	    interface is used to export the data contained in the tree in a
	    linear (storable in a file or printable in a console) format.
	    Output objects are implementation defined.

	    @see string-output.hpp is provided to mirror a std::string.
	    @see string-composite.hpp is provided to mirror a std::string.

	    @see input_receiver provides complimentary output functionality.
	 */

struct output_sender
{

	/*! \brief Sequential output request.

	    This function takes a data_output object so that the output_sender can
	    export its data.  The element should base the output format on the
	    output mode.  For example, if the output is to go to a file which
	    will be used by a program later, the element should export parsable
	    data.  If the output is to be displayed, the element should format
	    it for display.

	    The return value is the next output_sender to take control of the
	    data_output.  This function should output all of its own data and
	    pass control of data_output to its subelements in the order the data
	    will be used in the future.  For example, with a tagged format the
	    element will output the open tag, its data, pass control to its
	    first child, and send a close tag after its children have sent their
	    data (this can be managed by tagged_output.)

	    If an element has one following it, it should pass control to that
	    element by returning it after the element is done exporting itself
	    and its children.  If an element doesn't have anything following it,
	    it should return its parent element.
	 */

	virtual
		const output_sender
	*send_data(data_output*) const;
	//Send data, return element to send next output
	//Non-abstract, but functionless by default

	/*! \brief Recursive output request.

	    This function collects data from all of its children and combines it
	    with its own data and inserts it into a composite_data object.  This
	    function can pass a unique composite_data object to its children for
	    them to fill with their data, or it can provide the original
	    composite_data to them with an offset.  This entirely depends on the
	    implementation of composite_data by the using program.

	    This function is intended for formats which contain all section
	    boundary information at the beginning of the section.  For example,
	    number of children, number of bytes, etc.  This function allows
	    elements with those formats to determine how much space it will
	    require before sending its header/descriptor element.

	    The return value should indicate success of the output operation.
	    If this element has sub-elements, this function should contain a
	    loop which checks their returns and aborts if one fails to output
	    its data.
	 */

	virtual
		bool
	collect_data(composite_data&) const;
	//Collect data from elements
	//Non-abstract, but functionless by default

	/*! \brief Output filtering.

	    This function is provided as an arbitrary filtering interface.  This
	    allows a child element to obtain output formatting for its data.
	 */

	virtual
		bool
	output_filter(output_section&) const;
	//Filter output data
	//Non-abstract, but functionless by default

	virtual inline
	~output_sender() {};
}; //END------------------------------------------------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Output Automation~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Struct data_exporter----------------------------------------------------------
//Abstract data set exporter

	/*! \class data_exporter
	    \brief Data exportation manager.
	    \ingroup automation_group
	    \ingroup output_group
	    \ingroup base_group

	    This class is to manage the exportation of an entire set of data.
	    This should serve as a part of the base of a tree and should receive
	    initial control of data_output.  Depending on the implementation, it
	    should pass control of output to its first element using the
	    output_sender functions send_data and collect_data.

	    @see data_importer provides complimentary output functionality.
	 */

struct data_exporter
{

	/*! \brief Data exportation entry point.

	    This will be the initial exportation call at the base of the tree.
	    This function should initiate automatic exportation of the tree.
	 */

	virtual
		const output_sender
	*export_data(data_output*) const = 0;
	//Export data, return element to send next output

	virtual inline
	~data_exporter() {};
}; //END------------------------------------------------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif
