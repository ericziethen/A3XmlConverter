#pragma once

#include <fstream>

void openFile (std::ifstream&, const std::string&);
void closeFile (std::ifstream&);
void getLineFromFile (std::ifstream&, std::string &);