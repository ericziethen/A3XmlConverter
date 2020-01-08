#pragma once

#include "section.h"

typedef enum
{
	EUROSIEGER_SECTION_POS_UNKNOWN = 0,
	EUROSIEGER_SECTION_POS_UNKNOWN_01,
	EUROSIEGER_SECTION_POS_UNKNOWN_02,
	EUROSIEGER_SECTION_POS_UNKNOWN_03,

	// Parent Position, after Section Positions
	EUROSIEGER_SECTION_POS_PARENT_SECTION,
	NO_OF_EUROSIEGER_SECTION_POS_TYPES
} EUROSIEGER_SECTION_POS_TYPE;

class eurosieger :
	public section
{
public:
	eurosieger(void);
	~eurosieger(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();

	std::string EUROSIEGER_FIELD_UNKNOWN_01;
	std::string EUROSIEGER_FIELD_UNKNOWN_02;
	std::string EUROSIEGER_FIELD_UNKNOWN_03;
};

void AssignEurosiegerField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromEurosiegerSectionPosType (const EUROSIEGER_SECTION_POS_TYPE);
static EUROSIEGER_SECTION_POS_TYPE GetEurosiegerSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (EUROSIEGER_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (EUROSIEGER_SECTION_POS_TYPE);
std::string GetEurosiegerCsvHeader ();
