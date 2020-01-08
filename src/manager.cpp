#include "manager.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

manager::manager(void)
{
}

manager::~manager(void)
{
}

std::string manager::GetUniqueId ()
{
	return(this->Vornahme + this->Nachnahme);
} // GetUniqueId

SECTION_TYPE manager::GetSectionType ()
{
	return(SECTION_TYPE_MANAGER);
} // GetSectionType

std::string manager::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case MANAGER_SECTION_POS_VORNAHME:
		return (this->Vornahme);
	case MANAGER_SECTION_POS_NACHNAHME:
		return (this->Nachnahme);
	case MANAGER_SECTION_POS_KOMPETENZ:
		return (this->Kompetenz);
	case MANAGER_SECTION_POS_ALTER:
		return (this->Alter);
	case MANAGER_SECTION_POS_GEBURTSDATUM:
		return (this->Geburtsdatum);

			// Reference Section
	case MANAGER_SECTION_POS_REFERENCE_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromManagerSectionPosType (const MANAGER_SECTION_POS_TYPE ManagerSectionPosType)
{
	switch (ManagerSectionPosType)
	{
	case MANAGER_SECTION_POS_VORNAHME:
		return ("Vornahme");
	case MANAGER_SECTION_POS_NACHNAHME:
		return ("Nachnahme");
	case MANAGER_SECTION_POS_KOMPETENZ:
		return ("Kompetenz");
	case MANAGER_SECTION_POS_ALTER:
		return ("Alter");
	case MANAGER_SECTION_POS_GEBURTSDATUM:
		return ("Geburtsdatum");

	case MANAGER_SECTION_POS_REFERENCE_SECTION:
		return (XML_PARENT_SECTION_STRING);

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << ManagerSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromManagerSectionPosType

void manager::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case MANAGER_SECTION_POS_VORNAHME:
		this->Vornahme = FieldValue;
		break;
	case MANAGER_SECTION_POS_NACHNAHME:
		this->Nachnahme = FieldValue;
		break;
	case MANAGER_SECTION_POS_KOMPETENZ:
		this->Kompetenz = FieldValue;
		break;
	case MANAGER_SECTION_POS_ALTER:
		this->Alter = FieldValue;
		break;
	case MANAGER_SECTION_POS_GEBURTSDATUM:
		this->Geburtsdatum = FieldValue;
		break;

			// Reference Section	
	case MANAGER_SECTION_POS_REFERENCE_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void manager::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int ManagerPos = MANAGER_SECTION_POS_UNKNOWN + 1; ManagerPos < NO_OF_MANAGER_SECTION_POS_TYPES; ManagerPos++)
	{
		if (IncludeSectionPosIntoXml ((MANAGER_SECTION_POS_TYPE) ManagerPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromManagerSectionPosType ((MANAGER_SECTION_POS_TYPE) ManagerPos), 			
				this->GetValueAtSectionPos(ManagerPos))));
		}
	}

} // PopulateValuePairVectorForExport

void manager::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& ManagerValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = ManagerValuePairs.begin(); 
		Iterator != ManagerValuePairs.end(); ++Iterator)
	{
		MANAGER_SECTION_POS_TYPE FieldPos = GetManagerSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != MANAGER_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void manager::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = MANAGER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_MANAGER_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((MANAGER_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

static bool IncludeSectionPosIntoA3Db (MANAGER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case MANAGER_SECTION_POS_VORNAHME:
	case MANAGER_SECTION_POS_NACHNAHME:
	case MANAGER_SECTION_POS_KOMPETENZ:
	case MANAGER_SECTION_POS_ALTER:
	case MANAGER_SECTION_POS_GEBURTSDATUM:
		IncludeIntoA3Db = true;
		break;

	// Reference Section
	case MANAGER_SECTION_POS_REFERENCE_SECTION:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromManagerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (MANAGER_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case MANAGER_SECTION_POS_VORNAHME:
	case MANAGER_SECTION_POS_NACHNAHME:
	case MANAGER_SECTION_POS_KOMPETENZ:
	case MANAGER_SECTION_POS_ALTER:
	case MANAGER_SECTION_POS_GEBURTSDATUM:
	case MANAGER_SECTION_POS_REFERENCE_SECTION:
		IncludeIntoXml = true;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromManagerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static MANAGER_SECTION_POS_TYPE GetManagerSectionPosTypeFromString (const std::string& TypeString)
{
	MANAGER_SECTION_POS_TYPE FoundPos = MANAGER_SECTION_POS_UNKNOWN;

	for (int TempPos = MANAGER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_MANAGER_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromManagerSectionPosType ((MANAGER_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (MANAGER_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetManagerSectionPosTypeFromString

void AssignManagerField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<manager>(SectionList, SectionLineCount, Line);
} // AssignManagerField

std::string GetManagerCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = MANAGER_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_MANAGER_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromManagerSectionPosType ((MANAGER_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetManagerCsvHeader