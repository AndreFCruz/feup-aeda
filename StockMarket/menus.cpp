#include <iomanip>
#include "Market.h"
#include "menus.h"
#include "utils.h"


bool initialInfo(string & clientsFile, string & transactionsFile, string & ordersFile) {
	cout << TAB_BIG; showTitle("Stock Market");
	cout << "\n Type the name of the files where information is stored (FileName.txt): \n" << endl;
	cout << setw(21) << "Clients' file: "; setcolor(14); cin >> clientsFile;
	setcolor(15); cin.ignore(INT_MAX, '\n');

	cout << setw(21) << "Transactions' file: "; setcolor(14); cin >> transactionsFile;
	setcolor(15); cin.ignore(INT_MAX, '\n');

	cout << setw(21) << "Orders' file: "; setcolor(14); cin >> ordersFile;
	setcolor(15); cin.ignore(INT_MAX, '\n');	// clear the end-of-line character from the cin stream buffer

	return (validFile(clientsFile) && validFile(transactionsFile) && validFile(ordersFile) && !cin.fail());
}

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
	unsigned short int option; uint nif;

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
