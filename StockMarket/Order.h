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
	Order(string, double, unsigned);
	virtual ~Order() = default;
	Date getDatePlaced() const;
	string getStock() const;
	double getValue() const;
	unsigned getQuantity() const;
	
	virtual Client * getClientPtr() = 0;
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
	uint buyerNIF;

public:
	BuyOrder(string stock, double val, unsigned quantity, uint buyerNIF);
	//uint getClientNIF() const;
	Transaction * operator()(Order*);
	void saveChanges(ofstream&) const;
};

class SellOrder : public Order
{
	friend BuyOrder;
	uint sellerNIF;

public:
	SellOrder(string stock, double val, unsigned quantity, uint sellerNIF);
	//uint getClientNIF() const;
	Transaction * operator()(Order*);
	void saveChanges(ofstream&) const;
};
