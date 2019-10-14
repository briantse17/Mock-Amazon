#include "datastore.h"
#include <map>
#include <set>
#include "util.h"
#include "user.h"
#include "book.h"
#include "review.h"
#include <vector>
#include <iostream>
#include <fstream>



class myDataStore: public DataStore

{
public:
	myDataStore();

	~myDataStore();

	void addProduct(Product* p);

	void addUser(User* u);

	std::vector<Product*> search(std::vector<std::string>& terms, int type, std::string check);

	void dump(std::ostream& ofile);

	void addCart(std::string username, Product* p);

	void viewCart(std::string username);

	void buyCart(std::string username);

	void addReview(const std::string& prodName,
			   int rating,
			   const std::string& username,
			   const std::string& date,
			   const std::string& review_text);
	void viewReview(Product* product, std::string username);

	std::vector<std::pair<std::string, double> > makeSuggestion(std::string currentUser);
	void basicSims();
	std::vector<std::pair<std::string, double>> refinedSims(std::string username);


public:
	//stores users and their specific carts
	std::map<User*, std::vector<Product*>> umap;
	//stores keywords and their respective products
	std::map<std::string, std::set<Product*>> pmap;
	//stores all products created
	std::vector<Product*> allproducts;
	//stores all users created
	std::vector<User*> allusers;
	//adjacency list for basic similarities between users
	std::map<std::string, std::vector<std::pair<std::string, double>>> allsims;

};

