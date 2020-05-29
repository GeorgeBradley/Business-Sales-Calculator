//Accounts.cpp (where functions are implemented for the Accounts.h file)
#include "Accounts.h"
//Checks if username exists within the vector<User>

//This function is used to change decrement the iLoginAttempts variable (from the sales.cpp in the function void Login())
void Accounts::Login_Attempts(int& iLoginAttempts)
{
	std::cout << "#You have entered incorrect login details.#\n";
	std::cout << "You have " << iLoginAttempts - 1 << " attempts left before the program shuts down completely.";
	iLoginAttempts--;
	if (iLoginAttempts == 0) //if iLoginAttempts reaches 0 the body will exit out of the program.
	{
		std::cout << "You've had enough chances! We're closing the program down for security reasons.\n";
		exit(0); //This exits out of the program 
	}
}
//This checks if username exists to prevent duplicate usernames
bool Accounts::Does_Username_Exist(std::string& sUsername)
{
	for (const User& objUser : objUsers)
	{
		if (sUsername == objUser.sUsername)
		{
			std::cout << "Sorry, someone already has this username.\n";
			return true;
		}
	}
	return false;
}
//This function is used everytime an update is made within the vector<Item>.
void Accounts::Rewrite_Text_File(std::string inputFilePath)
{

	std::ofstream file;
	file.open(inputFilePath);
	for (const User& objUser : objUsers)
	{
		file << objUser.sUsername << "," << objUser.sPassword << ",\n";
	}
	file.close();
}

//Checks if Login details are correct.
bool Accounts::Is_Login_Details_Correct(std::string& sInputtedUsername, std::string& sInputtedPassword, int& iAttempts)
{
	for (const User& objUser : objUsers)
	{
		if (objUser.sUsername == sInputtedUsername && objUser.sPassword == sInputtedPassword)
		{
			std::cout << "You have successfully logged in.";
			Confirm_Continue("\nPress any key to continue...");
			return true;
		}
	}
	Login_Attempts(iAttempts);
	Confirm_Continue("\nPress any key to continue...");
	return false;
}

//This checks if the length of the username is valid
bool Accounts::Is_Length_of_Username_Valid(std::string sUsername, std::size_t stMinLength) const
{
	if (sUsername.size() < stMinLength)
	{
		std::cout << "\n";
		std::cout << "The username you've is too short.\nPlease enter a username that is at least 5 characters long.";
		return false;
	}
	return true;
}

//This checks if the password is secure, ascertaining that by the length
bool Accounts::Is_Password_Secure(std::string sPassword)
{
	std::cout << "\n";
	if (sPassword.size() < 5)
	{
		std::cout << "Your password isn't very strong. Please try again.\n\n";
		return false;
	}
	return true;
}
//Creates an account for user.
bool Accounts::Create_Account(std::string& inputFilePath)
{
	std::string sUsername;
	std::string sPassword;
	unsigned char cChoice = 0;
	std::cout << "Create new user.\n";
	Message_And_Input("Enter a new username: ", &sUsername);
	if (Is_Length_of_Username_Valid(sUsername, 2) == true && Is_String_Character_Allowed(sUsername) == true)
	{
		if (Does_Username_Exist(sUsername) == false)
		{
			do
			{
				do
				{
					Message_And_Input("Enter your new password: ", &sPassword);

				} while (Is_String_Character_Allowed(sPassword) == false);

			} while (Is_Password_Secure(sPassword) == false);
			bool bContinue = false;
			do
			{
				do
				{
					Message_And_Input("Do you wish to create an account with the details you've just provided? (y/n): ", &cChoice);
				} while (Is_Input_Valid());


				cChoice = toupper(cChoice);
				if (cChoice == 'Y')
				{
					std::cout << "Account successfully created!\n";
					Append_Credential_To_Text_File(inputFilePath, sUsername, sPassword);
					objUsers.push_back({ sUsername, sPassword });
					return true;
				}
				else if (cChoice == 'N')
				{
					std::cout << "You have chosen to cancel the creation of your account.\n";
					return false;
				}
				else
				{
					bContinue = false;
					Perform_Invalid_Operation();
					std::cout << "\n";
				}

			} while (bContinue == false);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
//where user logins in to account
bool Accounts::Login_To_Account(int& iLoginAttempts)
{
	std::string sInputUsername;
	std::string sInputPassword;
	std::cout << "Login using either guess or personal credentials\n"; \
		Enter_Credentials(sInputUsername, sInputPassword);
	if (Is_Login_Details_Correct(sInputUsername, sInputPassword, iLoginAttempts) == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//This appends a new credential to text file
void Accounts::Append_Credential_To_Text_File(std::string& inputFilePath, std::string& sUsername, std::string& sPassword)
{
	std::ofstream file;
	file.open(inputFilePath, std::ios_base::app);
	file << sUsername << "," << sPassword << ",\n";
	file.close();
}

//This add's text file to vector.
void Accounts::Add_Text_File_To_Vector(std::string& inputFilePath)
{
	std::vector<std::string>objSplit;
	std::string sLine = "";
	std::string sResult = "";
	std::ifstream file(inputFilePath);

	while (getline(file, sLine))
	{
		std::stringstream ssSplit(sLine);
		objSplit.resize(0);

		while (getline(ssSplit, sResult, ','))
		{
			objSplit.push_back(sResult);
		}
		if (objSplit.size() != 0)
		{
			objUsers.push_back({ objSplit.at(0), objSplit.at(1) });
		}
	}
}

//This is where user enters their username and password
void Accounts::Enter_Credentials(std::string& sInputUsername, std::string& sInputPassword)
{
	Message_And_Input("Enter your username: ", &sInputUsername);
	Message_And_Input("Enter your password: ", &sInputPassword);
	std::cout << "\n";
}
