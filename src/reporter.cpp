#include "reporter.h"

#include "error_handling.h"
#include "reporter_enum.h"
#include <sstream>
#include <iostream>

reporter::reporter(void)
{
}

reporter::~reporter(void)
{
}

std::string reporter::GetUniqueId ()
{
	return(this->Nachnahme + this->Vornahme);
} // GetUniqueId

SECTION_TYPE reporter::GetSectionType ()
{
	return(SECTION_TYPE_REPORTER);
} // GetSectionType

std::string reporter::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case REPORTER_SECTION_POS_SENDER:
		return (this->Sender);
	case REPORTER_SECTION_POS_NACHNAHME:
		return (this->Nachnahme);
	case REPORTER_SECTION_POS_VORNAHME:
		return (this->Vornahme);
	case REPORTER_SECTION_POS_BOESELIEB:
		return (this->BoeseLieb);

			// Parent Section
	case REPORTER_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromReporterSectionPosType (const REPORTER_SECTION_POS_TYPE ReporterSectionPosType)
{
	switch (ReporterSectionPosType)
	{
	case REPORTER_SECTION_POS_SENDER:
		return ("Sender");
	case REPORTER_SECTION_POS_NACHNAHME:
		return ("Nachnahme");
	case REPORTER_SECTION_POS_VORNAHME:
		return ("Vornahme");
	case REPORTER_SECTION_POS_BOESELIEB:
		return ("BoeseLieb");

	case REPORTER_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << ReporterSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromReporterSectionPosType

void reporter::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case REPORTER_SECTION_POS_SENDER:
		this->Sender = FieldValue;
		break;
	case REPORTER_SECTION_POS_NACHNAHME:
		this->Nachnahme = FieldValue;
		break;
	case REPORTER_SECTION_POS_VORNAHME:
		this->Vornahme = FieldValue;
		break;
	case REPORTER_SECTION_POS_BOESELIEB:
		this->BoeseLieb = FieldValue;
		break;

			// Parent Section	
	case REPORTER_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void reporter::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int ReporterPos = REPORTER_SECTION_POS_UNKNOWN + 1; ReporterPos < NO_OF_REPORTER_SECTION_POS_TYPES; ReporterPos++)
	{
		if (IncludeSectionPosIntoXml ((REPORTER_SECTION_POS_TYPE) ReporterPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromReporterSectionPosType ((REPORTER_SECTION_POS_TYPE) ReporterPos), 			
				this->GetValueAtSectionPos(ReporterPos))));
		}
	}

} // PopulateValuePairVectorForExport

void reporter::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& ReporterValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = ReporterValuePairs.begin(); 
		Iterator != ReporterValuePairs.end(); ++Iterator)
	{
		REPORTER_SECTION_POS_TYPE FieldPos = GetReporterSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != REPORTER_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void reporter::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = REPORTER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_REPORTER_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((REPORTER_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void reporter::DecodeEnumsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Enum BoeseLieb
	this->DecodeEnumFromA3Db(REPORTER_SECTION_POS_BOESELIEB, REPORTER_ENUM_BOESE_LIEB, GetReporterEnumValue, GetEnumDetails);

} // DecodeEnumsFromA3Db

void reporter::EncodeEnumsToA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Encode Enum BoeseLieb
	this->EncodeEnumToA3Db(REPORTER_SECTION_POS_BOESELIEB, REPORTER_ENUM_BOESE_LIEB, GetReporterEnumValue, GetEnumDetails);

} // EncodeEnumsToA3Db

void GetEnumDetails (int SectionPos, int EnumType, ENUM_FUNC& EnumFunc, int& EnumLow, int& EnumHigh)
{
	switch ((REPORTER_ENUM_TYPE) EnumType)
	{
	case REPORTER_ENUM_BOESE_LIEB:
		EnumFunc = GetNameFromReporterBoeseLiebType;
		EnumLow = REPORTER_BOESE_LIEB_UNKNOWN;
		EnumHigh = NO_OF_REPORTER_BOESE_LIEB_TYPES;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << EnumType << " (" << 
			GetNameFromReporterEnumType((REPORTER_ENUM_TYPE) EnumType) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	} // switch enum type
} // GetEnumDetails

static bool IncludeSectionPosIntoA3Db (REPORTER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case REPORTER_SECTION_POS_SENDER:
	case REPORTER_SECTION_POS_NACHNAHME:
	case REPORTER_SECTION_POS_VORNAHME:
	case REPORTER_SECTION_POS_BOESELIEB:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case REPORTER_SECTION_POS_PARENT_SECTION:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromReporterSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (REPORTER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case REPORTER_SECTION_POS_SENDER:
	case REPORTER_SECTION_POS_NACHNAHME:
	case REPORTER_SECTION_POS_VORNAHME:
	case REPORTER_SECTION_POS_BOESELIEB:
	case REPORTER_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromReporterSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static REPORTER_SECTION_POS_TYPE GetReporterSectionPosTypeFromString (const std::string& TypeString)
{
	REPORTER_SECTION_POS_TYPE FoundPos = REPORTER_SECTION_POS_UNKNOWN;

	for (int TempPos = REPORTER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_REPORTER_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromReporterSectionPosType ((REPORTER_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (REPORTER_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetReporterSectionPosTypeFromString

void AssignReporterField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<reporter>(SectionList, SectionLineCount, Line);
} // AssignReporterField

std::string GetReporterCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = REPORTER_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_REPORTER_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromReporterSectionPosType ((REPORTER_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetReporterCsvHeader

static REPORTER_ENUM_TYPE GetReporterEnumTypeFromPosition (REPORTER_SECTION_POS_TYPE SectionPos)
{
	REPORTER_ENUM_TYPE EnumType = REPORTER_ENUM_UNKNOWN;
	switch ((REPORTER_SECTION_POS_TYPE) SectionPos)
	{
	case REPORTER_SECTION_POS_BOESELIEB:
		EnumType = REPORTER_ENUM_BOESE_LIEB;
		break;

	default:
		//do nothing
		break;
	} // switch section pos

	return (EnumType);
} // GetReporterEnumTypeFromPosition

void GetReporterAllowedValues (std::vector<FIELD_VALUE_STRUCT>& AllowedValues)
{
	for (int SectionPos = REPORTER_SECTION_POS_UNKNOWN + 1; SectionPos < NO_OF_REPORTER_SECTION_POS_TYPES; SectionPos++)
	{
		ENUM_FUNC EnumFunc = nullptr;
		int EnumLow = 0;
		int EnumHigh = 0;
		REPORTER_ENUM_TYPE ReporterEnum = REPORTER_ENUM_UNKNOWN;
		bool DetailsFound = false;

		if ((ReporterEnum = GetReporterEnumTypeFromPosition ((REPORTER_SECTION_POS_TYPE) SectionPos)) != REPORTER_ENUM_UNKNOWN)
		{
			// Ignore this for special case handled below
			GetEnumDetails(SectionPos, ReporterEnum, EnumFunc, EnumLow, EnumHigh);
			DetailsFound = true;
		} // if enum field

		// Add Values
		if (DetailsFound)
		{
			// Add the Value Entry to the List
			AddFieldValueEntryToList (AllowedValues, GetNameFromReporterSectionPosType((REPORTER_SECTION_POS_TYPE) SectionPos));

			// Add allowed Values
			AddFieldValuesForLastEntry (AllowedValues, EnumLow, EnumHigh, EnumFunc);
		} // if got a function
	} // for each section pos
} // GetReporterAllowedValues
