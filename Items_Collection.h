#pragma once
#include <algorithm> //Used for lambda / and to iterate through vectors.
#include <numeric>
#include "Functions.h" //This stores created functions which have been used throughout the program.
#include "Item_Singular.h" //This is included because this is what the Items struct will model a vector of.
#include <stdio.h>
#include <iostream> //For cout / cin etc.
#include <vector> //This allows program to use vector (dynamic array) feature.
#include <string> //This allows for the use of strings.
#include <iomanip> //Used for controlling how many numbers after decimal point.
#include <limits.h> 
#include <algorithm>
//Struct for items
class Items
{
public:
	//Attribute vector of Item.
	std::vector<Item>objItems;
	//Member functions that perform all operations using the vector of objItems
	//Text file operations for vector
	void Rewrite_Text_File(std::string inputFilePath); //This re-writes the text file with the updated vector of items
	std::size_t Size() const; //This returns the size of the vector<Item>objItems
	bool Add_Item(std::string sFilePathway); //This adds item to the vector<Item>objItems
	bool Delete_All_Items(std::string inputFilePath);//This deletes all items within the vector<Item>objItems
	void Display_Warning(const double dUnderperformingPercentage) const; //This displays a warning if any of the the items consitutes less than 5% of total sales
	void Display_Item_At_Index(std::size_t iIndex) const; //This displays the item of whatever index is passed into it
	void Append_Item_To_Text_File(std::string inputFilePath, std::string sItemName, double dItemCost, int iQuantitySold);
	auto Least_Sold_Item() const; // returns the index of the least sold item
	auto Most_Sold_Item() const; // returns the index of the most sold item
	int Total_Quantity_Sold() const; // returns the total quantity sold
	bool Delete_An_Item(std::string inputFilePath); // Deletes an item
	bool Update_Item_Name(std::string inputeFilePath); // updates item name
	bool Update_Quantity_Sold(std::string inputeFilePath); // updates quantity sold
	bool Print_Items() const; // prints items 
	bool Check_If_Item_Exists(std::string sInputName) const; // used for checking if item exists to prevent duplicate items being entered
	bool Display_Underperforming_Items() const; //Displays the items which are underperforming (ones that constitutes less than 5% of total sales)_
	bool Display_Least_Sold_Item() const; //Displays least sold item
	bool Display_Most_Sold_Item() const; // Displays Most sold item
	int Difference_Between_Least_Most_Sold_Quantity() const; //returns the difference between the least and most sold quantity
	double Total_Sales() const; //Returns the total sales
	double Tax_To_Pay_Amount(const double dTaxRate) const; // returns the tax to pay amount
	double Take_Home_Profit(const double dTaxRate, const double dOperationalCostPercentage) const; //returns the take home profit (minusing tax and operational costs)
	double Total_Price_Sold() const; //returns the total price sold
	double Estimated_Operational_Cost(const double dOperationalCostPercentage) const; // returns the estimated operational cost
	double Average_Sale() const;
};

