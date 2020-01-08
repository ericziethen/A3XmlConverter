#pragma once

#include "section.h"
#include "reporter_enum.h"

typedef enum
{
	REPORTER_SECTION_POS_UNKNOWN = 0,
	REPORTER_SECTION_POS_SENDER,
	REPORTER_SECTION_POS_NACHNAHME,
	REPORTER_SECTION_POS_VORNAHME,
	REPORTER_SECTION_POS_BOESELIEB,

	// Parent Position, after Section Positions
	REPORTER_SECTION_POS_PARENT_SECTION,
	NO_OF_REPORTER_SECTION_POS_TYPES
} REPORTER_SECTION_POS_TYPE;

class reporter :
	public section
{
public:
	reporter(void);
	~reporter(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();
	void DecodeEnumsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeEnumsToA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);

	std::string Sender;
	std::string Nachnahme;
	std::string Vornahme;
	std::string BoeseLieb;
};

void AssignReporterField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromReporterSectionPosType (const REPORTER_SECTION_POS_TYPE);
static REPORTER_SECTION_POS_TYPE GetReporterSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (REPORTER_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (REPORTER_SECTION_POS_TYPE);
std::string GetReporterCsvHeader ();
static void GetEnumDetails (int, int, ENUM_FUNC&, int&, int&);

static REPORTER_ENUM_TYPE GetReporterEnumTypeFromPosition (REPORTER_SECTION_POS_TYPE);
void GetReporterAllowedValues (std::vector<FIELD_VALUE_STRUCT>&);
