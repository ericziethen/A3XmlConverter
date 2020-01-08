#pragma once

#include "section.h"
#include "schiri_enum.h"

typedef enum
{
	SCHIRI_SECTION_POS_UNKNOWN = 0,
	SCHIRI_SECTION_POS_VORNAHME,
	SCHIRI_SECTION_POS_NACHNAHME,
	SCHIRI_SECTION_POS_KOMPETENZ,
	SCHIRI_SECTION_POS_HAERTE,
	SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN,
	SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN,

	// Parent Position, after Section Positions
	SCHIRI_SECTION_POS_PARENT_SECTION,

	// Split Bitmasks
	SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER,
	SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER,
	SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN,
	SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL,
	SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING,

	// Expanded Fields
	SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN_EXPANDED,
	
	NO_OF_SCHIRI_SECTION_POS_TYPES
} SCHIRI_SECTION_POS_TYPE;

class schiri :
	public section
{
public:
	schiri(void);
	~schiri(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();
	void DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void SplitBitmaskFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void MergeBitmaskFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void GetGenericSplitFieldsForField (int, std::vector<int>&);
	bool GetBooleanTargetFieldForEnumVal (const int, const int, int&);
	void DecodeBooleansFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeBooleansToA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);

	std::string Vornahme;
	std::string Nachnahme;
	std::string Kompetenz;
	std::string Haerte;
	std::string UnbeliebterVerein;
	std::string UnbeliebterVerein_Expanded;
	std::string Schiedsrichtereigenschaften;
	
	// Split Bitmasks
	std::string Schiedsrichtereigenschaften_Split_Bitmask_HeimSchiedsrichter;
	std::string Schiedsrichtereigenschaften_Split_Bitmask_GastSchiedsrichter;
	std::string Schiedsrichtereigenschaften_Split_Bitmask_HasstMeckern;
	std::string Schiedsrichtereigenschaften_Split_Bitmask_HasstZeitspiel;
	std::string Schiedsrichtereigenschaften_Split_Bitmask_HasstCoaching;
};

void AssignSchiriField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromSchiriSectionPosType (const SCHIRI_SECTION_POS_TYPE);
static SCHIRI_SECTION_POS_TYPE GetSchiriSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (SCHIRI_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (SCHIRI_SECTION_POS_TYPE);
std::string GetSchiriCsvHeader ();

SCHIRI_BOOLEAN_TYPE GetSchiriBooleanTypeFromPosition (SCHIRI_SECTION_POS_TYPE);
void GetSchiriAllowedValues (std::vector<FIELD_VALUE_STRUCT>&);
