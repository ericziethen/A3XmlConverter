#pragma once

#include "tinyxml.h"
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "value_pair.h"

class xml_io
{
public:
	xml_io(void);
	~xml_io(void);
};

void WriteA3XmlData(TiXmlElement*, const std::string&, const std::vector<std::shared_ptr<value_pair>>&);
std::string GetA3StorageFileName (std::string);
void ReadA3XmlData(TiXmlElement*, std::vector<std::shared_ptr<value_pair>>&);
