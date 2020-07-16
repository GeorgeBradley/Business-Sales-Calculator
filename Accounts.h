#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "User.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "Functions.h"
#include <cstdlib> 
//This is the Login System struct called Accounts.
class Accounts
{
private:
	std::vector<User>objUsers; // account attribute
public:
	void Login_Attempts(int& iLoginAttempts);
	void Rewrite_Text_File(std::string inputFilePath);
	bool Is_Password_Secure(std::string sPassword);
	bool Is_Length_of_Username_Valid(std::string sUsername, std::size_t stMinLength) const;
	bool Does_Username_Exist(std::string& sUsername);
	bool Is_Login_Details_Correct(std::string& sInputtedUsername, std::string& sInputtedPassword, int& iAttempts);
	bool Create_Account(std::string& inputFilePath);
	bool Login_To_Account(int& iLoginAttempts);
	void Append_Credential_To_Text_File(std::string& inputFilePath, std::string& sUsername, std::string& sPassword);
	void Add_Text_File_To_Vector(std::string& inputFilePath);
	void Enter_Credentials(std::string& sInputUsername, std::string& sInputPassword);
};
