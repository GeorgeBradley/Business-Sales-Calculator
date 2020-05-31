#include "Files.h"
#include "Functions.h"
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
	std::cout << "1. Create a new items text file\n";
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

