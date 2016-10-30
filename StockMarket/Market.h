#pragma once

/*
 * Singleton Class to implement most of the logic behind the StockMarket
 */

using namespace std;

class Market
{
private:
	Market() = default;
	static Market * singleton_instance;

public:
	static Market * instance();


};
