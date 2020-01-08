#pragma once

#include "section.h"

typedef enum
{
	KRITIKER_SECTION_POS_UNKNOWN = 0,
	KRITIKER_SECTION_POS_NACHNAHME,
	KRITIKER_SECTION_POS_VORNAHME,

	// Parent Position, after Section Positions
	KRITIKER_SECTION_POS_PARENT_SECTION,
	NO_OF_KRITIKER_SECTION_POS_TYPES
} KRITIKER_SECTION_POS_TYPE;

class kritiker :
	public section
{
public:
	kritiker(void);
	~kritiker(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();

	std::string Nachnahme;
	std::string Vornahme;
};

void AssignKritikerField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromKritikerSectionPosType (const KRITIKER_SECTION_POS_TYPE);
static KRITIKER_SECTION_POS_TYPE GetKritikerSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (KRITIKER_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (KRITIKER_SECTION_POS_TYPE);
std::string GetKritikerCsvHeader ();
