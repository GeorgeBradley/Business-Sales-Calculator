#include "Files.h"

void File_Menu_System(std::vector<std::string>& objFile, std::string& inputFilePath)
{
	std::string sChoice = "";
	bool bExit = false;
	int iChoice = 0;

	do 
	{
		Display_File_Menu();
		Message_And_Input("Enter a number from the menu: ", &sChoice);
		if (Is_Input_A_Number(sChoice, &iChoice) == true)
		{
			switch (iChoice)
			{
			case 1:

				break;
			case 2:
				Display_Existing_Files(objFile, inputFilePath);
				break;
			default:
				std::cout << "You've entered an invalid command, please try again!\n";
			}
		}
		else
		{
			Confirm_Continue();
		}
	} 
	while (bExit == false);
	

}
void Display_File_Menu() 
{
	std::cout << "What would you like to do?\nChoose a number from the file menu...\n";
	std::cout << "1. Create a text file to store items in\n";
	std::cout << "2. Choose from an existing file\n";
}

void Display_Existing_Files(std::vector<std::string>& objFiles, std::string& inputFilePath)
{
	Add_Text_File_To_Vector(objFiles, inputFilePath);
	for (std::size_t stCount = 0; stCount < objFiles.size(); stCount++)
	{
		std::cout << stCount + 1 << ". " << objFiles.at(stCount);
	}
}

//This add's text file to vector.
void Add_Text_File_To_Vector(std::vector<std::string>&objFiles, std::string& inputFilePath)
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
			objFiles.push_back({ objSplit.at(0)});
		}
	}
}
bool Add_New_File(std::string &inputFilePath, std::vector<std::string>objFiles)
{
	
	std::string sNameOfNewTextFile;
	Message_And_Input("Enter name of new text file: ", &sNameOfNewTextFile);
	for (std::string objFile : objFiles)
	{
		if (objFile == sNameOfNewTextFile)
		{
			std::cout << "That file name already exists!\n";
			return false;
		}
	}
	std::cout << "Successfully added!\n";
	Append_Credential_To_Text_File(inputFilePath, sNameOfNewTextFile);
	return true;

}
void Append_Credential_To_Text_File(std::string& inputFilePath, std::string& sNewTextFile)
{
	std::ofstream file;
	file.open(inputFilePath, std::ios_base::app);
	file << sNewTextFile << ",\n";
	file.close();
}