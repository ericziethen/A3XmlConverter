#include "land.h"

#include "error_handling.h"
#include "a3_db_file_lib.h"
#include <sstream>

land::land(void)
{
	this->LandId = BLANK_LAND_ID;
}


land::~land(void)
{
}

std::string land::GetUniqueId ()
{
	return(this->LandId);
} // GetUniqueId

SECTION_TYPE land::GetSectionType ()
{
	return(SECTION_TYPE_LAND);
} // GetSectionType

std::string land::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case LAND_SECTION_POS_POKALWETTBEWERB:
		return (this->Pokalwettbewerb);
	case LAND_SECTION_POS_UNKNOWN_02:
		return (this->LAND_FIELD_UNKNOWN_02);
	case LAND_SECTION_POS_VEREINSZAHL:
		return (this->VereinsZahl);
	case LAND_SECTION_POS_UNKNOWN_04:
		return (this->LAND_FIELD_UNKNOWN_04);
	case LAND_SECTION_POS_UNKNOWN_05:
		return (this->LAND_FIELD_UNKNOWN_05);
	case LAND_SECTION_POS_UNKNOWN_06:
		return (this->LAND_FIELD_UNKNOWN_06);
	case LAND_SECTION_POS_LAND_ID:
		return (this->LandId);

	case LAND_SECTION_POS_LAND_ID_EXPANDED:
		return(this->LandId_Expanded);

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromLandSectionPosType (const LAND_SECTION_POS_TYPE LandSectionPosType)
{
	switch (LandSectionPosType)
	{
	case LAND_SECTION_POS_UNKNOWN:
		return ("LAND_FIELD_UNKNOWN");
	case LAND_SECTION_POS_POKALWETTBEWERB:
		return ("Pokalwettbewerb");
	case LAND_SECTION_POS_UNKNOWN_02:
		return ("LAND_FIELD_UNKNOWN_02");
	case LAND_SECTION_POS_VEREINSZAHL:
		return ("VereinsZahl");
	case LAND_SECTION_POS_UNKNOWN_04:
		return ("LAND_FIELD_UNKNOWN_04");
	case LAND_SECTION_POS_UNKNOWN_05:
		return ("LAND_FIELD_UNKNOWN_05");
	case LAND_SECTION_POS_UNKNOWN_06:
		return ("LAND_FIELD_UNKNOWN_06");
	case LAND_SECTION_POS_LAND_ID:
		return("Land_UNEXPANDED");

	case LAND_SECTION_POS_LAND_ID_EXPANDED:
		return("Land");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << LandSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromLandSectionPosType

void land::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case LAND_SECTION_POS_POKALWETTBEWERB:
		this->Pokalwettbewerb = FieldValue;
		break;
	case LAND_SECTION_POS_UNKNOWN_02:
		this->LAND_FIELD_UNKNOWN_02 = FieldValue;
		break;
	case LAND_SECTION_POS_VEREINSZAHL:
		this->VereinsZahl = FieldValue;
		break;
	case LAND_SECTION_POS_UNKNOWN_04:
		this->LAND_FIELD_UNKNOWN_04 = FieldValue;
		break;
	case LAND_SECTION_POS_UNKNOWN_05:
		this->LAND_FIELD_UNKNOWN_05 = FieldValue;
		break;
	case LAND_SECTION_POS_UNKNOWN_06:
		this->LAND_FIELD_UNKNOWN_06 = FieldValue;
		break;
	case LAND_SECTION_POS_LAND_ID:
		this->LandId = FieldValue;
		break;

	case LAND_SECTION_POS_LAND_ID_EXPANDED:
		this->LandId_Expanded = FieldValue;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void land::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int LandPos = LAND_SECTION_POS_UNKNOWN + 1; LandPos < NO_OF_LAND_SECTION_POS_TYPES; LandPos++)
	{
		if (IncludeSectionPosIntoXml ((LAND_SECTION_POS_TYPE) LandPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromLandSectionPosType ((LAND_SECTION_POS_TYPE) LandPos), 			
				this->GetValueAtSectionPos(LandPos))));
		}
	}

} // PopulateValuePairVectorForExport

void land::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& LandValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = LandValuePairs.begin(); 
		Iterator != LandValuePairs.end(); ++Iterator)
	{
		LAND_SECTION_POS_TYPE FieldPos = GetLandSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != LAND_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void land::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	A3_FILE_GROUP_TYPE FileGroupType = GetA3FileGroupFromFileName(FileName);

	// Only Populate list for Land Files
	if(FileGroupType == A3_FILE_GROUP_LANDXXX)
	{
		for (int TempPos = LAND_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_LAND_SECTION_POS_TYPES; TempPos++)
		{
			if (IncludeSectionPosIntoA3Db((LAND_SECTION_POS_TYPE) TempPos))
			{
				A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
			} // If include in A3Db
		} // for each position
	} // If land file
} // AddFieldsToA3DbList

bool land::UpdateLandIdIfNeeded (std::string LandId)
{
	bool Updated = false;

	// update land id if still blank
	if(GetValueAtSectionPos(LAND_SECTION_POS_LAND_ID).compare(BLANK_LAND_ID) == 0)
	{
		AssignField(LAND_SECTION_POS_LAND_ID, LandId);
		Updated = true;
	}

	return(Updated);
} // UpdateLandIdIfNeeded
void land::DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Land Field
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, LAND_SECTION_POS_LAND_ID, LAND_SECTION_POS_LAND_ID_EXPANDED, SectionList);

} // DecodeFieldsFromA3Db

void land::EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE ReferenceType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	switch (ReferenceType)
	{
	case FIELD_REFERENCE_LAND:
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, LAND_SECTION_POS_LAND_ID_EXPANDED, LAND_SECTION_POS_LAND_ID, SectionList);
		break;

	case FIELD_REFERENCE_VEREIN:
		break;

	default:
		break;
	} // switch reference types
} // EncodeFieldsToA3Db 

static bool IncludeSectionPosIntoA3Db (LAND_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{		
	case LAND_SECTION_POS_POKALWETTBEWERB:
	case LAND_SECTION_POS_UNKNOWN_02:
	case LAND_SECTION_POS_VEREINSZAHL:
	case LAND_SECTION_POS_UNKNOWN_04:
	case LAND_SECTION_POS_UNKNOWN_05:
	case LAND_SECTION_POS_UNKNOWN_06:
		IncludeIntoA3Db = true;
	break;

	case LAND_SECTION_POS_LAND_ID:
	case LAND_SECTION_POS_LAND_ID_EXPANDED:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromLandSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (LAND_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case LAND_SECTION_POS_POKALWETTBEWERB:
	case LAND_SECTION_POS_UNKNOWN_02:
	case LAND_SECTION_POS_UNKNOWN_04:
	case LAND_SECTION_POS_UNKNOWN_05:
	case LAND_SECTION_POS_UNKNOWN_06:
	case LAND_SECTION_POS_LAND_ID_EXPANDED:
		IncludeIntoXml = true;
		break;

	case LAND_SECTION_POS_VEREINSZAHL:
	case LAND_SECTION_POS_LAND_ID:
		IncludeIntoXml = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromLandSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static LAND_SECTION_POS_TYPE GetLandSectionPosTypeFromString (const std::string& TypeString)
{
	LAND_SECTION_POS_TYPE FoundPos = LAND_SECTION_POS_UNKNOWN;

	for (int TempPos = LAND_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_LAND_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromLandSectionPosType ((LAND_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (LAND_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetLandSectionPosTypeFromString

void AssignLandField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<land>(SectionList, SectionLineCount, Line);
} // AssignLandField

std::string GetLandCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = LAND_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_LAND_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromLandSectionPosType ((LAND_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetLandCsvHeader

void AssignVereinCountsForLand (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator LandIterator;
	std::vector<std::shared_ptr<section>> LandVector = SectionList [SECTION_TYPE_LAND];
	for(LandIterator = LandVector.begin(); LandIterator != LandVector.end(); ++LandIterator)
	{
		int VereinCount = 0;
		VereinCount = (*LandIterator)->GetMatchingSectionsFromList (SectionList[SECTION_TYPE_VEREIN]);

		// Set Verein Count
		std::static_pointer_cast<land>(SectionList[SECTION_TYPE_LAND].back())->AssignField(
			LAND_SECTION_POS_VEREINSZAHL, std::to_string(VereinCount));
	} // for each land in db
} // AssignVereinCountsForLand