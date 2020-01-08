#pragma once
#include "section.h"

typedef enum
{
	ASPIELER_SECTION_POS_UNKNOWN = 0,
	ASPIELER_SECTION_POS_VORNAHME,
	ASPIELER_SECTION_POS_NACHNAHME,

	// Parent Position, after Section Positions
	ASPIELER_SECTION_POS_PARENT_SECTION,
	NO_OF_ASPIELER_SECTION_POS_TYPES
} ASPIELER_SECTION_POS_TYPE;

class aspieler :
	public section
{
public:
	aspieler(void);
	~aspieler(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();

	std::string Vornahme;
	std::string Nachnahme;
};

void AssignASpielerField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromASpielerSectionPosType (const ASPIELER_SECTION_POS_TYPE);
static ASPIELER_SECTION_POS_TYPE GetASpielerSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (ASPIELER_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (ASPIELER_SECTION_POS_TYPE);
std::string GetASpielerCsvHeader ();
