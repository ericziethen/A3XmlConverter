#include "file_io.h"
#include <fstream>
#include <string>

void openFile (std::ifstream& FileHandleRef, const std::string& FileName)
{
	FileHandleRef.open (FileName.c_str(), std::ifstream::in);
}

void closeFile (std::ifstream& FileHandleRef)
{
	FileHandleRef.close();
}

void getLineFromFile (std::ifstream& FileHandleRef, std::string& LineRef)
{
	std::getline (FileHandleRef, LineRef);
}

