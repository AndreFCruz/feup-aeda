#include <stddef.h>
#include "Market.h"


Market* Market::singleton_instance = NULL;

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
		}	// Memory Leak ?
	}
	return false;
}