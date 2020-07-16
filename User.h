#pragma once
#include <iostream>
//This struct models a user and is used to be a vector in the Accounts.hpp
class User
{
private:
	//User attributes
	std::string sUsername;
	std::string sPassword;
public:
	//Constructor using initalisation list
	User(std::string sInitUsername, std::string sInitPassword)
		:sUsername(sInitUsername), sPassword(sInitPassword) //initalisation
	{
		//Nothing in the body of the constructor as initalisation has been done in the initalisation list two lines above.
	}
	std::string Get_User_Name() const{
		return sUsername;
	}
	std::string Get_Password() const {
		return sPassword;
	}
	~User() {

	}
};

