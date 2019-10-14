- **Name**: Brian Tse
- **USC ID**: 1664305014
- **Email**: briancht@usc.edu

AMAZON PROJECT:
This program simulates the e-commerce website amazon. In order to do this,
the program will offer the following functions to users:
1)LOGIN username password: this will allow the user to login to a specific
account given the right username and password
2)LOGOUT: this will allow users to logout of their account
3)AND r/n term term...:this will allow users to search for products within 
the database that contains all terms specified by user, further, results
will be sorted based on rating or name when users enter r and n 
respectively immediately after the AND term.
4)OR term term...:this will allow users to search for products within the
database that contains at least one of the terms specified by user
5)ADD search_hit_number: this will allow the currently logged in user to 
to a product to their cart
6)VIEWCART: this will allow the currently logged in user to view the 
products within their cart
7)BUYCART: this will allow the current user to purchase all avaiable items
within their cart
8)ADDREV seach_hit_number rating date review_text: this will allow the
current user to add a review to a specific product in the database by 
providing a rating, a date, and a review.
9)VIEWREV seach_hit_number: this will allow a user to view all reviews
written for a specific product
10)REC: this will allow a user to view all of the recommended products
that they have not rated before based on their preferences in respect
to other users in the database.
10)QUIT new_db_filename: this will exit the program and write the final 
contents of the database (with updated quantities of products and updated 
user balances) to a file specified.

In order to run the program, please run the below code in terminal.
To compile: make amazon
To run: ./amazon "input file name"
