#include "iverein.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

iverein::iverein(void)
{
}

iverein::~iverein(void)
{
}

std::string iverein::GetUniqueId ()
{
	return(this->Vereinsnahme);
} // GetUniqueId

SECTION_TYPE iverein::GetSectionType ()
{
	return(SECTION_TYPE_IVEREIN);
} // GetSectionType

std::string iverein::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case IVEREIN_SECTION_POS_VEREINSNAHME:
		return (this->Vereinsnahme);
	case IVEREIN_SECTION_POS_LAND:
		return (this->Land);
	case IVEREIN_SECTION_POS_LAND_EXPANDED:
		return (this->Land_Expanded);

			// Parent Section
	case IVEREIN_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromIVereinSectionPosType (const IVEREIN_SECTION_POS_TYPE IVereinSectionPosType)
{
	switch (IVereinSectionPosType)
	{
	case IVEREIN_SECTION_POS_VEREINSNAHME:
		return ("Vereinsnahme");
	case IVEREIN_SECTION_POS_LAND:
		return ("Land_UNEXPANDED");
	case IVEREIN_SECTION_POS_LAND_EXPANDED:
		return ("Land");

	case IVEREIN_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << IVereinSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromIVereinSectionPosType

void iverein::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case IVEREIN_SECTION_POS_VEREINSNAHME:
		this->Vereinsnahme = FieldValue;
		break;
	case IVEREIN_SECTION_POS_LAND:
		this->Land = FieldValue;
		break;
	case IVEREIN_SECTION_POS_LAND_EXPANDED:
		this->Land_Expanded = FieldValue;
		break;

			// Parent Section	
	case IVEREIN_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void iverein::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int IVereinPos = IVEREIN_SECTION_POS_UNKNOWN + 1; IVereinPos < NO_OF_IVEREIN_SECTION_POS_TYPES; IVereinPos++)
	{
		if (IncludeSectionPosIntoXml ((IVEREIN_SECTION_POS_TYPE) IVereinPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromIVereinSectionPosType ((IVEREIN_SECTION_POS_TYPE) IVereinPos), 			
				this->GetValueAtSectionPos(IVereinPos))));
		}
	}

} // PopulateValuePairVectorForExport

void iverein::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& IVereinValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = IVereinValuePairs.begin(); 
		Iterator != IVereinValuePairs.end(); ++Iterator)
	{
		IVEREIN_SECTION_POS_TYPE FieldPos = GetIVereinSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != IVEREIN_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void iverein::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = IVEREIN_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_IVEREIN_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((IVEREIN_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void iverein::DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Land Field
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, IVEREIN_SECTION_POS_LAND, IVEREIN_SECTION_POS_LAND_EXPANDED, SectionList);
} // DecodeFieldsFromA3Db

void iverein::EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE ReferenceType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	switch (ReferenceType)
	{
	case FIELD_REFERENCE_LAND:
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, IVEREIN_SECTION_POS_LAND_EXPANDED, IVEREIN_SECTION_POS_LAND, SectionList);
		break;

	case FIELD_REFERENCE_VEREIN:
		break;

	default:
		break;
	} // switch reference types
} // EncodeFieldsToA3Db

static bool IncludeSectionPosIntoA3Db (IVEREIN_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case IVEREIN_SECTION_POS_VEREINSNAHME:
	case IVEREIN_SECTION_POS_LAND:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case IVEREIN_SECTION_POS_PARENT_SECTION:
	case IVEREIN_SECTION_POS_LAND_EXPANDED:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromIVereinSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (IVEREIN_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case IVEREIN_SECTION_POS_VEREINSNAHME:
	case IVEREIN_SECTION_POS_PARENT_SECTION:
	case IVEREIN_SECTION_POS_LAND_EXPANDED:
		IncludeIntoXml = true;
		break;

	case IVEREIN_SECTION_POS_LAND:
		IncludeIntoXml = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromIVereinSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static IVEREIN_SECTION_POS_TYPE GetIVereinSectionPosTypeFromString (const std::string& TypeString)
{
	IVEREIN_SECTION_POS_TYPE FoundPos = IVEREIN_SECTION_POS_UNKNOWN;

	for (int TempPos = IVEREIN_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_IVEREIN_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromIVereinSectionPosType ((IVEREIN_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (IVEREIN_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetIVereinSectionPosTypeFromString

void AssignIVereinField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<iverein>(SectionList, SectionLineCount, Line);
} // AssignIVereinField

std::string GetIVereinCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = IVEREIN_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_IVEREIN_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromIVereinSectionPosType ((IVEREIN_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetIVereinCsvHeader
