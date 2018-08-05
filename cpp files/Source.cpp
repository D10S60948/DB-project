#include "Database.h"
#include "Books.h"
#include "Orders.h"
#include "Customers.h"
#include "Suppliers.h"
#include "Purchases.h"
#include "Customers.h"
#include "Employees.h"
#include "Discount.h"


using namespace std;

int menu();
void selectExecution(int);
void getListOfBooksInStock();
void getListOfOpenOrders();
void getListofCustomers();
void getListofSuppliers();
void selectDatesAndgetPurchases();
void getListOfBooksWithDiscount();
void isTheBookInStock();
void suppliersOfBook();
void AmountOfBookCopiesSold();
void booksPurchasedByCustomer();
void customerBaughtBooksMost();
void mostOrdersFromSupplier();
void amountOfOrdersInTimeFrame();
void amountOfOrdersInTimeFrameBecamePuchases();
void quarterlyIncome();
void newCustomersInTimeFrame();
void purchasesAmountFromSupplier();
void amountOfSalesOfEmployee();
void topTenSellers();

string convertIntsToString(int, int, int);
template <class T>
void deleteVector(vector<T*>);

int main(int argc, char*argv[])
{
	int selection_number = -1;

	while (selection_number != 99) 
		selectExecution(selection_number=menu());

	cout << "\n\n\n**** HAVE A GOOD DAY ****\n\n\n";

	return 0;
}


int menu() {
	int optionSelect = -1;
	cout << string(3, '\n');
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl <<
		"\t\tMENU" << endl << endl <<
		"1. All the books in stock" << endl <<
		"2. All open orders and their status" << endl <<
		"3. Customers list" << endl <<
		"4. Suppliers list" << endl <<
		"5. Purchases made within a ceratin time range" << endl <<
		"6. Books in discount" << endl <<
		"7. Check if a book is currently in stock" << endl <<
		"8. All suppliers of a certain book" << endl <<
		"9. How many copies of a book were sold since a certain date" << endl <<
		"10. Amount of books a certain customer purchased since a certain date" << endl <<
		"11. Details of the customer who bought the highest amount of books since a certain date" << endl <<
		"12. Details of the supplier who supllied the highest amount of books since a certain date" << endl <<
		"13. Amount of orders made in a certain time range" << endl <<
		"14. Amount of orders which became purchases made in a certain time range" << endl <<
		"15. Total discounts' amount customer received since a certain date" << endl <<
		"16. Purchases revenue of each quarter of a specific year" << endl <<
		"17. Amount of new customers since a certain date" << endl <<
		"18. Books pruchases from a specific supplier in a certain time range" << endl <<
		"19. Sales revenue of a specific seller in a certain time range" << endl <<
		"20. List of the 10 most selled books in a certain time range" << endl <<
		"99. Exit" << endl << endl <<
		"Please select one of the above: ";
	cin >> optionSelect; 
	cout << endl << endl << endl << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	return optionSelect;
}

void selectExecution(int selection)
{
	switch (selection)
	{
	case 1:
		getListOfBooksInStock();
		break;
	case 2:
		getListOfOpenOrders();
		break;
	case 3:
		getListofCustomers();
		break;
	case 4:
		getListofSuppliers();
		break;
	case 5:
		selectDatesAndgetPurchases();
		break;
	case 6:
		getListOfBooksWithDiscount();
		break;
	case 7:
		isTheBookInStock();
		break;
	case 8:
		suppliersOfBook();
		break;
	case 9:
		AmountOfBookCopiesSold();
		break;
	case 10:
		booksPurchasedByCustomer();
		break;
	case 11:
		customerBaughtBooksMost();
		break;
	case 12:
		mostOrdersFromSupplier();
		break;
	case 13:
		amountOfOrdersInTimeFrame();
		break;
	case 14:
		amountOfOrdersInTimeFrameBecamePuchases();
		break;
	case 15:
		break;
	case 16:
		quarterlyIncome();
		break;
	case 17:
		newCustomersInTimeFrame();
		break;
	case 18:
		purchasesAmountFromSupplier();
		break;
	case 19:
		amountOfSalesOfEmployee();
		break;
	case 20:
		topTenSellers();
		break;
	default:
		break;
	}

}

//	CASE 1
void getListOfBooksInStock()
{
	vector<book*> booksList = book::getAllBooksInStock();

	cout << "List of all books in stock:\n\n" <<
		"TITLE\n" <<
		"-----n";

	for (vector<book*>::iterator item = booksList.begin(); item != booksList.end(); item++)
	{
		cout << endl;
		book *curr = *item;
		cout << curr->getTitle() << "\t(Author: " << curr->getAuthor() << ")";
	}
	deleteVector(booksList);
}

// CASE 2
void getListOfOpenOrders()
{
	vector<order*> openOrdersList = order::getAllOpenOrders();

	cout << "List of all open orders:\n\n" << 
		"ORDER ID\tSTATUS" << endl <<
		"--------\t------";

	for (vector<order*>::iterator item = openOrdersList.begin(); item != openOrdersList.end(); item++)
	{
		cout << endl;
		order *curr = *item;
		cout << curr->getOrderID() << "\t\t" << curr->getStatus();
	}
	deleteVector(openOrdersList);
}	

// CASE 3
void getListofCustomers()
{
	vector<customer*> customersList = customer::getAllCustomers();

	cout << "List of all customers:\n\n" <<
		"CUSTOMER ID\tNAME" << endl <<
		"-----------\t----";

	for (vector<customer*>::iterator item = customersList.begin(); item != customersList.end(); item++)
	{
		cout << endl;
		customer *curr = *item;
		cout << curr->getId() << "\t\t" << curr->getFirstName() << " " << curr->getLastName();
	}
	deleteVector(customersList);
}

// CASE 4
void getListofSuppliers()
{
	vector<supplier*> suppliersList = supplier::getAllSuppliers();

	cout << "List of all suppliers:\n\n" <<
		"ID\tNAME\tPHONE" << endl <<
		"--\t----\t-----";

	for (vector<supplier*>::iterator item = suppliersList.begin(); item != suppliersList.end(); item++)
	{
		cout << endl;
		supplier *curr = *item;
		cout << curr->getID() << "\t" << curr->getName() << "\t" << curr->getPhone();
	}
	deleteVector(suppliersList);
}

// CASE 5
void selectDatesAndgetPurchases()
{
	int Fday, Fmonth, Fyear, Tday, Tmonth, Tyear;
	cout << "\nFrom date:" << endl << 
			"Day: "; cin >> Fday;
	cout << "Month: "; cin >> Fmonth;
	cout << "Year: "; cin >> Fyear;
	cout << "\nTo date:" << endl <<
		"Day: "; cin >> Tday;
	cout << "Month: "; cin >> Tmonth;
	cout << "Year: "; cin >> Tyear;
	cout << endl << endl;

	vector<purchase*> purchasesList = purchase::getAllPurchasesTimeRange(Fday, Fmonth, Fyear, Tday, Tmonth, Tyear);

	cout << "List of all purchases made between the specified dates:\n\n" <<
		"PURCHASE ID\tDATE\t\tWAS CANCELLED" << endl <<
		"-----------\t----\t\t-------------";

	for (vector<purchase*>::iterator item = purchasesList.begin(); item != purchasesList.end(); item++)
	{
		cout << endl;
		purchase *curr = *item;
		cout << curr->getID() << "\t\t" << curr->getDate() << "\t" << curr->getCancellation();
	}
	deleteVector(purchasesList);
}

// CASE 6
void getListOfBooksWithDiscount()
{
	vector<book*> booksList = book::getAllBooksWithDiscount();

	cout << "List of all books in stock:\n\n" <<
		"TITLE\n" <<
		"-----n";

	for (vector<book*>::iterator item = booksList.begin(); item != booksList.end(); item++)
	{
		cout << endl;
		book *curr = *item;
		cout << curr->getTitle() << "\t(Author: " << curr->getAuthor() << ")";
	}
	deleteVector(booksList);
}

// CASE 7
void isTheBookInStock()
{
	string name_of_book;
	cout << "Name of the book to check if is in stock: "; 
	getline(cin >> ws, name_of_book);
	
	cout << endl << name_of_book;
	book::isBookInStock(name_of_book) == true ? cout << " is in stock\n" : cout << " is not in stock\n";
}

// CASE 8
void suppliersOfBook()
{
	string name_of_book;
	cout << "Name of the requested book: ";
	getline(cin >> ws, name_of_book);

	vector<supplier*> suppliersList = supplier::getAllSuppliersofBook(name_of_book);

	cout << "List of all suppliers of \"" << name_of_book << "\":\n\n" <<
		"ID\tNAME\tPHONE" << endl <<
		"--\t----\t-----";

	for (vector<supplier*>::iterator item = suppliersList.begin(); item != suppliersList.end(); item++)
	{
		cout << endl;
		supplier *curr = *item;
		cout << curr->getID() << "\t" << curr->getName() << "\t" << curr->getPhone();
	}
	deleteVector(suppliersList);
}

// CASE 9
void AmountOfBookCopiesSold()
{
	unsigned int day, month, year;
	cout << "\nFrom date\nDay: "; cin >> day; cout << "Month: "; cin >> month; cout << "Year: "; cin >> year;
	string date = convertIntsToString(day, month, year);
	string name_of_book;
	cout << "Name of the requested book: ";
	getline(cin >> ws, name_of_book);

	cout << "\nFrom " << day << "/" << month << "/" << year << " " <<
		book::getAmountOfBookSoldCopies(name_of_book, date) << " copies of \"" << name_of_book << "\" were sold";
}

// CASE 10
void booksPurchasedByCustomer()
{
	unsigned int customerID, day, month, year;
	cout << "Customer ID: "; cin >> customerID;
	cout << "\nFrom date\nDay: "; cin >> day; cout << "Month: "; cin >> month; cout << "Year: "; cin >> year;
	
	string date = convertIntsToString(day, month, year);

	vector<book*> booksList = book::getBooksCustomerPurchased(date, customerID);

	cout << "List of all books in stock:\n\n" <<
		"TITLE\n" <<
		"-----";

	for (vector<book*>::iterator item = booksList.begin(); item != booksList.end(); item++)
	{
		cout << endl;
		book *curr = *item;
		cout << curr->getTitle() << "\t(Author: " << curr->getAuthor() << ")";
	}
	deleteVector(booksList);
}

// CASE 11 
void customerBaughtBooksMost()
{
	unsigned int day, month, year, winningCustomer;
	cout << "\nFrom date\nDay: "; cin >> day; cout << "Month: "; cin >> month; cout << "Year: "; cin >> year;

	string date = convertIntsToString(day, month, year);

	winningCustomer = customer::getmostBuyingCustomer(date);
	customer* cus = customer::getACustomer(winningCustomer);

	cout << "\n\nThe details of the customer who bought the most books-\nCustomer ID: " << cus->getId() << endl <<
		"Name: " << cus->getFirstName() << " " << cus->getLastName() << endl <<
		"Phone number: " << cus->getPhoneNumber();
	delete cus;
}

// CASE 12
void mostOrdersFromSupplier()
{
	unsigned int day, month, year;
	cout << "\nFrom date\nDay: "; cin >> day; cout << "Month: "; cin >> month; cout << "Year: "; cin >> year;

	string date = convertIntsToString(day, month, year);

	supplier* sup = supplier::getMostOrdersSupplier(date);

	cout << "\n\nThe details of the supplier with most orders-\nSupplier ID: " << sup->getID() << endl <<
		"Name: " << sup->getName() << endl <<
		"Phone number: " << sup->getPhone();
	
	delete sup;
}

// CASE 13
void amountOfOrdersInTimeFrame()
{
	unsigned int Fday, Fmonth, Fyear, Tday, Tmonth, Tyear;
	cout << "\nFrom date\nDay: "; cin >> Fday; cout << "Month: "; cin >> Fmonth; cout << "Year: "; cin >> Fyear;
	cout << "\nTo date\nDay: "; cin >> Tday; cout << "Month: "; cin >> Tmonth; cout << "Year: "; cin >> Tyear;
	string toDate = convertIntsToString(Tday, Tmonth, Tyear);
	string fromDate = convertIntsToString(Fday, Fmonth, Fyear);

	cout << "\nFrom " << Fday << "/" << Fmonth << "/" << Fyear << " to " << Tday << "/" << Tmonth << "/" << Tyear << " - " <<
		order::getAmountOfOrdersInTimeFrame(fromDate,toDate) << " orders were executed";
}

// CASE 14
void amountOfOrdersInTimeFrameBecamePuchases()
{
	unsigned int Fday, Fmonth, Fyear, Tday, Tmonth, Tyear;
	cout << "\nFrom date\nDay: "; cin >> Fday; cout << "Month: "; cin >> Fmonth; cout << "Year: "; cin >> Fyear;
	cout << "\nTo date\nDay: "; cin >> Tday; cout << "Month: "; cin >> Tmonth; cout << "Year: "; cin >> Tyear;
	string toDate = convertIntsToString(Tday, Tmonth, Tyear);
	string fromDate = convertIntsToString(Fday, Fmonth, Fyear);

	cout << "\nFrom " << Fday << "/" << Fmonth << "/" << Fyear << " to " << Tday << "/" << Tmonth << "/" << Tyear << " - " <<
		order::getAmountOfOrdersInTimeFrameYieldPurchase(fromDate, toDate) << " orders yield purchase";
}

// CASE 16
void quarterlyIncome()
{
	int Year = -1;

	cout << "\nSelect year: "; cin >> Year;

	vector<int*> incomeList = purchase::getQuarterlyIncome(Year);

	cout << "List of all books in stock:\n\n" <<
		"Q1\tQ2\tQ3\tQ4\n" <<
		"--\t--\t--\t--\n";

	for (vector<int*>::iterator item = incomeList.begin(); item != incomeList.end(); item++)
	{
		int *curr = *item;
		cout << *curr << "\t";
	}
	deleteVector(incomeList);
}

// CASE 17
void newCustomersInTimeFrame()
{
	unsigned int day, month, year;
	cout << "\nFrom date\nDay: "; cin >> day; cout << "Month: "; cin >> month; cout << "Year: "; cin >> year;

	string date = convertIntsToString(day, month, year);
	
	cout << "\nFrom " << day << "/" << month << "/" << year << " - " <<
		customer::getAmountOfNewCustomers(date) << " customers joined";
}

// CASE 18
void purchasesAmountFromSupplier()
{
	unsigned int Fday, Fmonth, Fyear, Tday, Tmonth, Tyear, supplierID;
	cout << "\nSupllier's ID: "; cin >> supplierID;
	cout << "\nFrom date\nDay: "; cin >> Fday; cout << "Month: "; cin >> Fmonth; cout << "Year: "; cin >> Fyear;
	cout << "\nTo date\nDay: "; cin >> Tday; cout << "Month: "; cin >> Tmonth; cout << "Year: "; cin >> Tyear;
	string toDate = convertIntsToString(Tday, Tmonth, Tyear);
	string fromDate = convertIntsToString(Fday, Fmonth, Fyear);

	cout << "\nFrom " << Fday << "/" << Fmonth << "/" << Fyear << " to " << Tday << "/" << Tmonth << "/" << Tyear << " - " <<
		"the sum amount of all purchases from supplier " << supplierID << " is " << order::getAmountOfOrdersInTimeFrameYieldPurchase(fromDate, toDate);
}

// CASE 19
void amountOfSalesOfEmployee()
{
	unsigned int Fday, Fmonth, Fyear, Tday, Tmonth, Tyear, employeeID;
	cout << "\nEmployee's ID: "; cin >> employeeID;
	cout << "\nFrom date\nDay: "; cin >> Fday; cout << "Month: "; cin >> Fmonth; cout << "Year: "; cin >> Fyear;
	cout << "\nTo date\nDay: "; cin >> Tday; cout << "Month: "; cin >> Tmonth; cout << "Year: "; cin >> Tyear;
	string toDate = convertIntsToString(Tday, Tmonth, Tyear);
	string fromDate = convertIntsToString(Fday, Fmonth, Fyear);

	cout << "\nFrom " << Fday << "/" << Fmonth << "/" << Fyear << " to " << Tday << "/" << Tmonth << "/" << Tyear << 
		" employee " << employeeID << " sold books in total amount of " << employee::getAmountOfTotalSales(fromDate, toDate,employeeID) << " Shkalims";
}

// CASE 20
void topTenSellers()
{
	unsigned int Fday, Fmonth, Fyear, Tday, Tmonth, Tyear;
	cout << "\nFrom date\nDay: "; cin >> Fday; cout << "Month: "; cin >> Fmonth; cout << "Year: "; cin >> Fyear;
	cout << "\nTo date\nDay: "; cin >> Tday; cout << "Month: "; cin >> Tmonth; cout << "Year: "; cin >> Tyear;
	string toDate = convertIntsToString(Tday, Tmonth, Tyear);
	string fromDate = convertIntsToString(Fday, Fmonth, Fyear);

	vector<book*> topSellersList = book::getTopTenSellers(fromDate,toDate);

	cout << "\nList of the top 10 sellers:\n\n" <<
		"SOLD\tTITLE\n" <<
		"-----\t-----";

	for (vector<book*>::iterator item = topSellersList.begin(); item != topSellersList.end(); item++)
	{
		cout << endl;
		book *curr = *item;
		cout << curr->getQuantityInStock() << "\t" << curr->getTitle() << "\t(Author: " << curr->getAuthor() << ")";
	}
	deleteVector(topSellersList);

}

// ASSISTING FUNCTIONS ( .1. convert ints to string - used for date queries && .2. deleting vectors function which frees allocated memory)

string convertIntsToString(int day, int month, int year)
{
	string Date = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
	return Date;
}

template <class T>
void deleteVector(vector<T*> vec)
{
	vector<T*>::iterator item = vec.begin();
	while (item != vec.end())
	{
		cout << endl;
		T *curr = *item;
		item++;
		delete curr;
	}
}