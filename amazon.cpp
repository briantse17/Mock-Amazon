#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "mydatastore.h"


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


using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    myDataStore ds;

    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;
    ReviewSectionParser* reviewSectionParser = new ReviewSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);
    parser.addSectionParser("reviews", reviewSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "============================================" << endl;
    cout << "Menu: " << endl;
    cout << "  LOGIN username password                   " << endl;
    cout << "  LOGOUT                                    " << endl;
    cout << "  AND r/n term term ...                     " << endl;
    cout << "  OR r/n term term ...                      " << endl;
    cout << "  ADD search_hit_number                     " << endl;
    cout << "  VIEWCART                                  " << endl;
    cout << "  BUYCART                                   " << endl;
    cout << "  ADDREV search_hit_number rating YYYY-MM-DD review_text" << endl;
    cout << "  VIEWREV search_hit_number                 " << endl;
    cout << "  REC                                       " << endl;
    cout << "  QUIT new_db_filename                      " << endl;
    cout << "============================================" << endl;

    vector<Product*> hits;
    bool done = false;
    string loginName = "";
    string password = "";
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string check;
                ss >> check;
                if(check != "r" && check != "n")
                {
                    continue;
                }
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0, check);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string check;
                ss >> check;
                if(check != "r" && check != "n")
                {
                    continue;
                }
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1, check);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            else if (cmd == "LOGIN")
            {
                bool found = false;
                if(ss >> loginName)
                {
                    for(int i = 0; i < int(ds.allusers.size()); i++)
                    {
                        if(loginName == ds.allusers[i]->getName())
                        {
                            if(ss >> password)
                            {
                                if(ds.allusers[i]->getPass() == hashFunc(password))
                                {
                                    found = true;
                                    cout << "User logged in" << endl;
                                }
                            }
                            //if user entered an incorrect password
                            else
                            {
                                password = "";
                                cout << "Invalid login credentials" << endl;
                                found = true;
                                break;
                            }
                        }
                    }
                    //if username does not match any in database
                    if(!found)
                    {
                        loginName = "";
                        cout << "Invalid login credentials" << endl;
                        continue;
                    }

                }
                //if user did not enter a username
                else
                {
                    cout << "Invalid user" << endl;
                    continue;
                }
            }
            else if (cmd == "LOGOUT")
            {
                if (loginName == "")
                {
                    cout << "No current user" << endl;
                }
                else
                {
                    loginName = "";
                }
            }

            else if (cmd == "REC")
            {
                vector<pair<string, double>> recommendations = ds.makeSuggestion(loginName);
                if(recommendations.empty())
                {
                    cout <<"No recommendations available" << endl;
                    continue;
                }
            }

            else if ( cmd == "BUYCART")
            {
                //string username;
                //ss >> username;
                if(loginName == "")
                {
                    cout << "No current user" << endl;
                    continue;
                }
                else
                {
                    ds.buyCart(loginName);
                }
            }
            else if ( cmd == "VIEWCART")
            {
                //string username;
                //ss >> username;
                if(loginName == "")
                {
                    cout << "No current user" << endl;
                    continue;
                }
                else
                {
                    ds.viewCart(loginName);
                }
            }
            else if ( cmd == "ADD")
            {
                //string username;
                int index;
                //ss >> username;
                ss >> index;
                if(loginName == "")
                {
                    cout << "No current user" << endl;
                    continue;
                }
                //check to see if the index provided is within range of Product vector
                else if(index <= 0 || index-1 > int(hits.size())-1)
                {
                    cout << "Invalid request" << endl;
                    continue;
                }
                else
                {
                    ds.addCart(loginName, hits[index-1]);
                }
            }
            else if ( cmd == "ADDREV")
            {
                if(loginName == "")
                {
                    cout << "No current user" << endl;
                    continue;
                }
                int index;
                int rating;
                string date;
                string review_text;
                if(ss >> index)
                {
                    if(index <= 0 || index-1 > int(hits.size())-1)
                    {
                        cout << "Invalid hit number" << endl;
                        continue;
                    }
                    else if(ss >> rating)
                    {
                        if(rating < 1 || rating > 5)
                        {
                            cout << "Invalid rating" << endl;
                            continue;
                        }
                        else if (ss >> date) 
                        {
                            if(getline(ss, review_text))
                            {
                                //remove leading and ending white space from review
                                trim(review_text);
                                ds.addReview(hits[index-1]->getName(), rating, loginName, date, review_text);
                            }
                        }
                    }
                }
                
            }
            else if( cmd == "VIEWREV")
            {
                int index;
                if(ss >> index)
                {
                    if(index <= 0 || index-1 > int(hits.size())-1)
                    {
                        cout << "Invalid hit number" << endl;
                        continue;
                    }
                    
                    else
                    {
                        ds.viewReview(hits[index-1], loginName);
                    }

                }

            }

            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    //std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}

