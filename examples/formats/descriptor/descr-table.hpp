/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <hparser/formats/descriptor-storage.hpp>

#include "section-filter.hpp"
#include "descr.hpp"

//Class DescrTable--------------------------------------------------------------
//Table element for first descriptor example
class DescrTable :
	public SectionFilter,
	public descriptor_storage
{
public:
	DescrTable(const Descr&);

	//From 'storage_section'------------------------------------------------
	section_releaser copy() const;
	//----------------------------------------------------------------------

	//From 'triggered_update'-----------------------------------------------
	bool local_update();
	//----------------------------------------------------------------------

private:
	//From 'descriptor_input'-----------------------------------------------
	bool section_complete(data_input*) const;
	bool makes_sense(data_input*) const;
	bool is_subsection(data_input*) const;
	input_receiver *new_subsection(data_input*);
	input_receiver *apply_input(data_input*);
	input_receiver *get_in_parent() const;
	//----------------------------------------------------------------------

	//From 'descriptor_output'----------------------------------------------
	bool send_descriptor(data_output*) const;
	bool send_content(data_output*) const;
	const output_sender *get_subsection() const;
	const output_sender *get_next() const;
	const output_sender *get_out_parent() const;
	//----------------------------------------------------------------------

	Descr SectionDescriptor;
	//element descriptor
}; //END------------------------------------------------------------------------
