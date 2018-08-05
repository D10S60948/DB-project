#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "Database.h"

using namespace std;

class employee
{
private:
	unsigned int id;
	string name;
	string phone;
public:
	employee(unsigned int id_, string name_, string phone_)
		:id(id_), name(name_), phone(phone_)
	{}

	//	GETTERS
	unsigned int getID() { return id; }
	string getName() { return name; }
	string getPhone() { return phone; }


	// RETURNS TOTAL SALES AMOUNT OF AN EMPLOYEE IN A SPECIFIC TIME FRAME
		static int getAmountOfTotalSales(string fromDate, string toDate, unsigned int employeeID)
	{
		CON;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("select sum(books.price*books_purchase.quantity) as total_sales from purchases join books_purchase join books on purchases.purchase_id = books_purchase.purchase_id and books_purchase.book_ttl = books.title where purchases.date >= ? and purchases.date <= ?  and emp_id=? group by emp_id union select 0 as total_sales");
			pstmt->setString(1, fromDate);
			pstmt->setString(2, toDate);
			pstmt->setUInt(3, employeeID);
			ResultSet *rset = pstmt->executeQuery();
			rset->first();

			int* res = new int(rset->getInt("total_sales"));

			delete rset;
			delete pstmt;
			delete con;
			int result;
			res ? result = *res : result = 0;
			delete res;
			return result;
		}
	}



};


#endif // !EMPLOYEES_H
