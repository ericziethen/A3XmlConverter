#include "amateurv.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

amateurv::amateurv(void)
{
}

amateurv::~amateurv(void)
{
}

std::string amateurv::GetUniqueId ()
{
	return(this->Vereinsnahme);
} // GetUniqueId

SECTION_TYPE amateurv::GetSectionType ()
{
	return(SECTION_TYPE_AMATEURV);
} // GetSectionType

std::string amateurv::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case AMATEURV_SECTION_POS_VEREINSNAHME:
		return (this->Vereinsnahme);

			// Parent Section
	case AMATEURV_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromAmateurvSectionPosType (const AMATEURV_SECTION_POS_TYPE AmateurvSectionPosType)
{
	switch (AmateurvSectionPosType)
	{
	case AMATEURV_SECTION_POS_VEREINSNAHME:
		return ("Vereinsnahme");

	case AMATEURV_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << AmateurvSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromAmateurvSectionPosType

void amateurv::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case AMATEURV_SECTION_POS_VEREINSNAHME:
		this->Vereinsnahme = FieldValue;
		break;

			// Parent Section	
	case AMATEURV_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void amateurv::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int AmateurvPos = AMATEURV_SECTION_POS_UNKNOWN + 1; AmateurvPos < NO_OF_AMATEURV_SECTION_POS_TYPES; AmateurvPos++)
	{
		if (IncludeSectionPosIntoXml ((AMATEURV_SECTION_POS_TYPE) AmateurvPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromAmateurvSectionPosType ((AMATEURV_SECTION_POS_TYPE) AmateurvPos), 			
				this->GetValueAtSectionPos(AmateurvPos))));
		}
	}

} // PopulateValuePairVectorForExport

void amateurv::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& AmateurvValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = AmateurvValuePairs.begin(); 
		Iterator != AmateurvValuePairs.end(); ++Iterator)
	{
		AMATEURV_SECTION_POS_TYPE FieldPos = GetAmateurvSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != AMATEURV_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void amateurv::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = AMATEURV_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_AMATEURV_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((AMATEURV_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

static bool IncludeSectionPosIntoA3Db (AMATEURV_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case AMATEURV_SECTION_POS_VEREINSNAHME:
		IncludeIntoA3Db = true;
		break;

// Parent Section
	case AMATEURV_SECTION_POS_PARENT_SECTION:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromAmateurvSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (AMATEURV_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case AMATEURV_SECTION_POS_VEREINSNAHME:
	case AMATEURV_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromAmateurvSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static AMATEURV_SECTION_POS_TYPE GetAmateurvSectionPosTypeFromString (const std::string& TypeString)
{
	AMATEURV_SECTION_POS_TYPE FoundPos = AMATEURV_SECTION_POS_UNKNOWN;

	for (int TempPos = AMATEURV_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_AMATEURV_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromAmateurvSectionPosType ((AMATEURV_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (AMATEURV_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetAmateurvSectionPosTypeFromString

void AssignAmateurvField (std::vector<std::shared_ptr<section>>& AmateurvList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<amateurv>(AmateurvList, SectionLineCount, Line);
} // AssignAmateurvField

std::string GetAmateurvCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = AMATEURV_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_AMATEURV_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromAmateurvSectionPosType ((AMATEURV_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetAmateurvCsvHeader