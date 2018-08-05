#ifndef BOOKS_H
#define BOOKS_h

#include "Database.h"

using namespace std;

class book
{
private:
	string title;
	string author;
	unsigned int quantity_in_stock;
	bool global_discout;
	unsigned int price;
public:
	book(string title_, string author_, unsigned int price_, unsigned int quantity_in_stock_, bool global_discount_)
		:title(title_), author(author_), price(price_), quantity_in_stock(quantity_in_stock_), global_discout(global_discount_)
	{}
	// GETTERS
	const string getTitle() const { return title; }
	const string getAuthor() const { return author; }
	const unsigned int getPrice() const { return price; }
	const unsigned int getQuantityInStock() const { return quantity_in_stock; }
	const bool getDiscount() const { return global_discout; }

	// GETIING A SPECIFIC BOOK BY THE TITLE
	static book * book::getById(string BTitle)
	{
		CON;
		PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM books WHERE title = ?");
		pstmt->setString(1, BTitle);
		ResultSet *rset = pstmt->executeQuery();
		if (rset->rowsCount() == 1) {
			rset->first();
			book *result = new book(rset->getString("title"), rset->getString("author"), rset->getInt("price"),	rset->getInt("quantity_in_stock"), rset->getBoolean("global_discout"));

			delete pstmt;
			delete rset;
			delete con;
			cout
				<< result->getTitle() << " " << result->getPrice() << endl;
			return result;
		}

		delete pstmt;
		delete rset;
		delete con;

		return 0;
	}

	// GETTING LIST OF ALL BOOKS
	static vector<book*> getAllBooksInStock() 
	{
		CON;
		vector<book*> res;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("SELECT * from books WHERE quantity_in_stock > 0");
			ResultSet *rset = pstmt->executeQuery();
			rset->beforeFirst();

			while (rset->next()) {
				book *Book = new book(rset->getString("title"), rset->getString("author"), rset->getUInt("price"), rset->getUInt("quantity_in_stock"), rset->getBoolean("global_discount"));
				res.push_back(Book);
			}
			delete rset;
			delete pstmt;
			delete con;
		}
		return res;
	}

	// GETTING LIST OF ALL BOOKS WITH DISCOUNT
	static vector<book*> getAllBooksWithDiscount()
	{
		CON;
		vector<book*> res;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("SELECT * from books WHERE global_discount=TRUE");
			ResultSet *rset = pstmt->executeQuery();
			rset->beforeFirst();

			while (rset->next()) {
				book *Book = new book(rset->getString("title"), rset->getString("author"), rset->getUInt("price"), rset->getUInt("quantity_in_stock"), rset->getBoolean("global_discount"));
				res.push_back(Book);
			}
			delete rset;
			delete pstmt;
			delete con;
		}
		return res;
	}

	// RETURNS 'TRUE' IF BOOK IN STOCK, 'FALSE' OTHERWISE
	static bool isBookInStock(string bookName)
	{
		CON;
		bool res;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("select quantity_in_stock from books where title=? union select 0 as quantity_in_stock");
			pstmt->setString(1, bookName);
			ResultSet *rset = pstmt->executeQuery();
			rset->first();
			res = (rset->getUInt("quantity_in_stock") > 0 ? true : false);
			
			delete rset;
			delete pstmt;
			delete con;
		}
		
		return res;
	}

	// RETURNS LIST OF BOOKS PURCHASED BY A CUSTOMER IN A SPECIFIC TIME FRAME
	static  vector<book*> getBooksCustomerPurchased(string sinceDate, unsigned int customerId)
	{
		CON;
		vector<book*> res;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("select * from books where title=(select book_ttl from books_purchase where purchase_id = (select purchase_id from purchases where date>? and cust_id = ?))");
			pstmt->setString(1, sinceDate);
			pstmt->setUInt(2, customerId);
			ResultSet *rset = pstmt->executeQuery();
			rset->beforeFirst();

			while (rset->next()) {
				book *Book = new book(rset->getString("title"), rset->getString("author"), rset->getUInt("price"), rset->getUInt("quantity_in_stock"), rset->getBoolean("global_discount"));
				res.push_back(Book);
			}
			delete rset;
			delete pstmt;
			delete con;
		}
		return res;
	}

	// RETURNS LIST OF MOST SOLD BOOKS IN A SPECIFIC TIME FRAME
	static  vector<book*> getTopTenSellers(string fromDate, string toDate)
	{
		CON;
		vector<book*> res;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("select *,sum(books_purchase.quantity) as sold_in_total from books_purchase join books  on books.title=books_purchase.book_ttl where books_purchase.purchase_id=any(select purchase_id from purchases where was_cancelled=false and date>=? and date<=?) group by books_purchase.book_ttl order by sold_in_total desc limit 10");
			pstmt->setString(1, fromDate);
			pstmt->setString(2, toDate);
			ResultSet *rset = pstmt->executeQuery();
			rset->beforeFirst();

			while (rset->next()) {
				book *Book = new book(rset->getString("book_ttl"), rset->getString("author"), rset->getUInt("price"), rset->getUInt("sold_in_total"), rset->getBoolean("global_discount"));
				res.push_back(Book);
			}
			delete rset;
			delete pstmt;
			delete con;
		}
		return res;
	}

	// RETURNS AMOUNT OF COPIES OF A SPECIFIED BOOK WERE BAUGHT SINCE A GIVEN DATE
	static int getAmountOfBookSoldCopies(string bookName, string fromDate)
	{
		CON;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("select sum(quantity-was_cancelled*quantity) as copies from books_purchase join purchases on books_purchase.purchase_id=purchases.purchase_id where book_ttl=? and date>=? group by book_ttl order by book_ttl");
			pstmt->setString(1, bookName);
			pstmt->setString(2, fromDate);
			ResultSet *rset = pstmt->executeQuery();
			rset->first();
			int res = rset->getInt("copies");

			delete rset;
			delete pstmt;
			delete con;
			return res;
		}
	}
};

#endif // !BOOK_H

