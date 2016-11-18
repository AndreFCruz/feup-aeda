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
	nif_t currentNIF;	// NIF corresponding to current user of the program
	
	Market();
	~Market();	// To delete all dynamically allocated memory
	// Private Destructor ? TBD

	map<nif_t, Client *> clients;
	vector<Transaction *> transactions;
	vector<Order *> unfulfilled_orders;

	string clientsFile, transactionsFile, ordersFile;
	bool clientsChanged;
	bool transactionsChanged;
	bool ordersChanged;

public:
	static Market * instance();

	bool signIn();
	bool signUp(string name, nif_t nif);
	void showClientInfo() const;
	void showClientHistory() const;
	void listBuyOrders() const;
	void listSellOrders() const;

	vector<Transaction*> clientHistory(Client *) const;
	void printTransactions(ostream&) const;
	void listTransactions(Date day1, Date day2);
	void listDailyTransactions(Date d);
	
	//bool placeBuyOrder(Client * buyer, string stock, double value, unsigned quantity);
	auto placeOrder(Order *);	// Abstracts of Buy/Sell type
	void saveChanges() const;	// Save All Info to Files

	friend ostream& operator<<(ostream & out, const Market & m);
};

// Prints Stock Market Statistics
ostream& operator<<(ostream & out, const Market & m);
