#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include "Database.h"

using namespace std;

class customer
{
private:
	unsigned int id;
	string firstName;
	string lastName;
	string phoneNumber;
	bool is_entitle;
public:
	customer(unsigned int id_, string personalName_, string familyName_, string phoneNumber_, bool is_entitle_)
		:id(id_), firstName(personalName_), lastName(familyName_), phoneNumber(phoneNumber_), is_entitle(is_entitle_)
	{}

	// GETTERS
	unsigned int getId() { return id; }
	string getFirstName() { return firstName; }
	string getLastName() { return lastName; }
	string getPhoneNumber() { return phoneNumber; }
	bool getIsEntitle() { return is_entitle; }

	// RETURNS CUSOMER BY ID
	static customer* getACustomer(unsigned int cusID)
	{
		CON;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("SELECT * from customers where customer_id=?");
			pstmt->setUInt(1, cusID);
			ResultSet *rset = pstmt->executeQuery();
			rset->first();
			customer* Customer = new customer(rset->getUInt("customer_id"), rset->getString("Fname"), rset->getString("Lname"), rset->getString("phone_no"), rset->getBoolean("is_entitle"));

			delete rset;
			delete pstmt;
			delete con;
			return Customer;
		}
	}

	// RETURNS LIST OF ALL CUSTOMERS
	static vector<customer*> getAllCustomers()
	{
		CON;
		vector<customer*> res;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("SELECT * from customers");
			ResultSet *rset = pstmt->executeQuery();
			rset->beforeFirst();

			while (rset->next()) {
				customer* Customer = new customer(rset->getUInt("customer_id"), rset->getString("Fname"), rset->getString("Lname"), rset->getString("phone_no"), rset->getBoolean("is_entitle"));
				res.push_back(Customer);
			}
			delete rset;
			delete pstmt;
			delete con;
		}
		return res;
	}

	// RETURNS THE MOST BOOKS BUYING CUSTOMER SINCE A SPECEIFIED DATE
	static unsigned int getmostBuyingCustomer(string fromDate)
	{
		CON;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("select cust_id,SUM(quantity) as quant from purchases join books_purchase on purchases.purchase_id=books_purchase.purchase_id where purchases.was_cancelled=0 and purchases.date>? group by cust_id order by quant desc limit 1;");
			pstmt->setString(1, fromDate);
			ResultSet *rset = pstmt->executeQuery();

			rset->first();

			unsigned int mostBuyingCustomer = rset->getUInt("cust_id");

			delete rset;
			delete pstmt;
			delete con;
			return mostBuyingCustomer;
		}
	}

	// RETURNS THE AMOUNT OF NEW CUSTOMERS SINCE A SPECIFIED DATE
	static unsigned int getAmountOfNewCustomers(string fromDate)
	{
		CON;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("select count(*) as new_customers from purchases join (select cust_id,min(date) mindate from purchases group by cust_id)x on purchases.cust_id=x.cust_id and purchases.date=x.mindate where date>?");
			pstmt->setString(1, fromDate);
			ResultSet *rset = pstmt->executeQuery();

			rset->first();

			unsigned int amountOfNewCustomers = rset->getUInt("new_customers");

			delete rset;
			delete pstmt;
			delete con;
			return amountOfNewCustomers;
		}
	}

};

#endif // !CUSTOMERS_H