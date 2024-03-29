#pragma once

#include <map>
#include <vector>
#include <set>
#include <unordered_set>
#include <queue>
#include "Client.h"
#include "Transaction.h"
#include "Order.h"
#include "News.h"
#include "Manager.h"

using namespace std;

#define DAYS_INACTIVE	20	/**< Time interval, in days, from which clients are considered inactive. */

/**
*  Singleton Class to implement most of the logic behind the StockMarket
*/

class Market
{
	friend class Manager;
private:
	static Market * singleton_instance;	/**< Market pointer. Contains the pointer to the singleton instance of Market. */
	nif_t currentNIF;					/**<  nif_t NIF. Saves the NIF of the current client. */
	string currentManager;				/**<  nif_t NIF. Saves the "username" of the current manager. */
	
	/**
	* A default constructor.
	*/
	Market();

	/**
	* A destructor.
	* Deletes all dynamically allocated memory.
	*/
	~Market();	

	map<nif_t, Client *> clients;			/**< Map clients. A map where the key's are clients NIF's and the values are client pointers.
												 Relates a NIF and a client for ease of access. */
	vector<Transaction *> transactions;		/**< Vector transactions. A vector saving pointers of all Market's transactions. */
	vector<Order *> unfulfilled_orders;		/**< Vector unfulfilled_orders. A vector saving pointers of all Market's unfulfilled orders. */

	// Data Structures for the 2nd part of the project
	set<News> news;							/**< Set news. A set, implemented as a Binary Search Tree (BST), of News objects. */
	priority_queue<Manager> managers;		/**< Priority Queue managers. A priority queue of manager objects. */
	unordered_set<Client *, clientPtrHash, clientPtrHash> inactive_clients;	/**< Hash Table inactive_clients. Stores the clients that are inactive for more than 1 month */

	string clientsFile;			/**< string clientsFile. String with the clients' file name. */
	string ordersFile;			/**< string ordersFile. String with the orders' file name. */
	string transactionsFile;	/**< string transactionsFile. String with the transactions' file name. */
	string newsFile;			/**< string newsFile. String with the news' file name. */
	string managersFile;		/**< string managersFile. String with the managers' file name. */

	bool clientsChanged;	   /**<	bool clientsChanged. Boolean set to true if any changes were made to the clients during execution. */	
	bool transactionsChanged;  /**< bool transactionsChanged. Boolean set to true if any changes were made to the transactions during execution. */
	bool ordersChanged;		   /**< bool ordersChanged. Boolean set to true if any changes were made to the orders during execution. */
	bool newsChanged;		   /**< bool newsChanged. Boolean set to true if any changes were made to the news during execution. */
	bool managersChanged;	   /**< bool managersChanged. Boolean set to true if any changes were made to the managers during execution. */

	/**
	* A private method that iterates through the clients BST and stores all inactive clients in a Hash Table.
	*/
	void checkInactiveClients();

public:
	/**
	* A member function returning the one and only instace of Market (creates it if one doesn't exist).
	* @return A pointer to the singleton instance of Market.
	*/
	static Market * instance();

	/**
	* A member function that signs in the user.
	* @param name Name of the client/user
	* @param nif  NIF othe client/user
	* @return A boolean, true if signing in was done successfully.
	*/
	bool signIn(string name, nif_t nif);

	/**
	* A member function that signs out the user.
	*/
	void signOut();

	/**
	* A member function that signs up the user.
	* @param name	The client's name.
	* @param nif	The client's NIF.
	* @param address	The client's address.
	* @param contact	The client's contact information.
	* @return A boolean, true if signing up was done successfully.
	*/
	bool signUp(string name, nif_t nif, string address, string contact);

	/**
	* A member function that signs in the manager.
	* @param name Username of the manager/user
	* @param pass Password of the manager/user
	* @return A boolean, true if signing in was done successfully.
	*/
	bool signInManager(string name, string pass);

	/**
	* A member function that signs out the user.
	*/
	void signOutManager();

	/**
	* A member function that signs up the user.
	* @param name Name of the manager/user
	* @param pass  Password of the manager/user
	* @return A boolean, true if signing up was done successfully.
	*/
	bool signUpManager(string name, string pass);

	/**
	* A member function that returns the current client's NIF.
	* @return The current client's nif.
	*/
	nif_t getCurrentNIF() const;

	/**
	* A member function that returns the current manager's NIF.
	* @return The current manager's nif.
	*/
	string getCurrentManager() const;

	/**
	* A const member function that displays the client's information.
	*/
	void showClientInfo() const;

	/**
	* A const member function that displays the client's history of transactions.
	*/
	void showClientHistory() const;

	/**
	* A const member function that displays the client's unfulfilled orders.
	*/
	void showClientOrders() const;

	/**
	* A member function that erases a client's unfulfilled order.
	* @param The number corresponding to the order to be erased (sorted by date placed).
	* @return A boolean, true if deletion of the order was done successfully.
	*/
	bool eraseClientOrder(unsigned choice);

	/**
	* A const member function that lists the buy orders.
	*/
	void showBuyOrders() const;

	/**
	* A const member function that lists the sell orders.
	*/
	void showSellOrders() const;

	/**
	* A const member function used to get the client's history of transactions.
	* @param c A client pointer.
	* @return A vector of the client's transactions.
	*/
	vector<Transaction*> clientHistory(Client * c) const;

	/**
	* A const member function that prints all transactions to the COUT output stream.
	*/
	void showTransactions() const;

	/**
	* Overload of member function that prints the transactions of a given Stock.
	* @param stock The Stock's name.
	*/
	void showTransactions(string stock) const;

	/**
	* Overload of member function that lists the transactions between 2 days.
	* @param day1 The first day of the interval.
	* @param day2 The last day of the interval.
	*/
	void showTransactions(Date day1, Date day2) const;

	/**
	* Overload of member function that lists the transactions of a given day.
	* @param d The day whose transactions will be shown. 
	*/
	void showTransactions(Date d) const;

	/**
	* A const member function that prints all News to the COUT output stream.
	*/
	void showNews() const;

	/**
	* Overload of member function that prints all News of a given Company.
	* @param company The Company's name.
	*/
	void showNews(string company) const;

	/**
	* Overload of member function that lists the News between 2 days.
	* @param day1 The first day of the interval.
	* @param day2 The last day of the interval.
	*/
	void showNews(Date day1, Date day2) const;

	/**
	* Overload of member function that lists the News of a given day.
	* @param d The day whose news will be shown.
	*/
	void showNews(Date d) const;

	/**
	* Shows the current list of inactive clients.
	*/
	void showInactiveClients() const;

	/**
	* Checks whether currently logged in client is considered active.
	* @return true if client is not in the Hash inactive_clients, false otherwise.
	*/
	bool isActiveClient() const;

	/**
	* A member function that changes the current client's address, if he is considered inactive.
	* @param address The new address.
	* @return A boolean, true if change was successful.
	*/
	bool changeAddress(string address);

	/**
	* A member function that changes the current client's contact information, if he is considered inactive.
	* @param contact The new contact information.
	* @return A boolean, true if change was successful.
	*/
	bool changeContact(string contact);

	/**
	* A member function that creates a News object with the given parameters,
	* and adds it to the attribute BST.
	* @param company The name of the company mentioned in the News.
	* @param d The date the news was published.
	* @param newspaper The name of the newspaper it was published in.
	* @param classification The News' classification (from 0 to 10).
	* @return A bool indicating whether the insert was successful.
	*/
	bool addNews(string company, Date d, string newspaper, unsigned short int classification);

	/**
	* A member function that erases a given News by its index in an iteration through the BST.
	* @param The index corresponding to the News to be erased.
	* @return A boolean, true if deletion was successful.
	*/
	bool eraseNews(unsigned idx);

	/**
	* A member function that changes a given News classification by its index in an iteration through the BST.
	* @param idx The index corresponding to the News to be erased.
	* @param num The new classification.
	* @return A boolean, true if change was successful.
	*/
	bool changeNewsClass(unsigned idx, unsigned num);

	/**
	* A member function that prints all Managers to the COUT output stream.
	*/
	void showManagers();

	/**
	* A member function that prints all information about the signed in Manager.
	*/
	void showOwnManager();

	/**
	* A member function that prints all information about the current Manager.
	* @param newpass The new password for the Manager account.
	*/
	void ChangeManagerPassword(string newpass);

	/**
	* A member function that erases the current Manager.
	* @return Bool corresponding to whether delete was successful.
	*/
	bool deleteOwnManager();

	/**
	* A member function that redistributes all Managers over the clients.
	*/
	void redistributeManagers();

	/**
	* A member function that returns the current client's Manager.
	*/
	Manager getClientManager();
	
	/**
	* A member function that adds an order to the unfulfilledOrders vector. Can be from Sell or Buy type.
	* @param o A pointer to the order.
	*/
	pair< vector<Transaction *>::iterator, vector<Transaction *>::iterator > placeOrder(Order * o);	// Abstracts of Buy/Sell type
	
	/**
	*	A member function that saves ALL information to the files.
	*/
	void saveChanges();

	/**
	* Overload of Operator << for class Market.
	* Prints the Market statistics.
	* @param out The outstream to write to.
	* @param m The Market.
	* @return Returns the output stream to allow chaining
	*/
	friend ostream& operator<<(ostream & out, const Market & m);
};

