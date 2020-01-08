#include "ajugend.h"

#include "error_handling.h"
#include "ajugend_enum.h"
#include <sstream>
#include <iostream>

ajugend::ajugend(void)
{
}

ajugend::~ajugend(void)
{
}

std::string ajugend::GetUniqueId ()
{
	return(this->Vornahme + this->Nachnahme);
} // GetUniqueId

SECTION_TYPE ajugend::GetSectionType ()
{
	return(SECTION_TYPE_AJUGEND);
} // GetSectionType

std::string ajugend::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case AJUGEND_SECTION_POS_VORNAHME:
		return (this->Vornahme);
	case AJUGEND_SECTION_POS_NACHNAHME:
		return (this->Nachnahme);
	case AJUGEND_SECTION_POS_VEREIN:
		return (this->Verein);
	case AJUGEND_SECTION_POS_VEREIN_EXPANDED:
		return (this->Verein_EXPANDED);
	case AJUGEND_SECTION_POS_POSITION:
		return (this->Position);

			// Parent Section
	case AJUGEND_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromAJugendSectionPosType (const AJUGEND_SECTION_POS_TYPE AJugendSectionPosType)
{
	switch (AJugendSectionPosType)
	{
	case AJUGEND_SECTION_POS_VORNAHME:
		return ("Vornahme");
	case AJUGEND_SECTION_POS_NACHNAHME:
		return ("Nachnahme");
	case AJUGEND_SECTION_POS_VEREIN:
		return ("Verein_UNEXPANDED");
	case AJUGEND_SECTION_POS_VEREIN_EXPANDED:
		return ("Verein");
	case AJUGEND_SECTION_POS_POSITION:
		return ("Position");

	case AJUGEND_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << AJugendSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromAJugendSectionPosType

void ajugend::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case AJUGEND_SECTION_POS_VORNAHME:
		this->Vornahme = FieldValue;
		break;
	case AJUGEND_SECTION_POS_NACHNAHME:
		this->Nachnahme = FieldValue;
		break;
	case AJUGEND_SECTION_POS_VEREIN:
		this->Verein = FieldValue;
		break;
	case AJUGEND_SECTION_POS_VEREIN_EXPANDED:
		this->Verein_EXPANDED = FieldValue;
		break;
	case AJUGEND_SECTION_POS_POSITION:
		this->Position = FieldValue;
		break;

			// Parent Section	
	case AJUGEND_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void ajugend::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int AJugendPos = AJUGEND_SECTION_POS_UNKNOWN + 1; AJugendPos < NO_OF_AJUGEND_SECTION_POS_TYPES; AJugendPos++)
	{
		if (IncludeSectionPosIntoXml ((AJUGEND_SECTION_POS_TYPE) AJugendPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromAJugendSectionPosType ((AJUGEND_SECTION_POS_TYPE) AJugendPos), 			
				this->GetValueAtSectionPos(AJugendPos))));
		}
	}

} // PopulateValuePairVectorForExport

void ajugend::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& AJugendValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = AJugendValuePairs.begin(); 
		Iterator != AJugendValuePairs.end(); ++Iterator)
	{
		AJUGEND_SECTION_POS_TYPE FieldPos = GetAJugendSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != AJUGEND_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void ajugend::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = AJUGEND_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_AJUGEND_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((AJUGEND_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void ajugend::DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Verein Field
	this->ConvertVereinField(SECTION_EXPANSION_FROM_A3DB_VEREIN, AJUGEND_SECTION_POS_VEREIN, AJUGEND_SECTION_POS_VEREIN_EXPANDED, 
								this->GetA3FileLandId(), SectionList);
} // DecodeFieldsFromA3Db

void ajugend::EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE ReferenceType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	switch (ReferenceType)
	{
	case FIELD_REFERENCE_LAND:
		break;

	case FIELD_REFERENCE_VEREIN:
		this->ConvertVereinField(SECTION_EXPANSION_TO_A3DB_VEREIN, AJUGEND_SECTION_POS_VEREIN_EXPANDED, AJUGEND_SECTION_POS_VEREIN, 
			this->GetA3FileLandId(), SectionList);
		break;

	default:
		break;
	} // switch reference types
} // EncodeFieldsToA3Db

void ajugend::DecodeEnumsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Enum Position
	this->DecodeEnumFromA3Db(AJUGEND_SECTION_POS_POSITION, AJUGEND_ENUM_POSITION, GetAjugendEnumValue, GetEnumDetails);

} // DecodeEnumsFromA3Db

void ajugend::EncodeEnumsToA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Encode Enum Position
	this->EncodeEnumToA3Db(AJUGEND_SECTION_POS_POSITION, AJUGEND_ENUM_POSITION, GetAjugendEnumValue, GetEnumDetails);

} // EncodeEnumsToA3Db

void GetEnumDetails (int SectionPos, int EnumType, ENUM_FUNC& EnumFunc, int& EnumLow, int& EnumHigh)
{
	switch ((AJUGEND_ENUM_TYPE) EnumType)
	{
	case AJUGEND_ENUM_POSITION:
		EnumFunc = GetNameFromAjugendPositionType;
		EnumLow = AJUGEND_POSITION_UNKNOWN;
		EnumHigh = NO_OF_AJUGEND_POSITION_TYPES;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << EnumType << " (" << 
			GetNameFromAjugendEnumType((AJUGEND_ENUM_TYPE) EnumType) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	} // switch enum type
} // GetEnumDetails

static bool IncludeSectionPosIntoA3Db (AJUGEND_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case AJUGEND_SECTION_POS_VORNAHME:
	case AJUGEND_SECTION_POS_NACHNAHME:
	case AJUGEND_SECTION_POS_VEREIN:
	case AJUGEND_SECTION_POS_POSITION:
		IncludeIntoA3Db = true;
		break;

// Parent Section
	case AJUGEND_SECTION_POS_PARENT_SECTION:
	case AJUGEND_SECTION_POS_VEREIN_EXPANDED:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromAJugendSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (AJUGEND_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case AJUGEND_SECTION_POS_VORNAHME:
	case AJUGEND_SECTION_POS_NACHNAHME:
	case AJUGEND_SECTION_POS_VEREIN_EXPANDED:
	case AJUGEND_SECTION_POS_POSITION:
	case AJUGEND_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;

	case AJUGEND_SECTION_POS_VEREIN:
		IncludeIntoXml = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromAJugendSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static AJUGEND_SECTION_POS_TYPE GetAJugendSectionPosTypeFromString (const std::string& TypeString)
{
	AJUGEND_SECTION_POS_TYPE FoundPos = AJUGEND_SECTION_POS_UNKNOWN;

	for (int TempPos = AJUGEND_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_AJUGEND_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromAJugendSectionPosType ((AJUGEND_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (AJUGEND_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetAJugendSectionPosTypeFromString

void AssignAJugendField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<ajugend>(SectionList, SectionLineCount, Line);
} // AssignAJugendField

std::string GetAJugendCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = AJUGEND_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_AJUGEND_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromAJugendSectionPosType ((AJUGEND_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetAJugendCsvHeader

static AJUGEND_ENUM_TYPE GetAJugendEnumTypeFromPosition (AJUGEND_SECTION_POS_TYPE SectionPos)
{
	AJUGEND_ENUM_TYPE EnumType = AJUGEND_ENUM_UNKNOWN;
	switch ((AJUGEND_SECTION_POS_TYPE) SectionPos)
	{
	case AJUGEND_SECTION_POS_POSITION:
		EnumType = AJUGEND_ENUM_POSITION;
		break;

	default:
		//do nothing
		break;
	} // switch section pos

	return (EnumType);
} // GetAJugendEnumTypeFromPosition

void GetAJugendAllowedValues (std::vector<FIELD_VALUE_STRUCT>& AllowedValues)
{
	for (int SectionPos = AJUGEND_SECTION_POS_UNKNOWN + 1; SectionPos < NO_OF_AJUGEND_SECTION_POS_TYPES; SectionPos++)
	{
		ENUM_FUNC EnumFunc = nullptr;
		int EnumLow = 0;
		int EnumHigh = 0;
		AJUGEND_ENUM_TYPE AJugendEnum = AJUGEND_ENUM_UNKNOWN;
		bool DetailsFound = false;

		if ((AJugendEnum = GetAJugendEnumTypeFromPosition ((AJUGEND_SECTION_POS_TYPE) SectionPos)) != AJUGEND_ENUM_UNKNOWN)
		{
			// Ignore this for special case handled below
			GetEnumDetails(SectionPos, AJugendEnum, EnumFunc, EnumLow, EnumHigh);
			DetailsFound = true;
		} // if enum field

		// Add Values
		if (DetailsFound)
		{
			// Add the Value Entry to the List
			AddFieldValueEntryToList (AllowedValues, GetNameFromAJugendSectionPosType((AJUGEND_SECTION_POS_TYPE) SectionPos));

			// Add allowed Values
			AddFieldValuesForLastEntry (AllowedValues, EnumLow, EnumHigh, EnumFunc);
		} // if got a function
	} // for each section pos
} // GetAJugendAllowedValues
