#include "turniergrp.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

turniergrp::turniergrp(void)
{
}

turniergrp::~turniergrp(void)
{
}

std::string turniergrp::GetUniqueId ()
{
	return(this->Land1 + this->Land2 + this->Land3 +
			this->Land4);
} // GetUniqueId

SECTION_TYPE turniergrp::GetSectionType ()
{
	return(SECTION_TYPE_TURNIERGRP);
} // GetSectionType

std::string turniergrp::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case TURNIERGRP_SECTION_POS_UNKNOWN_01:
		return (this->TURNIERGRP_FIELD_UNKNOWN_01);
	case TURNIERGRP_SECTION_POS_ANZAHL_TEAMS:
		return (this->AnzahlTeams);
	case TURNIERGRP_SECTION_POS_LAND1:
		return (this->Land1);
	case TURNIERGRP_SECTION_POS_UNKNOWN_04:
		return (this->TURNIERGRP_FIELD_UNKNOWN_04);
	case TURNIERGRP_SECTION_POS_LAND2:
		return (this->Land2);
	case TURNIERGRP_SECTION_POS_UNKNOWN_06:
		return (this->TURNIERGRP_FIELD_UNKNOWN_06);
	case TURNIERGRP_SECTION_POS_LAND3:
		return (this->Land3);
	case TURNIERGRP_SECTION_POS_UNKNOWN_08:
		return (this->TURNIERGRP_FIELD_UNKNOWN_08);
	case TURNIERGRP_SECTION_POS_LAND4:
		return (this->Land4);
	case TURNIERGRP_SECTION_POS_UNKNOWN_10:
		return (this->TURNIERGRP_FIELD_UNKNOWN_10);
	case TURNIERGRP_SECTION_POS_LAND1_EXPANDED:
		return (this->Land1_Expanded);
	case TURNIERGRP_SECTION_POS_LAND2_EXPANDED:
		return (this->Land2_Expanded);
	case TURNIERGRP_SECTION_POS_LAND3_EXPANDED:
		return (this->Land3_Expanded);
	case TURNIERGRP_SECTION_POS_LAND4_EXPANDED:
		return (this->Land4_Expanded);

			// Parent Section
	case TURNIERGRP_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromTurnierGrpSectionPosType (const TURNIERGRP_SECTION_POS_TYPE TurnierGrpSectionPosType)
{
	switch (TurnierGrpSectionPosType)
	{
	case TURNIERGRP_SECTION_POS_UNKNOWN_01:
		return ("TURNIERGRP_FIELD_UNKNOWN_01");
	case TURNIERGRP_SECTION_POS_ANZAHL_TEAMS:
		return ("AnzahlTeams");
	case TURNIERGRP_SECTION_POS_LAND1:
		return ("Land1_UNEXPANDED");
	case TURNIERGRP_SECTION_POS_UNKNOWN_04:
		return ("TURNIERGRP_FIELD_UNKNOWN_04");
	case TURNIERGRP_SECTION_POS_LAND2:
		return ("Land2_UNEXPANDED");
	case TURNIERGRP_SECTION_POS_UNKNOWN_06:
		return ("TURNIERGRP_FIELD_UNKNOWN_06");
	case TURNIERGRP_SECTION_POS_LAND3:
		return ("Land3_UNEXPANDED");
	case TURNIERGRP_SECTION_POS_UNKNOWN_08:
		return ("TURNIERGRP_FIELD_UNKNOWN_08");
	case TURNIERGRP_SECTION_POS_LAND4:
		return ("Land4_UNEXPANDED");
	case TURNIERGRP_SECTION_POS_UNKNOWN_10:
		return ("TURNIERGRP_FIELD_UNKNOWN_10");
	case TURNIERGRP_SECTION_POS_LAND1_EXPANDED:
		return ("Land1");
	case TURNIERGRP_SECTION_POS_LAND2_EXPANDED:
		return ("Land2");
	case TURNIERGRP_SECTION_POS_LAND3_EXPANDED:
		return ("Land3");
	case TURNIERGRP_SECTION_POS_LAND4_EXPANDED:
		return ("Land4");

	case TURNIERGRP_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << TurnierGrpSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromTurnierGrpSectionPosType

void turniergrp::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case TURNIERGRP_SECTION_POS_UNKNOWN_01:
		this->TURNIERGRP_FIELD_UNKNOWN_01 = FieldValue;
		break;
	case TURNIERGRP_SECTION_POS_ANZAHL_TEAMS:
		this->AnzahlTeams = FieldValue;
		break;
	case TURNIERGRP_SECTION_POS_LAND1:
		this->Land1 = FieldValue;
		break;
	case TURNIERGRP_SECTION_POS_UNKNOWN_04:
		this->TURNIERGRP_FIELD_UNKNOWN_04 = FieldValue;
		break;
	case TURNIERGRP_SECTION_POS_LAND2:
		this->Land2 = FieldValue;
		break;
	case TURNIERGRP_SECTION_POS_UNKNOWN_06:
		this->TURNIERGRP_FIELD_UNKNOWN_06 = FieldValue;
		break;
	case TURNIERGRP_SECTION_POS_LAND3:
		this->Land3 = FieldValue;
		break;
	case TURNIERGRP_SECTION_POS_UNKNOWN_08:
		this->TURNIERGRP_FIELD_UNKNOWN_08 = FieldValue;
		break;
	case TURNIERGRP_SECTION_POS_LAND4:
		this->Land4 = FieldValue;
		break;
	case TURNIERGRP_SECTION_POS_UNKNOWN_10:
		this->TURNIERGRP_FIELD_UNKNOWN_10 = FieldValue;
		break;
	case TURNIERGRP_SECTION_POS_LAND1_EXPANDED:
		this->Land1_Expanded = FieldValue;
		break;
	case TURNIERGRP_SECTION_POS_LAND2_EXPANDED:
		this->Land2_Expanded = FieldValue;
		break;
	case TURNIERGRP_SECTION_POS_LAND3_EXPANDED:
		this->Land3_Expanded = FieldValue;
		break;
	case TURNIERGRP_SECTION_POS_LAND4_EXPANDED:
		this->Land4_Expanded = FieldValue;
		break;

			// Parent Section	
	case TURNIERGRP_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void turniergrp::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int TurnierGrpPos = TURNIERGRP_SECTION_POS_UNKNOWN + 1; TurnierGrpPos < NO_OF_TURNIERGRP_SECTION_POS_TYPES; TurnierGrpPos++)
	{
		if (IncludeSectionPosIntoXml ((TURNIERGRP_SECTION_POS_TYPE) TurnierGrpPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromTurnierGrpSectionPosType ((TURNIERGRP_SECTION_POS_TYPE) TurnierGrpPos), 			
				this->GetValueAtSectionPos(TurnierGrpPos))));
		}
	}

} // PopulateValuePairVectorForExport

void turniergrp::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& TurnierGrpValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = TurnierGrpValuePairs.begin(); 
		Iterator != TurnierGrpValuePairs.end(); ++Iterator)
	{
		TURNIERGRP_SECTION_POS_TYPE FieldPos = GetTurnierGrpSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != TURNIERGRP_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void turniergrp::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = TURNIERGRP_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_TURNIERGRP_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((TURNIERGRP_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void turniergrp::DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Land Fields
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, TURNIERGRP_SECTION_POS_LAND1, TURNIERGRP_SECTION_POS_LAND1_EXPANDED, SectionList);
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, TURNIERGRP_SECTION_POS_LAND2, TURNIERGRP_SECTION_POS_LAND2_EXPANDED, SectionList);
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, TURNIERGRP_SECTION_POS_LAND3, TURNIERGRP_SECTION_POS_LAND3_EXPANDED, SectionList);
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, TURNIERGRP_SECTION_POS_LAND4, TURNIERGRP_SECTION_POS_LAND4_EXPANDED, SectionList);
} // DecodeFieldsFromA3Db

void turniergrp::EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE ReferenceType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	switch (ReferenceType)
	{
	case FIELD_REFERENCE_LAND:
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, TURNIERGRP_SECTION_POS_LAND1_EXPANDED, TURNIERGRP_SECTION_POS_LAND1, SectionList);
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, TURNIERGRP_SECTION_POS_LAND2_EXPANDED, TURNIERGRP_SECTION_POS_LAND2, SectionList);
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, TURNIERGRP_SECTION_POS_LAND3_EXPANDED, TURNIERGRP_SECTION_POS_LAND3, SectionList);
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, TURNIERGRP_SECTION_POS_LAND4_EXPANDED, TURNIERGRP_SECTION_POS_LAND4, SectionList);
		break;

	case FIELD_REFERENCE_VEREIN:
		break;

	default:
		break;
	} // switch reference types
} // EncodeFieldsToA3Db 

static bool IncludeSectionPosIntoA3Db (TURNIERGRP_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case TURNIERGRP_SECTION_POS_UNKNOWN_01:
	case TURNIERGRP_SECTION_POS_ANZAHL_TEAMS:
	case TURNIERGRP_SECTION_POS_LAND1:
	case TURNIERGRP_SECTION_POS_UNKNOWN_04:
	case TURNIERGRP_SECTION_POS_LAND2:
	case TURNIERGRP_SECTION_POS_UNKNOWN_06:
	case TURNIERGRP_SECTION_POS_LAND3:
	case TURNIERGRP_SECTION_POS_UNKNOWN_08:
	case TURNIERGRP_SECTION_POS_LAND4:
	case TURNIERGRP_SECTION_POS_UNKNOWN_10:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case TURNIERGRP_SECTION_POS_PARENT_SECTION:
	case TURNIERGRP_SECTION_POS_LAND1_EXPANDED:
	case TURNIERGRP_SECTION_POS_LAND2_EXPANDED:
	case TURNIERGRP_SECTION_POS_LAND3_EXPANDED:
	case TURNIERGRP_SECTION_POS_LAND4_EXPANDED:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromTurnierGrpSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (TURNIERGRP_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case TURNIERGRP_SECTION_POS_UNKNOWN_01:
	case TURNIERGRP_SECTION_POS_ANZAHL_TEAMS:
	case TURNIERGRP_SECTION_POS_UNKNOWN_04:
	case TURNIERGRP_SECTION_POS_UNKNOWN_06:
	case TURNIERGRP_SECTION_POS_UNKNOWN_08:
	case TURNIERGRP_SECTION_POS_UNKNOWN_10:
	case TURNIERGRP_SECTION_POS_PARENT_SECTION:
	case TURNIERGRP_SECTION_POS_LAND1_EXPANDED:
	case TURNIERGRP_SECTION_POS_LAND2_EXPANDED:
	case TURNIERGRP_SECTION_POS_LAND3_EXPANDED:
	case TURNIERGRP_SECTION_POS_LAND4_EXPANDED:
		IncludeIntoXml = true;
		break;

	case TURNIERGRP_SECTION_POS_LAND1:
	case TURNIERGRP_SECTION_POS_LAND2:
	case TURNIERGRP_SECTION_POS_LAND3:
	case TURNIERGRP_SECTION_POS_LAND4:
		IncludeIntoXml = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromTurnierGrpSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static TURNIERGRP_SECTION_POS_TYPE GetTurnierGrpSectionPosTypeFromString (const std::string& TypeString)
{
	TURNIERGRP_SECTION_POS_TYPE FoundPos = TURNIERGRP_SECTION_POS_UNKNOWN;

	for (int TempPos = TURNIERGRP_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_TURNIERGRP_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromTurnierGrpSectionPosType ((TURNIERGRP_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (TURNIERGRP_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetTurnierGrpSectionPosTypeFromString

void AssignTurnierGrpField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<turniergrp>(SectionList, SectionLineCount, Line);
} // AssignTurnierGrpField

std::string GetTurnierGrpCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = TURNIERGRP_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_TURNIERGRP_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromTurnierGrpSectionPosType ((TURNIERGRP_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetTurnierGrpCsvHeader
