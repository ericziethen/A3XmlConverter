#pragma once

#include "section.h"

typedef enum
{
	TURNIERGRP_SECTION_POS_UNKNOWN = 0,
	TURNIERGRP_SECTION_POS_UNKNOWN_01,
	TURNIERGRP_SECTION_POS_ANZAHL_TEAMS,
	TURNIERGRP_SECTION_POS_LAND1,
	TURNIERGRP_SECTION_POS_UNKNOWN_04,
	TURNIERGRP_SECTION_POS_LAND2,
	TURNIERGRP_SECTION_POS_UNKNOWN_06,
	TURNIERGRP_SECTION_POS_LAND3,
	TURNIERGRP_SECTION_POS_UNKNOWN_08,
	TURNIERGRP_SECTION_POS_LAND4,
	TURNIERGRP_SECTION_POS_UNKNOWN_10,

	// Parent Position, after Section Positions
	TURNIERGRP_SECTION_POS_PARENT_SECTION,
	TURNIERGRP_SECTION_POS_LAND1_EXPANDED,
	TURNIERGRP_SECTION_POS_LAND2_EXPANDED,
	TURNIERGRP_SECTION_POS_LAND3_EXPANDED,
	TURNIERGRP_SECTION_POS_LAND4_EXPANDED,
	NO_OF_TURNIERGRP_SECTION_POS_TYPES
} TURNIERGRP_SECTION_POS_TYPE;

class turniergrp :
	public section
{
public:
	turniergrp(void);
	~turniergrp(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();
	void DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);

	std::string TURNIERGRP_FIELD_UNKNOWN_01;
	std::string AnzahlTeams;
	std::string Land1;
	std::string TURNIERGRP_FIELD_UNKNOWN_04;
	std::string Land2;
	std::string TURNIERGRP_FIELD_UNKNOWN_06;
	std::string Land3;
	std::string TURNIERGRP_FIELD_UNKNOWN_08;
	std::string Land4;
	std::string TURNIERGRP_FIELD_UNKNOWN_10;
	std::string Land1_Expanded;
	std::string Land2_Expanded;
	std::string Land3_Expanded;
	std::string Land4_Expanded;
};

void AssignTurnierGrpField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromTurnierGrpSectionPosType (const TURNIERGRP_SECTION_POS_TYPE);
static TURNIERGRP_SECTION_POS_TYPE GetTurnierGrpSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (TURNIERGRP_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (TURNIERGRP_SECTION_POS_TYPE);
std::string GetTurnierGrpCsvHeader ();
