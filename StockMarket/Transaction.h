#pragma once

#include <iostream>
#include "Client.h"
#include "Date.h"
#include "defs.h"

class Client;

/*
Class to represent a transaction
*/
class Transaction
{
	nif_t sellerNIF;
	nif_t buyerNIF;
	string stock;
	double value;
	unsigned quantity;
	Date time_stamp;

public:
	Transaction() = default;
	Transaction(ifstream&);
	Transaction(nif_t buyerNIF, nif_t sellerNIF, string stock, double value, unsigned quantity);
	unsigned getQuantity() const;
	nif_t getSellerNIF() const;
	nif_t getBuyerNIF() const;
	Date getDate() const;
	void saveChanges(ofstream&) const;

	friend ostream& operator<<(ostream&, const Transaction&);
};

ostream& operator<<(ostream&, const Transaction&);