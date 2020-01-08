#pragma once
#include "section.h"

typedef enum
{
	FIXTURE_SECTION_POS_UNKNOWN = 0,
	FIXTURE_SECTION_POS_HOMETEAM,
	FIXTURE_SECTION_POS_AWAYTEAM,
	FIXTURE_SECTION_POS_MATCHDAY,

	// Parent Position, after Section Positions
	FIXTURE_SECTION_POS_PARENT_SECTION,
	NO_OF_FIXTURE_SECTION_POS_TYPES
} FIXTURE_SECTION_POS_TYPE;

class fixture :
	public section
{
public:
	fixture(void);
	~fixture(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVector (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();

	std::string Hometeam;
	std::string Awayteam;
	std::string Matchday;
};

void AssignFixtureField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromFixtureSectionPosType (const FIXTURE_SECTION_POS_TYPE);
static FIXTURE_SECTION_POS_TYPE GetFixtureSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (FIXTURE_SECTION_POS_TYPE);
std::string GetFixtureCsvHeader ();
