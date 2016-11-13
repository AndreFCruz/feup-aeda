#include "Client.h"
#include "utils.h"

Client::Client(string name, uint nif) : name(name)
{
	if (to_string(nif).size() == 9)	// NIF is valid ?
		this->nif = nif;
	else
		throw InvalidNIF(nif);
}

Client::Client(ifstream & in) {
	getline(in, name, ';'); trim(name);
	in >> nif; in.ignore(3, '\n');
}

string Client::getName() const {
	return name;
}

uint Client::getNIF() const {
	return nif;
}

void Client::saveChanges(ofstream & out) const {
	out << name << " ; " << nif << endl;
}