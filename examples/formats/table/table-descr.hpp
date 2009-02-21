/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#ifndef TABLE_DESCRIPTOR_HPP
#define TABLE_DESCRIPTOR_HPP

#include <hparser/data-input.hpp>
#include <hparser/data-output.hpp>

//Class TableDescr--------------------------------------------------------------
//Descriptor manager for table example
class TableDescr
{
public:
	TableDescr();

	//Descriptor interpretation---------------------------------------------
	unsigned int TakeDescriptor(const input_section&);
	output_section send_descriptor() const;
	//----------------------------------------------------------------------

	//Section range---------------------------------------------------------
	unsigned int GetBegin() const;
	void SetBegin(unsigned int);

	unsigned int GetSize() const;
	void SetSize(unsigned int);
	//----------------------------------------------------------------------

	//Number of elements----------------------------------------------------
	unsigned int GetElements() const;
	void SetElements(unsigned int);
	//----------------------------------------------------------------------

	//Section type----------------------------------------------------------
	bool IsTable() const;
	void SetIsTable(bool);
	//----------------------------------------------------------------------

	//Validity--------------------------------------------------------------
	bool IsValid() const;
	//----------------------------------------------------------------------

private:
	unsigned int Begin, Size, Elements;
	//Data begin, data size, table size

	bool Table, Valid;
	//Table flag, valid descriptor flag
}; //END------------------------------------------------------------------------

#endif
