#include "os_lib.h"

#include "error_handling.h"

#include <boost/filesystem/operations.hpp>
#include <sstream>

static void CreateDirectory (const boost::filesystem::path& DirPath)
{
	if (!boost::filesystem::create_directory(DirPath))
	{
		std::stringstream ErrorText;
		ErrorText << "Failed to created Directory " << DirPath << std::endl;
		programError (ErrorText.str());	
	}
} // CreateOutDirectory

bool EnsureDirectoryExists (const std::string DirPath)
{
	bool DirExists = false;

	// Create Directory if not existing already
	if(!boost::filesystem::exists (DirPath))
	{
		boost::filesystem::path Dir(DirPath);
		CreateDirectory(Dir);
		DirExists = true;
	} // if directory doesn't exist yet
	else
	{
		DirExists = true;
	}

	return (DirExists);
} // EnsureDirectoryExists
