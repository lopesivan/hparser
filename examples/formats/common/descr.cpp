/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "descr.hpp"

#include <iostream>
#include <sstream>

#include <hparser/classes/string-input.hpp>
#include <hparser/classes/string-output.hpp>

//Descr function bodies=========================================================
	Descr::Descr() : Title(), Size(0), Table(false), Valid(false) {}

	//Descriptor interpretation---------------------------------------------
	unsigned int Descr::TakeDescriptor(const input_section &iInput)
	{
	//reset everything
	Title = "";
	Size  = 0;
	Table = false;
	Valid = false;

	if (!iInput.size()) return 0;

	//find the start and end of the descriptor
	unsigned int Start = iInput.find("[");
	unsigned int End   = iInput.find("]");

	//check for an invalid descriptor
	if (Start != 0 || Start >= End || End < 0) return 0;

	//working data starts as a copy of the descriptor
	input_section Working = iInput.substr(1, End);

	//find the first separator
	unsigned int Separate = Working.find("/");

	//check for an invalid length of the first component ('T' or 'D')
	if (Separate != 1 || Working.size() < 1) return 0;

	//use temporaries for size and table in case of failure
	int  TempSize;
	bool TempTable;

	//check for descriptor type (table or data)
	if (Working[0] == 'D')      TempTable = false;
	else if (Working[0] == 'T') TempTable = true;
	else                        return 0;

	//remove descriptor type
	Working.erase(Working.begin(), Working.begin() + Separate + 1);

	//find the second separator
	Separate = Working.find("/");

	//check the position
	if (Separate < 1 || Working.size() < 1) return 0;

	//copy the size text
	input_section Temp = Working.substr(0, Separate);
	std::istringstream TempStream(Temp);

	//parse the size text
	TempStream >> TempSize;

	//check for a stream error or negative size
	if (!TempStream || TempSize < 0) return 0;

	//remove the size and the final delimiter
	Working.erase(Working.begin(), Working.begin() + Separate + 1);
	Working.erase(Working.end() - 1, Working.end());

	//copy everything
	Title = Working;
	Size  = TempSize;
	Table = TempTable;
	Valid = true;

	return End + 1;
	}


	output_section Descr::send_descriptor() const
	{
	//this function just reconstructs the descriptor and returns it

	std::ostringstream Working;

	Working << "[";
	Working << (Table? "T" : "D");
	Working << "/";
	Working << Size;
	Working << "/";
	Working << Title;
	Working << "]";

	if (!Working) return "";

	return Working.rdbuf()? Working.rdbuf()->str() : "";
	}
	//----------------------------------------------------------------------

	//Section title---------------------------------------------------------
	const std::string &Descr::GetTitle() const
	{ return Title; }

	void Descr::SetTitle(const std::string &tTitle)
	{ Title = tTitle; }
	//----------------------------------------------------------------------

	//Section size----------------------------------------------------------
	unsigned int Descr::GetSize() const
	{ return Size; }

	void Descr::SetSize(unsigned int sSize)
	{ Size = sSize; }
	//----------------------------------------------------------------------

	//Section type----------------------------------------------------------
	bool Descr::IsTable() const
	{ return Table; }

	void Descr::SetIsTable(bool tTable)
	{ Table = tTable; }
	//----------------------------------------------------------------------

	//Validity--------------------------------------------------------------
	bool Descr::IsValid() const
	{ return Valid; }
	//----------------------------------------------------------------------
//==============================================================================
