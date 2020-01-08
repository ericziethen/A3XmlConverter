#pragma once

#include "section.h"

typedef enum
{
	VPRAESID_SECTION_POS_UNKNOWN = 0,
	VPRAESID_SECTION_POS_VORNAHME,
	VPRAESID_SECTION_POS_NACHNAHME,
	VPRAESID_SECTION_POS_GEBURTSDATUM,

	// Parent Position, after Section Positions
	VPRAESID_SECTION_POS_PARENT_SECTION,
	NO_OF_VPRAESID_SECTION_POS_TYPES
} VPRAESID_SECTION_POS_TYPE;

class vpraesid :
	public section
{
public:
	vpraesid(void);
	~vpraesid(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();

	std::string Vornahme;
	std::string Nachnahme;
	std::string Geburtsdatum;
};

void AssignVpraesidField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromVpraesidSectionPosType (const VPRAESID_SECTION_POS_TYPE);
static VPRAESID_SECTION_POS_TYPE GetVpraesidSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (VPRAESID_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (VPRAESID_SECTION_POS_TYPE);
std::string GetVpraesidCsvHeader ();
