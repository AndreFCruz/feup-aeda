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
	uint sellerNIF;
	uint buyerNIF;
	string stock;
	double value;
	unsigned quantity;
	Date time_stamp;

public:
	Transaction() = default;
	Transaction(ifstream&);
	Transaction(uint buyerNIF, uint sellerNIF, string stock, double value, unsigned quantity);
	unsigned getQuantity() const;
	Date getDate() const;
	void saveChanges(ofstream&) const;

	friend ostream& operator<<(ostream&, const Transaction&);
};

ostream& operator<<(ostream&, const Transaction&);