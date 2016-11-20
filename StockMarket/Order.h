#pragma once

#include "Date.h"
#include "Client.h"
#include "defs.h"

using namespace std;

/*
Super Class to represent an ORDER
*/

/**
*  A super class used to represent an order.
*/
class Order
{
protected:
	string stock;			/**< string stock. A string with stock name. */
	double valuePerStock;	/**< valuePerStock. A double with the stock value. */
	unsigned quantity;		/**< unsigned quantity. An unsigned with the stock quantity.*/
	Date datePlaced;		/**< Date datePlaced. The date when the order was placed. */

public:
	
	/**
	* A constructor.
	* The construtor creates an order object, reading the data from the input stream passed as argument.
	* @param in The input stream to read from in order to build the order object.
	*/
	Order(ifstream& in);

	/**
	* A constructor.
	* The construtor creates an order object using the data passed as arguments.
	* @param s A string with the stock name.
	* @param value A double with the value per stock.
	* @param quant An unsigned with the stock quantity.
	*/
	Order(string s, double value, unsigned quant);

	/**
	* A virtual destructor.
	*/
	virtual ~Order() = default;

	/**
	* A const member function with no arguments to get the orders's place date.
	* @return A Date object , the date when the order was placed.
	*/
	Date getDatePlaced() const;

	/**
	* A const member function with no arguments to get the orders's stock name.
	* @return A string that is the name of the stock.
	*/
	string getStock() const;

	/**
	* A const member function with no arguments to get the value per stock.
	* @return A double, the value per stock.
	*/
	double getValue() const;

	/**
	* A const member function with no arguments to get the order stock quantity.
	* @return An unsigned, the quantity of stock.
	*/
	unsigned getQuantity() const;

	/**
	* A const member function that prints the order information.
	*/
	void printInfo() const;
	
	//virtual nif_t getClientNIF() = 0;

	/**
	*	A virtual definition of operator()
	*/
	virtual Transaction * operator()(Order*) = 0;

	/**
	*	A virtual function to save changes
	*/
	virtual void saveChanges(ofstream& out) const;

	/**
	*  A class used to represent an exception, InvalidValue.
	*  The object from InvalidValue class contains the invalid value stored.
	*/
	class InvalidValue {
		double value;
	public:
		InvalidValue(double value) : value(value) {}
		double getValue() const {
			return value;
		}
	};
};

class SellOrder;

class BuyOrder : public Order
{
	friend SellOrder;
	nif_t buyerNIF;		/**< nif_t buyerNIF. The NIF of the buyer. */

public:

	/**
	* A constructor.
	* The construtor creates a BuyOrder object, reading the data from the input stream passed as argument.
	* @param in The input stream to read from in order to build the BuyOrder object.
	*/
	BuyOrder(ifstream& in);

	/**
	* A constructor.
	* The construtor creates a BuyOrder object using the data passed as arguments.
	* @param stock A string with the stock name.
	* @param val A double with the value per stock.
	* @param quantity An unsigned with the stock quantity.
	* @param bueyrNIF The buyer NIF.
	*/
	BuyOrder(string stock, double val, unsigned quantity, nif_t buyerNIF);
	//nif_t getClientNIF() const;

	/**
	*	Overload of operator() for class Order. 
	*	@param o Pointer of an object Order.
	*	@return A transaction type object.
	*/
	Transaction * operator()(Order* o);

	/**
	*	A const memeber function to save changes in an output stream.
	*   @param out The outstream file to write to.
	*/
	void saveChanges(ofstream& out) const;
};

class SellOrder : public Order
{
	friend BuyOrder;
	nif_t sellerNIF;   /**< nif_t sellerNIF. The NIF of the seller. */

public:

	/**
	* A constructor.
	* The construtor creates a SellOrder object, reading the data from the input stream passed as argument.
	* @param in The input stream to read from in order to build the SellOrder object.
	*/
	SellOrder(ifstream& in);

	/**
	* A constructor.
	* The construtor creates a SellOrder object using the data passed as arguments.
	* @param stock A string with the stock name.
	* @param val A double with the value per stock.
	* @param quantity An unsigned with the stock quantity.
	* @param sellerNIF The seller's NIF.
	*/
	SellOrder(string stock, double val, unsigned quantity, nif_t sellerNIF);
	//nif_t getClientNIF() const;

	/**
	*	Overload of operator() for class Order.
	*	@param o Pointer of an object Order.
	*	@return A transaction type object.
	*/
	Transaction * operator()(Order* o);

	/**
	*	A const memeber function to save changes in an output stream.
	*   @param out The outstream file to write to.
	*/
	void saveChanges(ofstream& out) const;
};
