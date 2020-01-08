#include "liga.h"
#include "error_handling.h"
#include <sstream>
#include <iostream>

liga::liga(void)
{
}

liga::~liga(void)
{
}

std::string liga::GetUniqueId ()
{
	return(this->Liganame);
} // GetUniqueId

SECTION_TYPE liga::GetSectionType ()
{
	return(SECTION_TYPE_LIGA);
} // GetSectionType

std::string liga::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case LIGA_SECTION_POS_LIGA_NAHME:
		return (this->Liganame);
	case LIGA_SECTION_POS_LIGA_KUERZL:
		return (this->Ligakuerzl);
	case LIGA_SECTION_POS_VEREINSANZAHL:
		return (this->Vereinsanzahl);

			// Parent Section
	case LIGA_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromLigaSectionPosType (const LIGA_SECTION_POS_TYPE LigaSectionPosType)
{
	switch (LigaSectionPosType)
	{
	case LIGA_SECTION_POS_LIGA_NAHME:
		return ("Liganame");
	case LIGA_SECTION_POS_LIGA_KUERZL:
		return ("Ligakuerzl");
	case LIGA_SECTION_POS_VEREINSANZAHL:
		return ("Vereinsanzahl");

	case LIGA_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << LigaSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromLigaSectionPosType

void liga::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case LIGA_SECTION_POS_LIGA_NAHME:
		this->Liganame = FieldValue;
		break;
	case LIGA_SECTION_POS_LIGA_KUERZL:
		this->Ligakuerzl = FieldValue;
		break;
	case LIGA_SECTION_POS_VEREINSANZAHL:
		this->Vereinsanzahl = FieldValue;
		break;

			// Parent Section	
	case LIGA_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void liga::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int LigaPos = LIGA_SECTION_POS_UNKNOWN + 1; LigaPos < NO_OF_LIGA_SECTION_POS_TYPES; LigaPos++)
	{
		if (IncludeSectionPosIntoXml ((LIGA_SECTION_POS_TYPE) LigaPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromLigaSectionPosType ((LIGA_SECTION_POS_TYPE) LigaPos), 			
				this->GetValueAtSectionPos(LigaPos))));
		}
	}

} // PopulateValuePairVectorForExport

void liga::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& LigaValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = LigaValuePairs.begin(); 
		Iterator != LigaValuePairs.end(); ++Iterator)
	{
		LIGA_SECTION_POS_TYPE FieldPos = GetLigaSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != LIGA_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void liga::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = LIGA_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_LIGA_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((LIGA_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

static bool IncludeSectionPosIntoA3Db (LIGA_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case LIGA_SECTION_POS_LIGA_NAHME:
	case LIGA_SECTION_POS_LIGA_KUERZL:
	case LIGA_SECTION_POS_VEREINSANZAHL:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case LIGA_SECTION_POS_PARENT_SECTION:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromLigaSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (LIGA_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case LIGA_SECTION_POS_LIGA_NAHME:
	case LIGA_SECTION_POS_LIGA_KUERZL:
	case LIGA_SECTION_POS_VEREINSANZAHL:
	case LIGA_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromLigaSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static LIGA_SECTION_POS_TYPE GetLigaSectionPosTypeFromString (const std::string& TypeString)
{
	LIGA_SECTION_POS_TYPE FoundPos = LIGA_SECTION_POS_UNKNOWN;

	for (int TempPos = LIGA_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_LIGA_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromLigaSectionPosType ((LIGA_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (LIGA_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetLigaSectionPosTypeFromString

void AssignLigaField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<liga>(SectionList, SectionLineCount, Line);
} // AssignLigaField

std::string GetLigaCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = LIGA_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_LIGA_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromLigaSectionPosType ((LIGA_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetLigaCsvHeader
