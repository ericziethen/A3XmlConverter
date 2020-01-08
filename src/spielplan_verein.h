#pragma once
#include "section.h"

typedef enum
{
	SPIELPLAN_VEREIN_SECTION_POS_UNKNOWN = 0,
	SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME,

	// Parent Position, after Section Positions
	SPIELPLAN_VEREIN_SECTION_POS_PARENT_SECTION,
	SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME_EXPANDED,
	NO_OF_SPIELPLAN_VEREIN_SECTION_POS_TYPES
} SPIELPLAN_VEREIN_SECTION_POS_TYPE;

class spielplan_verein :
	public section
{
public:
	spielplan_verein(void);
	~spielplan_verein(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();
	void DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);

	std::string Vereinsname;
	std::string Vereinsname_Expanded;
};

void AssignSpielplan_VereinField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromSpielplan_VereinSectionPosType (const SPIELPLAN_VEREIN_SECTION_POS_TYPE);
static SPIELPLAN_VEREIN_SECTION_POS_TYPE GetSpielplan_VereinSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (SPIELPLAN_VEREIN_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (SPIELPLAN_VEREIN_SECTION_POS_TYPE);
std::string GetSpielplan_VereinCsvHeader ();
void PopulateSpielplanVereinMap (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], INT_STRING_HASHBIMAP_TYPE&);
