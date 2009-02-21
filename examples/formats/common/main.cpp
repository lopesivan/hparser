/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

//This 'main' file is used by all of the examples.  Each example defines the
//'BASE_TYPE' macro with the class name of the tree base for that example, and
//the 'BASE_TYPE_FILE' for its include file.

#include <iostream>

#include <hparser/file-manager.hpp>
#include <hparser/data-output.hpp>
#include <hparser/classes/string-message.hpp>

#include BASE_TYPE_FILE       /* specific include for each example */
#include "file-interface.hpp"
#include "data-display.hpp"

//Function main-----------------------------------------------------------------
int main(int argc, char *argv[])
{
	//This message is used as a 'template' for messages sent to the tree.
	//This can't be constructed as an argument because the argument must be
	//a non-const reference.
	comm_message Message;

	if (argc < 2 || argc > 3)
	//Argument check--------------------------------------------------------
	{
	std::cout << argv[0] << " [input file] (output file)\n";
	return 0;
	}
	//----------------------------------------------------------------------

	//Objects needed for parsing--------------------------------------------
	BASE_TYPE     tree_base;     /* specific class for each example */
	FileInterface FileTransfer;
	DataDisplay   Display;
	//----------------------------------------------------------------------

	if (argc > 1)
	//Initial file parsing--------------------------------------------------
	{
	std::cout << "### DATA PARSED FROM " << argv[1] << " ###\n";

	//set the file to transfer from
	if (!FileTransfer.set_file(argv[1])) std::cout << "SET FILE ERROR!\n";

	//load the file into the tree base
	if (!load_file(&tree_base, &FileTransfer)) std::cout << "INPUT ERROR!\n";

	std::cin.get();

	//update the tree data in case of parsing errors
	tree_base.global_update();

	//set the output mode of the tree to 'display'
	tree_base.send_message(Message = "DISPLAY");

	std::cout << "### RECONSTRUCTED FROM STORED DATA ###\n";

	//display the tree data to the display
	if (!export_data(&tree_base, &Display)) std::cout << "DISPLAY ERROR!\n";

	std::cin.get();
	}
	//----------------------------------------------------------------------

	if (argc > 2)
	//File reconstruction---------------------------------------------------
	{
	//set the output mode of the tree to 'output'
	tree_base.send_message(Message = "OUTPUT");

	std::cout << "### RECONSTRUCTED DATA SENT TO " << argv[2] << " ###\n";

	//set the file to transfer to
	if (!FileTransfer.set_file(argv[2])) std::cout << "SET FILE ERROR!\n";

	//save the data from the tree base into the second file
	if (!save_file(&tree_base, &FileTransfer)) std::cout << "OUTPUT ERROR!\n";

	std::cin.get();
	}
	//----------------------------------------------------------------------

	return 0;
} //END-------------------------------------------------------------------------
