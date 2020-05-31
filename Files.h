#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

void Display_File_Menu();
void Display_Existing_Files(std::vector<std::string>& objFile, std::string& inputFilePath);
void Add_Text_File_To_Vector(std::vector<std::string>& objFiles, std::string& inputFilePath);
void File_Menu_System(std::vector<std::string>& objFile, std::string& inputFilePath);
