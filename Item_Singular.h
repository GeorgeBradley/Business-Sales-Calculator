#pragma once
#include <string>
#include <iostream>
class Item
{
private:
	//Item attributes
	std::string sItemName;
	double dSalePrice;
	int iQuantitySold;
public:
	//Constructor which uses initalisation list to create true initalization, as opposed to initalising in the body of the constructor which isn't true initalisation.
	Item(std::string sInitItemName, double dInitSalePrice, int iInitQuantitySold)
		:sItemName(sInitItemName), dSalePrice(dInitSalePrice), iQuantitySold(iInitQuantitySold) //initalisation list
	{
		//Nothing in body of this constructor as initalisation takes place two lines above
	}
	Item(const Item& objItem)
		:Item(objItem.sItemName, objItem.dSalePrice, objItem.iQuantitySold)
	{
	}
	~Item() {

	}
	//Because I've privated the class attributes, I have created getters for each attribute
	std::string Get_Item_Name() const
	{
		return sItemName;
	}
	//Getter
	double Get_Sale_Price() const
	{
		return dSalePrice;
	}
	//Getter
	int Get_Quantity_Sold() const
	{
		return iQuantitySold;
	}
	//Member function that displays item information.
	void Display_Item() const
	{
		
	}

	//Calculates individual item sale for an item
	double Individual_Item_Sale() const
	{
		return dSalePrice * iQuantitySold;
	}

	//Updates name to whatever string parameter is passed in
	void Update_Name(std::string* sUpdateItemName)
	{
		sItemName = *sUpdateItemName;
	}
	//Updates Quantity Sold to whatever is passed in through int parameter

	void Update_Quantity_Sold(int* iUpdateQuantitySold)
	{
		iQuantitySold = *iUpdateQuantitySold;
	}
	
	//Overloading the << extraction operator to display Item
	friend std::ostream& operator<<(std::ostream& os, const Item& rhs) {
		os << "===================================\n"
			<< "\tName" << rhs.sItemName << "\n"
			<< "\tSale Price: " << char(156) << rhs.dSalePrice << "\n"
			<< "\tQuantity Sold: " << rhs.iQuantitySold << "\n"
			<< "\tIndividual Sale Total: " << char(156) << rhs.Individual_Item_Sale() << "\n"
			<< "===================================\n";

		return os;
	}
};


