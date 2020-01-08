#include "kritiker.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

kritiker::kritiker(void)
{
}

kritiker::~kritiker(void)
{
}

std::string kritiker::GetUniqueId ()
{
	return(this->Nachnahme + this->Vornahme);
} // GetUniqueId

SECTION_TYPE kritiker::GetSectionType ()
{
	return(SECTION_TYPE_KRITIKER);
} // GetSectionType

std::string kritiker::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case KRITIKER_SECTION_POS_NACHNAHME:
		return (this->Nachnahme);
	case KRITIKER_SECTION_POS_VORNAHME:
		return (this->Vornahme);

			// Parent Section
	case KRITIKER_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromKritikerSectionPosType (const KRITIKER_SECTION_POS_TYPE KritikerSectionPosType)
{
	switch (KritikerSectionPosType)
	{
	case KRITIKER_SECTION_POS_NACHNAHME:
		return ("Nachnahme");
	case KRITIKER_SECTION_POS_VORNAHME:
		return ("Vornahme");

	case KRITIKER_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << KritikerSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromKritikerSectionPosType

void kritiker::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case KRITIKER_SECTION_POS_NACHNAHME:
		this->Nachnahme = FieldValue;
		break;
	case KRITIKER_SECTION_POS_VORNAHME:
		this->Vornahme = FieldValue;
		break;

			// Parent Section	
	case KRITIKER_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void kritiker::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int KritikerPos = KRITIKER_SECTION_POS_UNKNOWN + 1; KritikerPos < NO_OF_KRITIKER_SECTION_POS_TYPES; KritikerPos++)
	{
		if (IncludeSectionPosIntoXml ((KRITIKER_SECTION_POS_TYPE) KritikerPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromKritikerSectionPosType ((KRITIKER_SECTION_POS_TYPE) KritikerPos), 			
				this->GetValueAtSectionPos(KritikerPos))));
		}
	}

} // PopulateValuePairVectorForExport

void kritiker::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& KritikerValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = KritikerValuePairs.begin(); 
		Iterator != KritikerValuePairs.end(); ++Iterator)
	{
		KRITIKER_SECTION_POS_TYPE FieldPos = GetKritikerSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != KRITIKER_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void kritiker::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = KRITIKER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_KRITIKER_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((KRITIKER_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

static bool IncludeSectionPosIntoA3Db (KRITIKER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case KRITIKER_SECTION_POS_NACHNAHME:
	case KRITIKER_SECTION_POS_VORNAHME:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case KRITIKER_SECTION_POS_PARENT_SECTION:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromKritikerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (KRITIKER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case KRITIKER_SECTION_POS_NACHNAHME:
	case KRITIKER_SECTION_POS_VORNAHME:
	case KRITIKER_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromKritikerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static KRITIKER_SECTION_POS_TYPE GetKritikerSectionPosTypeFromString (const std::string& TypeString)
{
	KRITIKER_SECTION_POS_TYPE FoundPos = KRITIKER_SECTION_POS_UNKNOWN;

	for (int TempPos = KRITIKER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_KRITIKER_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromKritikerSectionPosType ((KRITIKER_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (KRITIKER_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetKritikerSectionPosTypeFromString

void AssignKritikerField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<kritiker>(SectionList, SectionLineCount, Line);
} // AssignKritikerField

std::string GetKritikerCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = KRITIKER_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_KRITIKER_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromKritikerSectionPosType ((KRITIKER_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetKritikerCsvHeader
