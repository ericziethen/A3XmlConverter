#pragma once

#include "section.h"

typedef enum
{
	SPONSOR_SECTION_POS_UNKNOWN = 0,
	SPONSOR_SECTION_POS_SPONSORENNAHME,
	SPONSOR_SECTION_POS_UNKNOWN_02,
	SPONSOR_SECTION_POS_UNKNOWN_03,
	SPONSOR_SECTION_POS_UNKNOWN_04,
	SPONSOR_SECTION_POS_UNKNOWN_05,
	SPONSOR_SECTION_POS_UNKNOWN_06,
	SPONSOR_SECTION_POS_UNKNOWN_07,
	SPONSOR_SECTION_POS_UNKNOWN_08,
	SPONSOR_SECTION_POS_UNKNOWN_09,
	SPONSOR_SECTION_POS_UNKNOWN_10,
	SPONSOR_SECTION_POS_UNKNOWN_11,
	SPONSOR_SECTION_POS_UNKNOWN_12,
	SPONSOR_SECTION_POS_UNKNOWN_13,
	SPONSOR_SECTION_POS_UNKNOWN_14,
	SPONSOR_SECTION_POS_UNKNOWN_15,
	SPONSOR_SECTION_POS_UNKNOWN_16,
	SPONSOR_SECTION_POS_SCHRIFTART,
	SPONSOR_SECTION_POS_UNKNOWN_18,
	SPONSOR_SECTION_POS_UNKNOWN_19,

	// Parent Position, after Section Positions
	SPONSOR_SECTION_POS_PARENT_SECTION,
	NO_OF_SPONSOR_SECTION_POS_TYPES
} SPONSOR_SECTION_POS_TYPE;

class sponsor :
	public section
{
public:
	sponsor(void);
	~sponsor(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();

	std::string Sponsorennahme;
	std::string SPONSOR_FIELD_UNKNOWN_02;
	std::string SPONSOR_FIELD_UNKNOWN_03;
	std::string SPONSOR_FIELD_UNKNOWN_04;
	std::string SPONSOR_FIELD_UNKNOWN_05;
	std::string SPONSOR_FIELD_UNKNOWN_06;
	std::string SPONSOR_FIELD_UNKNOWN_07;
	std::string SPONSOR_FIELD_UNKNOWN_08;
	std::string SPONSOR_FIELD_UNKNOWN_09;
	std::string SPONSOR_FIELD_UNKNOWN_10;
	std::string SPONSOR_FIELD_UNKNOWN_11;
	std::string SPONSOR_FIELD_UNKNOWN_12;
	std::string SPONSOR_FIELD_UNKNOWN_13;
	std::string SPONSOR_FIELD_UNKNOWN_14;
	std::string SPONSOR_FIELD_UNKNOWN_15;
	std::string SPONSOR_FIELD_UNKNOWN_16;
	std::string Schriftart;
	std::string SPONSOR_FIELD_UNKNOWN_18;
	std::string SPONSOR_FIELD_UNKNOWN_19;

};

void AssignSponsorField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromSponsorSectionPosType (const SPONSOR_SECTION_POS_TYPE);
static SPONSOR_SECTION_POS_TYPE GetSponsorSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (SPONSOR_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (SPONSOR_SECTION_POS_TYPE);
std::string GetSponsorCsvHeader ();