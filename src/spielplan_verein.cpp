#include "spielplan_verein.h"
#include "error_handling.h"
#include <sstream>
#include <iostream>

spielplan_verein::spielplan_verein(void)
{
}

spielplan_verein::~spielplan_verein(void)
{
}

std::string spielplan_verein::GetUniqueId ()
{
	return(this->Vereinsname);
} // GetUniqueId

SECTION_TYPE spielplan_verein::GetSectionType ()
{
	return(SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN);
} // GetSectionType

std::string spielplan_verein::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME:
		return (this->Vereinsname);
	case SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME_EXPANDED:
		return (this->Vereinsname_Expanded);

			// Parent Section
	case SPIELPLAN_VEREIN_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromSpielplan_VereinSectionPosType (const SPIELPLAN_VEREIN_SECTION_POS_TYPE Spielplan_VereinSectionPosType)
{
	switch (Spielplan_VereinSectionPosType)
	{
	case SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME:
		return ("Vereinsname_UNEXPANDED");
	case SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME_EXPANDED:
		return ("Vereinsname");

	case SPIELPLAN_VEREIN_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << Spielplan_VereinSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromSpielplan_VereinSectionPosType

void spielplan_verein::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME:
		this->Vereinsname = FieldValue;
		break;
	case SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME_EXPANDED:
		this->Vereinsname_Expanded = FieldValue;
		break;

			// Parent Section	
	case SPIELPLAN_VEREIN_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void spielplan_verein::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int Spielplan_VereinPos = SPIELPLAN_VEREIN_SECTION_POS_UNKNOWN + 1; Spielplan_VereinPos < NO_OF_SPIELPLAN_VEREIN_SECTION_POS_TYPES; Spielplan_VereinPos++)
	{
		if (IncludeSectionPosIntoXml ((SPIELPLAN_VEREIN_SECTION_POS_TYPE) Spielplan_VereinPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromSpielplan_VereinSectionPosType ((SPIELPLAN_VEREIN_SECTION_POS_TYPE) Spielplan_VereinPos), 			
				this->GetValueAtSectionPos(Spielplan_VereinPos))));
		}
	}

} // PopulateValuePairVectorForExport

void spielplan_verein::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& Spielplan_VereinValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = Spielplan_VereinValuePairs.begin(); 
		Iterator != Spielplan_VereinValuePairs.end(); ++Iterator)
	{
		SPIELPLAN_VEREIN_SECTION_POS_TYPE FieldPos = GetSpielplan_VereinSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != SPIELPLAN_VEREIN_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void spielplan_verein::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = SPIELPLAN_VEREIN_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_SPIELPLAN_VEREIN_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((SPIELPLAN_VEREIN_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void spielplan_verein::DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Verein Field
	this->ConvertVereinField(SECTION_EXPANSION_FROM_A3DB_VEREIN, SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME, 
								SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME_EXPANDED, this->GetA3FileLandId(), SectionList);
} // DecodeFieldsFromA3Db

void spielplan_verein::EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE ReferenceType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	switch (ReferenceType)
	{
	case FIELD_REFERENCE_LAND:
		break;

	case FIELD_REFERENCE_VEREIN:
		this->ConvertVereinField(SECTION_EXPANSION_TO_A3DB_VEREIN, SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME_EXPANDED, 
			SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME, this->GetA3FileLandId(), SectionList);
		break;

	default:
		break;
	} // switch reference types
} // EncodeFieldsToA3Db 

static bool IncludeSectionPosIntoA3Db (SPIELPLAN_VEREIN_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case SPIELPLAN_VEREIN_SECTION_POS_PARENT_SECTION:
	case SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME_EXPANDED:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromSpielplan_VereinSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (SPIELPLAN_VEREIN_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME_EXPANDED:
	case SPIELPLAN_VEREIN_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;

	case SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME:
		IncludeIntoXml = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromSpielplan_VereinSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static SPIELPLAN_VEREIN_SECTION_POS_TYPE GetSpielplan_VereinSectionPosTypeFromString (const std::string& TypeString)
{
	SPIELPLAN_VEREIN_SECTION_POS_TYPE FoundPos = SPIELPLAN_VEREIN_SECTION_POS_UNKNOWN;

	for (int TempPos = SPIELPLAN_VEREIN_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_SPIELPLAN_VEREIN_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromSpielplan_VereinSectionPosType ((SPIELPLAN_VEREIN_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (SPIELPLAN_VEREIN_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetSpielplan_VereinSectionPosTypeFromString

void AssignSpielplan_VereinField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<spielplan_verein>(SectionList, SectionLineCount, Line);
} // AssignSpielplan_VereinField

std::string GetSpielplan_VereinCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = SPIELPLAN_VEREIN_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_SPIELPLAN_VEREIN_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromSpielplan_VereinSectionPosType ((SPIELPLAN_VEREIN_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetSpielplan_VereinCsvHeader

void PopulateSpielplanVereinMap (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], 
								 INT_STRING_HASHBIMAP_TYPE& SpielplanVereinMap)
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	std::vector<std::shared_ptr<section>> SectionVector = SectionList [SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN];
	int VereinCount = 0;
	// for simplicity just asume each value only exists once
	for (SectionIterator = SectionVector.begin(); SectionIterator != SectionVector.end(); ++SectionIterator)
	{
		// Increment Vereincount (Indices starting with 1, so do before inserting)
		VereinCount++;

		// Insert Team
		T_InserBimapValue<int,std::string>(
			VereinCount, std::static_pointer_cast<spielplan_verein>(*SectionIterator)->GetValueAtSectionPos(SPIELPLAN_VEREIN_SECTION_POS_VEREINSNAME_EXPANDED),
			SpielplanVereinMap);
	} // For each Spielplan Verein
} // PopulateSpielplanVereinMap
