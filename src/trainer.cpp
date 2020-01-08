#include "trainer.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

trainer::trainer(void)
{
}

trainer::~trainer(void)
{
}

std::string trainer::GetUniqueId ()
{
	return(this->Vornahme + this->Nachnahme);
} // GetUniqueId

SECTION_TYPE trainer::GetSectionType ()
{
	return(SECTION_TYPE_TRAINER);
} // GetSectionType

std::string trainer::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case TRAINER_SECTION_POS_VORNAHME:
		return (this->Vornahme);
	case TRAINER_SECTION_POS_NACHNAHME:
		return (this->Nachnahme);
	case TRAINER_SECTION_POS_KOMPETENZ:
		return (this->Kompetenz);
	case TRAINER_SECTION_POS_RUF:
		return (this->Ruf);
	case TRAINER_SECTION_POS_ALTER:
		return (this->Alter);
	case TRAINER_SECTION_POS_GEBURTSDATUM:
		return (this->Geburtsdatum);
	case TRAINER_SECTION_POS_UNKNOWN_07:
		return (this->TRAINER_FIELD_UNKNOWN_07);
	case TRAINER_SECTION_POS_UNKNOWN_08:
		return (this->TRAINER_FIELD_UNKNOWN_08);

			// Reference Section
	case TRAINER_SECTION_POS_REFERENCE_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromTrainerSectionPosType (const TRAINER_SECTION_POS_TYPE TrainerSectionPosType)
{
	switch (TrainerSectionPosType)
	{
	case TRAINER_SECTION_POS_VORNAHME:
		return ("Vornahme");
	case TRAINER_SECTION_POS_NACHNAHME:
		return ("Nachnahme");
	case TRAINER_SECTION_POS_KOMPETENZ:
		return ("Kompetenz");
	case TRAINER_SECTION_POS_RUF:
		return ("Ruf");
	case TRAINER_SECTION_POS_ALTER:
		return ("Alter");
	case TRAINER_SECTION_POS_GEBURTSDATUM:
		return ("Geburtsdatum");
	case TRAINER_SECTION_POS_UNKNOWN_07:
		return ("TRAINER_FIELD_UNKNOWN_07");
	case TRAINER_SECTION_POS_UNKNOWN_08:
		return ("TRAINER_FIELD_UNKNOWN_08");

	case TRAINER_SECTION_POS_REFERENCE_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << TrainerSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromTrainerSectionPosType

void trainer::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case TRAINER_SECTION_POS_VORNAHME:
		this->Vornahme = FieldValue;
		break;
	case TRAINER_SECTION_POS_NACHNAHME:
		this->Nachnahme = FieldValue;
		break;
	case TRAINER_SECTION_POS_KOMPETENZ:
		this->Kompetenz = FieldValue;
		break;
	case TRAINER_SECTION_POS_RUF:
		this->Ruf = FieldValue;
		break;
	case TRAINER_SECTION_POS_ALTER:
		this->Alter = FieldValue;
		break;
	case TRAINER_SECTION_POS_GEBURTSDATUM:
		this->Geburtsdatum = FieldValue;
		break;
	case TRAINER_SECTION_POS_UNKNOWN_07:
		this->TRAINER_FIELD_UNKNOWN_07 = FieldValue;
		break;
	case TRAINER_SECTION_POS_UNKNOWN_08:
		this->TRAINER_FIELD_UNKNOWN_08 = FieldValue;
		break;

			// Reference Section	
	case TRAINER_SECTION_POS_REFERENCE_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void trainer::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int TrainerPos = TRAINER_SECTION_POS_UNKNOWN + 1; TrainerPos < NO_OF_TRAINER_SECTION_POS_TYPES; TrainerPos++)
	{
		if (IncludeSectionPosIntoXml ((TRAINER_SECTION_POS_TYPE) TrainerPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromTrainerSectionPosType ((TRAINER_SECTION_POS_TYPE) TrainerPos), 			
				this->GetValueAtSectionPos(TrainerPos))));
		}
	}

} // PopulateValuePairVectorForExport

void trainer::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& TrainerValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = TrainerValuePairs.begin(); 
		Iterator != TrainerValuePairs.end(); ++Iterator)
	{
		TRAINER_SECTION_POS_TYPE FieldPos = GetTrainerSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != TRAINER_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void trainer::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = TRAINER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_TRAINER_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((TRAINER_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void trainer::DecodeEnumsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Enum Ruf
	this->DecodeEnumFromA3Db(TRAINER_SECTION_POS_RUF, TRAINER_ENUM_RUF, GetTrainerEnumValue, GetEnumDetails);

} // DecodeEnumsFromA3Db

void trainer::EncodeEnumsToA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Encode Enum Ruf
	this->EncodeEnumToA3Db(TRAINER_SECTION_POS_RUF, TRAINER_ENUM_RUF, GetTrainerEnumValue, GetEnumDetails);

} // EncodeEnumsToA3Db

void GetEnumDetails (int SectionPos, int EnumType, ENUM_FUNC& EnumFunc, int& EnumLow, int& EnumHigh)
{
	switch ((TRAINER_ENUM_TYPE) EnumType)
	{
	case TRAINER_ENUM_RUF:
		EnumFunc = GetNameFromTrainerRufType;
		EnumLow = TRAINER_RUF_UNKNOWN;
		EnumHigh = NO_OF_TRAINER_RUF_TYPES;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << EnumType << " (" << 
			GetNameFromTrainerEnumType((TRAINER_ENUM_TYPE) EnumType) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	} // switch enum type
} // GetEnumDetails

static bool IncludeSectionPosIntoA3Db (TRAINER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case TRAINER_SECTION_POS_VORNAHME:
	case TRAINER_SECTION_POS_NACHNAHME:
	case TRAINER_SECTION_POS_KOMPETENZ:
	case TRAINER_SECTION_POS_RUF:
	case TRAINER_SECTION_POS_ALTER:
	case TRAINER_SECTION_POS_GEBURTSDATUM:
	case TRAINER_SECTION_POS_UNKNOWN_07:
	case TRAINER_SECTION_POS_UNKNOWN_08:
		IncludeIntoA3Db = true;
		break;

	// Reference Section
	case TRAINER_SECTION_POS_REFERENCE_SECTION:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromTrainerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (TRAINER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case TRAINER_SECTION_POS_VORNAHME:
	case TRAINER_SECTION_POS_NACHNAHME:
	case TRAINER_SECTION_POS_KOMPETENZ:
	case TRAINER_SECTION_POS_RUF:
	case TRAINER_SECTION_POS_ALTER:
	case TRAINER_SECTION_POS_GEBURTSDATUM:
	case TRAINER_SECTION_POS_UNKNOWN_07:
	case TRAINER_SECTION_POS_UNKNOWN_08:
	case TRAINER_SECTION_POS_REFERENCE_SECTION:
		IncludeIntoXml = true;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromTrainerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static TRAINER_SECTION_POS_TYPE GetTrainerSectionPosTypeFromString (const std::string& TypeString)
{
	TRAINER_SECTION_POS_TYPE FoundPos = TRAINER_SECTION_POS_UNKNOWN;

	for (int TempPos = TRAINER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_TRAINER_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromTrainerSectionPosType ((TRAINER_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (TRAINER_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetTrainerSectionPosTypeFromString

void AssignTrainerField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<trainer>(SectionList, SectionLineCount, Line);
} // AssignTrainerField

std::string GetTrainerCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = TRAINER_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_TRAINER_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromTrainerSectionPosType ((TRAINER_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetTrainerCsvHeader

static TRAINER_ENUM_TYPE GetTrainerEnumTypeFromPosition (TRAINER_SECTION_POS_TYPE SectionPos)
{
	TRAINER_ENUM_TYPE EnumType = TRAINER_ENUM_UNKNOWN;
	switch ((TRAINER_SECTION_POS_TYPE) SectionPos)
	{
	case TRAINER_SECTION_POS_RUF:
		EnumType = TRAINER_ENUM_RUF;
		break;

	default:
		//do nothing
		break;
	} // switch section pos

	return (EnumType);
} // GetTrainerEnumTypeFromPosition

void GetTrainerAllowedValues (std::vector<FIELD_VALUE_STRUCT>& AllowedValues)
{
	for (int SectionPos = TRAINER_SECTION_POS_UNKNOWN + 1; SectionPos < NO_OF_TRAINER_SECTION_POS_TYPES; SectionPos++)
	{
		ENUM_FUNC EnumFunc = nullptr;
		int EnumLow = 0;
		int EnumHigh = 0;
		TRAINER_ENUM_TYPE TrainerEnum = TRAINER_ENUM_UNKNOWN;
		bool DetailsFound = false;

		if ((TrainerEnum = GetTrainerEnumTypeFromPosition ((TRAINER_SECTION_POS_TYPE) SectionPos)) != TRAINER_ENUM_UNKNOWN)
		{
			// Ignore this for special case handled below
			GetEnumDetails(SectionPos, TrainerEnum, EnumFunc, EnumLow, EnumHigh);
			DetailsFound = true;
		} // if enum field

		// Add Values
		if (DetailsFound)
		{
			// Add the Value Entry to the List
			AddFieldValueEntryToList (AllowedValues, GetNameFromTrainerSectionPosType((TRAINER_SECTION_POS_TYPE) SectionPos));

			// Add allowed Values
			AddFieldValuesForLastEntry (AllowedValues, EnumLow, EnumHigh, EnumFunc);
		} // if got a function
	} // for each section pos
} // GetTrainerAllowedValues
