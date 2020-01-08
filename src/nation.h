#pragma once

#include "section.h"

#define NATION_MAX_INDEX 127

typedef enum
{
	NATION_SECTION_POS_UNKNOWN = 0,
	NATION_SECTION_POS_LAND,
	NATION_SECTION_POS_UNKNOWN_02,
	NATION_SECTION_POS_KUERZEL,
	NATION_SECTION_POS_UNKNOWN_04,
	NATION_SECTION_POS_UNKNOWN_05,
	NATION_SECTION_POS_UNKNOWN_06,
	NATION_SECTION_POS_UNKNOWN_07,
	NATION_SECTION_POS_UNKNOWN_08,
	NATION_SECTION_POS_UNKNOWN_09,
	NATION_SECTION_POS_UNKNOWN_10,
	NATION_SECTION_POS_UNKNOWN_11,

	NATION_SECTION_POS_VEREINSANZAHL,

	// Parent Position, after Section Positions
	NATION_SECTION_POS_PARENT_SECTION,
	NO_OF_NATION_SECTION_POS_TYPES
} NATION_SECTION_POS_TYPE;

class nation :
	public section
{
public:
	nation(void);
	~nation(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();
	void IncrementVereinCount (int);

	std::string Land;
	std::string NATION_FIELD_UNKNOWN_02;
	std::string Kuerzel;
	std::string NATION_FIELD_UNKNOWN_04;
	std::string NATION_FIELD_UNKNOWN_05;
	std::string NATION_FIELD_UNKNOWN_06;
	std::string NATION_FIELD_UNKNOWN_07;
	std::string NATION_FIELD_UNKNOWN_08;
	std::string NATION_FIELD_UNKNOWN_09;
	std::string NATION_FIELD_UNKNOWN_10;
	std::string NATION_FIELD_UNKNOWN_11;
	
	std::string Vereinsanzahl;
};

void AssignNationField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromNationSectionPosType (const NATION_SECTION_POS_TYPE);
static NATION_SECTION_POS_TYPE GetNationSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (NATION_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (NATION_SECTION_POS_TYPE);
std::string GetNationCsvHeader ();
bool SortByNationCode (const std::shared_ptr<section>& Nation1, const std::shared_ptr<section>& Nation2);
std::string NationValueToNationString (const std::string&, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
std::string NationStringToNationValue (const std::string&, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
