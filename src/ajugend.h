#pragma once
#include "section.h"
#include "ajugend_enum.h"

typedef enum
{
	AJUGEND_SECTION_POS_UNKNOWN = 0,
	AJUGEND_SECTION_POS_VORNAHME,
	AJUGEND_SECTION_POS_NACHNAHME,
	AJUGEND_SECTION_POS_VEREIN,
	AJUGEND_SECTION_POS_POSITION,

	// Parent Position, after Section Positions
	AJUGEND_SECTION_POS_PARENT_SECTION,
	AJUGEND_SECTION_POS_VEREIN_EXPANDED,
	NO_OF_AJUGEND_SECTION_POS_TYPES
} AJUGEND_SECTION_POS_TYPE;

class ajugend :
	public section
{
public:
	ajugend(void);
	~ajugend(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();
	void DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE ReferenceType, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void DecodeEnumsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeEnumsToA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);

	std::string Vornahme;
	std::string Nachnahme;
	std::string Verein;
	std::string Verein_EXPANDED;
	std::string Position;
};

void AssignAJugendField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromAJugendSectionPosType (const AJUGEND_SECTION_POS_TYPE);
static AJUGEND_SECTION_POS_TYPE GetAJugendSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (AJUGEND_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (AJUGEND_SECTION_POS_TYPE);
std::string GetAJugendCsvHeader ();
static void GetEnumDetails (int, int, ENUM_FUNC&, int&, int&);

static AJUGEND_ENUM_TYPE GetAJugendEnumTypeFromPosition (AJUGEND_SECTION_POS_TYPE);
void GetAJugendAllowedValues (std::vector<FIELD_VALUE_STRUCT>&);
