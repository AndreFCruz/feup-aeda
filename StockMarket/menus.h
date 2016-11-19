#pragma once


// Gather initial information for StockMarket Construction
bool initialInfo(string &clientsFile, string &transactionsFile, string &ordersFile);

// Menu implementation
void clientMenu();
void transactionMenu();
void orderMenu();
void startingMenu();
void initialMenu();

/**
* Generic helper function that handles a new order.
* @param newOrder A pointer to the newly created Order to be handled.
*/
void addOrder(Order * newOrder);
