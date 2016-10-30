#include "Client.h"

Client::Client(string name, unsigned int nif) : name(name)
{
	if (to_string(nif).size() == 9)	// NIF is valid ?
		this->nif = nif;
	else
		throw InvalidNIF(nif);
}

string Client::getName() const {
	return name;
}

unsigned int Client::getNIF() const {
	return nif;
}

vector<Transaction *> Client::getHistory() {
	return history;
}

void Client::addTransaction(Transaction * t) {
	history.push_back(t);
}

