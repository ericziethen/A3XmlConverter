#include "spiel.h"
#include "error_handling.h"
#include "misc_lib.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include "spielplan_verein.h"
#include "liga.h"


spiel::spiel(const std::string& Heimmannschaft, const std::string& Auswaertsmannschaft, const std::string& Spieltag)
{
	this->Heimmannschaft = Heimmannschaft;
	this->Auswaertsmannschaft = Auswaertsmannschaft;
	this->Spieltag = Spieltag;
}

spiel::spiel(void)
{
}

spiel::~spiel(void)
{
}

std::string spiel::GetUniqueId ()
{
	return(this->Spieltag + this->Heimmannschaft + this->Auswaertsmannschaft);
} // GetUniqueId

SECTION_TYPE spiel::GetSectionType ()
{
	return(SECTION_TYPE_SPIEL_HIDDEN);
} // GetSectionType

std::string spiel::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case SPIEL_SECTION_POS_SPIELTAG:
		return (this->Spieltag);
	case SPIEL_SECTION_POS_HEIMMANNSCHAFT:
		return (this->Heimmannschaft);
	case SPIEL_SECTION_POS_AUSWAERTSMANNSCHAFT:
		return (this->Auswaertsmannschaft);

			// Parent Section
	case SPIEL_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromSpielSectionPosType (const SPIEL_SECTION_POS_TYPE SpielSectionPosType)
{
	switch (SpielSectionPosType)
	{
	case SPIEL_SECTION_POS_SPIELTAG:
		return ("Spieltag");
	case SPIEL_SECTION_POS_HEIMMANNSCHAFT:
		return ("Heimmannschaft");
	case SPIEL_SECTION_POS_AUSWAERTSMANNSCHAFT:
		return ("Auswaertsmannschaft");

	case SPIEL_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << SpielSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromSpielSectionPosType

void spiel::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case SPIEL_SECTION_POS_SPIELTAG:
		this->Spieltag = FieldValue;
		break;
	case SPIEL_SECTION_POS_HEIMMANNSCHAFT:
		this->Heimmannschaft = FieldValue;
		break;
	case SPIEL_SECTION_POS_AUSWAERTSMANNSCHAFT:
		this->Auswaertsmannschaft = FieldValue;
		break;

			// Parent Section	
	case SPIEL_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void spiel::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int SpielPos = SPIEL_SECTION_POS_UNKNOWN + 1; SpielPos < NO_OF_SPIEL_SECTION_POS_TYPES; SpielPos++)
	{
		if (IncludeSectionPosIntoXml ((SPIEL_SECTION_POS_TYPE) SpielPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromSpielSectionPosType ((SPIEL_SECTION_POS_TYPE) SpielPos), 			
				this->GetValueAtSectionPos(SpielPos))));
		}
	}

} // PopulateValuePairVectorForExport

void spiel::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& SpielValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = SpielValuePairs.begin(); 
		Iterator != SpielValuePairs.end(); ++Iterator)
	{
		SPIEL_SECTION_POS_TYPE FieldPos = GetSpielSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != SPIEL_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void spiel::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = SPIEL_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_SPIEL_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((SPIEL_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void spiel::CalculateMatchDay (const std::string& NoOfLigaTeamsString, int NoOfMatchdaysIncludingThis)
{
	int NoOfLigaTeams = T_StringToNumber<int>(NoOfLigaTeamsString);
	double MatchesPerMatchDay = NoOfLigaTeams / 2; // Assuming for now all leagues have even number of teams

	// The Matchday is calculated by The Number of Matches divided by the Number of matches per match day and this result rounded up
	double MatchDayNumber = std::ceil(NoOfMatchdaysIncludingThis / MatchesPerMatchDay);

	this->AssignField(SPIEL_SECTION_POS_SPIELTAG, std::to_string(MatchDayNumber));
} // CalculateMatchDay

void spiel::ConvertSpielplanSpielVerein (SPIEL_SECTION_POS_TYPE SectionPos, SPIEL_VEREIN_CONVERT_TYPE ConvertType, INT_STRING_HASHBIMAP_TYPE VereinMap)
{
	// Get the Verein Value to Convert
	int VereinValue;
	std::string VereinValueString = this->GetValueAtSectionPos(SectionPos);
	std::string VereinString;

	// Lookup the String Value
	switch (ConvertType)
	{
	case SPIEL_VEREIN_CONVERT_TO_STRING:
		VereinValue = T_StringToNumber<int>(VereinValueString);
		VereinString = T_GetRightBimapValue<int, std::string>(VereinValue, VereinMap);
		break;

	case SPIEL_VEREIN_CONVERT_FROM_STRING:
		VereinValue = T_GetLeftBimapValue<int, std::string>(VereinValueString, VereinMap);
		VereinString = std::to_string(VereinValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled ConvertType: " << ConvertType <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	// Store the Value
	this->AssignField (SectionPos, VereinString);
} // DecodeFieldsFromA3Db

static bool IncludeSectionPosIntoA3Db (SPIEL_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case SPIEL_SECTION_POS_HEIMMANNSCHAFT:
	case SPIEL_SECTION_POS_AUSWAERTSMANNSCHAFT:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case SPIEL_SECTION_POS_SPIELTAG:
	case SPIEL_SECTION_POS_PARENT_SECTION:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromSpielSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (SPIEL_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case SPIEL_SECTION_POS_HEIMMANNSCHAFT:
	case SPIEL_SECTION_POS_AUSWAERTSMANNSCHAFT:
	case SPIEL_SECTION_POS_SPIELTAG:
	case SPIEL_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromSpielSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static SPIEL_SECTION_POS_TYPE GetSpielSectionPosTypeFromString (const std::string& TypeString)
{
	SPIEL_SECTION_POS_TYPE FoundPos = SPIEL_SECTION_POS_UNKNOWN;

	for (int TempPos = SPIEL_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_SPIEL_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromSpielSectionPosType ((SPIEL_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (SPIEL_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetSpielSectionPosTypeFromString

void AssignSpielField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<spiel>(SectionList, SectionLineCount, Line);
} // AssignSpielField

std::string GetSpielCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = SPIEL_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_SPIEL_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromSpielSectionPosType ((SPIEL_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetSpielCsvHeader

bool SortByMatchDay (const std::shared_ptr<section>& Match1, const std::shared_ptr<section>& Match2)
{
	return (T_StringToNumber<int> (std::static_pointer_cast<spiel>(Match1)->GetValueAtSectionPos (SPIEL_SECTION_POS_SPIELTAG)) < 
			T_StringToNumber<int> (std::static_pointer_cast<spiel>(Match2)->GetValueAtSectionPos (SPIEL_SECTION_POS_SPIELTAG)));
} // SortByMatchDay

void SortMatchesByMatchDay (std::vector<std::shared_ptr<section>>& MatchList)
{
	std::sort(MatchList.begin(), MatchList.end(), SortByMatchDay);
} // SortMatchesByMatchDay


void ConvertAllSpielTeams (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], SPIEL_VEREIN_CONVERT_TYPE ConvertType)
{
	// Get the Vereine
	INT_STRING_HASHBIMAP_TYPE VereinMap;
	PopulateSpielplanVereinMap(SectionList, VereinMap);

	VereinMap.insert (boost::bimap<int, std::string>::value_type(1, "Test"));

//	for( INT_STRING_HASHBIMAP_TYPE::const_iterator iter = VereinMap.begin(), iend = VereinMap.end(); iter != iend; ++iter )
//		std::cout << iter->left << " <--> " << iter->right << std::endl;

	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	std::vector<std::shared_ptr<section>> VereinList = SectionList [SECTION_TYPE_SPIEL_HIDDEN];
	for (SectionIterator = VereinList.begin(); SectionIterator != VereinList.end(); ++SectionIterator)
	{
		std::static_pointer_cast<spiel>(*SectionIterator)->ConvertSpielplanSpielVerein (
			SPIEL_SECTION_POS_HEIMMANNSCHAFT, ConvertType, VereinMap);
		std::static_pointer_cast<spiel>(*SectionIterator)->ConvertSpielplanSpielVerein (
			SPIEL_SECTION_POS_AUSWAERTSMANNSCHAFT, ConvertType, VereinMap);
	} // for each spiel
} // ConvertAllSpielTeams

static int GetRoundRobinTeamIndex (ROUND_ROBIN_TEAM_TYPE TeamType, int MatchDay, int MatchNo, int NoOfTeams)
{
	int TeamIndex = -9000;
	switch (TeamType)
	{
	case ROUND_ROBIN_TEAM_HOME:
		// Home Teams are from 1 to NoOfTeams/2 
		TeamIndex = MatchNo;
		break;

	case ROUND_ROBIN_TEAM_AWAY:
		TeamIndex = (NoOfTeams + 1) - MatchNo;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Round Robin Type " << TeamType << " -> " << __FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return (TeamIndex);
} // GetRoundRobinTeamIndex

static int GetRoundRobinList (int RoundRobinList [SPIELPLAN_MAX_VEREIN+1], int MatchDay, int NoOfTeams)
{
	int TeamsInList = 0;

	if ((NoOfTeams % 2) == 0)
		TeamsInList = NoOfTeams; // even number of teams
	else
		TeamsInList = NoOfTeams + 1; // originally odd no of teams
	
	// Check if we don't exceed the max number of teams allowed
	if (TeamsInList > SPIELPLAN_MAX_VEREIN)
	{
		std::stringstream ErrorText;
		ErrorText << "Max Number of Teams allowed is " << SPIELPLAN_MAX_VEREIN-1 << ", trying to import " << NoOfTeams << " -> " << __FUNCTION__;
		programError ( ErrorText.str());
	}

	int Team1 = 1;
	RoundRobinList[1] = Team1;
	
	// For each Position from 1
	for (int Pos = 2; Pos <= TeamsInList; Pos++)
	{
		// Get the Team Value for this Position
		int TargetValue = Pos + (MatchDay - 1);
		if (TargetValue > TeamsInList) // rollover
			RoundRobinList [Pos] = Team1 + (TargetValue - TeamsInList);
		else
			RoundRobinList [Pos] = TargetValue;
	} 
/*
	Set 1 tp Position 1
	for each position (2 .. NoOfTeams)
		get IndexValue (NoOfTeams, MatchDay, Index
			if (Pos) + MatchDay - 1) > NoOfTeams
				Set Index to 1 + (NoOfTeams - Pos)
			else
				Set Index to ((Pos) + MatchDay)
*/
	return (TeamsInList);
} // GetRoundRobinList

static void CalcMatchdayFixtures (int MatchDay, int NoOfTeams, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Get the Round Robin list for this Match Day
	int RoundRobinList [SPIELPLAN_MAX_VEREIN+1] = {0};

	// Get the Number of Teams including any padded team for Odd number of teams
	int ActualTeamCount = GetRoundRobinList (RoundRobinList, MatchDay, NoOfTeams);
	int NoOfMatchedPerDay = ActualTeamCount / 2;

	std::string ParentId = std::static_pointer_cast<liga>(SectionList[SECTION_TYPE_LIGA].back())->GetUniqueId();

	// Calculate the First Round Matches
	for (int MatchNo = 1; MatchNo <= NoOfMatchedPerDay; MatchNo++)
	{
		int HomeTeam = RoundRobinList [GetRoundRobinTeamIndex (ROUND_ROBIN_TEAM_HOME, MatchDay, MatchNo, ActualTeamCount)];
		int AwayTeam = RoundRobinList [GetRoundRobinTeamIndex (ROUND_ROBIN_TEAM_AWAY, MatchDay, MatchNo, ActualTeamCount)];

		if ((HomeTeam <= NoOfTeams) && (AwayTeam <= NoOfTeams))
		{
			SectionList[SECTION_TYPE_SPIEL_HIDDEN].push_back(std::shared_ptr<spiel> (
				new spiel(std::to_string(HomeTeam), std::to_string(AwayTeam), std::to_string(MatchDay))));
			std::static_pointer_cast<spiel>(SectionList[SECTION_TYPE_SPIEL_HIDDEN].back())->AssignField(SPIEL_SECTION_POS_PARENT_SECTION, ParentId);
		} // if both teams an original team
	} // for each match on the Match day
} // CalcMatchdayFixtures

void AutogenerateFixtures (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Clear all Current Fixtures
	SectionList [SECTION_TYPE_SPIEL_HIDDEN].clear();

	// Get the Numbers of Teams
	size_t NumberOfTeams = SectionList [SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN].size();

	// Set the Number in the League
	std::static_pointer_cast<liga>(SectionList[SECTION_TYPE_LIGA].back())->
		AssignField (LIGA_SECTION_POS_VEREINSANZAHL, std::to_string(NumberOfTeams));

	// Calc number of unique Match Days
	int UniqueMatchDays = NumberOfTeams - 1;

	// Calc fixtures of the first round
	for (int MatchDay = 1; MatchDay <= UniqueMatchDays; MatchDay++)
	{
		CalcMatchdayFixtures (MatchDay, NumberOfTeams, SectionList);
	} // for each unique match day
	
	// Calculate the Second Round Matches
	int MatchesSoFar = SectionList [SECTION_TYPE_SPIEL_HIDDEN].size();
		
	std::string ParentId = std::static_pointer_cast<liga>(SectionList[SECTION_TYPE_LIGA].back())->GetUniqueId();
	for (int MatchNo = 0; MatchNo < MatchesSoFar; MatchNo++)
	{
		const std::shared_ptr<spiel> CurrentMatch = std::static_pointer_cast<spiel>(SectionList [SECTION_TYPE_SPIEL_HIDDEN].at(MatchNo));

		// Calculate the MatchDay
		int NewMatchDay = T_StringToNumber<int>(CurrentMatch->GetValueAtSectionPos(SPIEL_SECTION_POS_SPIELTAG)) + UniqueMatchDays;

		// Create the new Match
		SectionList[SECTION_TYPE_SPIEL_HIDDEN].push_back(std::shared_ptr<spiel> (new spiel(
			CurrentMatch->GetValueAtSectionPos(SPIEL_SECTION_POS_AUSWAERTSMANNSCHAFT),
			CurrentMatch->GetValueAtSectionPos(SPIEL_SECTION_POS_HEIMMANNSCHAFT),
			std::to_string(NewMatchDay))));

		// Set Parent Sections
		std::static_pointer_cast<spiel>(SectionList[SECTION_TYPE_SPIEL_HIDDEN].back())->AssignField(SPIEL_SECTION_POS_PARENT_SECTION, ParentId);

	} // for the number of existing matches
} // AutogenerateFixtures