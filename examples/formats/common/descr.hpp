/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2006 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

//The 'Descr' class manages descriptors for the descriptor examples.  This class
//parses them from text and exports them to text.

#ifndef DESCRIPTOR_HPP
#define DESCRIPTOR_HPP

#include <string>

#include <hparser/data-input.hpp>
#include <hparser/data-output.hpp>

//Class Descr-------------------------------------------------------------------
//Descriptor manager
class Descr
{
public:
	Descr();

	//Descriptor interpretation---------------------------------------------
	unsigned int TakeDescriptor(const input_section&);
	output_section send_descriptor() const;
	//----------------------------------------------------------------------

	//Section title---------------------------------------------------------
	const std::string &GetTitle() const;
	void SetTitle(const std::string&);
	//----------------------------------------------------------------------

	//Section size----------------------------------------------------------
	unsigned int GetSize() const;
	void SetSize(unsigned int);
	//----------------------------------------------------------------------

	//Section type----------------------------------------------------------
	bool IsTable() const;
	void SetIsTable(bool);
	//----------------------------------------------------------------------

	//Validity--------------------------------------------------------------
	bool IsValid() const;
	//----------------------------------------------------------------------

private:
	std::string Title;
	//Table or data title

	unsigned int Size;
	//Table or data size

	bool Table, Valid;
	//Table flag, valid descriptor flag
}; //END------------------------------------------------------------------------

#endif
