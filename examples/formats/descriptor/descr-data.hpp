/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <hparser/linked-section.hpp>

#include "descr.hpp"

//Class DescrData---------------------------------------------------------------
//Data element for first descriptor example
class DescrData :
	public linked_section
{
public:
	DescrData(const Descr&);

	//From 'storage_section'------------------------------------------------
	section_releaser copy() const;
	//----------------------------------------------------------------------

	//From 'input_receiver'-------------------------------------------------
	input_receiver *receive_data(data_input*);
	//----------------------------------------------------------------------

	//From 'output_sender'--------------------------------------------------
	const output_sender *send_data(data_output*) const;
	//----------------------------------------------------------------------

	//From 'triggered_update'-----------------------------------------------
	bool local_update();
	//----------------------------------------------------------------------

private:
	Descr SectionDescriptor;
	//element descriptor

	std::string Data;
	//Element data
}; //END------------------------------------------------------------------------
