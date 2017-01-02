#include <iomanip>
#include "Market.h"
#include "menus.h"
#include "utils.h"


bool initialInfo(string & clientsFile, string & transactionsFile, string & ordersFile, string & newsFile, string & managersFile) {
	cout << TAB_BIG; showTitle("Stock Market");
	cout << "\n Type the name of the files where information is stored (FileName.txt): \n" << endl;
	cout << setw(21) << "Clients' file: "; setcolor(14); cin >> clientsFile;
	setcolor(15); cin.ignore(INT_MAX, '\n');	// clear the end-of-line character from the cin stream buffer

	cout << setw(21) << "Transactions' file: "; setcolor(14); cin >> transactionsFile;
	setcolor(15); cin.ignore(INT_MAX, '\n');	// clear the end-of-line character from the cin stream buffer

	cout << setw(21) << "Orders' file: "; setcolor(14); cin >> ordersFile;
	setcolor(15); cin.ignore(INT_MAX, '\n');	// clear the end-of-line character from the cin stream buffer

	cout << setw(21) << "News' file: "; setcolor(14); cin >> newsFile;
	setcolor(15); cin.ignore(INT_MAX, '\n');	// clear the end-of-line character from the cin stream buffer

	cout << setw(21) << "Managers' file: "; setcolor(14); cin >> managersFile;
	setcolor(15); cin.ignore(INT_MAX, '\n');	// clear the end-of-line character from the cin stream buffer

	return (validFile(clientsFile) && validFile(transactionsFile) && validFile(ordersFile)
			&& validFile(newsFile) && validFile(managersFile) &&  !cin.fail());
}

/******************************************
 * CLIENTS' MENU
 ******************************************/
unsigned short int clientOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Client's Menu");
	cout << TAB << "1 - Show Information" << endl;
	cout << TAB << "2 - Show Transaction History" << endl;
	cout << TAB << "3 - Show unfulfilled Orders" << endl;
	cout << TAB << "4 - Delete a unfullfilled Order" << endl;
	cout << TAB << "5 - View manager information" << endl;
	cout << TAB << "6 - Exit menu" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 6, msg);

	if (option == 6)
		return false;	// false == 0

	return option;
}

void clientMenu() {
	unsigned short int option;

	while ((option = clientOptions())) {
		switch (option) {
		case 1: //Show Info
			Market::instance()->showClientInfo();
			break;
		case 2: //Show Client History
			cout << endl << TAB << "Client's transaction History:\n\n";
			Market::instance()->showClientHistory();
			break;
		case 3:
			cout << endl << TAB << "Client's unfulfilled Orders:\n";
			Market::instance()->showClientOrders();
			break;
		case 4:
			int choice;
			Market::instance()->showClientOrders();
			cout << endl << TAB << "Select the Order you wish to erase: (example: 1 for first, 2 for second,...)\n" << TAB << "Your option: ";
			cin >> choice; cin.ignore();

			if (Market::instance()->eraseClientOrder(choice))
				cout << TAB << "Order successfully erased!\n\n";
			else
				cout << TAB << "Failed to erase Order!\n\n";
			break;
		case 5:
			cout << " Name:" << Market::instance()->getClientManager();
		}
		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
	}
}


/******************************************
* TRANSACTIONS' MENU
******************************************/
unsigned short int transactionOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Transactions' Menu");
	cout << TAB << "1 - List ALL transactions" << endl;
	cout << TAB << "2 - List client's transactions" << endl;
	cout << TAB << "3 - List transactions of a specific Stock" << endl;
	cout << TAB << "4 - List transactions between 2 days" << endl;
	cout << TAB << "5 - List daily transactions " << endl;
	cout << TAB << "6 - Exit sub-menu" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 6, msg);

	if (option == 6)
		return false;	// false == 0

	return option;
}

void transactionMenu() {
	unsigned short int option; string str; Date d;

	while ((option = transactionOptions())) {
		switch (option) {
		case 1: //list all transactions
			cout << endl;
			Market::instance()->showTransactions();
			break;
		case 2: //list client's transactions
			cout << endl;
			Market::instance()->showClientHistory();
			break;
		case 3: //list transactions of a specific Stock
			cout << endl << TAB << setw(10) << "Stock: ";
			getline(cin, str); trim(str); cout << endl;
			Market::instance()->showTransactions(str);
			break;
		case 4: //list transactions between 2 days
			d = getDate("First day: "); cout << endl;
			Market::instance()->showTransactions(d, getDate("Last day: "));
			break;
		case 5: //list daily transactions
			cout << endl;
			Market::instance()->showTransactions(getDate("Transaction day: "));
			break;
		}
		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
	}
}

/******************************************
* ORDERS' MENU
******************************************/
unsigned short int orderOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Orders' Menu");
	cout << TAB << "1 - List ALL buy orders" << endl;
	cout << TAB << "2 - List ALL sell orders" << endl;
	cout << TAB << "3 - Add buy order" << endl;
	cout << TAB << "4 - Add sell order" << endl;
	cout << TAB << "5 - Exit sub-menu" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 5, msg);

	if (option == 5)
		return false;	// false == 0

	return option;
}

void orderMenu() {
	unsigned short int option;
	string stock;
	double val;
	unsigned quantity;
	Order * newOrder;

	while ((option = orderOptions())) {
		switch (option) {
		case 1: //list all buy orders
			Market::instance()->showBuyOrders();
			break;
		case 2: //list all sell orders
			Market::instance()->showSellOrders();
			break;
		case 3: 
			cout << TAB << "Adding a new Buy Order...\n\n";
			setcolor(14); cout << TAB << setw(20) << "Stock: "; setcolor(15);
			getline(cin, stock); trim(stock);
			val = getValue<double>("Stock's value: ", 20);
			quantity = getValue<unsigned int>("Quantity: ", 20);

			newOrder = new BuyOrder(stock, val, quantity, Market::instance()->getCurrentNIF());
			addOrder(newOrder);
			break;
		case 4: 
			cout << TAB << "Adding a new Sell Order...\n\n";
			setcolor(14); cout << TAB << setw(20) << "Stock: "; setcolor(15);
			getline(cin, stock); trim(stock);
			val = getValue<double>("Stock's value: ", 20);
			quantity = getValue<unsigned int>("Quantity: ", 20);

			newOrder = new SellOrder(stock, val, quantity, Market::instance()->getCurrentNIF());
			addOrder(newOrder);
			break;
		}
		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
	}
}


/******************************************
* NEWS' MENU
******************************************/
unsigned short int newsOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("News' Menu");
	cout << TAB << "1 - List all News" << endl;
	cout << TAB << "2 - List News of a specific Company" << endl;
	cout << TAB << "3 - List News published on a specific day" << endl;
	cout << TAB << "4 - List News published on a time interval" << endl;
	cout << TAB << "5 - Add a News" << endl;
	cout << TAB << "6 - Erase a News" << endl;	// Morally questionable...
	cout << TAB << "7 - Change a News' Classification" << endl;
	cout << TAB << "8 - Exit sub-menu" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 8, msg);
	cout << endl << endl;

	if (option == 8) {
		Market::instance()->signOut();
		return false;
	}

	return option;
}

void newsMenu() {
	unsigned short int option;
	unsigned short int idx, classification; // Varied usage regarding input from user
	string str;	// Varied usage regarding input from user
	string newspaper;
	Date d;

	while ((option = newsOptions())) {
		switch (option) {
		case 1: // list all news
			Market::instance()->showNews();
			break;
		case 2:	// list news of specific company
			cout << endl << TAB << setw(10) << "Company: ";
			getline(cin, str); trim(str); cout << endl;
			Market::instance()->showNews(str);
			break;
		case 3: // list news on specific day
			d = getDate("News' publishing date: "); cout << endl;
			Market::instance()->showNews(d);
			break;
		case 4:	// list news on time interval
			d = getDate("First day: "); cout << endl;
			Market::instance()->showNews(d, getDate("Last day: "));
			break;
		case 5:	// add a news
			//company
			cout << TAB << "Adding a News...\n\n";
			setcolor(14); cout << TAB << setw(20) << "Company: "; setcolor(15);
			getline(cin, str); trim(str);

			//date
			d = getDate("\nNews' publishing date: "); cout << endl;

			//newspaper
			setcolor(14); cout << TAB << setw(20) << "Newspaper: "; setcolor(15);
			getline(cin, newspaper); trim(newspaper);

			//classification
			classification = getValue<unsigned short int>("\nClassification: ", 20);

			cout << "\n\t" << (Market::instance()->addNews(str, d, newspaper, classification) ? "Success!" : "Unsuccessful...") << endl;

			break;

		case 6:	// erase a news -- mandatory by project specification, altough morally questionable...
			Market::instance()->showNews();

			cout << endl << endl;
			idx = getValue<unsigned short int>("Index to erase: ", 20);

			cout << "\n\t" << (Market::instance()->eraseNews(idx - 1) ? "Success!" : "Unsuccessful...") << endl;

			break;
		case 7: // change a news' classification -- mandatory by project specification, altough morally questionable...
			Market::instance()->showNews();

			cout << endl << endl;
			idx = getValue<unsigned short int>("Index to change: ", 20);

			cout << endl;
			classification = getValue<unsigned short int>("New Classification: ", 20);

			cout << "\n\t" << (Market::instance()->changeNewsClass(idx - 1, classification) ? "Success!" : "Unsuccessful...") << endl;
			break;
		}
		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
	}
}


/******************************************
* HOME MENU
******************************************/
unsigned short int homeOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Home Menu");
	cout << TAB << "1 - Client's Menu" << endl;
	cout << TAB << "2 - Transactions' Menu" << endl;
	cout << TAB << "3 - Orders' Menu" << endl;
	cout << TAB << "4 - News' Menu" << endl;
	cout << TAB << "5 - Statistic Information" << endl;
	cout << TAB << "6 - Sign Out" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 6, msg);
	cout << endl << endl;

	if (option == 6) {
		Market::instance()->signOut();
		return false;
	}

	return option;
}

void homeMenu() {
	unsigned int option;

	while ((option = homeOptions()))
		switch (option) {
		case 1:
			clientMenu();
			break;
		case 2:
			transactionMenu();
			break;
		case 3:
			orderMenu();
			break;
		case 4:
			newsMenu();
			break;
		case 5:
			cout << *(Market::instance());
			cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
			break;

		}
}

/******************************************
* Menu de Inicialização
******************************************/
unsigned short int initialOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Initial Menu");
	cout << TAB << "1 - Sign In as Client" << endl;
	cout << TAB << "2 - Sign Up as Client" << endl;
	cout << TAB << "3 - Sign In as Manager" << endl;
	cout << TAB << "4 - Sign Up as Manager" << endl;
	cout << TAB << "5 - Exit program" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 5, msg);
	cout << endl << endl;

	if (option == 5) {
		Market::instance()->saveChanges();
		setcolor(14);
		cout << TAB << "Thank you for using our software!\n" << TAB << "Developed by Andre Cruz, Edgar Carneiro and Joao Conde\n" << endl;
		setcolor(15);
		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
		return false;
	}

	return option;
}

void initialMenu() {
	unsigned int option;
	string name, pass;
	nif_t nif;
	cout << endl;
	
	while ((option = initialOptions()))
		switch (option) {
		case 1:
			setcolor(14);
			cout << TAB << setw(10) << "Name: ";
			setcolor(15);
			getline(cin, name, '\n'); trim(name);
			nif = getValue<nif_t>("NIF: ", 10);

			if (Market::instance()->signIn(name, nif)) {
				cout << endl << TAB_BIG << "Signed In successfully!\n";
				cout << endl << TAB_BIG << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
				homeMenu();
			}
			else {
				cout << endl << TAB_BIG << "Sign In Unsuccessful.\n";
				cout << endl << TAB_BIG << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
			}
			break;
		case 2:
			cout << TAB << setw(10) << "Name: ";
			getline(cin, name); trim(name);
			nif = getValue<nif_t>("NIF: ", 10);
		
			try {
				Market::instance()->signUp(name,nif);
			}
			catch (Client::InvalidNIF & e) {
				cout << TAB <<"\nInvalidNIF: " << e.getNIF() << endl;
			}
			cout << TAB << "\nPress ENTER to continue..."; cin.ignore(INT_MAX, '\n');
			break;
		case 3:	// Sign In as Manager
			setcolor(14);
			cout << TAB << setw(10) << "Name: ";
			setcolor(15);
			getline(cin, name, '\n'); trim(name);
			setcolor(14);
			cout << TAB << setw(10) << "Password: ";
			setcolor(15);
			getline(cin, pass, '\n'); trim(pass);

			if (Market::instance()->signInManager(name, pass)) {
				cout << endl << TAB_BIG << "Signed In successfully!\n";
				cout << endl << TAB_BIG << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
				managerMenu();
			}
			else {
				cout << endl << TAB_BIG << "Sign In Unsuccessful.\n";
				cout << endl << TAB_BIG << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
			}
			break;
		case 4: // Sign Up as Manager
			cout << TAB << setw(10) << "Name: ";
			getline(cin, name); trim(name);
			
			cout << TAB << setw(10) << "Password: ";
			getline(cin, pass); trim(pass);

			try {
				Market::instance()->signUpManager(name, pass);
				Market::instance()->redistributeManagers();
			}
			catch (Manager::InvalidPassword & e) {
				cout << TAB << "\nInvalid Password: " << e.getPassword() << ". Must use, at least, 6 characters." << endl;
			}
			cout << TAB << "\nPress ENTER to continue..."; cin.ignore(INT_MAX, '\n');
			break;
		}
}

/* Generic Helper Function for Handling New Orders */
void addOrder(Order * newOrder)
{
	unsigned originalQuantity = newOrder->getQuantity();
	auto result = Market::instance()->placeOrder(newOrder);

	bool fullfilled = true;
	unsigned transactioned = 0;
	for (auto it = result.first; it != result.second; ++it) {
		transactioned += (*it)->getQuantity();
	}

	cout << endl << TAB;
	if (0 == transactioned) {
		cout << "StockMarket was unable to fulfill your Order and was put on hold till compatible orders are found.\n\n";
		return;
	} else if (transactioned != originalQuantity) {
		cout
			<< "Your order was partially fullfilled. Waiting for more Buy Orders to completely fullfill it!\n"
			<< TAB << "Transactioned stocks: " << transactioned << ".\n\n\n";
	} else {
		cout << "Your order was instantly fullfilled!\n";
	}

	cout << TAB_BIG << "Transactions generated:\n\n";
	while (result.first != result.second)
		cout << TAB << *(*(result.first++));
}

/******************************************
* MANAGER'S MENU
******************************************/
unsigned short int managerOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Manager Menu");
	cout << TAB << "1 - List your own information" << endl;
	cout << TAB << "2 - See other Manager's info" << endl;
	cout << TAB << "3 - Change your password" << endl;
	cout << TAB << "4 - Delete your Manager Account" << endl;
	cout << TAB << "5 - Sign Out" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 5, msg);
	cout << endl << endl;

	if (option == 5) {
		Market::instance()->signOutManager();
		return false;
	}

	return option;
}

void managerMenu() {
	unsigned int option;
	string newpass;
	cout << endl;

	while ((option = managerOptions())) {
		switch (option) {
		case 1:
			Market::instance()->showOwnManager();
			break;
		case 2:
			Market::instance()->showManagers();
			break;
		case 3:
			cout << TAB << setw(10) << "New Password: ";
			getline(cin, newpass); trim(newpass);

			//Checking if Password is 
			try {
				Market::instance()->ChangeManagerPassword(newpass);
			}
			catch (Manager::InvalidPassword & e) {
				cout << TAB << "\nInvalid Password: " << e.getPassword() << ". Must use, at least, 6 characters." << endl;
			}
			
			break;
		case 4:
			if (Market::instance()->deleteOwnManager())
				cout << TAB << "Manager successfully erased!\n";
			else
				cout << TAB << "Manager deletion failed.\n";

			Market::instance()->redistributeManagers();
			break;
		}

		cout << TAB << "\nPress ENTER to continue..."; cin.ignore(INT_MAX, '\n');
	}
}
