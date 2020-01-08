#pragma once

#include "section.h"

typedef enum
{
	IVEREIN_SECTION_POS_UNKNOWN = 0,
	IVEREIN_SECTION_POS_VEREINSNAHME,
	IVEREIN_SECTION_POS_LAND,

	// Parent Position, after Section Positions
	IVEREIN_SECTION_POS_PARENT_SECTION,
	IVEREIN_SECTION_POS_LAND_EXPANDED,
	NO_OF_IVEREIN_SECTION_POS_TYPES
} IVEREIN_SECTION_POS_TYPE;

class iverein :
	public section
{
public:
	iverein(void);
	~iverein(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();
	void DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);

	std::string Vereinsnahme;
	std::string Land;
	std::string Land_Expanded;
};

void AssignIVereinField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromIVereinSectionPosType (const IVEREIN_SECTION_POS_TYPE);
static IVEREIN_SECTION_POS_TYPE GetIVereinSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (IVEREIN_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (IVEREIN_SECTION_POS_TYPE);
std::string GetIVereinCsvHeader ();
