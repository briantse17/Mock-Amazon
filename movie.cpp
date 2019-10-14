#include "movie.h"


using namespace std;

Movie::Movie (const string category, const string name, double price, int quant, string genre, string rating) 
: Product(category, name, price, quant)
{
	genre_ = genre;
	rating_ = rating;
}


Movie::~Movie()
{

}


set<string> Movie::keywords() const
{
	set<string> s3;
	set<string> s1 = parseStringToWords(name_);
	typename set<string>:: iterator it = s1.begin();
	while(it!=s1.end())
	{
		s3.insert(*it);
		it++;
	}
	set<string> s2 = parseStringToWords(genre_);
	typename set<string>:: iterator its = s2.begin();
	while(its!=s2.end())
	{
		s3.insert(*its);
		its++;
	}
	return s3;
}


string Movie::displayString() const
{
	double average = avgRating();
	stringstream ss;
    ss << fixed << setprecision(2) << average;
    string avg = ss.str();
	string temp = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ +"\n" + to_string(price_) + " " + to_string(qty_) + " left." + "\n" + "Rating: " + avg;
	return temp;
}


void Movie::dump(ostream& os) const
{
	string temp = category_ + "\n" + name_ + "\n" + to_string(price_) + "\n" + to_string(qty_) + "\n" + genre_ + "\n" + rating_ + "\n";
	os << temp; 
}

