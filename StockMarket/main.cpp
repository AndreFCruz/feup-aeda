#include <iostream>
#include <stddef.h>
#include "Market.h"
#include "menus.h"



int main()
{
	Market::instance();	// Will call constructor automatically

	initialMenu();		// Initiate Menu

	Market::instance()->saveChanges();	// Save Eventual Changes to Files

	return EXIT_SUCCESS;
}
