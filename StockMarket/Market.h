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
	
	Market();
	~Market();	// To delete all dynamically allocated memory
	// Private Destructor ? TBD

	map<uint, Client *> clients;
	vector<Transaction *> transactions;
	vector<Order *> unfulfilled_orders;

	string clientsFile, transactionsFile, ordersFile;
	bool clientsChanged;
	bool transactionsChanged;
	bool ordersChanged;

public:
	static Market * instance();

	void showClientInfo(uint nif);
	void showClientHistory(uint nif);
	vector<Transaction*> clientHistory(Client *);
	void printTransactions(ostream&) const;
	//bool placeBuyOrder(Client * buyer, string stock, double value, unsigned quantity);
	bool placeOrder(Order *);	// Abstracts of Buy/Sell type
	void saveChanges();	// Save All Info to Files

	friend ostream& operator<<(ostream & out, const Market & m);
};

// Prints Stock Market Statistics
ostream& operator<<(ostream & out, const Market & m);
