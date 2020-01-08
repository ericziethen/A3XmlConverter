#include "promi.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

promi::promi(void)
{
}

promi::~promi(void)
{
}

std::string promi::GetUniqueId ()
{
	return(this->Nachnahme + this->Vornahme);
} // GetUniqueId

SECTION_TYPE promi::GetSectionType ()
{
	return(SECTION_TYPE_PROMI);
} // GetSectionType

std::string promi::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case PROMI_SECTION_POS_NACHNAHME:
		return (this->Nachnahme);
	case PROMI_SECTION_POS_VORNAHME:
		return (this->Vornahme);
	case PROMI_SECTION_POS_LIEBLINGSVEREIN:
		return (this->Lieblingsverein);
	case PROMI_SECTION_POS_LIEBLINGSVEREIN_EXPANDED:
		return (this->Lieblingsverein_Expanded);

			// Parent Section
	case PROMI_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromPromiSectionPosType (const PROMI_SECTION_POS_TYPE PromiSectionPosType)
{
	switch (PromiSectionPosType)
	{
	case PROMI_SECTION_POS_NACHNAHME:
		return ("Nachnahme");
	case PROMI_SECTION_POS_VORNAHME:
		return ("Vornahme");
	case PROMI_SECTION_POS_LIEBLINGSVEREIN:
		return ("Lieblingsverein_UNEXPANDED");
	case PROMI_SECTION_POS_LIEBLINGSVEREIN_EXPANDED:
		return ("Lieblingsverein");

	case PROMI_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << PromiSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromPromiSectionPosType

void promi::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case PROMI_SECTION_POS_NACHNAHME:
		this->Nachnahme = FieldValue;
		break;
	case PROMI_SECTION_POS_VORNAHME:
		this->Vornahme = FieldValue;
		break;
	case PROMI_SECTION_POS_LIEBLINGSVEREIN:
		this->Lieblingsverein = FieldValue;
		break;
	case PROMI_SECTION_POS_LIEBLINGSVEREIN_EXPANDED:
		this->Lieblingsverein_Expanded = FieldValue;
		break;

			// Parent Section	
	case PROMI_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void promi::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int PromiPos = PROMI_SECTION_POS_UNKNOWN + 1; PromiPos < NO_OF_PROMI_SECTION_POS_TYPES; PromiPos++)
	{
		if (IncludeSectionPosIntoXml ((PROMI_SECTION_POS_TYPE) PromiPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromPromiSectionPosType ((PROMI_SECTION_POS_TYPE) PromiPos), 			
				this->GetValueAtSectionPos(PromiPos))));
		}
	}

} // PopulateValuePairVectorForExport

void promi::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& PromiValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = PromiValuePairs.begin(); 
		Iterator != PromiValuePairs.end(); ++Iterator)
	{
		PROMI_SECTION_POS_TYPE FieldPos = GetPromiSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != PROMI_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void promi::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = PROMI_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_PROMI_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((PROMI_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void promi::DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Verein Field
	this->ConvertVereinField(SECTION_EXPANSION_FROM_A3DB_VEREIN, PROMI_SECTION_POS_LIEBLINGSVEREIN, PROMI_SECTION_POS_LIEBLINGSVEREIN_EXPANDED, 
								this->GetA3FileLandId(), SectionList);
} // DecodeFieldsFromA3Db

void promi::EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE ReferenceType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	switch (ReferenceType)
	{
	case FIELD_REFERENCE_LAND:
		break;

	case FIELD_REFERENCE_VEREIN:
		this->ConvertVereinField(SECTION_EXPANSION_TO_A3DB_VEREIN, PROMI_SECTION_POS_LIEBLINGSVEREIN_EXPANDED, PROMI_SECTION_POS_LIEBLINGSVEREIN, 
			this->GetA3FileLandId(), SectionList);
		break;

	default:
		break;
	} // switch reference types
} // EncodeFieldsToA3Db 

static bool IncludeSectionPosIntoA3Db (PROMI_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case PROMI_SECTION_POS_NACHNAHME:
	case PROMI_SECTION_POS_VORNAHME:
	case PROMI_SECTION_POS_LIEBLINGSVEREIN:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case PROMI_SECTION_POS_PARENT_SECTION:
	case PROMI_SECTION_POS_LIEBLINGSVEREIN_EXPANDED:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromPromiSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (PROMI_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case PROMI_SECTION_POS_NACHNAHME:
	case PROMI_SECTION_POS_VORNAHME:
	case PROMI_SECTION_POS_LIEBLINGSVEREIN_EXPANDED:
	case PROMI_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;

	case PROMI_SECTION_POS_LIEBLINGSVEREIN:
		IncludeIntoXml = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromPromiSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static PROMI_SECTION_POS_TYPE GetPromiSectionPosTypeFromString (const std::string& TypeString)
{
	PROMI_SECTION_POS_TYPE FoundPos = PROMI_SECTION_POS_UNKNOWN;

	for (int TempPos = PROMI_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_PROMI_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromPromiSectionPosType ((PROMI_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (PROMI_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetPromiSectionPosTypeFromString

void AssignPromiField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<promi>(SectionList, SectionLineCount, Line);
} // AssignPromiField

std::string GetPromiCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = PROMI_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_PROMI_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromPromiSectionPosType ((PROMI_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetPromiCsvHeader
