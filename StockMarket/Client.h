#pragma once

#include <string>
#include <vector>
#include "Transaction.h"

using namespace std;

/*
Class to represent a client
*/
class Client
{
	string name;
	unsigned int nif;
	vector<Transaction *> history;

public:
	Client() = default;
	Client(string, unsigned int);
	string getName() const;
	unsigned int getNIF() const;
	vector<Transaction *> getHistory();
	void addTransaction(Transaction *);

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
