#include <algorithm>
#include "Market.h"
#include "defs.h"
#include "menus.h"
#include "utils.h"


Market* Market::singleton_instance = NULL;

Market::Market() {
	ifstream file_in; string line;
	unsigned numberOfObjects;
	ordersChanged = transactionsChanged = clientsChanged = false;

	while (!initialInfo(clientsFile, transactionsFile, ordersFile)) {
		cout << "\nInvalid StockMarket Initialization ! Carefully type the information required! \a\n\n";
		cout << TAB << "\n Press ENTER to retry..."; cin.ignore(INT_MAX, '\n');
		clearScreen();
	}

	/* Populate Data Structures */
	// Clients from file
	file_in.open(clientsFile);
	file_in >> numberOfObjects;
	for (unsigned i = 0; i < numberOfObjects; ++i) {
		Client * temp_c = new Client(file_in);
		clients.insert(pair<nif_t, Client*>(temp_c->getNIF(), temp_c));
	}
	file_in.close();

	// Transactions from file
	file_in.open(transactionsFile);
	file_in >> numberOfObjects;
	transactions.reserve(numberOfObjects);
	for (unsigned i = 0; i < numberOfObjects; ++i) {
		Transaction * temp_t = new Transaction(file_in);
		transactions.push_back(temp_t);
	}
	file_in.close();
	
	// Sort transactions by chronological order
	sort(transactions.begin(), transactions.end(), [](const Transaction * t1, const Transaction * t2) {return t1->getDate() < t2->getDate(); });

	// Unfulfilled Orders from file
	char c;	// Buy/Sell Char Flag
	file_in.open(ordersFile);
	file_in >> numberOfObjects;
	transactions.reserve(numberOfObjects);
	for (int i = 0; i < numberOfObjects; ++i) {
		Order * temp_o;
		file_in >> c;
		switch (c) {
		case 'B':
			temp_o = new BuyOrder(file_in);
			break;
		case 'S':
			temp_o = new SellOrder(file_in);
			break;
		default:
			cerr << "Invalid Order Identifier in File \"" << ordersFile << "\".\n";
			break;
		}
		unfulfilled_orders.push_back(temp_o);
	}
	file_in.close();
}

Market::~Market() {
	// Warning: Do Not delete from files

	// Delete Clients from Memory
	for (auto p : clients)
		delete p.second;

	// Delete Transactions from Memory
	for (Transaction * t : transactions)
		delete t;

	// Delete Orders from Memory
	for (Order * o : unfulfilled_orders)
		delete o;
}

Market* Market::instance() {
	if (!singleton_instance)
		singleton_instance = new Market;

	return singleton_instance;
}

bool Market::signIn() {
	string name;
	nif_t nif;

	cout << "Name: ";
	getline(cin, name, '\n');
	trim(name);
	cout << "NIF: ";
	cin >> nif;

	for (auto it = clients.begin(); it != clients.end(); ++it) {
		if ((it->first == nif) && ((it->second)->getName() == name)) {
			currentNIF = nif;
			return true;
		}
	}
	return false;
}

bool Market::signUp(string name, nif_t nif) {
	// acrescentar cliente ao map (nif, client*) e mudar currentNIF etc
	Client * newClient = new Client(name, nif);
	clients.insert(pair<nif_t, Client *>(nif, newClient));
	
	currentNIF = nif;
	clientsChanged = true;
	cout << TAB << "New Client created sucessfully!\n"
		 << TAB << "\nPress ENTER to continue..."; cin.ignore(INT_MAX, '\n');	//Re-check
	return true;
}

// Can throw exception, should be handled by higher function
void Market::showClientInfo() const {
	Client * cli = clients.at(currentNIF);

	cout << "Name: " << cli->getName() << ". NIF: " << cli->getNIF() << endl;
}

// Can throw exception, should be handled by higher function
void Market::showClientHistory() const {
	Client * cli = clients.at(currentNIF);
	cout << *cli;

	for (Transaction * t_ptr : clientHistory(cli))
		cout << *t_ptr;
}

vector<Transaction *> Market::clientHistory(Client * c_ptr) const {
	vector<Transaction *> result;
	for (Transaction * t_ptr : transactions) {
		if (t_ptr->getBuyerNIF() == c_ptr->getNIF() || t_ptr->getSellerNIF() == c_ptr->getNIF())
			result.push_back(t_ptr);
	}

	return result;
}

void Market::printTransactions(ostream & out) const
{
	for (Transaction * t : transactions) {
		out << *t;
	}
}

void Market::listTransactions(Date day1, Date day2) {

	for (size_t i = 0; i < transactions.size(); i++) {
		Date d = transactions.at(i)->getDate();
		
		if (isBetween(d, day1, day2))
			cout << transactions.at(i);
	}

}

void Market::listDailyTransactions(Date d) {

	for (size_t i = 0; i < transactions.size(); i++) {
		if (transactions.at(i)->getDate() == d)
			cout << transactions.at(i);
	}
}

void Market::listBuyOrders() const {
	for (Order * ptr : unfulfilled_orders) {
		if (dynamic_cast<BuyOrder*>(ptr) != NULL)
			ptr->printInfo();
	}
}

void Market::listSellOrders() const {
	for (Order * ptr : unfulfilled_orders) {
		if (dynamic_cast<SellOrder*>(ptr) != NULL)
			ptr->printInfo();
	}
}

// wtf isto devia estar na implementacao do menu. E btw nao devia ser possivel adicionar transacoes, so qd ordens sao fulfilled
//void Market::addTransaction() {
//	
//	nif_t buyer, seller;
//	string stock;
//	double val;
//	unsigned quant;
//
//	cout << "Buyer NIF: ";
//	cin >> buyer; cin.ignore();
//
//	cout << "Seller NIF: ";
//	cin >> seller; cin.ignore();
//
//	cout << "Stock: ";
//	getline(cin, stock);
//
//	cout << "Value: ";
//	cin >> val; cin.ignore();
//
//	cout << "Quantity: ";
//	cin >> quant; cin.ignore();
//
//	Transaction *t = new Transaction(buyer, seller, stock, val, quant);
//
//	transactions.push_back(t);
//}

/* To Delete (?) */
//bool Market::placeBuyOrder(Client * buyer, string stock, double value, unsigned quantity)
//{
//	Order * ptr = new BuyOrder(stock, value, quantity, buyer);	// exception can be thrown, should be handled by higher level function
//
//	for (unsigned i = 0; i < unfulfilled_orders.size(); i++) {
//		Transaction * trans;
//		if ((trans = (*unfulfilled_orders[i])(ptr)) != NULL) {	// Transaction Successful ?
//			transactions.push_back(trans);
//
//			// Corresponding Sell Order Fulfilled ?
//			if (unfulfilled_orders[i]->getQuantity() == 0) {
//				delete unfulfilled_orders[i];
//				unfulfilled_orders.erase(unfulfilled_orders.begin() + i);
//			}
//			if (0 == quantity) {
//				delete ptr;
//				return true;
//			}
//		}	// Memory Leak ?
//	}
//	return false;
//}

// Returns pair< vector<Transaction *>::iterator, vector<Transaction *>::iterator >
auto Market::placeOrder(Order * ptr)
{
	typedef vector<Transaction *>::iterator transIt;
	size_t initialSize = transactions.size();
	for (unsigned i = 0; i < unfulfilled_orders.size(); i++) {
		Transaction * trans;
		if ((trans = (*unfulfilled_orders[i])(ptr)) != NULL) {	// Transaction Successful ?
			transactions.push_back(trans);
			
			// Corresponding Buy/Sell Order Fulfilled ?
			if (unfulfilled_orders[i]->getQuantity() == 0) {
				delete unfulfilled_orders[i];
				unfulfilled_orders.erase(unfulfilled_orders.begin() + i);
			}
			if (0 == ptr->getQuantity()) {
				delete ptr;
				break;
			}
		}
	}
	ordersChanged = true;
	if (transactions.size() > initialSize) {
		transactionsChanged = true;
		return pair<transIt, transIt>(transactions.begin() + initialSize, transactions.end());
	}

	return pair<transIt, transIt> (transactions.end(), transactions.end());
}

void Market::addBuyOrder()
{
	//Getting the info from the user
	string stock;
	double val;
	unsigned quantity;

	cout << TAB << "Adding a new Buy Order...\nStock: ";
	getline(cin, stock);
	trim(stock);
	cout << "Stock's value: ";
	cin >> val; cin.ignore();	//Falta a gestão de inputs errados (ex. a5a6)
	cout << "Quantity: ";
	cin >> quantity; cin.ignore();	//Gestao inputs

	Order * newOrder = new BuyOrder(stock, val, quantity, currentNIF);
	unfulfilled_orders.push_back(newOrder);		//Ao fim de meia hora n vejo onde o se faz a atualização do unfulfilledorders, que dps e usado no placeORder.. Re-verificar
	auto result = placeOrder(newOrder);
	
	bool fullfilled = true;
	if (result.first != result.second) {	//Transitions were made
		for (unsigned int i = 0; i < unfulfilled_orders.size(); i++) {
			if (unfulfilled_orders.at(i) == newOrder)
				fullfilled = false;			//Buy Order not fully fullfilled
		}
		if (fullfilled)
			cout << "Your order was instantly fullfilled!\n";
		else
			cout << "Your order was partially fullfilled. Waiting for more Sell Orders to completely fullfill it!\n";

		cout << "Transactions that were made:\n ";
		while (result.first != result.second)	//Showing the transactions made
		{
			cout << *result.first;	//Well-Done? Possibly not
			result.first++;
		}
	}
	else
		cout << "Waiting for Sell Orders to fullfill your order!\n";

}

void Market::addSellOrder()
{
	//Getting the info from the user
	string stock;
	double val;
	unsigned quantity;

	cout << TAB << "Adding a new Sell Order...\nStock: ";
	getline(cin, stock);
	trim(stock);
	cout << "Stock's value: ";
	cin >> val; cin.ignore();	//Falta a gestão de inputs errados (ex. a5a6)
	cout << "Quantity: ";
	cin >> quantity; cin.ignore();	//Gestao inputs

	Order * newOrder = new SellOrder(stock, val, quantity, currentNIF);
	unfulfilled_orders.push_back(newOrder);		//Ao fim de meia hora n vejo onde o se faz a atualização do unfulfilledorders, que dps e usado no placeORder.. Re-verificar
	auto result = placeOrder(newOrder);

	bool fullfilled = true;
	if (result.first != result.second) {	//Transitions were made
		for (unsigned int i = 0; i < unfulfilled_orders.size(); i++) {
			if (unfulfilled_orders.at(i) == newOrder)
				fullfilled = false;			//Order not fully fullfilled
		}
		if (fullfilled)
			cout << "Your order was instantly fullfilled!\n";
		else
			cout << "Your order was partially fullfilled. Waiting for more Buy Orders to completely fullfill it!\n";

		cout << "Transactions that were made:\n\n";
		while (result.first != result.second)	//Showing the transactions made
		{
			cout << *(*result.first) << endl;	//Well-Done? Possibly not
			result.first++;
		}
	}
	else
		cout << "Waiting for Buy Orders to fullfill your order!\n";
}

void Market::saveChanges() const {
	ofstream out;

	// Save Clients if Changed
	if (clientsChanged) {
		out.open(clientsFile);
		out << clients.size();

		for (auto p : clients)
			p.second->saveChanges(out);

		out.close();
	}

	// Save Transactions if Changed
	if (transactionsChanged) {
		out.open(transactionsFile);
		out << transactions.size();

		for (Transaction * ptr : transactions)
			ptr->saveChanges(out);

		out.close();
	}

	// Save Orders if Changed
	if (ordersChanged) {
		out.open(ordersFile);
		out << unfulfilled_orders.size();

		for (Order * ptr : unfulfilled_orders)
			ptr->saveChanges(out);

		out.close();
	}
}

ostream& operator<<(ostream & out, const Market & m) {
	out << "Place Holder for StockMarket Statistics.\n";
	return out;
}