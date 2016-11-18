#pragma once

#include "Date.h"
#include "Client.h"
#include "defs.h"

using namespace std;

/*
Super Class to represent an ORDER
*/
class Order
{
protected:
	string stock;
	double valuePerStock;
	unsigned quantity;
	Date datePlaced;

public:
	Order(ifstream&);
	Order(string, double, unsigned);
	virtual ~Order() = default;
	Date getDatePlaced() const;
	string getStock() const;
	double getValue() const;
	unsigned getQuantity() const;
	void printInfo() const;
	
	//virtual nif_t getClientNIF() = 0;
	virtual Transaction * operator()(Order*) = 0;
	virtual void saveChanges(ofstream&) const;

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
	nif_t buyerNIF;

public:
	BuyOrder(ifstream&);
	BuyOrder(string stock, double val, unsigned quantity, nif_t buyerNIF);
	//nif_t getClientNIF() const;
	Transaction * operator()(Order*);
	void saveChanges(ofstream&) const;
};

class SellOrder : public Order
{
	friend BuyOrder;
	nif_t sellerNIF;

public:
	SellOrder(ifstream&);
	SellOrder(string stock, double val, unsigned quantity, nif_t sellerNIF);
	//nif_t getClientNIF() const;
	Transaction * operator()(Order*);
	void saveChanges(ofstream&) const;
};
