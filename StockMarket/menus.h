#pragma once


// Gather initial information for StockMarket Construction
<<<<<<< HEAD

/** \fn
*	Function that initializes the program. 
*	@param clientsFile  A string with the clients file name.
*	@param transactionsFile  A string with the transactions file name.
*	@param ordersFile  A string with the orders file name.
*	@return A boolean, true if the set up was successfull.
*/
bool initialInfo(string &clientsFile, string &transactionsFile, string &ordersFile);

// Menu implementation

/** \fn
*	Function working as the client editing menu.
*/
void clientMenu();

/** \fn
*	Function working as the transactions editing menu.
*/
void transactionMenu();

/** \fn
*	Function working as the orders editing menu.
*/
void orderMenu();

/** \fn
*	Function working as the starting menu (main menu).
*/
void startingMenu();
<<<<<<< HEAD

/** \fn
*	Function working as the initializing menu, signing up/in the user.
*/
void initialMenu();

/** \fn
* 	Generic helper function that handles a new order.
* 	@param newOrder A pointer to the newly created Order to be handled.
*/
void addOrder(Order * newOrder);
