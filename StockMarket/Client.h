#pragma once

#include <string>
#include <vector>
#include "Transaction.h"

using namespace std;

class Transaction;	// Forward declaration due to circular includes

/*
Class to represent a client
*/
class Client
{
	string name;
	uint nif;

public:
	Client() = default;
	Client(ifstream&);
	Client(string, uint);
	string getName() const;
	uint getNIF() const;
	void saveChanges(ofstream&) const;

	class InvalidNIF
	{
		uint nif;
	public:
		InvalidNIF(uint nif) : nif(nif) {}
		uint getNIF() const {
			return nif;
		}
	};
};
