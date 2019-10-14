#include "product.h"
#include "util.h"
#include <string>
#include <set>
#include <iostream>

class Book : public Product
{
public:
	Book(const std::string category, const std::string name, double price, int quant, std::string isbn, std::string author);

	~Book();

	std::set<std::string> keywords() const;

	std::string displayString() const;

	void dump(std::ostream& os) const;

protected:
	std::string isbn_;
	std::string author_;
};