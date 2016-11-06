#pragma once

#include "Date.h"
#include "Client.h"

using namespace std;

/*
Super Class to represent an ORDER
*/
class Order
{
protected:
	Date placed;
	string stock;
	double valuePerStock;	// Value per stock
	unsigned quantity;

public:
	Order(string, double, unsigned);
	virtual ~Order() = default;
	Date getDatePlaced() const;
	string getStock() const;
	double getValue() const;
	unsigned getQuantity() const;
	
	virtual Client * getClientPtr() = 0;
	virtual Transaction * operator()(Order*) = 0;	// Useful? TBD

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
	Client * buyer;

public:
	BuyOrder(string stock, double val, unsigned quantity, Client* buyer);
	Client * getClientPtr();
	Transaction * operator()(Order*);
};

class SellOrder : public Order
{
	friend BuyOrder;
	Client * seller;

public:
	SellOrder(string stock, double val, unsigned quantity, Client* seller);
	Client * getClientPtr();
	Transaction * operator()(Order*);
};
