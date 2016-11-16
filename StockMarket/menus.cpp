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
	unsigned short int option; nif_t nif;

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


/******************************************
* Gestao de Transacoes
******************************************/
unsigned short int transactionOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Transactions Menu");
	cout << TAB << "1 - List ALL transactions" << endl;
	cout << TAB << "2 - List client's transactions" << endl;
	cout << TAB << "3 - List transactions between 2 days" << endl;
	cout << TAB << "4 - List daily transactions " << endl;
	cout << TAB << "5 - Add transaction" << endl;
	cout << TAB << "6 - Exit sub-menu" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 6, msg);

	if (option == 6)
		return false;	// false == 0

	return option;
}

void transactionMenu() {
	unsigned short int option; string clientName;

	while ((option = transactionOptions())) {
		switch (option) {
		case 1: //list all transactions
			cout << endl;
			Market::instance()->listTransactions();
			break;
		case 2: //list client transactions
			cout << endl << TAB << "Client name: "; getline(cin, clientName);
			Market::instance()->listTransactions(clientName);
			break;
		case 3: //list transactions between 2 days
			Market::instance()->listTransactions(getDate("First day"), getDate("Last day"));
			break;
		case 4: //list daily transactions
			cout << endl << TAB << "Transaction day\n";
			Market::instance()->listTransactions(getDate());
			break;
		case 5: //add transaction
			Market::instance()->addTransaction();
			break;
		}
		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
	}

	Market::instance()->saveChanges();
}

/******************************************
* Gestao de Ordens
******************************************/
unsigned short int orderOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Orders Menu");
	cout << TAB << "1 - List ALL buy orders" << endl;
	cout << TAB << "2 - List ALL sell orders" << endl;
	cout << TAB << "3 - Add buy order" << endl;
	cout << TAB << "4 - Add sell order" << endl;
	cout << TAB << "5 - Exit sub-menu" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 5, msg);

	if (option == 6)
		return false;	// false == 0

	return option;
}

void orderMenu() {
	unsigned short int option; 

	while ((option = transactionOptions())) {
		switch (option) {
		case 1: //list all buy orders
			cout << endl;
			Market::instance()->listBuyOrders();
			break;
		case 2: //list sell orders
			Market::instance()->listSellOrders();
			break;
		case 3: 
			Market::instance()->addBuyOrder();
			break;
		case 4: 
			cout << endl << TAB << "Transaction day\n";
			Market::instance()->addSellOrder();
			break;
		}
		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
	}

	Market::instance()->saveChanges();
}



/******************************************
* Menu Inicial
******************************************/
unsigned short int initialOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Initial Menu");
	cout << TAB << "1 - Manage clients" << endl;
	cout << TAB << "2 - Manage transactions" << endl;
	cout << TAB << "3 - Manage orders" << endl;
	cout << TAB << "4 - Statistic Information" << endl;
	cout << TAB << "5 - Exit program" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 5, msg);
	cout << endl << endl;

	if (option == 5) {
		setcolor(14);
		cout << TAB << "Thank you for using our software!\n" << TAB << "Developed by Andre Cruz, Edgar Carneiro and Joao Conde\n" << endl;
		setcolor(15);
		return false;
	}


	return option;
}

void initialMenu() {
	unsigned int option;


	while ((option = initialOptions()))
		switch (option) {
		case 1: clientMenu();
			break;
		case 2: transactionMenu();
			break;
		case 3: orderMenu();
			break;
		case 4: //Show statistics? 
			break;
		}

	Market::instance()->saveChanges();
}
