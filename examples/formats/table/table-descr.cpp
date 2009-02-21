/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include "table-descr.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include <hparser/classes/string-input.hpp>
#include <hparser/classes/string-output.hpp>

//TableDescr function bodies====================================================
	TableDescr::TableDescr() : Begin(0), Size(0), Elements(0), Table(false),
	Valid(false) {}

	//Descriptor interpretation---------------------------------------------
	unsigned int TableDescr::TakeDescriptor(const input_section &iInput)
	{
	//reset everything
	Begin    = 0;
	Size     = 0;
	Elements = 0;
	Table    = false;
	Valid    = false;

	if (!iInput.size()) return 0;

	//find the start and size of the descriptor
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

	//use temporaries in case of failure
	int  TempBegin    = 0;
	int  TempSize     = 0;
	int  TempElements = 0;
	bool TempTable    = false;
	input_section Temp;

	//check for descriptor type (table or data)
	if (Working[0] == 'N')      TempTable = false;
	else if (Working[0] == 'T') TempTable = true;
	else                        return 0;

	//remove descriptor type
	Working.erase(Working.begin(), Working.begin() + Separate + 1);

	//find the second separator
	Separate = Working.find("/");

	//check the position
	if (Separate < 1 || Working.size() < 1) return 0;

	//copy the first parameter
	Temp = Working.substr(0, Separate);

	//parse the first parameter
	if (!(std::istringstream(Temp) >> (TempTable? TempElements : TempBegin)))
	return 0;

	//check for a stream error or negative parameter
	if ((TempTable? TempElements : TempBegin) < 0) return 0;

	//remove the first parameter
	Working.erase(Working.begin(), Working.begin() + Separate + 1);

	//find the third separator
	Separate = Working.find(TempTable? "/" : "]");

	//check the position
	if (Separate < 1 || Working.size() < 1) return 0;

	//copy the second parameter
	Temp = Working.substr(0, Separate);

	//parse the second parameter
	if (!(std::istringstream(Temp) >> (TempTable? TempBegin : TempSize)))
	return 0;

	//check for a stream error or negative parameter
	if ((TempTable? TempBegin : TempSize) < 0) return 0;

	//remove the second parameter
	Working.erase(Working.begin(), Working.begin() + Separate + 1);

	if (TempTable)
	{
	//find the fourth separator
	Separate = Working.find("]");

	//check the position
	if (Separate < 1 || Working.size() < 1) return 0;

	//copy the third parameter
	Temp = Working.substr(0, Separate);

	//parse the third parameter
	if (!(std::istringstream(Temp) >> TempSize)) return 0;

	//check for a stream error or negative parameter
	if (TempSize < 0) return 0;

	//remove the third parameter
	Working.erase(Working.begin(), Working.begin() + Separate + 1);
	}

	//Check for end of parameters
	if (Working.size()) return 0;

	//copy everything
	Begin    = TempBegin;
	Size     = TempSize;
	Elements = TempElements;
	Table    = TempTable;
	Valid    = true;

	return End + 1;
	}


	output_section TableDescr::send_descriptor() const
	{
	//this function just reconstructs the descriptor and returns it

	std::ostringstream Working;

	Working << "[";
	Working << (Table? "T" : "N");
	Working << "/";
	if (Table) Working << Elements << "/";
	Working << Begin;
	Working << "/";
	Working << Size;
	Working << "]";

	if (!Working) return "";

	return Working.rdbuf()? Working.rdbuf()->str() : "";
	}
	//----------------------------------------------------------------------

	//Section range---------------------------------------------------------
	unsigned int TableDescr::GetBegin() const
	{ return Begin; }

	void TableDescr::SetBegin(unsigned int bBegin)
	{ Begin = bBegin; }

	unsigned int TableDescr::GetSize() const
	{ return Size; }

	void TableDescr::SetSize(unsigned int sSize)
	{ Size = sSize; }
	//----------------------------------------------------------------------

	//Number of elements----------------------------------------------------
	unsigned int TableDescr::GetElements() const
	{ return Table? Elements : 0; }

	void TableDescr::SetElements(unsigned int eElements)
	{ if (Table) Elements = eElements; }
	//----------------------------------------------------------------------

	//Section type----------------------------------------------------------
	bool TableDescr::IsTable() const
	{ return Table; }

	void TableDescr::SetIsTable(bool tTable)
	{ Table = tTable; }
	//----------------------------------------------------------------------

	//Validity--------------------------------------------------------------
	bool TableDescr::IsValid() const
	{ return Valid; }
	//----------------------------------------------------------------------
//==============================================================================
