#pragma once

#include <string>
#include <vector>
#include <memory>
#include "section.h"

#define XML_STORAGE_FOLDER_NAME		"SavToXml"
#define SAV_STORAGE_FOLDER_NAME		"XmlToSav"
#define XML_STORAGE_DIR				XML_STORAGE_FOLDER_NAME "\\" 
#define SAV_STORAGE_DIR				XML_STORAGE_DIR SAV_STORAGE_FOLDER_NAME "\\"

void WriteAllowedValueList (const SECTION_TYPE, const std::string [MAX_ALLOWED_FIELD_VALUES][NO_OF_SECTION_TYPES], const int, const int);
void WriteA3DbExternalFile (const std::string&, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);
bool ReadA3DbExternalFile (const std::string&, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
static std::string FormXmlStorageName (const std::string&, SECTION_TYPE);
static void PopulateValuePairsFromSection (SECTION_TYPE, std::vector<std::shared_ptr<section>>::iterator&, 
											std::vector<std::shared_ptr<value_pair>>&, const std::string&);
static void PopulateSectionFromValuePairs (SECTION_TYPE, std::vector<std::shared_ptr<section>>&, std::vector<std::shared_ptr<value_pair>>&);
