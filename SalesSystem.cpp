// Sales.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "Accounts.h" //Included for the purposes of a Login System
#include "Functions.h" //This is used to access functions (I created) that are used through all cpp files
#include "Items_Collection.h" //This is used for the main sales system
#include "Files.h"
#include <cctype>
#include <fstream> //This allows for input / output to an external textfile
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string> //included for using std::string
#include <vector> //included so vectors can be used
//Displays menu items
void Display_Menu()
{
	std::cout << "What would you like to do?\nChoose a number from the Menu...\n";
	std::cout << "\t0. Quit application completely.\n";
	std::cout << "\t1. Add item(s)\n";
	std::cout << "\t2. Total quantity of items sold\n";
	std::cout << "\t3. Total price of items sold\n";
	std::cout << "\t4. Most sold item(s)\n";
	std::cout << "\t5. Least sold item(s)\n";
	std::cout << "\t6. Difference in sales between the most and least sold items\n";
	std::cout << "\t7. Estimated operational cost (50% of sales)\n";
	std::cout << "\t8. Show Tax paid (20% of sales)\n";
	std::cout << "\t9. Profit (Total after tax and operational costs)\n";
	std::cout << "\t10. Total amount of money generated\n";
	std::cout << "\t11. Check to see if any items constitutes less than 5% of total sales\n";
	std::cout << "\t12. Show additional options\n";
	std::cout << "\t13. Logout\n";
	std::cout << "\n";
}

//Displays additional menu items
void Display_Additional_Menu()
{
	std::cout << "What would you like to do?\nChoose a number from the additional menu...\n";
	std::cout << "\t0. Back to main menu\n";
	std::cout << "\t1. Display items\n";
	std::cout << "\t2. Delete an item\n";
	std::cout << "\t3. Display underperforming items\n";
	std::cout << "\t4. Update an item name\n";
	std::cout << "\t5. Update quantity sold for an individual item.\n";
	std::cout << "\t6. Delete all items\n";
	std::cout << "\t7. Average quantity sold\n";
	std::cout << "\n";
}

//Runs additional menu system
void AdditionalMenu(Items* objItems, std::string inputFilePath)
{
	int iChoice = 0;
	std::string sChoice = "";
	bool bExitAdditionalMenu = false;
	do
	{
		std::cout << "====================================================\n";
		std::cout << "\t\tSales System | Additional Menu\n";
		std::cout << "====================================================\n";
		Display_Additional_Menu();
		Message_And_Input("Enter a number from the additional menu: ", &sChoice);

		if (Is_Input_A_Number(sChoice, &iChoice) == true)
		{
			switch (iChoice)
			{
			case 0:
				std::cout << "\nYou've chosen option 0.";
				bExitAdditionalMenu = true;
				Confirm_Continue("\nPress any key to continue back to main menu...");
				break;

			case 1:
				std::cout << "\nYou've chosen option 1.\n";
				objItems->Print_Items();
				Confirm_Continue("\nPress any key to continue...");
				break;

			case 2:
				std::cout << "\nYou've chosen option 2.\n";
				objItems->Delete_An_Item(inputFilePath);
				Confirm_Continue("\nPress any key to continue...");
				break;

			case 3:
				std::cout << "\nYou've chosen option 3.\n";
				objItems->Display_Underperforming_Items();
				Confirm_Continue("\nPress any key to continue...");
				break;

			case 4:
				std::cout << "\nYou've chosen option 4.\n";
				objItems->Update_Item_Name(inputFilePath);
				Confirm_Continue("\nPress any key to continue...");
				break;

			case 5:
				std::cout << "\nYou've chosen option 5.\n";
				objItems->Update_Quantity_Sold(inputFilePath);
				Confirm_Continue("\nPress any key to continue...");
				break;

			case 6:
				std::cout << "\nYou've chosen option 6.\n";
				objItems->Delete_All_Items(inputFilePath);
				Confirm_Continue("\nPress any key to continue...");
				break;
			case 7:
				std::cout << "\nYou've chosen option 7.\n";
				if (objItems->Size() != 0)
				{
					std::cout << "Average sale: " << objItems->Average_Sale() << "\n";
				}
				else
				{
					Nothing_To_Display_Message();
				}
				Confirm_Continue("\nPress any key to continue...");
				break;


			default:
				//If the user inputs a number which isn't part of the menu
				std::cout << "\n#You've entered an option that doesn't exist.\n";
				std::cout << "Enter a number listed in the above menu.#\n";
				Confirm_Continue("\nPress any key to continue...");
			}
		}
		else
		{
			//If the user enters characters in the iOption variable
			Confirm_Continue("\nPress any key to continue...");
		}

	} while (bExitAdditionalMenu == false);
}
void Display_Login_Menu() {
	std::cout << "===============================================================================\n";
	std::cout << "\t\tLOGIN TO USE SALES SYSTEM\n";
	std::cout << "===============================================================================\n";
	std::cout << "To use Sales System, please create an account.\n";
	std::cout << "Alternatively you can login with the following guess credentials...\n\n";

	std::cout << "\tUsername: guess\n";
	std::cout << "\tPassword: pass\n\n";

	std::cout << "What would you like to do?\nChoose a number from the menu...\n\n";
	std::cout << "1. Create an Account\n";
	std::cout << "2. Login to Existing Account\n";
	std::cout << "3. Exit program\n";
	std::cout << "\n";

}
//Login System
void Login(Accounts& objAccounts, std::string& inputFilePath)
{
	bool bLoginSuccessful = false; //If this variable becomes true, this means user has successfully logged in
	objAccounts.Add_Text_File_To_Vector(inputFilePath);
	int iMenuChoice = 0; ///This stores the user's menu option selection
	std::string sMenuChoice = "";
	int iLoginAttempts = 4; //This variable stores the amount of login attempts allowed before the program shuts down
	do
	{
		Display_Login_Menu();
		Message_And_Input("Choose a number from the menu: ", &sMenuChoice);
		//First ensuring input is valid before making any comparison for each of each of the cases
		if (Is_Input_A_Number(sMenuChoice, &iMenuChoice))
		{
			switch (iMenuChoice)
			{
			case 1:
				std::cout << "\n";
				objAccounts.Create_Account(inputFilePath);
				Confirm_Continue("\nPress any key to continue...");
				break;

			case 2:
				std::cout << "\n";
				bLoginSuccessful = objAccounts.Login_To_Account(iLoginAttempts); //passes iLoginAttempts variable which is intially set to 4
				break;
			case 3:
				std::cout << "You have exited the program.\n";
				exit(0);
			default:
				std::cout << "\n";
				Display_Invalid_Command_Message();
				Confirm_Continue("\nPress any key to continue...");
			}
		}
		else
		{
			Confirm_Continue("\nPress any key to continue...");
		}
	} while (bLoginSuccessful == false);
}

void Add_Text_File_To_Vector(Items& objItems, std::string& inputFilePath)
{
	std::vector<std::string>objSplit;//Will store contiguously item name, item price, and item quantity
	std::string sLine = "";
	std::string sResult = "";
	std::ifstream file(inputFilePath);

	//This gets the line from the file
	while (getline(file, sLine))
	{
		//This splits the line
		std::stringstream ssSplit(sLine);
		objSplit.resize(0);

		//This uses the delimiter ',' to split
		while (getline(ssSplit, sResult, ','))
		{
			objSplit.push_back(sResult);
		}
		if (objSplit.size() != 0)
		{
			objItems.objItems.push_back({ objSplit.at(0), stod(objSplit.at(1)), stoi(objSplit.at(2)) });
		}
	}
}

//This is the main starting point of execution, it first begins, and ends in this function.
//The main contains the declaration of the user-defined datatype "Items" which is modeled through the means of two structs "Item" singular and "Items" (a vector of Items); Everything pertaining to the item has been used through accessing its member functions / methods through the dot operator e.g. Items.Add_New_Item(). I've put the Items in a menu which operates in a while-loop and have used a switch to allow the user to select an option in the meny I've included error-validation to ensure users don't easily make mistakes. 
int main()
{
	bool bValid = false;
	bool bLogout = false;
	Accounts objUsers; //Declaring instance of Accounts struct (defined and implemented in seperate files, "Accounts.h" and "Accounts.cpp")
	Items objItems; //Declaring instance of Items struct (defined and implemented in seperate files, Items_Collection.h and Items_Collection.cpp)
	std::vector<std::string>objFile;
	//Declaring file pathways.
	std::string inputFilePathUsers = "Users.txt"; //File path name for storing user credentials
	std::string inputFilePathItems = "Items.txt"; // file path name for storing items
	std::string inputFilePathFiles = "Files.txt";
	const double dTaxRate = 0.2; //This is where the tax rate can be modified to reflect calculations made by program
	const double dOperationalCostPercentage = 0.5; //This is where operational cost percentage can be modified to reflect calculations made by program
	const double dUnderperformingPercentage = 0.05;//This is the percentage that makes the comparison as to whether an item is underperforming
	std::cout << std::setprecision(2) << std::fixed;//This ensures currency displays 2 numbers after the decimal place
	Add_Text_File_To_Vector(objItems, inputFilePathItems);//Adds items currently stored in the text file.
	do
	{
		Login(objUsers, inputFilePathUsers);
		File_Menu_System(objFile, inputFilePathFiles);
		do
		{
			
			bLogout = false;
			std::cout << "===========================================\n";
			std::cout << "\t\tSales System | Main Menu\n";
			std::cout << "===========================================\n";
			std::cout << "Test";
			Display_Menu();
			std::string sMenuChoice = "";//Choice will be stored in string for coversion once validated as an INT
			int iMenuChoice = 0;
			std::cout << "You currently have " << objItems.Size() << " items in the system.\n";
			std::cout << "Enter a number from the main menu: ";
			std::cin >> sMenuChoice;

			if (Is_Input_A_Number(sMenuChoice, &iMenuChoice) == true) //Checks to ensure input is valid
			{
				switch (iMenuChoice) //Condition processed here and subsequently checked with each case, if not met, will through an error message.
				{
				case 0:
					std::cout << "\n";
					std::cout << "You have exited the program.\n";
					return 0; //exits out of program

				case 1:
					std::cout << "\n";
					std::cout << "You've chosen option 1 - Add Item(s)\n";
					objItems.Add_Item(inputFilePathItems);
					Confirm_Continue("\nPress any key to continue...");
					break;

				case 2:
					std::cout << "\n";
					std::cout << "You've chosen option 2.\n";
					if (objItems.Size() != 0)
					{
						std::cout << "Total quantity sold is: " << objItems.Total_Quantity_Sold() << ".\n";
					}
					else
					{
						Nothing_To_Display_Message();
					}
					Confirm_Continue("\nPress any key to continue...");
					break;

				case 3:
					std::cout << "\nYou've chosen option 3.\n";
					if (objItems.Size() != 0)
					{
						std::cout << "Total price of items sold: " << char(156) << objItems.Total_Price_Sold() << ".\n";
					}
					else
					{
						Nothing_To_Display_Message();
					}
					Confirm_Continue("\nPress any key to continue...");
					break;
				case 4:
					std::cout << "\nYou've chosen option 4.\n";
					objItems.Display_Most_Sold_Item();
					Confirm_Continue("\nPress any key to continue...");
					break;

				case 5:
					std::cout << "\n";
					std::cout << "You've chosen option 5.\n";
					objItems.Display_Least_Sold_Item();
					Confirm_Continue("\nPress any key to continue...");
					break;

				case 6:
					std::cout << "\n";
					std::cout << "You've chosen option 6.\n";
					if (objItems.Size() == 0)
					{
						Nothing_To_Display_Message();
					}
					else
					{
						std::cout << "Difference between most and least sold: " << objItems.Difference_Between_Least_Most_Sold_Quantity() << ".\n";
					}
					Confirm_Continue("\nPress any key to continue....");
					break;

				case 7:
					std::cout << "\n";
					std::cout << "You've chosen option 7.\n";
					if (objItems.Size() == 0)
					{
						Nothing_To_Display_Message();
					}
					else
					{
						std::cout << "Estimated operational cost (50% of sales): " << char(156) << objItems.Estimated_Operational_Cost(dOperationalCostPercentage) << ".\n";
					}
					Confirm_Continue("\nPress any key to continue...");
					break;
				case 8:
					std::cout << "\n";
					std::cout << "You've chosen option 8.\n";
					if (objItems.Size() == 0)
					{
						Nothing_To_Display_Message();
					}
					else
					{
						std::cout << "Tax paid (20% of sales): " << char(156) << objItems.Tax_To_Pay_Amount(dTaxRate) << ".\n";
					}
					Confirm_Continue("\nPress any key to continue...");
					break;
				case 9:
					std::cout << "\n";
					std::cout << "You've chosen option 9.\n";
					if (objItems.Size() != 0)
					{
						std::cout << "Profit (Total after tax and operational costs): " << char(156) << objItems.Take_Home_Profit(dTaxRate, dOperationalCostPercentage) << ".\n";
					}
					else
					{
						Nothing_To_Display_Message();
					}
					Confirm_Continue("\nPress any key to continue...");
					break;

				case 10:
					if (objItems.Size() != 0)
					{
						std::cout << "\nYou've chosen option 10.\n";
						std::cout << "Total amount of money generated: " << char(156) << objItems.Total_Sales() << "\n";

					}
					else
					{
						Nothing_To_Display_Message();
					}
					Confirm_Continue("\nPress any key to continue...");
					break;

				case 11:

					if (objItems.Size() != 0)
					{
						std::cout << "\nYou've chosen option 11.\n";
						objItems.Display_Warning(dUnderperformingPercentage);
					}
					else
					{
						Nothing_To_Display_Message();
					}
					Confirm_Continue("\nPress any key to continue...");
					break;

				case 12:
					std::cout << "\n";
					std::cout << "You've chosen option 12.";
					Confirm_Continue("\nPress any key to continue to additional menu... ");
					AdditionalMenu(&objItems, inputFilePathItems);
					break;

				case 13:
					std::cout << "\n";
					std::cout << "You've chosen option 13.\n";
					std::cout << "You have logged out.\n";
					Confirm_Continue("\nPress any key to continue...");
					bLogout = true;
					break;

				default:
					std::cout << "\n";
					Display_Invalid_Command_Message();
					Confirm_Continue("\nPress any key to continue");
					break;
				}
			}
			else
			{
				Confirm_Continue();
				std::cout << "\n";
			}
			std::cout << "\n";
		} while (bLogout == false);
	} while (bValid == false);
}

