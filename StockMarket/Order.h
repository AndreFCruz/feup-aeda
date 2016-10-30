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
	Date getDatePlaced() const;
	double getValue() const;

	virtual bool operator()() const = 0;	// Overload function operator -- use TBD
};

class BuyOrder : Order
{
	Client * buyer;
};

class SellOrder : Order
{
	Client * seller;
};
