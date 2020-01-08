#include "eurosieger.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

eurosieger::eurosieger(void)
{
}

eurosieger::~eurosieger(void)
{
}

std::string eurosieger::GetUniqueId ()
{
	return(this->EUROSIEGER_FIELD_UNKNOWN_01);
} // GetUniqueId

SECTION_TYPE eurosieger::GetSectionType ()
{
	return(SECTION_TYPE_EUROSIEGER);
} // GetSectionType

std::string eurosieger::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case EUROSIEGER_SECTION_POS_UNKNOWN_01:
		return (this->EUROSIEGER_FIELD_UNKNOWN_01);
	case EUROSIEGER_SECTION_POS_UNKNOWN_02:
		return (this->EUROSIEGER_FIELD_UNKNOWN_02);
	case EUROSIEGER_SECTION_POS_UNKNOWN_03:
		return (this->EUROSIEGER_FIELD_UNKNOWN_03);

			// Parent Section
	case EUROSIEGER_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromEurosiegerSectionPosType (const EUROSIEGER_SECTION_POS_TYPE EurosiegerSectionPosType)
{
	switch (EurosiegerSectionPosType)
	{
	case EUROSIEGER_SECTION_POS_UNKNOWN_01:
		return ("EUROSIEGER_FIELD_UNKNOWN_01");
	case EUROSIEGER_SECTION_POS_UNKNOWN_02:
		return ("EUROSIEGER_FIELD_UNKNOWN_02");
	case EUROSIEGER_SECTION_POS_UNKNOWN_03:
		return ("EUROSIEGER_FIELD_UNKNOWN_03");

	case EUROSIEGER_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << EurosiegerSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromEurosiegerSectionPosType

void eurosieger::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case EUROSIEGER_SECTION_POS_UNKNOWN_01:
		this->EUROSIEGER_FIELD_UNKNOWN_01 = FieldValue;
		break;
	case EUROSIEGER_SECTION_POS_UNKNOWN_02:
		this->EUROSIEGER_FIELD_UNKNOWN_02 = FieldValue;
		break;
	case EUROSIEGER_SECTION_POS_UNKNOWN_03:
		this->EUROSIEGER_FIELD_UNKNOWN_03 = FieldValue;
		break;

			// Parent Section	
	case EUROSIEGER_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void eurosieger::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int EurosiegerPos = EUROSIEGER_SECTION_POS_UNKNOWN + 1; EurosiegerPos < NO_OF_EUROSIEGER_SECTION_POS_TYPES; EurosiegerPos++)
	{
		if (IncludeSectionPosIntoXml ((EUROSIEGER_SECTION_POS_TYPE) EurosiegerPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromEurosiegerSectionPosType ((EUROSIEGER_SECTION_POS_TYPE) EurosiegerPos), 			
				this->GetValueAtSectionPos(EurosiegerPos))));
		}
	}

} // PopulateValuePairVectorForExport

void eurosieger::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& EurosiegerValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = EurosiegerValuePairs.begin(); 
		Iterator != EurosiegerValuePairs.end(); ++Iterator)
	{
		EUROSIEGER_SECTION_POS_TYPE FieldPos = GetEurosiegerSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != EUROSIEGER_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void eurosieger::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = EUROSIEGER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_EUROSIEGER_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((EUROSIEGER_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

static bool IncludeSectionPosIntoA3Db (EUROSIEGER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case EUROSIEGER_SECTION_POS_UNKNOWN_01:
	case EUROSIEGER_SECTION_POS_UNKNOWN_02:
	case EUROSIEGER_SECTION_POS_UNKNOWN_03:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case EUROSIEGER_SECTION_POS_PARENT_SECTION:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromEurosiegerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (EUROSIEGER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case EUROSIEGER_SECTION_POS_UNKNOWN_01:
	case EUROSIEGER_SECTION_POS_UNKNOWN_02:
	case EUROSIEGER_SECTION_POS_UNKNOWN_03:
	case EUROSIEGER_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromEurosiegerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static EUROSIEGER_SECTION_POS_TYPE GetEurosiegerSectionPosTypeFromString (const std::string& TypeString)
{
	EUROSIEGER_SECTION_POS_TYPE FoundPos = EUROSIEGER_SECTION_POS_UNKNOWN;

	for (int TempPos = EUROSIEGER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_EUROSIEGER_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromEurosiegerSectionPosType ((EUROSIEGER_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (EUROSIEGER_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetEurosiegerSectionPosTypeFromString

void AssignEurosiegerField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<eurosieger>(SectionList, SectionLineCount, Line);
} // AssignEurosiegerField

std::string GetEurosiegerCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = EUROSIEGER_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_EUROSIEGER_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromEurosiegerSectionPosType ((EUROSIEGER_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetEurosiegerCsvHeader
