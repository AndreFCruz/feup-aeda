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
	unsigned int nif;

public:
	Client() = default;
	Client(string, unsigned int);
	string getName() const;
	unsigned int getNIF() const;

	class InvalidNIF
	{
		unsigned int nif;
	public:
		InvalidNIF(unsigned int nif) : nif(nif) {}
		unsigned int getNIF() const {
			return nif;
		}
	};
};
