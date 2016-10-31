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

bool Market::placeBuyOrder(Client * buyer, string stock, double value, unsigned quantity)
{
	Order * ptr = new BuyOrder(buyer, stock, value, quantity);	// exception can be thrown, should be handled by higher level function


}