#pragma once

#include "section.h"
#include "trainer_enum.h"

typedef enum
{
	TRAINER_SECTION_POS_UNKNOWN,
	TRAINER_SECTION_POS_VORNAHME,
	TRAINER_SECTION_POS_NACHNAHME,
	TRAINER_SECTION_POS_KOMPETENZ,
	TRAINER_SECTION_POS_RUF,
	TRAINER_SECTION_POS_ALTER,
	TRAINER_SECTION_POS_GEBURTSDATUM,
	TRAINER_SECTION_POS_UNKNOWN_07,
	TRAINER_SECTION_POS_UNKNOWN_08,

	// Reference Position, after Section Positions
	TRAINER_SECTION_POS_REFERENCE_SECTION,
	NO_OF_TRAINER_SECTION_POS_TYPES
} TRAINER_SECTION_POS_TYPE;

class trainer :
	public section
{
public:
	trainer(void);
	~trainer(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();
	void DecodeEnumsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeEnumsToA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);

	std::string Vornahme;
	std::string Nachnahme;
	std::string Kompetenz;
	std::string Ruf;
	std::string Alter;
	std::string Geburtsdatum;
	std::string TRAINER_FIELD_UNKNOWN_07;
	std::string TRAINER_FIELD_UNKNOWN_08;
};

void AssignTrainerField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromTrainerSectionPosType (const TRAINER_SECTION_POS_TYPE);
static TRAINER_SECTION_POS_TYPE GetTrainerSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (TRAINER_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (TRAINER_SECTION_POS_TYPE);
std::string GetTrainerCsvHeader ();
static void GetEnumDetails (int, int, ENUM_FUNC&, int&, int&);

static TRAINER_ENUM_TYPE GetTrainerEnumTypeFromPosition (TRAINER_SECTION_POS_TYPE);
void GetTrainerAllowedValues (std::vector<FIELD_VALUE_STRUCT>&);
