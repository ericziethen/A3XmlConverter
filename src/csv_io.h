#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "value_pair.h"

class csv_io
{
public:
	csv_io(void);
	~csv_io(void);
};

std::string GetA3StorageFileName (std::string);

void ReadA3Data (const std::string&, std::vector<std::shared_ptr<value_pair>>&, int&, bool&);
static void ReadRawCsv (const std::string&, std::vector<std::shared_ptr<value_pair>>&, bool);
void WriteA3Data (std::ofstream&,const std::vector<std::shared_ptr<value_pair>>&, int&);
static void WriteRawCsv (std::ofstream&, const std::vector<std::shared_ptr<value_pair>>&, bool);
void OpenExternalFileForWriting (const std::string&, std::ofstream&);

