#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Functions.h"
void Display_File_Menu();
void Display_Existing_Files(std::vector<std::string>& objFile, std::string& inputFilePath);
void Add_Text_File_To_Vector(std::vector<std::string>& objFiles, std::string& inputFilePath);
void File_Menu_System(std::vector<std::string>& objFile, std::string& inputFilePath, std::string &ItemFilePath);
void Append_Credential_To_Text_File(std::string& inputFilePath, std::string& sNewTextFile);
bool Add_New_File(std::string& inputFilePath, std::vector<std::string>& objFiles);