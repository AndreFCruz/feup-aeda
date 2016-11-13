#include <algorithm>
#include "Market.h"
#include "defs.h"
#include "menus.h"
#include "utils.h"


Market* Market::singleton_instance = NULL;

Market::Market() {
	ifstream file_in; string line;
	unsigned numberOfObjects;
	ordersChanged = transactionsChanged = clientsChanged = false;

	while (!initialInfo(clientsFile, transactionsFile, ordersFile)) {
		cout << "\nInvalid StockMarket Initialization ! Carefully type the information required! \a\n\n";
		cout << TAB << "\n Press ENTER to retry..."; cin.ignore(INT_MAX, '\n');
		clearScreen();
	}

	/* Populate Data Structures */
	// Clients from file
	file_in.open(clientsFile);
	file_in >> numberOfObjects;
	for (int i = 0; i < numberOfObjects; ++i) {
		Client * temp_c = new Client(file_in);
		clients.insert(pair<uint, Client*>(temp_c->getNIF(), temp_c));
	}
	file_in.close();

	// Transactions from file
	file_in.open(transactionsFile);
	file_in >> numberOfObjects;
	transactions.reserve(numberOfObjects);
	for (int i = 0; i < numberOfObjects; ++i) {
		Transaction * temp_t = new Transaction(file_in);
		transactions.push_back(temp_t);
	}
	file_in.close();
	
	// Sort transactions by chronological order
	sort(transactions.begin(), transactions.end(), [](const Transaction * t1, const Transaction * t2) {return t1->getDate() < t2->getDate(); });

	// Unfulfilled Orders from file
	char c;	// Buy/Sell Char Flag
	file_in.open(ordersFile);
	file_in >> numberOfObjects;
	transactions.reserve(numberOfObjects);
	for (int i = 0; i < numberOfObjects; ++i) {
		Order * temp_o;
		file_in >> c;
		switch (c) {
		case 'B':
			temp_o = new BuyOrder(file_in);
			break;
		case 'S':
			temp_o = new SellOrder(file_in);
			break;
		default:
			cerr << "Invalid Order Identifier in File \"" << ordersFile << "\".\n";
			break;
		}
		unfulfilled_orders.push_back(temp_o);
	}
	file_in.close();
}

Market::~Market() {
	// Warning: Do Not delete from files

	// Delete Clients from Memory
	for (auto p : clients)
		delete p.second;

	// Delete Transactions from Memory
	for (Transaction * t : transactions)
		delete t;

	// Delete Orders from Memory
	for (Order * o : unfulfilled_orders)
		delete o;
}

Market* Market::instance() {
	if (!singleton_instance)
		singleton_instance = new Market;

	return singleton_instance;
}

void Market::printTransactions(ostream & out) const
{
	for (Transaction * t : transactions) {
		out << *t;
	}
}

/* To Delete (?) */
//bool Market::placeBuyOrder(Client * buyer, string stock, double value, unsigned quantity)
//{
//	Order * ptr = new BuyOrder(stock, value, quantity, buyer);	// exception can be thrown, should be handled by higher level function
//
//	for (unsigned i = 0; i < unfulfilled_orders.size(); i++) {
//		Transaction * trans;
//		if ((trans = (*unfulfilled_orders[i])(ptr)) != NULL) {	// Transaction Successful ?
//			transactions.push_back(trans);
//
//			// Corresponding Sell Order Fulfilled ?
//			if (unfulfilled_orders[i]->getQuantity() == 0) {
//				delete unfulfilled_orders[i];
//				unfulfilled_orders.erase(unfulfilled_orders.begin() + i);
//			}
//			if (0 == quantity) {
//				delete ptr;
//				return true;
//			}
//		}	// Memory Leak ?
//	}
//	return false;
//}

bool Market::placeOrder(Order * ptr)
{
	for (unsigned i = 0; i < unfulfilled_orders.size(); i++) {
		Transaction * trans;
		if ((trans = (*unfulfilled_orders[i])(ptr)) != NULL) {	// Transaction Successful ?
			transactions.push_back(trans);
			
			// Corresponding Buy/Sell Order Fulfilled ?
			if (unfulfilled_orders[i]->getQuantity() == 0) {
				delete unfulfilled_orders[i];
				unfulfilled_orders.erase(unfulfilled_orders.begin() + i);
			}
			if (0 == ptr->getQuantity()) {
				delete ptr;
				return true;
			}
		}
	}
	return false;
}