#pragma once

#include "section.h"
#include "schiri_enum.h"

typedef enum
{
	ISCHIRI_SECTION_POS_UNKNOWN = 0,
	ISCHIRI_SECTION_POS_NACHNAHME,
	ISCHIRI_SECTION_POS_VORNAHME,
	ISCHIRI_SECTION_POS_KOMPETENZ,
	ISCHIRI_SECTION_POS_HAERTE,
	ISCHIRI_SECTION_POS_NATIONALITAET,
	ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN,

	// Parent Position, after Section Positions
	ISCHIRI_SECTION_POS_PARENT_SECTION,

	// Split Bitmasks
	ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER,
	ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER,
	ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN,
	ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL,
	ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING,

	NO_OF_ISCHIRI_SECTION_POS_TYPES
} ISCHIRI_SECTION_POS_TYPE;

class ischiri:
	public section
{
public:
	ischiri(void);
	~ischiri(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();
	void SplitBitmaskFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void MergeBitmaskFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void GetGenericSplitFieldsForField (int, std::vector<int>&);
	bool GetBooleanTargetFieldForEnumVal (const int, const int, int&);
	void DecodeBooleansFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeBooleansToA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);

	std::string Nachnahme;
	std::string Vornahme;
	std::string Kompetenz;
	std::string Haerte;
	std::string Nationalitaet;
	std::string Schiedsrichtereigenschaften;

	// Split Bitmasks
	std::string Schiedsrichtereigenschaften_Split_Bitmask_HeimSchiedsrichter;
	std::string Schiedsrichtereigenschaften_Split_Bitmask_GastSchiedsrichter;
	std::string Schiedsrichtereigenschaften_Split_Bitmask_HasstMeckern;
	std::string Schiedsrichtereigenschaften_Split_Bitmask_HasstZeitspiel;
	std::string Schiedsrichtereigenschaften_Split_Bitmask_HasstCoaching;
};

void AssignISchiriField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromISchiriSectionPosType (const ISCHIRI_SECTION_POS_TYPE);
static ISCHIRI_SECTION_POS_TYPE GetISchiriSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (ISCHIRI_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (ISCHIRI_SECTION_POS_TYPE);
std::string GetISchiriCsvHeader ();

SCHIRI_BOOLEAN_TYPE GetISchiriBooleanTypeFromPosition (ISCHIRI_SECTION_POS_TYPE);
void GetISchiriAllowedValues (std::vector<FIELD_VALUE_STRUCT>&);
