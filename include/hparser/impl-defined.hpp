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

#ifndef IMPL_DEFINED_HPP
#define IMPL_DEFINED_HPP

/*! \defgroup implementation_group Optional Class Definitions
  @see concept_group provides an explanation of the implementation-defined
  concept.
*/

/*! \defgroup concept_group Implementation-defined Classes
  'hparser' uses the following class declarations to allow object interfaces
  to provide the lib user with channels of communication.  While the library
  doesn't provide functionality for these classes, their mere declarations and
  use as virtual function arguments in lib classes allows the lib user to
  define how to pass information between lib objects.
*/

//Class input_section-----------------------------------------------------------
//Data input type (implementation defined)

	/*! \class __input_section__
	    \brief Input data type (user-defined.)
	    \ingroup concept_group

	    This class provides an interface slot for data to be input and
	    parsed by components of the library.

	    \attention To define this class, remove the __ from before and
	    after.  They are added for the purposes of differentiation between
	    the class concept and the definition(s) provided by the library
	    for optional use.

	    @see classes/string-input.hpp provides a simple definition.
	 */

class input_section; //END------------------------------------------------------

//Class output_section----------------------------------------------------------
//Data output type (implementation defined)

	/*! \class __output_section__
	    \brief Output data type (user-defined.)
	    \ingroup concept_group

	    This class provides an interface slot for data to be output by
	    components of the library.

	    \attention To define this class, remove the __ from before and
	    after.  They are added for the purposes of differentiation between
	    the class concept and the definition(s) provided by the library
	    for optional use.

	    @see classes/string-output.hpp provides a simple definition.
	 */

class output_section; //END-----------------------------------------------------

//Class composite_data----------------------------------------------------------
//Composite data type (implementation defined)

	/*! \class __composite_data__
	    \brief Composite input/output data type (user-defined.)
	    \ingroup concept_group

	    This class provides an interface slot for data to be expanded and
	    combined by components of this library.

	    \attention To define this class, remove the __ from before and
	    after.  They are added for the purposes of differentiation between
	    the class concept and the definition(s) provided by the library
	    for optional use.

	    @see classes/string-composite.hpp provides a simple definition.
	 */

class composite_data; //END-----------------------------------------------------

//Class comm_message------------------------------------------------------------
//Message transmitted between objects (implementation defined)

	/*! \class __comm_message__
	    \brief Message data type (user-defined.)
	    \ingroup concept_group

	    This class provides an interface slot for messages to be passed
	    between components of this library.

	    \attention To define this class, remove the __ from before and
	    after.  They are added for the purposes of differentiation between
	    the class concept and the definition(s) provided by the library
	    for optional use.

	    @see classes/string-message.hpp provides a simple definition.
	 */

class comm_message; //END-------------------------------------------------------

//Class scope_identifier--------------------------------------------------------
//Identifies the location of a scope (implementation defined)

	/*! \class __scope_identifier__
	    \brief Hierarchy scope type (user-defined.)
	    \ingroup concept_group

	    This class provides an interface slot for passing scope identifiers
	    between components of this library.

	    \attention To define this class, remove the __ from before and
	    after.  They are added for the purposes of differentiation between
	    the class concept and the definition(s) provided by the library
	    for optional use.

	    @see classes/filo-scope.hpp provides a simple definition.
	 */

class scope_identifier; //END---------------------------------------------------

//Class element_interface-------------------------------------------------------
//The interface parameter of an element (implementation defined)

	/*! \class __element_interface__
	    \brief Parallel interface type (user-defined.)
	    \ingroup concept_group

	    This class provides an interface slot for components of this library
	    to access a parallel structural interface such as a GUI.

	    \attention To define this class, remove the __ from before and
	    after.  They are added for the purposes of differentiation between
	    the class concept and the definition(s) provided by the library
	    for optional use.
	 */

class element_interface; //END--------------------------------------------------

#endif
