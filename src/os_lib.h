#pragma once

#include <boost/filesystem/path.hpp>

static void CreateOutDirectory (const boost::filesystem::path&);
bool EnsureDirectoryExists (const std::string);
