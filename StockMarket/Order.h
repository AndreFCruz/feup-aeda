#pragma once

#include "Date.h"
#include "Client.h"

using namespace std;

/*
Super Class to represent an ORDER
*/
class Order
{
	Date placed;
	string stock;
	double valuePerStock;	// Value per stock, in cents

public:
	Order(string, double);
	virtual ~Order() = default;
	Date getDatePlaced() const;
	double getValue() const;

	virtual Transaction * operator()(Order*) const = 0;	// Useful? TBD

	class InvalidValue {
		double value;
	public:
		InvalidValue(double value) : value(value) {}
		double getValue() const {
			return value;
		}
	};
};

class BuyOrder : public Order
{
	Client * buyer;

public:
	BuyOrder(Client*, string, double val, unsigned quantity);
	Transaction * operator()(Order*) const;
};

class SellOrder : public Order
{
	Client * seller;

public:
	SellOrder(Client*, string, double val);
	Transaction * operator()(Order*) const;
};
