//  Functions.cpp
//  Sale System
//These functions are used throughout all cpp files
#include "Functions.h"
//Clears all contents in the the text file.

//This wipes an entire text file blank
bool Boundary_Check_Value_Is_Valid(int iValue, int iMin, int iMax)
{
	if (iValue < iMin)
	{
		std::cout << "\nToo low! Try again!\n\n";
		return false;
	}
	if (iValue > iMax)
	{
		std::cout << "\nToo high! Try again!\n\n";
		return false;
	}
	return true;
}

bool Boundary_Check_Value_Is_Valid(double dValue, double iMin, double iMax) {
	if (dValue < iMin)
	{
		std::cout << "\nThe number you have entered is too low! Try again!\n\n";
		return false;
	}
	if (dValue > iMax)
	{
		std::cout << "\nThe number you have entered is too high! Try again!\n\n";
		return false;
	}
	return true;
}
bool Is_Input_A_Number(std::string sLine, double* dValue) {

	for (const unsigned char& c : sLine)
	{
		if (isalpha(c) || isspace(c))
		{
			std::cout << "\n#Invalid input!\nEnter a number with no characters or spaces, and don't enter a ridiculous amount!\n\n#";
			return false;
		}
	}
	try
	{
		*dValue = stod(sLine);
	}
	catch (...)
	{
		std::cout << "\n#Invalid input!\nEnter a number with no characters or spaces, and don't enter a ridiculous amount!\n\n#";
		return false;
	}
	return true;
}
//This function takes a string through the parameter and then checks if it has either has characters or spaces
bool Is_Input_A_Number(std::string sLine, int* iValue) {

	for (const unsigned char& c : sLine)
	{
		if (isalpha(c) || isspace(c) || !isdigit(c))
		{
			std::cout << "\n#Invalid input! Enter a number with no characters or spaces.#";
			return false;
		}
	}
	//if an exception is caused with the conversion e.g. it going beyond the scope of the INT size it will catch it
	try
	{
		*iValue = stoi(sLine);
	}
	catch (...)
	{
		std::cout << "\n#Invalid input! Enter a number with no characters or spaces.#";
		return false;
	}

	return true;
}


void Clear_Text_File_Contents(std::string inputFilePath)
{
	std::ofstream ofs;
	ofs.open(inputFilePath, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}
void Nothing_To_Display_Message()
{
	std::cout << "\n\t#There is currently nothing to display.\n\tPlease use option 1 in the main menu to add item(s).#\n";
}

void Display_Invalid_Command_Message()
{
	std::cout << "#Invalid command, please try again.#";
}
//This function ensures that the user can't enter the character ',' due to it being used as a delimiter when saving and loading files
bool Is_String_Character_Allowed(std::string sValue)
{
	for (const char& c : sValue)
	{
		if (c == ',')
		{
			std::cout << "\n',' is not allowed.\n";
			std::cout << "Please enter valid characters only!\n";
			return false;
		}
	}
	return true;
}
//This is used for sentencing one of my sentences for the procedure "Display_Warning()", 
//if more than one item underperformed it will display "products" 
//as in plural, and if only one item underperformed (less than 5% of total sales) 
//then "product" as in singular will be displayed.
std::string Product_Or_Products(int iNumber)
{
	return (iNumber > 1) ? "products" : "product";
}
//This clears the std::cin buffer if an error is detected after the std:: failed
void Perform_Invalid_Operation() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "\n";
	Display_Invalid_Command_Message();
}

//These are overloaded functions to display a message as well input into the console
void Message_And_Input(std::string prompt, std::string* value)
{
	std::cout << prompt;
	std::getline(std::cin >> std::ws, *value);


}
//These are overloaded functions to display a message as well input into the console
void Message_And_Input(std::string prompt, const std::size_t iIndex, std::string* value)
{
	std::cout << prompt;
	std::cout << char(iIndex);
	std::getline(std::cin >> std::ws, *value);
}
//Overloaded function which displays a message of whatever is passed in and an input of datatype "int"
void Message_And_Input(std::string prompt, int* value)
{
	std::cout << prompt;
	std::cin >> *value;
}
//Overloaded function which displays a message of whatever is passed in and an input of datatype "double"
void Message_And_Input(std::string prompt, double* value)
{
	std::cout << prompt;
	std::cout << char(156);
	std::cin >> *value;

}
//Overloaded function which displays a message of whatever is passed in and an input of datatype "char"
void Message_And_Input(std::string prompt, unsigned char* value) {
	std::cout << prompt;
	std::cin >> *value;
}

bool Is_Input_Valid() //This checks whether the std:cin is valid
{
	bool bError = false;
	if (!std::cin)
	{
		Perform_Invalid_Operation();
		bError = true;
	}
	else
	{
		bError = false;
	}
	return bError;
}

void Confirm_Continue(std::string sMessage)
{
	std::cout << sMessage; //This displays whatever message is passed into parameter
	_getch(); //This pauses the program to allow the user to decide when to continue
	system("cls"); //This clears the screen
}
bool Is_String_Length_Valid(std::string sString, const std::size_t stLengthMinimum, const std::size_t stLengthMaximum)
{
	if (sString.size() < stLengthMinimum)
	{

		std::cout << "\n\t#The item name you're trying to enter is too short!\n\tTry again!\n";
		return false;
	}
	else if (sString.size() > stLengthMaximum)
	{
		std::cout << "\n\t#The item name you're trying to enter is too long!\n\tTry again!\n";
		return false;
	}
	else
	{
		return true;
	}

}