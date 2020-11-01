//  Items_Collection.cpp (where functions / procedures are implemented for Items_Collection.h file)
#include "Items_Collection.h"
//This function returns the size of the size of objItems, which is used in Sales.cpp to check if the size is 0
std::size_t Items::Size() const
{
	return objItems.size();
}
//Deletes all items from vector and text file
bool Items::Delete_All_Items(std::string inputFilePath)
{
	unsigned char cChoice = 0;
	bool bContinue = false;
	//If the size of objItems isn't equal to 0 it will continue as normal, else, it will stop running.
	if (objItems.size() != 0)
	{
		do
		{
			do
			{
				Message_And_Input("Are you sure you want to delete all items? (y/n): ", &cChoice);
			} while (Is_Input_Valid());

			cChoice = toupper(cChoice);
			if (cChoice == 'Y')
			{
				objItems.clear();
				Clear_Text_File_Contents(inputFilePath);
				std::cout << "All items have been deleted.\n";
				return true;
			}
			else if (cChoice == 'N')
			{
				std::cout << "No items were deleted.\n";
				return false;
			}
			else
			{
				Perform_Invalid_Operation();
				std::cout << "\n";
				bContinue = false;
			}
		} while (bContinue == false);
	}
	else
	{
		std::cout << "There are no items to delete.\n";
	}
	return false;
}

//This procedure displays the underperforming items, namely items that have scored individual sales less than 5% of the total sales.
//It also uses "Display_Item_At_Index" procedure which will display whatever index is passed in to it.
bool Items::Display_Underperforming_Items() const
{
	double dFivePercentOfTotalSales = Total_Quantity_Sold() * 0.05; //This ascertains 5% of total sales so it can be compared with individual items.
	int iNumberOfUnderperforming = 0; //This variable is used to count how many items are underperforming within the for loop
	int iCount = 0;
	if (objItems.size() == 0) //First checks if objItems size is equal to 0, if it is will prompt user to add an item.
	{
		Nothing_To_Display_Message();
	}
	else
	{
		for (std::size_t iCount = 0; iCount < objItems.size(); iCount++)
		{
			if (objItems.at(iCount).Get_Quantity_Sold() < dFivePercentOfTotalSales)
			{
				iNumberOfUnderperforming++;
				std::cout << "Item " << iCount + 1 << "\n";
				Display_Item_At_Index(iCount);
			}
		}
	}

	if (objItems.size() > 0 && iNumberOfUnderperforming == 0)
	{
		std::cout << "There are currently no underperforming items.\n";
	}
	return true;
}

//This function is used everytime an update is made within the vector<Item>.
void Items::Rewrite_Text_File(std::string inputFilePath)
{
	std::ofstream file;
	file.open(inputFilePath);
	for (const Item& objItem : objItems)
	{
		file << objItem.Get_Item_Name() << "," << objItem.Get_Sale_Price() << "," << objItem.Get_Quantity_Sold() << ",\n";
	}
	file.close();
}
//This function locates the name of inputted item and if it finds the item in the vector will subsequently delete it.
//For this I've used "Find_IF" function from the #include <algorithm> library (as well as Lambda).
bool Items::Delete_An_Item(std::string inputFilePath)
{
	unsigned char cChoice = 0;
	std::string sName = "";
	bool bContinue = false;
	if (objItems.size() != 0)
	{
		Message_And_Input("Enter the name of item you wish to delete: ", &sName);
		//using the algorithm libary and is what's called "Lambda".
		auto iIndex = std::find_if(objItems.begin(), objItems.end(),
			[&](const Item& objItem) { return objItem.Get_Item_Name() == sName; });

		if (iIndex != objItems.end())
		{
			do
			{
				do
				{
					Message_And_Input("Are you sure you want to delete this item? (y/n): ", &cChoice);
				} while (Is_Input_Valid());

				cChoice = std::toupper(cChoice);
				if (cChoice == 'Y')
				{
					objItems.erase(iIndex);
					std::cout << sName << " has been deleted.\n";
					Rewrite_Text_File(inputFilePath);
					return true;
				}
				else if (cChoice == 'N')
				{
					std::cout << "You've decided not to delete '" << sName << "'.\n";
					return false;
				}
				else
				{
					Perform_Invalid_Operation();
					bContinue = false;
				}
			} while (bContinue == false);	
		}
		else
		{
			std::cout << "The item you're trying to delete doesn't exist.\n";
			return false;
		}
	}
	else
	{
		std::cout << "There are currently no items to delete.\n";
	}
	return false;
}


//This function uses #include <algorithm> library and lambda and loops through the vector of items to ascertain whether the item being entered already exists. It was compare the "sInputName" being passed in through the parameter to item names within the vector. This is used to prevent duplication of Item names, to lessen confusion. This function is called in the procedure "Add_New_Item()".
bool Items::Check_If_Item_Exists(std::string sInputName) const
{
	bool bExists = false;
	auto it = std::find_if(objItems.begin(), objItems.end(),
		[&](const Item& item) { return item.Get_Item_Name() == sInputName; });
	if (it == objItems.end())
	{
		bExists = false;
	}
	else
	{
		std::cout << "\nTry again! There's already an item with that name.\n\n";
		bExists = true;
	}
	return bExists;
}

//This procedure adds new items when called dynamically to the vector using the "push_back()" method of the vector. It has user-input validation to ensure input errors aren't easily made. If a mistake is made by the user the various do-while loops will ensure they enter valid data.
void Items::Append_Item_To_Text_File(std::string inputFilePath, std::string sItemName, double dItemCost, int iQuantitySold)
{
	std::ofstream file;
	file.open(inputFilePath, std::fstream::app);
	file << sItemName << "," << dItemCost << "," << iQuantitySold << ",\n";
	file.close();
}

//This member-function adds a new item to the vector<Item>
bool Items::Add_Item(std::string sFilePathway)
{
	std::string sInputName;
	double dInputSalePrice = 0;
	int iInputQuantity = 0;
	std::string sInputSalePrice = "";
	std::string sInputQuantity = "";

	//This is where the iHowManyItems is used to loop through the number to push_back() items to objItems vector
	do
	{
		std::cout << "\n";
		std::cout << "**Enter information for new item**\n";
		std::cout << "\n";
		//This is where user enters the item name
		do
		{
			Message_And_Input("\tName: ", &sInputName);
		}
		//Error checking
		while (Is_String_Character_Allowed(sInputName) == false && Is_String_Length_Valid(sInputName, 1, 15) == false); //can enter a maximum of 15 characters

	} while (Check_If_Item_Exists(sInputName) == true); //ask them again if they're trying to input a name that already exists

	//This is where user enters sale price for item.
	do
	{
		do
		{
			Message_And_Input("\tSale price: ", 156, &sInputSalePrice);
		} 
		while (Is_Input_A_Number(sInputSalePrice, &dInputSalePrice) == false);

	} 
	while (Boundary_Check_Value_Is_Valid(dInputSalePrice, 0.0, 10000000.0) == false);

	do
	{
		//This is where the quantity sold for an item is entered
		do
		{
			Message_And_Input("\tQuantity sold: ", &sInputQuantity);
		} 
		while (Is_Input_A_Number(sInputQuantity, &iInputQuantity) == false);
	} 
	while (Boundary_Check_Value_Is_Valid(iInputQuantity, 0, 100000) == false);

	unsigned char cChoice = 0;
	bool bContinue = false;
	std::cout << "\n";
	//This is where the user is now able to confirm whether they wish to add the item they've just entered the informationf for
	do
	{
		Message_And_Input("Do you wish to add this item? (y/n): ", &cChoice);
		cChoice = toupper(cChoice);
		if (cChoice == 'Y')
		{
			std::cout << "Item has been succesfully added!\n";
			objItems.emplace_back(Item{ sInputName, dInputSalePrice, iInputQuantity });//using push_back to add item using constuctor parameters
			Append_Item_To_Text_File(sFilePathway, sInputName, dInputSalePrice, iInputQuantity);
			bContinue = true;
		}
		else if (cChoice == 'N')
		{
			std::cout << "You have chosen to disregard this item.\n";
			bContinue = true;
		}
		else
		{
			Perform_Invalid_Operation();
			bContinue = false;
		}
	} while (Is_Input_Valid() || bContinue == false);
	
	return true;
}
//This procedure is first used to ask the user how many items they wish to add. If they enter a number less than 5 they will be re-prompted to enter a higher number. I've included user validation to ensure user-errors can't be made to promote usability. After the user has entered the number of items that they would like they will then be subsequently prompted to enter the information pertaining to each of the items. This calls the "Add_New_Item() procedure".

//This procedure loops through the vector using a "Ranged Based For Loop" and adds the quantity of all sold items collectively to generate a total.
int Items::Total_Quantity_Sold() const
{
	auto sum = std::accumulate(objItems.begin(), objItems.end(), 0, 
		[](auto& accum, auto& objItem) { return accum + objItem.Get_Quantity_Sold(); });
	return sum;
	/*int iTotalQuantitySold = 0;
	for (const Item& objItem : objItems)
	{
		iTotalQuantitySold += objItem.Get_Quantity_Sold();
	}
	return iTotalQuantitySold;*/
}

//This function returns the element index of the items vector of the most sold item.
auto Items::Most_Sold_Item() const
{
	auto highest_grade_it = std::max_element(objItems.begin(), objItems.end(), [](auto& a, auto& b) {
		return a.Get_Quantity_Sold() < b.Get_Quantity_Sold();
		});
	return highest_grade_it;
	/*int iMostSoldItemValue = 0;
	std::size_t iIndexOfMostSoldItem = 0;
	for (std::size_t iCount = 0; iCount < objItems.size(); iCount++)
	{
		if (objItems.at(iCount).Get_Quantity_Sold() > iMostSoldItemValue)
		{
			iMostSoldItemValue = objItems.at(iCount).Get_Quantity_Sold();
			iIndexOfMostSoldItem = iCount;
		}
	}
	return iIndexOfMostSoldItem;*/
}

//This procedure calls the function "Index_Of_Most_Sold_Item()" to return the index of the most sold item. 
//Once the index of the highest selling item has been returned a for loop will iterate through the items vector and see if
//any other items scored the same, if they did it a variable by the name of "iCountNumberOfMostSoldItems" will be incremented. 
//After that, if the iCountNumberOfMostSoldItems is greater than 1 another For Loop will iterate and compare and display if the value in quantity sold is the same as the highest.
bool Items::Display_Most_Sold_Item() const
{
	if (objItems.size() == 0)
	{
		Nothing_To_Display_Message();
		return false;
	}
	auto MostSoldItem = Most_Sold_Item();
	int iCountNumberOfMostSoldItems = 1;

	for (const auto& objItem : objItems)
	{
		if (objItem.Get_Quantity_Sold() == MostSoldItem->Get_Quantity_Sold())
		{
			iCountNumberOfMostSoldItems++;
		}
	}

	if (MostSoldItem->Get_Quantity_Sold() == 0)
	{
		std::cout << "None of your sales exceeded profit greater than 0.\n";
	}
	else if (iCountNumberOfMostSoldItems >= 1)
	{
		std::cout << "The highest selling item(s)...\n";

	
		for (std::size_t iCount = 0; iCount < objItems.size(); iCount++)
		{
			if (objItems.at(iCount).Get_Quantity_Sold() == MostSoldItem->Get_Quantity_Sold())
			{
				Display_Item_At_Index(iCount);
			}
		}
	}
	return true;
}

//Returns the index of element in the items vector to the item that has sold the least amount.
auto Items::Least_Sold_Item() const
{
	auto lowest_grade_it = std::min_element(objItems.begin(), objItems.end(), [](auto& a, auto& b) {
		return a.Get_Quantity_Sold() < b.Get_Quantity_Sold();
		});
	return lowest_grade_it;

	/*int iLeastSoldItem = INT_MAX;
	std::size_t iIndexOfLeastSoldItem = 0;

	for (std::size_t iCount = 0; iCount < objItems.size(); iCount++)
	{
		if (objItems.at(iCount).Get_Quantity_Sold() < iLeastSoldItem)
		{
			iLeastSoldItem = objItems.at(iCount).Get_Quantity_Sold();
			iIndexOfLeastSoldItem = iCount;
		}
	}
	return iIndexOfLeastSoldItem;*/
}

//The same logic as the procedure "Display_Most_Sold_Item()" is applied to this one. This displays the least sold item/s.
bool Items::Display_Least_Sold_Item() const
{
	if (objItems.size() == 0)
	{
		Nothing_To_Display_Message();
		return false;
	}
	auto LeastSoldItem = Least_Sold_Item();
	int iLeastSoldItem = LeastSoldItem->Get_Quantity_Sold();
	int iCountNumberOfLeastSoldItems = 1;
	for (int iCount = 0; iCount < objItems.size(); iCount++)
	{
		if (objItems.at(iCount).Get_Quantity_Sold() == iLeastSoldItem)
		{
			iCountNumberOfLeastSoldItems++;
		}
	}
	if (iCountNumberOfLeastSoldItems >= 1)
	{
		std::cout << "The lowest selling item(s)...\n";
		for (std::size_t iCount = 0; iCount < objItems.size(); iCount++)
		{
			if (objItems.at(iCount).Get_Quantity_Sold() == iLeastSoldItem)
			{
				Display_Item_At_Index(iCount);
			}
		}
	}
	return true;
}
//This procedure displays the index of items vector of whatever is passed into it (through its single parameter), and is used several times in this program, namely in the functions: "Display_Underperforming_Items()", "Display_Least_Amount_Sold()", and "Display_Most_Amount_Sold()".
void Items::Display_Item_At_Index(std::size_t iIndex) const
{
	std::cout << objItems.at(iIndex);
}

//This calculates the difference between the most sold and the least sold (in terms of quantity).
int Items::Difference_Between_Least_Most_Sold_Quantity()const
{
	return Most_Sold_Item()->Get_Quantity_Sold() - Least_Sold_Item()->Get_Quantity_Sold();
}

//This calculates the total sales (not considering tax or operational costs).
double Items::Total_Sales() const
{
	double dTotalSales = 0;
	if (objItems.size() != 0)
	{
		/*for (const Item& objItem : objItems)
		{
			dTotalSales += objItem.Individual_Item_Sale();
		}*/
		dTotalSales = std::accumulate(objItems.begin(), objItems.end(), 0.0,
			[](auto& accum, auto& objItem) { return accum + objItem.Individual_Item_Sale(); });
		
	}
	else
	{
		Nothing_To_Display_Message();
	}
	return dTotalSales;
}

//This calculates the estimated operational cost at a rate of 50%
double Items::Estimated_Operational_Cost(const double dOperationalCostPerecentage) const
{
	return Total_Sales() * dOperationalCostPerecentage;
}
//This calculates the amount of tax that has to be paid (rate of 20%).
double Items::Tax_To_Pay_Amount(const double dTaxRate) const
{
	return Total_Sales() * dTaxRate;
}
//This calculates total profit (after tax and operational costs)
double Items::Take_Home_Profit(const double dTaxRate, const double dOperationalCostPercentage) const
{
	return Total_Sales() - (Tax_To_Pay_Amount(dTaxRate) + Estimated_Operational_Cost(dOperationalCostPercentage));
}
//THis prints all the items in the vector, if all items have been deleted (after the initial 5 or more have have been inputted) it will display a message that states "there are no items to display".
bool Items::Print_Items() const
{
	int iCountNumber = 1;
	if (objItems.size() != 0)
	{
		for (const Item& objItem : objItems)
		{
			std::cout << "Displaying information for item " << iCountNumber++ << "...\n";
			std::cout << objItem;
		}
	}
	else
	{
		Nothing_To_Display_Message();
		return false;
	}
	return true;
}

//This procedure displays a warning if the product constitutes less than 5% of sales individually.
void Items::Display_Warning(const double dUnderperformingPercentage) const
{
	double dPercentageOfTotalSales = Total_Quantity_Sold() * dUnderperformingPercentage;
	int iNumberOfItemsUnderperforming = 0;

	if (objItems.size() != 0)
	{
		for (const Item& Item : objItems)
		{
			if (Item.Get_Quantity_Sold() < dPercentageOfTotalSales)
			{
				iNumberOfItemsUnderperforming++;
			}
		}

		if (iNumberOfItemsUnderperforming >= 1)
		{
			std::cout << "#Warning! You have " << iNumberOfItemsUnderperforming << " " << Product_Or_Products(iNumberOfItemsUnderperforming) << " that constitutes less than 5% of total sales.#\n";
		}
		else
		{
			std::cout << "Well done! All your products constitutes to more than 5% of sales individually.\n";
		}
	}
}

//This is an additional feature I added which allows the user to update quantity sold for a specfic item and change it explicitly. This uses a For Loop to iterate through the vector until the name matches. If it does they will subsequently be able to change the quantity's value of the specified item.
bool Items::Update_Quantity_Sold(std::string inputFilePath)
{
	std::string sFindName = "";
	std::string sOriginalQuantity = "";
	int iOriginalQuantity = 0;
	std::string sUpdateQuantitySold = "";
	int iUpdateQuantitySold = 0;

	unsigned char cChoice = 0;
	if (objItems.size() != 0)
	{
		Message_And_Input("Enter the name of the item you wish to update the quantity of: ", &sFindName);
		for (Item& objItem : objItems)
		{
			if (objItem.Get_Item_Name() == sFindName)
			{
				iOriginalQuantity = objItem.Get_Quantity_Sold();
				std::cout << "Update quantity sold from " << objItem.Get_Quantity_Sold() << " to: ";
				std::cin >> sUpdateQuantitySold;
				if (Is_Input_A_Number(sUpdateQuantitySold, &iUpdateQuantitySold) == true) //checks if an error occurs
				{
					do
					{
						Message_And_Input("Are you sure you want to update the quantity of this item? (y/n): ", &cChoice);
					} while (Is_Input_Valid());
					cChoice = std::toupper(cChoice);

					if (cChoice == 'Y')
					{
						objItem.Update_Quantity_Sold(&iUpdateQuantitySold);
						Rewrite_Text_File(inputFilePath);
						std::cout << sFindName << " original quantity has been updated from " << iOriginalQuantity << " to " << iUpdateQuantitySold << ".\n";
						return true;
					}
				}
				else
				{
					Perform_Invalid_Operation();
				}
			}
		}
		std::cout << "Couldn't find '" << sFindName << "'.\n";

	}
	else
	{
		std::cout << "There are currently no items to update.\n";
	}
	return false;
}

//This function has similar logic to "Update_Quantity_Sold()"
bool Items::Update_Item_Name(std::string inputFilePath)
{
	std::string sFindName;
	std::string sUpdateName;
	std::string sOriginalName;
	unsigned char cChoice = 0;
	if (objItems.size() != 0)
	{
		Message_And_Input("Enter the name of the item you wish to rename: ", &sFindName);
		sOriginalName = sFindName;

		for (Item& objItem : objItems)
		{
			if (objItem.Get_Item_Name() == sFindName)
			{
				std::cout << "Change name to: ";
				std::getline(std::cin >> std::ws, sUpdateName);
				if (Check_If_Item_Exists(sUpdateName) == true)
				{
					return false;
				}
				bool bContinue = false;
				do
				{
					do
					{
						Message_And_Input("Are you sure you want to update the name of this item? (y/n): ", &cChoice);
					} while (Is_Input_Valid());

					cChoice = toupper(cChoice);
					if (cChoice == 'Y')
					{
						objItem.Update_Name(&sUpdateName);
						std::cout << sOriginalName << " has been changed to " << sUpdateName << ".\n";
						Rewrite_Text_File(inputFilePath);
						return true;
					}
					else if (cChoice == 'N')
					{
						std::cout << "You've chosen not to rename " << sOriginalName << " to " << sUpdateName << "\n";
						return false;
					}
					else
					{
						bContinue = false;
						Perform_Invalid_Operation();
					}
				} while (bContinue == false);
			}
		}
		std::cout << "Couldn't find '" << sFindName << "'.\n";
	}
	else
	{
		std::cout << "There are currently no items to update.\n";
	}
	return false;
}
//This function returns the average sale
double Items::Average_Sale() const
{
	return Total_Quantity_Sold() / (int)objItems.size();
}

//Calculates the total price.
double Items::Total_Price_Sold() const
{
	auto totalPriceSold = std::accumulate(objItems.begin(), objItems.end(), 0.0,
	[](auto& accum, auto& objItem) { return accum + objItem.Get_Sale_Price();});
	return totalPriceSold;
	
	/*double dTotalPriceSold = 0;
	for (const Item& objItem : objItems)
	{
		dTotalPriceSold += objItem.Get_Sale_Price();
	}
	return dTotalPriceSold;*/
}

