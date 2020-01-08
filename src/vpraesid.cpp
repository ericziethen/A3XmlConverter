#include "vpraesid.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

vpraesid::vpraesid(void)
{
}

vpraesid::~vpraesid(void)
{
}

std::string vpraesid::GetUniqueId ()
{
	return(this->Vornahme + this->Nachnahme);
} // GetUniqueId

SECTION_TYPE vpraesid::GetSectionType ()
{
	return(SECTION_TYPE_VPRAESID);
} // GetSectionType

std::string vpraesid::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case VPRAESID_SECTION_POS_VORNAHME:
		return (this->Vornahme);
	case VPRAESID_SECTION_POS_NACHNAHME:
		return (this->Nachnahme);
	case VPRAESID_SECTION_POS_GEBURTSDATUM:
		return (this->Geburtsdatum);

			// Parent Section
	case VPRAESID_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromVpraesidSectionPosType (const VPRAESID_SECTION_POS_TYPE VpraesidSectionPosType)
{
	switch (VpraesidSectionPosType)
	{
	case VPRAESID_SECTION_POS_VORNAHME:
		return ("Vornahme");
	case VPRAESID_SECTION_POS_NACHNAHME:
		return ("Nachnahme");
	case VPRAESID_SECTION_POS_GEBURTSDATUM:
		return ("Geburtsdatum");

	case VPRAESID_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << VpraesidSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromVpraesidSectionPosType

void vpraesid::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case VPRAESID_SECTION_POS_VORNAHME:
		this->Vornahme = FieldValue;
		break;
	case VPRAESID_SECTION_POS_NACHNAHME:
		this->Nachnahme = FieldValue;
		break;
	case VPRAESID_SECTION_POS_GEBURTSDATUM:
		this->Geburtsdatum = FieldValue;
		break;

	// Parent Section	
	case VPRAESID_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void vpraesid::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int VpraesidPos = VPRAESID_SECTION_POS_UNKNOWN + 1; VpraesidPos < NO_OF_VPRAESID_SECTION_POS_TYPES; VpraesidPos++)
	{
		if (IncludeSectionPosIntoXml ((VPRAESID_SECTION_POS_TYPE) VpraesidPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromVpraesidSectionPosType ((VPRAESID_SECTION_POS_TYPE) VpraesidPos), 			
				this->GetValueAtSectionPos(VpraesidPos))));
		}
	}
} // PopulateValuePairVectorForExport

void vpraesid::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& VpraesidValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = VpraesidValuePairs.begin(); 
		Iterator != VpraesidValuePairs.end(); ++Iterator)
	{
		VPRAESID_SECTION_POS_TYPE FieldPos = GetVpraesidSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != VPRAESID_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void vpraesid::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = VPRAESID_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_VPRAESID_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((VPRAESID_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

static bool IncludeSectionPosIntoA3Db (VPRAESID_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case VPRAESID_SECTION_POS_VORNAHME:
	case VPRAESID_SECTION_POS_NACHNAHME:
	case VPRAESID_SECTION_POS_GEBURTSDATUM:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case VPRAESID_SECTION_POS_PARENT_SECTION:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromVpraesidSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (VPRAESID_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case VPRAESID_SECTION_POS_VORNAHME:
	case VPRAESID_SECTION_POS_NACHNAHME:
	case VPRAESID_SECTION_POS_GEBURTSDATUM:
	case VPRAESID_SECTION_POS_PARENT_SECTION:
		IncludeIntoXml = true;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromVpraesidSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static VPRAESID_SECTION_POS_TYPE GetVpraesidSectionPosTypeFromString (const std::string& TypeString)
{
	VPRAESID_SECTION_POS_TYPE FoundPos = VPRAESID_SECTION_POS_UNKNOWN;

	for (int TempPos = VPRAESID_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_VPRAESID_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromVpraesidSectionPosType ((VPRAESID_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (VPRAESID_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetVpraesidSectionPosTypeFromString

void AssignVpraesidField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<vpraesid>(SectionList, SectionLineCount, Line);
} // AssignVpraesidField

std::string GetVpraesidCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = VPRAESID_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_VPRAESID_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromVpraesidSectionPosType ((VPRAESID_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetVpraesidCsvHeader
