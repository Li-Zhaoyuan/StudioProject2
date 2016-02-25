#ifndef READ_TEXT_FILE_H
#define READ_TEXT_FILE_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

bool ReadFromTxt(const char* file_path, std::vector<std::string> &Text);

#endif