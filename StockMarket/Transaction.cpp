#include "Transaction.h"

Transaction::Transaction(Client * seller, Client * buyer, string stock) : seller(seller), buyer(buyer), stock(stock) {}

ostream& operator<<(ostream & out, const Transaction & t)
{
	out << "Seller (name/NIF): " << t.seller->getName() << " / " << t.seller->getNIF() << endl
		<< "Buyer (name/NIF): " << t.buyer->getName() << " / " << t.buyer->getNIF() << endl
		<< "Time Stamp: " << t.time_stamp << endl;
	return out;
}