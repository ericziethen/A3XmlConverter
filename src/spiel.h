#pragma once
#include "section.h"

#define SPIELPLAN_MAX_VEREIN 1000

typedef enum
{
	ROUND_ROBIN_TEAM_UNKNOWN,
	ROUND_ROBIN_TEAM_HOME,
	ROUND_ROBIN_TEAM_AWAY,
	NO_OF_ROUND_ROBIN_TEAM_TYPES
} ROUND_ROBIN_TEAM_TYPE;

typedef enum
{
	SPIEL_SECTION_POS_UNKNOWN = 0,
	SPIEL_SECTION_POS_HEIMMANNSCHAFT,
	SPIEL_SECTION_POS_AUSWAERTSMANNSCHAFT,
	SPIEL_SECTION_POS_SPIELTAG,

	// Parent Position, after Section Positions
	SPIEL_SECTION_POS_PARENT_SECTION,
	NO_OF_SPIEL_SECTION_POS_TYPES
} SPIEL_SECTION_POS_TYPE;

typedef enum
{
	SPIEL_VEREIN_CONVERT_TO_STRING,
	SPIEL_VEREIN_CONVERT_FROM_STRING,
} SPIEL_VEREIN_CONVERT_TYPE;

class spiel :
	public section
{
public:
	spiel(const std::string&, const std::string&, const std::string&);
	spiel(void);
	~spiel(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();
	void CalculateMatchDay (const std::string&, int);
	void ConvertSpielplanSpielVerein (SPIEL_SECTION_POS_TYPE, SPIEL_VEREIN_CONVERT_TYPE, INT_STRING_HASHBIMAP_TYPE);

	std::string Heimmannschaft;
	std::string Auswaertsmannschaft;
	std::string Spieltag;
};

void AssignSpielField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromSpielSectionPosType (const SPIEL_SECTION_POS_TYPE);
static SPIEL_SECTION_POS_TYPE GetSpielSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (SPIEL_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (SPIEL_SECTION_POS_TYPE);
std::string GetSpielCsvHeader ();
bool SortByMatchDay (const std::shared_ptr<section>&, const std::shared_ptr<section>&);
void SortMatchesByMatchDay (std::vector<std::shared_ptr<section>>&);
void ConvertAllSpielTeams (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], SPIEL_VEREIN_CONVERT_TYPE);
void AutogenerateFixtures (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
static void CalcMatchdayFixtures (int, int, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
static int GetRoundRobinList (int [SPIELPLAN_MAX_VEREIN+1], int, int);
static int GetRoundRobinTeamIndex (ROUND_ROBIN_TEAM_TYPE, int, int, int);
