#include "Transaction.h"
#include "utils.h"
#include "defs.h"

Transaction::Transaction(uint buyerNIF, uint sellerNIF, string stock, double value, unsigned quantity) :
	sellerNIF(sellerNIF), buyerNIF(buyerNIF), stock(stock), value(value), quantity(quantity) {}

// Constructs Transaction from Input FileStream
Transaction::Transaction(ifstream& in) {
	string s;
	
	// Extract Stock Name
	getline(in, s, ';'); trim(s);
	stock = s;

	// Extract Clients' NIFs
	in.ignore(3, 'S'); // Extract 'S' (Seller)
	in >> sellerNIF;
	in.ignore(3, 'B'); // Extract 'B' (Buyer)
	in >> buyerNIF;
	in.ignore(3, ';');

	// Extract Value
	in >> value;
	in.ignore(3, ';');

	// Extract Quantity
	in >> quantity;
	in.ignore(3, ';');

	// Extract Date
	in >> time_stamp;
	in.ignore(3, '\n');
}

void Transaction::saveChanges(ofstream & out) const {
	out << stock << " ; " << 'S' << sellerNIF << " ; " << 'B' << buyerNIF << " ; "
		<< value << " ; " << quantity << " ; " << time_stamp << endl;
}

unsigned Transaction::getQuantity() const {
	return quantity;
}

Date Transaction::getDate() const {
	return time_stamp;
}

ostream& operator<<(ostream & out, const Transaction & t)
{
	out << "Seller NIF: " << t.sellerNIF << ". Buyer NIF: " << t.buyerNIF << ".\n"
		<< "Transactioned " << t.quantity << "stocks of " << t.stock << " at " << t.value << "." << endl
		<< "Time Stamp: " << t.time_stamp << endl << endl;
	return out;
}