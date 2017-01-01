#pragma once

#include <string>
#include <vector>
#include "Client.h"
#include "Market.h"

using namespace std;

class Client;	// Forward declaration due to circular includes
class Market;	// Forward declaration due to circular includes

/**
*  A class used to represent a Manager.
*
*/

class Manager
{
	string name;		/**< string name. The name of the Manager */
	string password;	/**< string password. The password of the Manager account */
	vector <Client *> clients;	/**< vector <Client *> clients. The clients that are associated to the Manager */

public:

	/**
	* Explicit default constructor.
	*/
	Manager() = default;

	/**
	* Constructor for Manager object.
	* The construtor creates a Manager object, with the data supplied as arguments.
	* @param name The name of the Manager.
	* @param password The password of the Manager account.
	*/
	Manager(string name, string password);

	/**
	* Constructor from file.
	* The construtor creates a Client object, reading the data from the input stream passed as argument.
	* @param in The input stream to read from in order to build the client object.
	*/
	Manager(ifstream& in);

	/**
	* A const member function that writes the Manager's info to the output stream,
	* used to save the Manager's attributes.
	* @param out The output stream to write the Manager's information.
	*/
	void saveChanges(ofstream& out) const;

	/**
	*  A class used to represent an exception.
	*  The exception object contains the an invalid password
	*/
	class InvalidPassword
	{
		string password;
	public:
		/**
		* A constructor.
		* The construtor creates an InvalidPassword object with the supplied password.
		* @param password	The password in question.
		*/
		InvalidPassword(string password) : password(password) {}

		/**
		* A const member function with no arguments to get the object's password.
		* @return A string, the password that originated the creation of this object.
		*/
		string getPassword() const {
			return password;
		}
	};

	/**
	* A const member function with no arguments to get the Manager's name.
	* @return A string, the Manager's name.
	*/
	string getName() const;

	/**
	* A const member function with no arguments to get the Manager's password. Used for Sign in purposes.
	* @return A string, the Manager's password.
	*/
	string getPassword() const;

	/**
	* A member function with no arguments to get Manager's clients.
	* @return A vector of pointers to Clients, the Manager's clients.
	*/
	vector <Client *> getClients();

	/**
	* A const member function with no arguments to get the Manager's number of clients.
	* @return A unsgined, the Manager's number of clients.
	*/
	unsigned getNumberClients() const;

	/**
	* A member function to change the Manager's password.
	* @param newpass, the Manager's new password.
	*/
	void setPassword(string newpass);

	/**
	* Overload of Output Operator << for class Manager.
	* Prints the Manager's information in a human friendly way.
	* @param out The outstream to write to.
	* @param manager The Manager to be written.
	* @return Returns the output stream to allow chaining.
	*/
	friend ostream& operator<<(ostream& out, const Manager& manager);

	/**
	* Overload of Operator < for class Manager.
	* @param m1 First Manager.
	* @param m2 Second Manager.
	* @return Returns a boolean value, true if m1 < m2.
	*/
	friend bool operator<(const Manager & m1, const Manager & m2);
};