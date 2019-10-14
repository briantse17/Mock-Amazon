#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type, unsigned long long password) :
    name_(name), balance_(balance), type_(type), password_(password)
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

unsigned long long User::getPass() const
{
	return password_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << password_ <<endl;
}

std::map<std::string, int> User::getUserRevs()
{
	return userRevs;
}

void User::addUserRev(std::string name, int rating)
{
	userRevs.insert(make_pair(name, rating));
}

std::set<std::string> User::getUserProd()
{
	return userProd;
}

void User::addUserProd(std::string name)
{
	userProd.insert(name);
}

