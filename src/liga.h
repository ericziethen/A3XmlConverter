#pragma once
#include "section.h"

typedef enum
{
	LIGA_SECTION_POS_UNKNOWN = 0,
	LIGA_SECTION_POS_LIGA_NAHME,
	LIGA_SECTION_POS_LIGA_KUERZL,
	LIGA_SECTION_POS_VEREINSANZAHL,

	// Parent Position, after Section Positions
	LIGA_SECTION_POS_PARENT_SECTION,
	NO_OF_LIGA_SECTION_POS_TYPES
} LIGA_SECTION_POS_TYPE;

class liga :
	public section
{
public:
	liga(void);
	~liga(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();

	std::string Liganame;
	std::string Ligakuerzl;
	std::string Vereinsanzahl;
};

void AssignLigaField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromLigaSectionPosType (const LIGA_SECTION_POS_TYPE);
static LIGA_SECTION_POS_TYPE GetLigaSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (LIGA_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (LIGA_SECTION_POS_TYPE);
std::string GetLigaCsvHeader ();
