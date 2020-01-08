#include "sponsor.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

sponsor::sponsor(void)
{
}

sponsor::~sponsor(void)
{
}

std::string sponsor::GetUniqueId ()
{
	return(this->Sponsorennahme);
} // GetUniqueId

SECTION_TYPE sponsor::GetSectionType ()
{
	return(SECTION_TYPE_SPONSOR);
} // GetSectionType

std::string sponsor::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case SPONSOR_SECTION_POS_SPONSORENNAHME:
		return (this->Sponsorennahme);
	case SPONSOR_SECTION_POS_UNKNOWN_02:
		return (this->SPONSOR_FIELD_UNKNOWN_02);
	case SPONSOR_SECTION_POS_UNKNOWN_03:
		return (this->SPONSOR_FIELD_UNKNOWN_03);
	case SPONSOR_SECTION_POS_UNKNOWN_04:
		return (this->SPONSOR_FIELD_UNKNOWN_04);
	case SPONSOR_SECTION_POS_UNKNOWN_05:
		return (this->SPONSOR_FIELD_UNKNOWN_05);
	case SPONSOR_SECTION_POS_UNKNOWN_06:
		return (this->SPONSOR_FIELD_UNKNOWN_06);
	case SPONSOR_SECTION_POS_UNKNOWN_07:
		return (this->SPONSOR_FIELD_UNKNOWN_07);
	case SPONSOR_SECTION_POS_UNKNOWN_08:
		return (this->SPONSOR_FIELD_UNKNOWN_08);
	case SPONSOR_SECTION_POS_UNKNOWN_09:
		return (this->SPONSOR_FIELD_UNKNOWN_09);
	case SPONSOR_SECTION_POS_UNKNOWN_10:
		return (this->SPONSOR_FIELD_UNKNOWN_10);
	case SPONSOR_SECTION_POS_UNKNOWN_11:
		return (this->SPONSOR_FIELD_UNKNOWN_11);
	case SPONSOR_SECTION_POS_UNKNOWN_12:
		return (this->SPONSOR_FIELD_UNKNOWN_12);
	case SPONSOR_SECTION_POS_UNKNOWN_13:
		return (this->SPONSOR_FIELD_UNKNOWN_13);
	case SPONSOR_SECTION_POS_UNKNOWN_14:
		return (this->SPONSOR_FIELD_UNKNOWN_14);
	case SPONSOR_SECTION_POS_UNKNOWN_15:
		return (this->SPONSOR_FIELD_UNKNOWN_15);
	case SPONSOR_SECTION_POS_UNKNOWN_16:
		return (this->SPONSOR_FIELD_UNKNOWN_16);
	case SPONSOR_SECTION_POS_SCHRIFTART:
		return (this->Schriftart);
	case SPONSOR_SECTION_POS_UNKNOWN_18:
		return (this->SPONSOR_FIELD_UNKNOWN_18);
	case SPONSOR_SECTION_POS_UNKNOWN_19:
		return (this->SPONSOR_FIELD_UNKNOWN_19);

			// Parent Section
	case SPONSOR_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromSponsorSectionPosType (const SPONSOR_SECTION_POS_TYPE SponsorSectionPosType)
{
	switch (SponsorSectionPosType)
	{
	case SPONSOR_SECTION_POS_SPONSORENNAHME:
		return ("Sponsorennahme");
	case SPONSOR_SECTION_POS_UNKNOWN_02:
		return ("SPONSOR_FIELD_UNKNOWN_02");
	case SPONSOR_SECTION_POS_UNKNOWN_03:
		return ("SPONSOR_FIELD_UNKNOWN_03");
	case SPONSOR_SECTION_POS_UNKNOWN_04:
		return ("SPONSOR_FIELD_UNKNOWN_04");
	case SPONSOR_SECTION_POS_UNKNOWN_05:
		return ("SPONSOR_FIELD_UNKNOWN_05");
	case SPONSOR_SECTION_POS_UNKNOWN_06:
		return ("SPONSOR_FIELD_UNKNOWN_06");
	case SPONSOR_SECTION_POS_UNKNOWN_07:
		return ("SPONSOR_FIELD_UNKNOWN_07");
	case SPONSOR_SECTION_POS_UNKNOWN_08:
		return ("SPONSOR_FIELD_UNKNOWN_08");
	case SPONSOR_SECTION_POS_UNKNOWN_09:
		return ("SPONSOR_FIELD_UNKNOWN_09");
	case SPONSOR_SECTION_POS_UNKNOWN_10:
		return ("SPONSOR_FIELD_UNKNOWN_10");
	case SPONSOR_SECTION_POS_UNKNOWN_11:
		return ("SPONSOR_FIELD_UNKNOWN_11");
	case SPONSOR_SECTION_POS_UNKNOWN_12:
		return ("SPONSOR_FIELD_UNKNOWN_12");
	case SPONSOR_SECTION_POS_UNKNOWN_13:
		return ("SPONSOR_FIELD_UNKNOWN_13");
	case SPONSOR_SECTION_POS_UNKNOWN_14:
		return ("SPONSOR_FIELD_UNKNOWN_14");
	case SPONSOR_SECTION_POS_UNKNOWN_15:
		return ("SPONSOR_FIELD_UNKNOWN_15");
	case SPONSOR_SECTION_POS_UNKNOWN_16:
		return ("SPONSOR_FIELD_UNKNOWN_16");
	case SPONSOR_SECTION_POS_SCHRIFTART:
		return ("Schriftart");
	case SPONSOR_SECTION_POS_UNKNOWN_18:
		return ("SPONSOR_FIELD_UNKNOWN_18");
	case SPONSOR_SECTION_POS_UNKNOWN_19:
		return ("SPONSOR_FIELD_UNKNOWN_19");

	case SPONSOR_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << SponsorSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromSponsorSectionPosType

void sponsor::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case SPONSOR_SECTION_POS_SPONSORENNAHME:
		this->Sponsorennahme = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_02:
		this->SPONSOR_FIELD_UNKNOWN_02 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_03:
		this->SPONSOR_FIELD_UNKNOWN_03 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_04:
		this->SPONSOR_FIELD_UNKNOWN_04 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_05:
		this->SPONSOR_FIELD_UNKNOWN_05 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_06:
		this->SPONSOR_FIELD_UNKNOWN_06 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_07:
		this->SPONSOR_FIELD_UNKNOWN_07 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_08:
		this->SPONSOR_FIELD_UNKNOWN_08 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_09:
		this->SPONSOR_FIELD_UNKNOWN_09 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_10:
		this->SPONSOR_FIELD_UNKNOWN_10 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_11:
		this->SPONSOR_FIELD_UNKNOWN_11 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_12:
		this->SPONSOR_FIELD_UNKNOWN_12 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_13:
		this->SPONSOR_FIELD_UNKNOWN_13 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_14:
		this->SPONSOR_FIELD_UNKNOWN_14 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_15:
		this->SPONSOR_FIELD_UNKNOWN_15 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_16:
		this->SPONSOR_FIELD_UNKNOWN_16 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_SCHRIFTART:
		this->Schriftart = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_18:
		this->SPONSOR_FIELD_UNKNOWN_18 = FieldValue;
		break;
	case SPONSOR_SECTION_POS_UNKNOWN_19:
		this->SPONSOR_FIELD_UNKNOWN_19 = FieldValue;
		break;

			// Parent Section	
	case SPONSOR_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void sponsor::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int SponsorPos = SPONSOR_SECTION_POS_UNKNOWN + 1; SponsorPos < NO_OF_SPONSOR_SECTION_POS_TYPES; SponsorPos++)
	{
		if (IncludeSectionPosIntoXml ((SPONSOR_SECTION_POS_TYPE) SponsorPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromSponsorSectionPosType ((SPONSOR_SECTION_POS_TYPE) SponsorPos), 			
				this->GetValueAtSectionPos(SponsorPos))));
		}
	}

} // PopulateValuePairVectorForExport

void sponsor::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& SponsorValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = SponsorValuePairs.begin(); 
		Iterator != SponsorValuePairs.end(); ++Iterator)
	{
		SPONSOR_SECTION_POS_TYPE FieldPos = GetSponsorSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != SPONSOR_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void sponsor::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = SPONSOR_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_SPONSOR_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((SPONSOR_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

static bool IncludeSectionPosIntoA3Db (SPONSOR_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case SPONSOR_SECTION_POS_SPONSORENNAHME:
	case SPONSOR_SECTION_POS_UNKNOWN_02:
	case SPONSOR_SECTION_POS_UNKNOWN_03:
	case SPONSOR_SECTION_POS_UNKNOWN_04:
	case SPONSOR_SECTION_POS_UNKNOWN_05:
	case SPONSOR_SECTION_POS_UNKNOWN_06:
	case SPONSOR_SECTION_POS_UNKNOWN_07:
	case SPONSOR_SECTION_POS_UNKNOWN_08:
	case SPONSOR_SECTION_POS_UNKNOWN_09:
	case SPONSOR_SECTION_POS_UNKNOWN_10:
	case SPONSOR_SECTION_POS_UNKNOWN_11:
	case SPONSOR_SECTION_POS_UNKNOWN_12:
	case SPONSOR_SECTION_POS_UNKNOWN_13:
	case SPONSOR_SECTION_POS_UNKNOWN_14:
	case SPONSOR_SECTION_POS_UNKNOWN_15:
	case SPONSOR_SECTION_POS_UNKNOWN_16:
	case SPONSOR_SECTION_POS_SCHRIFTART:
	case SPONSOR_SECTION_POS_UNKNOWN_18:
	case SPONSOR_SECTION_POS_UNKNOWN_19:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case SPONSOR_SECTION_POS_PARENT_SECTION:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromSponsorSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (SPONSOR_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case SPONSOR_SECTION_POS_SPONSORENNAHME:
	case SPONSOR_SECTION_POS_UNKNOWN_02:
	case SPONSOR_SECTION_POS_UNKNOWN_03:
	case SPONSOR_SECTION_POS_UNKNOWN_04:
	case SPONSOR_SECTION_POS_UNKNOWN_05:
	case SPONSOR_SECTION_POS_UNKNOWN_06:
	case SPONSOR_SECTION_POS_UNKNOWN_07:
	case SPONSOR_SECTION_POS_UNKNOWN_08:
	case SPONSOR_SECTION_POS_UNKNOWN_09:
	case SPONSOR_SECTION_POS_UNKNOWN_10:
	case SPONSOR_SECTION_POS_UNKNOWN_11:
	case SPONSOR_SECTION_POS_UNKNOWN_12:
	case SPONSOR_SECTION_POS_UNKNOWN_13:
	case SPONSOR_SECTION_POS_UNKNOWN_14:
	case SPONSOR_SECTION_POS_UNKNOWN_15:
	case SPONSOR_SECTION_POS_UNKNOWN_16:
	case SPONSOR_SECTION_POS_SCHRIFTART:
	case SPONSOR_SECTION_POS_UNKNOWN_18:
	case SPONSOR_SECTION_POS_UNKNOWN_19:
	case SPONSOR_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromSponsorSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static SPONSOR_SECTION_POS_TYPE GetSponsorSectionPosTypeFromString (const std::string& TypeString)
{
	SPONSOR_SECTION_POS_TYPE FoundPos = SPONSOR_SECTION_POS_UNKNOWN;

	for (int TempPos = SPONSOR_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_SPONSOR_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromSponsorSectionPosType ((SPONSOR_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (SPONSOR_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetSponsorSectionPosTypeFromString

void AssignSponsorField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<sponsor>(SectionList, SectionLineCount, Line);
} // AssignSponsorField

std::string GetSponsorCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = SPONSOR_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_SPONSOR_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromSponsorSectionPosType ((SPONSOR_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetSponsorCsvHeader