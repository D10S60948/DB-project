#ifndef DISCOUNTS_H
#define DISCOUNTS_H

#include "Database.h"

using namespace std;

class discount
{
private:
	string type;
	int precentage;
public:
	discount(string type_, int precentage_)
		:type(type_), precentage(precentage_)
	{}

	//	GETTERS
	string getType() { return type; }
	int getPrecentage() { return precentage; }


};


#endif // !DISCOUNTS_H
