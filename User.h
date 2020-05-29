#pragma once
#include <iostream>
//This struct models a user and is used to be a vector in the Accounts.hpp
struct User
{
	//User attributes
	std::string sUsername;
	std::string sPassword;
	//Constructor using initalisation list
	User(std::string sInitUsername, std::string sInitPassword)
		:sUsername(sInitUsername), sPassword(sInitPassword) //initalisation
	{
		//Nothing in the body of the constructor as initalisation has been done in the initalisation list two lines above.
	}
};

