#pragma once

#include "section.h"

#define BLANK_LAND_ID "BLANK_LAND_ID"

typedef enum
{
	LAND_SECTION_POS_UNKNOWN,
	LAND_SECTION_POS_POKALWETTBEWERB,
	LAND_SECTION_POS_UNKNOWN_02,
	LAND_SECTION_POS_VEREINSZAHL,
	LAND_SECTION_POS_UNKNOWN_04,
	LAND_SECTION_POS_UNKNOWN_05,
	LAND_SECTION_POS_UNKNOWN_06,
	
	// Special Fields
	LAND_SECTION_POS_LAND_ID,

	// Expanded Fields
	LAND_SECTION_POS_LAND_ID_EXPANDED,

	NO_OF_LAND_SECTION_POS_TYPES
} LAND_SECTION_POS_TYPE;

class land :
	public section
{
public:
	land(void);
	~land(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE land::GetSectionType ();
	bool UpdateLandIdIfNeeded (std::string);
	void DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);

	std::string Pokalwettbewerb;
	std::string LAND_FIELD_UNKNOWN_02;
	std::string VereinsZahl;
	std::string LAND_FIELD_UNKNOWN_04;
	std::string LAND_FIELD_UNKNOWN_05;
	std::string LAND_FIELD_UNKNOWN_06;
	std::string LandId;

	// Expanded Fields
	std::string LandId_Expanded;
};

void AssignLandField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromLandSectionPosType (const LAND_SECTION_POS_TYPE);
static LAND_SECTION_POS_TYPE GetLandSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (LAND_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (LAND_SECTION_POS_TYPE);
std::string GetLandCsvHeader ();
void AssignVereinCountsForLand (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
