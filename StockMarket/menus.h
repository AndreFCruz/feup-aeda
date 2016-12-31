#pragma once


// Gather initial information for StockMarket Construction

/** \fn
*	Function that initializes the program. 
*	@param clientsFile  A string with the clients' file name.
*	@param transactionsFile  A string with the transactions' file name.
*	@param ordersFile  A string with the orders' file name.
*	@param newsFile  A string with the news' file name.
*	@param managersFile  A string with the managers' file name.
*	@return A boolean, true if the set up was successfull.
*/
bool initialInfo(string &clientsFile, string &transactionsFile, string &ordersFile, string &newsFile, string &managersFile);

// Menu implementation

/** \fn
*	Function working as the client's settings menu.
*/
void clientMenu();

/** \fn
*	Function working as the transactions' editing menu.
*/
void transactionMenu();

/** \fn
*	Function working as the orders' editing menu.
*/
void orderMenu();

/** \fn
*	Function working as the news' editing menu.
*/
void newsMenu();

/** \fn
*	Function working as the Client's home menu (main menu).
*/
void homeMenu();

/** \fn
*	Function working as the initializing menu, signing up/in the user.
*/
void initialMenu();

/** \fn
* 	Generic helper function that handles a new order.
* 	@param newOrder A pointer to the newly created Order to be handled.
*/
void addOrder(Order * newOrder);
