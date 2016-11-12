#include <stddef.h>
#include "Market.h"
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
	// Clients from file
	file_in.open(clientsFile);
	file_in >> numberOfObjects;
	for (int i = 0; i < numberOfObjects; ++i) {
		Client * temp_c = new Client(file_in);
		clients.insert(pair<unsigned int, Client*>(temp_c->getNIF(), temp_c));
	}
	file_in.close();
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