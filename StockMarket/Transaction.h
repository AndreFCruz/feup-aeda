#pragma once

#include <iostream>
#include "Client.h"
#include "Date.h"

class Client;

/*
Class to represent a transaction
*/
class Transaction
{
	Client * seller;
	Client * buyer;
	string stock;
	double value;
	unsigned quantity;
	Date time_stamp;

public:
	Transaction() = default;
	Transaction(Client * seller, Client * buyer, string stock, double value, unsigned quantity);
	unsigned getQuantity() const;

	friend ostream& operator<<(ostream&, const Transaction&);
};
