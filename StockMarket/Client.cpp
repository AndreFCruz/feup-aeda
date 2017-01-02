#include "Client.h"
#include "utils.h"

Client::Client(string name, nif_t nif, string address, string contact) : name(name), address(address), contact(contact)
{
	if (to_string(nif).size() == 9)	// NIF is valid ?
		this->nif = nif;
	else
		throw InvalidNIF(nif);
}

Client::Client(ifstream & in) {
	// Extract Name and NIF
	getline(in, name, ';'); trim(name);
	in >> nif; in.ignore(3, ';');

	// Extract Address
	getline(in, address, ';'); trim(address);

	// Extract Contact Information
	getline(in, contact, ';'); trim(contact);
	in.ignore(3, '\n');
}

string Client::getName() const {
	return name;
}

nif_t Client::getNIF() const {
	return nif;
}

string Client::getContact() const {
	return contact;
}

bool Client::setAddress(string address) {
	if (address.empty())
		return false;

	this->address = address;
	return true;
}

bool Client::setContact(string contact) {
	if (contact.empty())
		return false;

	this->contact = contact;
	return true;
}

void Client::saveChanges(ofstream & out) const {
	out << name << " ; " << nif << " ; " << address << " ; " << contact << " ;\n";
}

ostream& operator<<(ostream & out, const Client & cli) {
	return out << "Client's name: " << cli.getName() << ". Client's NIF: " << cli.getNIF()
		<< ". Client's Contact: " << cli.getContact() << endl;
}