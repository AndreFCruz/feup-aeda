#include <iomanip>
#include "Market.h"
#include "menus.h"
#include "utils.h"

/******************************************
 * Gestao de Clientes
 ******************************************/
unsigned short int clientOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Client Menu");
	cout << TAB << "1 - Show Information" << endl;
	cout << TAB << "2 - Show History" << endl;
	cout << TAB << "3 - Exit menu" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 3, msg);

	if (option == 3)
		return false;	// false == 0

	return option;
}

void clientMenu() {
	unsigned short int option; unsigned int nif;

	while ((option = clientOptions())) {
		switch (option) {
		case 1: //Show Info
			cout << endl << TAB << "Client's NIF: "; cin >> nif;
			Market::instance()->showClientInfo(nif);
			break;
		case 2: //Show Client History
			cout << endl << TAB << "Client's NIF: "; cin >> nif;
			Market::instance()->showClientHistory(nif);
			break;
		}
		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
	}

	Market::instance()->saveChanges();
}


// Template for Future Menu Functions
