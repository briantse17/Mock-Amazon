#include <iostream>
#include <string>


unsigned long long hashFunc(std::string password)
{
	unsigned long long hashnum = 0;
	for (int i = 0; i < int(password.size()); i++)
	{ 
		hashnum = int(password[i]) + 128*hashnum;
	}
	unsigned int digits[4] = {0,0,0,0};
	int counter = 3;
	while(hashnum != 0)
	{
		digits[counter] = hashnum%65521;
		hashnum = hashnum/65521;
		counter--;
	}
	unsigned long long finalPass = (45912 * digits[0] + 35511 * digits[1] + 65169 * digits[2] + 4625 * digits[3]) % 65521;
	return finalPass;
}
