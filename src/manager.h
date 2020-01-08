#pragma once

#include "section.h"

typedef enum
{
	MANAGER_SECTION_POS_UNKNOWN = 0,
	MANAGER_SECTION_POS_VORNAHME,
	MANAGER_SECTION_POS_NACHNAHME,
	MANAGER_SECTION_POS_KOMPETENZ,
	MANAGER_SECTION_POS_ALTER,
	MANAGER_SECTION_POS_GEBURTSDATUM,

	// Reference Position, after Section Positions
	MANAGER_SECTION_POS_REFERENCE_SECTION,
	NO_OF_MANAGER_SECTION_POS_TYPES
} MANAGER_SECTION_POS_TYPE;

class manager :
	public section
{
public:
	manager(void);
	~manager(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE manager::GetSectionType ();

	std::string Vornahme;
	std::string Nachnahme;
	std::string Kompetenz;
	std::string Alter;
	std::string Geburtsdatum;
};

void AssignManagerField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromManagerSectionPosType (const MANAGER_SECTION_POS_TYPE);
static MANAGER_SECTION_POS_TYPE GetManagerSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (MANAGER_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (MANAGER_SECTION_POS_TYPE);
std::string GetManagerCsvHeader ();
