#pragma once

#include <string>
#include <vector>
#include "Transaction.h"
#include "defs.h"

using namespace std;

class Transaction;	// Forward declaration due to circular includes

/*
Class to represent a client
*/
class Client
{
	string name;
	nif_t nif;

public:
	Client() = default;
	Client(ifstream&);
	Client(string, nif_t);
	string getName() const;
	nif_t getNIF() const;
	void saveChanges(ofstream&) const;

	class InvalidNIF
	{
		nif_t nif;
	public:
		InvalidNIF(nif_t nif) : nif(nif) {}
		nif_t getNIF() const {
			return nif;
		}
	};
};

ostream& operator<<(ostream&, const Client&);
