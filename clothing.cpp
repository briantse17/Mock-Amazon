#include "clothing.h"

using namespace std;

Clothing::Clothing (const string category, const string name, double price, int quant, string size, string brand) 
: Product(category, name, price, quant)
{
	size_ = size;
	brand_ = brand;
}


Clothing::~Clothing()
{

}


set<string> Clothing::keywords() const
{
	set<string> s3;
	set<string> s1 = parseStringToWords(name_);
	typename set<string>:: iterator it = s1.begin();
	while(it!=s1.end())
	{
		s3.insert(*it);
		it++;
	}
	set<std::string> s2 = parseStringToWords(brand_);
	typename set<string>:: iterator its = s2.begin();
	while(its!=s2.end())
	{
		s3.insert(*its);
		its++;
	}
	return s3;
}


string Clothing::displayString() const
{
	double average = avgRating();
	stringstream ss;
    ss << fixed << setprecision(2) << average;
    string avg = ss.str();
	string temp = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left." + "\n" + "Rating: " + avg;
	return temp;
}


void Clothing::dump(ostream& os) const
{
	string temp = category_ + "\n" + name_ + "\n" + to_string(price_) + "\n" + to_string(qty_) + "\n" + size_ + "\n" + brand_ + "\n";
	os << temp; 
}

