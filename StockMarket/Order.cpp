#include "Order.h"
#include "utils.h"

/* Order Implementation */

Order::Order(string stock, double value, unsigned quantity) : stock(stock), quantity(quantity)
{
	if (value > 0)
		this->valuePerStock = value;
	else
		throw InvalidValue(value);
}

Date Order::getDatePlaced() const {
	return datePlaced;
}

string Order::getStock() const {
	return stock;
}

double Order::getValue() const {
	return valuePerStock;
}

unsigned Order::getQuantity() const {
	return quantity;
}

void Order::saveChanges(ofstream & out) const {
	out << stock << " ; " << valuePerStock << " ; " << quantity << " ; " << datePlaced << " ; ";
}

/// ///

/* BuyOrder Implementation */
BuyOrder::BuyOrder(string stock, double val, unsigned quantity, uint buyerNIF) : Order(stock, val, quantity), buyerNIF(buyerNIF) {}

//uint BuyOrder::getClientNIF() const {
//	return buyerNIF;
//}

Transaction * BuyOrder::operator()(Order* ord) {
	SellOrder * sellOrd = NULL;

	if (ord->getStock() == this->stock && ord->getValue() <= this->valuePerStock && (sellOrd = dynamic_cast<SellOrder*>(ord)) != NULL) {
		double effectiveVal = (this->valuePerStock + sellOrd->valuePerStock) / 2;
		unsigned effectiveQuant = quantity < sellOrd->quantity ? quantity : sellOrd->quantity;

		Transaction * result = new Transaction(sellOrd->seller, buyer, stock, effectiveVal, effectiveQuant);

		quantity -= sellOrd->quantity;
		sellOrd->quantity -= quantity;

		return result;
	}
	else
		return NULL;
}

void BuyOrder::saveChanges(ofstream & out) const {
	out << "B ";
	Order::saveChanges(out);
	out << buyerNIF << endl;
}

/// ///

/* SellOrder Implementation */
SellOrder::SellOrder(string stock, double val, unsigned quantity, uint sellerNIF) : Order(stock, val, quantity), sellerNIF(sellerNIF) {}

//Client * SellOrder::getClientNIF() const {
//	return sellerNIF;
//}

Transaction * SellOrder::operator()(Order* ord) {
	BuyOrder * buyOrd = NULL;

	if (ord->getStock() == this->stock && ord->getValue() >= this->valuePerStock && (buyOrd = dynamic_cast<BuyOrder*>(ord)) != NULL) {
		double effectiveVal = (this->valuePerStock + buyOrd->valuePerStock) / 2;
		unsigned effectiveQuant = quantity < buyOrd->quantity ? quantity : buyOrd->quantity;

		Transaction * result = new Transaction(buyOrd->buyerNIF, sellerNIF, stock, effectiveVal, effectiveQuant);

		quantity -= buyOrd->quantity;
		buyOrd->quantity -= quantity;

		return result;
	}
	else
		return NULL;
}

void SellOrder::saveChanges(ofstream & out) const {
	out << "S ";
	Order::saveChanges(out);
	out << sellerNIF << endl;
}
/// ///