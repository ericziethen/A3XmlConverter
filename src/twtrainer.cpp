#include "twtrainer.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

twtrainer::twtrainer(void)
{
}

twtrainer::~twtrainer(void)
{
}

std::string twtrainer::GetUniqueId ()
{
	return(this->Vornahme + this->Nachnahme);
} // GetUniqueId

SECTION_TYPE twtrainer::GetSectionType ()
{
	return(SECTION_TYPE_TWTRAINER);
} // GetSectionType

std::string twtrainer::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case TWTRAINER_SECTION_POS_VORNAHME:
		return (this->Vornahme);
	case TWTRAINER_SECTION_POS_NACHNAHME:
		return (this->Nachnahme);
	case TWTRAINER_SECTION_POS_KOMPETENZ:
		return (this->Kompetenz);
	case TWTRAINER_SECTION_POS_ALTER:
		return (this->Alter);
	case TWTRAINER_SECTION_POS_GEBURTSDATUM:
		return (this->Geburtsdatum);
	case TWTRAINER_SECTION_POS_UNKNWON_06:
		return (this->TWTRAINER_FIELD_UNKNOWN_06);
	case TWTRAINER_SECTION_POS_UNKNOWN_07:
		return (this->TWTRAINER_FIELD_UNKNOWN_07);

			// Parent Section
	case TWTRAINER_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromTwTrainerSectionPosType (const TWTRAINER_SECTION_POS_TYPE TwTrainerSectionPosType)
{
	switch (TwTrainerSectionPosType)
	{
	case TWTRAINER_SECTION_POS_VORNAHME:
		return ("Vornahme");
	case TWTRAINER_SECTION_POS_NACHNAHME:
		return ("Nachnahme");
	case TWTRAINER_SECTION_POS_KOMPETENZ:
		return ("Kompetenz");
	case TWTRAINER_SECTION_POS_ALTER:
		return ("Alter");
	case TWTRAINER_SECTION_POS_GEBURTSDATUM:
		return ("Geburtsdatum");
	case TWTRAINER_SECTION_POS_UNKNWON_06:
		return ("TWTRAINER_FIELD_UNKNOWN_06");
	case TWTRAINER_SECTION_POS_UNKNOWN_07:
		return ("TWTRAINER_FIELD_UNKNOWN_07");

	case TWTRAINER_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << TwTrainerSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromTwTrainerSectionPosType

void twtrainer::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case TWTRAINER_SECTION_POS_VORNAHME:
		this->Vornahme = FieldValue;
		break;
	case TWTRAINER_SECTION_POS_NACHNAHME:
		this->Nachnahme = FieldValue;
		break;
	case TWTRAINER_SECTION_POS_KOMPETENZ:
		this->Kompetenz = FieldValue;
		break;
	case TWTRAINER_SECTION_POS_ALTER:
		this->Alter = FieldValue;
		break;
	case TWTRAINER_SECTION_POS_GEBURTSDATUM:
		this->Geburtsdatum = FieldValue;
		break;
	case TWTRAINER_SECTION_POS_UNKNWON_06:
		this->TWTRAINER_FIELD_UNKNOWN_06 = FieldValue;
		break;
	case TWTRAINER_SECTION_POS_UNKNOWN_07:
		this->TWTRAINER_FIELD_UNKNOWN_07 = FieldValue;
		break;

			// Parent Section	
	case TWTRAINER_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void twtrainer::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int TwTrainerPos = TWTRAINER_SECTION_POS_UNKNOWN + 1; TwTrainerPos < NO_OF_TWTRAINER_SECTION_POS_TYPES; TwTrainerPos++)
	{
		if (IncludeSectionPosIntoXml ((TWTRAINER_SECTION_POS_TYPE) TwTrainerPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromTwTrainerSectionPosType ((TWTRAINER_SECTION_POS_TYPE) TwTrainerPos), 			
				this->GetValueAtSectionPos(TwTrainerPos))));
		}
	}

} // PopulateValuePairVectorForExport

void twtrainer::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& TwTrainerValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = TwTrainerValuePairs.begin(); 
		Iterator != TwTrainerValuePairs.end(); ++Iterator)
	{
		TWTRAINER_SECTION_POS_TYPE FieldPos = GetTwTrainerSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != TWTRAINER_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void twtrainer::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = TWTRAINER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_TWTRAINER_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((TWTRAINER_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

static bool IncludeSectionPosIntoA3Db (TWTRAINER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case TWTRAINER_SECTION_POS_VORNAHME:
	case TWTRAINER_SECTION_POS_NACHNAHME:
	case TWTRAINER_SECTION_POS_KOMPETENZ:
	case TWTRAINER_SECTION_POS_ALTER:
	case TWTRAINER_SECTION_POS_GEBURTSDATUM:
	case TWTRAINER_SECTION_POS_UNKNWON_06:
	case TWTRAINER_SECTION_POS_UNKNOWN_07:
		IncludeIntoA3Db = true;
		break;

	// Parent Section
	case TWTRAINER_SECTION_POS_PARENT_SECTION:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromTwTrainerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (TWTRAINER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case TWTRAINER_SECTION_POS_VORNAHME:
	case TWTRAINER_SECTION_POS_NACHNAHME:
	case TWTRAINER_SECTION_POS_KOMPETENZ:
	case TWTRAINER_SECTION_POS_ALTER:
	case TWTRAINER_SECTION_POS_GEBURTSDATUM:
	case TWTRAINER_SECTION_POS_UNKNWON_06:
	case TWTRAINER_SECTION_POS_UNKNOWN_07:
	case TWTRAINER_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromTwTrainerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static TWTRAINER_SECTION_POS_TYPE GetTwTrainerSectionPosTypeFromString (const std::string& TypeString)
{
	TWTRAINER_SECTION_POS_TYPE FoundPos = TWTRAINER_SECTION_POS_UNKNOWN;

	for (int TempPos = TWTRAINER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_TWTRAINER_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromTwTrainerSectionPosType ((TWTRAINER_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (TWTRAINER_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetTwTrainerSectionPosTypeFromString

void AssignTwTrainerField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<twtrainer>(SectionList, SectionLineCount, Line);
} // AssignTwTrainerField

std::string GetTwTrainerCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = TWTRAINER_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_TWTRAINER_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromTwTrainerSectionPosType ((TWTRAINER_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetTwTrainerCsvHeader