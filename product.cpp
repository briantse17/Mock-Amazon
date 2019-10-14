#include <sstream>
#include <iomanip>
#include "product.h"
#include "msort.h"

using namespace std;

struct compDate {
  bool operator()(Review a, Review b)
  {
   if(a.date > b.date)
    {
        return true;
    }
    else 
    {
        return false;
    }
  }
};


Product::Product(const std::string category, const std::string name, double price, int qty) :
    name_(name),
    price_(price),
    qty_(qty),
    category_(category)
{

}

Product::~Product()
{

}


double Product::getPrice() const
{
    return price_;
}

std::string Product::getName() const
{
    return name_;
}

void Product::subtractQty(int num)
{
    qty_ -= num;
}

int Product::getQty() const
{
    return qty_;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Product::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

void Product::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}

void Product::dumpRev(std::ostream&os) const
{
    for(int i = 0; i < int(reviews.size()); i++)
    {
        os << name_ << "\n" << reviews[i].rating << " " << reviews[i].username << " " << reviews[i].date << " " << reviews[i].reviewText << "\n";
    }
}

void Product::addRev(int rating,
               const std::string& username,
               const std::string& date,
               const std::string& review_text)
{
    reviews.push_back(Review(rating, username, date, review_text));
}

void Product::getRev(string username)
{
    compDate c3;
    mergeSort(reviews, c3);
    for (int i = 0; i < int(reviews.size()); i++)
    {
        cout << reviews[i].date << " " << reviews[i].rating << " " << reviews[i].username << " " << reviews[i].reviewText << endl;
    }
}

double Product::avgRating() const
{
    if(reviews.size() == 0)
    {
        return 0;
    }
    double sum = 0;
    int size = 0;
    double average = 0;
    for(int i = 0; i < int(reviews.size()); i++)
    {
        sum += reviews[i].rating;
        size++;
    }
    average = double(sum/size);
    return average;
}


vector<Review> Product::getReview()
{
    return reviews;
}