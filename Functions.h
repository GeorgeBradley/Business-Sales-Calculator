#pragma once
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cctype>
#include <fstream> //This allows for input / output to an external textfile
// requires '#include <limits>'
#include <sstream>
#include <conio.h>
#include <algorithm>
std::string Product_Or_Products(int iNumber);
void Display_Invalid_Command_Message();
//Used for ensuring what user has inputted isn't a disproportinate amount
bool Boundary_Check_Value_Is_Valid(int iValue, int iMin, int iMax); //overloaded function to handle ints
bool Boundary_Check_Value_Is_Valid(double dValue, double dMin, double dMax); //overloaded function to handle doubles
void Confirm_Continue(std::string sMessage = "\nPress any key to continue...");
void Message_And_Input(std::string prompt, std::string* value);
void Message_And_Input(std::string prompt, std::size_t stIndex, std::string* value);//Used to display the '£' to demonstrate it's currency
void Message_And_Input(std::string prompt, int* value);
void Message_And_Input(std::string prompt, double* value);
void Message_And_Input(std::string prompt, unsigned char* value);
void Nothing_To_Display_Message();
bool Is_Input_Valid();
bool Is_String_Character_Allowed(std::string sValue);
bool Is_Input_A_Number(std::string sLine, double* dValue);
bool Is_Input_A_Number(std::string sLine, int* iValue);
bool Is_String_Length_Valid(std::string sItemName, const std::size_t stLengthMinimum, const std::size_t stLengthMaximum);
void Perform_Invalid_Operation();
void Clear_Text_File_Contents(std::string inputFilePath);