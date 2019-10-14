#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>


/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type, unsigned long long password);
    virtual ~User();

    double getBalance() const;
    std::string getName() const;
    unsigned long long getPass() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);
    std::map<std::string, int> getUserRevs();
    void addUserRev(std::string name, int rating);
    void addUserProd(std::string name);
    std::set<std::string> getUserProd();

private:
    std::string name_;
    double balance_;
    int type_;
    unsigned long long password_;
    std::map<std::string, int> userRevs;
    std::set<std::string> userProd;
};
#endif
