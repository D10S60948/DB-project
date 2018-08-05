#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include "Database.h"

using namespace std;

class supplier
{
private:
	unsigned int id;
	string name;
	string phone;
public:
	supplier(unsigned int id_, string name_, string phone_)
		:id(id_), name(name_), phone(phone_)
	{}

	// GETTERS
	unsigned int getID() { return id; }
	string getName() { return name; }
	string getPhone() { return phone; }

	// RETURNS LIST OF ALL SUPPLIERS
	static vector<supplier*> getAllSuppliers()
	{
		CON;
		vector<supplier*> res;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("SELECT * from suppliers");
			ResultSet *rset = pstmt->executeQuery();
			rset->beforeFirst();

			while (rset->next()) {
				supplier* Supplier = new supplier(rset->getUInt("supplier_id"), rset->getString("name"), rset->getString("phone"));
				res.push_back(Supplier);
			}
			delete rset;
			delete pstmt;
			delete con;
		}
		return res;
	}

	// RETURNS SUPPLIER MADE THE MOST ORDERS
	static supplier* getMostOrdersSupplier(string Fromdate)
	{
		CON;

		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("select * from suppliers where supplier_id = (select supp_id from orders where date> ? group by supp_id order by count(*) desc limit 1)");
			pstmt->setString(1, Fromdate);
			ResultSet *rset = pstmt->executeQuery();
			rset->first();

			supplier* res = new supplier(rset->getUInt("supplier_id"), rset->getString("name"), rset->getString("phone"));

			delete rset;
			delete pstmt;
			delete con;
			return res;
		}
	}

	// RETURNS TOTAL PURCHASES AMOUNT MADE FROM A SUPPLIER IN A GIVEN TIME FRAME
	static int getTotalPurchasesAmountFromASupplier(string fromDate, string toDate, unsigned int supplierId)
	{
		CON;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("select supplier_ID, sum(price*quantity) as purchases_sum from supplying_books where sup_date>=? and sup_date<=? and supplier_ID=? group by supplier_ID");
			pstmt->setString(1, fromDate);
			pstmt->setString(2, toDate);
			pstmt->setUInt(3, supplierId);
			ResultSet *rset = pstmt->executeQuery();
			rset->first();

			int res = rset->getInt("purchases_sum");

			delete rset;
			delete pstmt;
			delete con;
			return res;
		}
	}

	// RETURNS LIST OF ALL SUPPLIERS OF A SPECIFIED BOOK
	static vector<supplier*> getAllSuppliersofBook(string bookName)
	{
		CON;
		vector<supplier*> res;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("select * from suppliers join supplying_books on suppliers.supplier_id=supplying_books.supplier_ID where supplying_books.Btitle=?");
			pstmt->setString(1, bookName);
			ResultSet *rset = pstmt->executeQuery();
			rset->beforeFirst();

			while (rset->next()) {
				supplier* Supplier = new supplier(rset->getUInt("supplier_id"), rset->getString("name"), rset->getString("phone"));
				res.push_back(Supplier);
			}
			delete rset;
			delete pstmt;
			delete con;
		}
		return res;
	}

	};


#endif // !SUPPLIERS_H