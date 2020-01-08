#pragma once

#include "section.h"

typedef enum
{
	AMATEURV_SECTION_POS_UNKNOWN = 0,
	AMATEURV_SECTION_POS_VEREINSNAHME,

	// Parent Position, after Section Positions
	AMATEURV_SECTION_POS_PARENT_SECTION,
	NO_OF_AMATEURV_SECTION_POS_TYPES
} AMATEURV_SECTION_POS_TYPE;

class amateurv :
	public section
{
public:
	amateurv(void);
	~amateurv(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();

	std::string Vereinsnahme;
};

void AssignAmateurvField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromAmateurvSectionPosType (const AMATEURV_SECTION_POS_TYPE);
static AMATEURV_SECTION_POS_TYPE GetAmateurvSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (AMATEURV_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (AMATEURV_SECTION_POS_TYPE);
std::string GetAmateurvCsvHeader ();
