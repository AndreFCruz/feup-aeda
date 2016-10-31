#include "Order.h"

Order::Order(string stock, double value) : stock(stock)
{
	if (value > 0)
		this->valuePerStock = value;
	else
		throw InvalidValue(value);
}

