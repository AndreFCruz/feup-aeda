#include "Transaction.h"

Transaction::Transaction(Client * seller, Client * buyer, string stock, double value, unsigned quantity) :
	seller(seller), buyer(buyer), stock(stock), value(value), quantity(quantity) {}

unsigned Transaction::getQuantity() const {
	return quantity;
}

ostream& operator<<(ostream & out, const Transaction & t)
{
	out << "Seller (name/NIF): " << t.seller->getName() << " / " << t.seller->getNIF() << endl
		<< "Buyer (name/NIF): " << t.buyer->getName() << " / " << t.buyer->getNIF() << endl
		<< "Time Stamp: " << t.time_stamp << endl
		<< "Transactioned " << t.quantity << "stocks of " << t.stock << " at " << t.value << "." << endl;
	return out;
}