#include "nation.h"

#include "error_handling.h"
#include "misc_lib.h"
#include <sstream>
#include <iostream>
#include <algorithm>

#define NATION_DEFAULT_VEREINSANZAHL "0"

nation::nation(void)
{
	this->AssignField(NATION_SECTION_POS_VEREINSANZAHL, NATION_DEFAULT_VEREINSANZAHL);
}

nation::~nation(void)
{
}

std::string nation::GetUniqueId ()
{
	return(this->Land);
} // GetUniqueId

SECTION_TYPE nation::GetSectionType ()
{
	return(SECTION_TYPE_NATION);
} // GetSectionType

std::string nation::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case NATION_SECTION_POS_LAND:
		return (this->Land);
	case NATION_SECTION_POS_UNKNOWN_02:
		return (this->NATION_FIELD_UNKNOWN_02);
	case NATION_SECTION_POS_KUERZEL:
		return (this->Kuerzel);
	case NATION_SECTION_POS_UNKNOWN_04:
		return (this->NATION_FIELD_UNKNOWN_04);
	case NATION_SECTION_POS_UNKNOWN_05:
		return (this->NATION_FIELD_UNKNOWN_05);
	case NATION_SECTION_POS_UNKNOWN_06:
		return (this->NATION_FIELD_UNKNOWN_06);
	case NATION_SECTION_POS_UNKNOWN_07:
		return (this->NATION_FIELD_UNKNOWN_07);
	case NATION_SECTION_POS_UNKNOWN_08:
		return (this->NATION_FIELD_UNKNOWN_08);
	case NATION_SECTION_POS_UNKNOWN_09:
		return (this->NATION_FIELD_UNKNOWN_09);
	case NATION_SECTION_POS_UNKNOWN_10:
		return (this->NATION_FIELD_UNKNOWN_10);
	case NATION_SECTION_POS_UNKNOWN_11:
		return (this->NATION_FIELD_UNKNOWN_11);

	case NATION_SECTION_POS_VEREINSANZAHL:
		return (this->Vereinsanzahl);

			// Parent Section
	case NATION_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromNationSectionPosType (const NATION_SECTION_POS_TYPE NationSectionPosType)
{
	switch (NationSectionPosType)
	{
	case NATION_SECTION_POS_LAND:
		return ("Land");
	case NATION_SECTION_POS_UNKNOWN_02:
		return ("NATION_FIELD_UNKNOWN_02");
	case NATION_SECTION_POS_KUERZEL:
		return ("Kuerzel");
	case NATION_SECTION_POS_UNKNOWN_04:
		return ("NATION_FIELD_UNKNOWN_04");
	case NATION_SECTION_POS_UNKNOWN_05:
		return ("NATION_FIELD_UNKNOWN_05");
	case NATION_SECTION_POS_UNKNOWN_06:
		return ("NATION_FIELD_UNKNOWN_06");
	case NATION_SECTION_POS_UNKNOWN_07:
		return ("NATION_FIELD_UNKNOWN_07");
	case NATION_SECTION_POS_UNKNOWN_08:
		return ("NATION_FIELD_UNKNOWN_08");
	case NATION_SECTION_POS_UNKNOWN_09:
		return ("NATION_FIELD_UNKNOWN_09");
	case NATION_SECTION_POS_UNKNOWN_10:
		return ("NATION_FIELD_UNKNOWN_10");
	case NATION_SECTION_POS_UNKNOWN_11:
		return ("NATION_FIELD_UNKNOWN_11");
	case NATION_SECTION_POS_VEREINSANZAHL:
		return ("Vereinszahl");

	case NATION_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << NationSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromNationSectionPosType

void nation::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case NATION_SECTION_POS_LAND:
		this->Land = FieldValue;
		break;
	case NATION_SECTION_POS_UNKNOWN_02:
		this->NATION_FIELD_UNKNOWN_02 = FieldValue;
		break;
	case NATION_SECTION_POS_KUERZEL:
		this->Kuerzel = FieldValue;
		break;
	case NATION_SECTION_POS_UNKNOWN_04:
		this->NATION_FIELD_UNKNOWN_04 = FieldValue;
		break;
	case NATION_SECTION_POS_UNKNOWN_05:
		this->NATION_FIELD_UNKNOWN_05 = FieldValue;
		break;
	case NATION_SECTION_POS_UNKNOWN_06:
		this->NATION_FIELD_UNKNOWN_06 = FieldValue;
		break;
	case NATION_SECTION_POS_UNKNOWN_07:
		this->NATION_FIELD_UNKNOWN_07 = FieldValue;
		break;
	case NATION_SECTION_POS_UNKNOWN_08:
		this->NATION_FIELD_UNKNOWN_08 = FieldValue;
		break;
	case NATION_SECTION_POS_UNKNOWN_09:
		this->NATION_FIELD_UNKNOWN_09 = FieldValue;
		break;
	case NATION_SECTION_POS_UNKNOWN_10:
		this->NATION_FIELD_UNKNOWN_10 = FieldValue;
		break;
	case NATION_SECTION_POS_UNKNOWN_11:
		this->NATION_FIELD_UNKNOWN_11 = FieldValue;
		break;
	case NATION_SECTION_POS_VEREINSANZAHL:
		this->Vereinsanzahl = FieldValue;
		break;

			// Parent Section	
	case NATION_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void nation::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int NationPos = NATION_SECTION_POS_UNKNOWN + 1; NationPos < NO_OF_NATION_SECTION_POS_TYPES; NationPos++)
	{
		if (IncludeSectionPosIntoXml ((NATION_SECTION_POS_TYPE) NationPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromNationSectionPosType ((NATION_SECTION_POS_TYPE) NationPos), 			
				this->GetValueAtSectionPos(NationPos))));
		}
	}

} // PopulateValuePairVectorForExport

void nation::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& NationValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = NationValuePairs.begin(); 
		Iterator != NationValuePairs.end(); ++Iterator)
	{
		NATION_SECTION_POS_TYPE FieldPos = GetNationSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != NATION_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void nation::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = NATION_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_NATION_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((NATION_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void nation::IncrementVereinCount (int Increment)
{
#if DEBUG_ENABLED
std::cout << __FUNCTION__ << " - " << this->GetUniqueId() << " - INCREMENT_COUNT from " << this->GetValueAtSectionPos(NATION_SECTION_POS_VEREINSANZAHL) << std::endl;
#endif

	// Get the Value
	std::string VereinsZahl = this->GetValueAtSectionPos(NATION_SECTION_POS_VEREINSANZAHL);

	// Increment the Value
	VereinsZahl = T_IncrementStringNumber<int>(VereinsZahl, Increment);

	// Assign the new Value
	this->AssignField(NATION_SECTION_POS_VEREINSANZAHL, VereinsZahl);
} // IncrementVereinCount

std::string NationValueToNationString (const std::string& NationValue, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
#if DEBUG_ENABLED
	std::cout << __FUNCTION__ << "-> NationValue ::: " << NationValue << std::endl;
#endif

	std::string NationString = "";

	// Fields can be blank, so we can only convert if there is something, otherwise leave it blank
	if (NationValue.size() > 0)
	{
		int NationInt = T_StringToNumber<int>(NationValue);

		if (NationInt >= 0)
		{
			size_t NationIndex = NationInt;
			if (SectionList[SECTION_TYPE_NATION].size() >= NationIndex)
			{
				// Get Land ID at the Given Index
				NationString = std::static_pointer_cast<nation>(SectionList[SECTION_TYPE_NATION].at(NationIndex))->GetValueAtSectionPos(NATION_SECTION_POS_LAND);
			} // if have at least enough nations
			else
			{		
				std::stringstream ErrorText;
				ErrorText << "Only " << SectionList[SECTION_TYPE_NATION].size() << " Nations found, trying to access Nation " << NationIndex << " -> " << __FUNCTION__;
				programError (ErrorText.str());	
			}
		} // only allow positive indices
	} // if have a valid string
#if DEBUG_ENABLED
	else
	{
		std::cout << __FUNCTION__ << "::: Ignore, Input Size only " << NationValue.size() << std::endl;
	}
#endif

	return (NationString);
} // NationValueToNationString

std::string NationStringToNationValue (const std::string& NationString, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{	
#if DEBUG_ENABLED
	std::cout << __FUNCTION__ << "::: " << NationString << std::endl;
#endif

	std::string NationValue = "";
	// Fields can be blank, so we can only convert if there is something, otherwise leave it blank
	if (NationString.size() > 0)
	{
		bool NationFound = false;

		std::vector<std::shared_ptr<section>>::iterator NationIterator;
		std::vector<std::shared_ptr<section>> NationVector = SectionList [SECTION_TYPE_NATION];
		for (NationIterator = NationVector.begin(); (NationIterator != NationVector.end()) && (!NationFound); ++NationIterator)
		{
			if (std::static_pointer_cast<nation>(*NationIterator)->GetValueAtSectionPos(NATION_SECTION_POS_LAND).compare(NationString) == 0)
			{
				NationFound = true;
				// Get the value at the index
				NationValue = std::to_string(NationIterator - NationVector.begin());
			}
		} // for each nation

		if (!NationFound)
		{
			std::stringstream ErrorText;
			ErrorText << "No nation found with Value \"" << NationString << "\"" << __FUNCTION__ << std::endl;
			programError (ErrorText.str());	
		} // If not found Give an Error
	} // if there is something to look up

	return (NationValue);
} // NationStringToNationValue


static bool IncludeSectionPosIntoA3Db (NATION_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case NATION_SECTION_POS_LAND:
	case NATION_SECTION_POS_UNKNOWN_02:
	case NATION_SECTION_POS_KUERZEL:
	case NATION_SECTION_POS_UNKNOWN_04:
	case NATION_SECTION_POS_UNKNOWN_05:
	case NATION_SECTION_POS_UNKNOWN_06:
	case NATION_SECTION_POS_UNKNOWN_07:
	case NATION_SECTION_POS_UNKNOWN_08:
	case NATION_SECTION_POS_UNKNOWN_09:
	case NATION_SECTION_POS_UNKNOWN_10:
	case NATION_SECTION_POS_UNKNOWN_11:
			IncludeIntoA3Db = true;
		break;

		// Parent Section
	case NATION_SECTION_POS_PARENT_SECTION:
	case NATION_SECTION_POS_VEREINSANZAHL:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromNationSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (NATION_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case NATION_SECTION_POS_LAND:
	case NATION_SECTION_POS_UNKNOWN_02:
	case NATION_SECTION_POS_KUERZEL:
	case NATION_SECTION_POS_UNKNOWN_04:
	case NATION_SECTION_POS_UNKNOWN_05:
	case NATION_SECTION_POS_UNKNOWN_06:
	case NATION_SECTION_POS_UNKNOWN_07:
	case NATION_SECTION_POS_UNKNOWN_08:
	case NATION_SECTION_POS_UNKNOWN_09:
	case NATION_SECTION_POS_UNKNOWN_10:
	case NATION_SECTION_POS_UNKNOWN_11:
	case NATION_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;
		
	case NATION_SECTION_POS_VEREINSANZAHL:
		IncludeIntoXml = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromNationSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static NATION_SECTION_POS_TYPE GetNationSectionPosTypeFromString (const std::string& TypeString)
{
	NATION_SECTION_POS_TYPE FoundPos = NATION_SECTION_POS_UNKNOWN;

	for (int TempPos = NATION_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_NATION_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromNationSectionPosType ((NATION_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (NATION_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetNationSectionPosTypeFromString

void AssignNationField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<nation>(SectionList, SectionLineCount, Line);
} // AssignNationField

std::string GetNationCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = NATION_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_NATION_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromNationSectionPosType ((NATION_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetNationCsvHeader
