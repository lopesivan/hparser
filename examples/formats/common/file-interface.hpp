/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

//The 'FileInterface' class manages all file input and output for the examples.
//This reads files in text mode, generally a line at a time.

#include <hparser/input-resource.hpp>
#include <hparser/aux/generic-file.hpp>
#include <hparser/classes/string-input.hpp>

#include "modes.hpp"

//Class FileInterface-----------------------------------------------------------
class FileInterface :
	public text_file,
	public input_resource
{
public:
	FileInterface();

	//From 'data_input'-----------------------------------------------------
	const input_section &receive_input();
	bool next_input(input_count);
	bool replace_buffer(input_count);
	bool set_input_mode(unsigned int);
	//----------------------------------------------------------------------

	//From 'data_output'----------------------------------------------------
	bool send_output(const output_section&);
	//----------------------------------------------------------------------

	//From 'input_resource'-------------------------------------------------
	const input_section &get_input(input_resource_count, input_resource_count);
	bool set_input_index(input_resource_count);
	//----------------------------------------------------------------------

	//From 'input_resource_owner'-------------------------------------------
	input_resource *get_input_resource();
	//----------------------------------------------------------------------

private:
	input_section CurrentData, LoadedData, ResourceData;
	//Current data, loaded data

	DataMode InputMode;
	//Input parsing mode (see 'modes.hpp')

	input_resource_count input_resourceIndex;
	//Starting point of resource
}; //END------------------------------------------------------------------------
