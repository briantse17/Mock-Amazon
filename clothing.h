#include "product.h"
#include "util.h"
#include <string>
#include <set>
#include <iostream>

class Clothing : public Product
{
public:
	Clothing(const std::string category, const std::string name, double price, int quant, std::string size, std::string brand);

	~Clothing();

	std::set<std::string> keywords() const;

	std::string displayString() const;

	void dump(std::ostream& os) const;

protected:
	std::string size_;
	std::string brand_;
};