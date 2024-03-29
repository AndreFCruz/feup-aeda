#pragma once

#include <string>
#include <vector>
#include "Transaction.h"
#include "defs.h"

using namespace std;

class Transaction;	// Forward declaration due to circular includes

/**
 *  A class used to represent a client. 
 *  Each client object has a name and a nif (from the portuguese "Numero de Identificação Fiscal").
 */
class Client
{
	string name;	/**< string name. The client's name. */
	nif_t nif;		/**< nif_t nif. The client's NIF. */
	string address;	/**< string address. The client's address. */
	string contact;	/**< string contact. The client's contact information. */

public:

	/**
	* Explicit default constructor.
	*/
	Client() = default;

	/**
	* Constructor from file.
	* The construtor creates a Client object, reading the data from the input stream passed as argument.
	* @param in The input stream to read from in order to build the client object.
	*/
	Client(ifstream& in); 

	/**
	* A constructor.
	* The construtor creates a client object with the data passed as arguments.
	* @param name	The client's name.
	* @param nif	The client's NIF.
	* @param address	The client's address.
	* @param contact	The client's contact information.
	*/
	Client(string name, nif_t nif, string address, string contact);

	/**
	* A const member function with no arguments to get the client's name.
	* @return A string, the client's name.
	*/
	string getName() const;

	/**
	* A const member function with no arguments to get the client's contact information.
	* @return A string, the client's contact information.
	*/
	string getContact() const;

	/**
	* A const member function with no arguments to get the client's address.
	* @return A string, the client's current address information.
	*/
	string getAddress() const;

	/**
	* A const member function with no arguments to get the client's NIF.
	* @return A nif_t, the client's NIF.
	*/
	nif_t getNIF() const;

	/**
	* Changes the client's address.
	* @param address The new address.
	* @return A boolean, true if change was successful.
	*/
	bool setAddress(string address);

	/**
	* Changes the client's contact information.
	* @param contact The new contact information.
	* @return A boolean, true if change was successful.
	*/
	bool setContact(string contact);

	/**
	* A const member function that writes the client's info to the output stream.
	* Generally used to save the client's attributes to a file.
	* @param out The output stream to write the client's information.
	*/
	void saveChanges(ofstream& out) const;

	/**
	*  A class used to represent an exception.
	*  The exception object contains the invalid NIF
	*/
	class InvalidNIF
	{
		nif_t nif;
	public:
		/**
		* A constructor.
		* The construtor creates an InvalidNIF object with the supplied NIF.
		* @param nif	The nif in question.
		*/
		InvalidNIF(nif_t nif) : nif(nif) {}

		/**
		* A const member function with no arguments to get the object's NIF.
		* @return A nif_t, the NIF that originated the creation of this object.
		*/
		nif_t getNIF() const {
			return nif;
		}
	};
};


/**
 * Overload of Operator << for class Client.
 * Prints the specified Client (2nd argument) to the outstream passed as 1st argument.
 * @param out The outstream to write to.
 * @param c The client to be written.
 * @return Returns the output stream to allow chaining
 */
ostream& operator<<(ostream& out, const Client& c);

/**
 * A structure to encapsulate the Hash and Comparison functions of Client Pointers.
 */
struct clientPtrHash
{
	/**
	* Hash Function for Client*
	* @param cli Pointer to a Client object.
	* @return hash value.
	*/
	int operator() (const Client * cli) const
	{
		return (int) cli->getNIF();
	}

	/**
	* Comparison Function for Client*
	* @param cli1 Pointer to a Client object.
	* @param cli1 Pointer to a Client object.
	* @return true if Clients pointed by cli1 and cli2 are the same, false otherwise.
	*/
	bool operator() (const Client * cli1, const Client * cli2) const
	{
		return cli1 == cli2; // Two client's are distinct if their pointers are distinct
	}
};