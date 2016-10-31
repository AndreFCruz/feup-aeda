#pragma once

#include <vector>
#include "Transaction.h"
#include "Order.h"

/*
 * Singleton Class to implement most of the logic behind the StockMarket
 */

using namespace std;

class Market
{
private:
	static Market * singleton_instance;
	
	Market() = default;	// TODO : change constructor
	~Market();	// To delete all dynamically allocated memory
	vector<Transaction *> transactions;
	vector<Order *> unfulfilled_orders;

public:
	static Market * instance();

	void printTransactions(ostream&) const;
	bool placeBuyOrder(Client * buyer, string stock, double value, unsigned quantity);
};
