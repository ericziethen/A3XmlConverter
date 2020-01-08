#pragma once

#include "section.h"

typedef enum
{
	CLEAGUEGRP_SECTION_POS_UNKNOWN = 0,
	CLEAGUEGRP_SECTION_POS_GRUPPEN_NUMMER,
	CLEAGUEGRP_SECTION_POS_ANZAHL_TEAMS,
	CLEAGUEGRP_SECTION_POS_LAND1,
	CLEAGUEGRP_SECTION_POS_VEREIN1,
	CLEAGUEGRP_SECTION_POS_LAND2,
	CLEAGUEGRP_SECTION_POS_VEREIN2,
	CLEAGUEGRP_SECTION_POS_LAND3,
	CLEAGUEGRP_SECTION_POS_VEREIN3,
	CLEAGUEGRP_SECTION_POS_LAND4,
	CLEAGUEGRP_SECTION_POS_VEREIN4,

	// Parent Position, after Section Positions
	CLEAGUEGRP_SECTION_POS_PARENT_SECTION,
	CLEAGUEGRP_SECTION_POS_LAND1_EXPANDED,
	CLEAGUEGRP_SECTION_POS_VEREIN1_EXPANDED,
	CLEAGUEGRP_SECTION_POS_LAND2_EXPANDED,
	CLEAGUEGRP_SECTION_POS_VEREIN2_EXPANDED,
	CLEAGUEGRP_SECTION_POS_LAND3_EXPANDED,
	CLEAGUEGRP_SECTION_POS_VEREIN3_EXPANDED,
	CLEAGUEGRP_SECTION_POS_LAND4_EXPANDED,
	CLEAGUEGRP_SECTION_POS_VEREIN4_EXPANDED,
	NO_OF_CLEAGUEGRP_SECTION_POS_TYPES
} CLEAGUEGRP_SECTION_POS_TYPE;

class cleaguegrp :
	public section
{
public:
	cleaguegrp(void);
	~cleaguegrp(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();
	void DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);

	std::string GruppenNummer;
	std::string AnzahlTeams;
	std::string Land1;
	std::string Verein1;
	std::string Land2;
	std::string Verein2;
	std::string Land3;
	std::string Verein3;
	std::string Land4;
	std::string Verein4;
	
	std::string Land1_Expanded;
	std::string Verein1_Expanded;
	std::string Land2_Expanded;
	std::string Verein2_Expanded;
	std::string Land3_Expanded;
	std::string Verein3_Expanded;
	std::string Land4_Expanded;
	std::string Verein4_Expanded;
};

void AssignCleagueGrpField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromCleagueGrpSectionPosType (const CLEAGUEGRP_SECTION_POS_TYPE);
static CLEAGUEGRP_SECTION_POS_TYPE GetCleagueGrpSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (CLEAGUEGRP_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (CLEAGUEGRP_SECTION_POS_TYPE);
std::string GetCleagueGrpCsvHeader ();
