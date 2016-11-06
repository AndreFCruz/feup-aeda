#include <iomanip>
#include "Market.h"
#include "menus.h"
#include "utils.h"

/******************************************
 * Gestao de Clientes
 ******************************************/
unsigned short int clientEditOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Edit Client Menu");
	cout << TAB << "1 - Change name" << endl;
	cout << TAB << "2 - Add amount spent" << endl;
	cout << TAB << "3 - Change total spent" << endl;
	cout << TAB << "4 - Exit sub-menu" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 4, msg);

	if (option == 4)
		return false;	// false == 0

	return option;
}

//void clientEditMenu() {
//	unsigned short int option; string name1, name2; float value;
//
//	while ((option = clientEditOptions())) {
//		switch (option) {
//		case 1: //Change name
//			Market::instance()->changeClientName();
//			break;
//		case 2: //add amount
//			cout << endl << TAB <<"Client's name: "; getline(cin, name1);
//			cout << TAB << "Amount spent: "; cin >> value;
//			Market::instance()->addClientTotal(name1, value);
//			break;
//		case 3: //change total
//			cout << endl << TAB <<"Client's name: "; getline(cin, name1);
//			cout << TAB << "Total spent: "; cin >> value;
//			Market::instance()->changeClientTotal(name1, value);
//			break;
//		}
//		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
//	}
//
//	Market::instance()->saveChanges();
//}


// Template for Future Menu Functions
