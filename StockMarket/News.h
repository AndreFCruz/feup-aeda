#pragma once

#include <string>
#include "Date.h"

using namespace std;

/**
 *  A class used to represent a News.
 *  
 */

class News
{
	string newspaper;	/**< string newspaper. The name of the newspaper that  */
	Date date;

public:

	/**
	* Explicit default constructor.
	*/
	News() = default;

	/**
	* Constructor from file.
	* The construtor creates a News object, reading the data from the input stream passed as argument.
	* @param in The input stream to read from in order to build the client object.
	*/
	News(ifstream& in);

	/**
	* A const member function that writes the news' info to the output stream,
	* used to save the news' attributes.
	* @param out The output stream to write the news' information.
	*/
	void saveChanges(ofstream& out) const;

	/**
	* Overload of Operator < for class News.
	* @param d1 First News
	* @param d2 Second News
	* @return Returns a boolean value, true if n1 < n2
	*/
	friend bool operator<(const News & n1, const News & n2);
};

