#include "cleaguegrp.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

cleaguegrp::cleaguegrp(void)
{
}

cleaguegrp::~cleaguegrp(void)
{
}

std::string cleaguegrp::GetUniqueId ()
{
	return(this->GruppenNummer);
} // GetUniqueId

SECTION_TYPE cleaguegrp::GetSectionType ()
{
	return(SECTION_TYPE_CLEAGUEGRP);
} // GetSectionType

std::string cleaguegrp::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case CLEAGUEGRP_SECTION_POS_GRUPPEN_NUMMER:
		return (this->GruppenNummer);
	case CLEAGUEGRP_SECTION_POS_ANZAHL_TEAMS:
		return (this->AnzahlTeams);
	case CLEAGUEGRP_SECTION_POS_LAND1:
		return (this->Land1);
	case CLEAGUEGRP_SECTION_POS_VEREIN1:
		return (this->Verein1);
	case CLEAGUEGRP_SECTION_POS_LAND2:
		return (this->Land2);
	case CLEAGUEGRP_SECTION_POS_VEREIN2:
		return (this->Verein2);
	case CLEAGUEGRP_SECTION_POS_LAND3:
		return (this->Land3);
	case CLEAGUEGRP_SECTION_POS_VEREIN3:
		return (this->Verein3);
	case CLEAGUEGRP_SECTION_POS_LAND4:
		return (this->Land4);
	case CLEAGUEGRP_SECTION_POS_VEREIN4:
		return (this->Verein4);

	case CLEAGUEGRP_SECTION_POS_LAND1_EXPANDED:
		return (this->Land1_Expanded);
	case CLEAGUEGRP_SECTION_POS_VEREIN1_EXPANDED:
		return (this->Verein1_Expanded);
	case CLEAGUEGRP_SECTION_POS_LAND2_EXPANDED:
		return (this->Land2_Expanded);
	case CLEAGUEGRP_SECTION_POS_VEREIN2_EXPANDED:
		return (this->Verein2_Expanded);
	case CLEAGUEGRP_SECTION_POS_LAND3_EXPANDED:
		return (this->Land3_Expanded);
	case CLEAGUEGRP_SECTION_POS_VEREIN3_EXPANDED:
		return (this->Verein3_Expanded);
	case CLEAGUEGRP_SECTION_POS_LAND4_EXPANDED:
		return (this->Land4_Expanded);
	case CLEAGUEGRP_SECTION_POS_VEREIN4_EXPANDED:
		return (this->Verein4_Expanded);

			// Parent Section
	case CLEAGUEGRP_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromCleagueGrpSectionPosType (const CLEAGUEGRP_SECTION_POS_TYPE CleagueGrpSectionPosType)
{
	switch (CleagueGrpSectionPosType)
	{
	case CLEAGUEGRP_SECTION_POS_GRUPPEN_NUMMER:
		return ("GruppenNummer");
	case CLEAGUEGRP_SECTION_POS_ANZAHL_TEAMS:
		return ("AnzahlTeams");
	case CLEAGUEGRP_SECTION_POS_LAND1:
		return ("Land1_UNEXPANDED");
	case CLEAGUEGRP_SECTION_POS_VEREIN1:
		return ("Verein1_UNEXPANDED");
	case CLEAGUEGRP_SECTION_POS_LAND2:
		return ("Land2_UNEXPANDED");
	case CLEAGUEGRP_SECTION_POS_VEREIN2:
		return ("Verein2_UNEXPANDED");
	case CLEAGUEGRP_SECTION_POS_LAND3:
		return ("Land3_UNEXPANDED");
	case CLEAGUEGRP_SECTION_POS_VEREIN3:
		return ("Verein3_UNEXPANDED");
	case CLEAGUEGRP_SECTION_POS_LAND4:
		return ("Land4_UNEXPANDED");
	case CLEAGUEGRP_SECTION_POS_VEREIN4:
		return ("Verein4_UNEXPANDED");

	case CLEAGUEGRP_SECTION_POS_LAND1_EXPANDED:
		return ("Land1");
	case CLEAGUEGRP_SECTION_POS_VEREIN1_EXPANDED:
		return ("Verein1");
	case CLEAGUEGRP_SECTION_POS_LAND2_EXPANDED:
		return ("Land2");
	case CLEAGUEGRP_SECTION_POS_VEREIN2_EXPANDED:
		return ("Verein2");
	case CLEAGUEGRP_SECTION_POS_LAND3_EXPANDED:
		return ("Land3");
	case CLEAGUEGRP_SECTION_POS_VEREIN3_EXPANDED:
		return ("Verein3");
	case CLEAGUEGRP_SECTION_POS_LAND4_EXPANDED:
		return ("Land4");
	case CLEAGUEGRP_SECTION_POS_VEREIN4_EXPANDED:
		return ("Verein4");

	case CLEAGUEGRP_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << CleagueGrpSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromCleagueGrpSectionPosType

void cleaguegrp::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case CLEAGUEGRP_SECTION_POS_GRUPPEN_NUMMER:
		this->GruppenNummer = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_ANZAHL_TEAMS:
		this->AnzahlTeams = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_LAND1:
		this->Land1 = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_VEREIN1:
		this->Verein1 = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_LAND2:
		this->Land2 = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_VEREIN2:
		this->Verein2 = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_LAND3:
		this->Land3 = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_VEREIN3:
		this->Verein3 = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_LAND4:
		this->Land4 = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_VEREIN4:
		this->Verein4 = FieldValue;
		break;

	case CLEAGUEGRP_SECTION_POS_LAND1_EXPANDED:
		this->Land1_Expanded = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_VEREIN1_EXPANDED:
		this->Verein1_Expanded = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_LAND2_EXPANDED:
		this->Land2_Expanded = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_VEREIN2_EXPANDED:
		this->Verein2_Expanded = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_LAND3_EXPANDED:
		this->Land3_Expanded = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_VEREIN3_EXPANDED:
		this->Verein3_Expanded = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_LAND4_EXPANDED:
		this->Land4_Expanded = FieldValue;
		break;
	case CLEAGUEGRP_SECTION_POS_VEREIN4_EXPANDED:
		this->Verein4_Expanded = FieldValue;
		break;

			// Parent Section	
	case CLEAGUEGRP_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void cleaguegrp::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int CleagueGrpPos = CLEAGUEGRP_SECTION_POS_UNKNOWN + 1; CleagueGrpPos < NO_OF_CLEAGUEGRP_SECTION_POS_TYPES; CleagueGrpPos++)
	{
		if (IncludeSectionPosIntoXml ((CLEAGUEGRP_SECTION_POS_TYPE) CleagueGrpPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromCleagueGrpSectionPosType ((CLEAGUEGRP_SECTION_POS_TYPE) CleagueGrpPos), 			
				this->GetValueAtSectionPos(CleagueGrpPos))));
		}
	}

} // PopulateValuePairVectorForExport

void cleaguegrp::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& CleagueGrpValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = CleagueGrpValuePairs.begin(); 
		Iterator != CleagueGrpValuePairs.end(); ++Iterator)
	{
		CLEAGUEGRP_SECTION_POS_TYPE FieldPos = GetCleagueGrpSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != CLEAGUEGRP_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void cleaguegrp::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = CLEAGUEGRP_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_CLEAGUEGRP_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((CLEAGUEGRP_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void cleaguegrp::DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Land Field
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, CLEAGUEGRP_SECTION_POS_LAND1, CLEAGUEGRP_SECTION_POS_LAND1_EXPANDED, SectionList);
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, CLEAGUEGRP_SECTION_POS_LAND2, CLEAGUEGRP_SECTION_POS_LAND2_EXPANDED, SectionList);
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, CLEAGUEGRP_SECTION_POS_LAND3, CLEAGUEGRP_SECTION_POS_LAND3_EXPANDED, SectionList);
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, CLEAGUEGRP_SECTION_POS_LAND4, CLEAGUEGRP_SECTION_POS_LAND4_EXPANDED, SectionList);

	// Decode Verein Field
	this->ConvertVereinField(SECTION_EXPANSION_FROM_A3DB_VEREIN, CLEAGUEGRP_SECTION_POS_VEREIN1, CLEAGUEGRP_SECTION_POS_VEREIN1_EXPANDED, 
		this->GetValueAtSectionPos(CLEAGUEGRP_SECTION_POS_LAND1), SectionList);
	this->ConvertVereinField(SECTION_EXPANSION_FROM_A3DB_VEREIN, CLEAGUEGRP_SECTION_POS_VEREIN2, CLEAGUEGRP_SECTION_POS_VEREIN2_EXPANDED, 
		this->GetValueAtSectionPos(CLEAGUEGRP_SECTION_POS_LAND2), SectionList);
	this->ConvertVereinField(SECTION_EXPANSION_FROM_A3DB_VEREIN, CLEAGUEGRP_SECTION_POS_VEREIN3, CLEAGUEGRP_SECTION_POS_VEREIN3_EXPANDED, 
		this->GetValueAtSectionPos(CLEAGUEGRP_SECTION_POS_LAND3), SectionList);
	this->ConvertVereinField(SECTION_EXPANSION_FROM_A3DB_VEREIN, CLEAGUEGRP_SECTION_POS_VEREIN4, CLEAGUEGRP_SECTION_POS_VEREIN4_EXPANDED, 
		this->GetValueAtSectionPos(CLEAGUEGRP_SECTION_POS_LAND4), SectionList);
} // DecodeFieldsFromA3Db

void cleaguegrp::EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE ReferenceType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	switch (ReferenceType)
	{
	case FIELD_REFERENCE_LAND:
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, CLEAGUEGRP_SECTION_POS_LAND1_EXPANDED, CLEAGUEGRP_SECTION_POS_LAND1, SectionList);
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, CLEAGUEGRP_SECTION_POS_LAND2_EXPANDED, CLEAGUEGRP_SECTION_POS_LAND2, SectionList);
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, CLEAGUEGRP_SECTION_POS_LAND3_EXPANDED, CLEAGUEGRP_SECTION_POS_LAND3, SectionList);
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, CLEAGUEGRP_SECTION_POS_LAND4_EXPANDED, CLEAGUEGRP_SECTION_POS_LAND4, SectionList);
		break;

	case FIELD_REFERENCE_VEREIN:
		this->ConvertVereinField(SECTION_EXPANSION_TO_A3DB_VEREIN, CLEAGUEGRP_SECTION_POS_VEREIN1_EXPANDED, CLEAGUEGRP_SECTION_POS_VEREIN1,
			this->GetValueAtSectionPos(CLEAGUEGRP_SECTION_POS_LAND1), SectionList);
		this->ConvertVereinField(SECTION_EXPANSION_TO_A3DB_VEREIN, CLEAGUEGRP_SECTION_POS_VEREIN2_EXPANDED, CLEAGUEGRP_SECTION_POS_VEREIN2,
			this->GetValueAtSectionPos(CLEAGUEGRP_SECTION_POS_LAND2), SectionList);
		this->ConvertVereinField(SECTION_EXPANSION_TO_A3DB_VEREIN, CLEAGUEGRP_SECTION_POS_VEREIN3_EXPANDED, CLEAGUEGRP_SECTION_POS_VEREIN3,
			this->GetValueAtSectionPos(CLEAGUEGRP_SECTION_POS_LAND3), SectionList);
		this->ConvertVereinField(SECTION_EXPANSION_TO_A3DB_VEREIN, CLEAGUEGRP_SECTION_POS_VEREIN4_EXPANDED, CLEAGUEGRP_SECTION_POS_VEREIN4,
			this->GetValueAtSectionPos(CLEAGUEGRP_SECTION_POS_LAND4), SectionList);
		break;

	default:
		break;
	} // switch reference types
} // EncodeFieldsToA3Db 

static bool IncludeSectionPosIntoA3Db (CLEAGUEGRP_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case CLEAGUEGRP_SECTION_POS_GRUPPEN_NUMMER:
	case CLEAGUEGRP_SECTION_POS_ANZAHL_TEAMS:
	case CLEAGUEGRP_SECTION_POS_LAND1:
	case CLEAGUEGRP_SECTION_POS_VEREIN1:
	case CLEAGUEGRP_SECTION_POS_LAND2:
	case CLEAGUEGRP_SECTION_POS_VEREIN2:
	case CLEAGUEGRP_SECTION_POS_LAND3:
	case CLEAGUEGRP_SECTION_POS_VEREIN3:
	case CLEAGUEGRP_SECTION_POS_LAND4:
	case CLEAGUEGRP_SECTION_POS_VEREIN4:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case CLEAGUEGRP_SECTION_POS_PARENT_SECTION:
	case CLEAGUEGRP_SECTION_POS_LAND1_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_VEREIN1_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_LAND2_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_VEREIN2_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_LAND3_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_VEREIN3_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_LAND4_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_VEREIN4_EXPANDED:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromCleagueGrpSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (CLEAGUEGRP_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case CLEAGUEGRP_SECTION_POS_GRUPPEN_NUMMER:
	case CLEAGUEGRP_SECTION_POS_ANZAHL_TEAMS:
	case CLEAGUEGRP_SECTION_POS_PARENT_SECTION:
	case CLEAGUEGRP_SECTION_POS_LAND1_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_VEREIN1_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_LAND2_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_VEREIN2_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_LAND3_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_VEREIN3_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_LAND4_EXPANDED:
	case CLEAGUEGRP_SECTION_POS_VEREIN4_EXPANDED:
		IncludeIntoXml = true;
		break;

	case CLEAGUEGRP_SECTION_POS_LAND1:
	case CLEAGUEGRP_SECTION_POS_VEREIN1:
	case CLEAGUEGRP_SECTION_POS_LAND2:
	case CLEAGUEGRP_SECTION_POS_VEREIN2:
	case CLEAGUEGRP_SECTION_POS_LAND3:
	case CLEAGUEGRP_SECTION_POS_VEREIN3:
	case CLEAGUEGRP_SECTION_POS_LAND4:
	case CLEAGUEGRP_SECTION_POS_VEREIN4:
		IncludeIntoXml = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromCleagueGrpSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static CLEAGUEGRP_SECTION_POS_TYPE GetCleagueGrpSectionPosTypeFromString (const std::string& TypeString)
{
	CLEAGUEGRP_SECTION_POS_TYPE FoundPos = CLEAGUEGRP_SECTION_POS_UNKNOWN;

	for (int TempPos = CLEAGUEGRP_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_CLEAGUEGRP_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromCleagueGrpSectionPosType ((CLEAGUEGRP_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (CLEAGUEGRP_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetCleagueGrpSectionPosTypeFromString

void AssignCleagueGrpField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<cleaguegrp>(SectionList, SectionLineCount, Line);
} // AssignCleagueGrpField

std::string GetCleagueGrpCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = CLEAGUEGRP_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_CLEAGUEGRP_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromCleagueGrpSectionPosType ((CLEAGUEGRP_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetCleagueGrpCsvHeader
