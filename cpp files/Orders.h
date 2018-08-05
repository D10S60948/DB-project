#ifndef ORDERS_H
#define ORDERS_H

#include "Database.h"

using namespace std;

class order
{
private:
	unsigned int order_id;
	unsigned int supplier_id;
	unsigned int customer_id;
	string status;
	string date;
public:
	order(unsigned int order_id_, unsigned int supplier_id_, unsigned int customer_id_, string status_, string date_)
		:order_id(order_id_), supplier_id(supplier_id_), customer_id(customer_id_), status(status_), date(date_)
	{}

	// GETTERS
	unsigned int getOrderID() { return order_id; }
	unsigned int getSupplierID() { return supplier_id; }
	unsigned int getCustomerID() { return customer_id; }
	string getStatus() { return status; }
	string getDate() { return date; }

	//	RETURNS ALL OPEN ORDERS
	static vector<order*> getAllOpenOrders()
	{
		CON;
		vector<order*> res;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("SELECT * from orders WHERE status!='close'");
			ResultSet *rset = pstmt->executeQuery();
			rset->beforeFirst();

			while (rset->next()) {
				order* Order = new order(rset->getUInt("order_id"), rset->getUInt("supp_id"), rset->getUInt("cus_id"), rset->getString("status"), rset->getString("date"));
				res.push_back(Order);
			}
			delete rset;
			delete pstmt;
			delete con;
		}
		return res;
	}

	//	RETURNS AMOUNT OF ORDERS IN A SPECIFIC TIME FRAME
	static int getAmountOfOrdersInTimeFrame(string fromDate, string toDate)
	{
		CON;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("select count(*) from orders where date>? and date<?");
			pstmt->setString(1, fromDate);
			pstmt->setString(2, toDate);
			ResultSet *rset = pstmt->executeQuery();
			rset->first();
			int res = rset->getInt("count(*)");

			delete rset;
			delete pstmt;
			delete con;

			return res;
		}
	}

	//	RETURNS AMOUNT OF ORDERS IN A SPECIFIC TIME FRAME YIELD PURCHASES
	static int getAmountOfOrdersInTimeFrameYieldPurchase(string fromDate, string toDate)
	{
		CON;
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("select count(distinct books_order.order_id) as orderAmount from books_order join orders on books_order.order_id=orders.order_id where date>? and date<? and books_order.quantity_purchased>0");
			pstmt->setString(1, fromDate);
			pstmt->setString(2, toDate);
			ResultSet *rset = pstmt->executeQuery();
			rset->first();
			int res = rset->getInt("orderAmount");

			delete rset;
			delete pstmt;
			delete con;

			return res;
		}
	}

};




#endif // !ORDERS_H

