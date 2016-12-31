#include <iomanip>
#include "Manager.h"
#include "utils.h"


Manager::Manager(string name, string password) :
	name(name), password(password) {};

Manager::Manager(ifstream& in) {
	string s;
	string helper;

	//Extract Manager's name
	getline(in, s, ';');
	name = s;
	trim(name);

	//Extract Manager's password
	getline(in, s, ';');
	password = s;
	trim(password);

	//Extracting Manager's clients
	getline(in, s, ';');

	//Extracting every client but the last
	while (s.find(',') != string::npos) {
		helper = s.substr(0, s.find(','));
		trim(helper);

		//Extracting the client out of the NIF
		for (auto it = Market::instance()->clients.begin(); it != Market::instance()->clients.end(); ++it) {
			if (it->first == (nif_t)stoi(helper))
				clients.push_back(it->second);
		}

		s.erase(0, s.find(',') + 1);
	}

	//Getting the last client
	trim(s);

	for (auto it = Market::instance()->clients.begin(); it != Market::instance()->clients.end(); ++it) {
		if (it->first == (nif_t)stoi(helper))
			clients.push_back(it->second);
	}
}

void Manager::saveChanges(ofstream& out) const {
	out << name << " ; " << password << " ; ";
	
	//All Clients but the last one
	for (unsigned i = 0; i < clients.size()-1; ++i) {
		out << clients.at(i)->getNIF() << ", ";
	}

	//Last Client
	out << clients.at(clients.size() - 1)->getNIF() << ";" << endl;
}

string Manager::getName() const {
	return this->name;
}

string Manager::getPassword() const {
	return this->password;
}
vector <Client *> Manager::getClients() const {
	return this->clients;
}

unsigned Manager::getNumberClients() const {
	return (unsigned) this->clients.size();
}

ostream& operator<<(ostream& out, const Manager& manager) {
	out << setw(20) << manager.name << ". Number of Clients: " << setw(3) << manager.getNumberClients() << endl;
	return out;
}

bool operator<(const Manager & m1, const Manager & m2) {
	if (m1.getClients().size() < m2.getClients().size())
		return true;
	else if (m1.getClients().size() > m2.getClients().size())
		return false;
	else if (m1.getClients().size() == m2.getClients().size()) {
		if (m1.getName() < m2.getName())
			return true;
	}
	return false;
}