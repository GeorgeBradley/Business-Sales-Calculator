#pragma once
#include <string>
#include <iostream>
struct Item
{
	//Item attributes
	std::string sItemName;
	double dSalePrice;
	int iQuantitySold;

	//Constructor which uses initalisation list to create true initalization, as opposed to initalising in the body of the constructor which isn't true initalisation.
	Item(std::string sInitItemName, double dInitSalePrice, int iInitQuantitySold)
		:sItemName(sInitItemName), dSalePrice(dInitSalePrice), iQuantitySold(iInitQuantitySold) //initalisation list
	{
		//Nothing in body of this constructor as initalisation takes place two lines above
	}

	//Member function that displays item information.
	void Display_Item() const
	{
		std::cout << "===================================\n";
		std::cout << "\tName: " << sItemName << "\n";
		std::cout << "\tSale Price: " << char(156) << dSalePrice << "\n";
		std::cout << "\tQuantity Sold: " << iQuantitySold << "\n";
		std::cout << "\tIndividual Sale Total: " << char(156) << Individual_Item_Sale() << "\n";
		std::cout << "===================================\n";
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
};


