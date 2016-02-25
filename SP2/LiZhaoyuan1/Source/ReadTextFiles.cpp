#include "ReadTextFile.h"

bool ReadFromTxt(const char* file_path, std::vector<std::string> &Text)
{
	std::ifstream myfile(file_path, std::ios::binary);
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			char reading[256];
			myfile.getline(reading, 256);
			Text.push_back(reading);
		}
		myfile.close();
		return true;
	}
	else
	{
		std::cout << "cannot read" << std::endl;
		return false;
	}
}