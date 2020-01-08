#include "aspieler.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

aspieler::aspieler(void)
{
}

aspieler::~aspieler(void)
{
}

std::string aspieler::GetUniqueId ()
{
	return(this->Vornahme + this->Nachnahme);
} // GetUniqueId

SECTION_TYPE aspieler::GetSectionType ()
{
	return(SECTION_TYPE_ASPIELER);
} // GetSectionType

std::string aspieler::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case ASPIELER_SECTION_POS_VORNAHME:
		return (this->Vornahme);
	case ASPIELER_SECTION_POS_NACHNAHME:
		return (this->Nachnahme);

			// Parent Section
	case ASPIELER_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromASpielerSectionPosType (const ASPIELER_SECTION_POS_TYPE ASpielerSectionPosType)
{
	switch (ASpielerSectionPosType)
	{
	case ASPIELER_SECTION_POS_VORNAHME:
		return ("Vornahme");
	case ASPIELER_SECTION_POS_NACHNAHME:
		return ("Nachnahme");

	case ASPIELER_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << ASpielerSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromASpielerSectionPosType

void aspieler::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case ASPIELER_SECTION_POS_VORNAHME:
		this->Vornahme = FieldValue;
		break;
	case ASPIELER_SECTION_POS_NACHNAHME:
		this->Nachnahme = FieldValue;
		break;

			// Parent Section	
	case ASPIELER_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void aspieler::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int ASpielerPos = ASPIELER_SECTION_POS_UNKNOWN + 1; ASpielerPos < NO_OF_ASPIELER_SECTION_POS_TYPES; ASpielerPos++)
	{
		if (IncludeSectionPosIntoXml ((ASPIELER_SECTION_POS_TYPE) ASpielerPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromASpielerSectionPosType ((ASPIELER_SECTION_POS_TYPE) ASpielerPos), 			
				this->GetValueAtSectionPos(ASpielerPos))));
		}
	}

} // PopulateValuePairVectorForExport

void aspieler::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& ASpielerValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = ASpielerValuePairs.begin(); 
		Iterator != ASpielerValuePairs.end(); ++Iterator)
	{
		ASPIELER_SECTION_POS_TYPE FieldPos = GetASpielerSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != ASPIELER_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void aspieler::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = ASPIELER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_ASPIELER_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((ASPIELER_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

static bool IncludeSectionPosIntoA3Db (ASPIELER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case ASPIELER_SECTION_POS_VORNAHME:
	case ASPIELER_SECTION_POS_NACHNAHME:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case ASPIELER_SECTION_POS_PARENT_SECTION:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromASpielerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (ASPIELER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case ASPIELER_SECTION_POS_VORNAHME:
	case ASPIELER_SECTION_POS_NACHNAHME:
	case ASPIELER_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromASpielerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static ASPIELER_SECTION_POS_TYPE GetASpielerSectionPosTypeFromString (const std::string& TypeString)
{
	ASPIELER_SECTION_POS_TYPE FoundPos = ASPIELER_SECTION_POS_UNKNOWN;

	for (int TempPos = ASPIELER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_ASPIELER_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromASpielerSectionPosType ((ASPIELER_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (ASPIELER_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetASpielerSectionPosTypeFromString

void AssignASpielerField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<aspieler>(SectionList, SectionLineCount, Line);
} // AssignASpielerField

std::string GetASpielerCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = ASPIELER_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_ASPIELER_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromASpielerSectionPosType ((ASPIELER_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetASpielerCsvHeader
