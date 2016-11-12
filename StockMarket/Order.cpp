#include "Order.h"

/* Order Implementation */

Order::Order(string stock, double value, unsigned quantity) : stock(stock), quantity(quantity)
{
	if (value > 0)
		this->valuePerStock = value;
	else
		throw InvalidValue(value);
}

Date Order::getDatePlaced() const {
	return placed;
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

/// ///

/* BuyOrder Implementation */
BuyOrder::BuyOrder(string stock, double val, unsigned quantity, Client* buyer) : Order(stock, val, quantity), buyer(buyer) {}

Client * BuyOrder::getClientPtr() {
	return buyer;
}

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

/// ///

/* BuyOrder Implementation */
SellOrder::SellOrder(string stock, double val, unsigned quantity, Client* buyer) : Order(stock, val, quantity), seller(seller) {}

Client * SellOrder::getClientPtr() {
	return seller;
}

Transaction * SellOrder::operator()(Order* ord) {
	BuyOrder * buyOrd = NULL;

	if (ord->getStock() == this->stock && ord->getValue() >= this->valuePerStock && (buyOrd = dynamic_cast<BuyOrder*>(ord)) != NULL) {
		double effectiveVal = (this->valuePerStock + buyOrd->valuePerStock) / 2;
		unsigned effectiveQuant = quantity < buyOrd->quantity ? quantity : buyOrd->quantity;

		Transaction * result = new Transaction(seller, buyOrd->buyer, stock, effectiveVal, effectiveQuant);

		quantity -= buyOrd->quantity;
		buyOrd->quantity -= quantity;

		return result;
	}
	else
		return NULL;
}


/// ///