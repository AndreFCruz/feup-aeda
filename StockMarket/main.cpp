#include <iostream>
#include <stddef.h>
#include "Market.h"
#include "menus.h"



int main()
{
	std::cout << "Hello World!!\n";
	Market::instance();

	initialMenu();

	return EXIT_SUCCESS;
}
