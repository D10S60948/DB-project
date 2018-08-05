#ifndef PURCHASES_H
#define PURCHASES_H

#include "Database.h"

using namespace std;

class purchase
{
private:
	unsigned int id;
	string date;
	bool was_cancelled;
	unsigned int employee_id;
	unsigned int customer_id;
public:
	purchase(unsigned int id_, unsigned int customer_id_, unsigned int employee_id_, string date_, bool was_cancelled_)
		:id(id_), customer_id(customer_id_), employee_id(employee_id_), date(date_), was_cancelled(was_cancelled_)
	{}

	// GETTERS
	unsigned int getID() { return id; }
	string getDate() { return date; }
	bool getCancellation() { return was_cancelled; }
	unsigned int getEmployee() { return employee_id; }
	unsigned int getCustomer() { return customer_id; }

	//	RETURNS ALL PURCHASES BETWEEN 2 DATES
	static vector<purchase*> getAllPurchasesTimeRange(int fromDay, int fromMonth, int fromYear, int toDay, int toMonth, int toYear)
	{
		string tempDay(to_string(fromDay)), tempMonth(to_string(fromMonth)), tempYear(to_string(fromYear));
		string dateFrom = tempYear + "-" + tempMonth + "-" + tempDay;
		tempDay = to_string(toDay); tempMonth = to_string(toMonth); tempYear = to_string(toYear);
		string toDate = tempYear + "-" + tempMonth + "-" + tempDay;

		CON;
		vector<purchase*> res;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("SELECT * from purchases WHERE date > ? AND date < ? ORDER BY date ASC");
			pstmt->setString(1, dateFrom);
			pstmt->setString(2, toDate);
			ResultSet *rset = pstmt->executeQuery();
			rset->beforeFirst();

			while (rset->next()) {
				purchase* Purchase = new purchase(rset->getUInt("purchase_id"), rset->getUInt("cust_id"), rset->getUInt("emp_id"),rset->getString("date"), rset->getBoolean("was_cancelled"));
				res.push_back(Purchase);
			}
			delete rset;
			delete pstmt;
			delete con;
		}
		return res;
	}

	//	RETURNS ALL PURCHASES BETWEEN 2 DATES
	static vector<int*> getQuarterlyIncome(int year)
	{
		string yearTocalc(to_string(year));
		string firstQbeg = yearTocalc + "0101";
		string firstQend = yearTocalc + "0331";
		string secondQbeg = yearTocalc + "0401";
		string secondQend = yearTocalc + "0630";
		string thirdQbeg = yearTocalc + "0701";
		string thirdQend = yearTocalc + "0930";
		string fourthQbeg = yearTocalc + "1001";
		string fourthQend = yearTocalc + "1231";

		CON;
		vector<int*> res;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("select sum(books_purchase.quantity*price) as income from purchases join books_purchase join books on purchases.purchase_id=books_purchase.purchase_id and books_purchase.book_ttl=books.title where purchases.date>=? and purchases.date<=?");
			pstmt->setString(1, firstQbeg);
			pstmt->setString(2, firstQend);
			ResultSet *rset = pstmt->executeQuery();
			rset->first();
			int* q1 = new int(rset->getInt("income"));
			res.push_back(q1);

			pstmt = con->prepareStatement("select sum(books_purchase.quantity*price) as income from purchases join books_purchase join books on purchases.purchase_id=books_purchase.purchase_id and books_purchase.book_ttl=books.title where purchases.date>=? and purchases.date<=?");
			pstmt->setString(1, secondQbeg);
			pstmt->setString(2, secondQend);
			rset = pstmt->executeQuery();
			rset->first();
			int* q2 = new int(rset->getInt("income"));
			res.push_back(q2);

			pstmt = con->prepareStatement("select sum(books_purchase.quantity*price) as income from purchases join books_purchase join books on purchases.purchase_id=books_purchase.purchase_id and books_purchase.book_ttl=books.title where purchases.date>=? and purchases.date<=?");
			pstmt->setString(1, thirdQbeg);
			pstmt->setString(2, thirdQend);
			rset = pstmt->executeQuery();
			if (rset) {
				rset->first();
				int* q3 = new int(rset->getInt("income"));
				res.push_back(q3);
			}

			pstmt = con->prepareStatement("select sum(books_purchase.quantity*price) as income from purchases join books_purchase join books on purchases.purchase_id=books_purchase.purchase_id and books_purchase.book_ttl=books.title where purchases.date>=? and purchases.date<=?");
			pstmt->setString(1, fourthQbeg);
			pstmt->setString(2, fourthQend);
			rset = pstmt->executeQuery();
			if (rset) {
				rset->first();
				int* q4 = new int(rset->getInt("income"));
				res.push_back(q4);
			}
				

			delete rset;
			delete pstmt;
			delete con;
		}
		return res;
	}

};




#endif // !PURCHASES_H

