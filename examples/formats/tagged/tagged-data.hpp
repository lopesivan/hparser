/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <string>

#include <hparser/linked-section.hpp>

//Class TaggedData--------------------------------------------------------------
//Data element for tagged example
class TaggedData :
	public linked_section
{
public:
	//From 'storage_section'------------------------------------------------
	section_releaser copy() const;
	//----------------------------------------------------------------------

	//From 'input_receiver'-------------------------------------------------
	input_receiver *receive_data(data_input*);
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	const output_sender *send_data(data_output*) const;
	//----------------------------------------------------------------------

private:
	std::string Data;
	//Element data
}; //END------------------------------------------------------------------------
