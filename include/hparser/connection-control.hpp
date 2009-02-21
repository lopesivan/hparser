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

#ifndef CONNECTION_CONTROL_HPP
#define CONNECTION_CONTROL_HPP

//Struct connection_control-----------------------------------------------------
//Controls connection of elements
struct storage_section;

	/*! \class connection_control
	    \brief Element connection control interface.
	    \ingroup interfaces_group

	    This class provides connection control functions to authorize two
	    elements to connect, to connect them, and to disconnect them.  These
	    functions are intended to be called internally by the tree when it
	    is modified to gain approval from and notify a parallel interface.
	 */

struct connection_control
{

    /** @name Connection Functions
     *  Functions to connect or disconnect
     */
    //@{
	/*! \brief Connect the parallel interface.

	    This function should be implemented in a final element class so that
	    it connects/reconnects a parallel interface such as a GUI.
	 */

	virtual
		bool
	connect() = 0;
	//Connect this element

	/*! \brief Disconnect the parallel interface.

	    This function should be implemented in a final element class so that
	    it disconnects a parallel interface such as a GUI.
	 */

	virtual
		bool
	disconnect() = 0;
	//Disconnect this element
    //@}

    /** @name Permission Functions
     *  Functions to gain permission to connect
     */
    //@{
	/*! \brief Authorize an element to be added directly after.

	    This function requests authorization to connect an element directly
	    following this object.  This function should check that it makes
	    sense to put the element after this object at most.  Structural
	    checks beyond that are handled by the library.
	 */

	virtual
		bool
	allow_next(const storage_section*) const = 0;
	//Check allowance of element as next

	/*! \brief Authorize an element to be added below.

	    This function requests authorization to connect an element directly
	    below this object.  This function should check that it makes sense
	    to put the element underneath this object at most.  Structural
	    checks beyond that are handled by the library.
	 */

	virtual
		bool
	allow_child(const storage_section*) const = 0;
	//Check allowance of element as child

	/*! \brief Authorize a replacement element.

	    This function requests authorization to connect an element directly
	    below this object.  This function should check that it makes sense
	    to put the element in place of this object at most.  Structural
	    checks beyond that are handled by the library.
	 */

	virtual
		bool
	allow_here(const storage_section*) const = 0;
	//Check allowance of element here
    //@}

	virtual inline
	~connection_control() {};
}; //END------------------------------------------------------------------------

#endif
