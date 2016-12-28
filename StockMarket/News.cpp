#include <iomanip>
#include "News.h"
#include "utils.h"


News::News(string company, Date d, string newspaper, unsigned short int classification) :
	company(company), date(d), newspaper(newspaper), classification(classification) {};

News::News(ifstream& in) {
	string s;

	// Extract Company's Name
	getline(in, s, ';');
	company = s;
	trim(company);

	// Extract Date
	in >> date;
	in.ignore(5, ';');

	// Extract Newspaper's Name
	getline(in, s, ';');
	newspaper = s;
	trim(newspaper);

	// Extract News' Classification
	in >> classification;

	in.ignore(5, '\n');
}

void News::saveChanges(ofstream& out) const {
	out << company << " ; " << date << " ; " << newspaper << " ; " << classification << endl;
}

string News::getCompany() const {
	return this->company;
}

Date News::getDate() const {
	return this->date;
}

string News::getNewspaper() const {
	return this->newspaper;
}

unsigned short int News::getClassification() const {
	return this->classification;
}

void News::setClassification(unsigned short int c) {
	this->classification = c;
}

ostream& operator<<(ostream& out, const News& n) {
	out << setw(20) << n.company << ". Date Published: " << n.date << ". Classification: "
		<< setw(2) << n.classification << ". Newspaper: " << setw(20) << n.newspaper << endl;
	return out;
}

bool operator<(const News & n1, const News & n2) {
	if (n1.company != n2.company)
		return n1.company < n2.company;
	else if (n1.date != n2.date)
		return n1.date < n2.date;
	else
		return n1.newspaper < n2.newspaper;
}