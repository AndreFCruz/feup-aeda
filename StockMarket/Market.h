#pragma once

#include <map>
#include <vector>
#include "Client.h"
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
	map<unsigned int, Client *> clients;
	vector<Transaction *> transactions;
	vector<Order *> unfulfilled_orders;

public:
	static Market * instance();

	void showClientInfo(unsigned int nif);
	void showClientHistory(unsigned int nif);
	vector<Transaction*> clientHistory(Client *);
	void printTransactions(ostream&) const;
	//bool placeBuyOrder(Client * buyer, string stock, double value, unsigned quantity);
	bool placeOrder(Order *);	// Abstracts of Buy/Sell type
	void saveChanges();	// Save All Info to
};
