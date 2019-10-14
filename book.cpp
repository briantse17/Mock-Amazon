#include "book.h"

using namespace std;

Book::Book (const string category, const string name, double price, int quant, string isbn, string author) 
: Product(category, name, price, quant)
{
	isbn_ = isbn;
	author_ = author;
}


Book::~Book()
{

}


set<string> Book::keywords() const
{
	set<string> s3;
	set<string> s1 = parseStringToWords(name_);
	typename set<string>:: iterator it = s1.begin();
	while(it!=s1.end())
	{
		s3.insert(*it);
		it++;
	}
	set<std::string> s2 = parseStringToWords(author_);
	typename set<string>:: iterator its = s2.begin();
	while(its!=s2.end())
	{
		s3.insert(*its);
		its++;
	}
	s3.insert(isbn_);
	return s3;
}


string Book::displayString() const
{	
	double average = avgRating();
    stringstream ss;
    ss << fixed << setprecision(2) << average;
    string avg = ss.str();
 	string temp = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left." + "\n" + "Rating: " + avg;
	return temp;
}


void Book::dump(ostream& os) const
{
	string temp = category_ + "\n" + name_ + "\n" + to_string(price_) + "\n" + to_string(qty_) + "\n" + isbn_ + "\n" + author_ + "\n";
	os << temp; 
}
