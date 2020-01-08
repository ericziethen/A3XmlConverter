#include "fixture.h"
#include "error_handling.h"
#include <sstream>
#include <iostream>

fixture::fixture(void)
{
}

fixture::~fixture(void)
{
}

std::string fixture::GetUniqueId ()
{
	return(this->Matchday + this->Hometeam + this->Awayteam);
} // GetUniqueId

SECTION_TYPE fixture::GetSectionType ()
{
	return(SECTION_TYPE_FIXTURE_HIDDEN);
} // GetSectionType

std::string fixture::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case FIXTURE_SECTION_POS_MATCHDAY:
		return (this->Matchday);
	case FIXTURE_SECTION_POS_HOMETEAM:
		return (this->Hometeam);
	case FIXTURE_SECTION_POS_AWAYTEAM:
		return (this->Awayteam);

			// Parent Section
	case FIXTURE_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromFixtureSectionPosType (const FIXTURE_SECTION_POS_TYPE FixtureSectionPosType)
{
	switch (FixtureSectionPosType)
	{
	case FIXTURE_SECTION_POS_MATCHDAY:
		return ("FIXTURE_SECTION_ENUM_POS_MATCHDAY");
	case FIXTURE_SECTION_POS_HOMETEAM:
		return ("FIXTURE_SECTION_ENUM_POS_HOMETEAM");
	case FIXTURE_SECTION_POS_AWAYTEAM:
		return ("FIXTURE_SECTION_ENUM_POS_AWAYTEAM");

	case FIXTURE_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << FixtureSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromFixtureSectionPosType

void fixture::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case FIXTURE_SECTION_POS_MATCHDAY:
		this->Matchday = FieldValue;
		break;
	case FIXTURE_SECTION_POS_HOMETEAM:
		this->Hometeam = FieldValue;
		break;
	case FIXTURE_SECTION_POS_AWAYTEAM:
		this->Awayteam = FieldValue;
		break;

			// Parent Section	
	case FIXTURE_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void fixture::PopulateValuePairVector (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int FixturePos = FIXTURE_SECTION_POS_UNKNOWN + 1; FixturePos < NO_OF_FIXTURE_SECTION_POS_TYPES; FixturePos++)
	{
		ValuePairVector.push_back(std::shared_ptr<value_pair> (
			new value_pair(GetNameFromFixtureSectionPosType ((FIXTURE_SECTION_POS_TYPE) FixturePos), 			
			this->GetValueAtSectionPos(FixturePos))));
	}

} // PopulateValuePairVector

void fixture::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& FixtureValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = FixtureValuePairs.begin(); 
		Iterator != FixtureValuePairs.end(); ++Iterator)
	{
		FIXTURE_SECTION_POS_TYPE FieldPos = GetFixtureSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != FIXTURE_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void fixture::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = FIXTURE_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_FIXTURE_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((FIXTURE_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

static bool IncludeSectionPosIntoA3Db (FIXTURE_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case FIXTURE_SECTION_POS_MATCHDAY:
	case FIXTURE_SECTION_POS_HOMETEAM:
	case FIXTURE_SECTION_POS_AWAYTEAM:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case FIXTURE_SECTION_POS_PARENT_SECTION:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromFixtureSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static FIXTURE_SECTION_POS_TYPE GetFixtureSectionPosTypeFromString (const std::string& TypeString)
{
	FIXTURE_SECTION_POS_TYPE FoundPos = FIXTURE_SECTION_POS_UNKNOWN;

	for (int TempPos = FIXTURE_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_FIXTURE_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromFixtureSectionPosType ((FIXTURE_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (FIXTURE_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetFixtureSectionPosTypeFromString

void AssignFixtureField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<fixture>(SectionList, SectionLineCount, Line);
} // AssignFixtureField

std::string GetFixtureCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = FIXTURE_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_FIXTURE_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromFixtureSectionPosType ((FIXTURE_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetFixtureCsvHeader
