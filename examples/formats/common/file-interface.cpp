/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "file-interface.hpp"

#include <hparser/classes/string-output.hpp>
#include <hparser/formats/tag-properties.hpp>

//FileInterface function bodies=================================================
	FileInterface::FileInterface() : InputMode(Other), input_resourceIndex(0)
	{}

	//From 'data_input'-----------------------------------------------------
	const input_section &FileInterface::receive_input()
	{
	//if the current buffer has data, return it again
	if (CurrentData.size()) return CurrentData;

	if (!this->is_open()) return CurrentData;
	file_stream.clear();

	if (InputMode == Tagged)
	//Tagged data input mode________________________________________________
	{
	//This input mode reads single lines at a time and splits the line into
	//valid tags (e.g. "<tag>") and data other than tags.

	if (!LoadedData.size())
	while (!LoadedData.size() && !this->end_of_data())
	//read until a non-blank line is read
	 {
	LoadedData.resize(1024);
	file_stream.getline(&LoadedData[0], LoadedData.size());
	LoadedData.resize(strlen(&LoadedData[0]));
	remove_extra(CurrentData);
	 }

	//extract the next tag or non-tag and return it
	return CurrentData = extract_next(LoadedData);
	}
	//______________________________________________________________________

	else
	//Other format input mode_______________________________________________
	{
	//this input mode reads single lines, removes leading and trailing
	//whitespace, and returns the entire line

	while (!CurrentData.size() && !this->end_of_data())
	 {
	CurrentData.resize(1024);
	file_stream.getline(&CurrentData[0], CurrentData.size());
	CurrentData.resize(strlen(&CurrentData[0]));
	remove_extra(CurrentData);
	 }

	return CurrentData;
	}
	//______________________________________________________________________
	}


	bool FileInterface::next_input(input_count cCount)
	{
	//This function clears the entire 'current' buffer if the argument is 0,
	//otherwise it only clears the number of characters used.  If the buffer
	//becomes empty, the next 'receive_input' function call will fill the
	//buffer with new data.

	if (!this->is_open()) return false;

	//don't allow more than the buffer contains
	if (cCount > CurrentData.size()) return false;

	if (!cCount) CurrentData = "";
	else         CurrentData.erase(0, cCount);

	return true;
	}


	bool FileInterface::replace_buffer(input_count cCount)
	{
	//this function moves the read counter back to replace data currently in
	//the buffer

	if (!this->is_open()) return false;

	//check for the new read position
	if (!cCount) cCount = CurrentData.size();
	int New = this->read_position() - cCount;
	if (New < 0) return false;

	//set the new read position
	if (!this->set_read_position(New)) return false;

	//clear the buffer so that the next 'receive_input' call forces a new
	//read operation
	if (!this->next_input(0)) return false;

	return true;
	}


	bool FileInterface::set_input_mode(unsigned int mMode)
	{
	//this function allows switching between 'tagged' and 'other' modes

	if (mMode == Tagged)     InputMode = Tagged;
	else if (mMode == Other) InputMode = Other;
	else                     return false;

	return true;
	}
	//----------------------------------------------------------------------

	//From 'data_output'----------------------------------------------------
	bool FileInterface::send_output(const output_section &oOutput)
	{
	//simple text data output function

	if (!this->is_open()) return false;

	file_stream << oOutput;
	file_stream.flush();

	return file_stream;
	}
	//----------------------------------------------------------------------

	//From 'input_resource'-------------------------------------------------
	const input_section &FileInterface::get_input(input_resource_count sStart,
	input_resource_count sSize)
	{
	bool WasOpen = false;

	if (!this->is_open())
	 {
	if (!this->open_file(true, false)) return ResourceData = "";
	WasOpen = true;
	 }

	ResourceData.resize(sSize);
	input_count Current = this->read_position();

	if (!this->set_read_position(sStart + input_resourceIndex)) ResourceData = "";
	else file_stream.read(&ResourceData[0], sSize);

	if (!this->set_read_position(Current))/* ResourceData = ""*/;

	if (WasOpen && !this->close_file())/* return ResourceData = ""*/;

	return ResourceData;
	}

	bool FileInterface::set_input_index(input_resource_count iIndex)
	{
	if (iIndex) input_resourceIndex = iIndex;
	else        input_resourceIndex = this->read_position();
	return true;
	}
	//----------------------------------------------------------------------

	//From 'input_resource_owner'-------------------------------------------
	input_resource *FileInterface::get_input_resource()
	{ return this; }
	//----------------------------------------------------------------------
//==============================================================================
