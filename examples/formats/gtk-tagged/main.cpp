/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007-2008 Kevin P. Barry (ta0kira@users.sourceforge.net)      *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <iostream>

#include <hparser/operators.hpp>
#include <hparser/file-manager.hpp>
#include <hparser/data-output.hpp>
#include <hparser/classes/string-message.hpp>
#include <hparser/classes/filo-scope.hpp>

#include "gtk-tagged-base.hpp"
#include "file-interface.hpp"
#include "data-display.hpp"
#include "gtk-proxy.hpp"


//Specific GTK components for the main window
MainView GlobalView = { NULL, NULL, NULL };

//Callback to close the GTK loop when the window closes
static void WindowExit(GtkWidget*, gpointer)
{ gtk_main_quit(); }


//Function main-----------------------------------------------------------------
int main(int argc, char *argv[])
{
	//GUI components%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	gtk_init (&argc, &argv);
	GlobalView.Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(GlobalView.Window), "destroy", G_CALLBACK(WindowExit), NULL);
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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
	GTKTaggedBase tree_base;
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

	//update the tree data in case of parsing errors
	tree_base.global_update();

	//GUI components%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//wait until after parsing to show the window

	gtk_window_set_default_size(GTK_WINDOW(GlobalView.Window), 0, 500);
	gtk_widget_show(GlobalView.Window);
	gtk_main();
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	//after the changes are made with GTK they are exported

	//set the output mode of the tree to 'display'
	tree_base.send_message(Message = "DISPLAY");

	std::cout << "### RECONSTRUCTED FROM STORED DATA ###\n";

	//display the tree data to the display
	if (!export_data(&tree_base, &Display)) std::cout << "DISPLAY ERROR!\n";
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
	}
	//----------------------------------------------------------------------

	return 0;
} //END-------------------------------------------------------------------------


//Function SwitchFunction-------------------------------------------------------
//Switches two 'hparser' elements
void SwitchFunction(void*, gpointer sSection)
{
	//the only thing really required here is the call to 'swap_elements';
	//everything else is just the formality of choosing two elements

	//this stores the first element to be selected
	static storage_section *CurrentSection = NULL;

	if (!sSection || CurrentSection == sSection)
	//if the argument is a NULL then reset__________________________________
	{
	std::cout << "reset first element\n";
	CurrentSection = NULL;
	}

	else if (!CurrentSection)
	//if the argument is the same then reset________________________________
	{
	std::cout << "first element set\n";
	CurrentSection = (storage_section*) sSection;
	}

	else
	//start the swap operation______________________________________________
	{
	std::cout << "execute swap:\n";

	//temporaries for convenience
	storage_section *Left  = CurrentSection;
	storage_section *Right = (storage_section*) sSection;

	//display general swap information

	//any NULL or equals causes a cancel (should be caught already)
	if (!Left || !Right || Left == Right) return;

	scope_identifier Current;
	Left->current_scope(Current, 0 /*NULL*/);
	std::cout << " " << Current.composite_scope() << "\n";

	Current.clear_scope();
	Right->current_scope(Current, 0 /*NULL*/);
	std::cout << " " << Current.composite_scope() << "\n";

	std::cout << "positions: ";
	std::cout << " " << Left->count_previous()  << " (" << Left->count_depth()  << ")  ";
	std::cout << " " << Right->count_previous() << " (" << Right->count_depth() << ")\n";

	if (!swap_elements(Left, Right))
	//perform the actual swap_______________________________________________
	//('swap_elements' automatically checks for vertical indirect ownership)
	 {
	std::cout << "could not swap elements\n";
	std::cout << "reset first element\n";
	CurrentSection = NULL;
	return;
	 }

	std::cout << "elements swapped\n";

	//reset the pointer
	CurrentSection = NULL;
	std::cout << "swap complete\n";
	}
} //END-------------------------------------------------------------------------
