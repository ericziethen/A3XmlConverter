#pragma once

#include "section.h"

typedef enum
{
	TWTRAINER_SECTION_POS_UNKNOWN = 0,
	TWTRAINER_SECTION_POS_VORNAHME,
	TWTRAINER_SECTION_POS_NACHNAHME,
	TWTRAINER_SECTION_POS_KOMPETENZ,
	TWTRAINER_SECTION_POS_ALTER,
	TWTRAINER_SECTION_POS_GEBURTSDATUM,
	TWTRAINER_SECTION_POS_UNKNWON_06,
	TWTRAINER_SECTION_POS_UNKNOWN_07,

	// Parent Position, after Section Positions
	TWTRAINER_SECTION_POS_PARENT_SECTION,
	NO_OF_TWTRAINER_SECTION_POS_TYPES
} TWTRAINER_SECTION_POS_TYPE;

class twtrainer :
	public section
{
public:
	twtrainer(void);
	~twtrainer(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();

	std::string Vornahme;
	std::string Nachnahme;
	std::string Kompetenz;
	std::string Alter;
	std::string Geburtsdatum;
	std::string TWTRAINER_FIELD_UNKNOWN_06;
	std::string TWTRAINER_FIELD_UNKNOWN_07;
};

void AssignTwTrainerField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromTwTrainerSectionPosType (const TWTRAINER_SECTION_POS_TYPE);
static TWTRAINER_SECTION_POS_TYPE GetTwTrainerSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (TWTRAINER_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (TWTRAINER_SECTION_POS_TYPE);
std::string GetTwTrainerCsvHeader ();
