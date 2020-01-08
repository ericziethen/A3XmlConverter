#pragma once

#include "section.h"

typedef enum
{
	PROMI_SECTION_POS_UNKNOWN = 0,
	PROMI_SECTION_POS_NACHNAHME,
	PROMI_SECTION_POS_VORNAHME,
	PROMI_SECTION_POS_LIEBLINGSVEREIN,

	// Parent Position, after Section Positions
	PROMI_SECTION_POS_PARENT_SECTION,
	PROMI_SECTION_POS_LIEBLINGSVEREIN_EXPANDED,
	NO_OF_PROMI_SECTION_POS_TYPES
} PROMI_SECTION_POS_TYPE;

class promi :
	public section
{
public:
	promi(void);
	~promi(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();
	void DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);

	std::string Nachnahme;
	std::string Vornahme;
	std::string Lieblingsverein;
	std::string Lieblingsverein_Expanded;
};

void AssignPromiField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromPromiSectionPosType (const PROMI_SECTION_POS_TYPE);
static PROMI_SECTION_POS_TYPE GetPromiSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (PROMI_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (PROMI_SECTION_POS_TYPE);
std::string GetPromiCsvHeader ();
