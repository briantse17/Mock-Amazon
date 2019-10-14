#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    string lowRawWords = convToLower(rawWords);
    //start holds index at which we want to begin parsing from
    int start = 0;
    std::set<string> temp;

    for (unsigned int i = 0; i < lowRawWords.size(); i++)
    {
        string keyword;
        //check specifically for '-' since it may be contained between numbers in ISBN, should be included
        if(lowRawWords[i] == '-')
        {
            continue;
        }
        //checks to see if current char is a numerical or alphabetical number and if we're at end of string
        if(!isalnum(lowRawWords[i]) || i == lowRawWords.size()-1)
        {
            if(i == lowRawWords.size()-1)
            {
                i++;
            }
            //if substring is less than 2 letters
            if (i - start < 2)
            {
                //skip the next char since it is too short and continue parsing    
                start = i+1;
                continue;  
            }
            else
            {
                keyword = lowRawWords.substr(start, i-start);
                temp.insert(keyword);
                start = i+1;
            }
        }
    }
 return temp;
}


std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

