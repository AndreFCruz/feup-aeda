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
	string company;		/**< string company. The name of the company mentioned in the news */
	Date date;			/**< Date date. The date when it was published */
	string newspaper;	/**< string newspaper. The name of the newspaper that published the news. */
	unsigned short int classification;	/**< unsigned short int classification. The news' classification,
										from 0 to 10, indicating whether its good (10) or bad (0) */

public:

	/**
	* Explicit default constructor.
	*/
	News() = default;

	/**
	* Constructor for News object.
	* The construtor creates a News object, with the data supplied as arguments.
	* @param company The name of the company mentioned.
	* @param d The date when the news was published.
	* @param newspaper The name of the newspaper where the news was published.
	* @param classification The News' classification, from bad (0) to good (10).
	*/
	News(string company, Date d, string newspaper, unsigned short int classification);

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
	* A const member function with no arguments to get the News' Company name.
	* @return A string, the Company's name.
	*/
	string getCompany() const;

	/**
	* A const member function with no arguments to get the Date the news was published.
	* @return A Date object, with the information regarding when the news was published.
	*/
	Date getDate() const;

	/**
	* A const member function with no arguments to get the News' Newspaper name.
	* @return A string, the Newspaper's name.
	*/
	string getNewspaper() const;

	/**
	* A const member function with no arguments to get the News' Classification.
	* @return An unsigned short int, corresponding to the News classification, from bad (0) to good (10).
	*/
	unsigned short int getClassification() const;

	/**
	* Overload of Output Operator << for class News.
	* Prints the News' information in a human friendly way.
	* @param out The outstream to write to.
	* @param n The News to be written.
	* @return Returns the output stream to allow chaining
	*/
	friend ostream& operator<<(ostream& out, const News& n);

	/**
	* Overload of Operator < for class News.
	* @param d1 First News
	* @param d2 Second News
	* @return Returns a boolean value, true if n1 < n2
	*/
	friend bool operator<(const News & n1, const News & n2);
};

