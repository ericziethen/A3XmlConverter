#include "schiri.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

schiri::schiri(void)
{
}

schiri::~schiri(void)
{
}

std::string schiri::GetUniqueId ()
{
	return(this->Vornahme + this->Nachnahme);
} // GetUniqueId

SECTION_TYPE schiri::GetSectionType ()
{
	return(SECTION_TYPE_SCHIRI);
} // GetSectionType

std::string schiri::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case SCHIRI_SECTION_POS_VORNAHME:
		return (this->Vornahme);
	case SCHIRI_SECTION_POS_NACHNAHME:
		return (this->Nachnahme);
	case SCHIRI_SECTION_POS_KOMPETENZ:
		return (this->Kompetenz);
	case SCHIRI_SECTION_POS_HAERTE:
		return (this->Haerte);
	case SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN:
		return (this->UnbeliebterVerein);
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		return (this->Schiedsrichtereigenschaften);
	case SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN_EXPANDED:
		return (this->UnbeliebterVerein_Expanded);

			// Parent Section
	case SCHIRI_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

		// Split Bitmask Fields 
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER:
		return (this->Schiedsrichtereigenschaften_Split_Bitmask_HeimSchiedsrichter);
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER:
		return (this->Schiedsrichtereigenschaften_Split_Bitmask_GastSchiedsrichter);
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN:
		return (this->Schiedsrichtereigenschaften_Split_Bitmask_HasstMeckern);
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL:
		return (this->Schiedsrichtereigenschaften_Split_Bitmask_HasstZeitspiel);
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING:
		return (this->Schiedsrichtereigenschaften_Split_Bitmask_HasstCoaching);

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromSchiriSectionPosType (const SCHIRI_SECTION_POS_TYPE SchiriSectionPosType)
{
	switch (SchiriSectionPosType)
	{
	case SCHIRI_SECTION_POS_VORNAHME:
		return ("Vornahme");
	case SCHIRI_SECTION_POS_NACHNAHME:
		return ("Nachnahme");
	case SCHIRI_SECTION_POS_KOMPETENZ:
		return ("Kompetenz");
	case SCHIRI_SECTION_POS_HAERTE:
		return ("Haerte");
	case SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN:
		return ("UnbeliebterVerein_UNEXPANDED");
	case SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN_EXPANDED:
		return ("UnbeliebterVerein");
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		return ("Schiedsrichtereigenschaften_UNSPLIT_BITMASK");

	case SCHIRI_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	// Split Bitmask Fields	
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER:
		return("Heimschiedsrichter");
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER:
		return("Gastschiedsrichter");
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN:
		return("HasstMeckern");
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL:
		return("HasstZeitspiel");
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING:
		return("HasstCoaching");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << SchiriSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromSchiriSectionPosType

void schiri::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case SCHIRI_SECTION_POS_VORNAHME:
		this->Vornahme = FieldValue;
		break;
	case SCHIRI_SECTION_POS_NACHNAHME:
		this->Nachnahme = FieldValue;
		break;
	case SCHIRI_SECTION_POS_KOMPETENZ:
		this->Kompetenz = FieldValue;
		break;
	case SCHIRI_SECTION_POS_HAERTE:
		this->Haerte = FieldValue;
		break;
	case SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN:
		this->UnbeliebterVerein = FieldValue;
		break;
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		this->Schiedsrichtereigenschaften = FieldValue;
		break;
	case SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN_EXPANDED:
		this->UnbeliebterVerein_Expanded = FieldValue;
		break;

	// Parent Section	
	case SCHIRI_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

	// Split Bismark Fields
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER:
		this->Schiedsrichtereigenschaften_Split_Bitmask_HeimSchiedsrichter = FieldValue;
		break;
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER:
		this->Schiedsrichtereigenschaften_Split_Bitmask_GastSchiedsrichter = FieldValue;
		break;
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN:
		this->Schiedsrichtereigenschaften_Split_Bitmask_HasstMeckern = FieldValue;
		break;
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL:
		this->Schiedsrichtereigenschaften_Split_Bitmask_HasstZeitspiel = FieldValue;
		break;
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING:
		this->Schiedsrichtereigenschaften_Split_Bitmask_HasstCoaching = FieldValue;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void schiri::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int SchiriPos = SCHIRI_SECTION_POS_UNKNOWN + 1; SchiriPos < NO_OF_SCHIRI_SECTION_POS_TYPES; SchiriPos++)
	{
		if (IncludeSectionPosIntoXml ((SCHIRI_SECTION_POS_TYPE) SchiriPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromSchiriSectionPosType ((SCHIRI_SECTION_POS_TYPE) SchiriPos), 			
				this->GetValueAtSectionPos(SchiriPos))));
		}
	}

} // PopulateValuePairVectorForExport

void schiri::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& SchiriValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = SchiriValuePairs.begin(); 
		Iterator != SchiriValuePairs.end(); ++Iterator)
	{
		SCHIRI_SECTION_POS_TYPE FieldPos = GetSchiriSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != SCHIRI_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void schiri::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = SCHIRI_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_SCHIRI_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((SCHIRI_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void schiri::DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Unbeliebter Verein Field
	this->ConvertVereinField(SECTION_EXPANSION_FROM_A3DB_VEREIN, SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN, 
								SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN_EXPANDED, this->GetA3FileLandId(), SectionList);
} // DecodeFieldsFromA3Db

void schiri::EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE ReferenceType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	switch (ReferenceType)
	{
	case FIELD_REFERENCE_LAND:
		break;

	case FIELD_REFERENCE_VEREIN:
		this->ConvertVereinField(SECTION_EXPANSION_TO_A3DB_VEREIN, SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN_EXPANDED, 
			SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN, this->GetA3FileLandId(), SectionList);
		break;

	default:
		break;
	} // switch reference types
} // EncodeFieldsToA3Db

void schiri::SplitBitmaskFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	ENUM_VALUE_LIST BitmaskFields;

	// Split Eigenschaften und Heim/Gast Field
	this->SplitBitmaskField (SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN, 
		GetEnumValueList(SCHIRI_ENUM_EIGENSCHAFTEN_UND_HEIM_GAST, BitmaskFields));

} // SplitBitmaskFields

void schiri::MergeBitmaskFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	ENUM_VALUE_LIST BitmaskFields;

	// Merge Eigenschaften
	this->MergeBitmaskField (SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN, 
		GetEnumValueList(SCHIRI_ENUM_EIGENSCHAFTEN_UND_HEIM_GAST, BitmaskFields));

} // MergeBitmaskFields

void schiri::DecodeBooleansFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Boolean HeimSchiedsrichter
	this->DecodeBooleanFromA3Db(SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER);

	// Decode Boolean Auswaertsschidsrichter
	this->DecodeBooleanFromA3Db(SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER);

	// Decode Boolean Hasst Meckern
	this->DecodeBooleanFromA3Db(SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN);

	// Decode Boolean Hasst Coaching
	this->DecodeBooleanFromA3Db(SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING);

	// Decode Boolean Hasst Zeitspiel
	this->DecodeBooleanFromA3Db(SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL);

} // DecodeBooleansFromA3Db

void schiri::EncodeBooleansToA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Encode Boolean HeimSchiedsrichter
	this->EncodeBooleanToA3Db(SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER, 
		GetValueFromSchiriBooleanType(SCHIRI_BOOLEAN_HEIMSCHIEDSRICHTER));

	// Encode Boolean Auswaertsschidsrichter
	this->EncodeBooleanToA3Db(SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER, 
		GetValueFromSchiriBooleanType(SCHIRI_BOOLEAN_GASTSCHIEDSRICHTER));

	// Encode Boolean  Hasst Meckern
	this->EncodeBooleanToA3Db(SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN, 
		GetValueFromSchiriBooleanType(SCHIRI_BOOLEAN_HASST_MECKERN));

	// v Boolean Hasst Coaching
	this->EncodeBooleanToA3Db(SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING, 
		GetValueFromSchiriBooleanType(SCHIRI_BOOLEAN_HASST_COACHING));

	// Encode Boolean Hasst Zeitspiel
	this->EncodeBooleanToA3Db(SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL, 
		GetValueFromSchiriBooleanType(SCHIRI_BOOLEAN_HASST_ZEITSPIEL));

} // EncodeBooleansToA3Db

void schiri::GetGenericSplitFieldsForField (int SchiriSectionPos, std::vector<int>& SplitFields)
{
	switch ((SCHIRI_SECTION_POS_TYPE) SchiriSectionPos)
	{

	// No Generic Split Fields but Bitmask
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SchiriSectionPos << "-" << 
			GetNameFromSchiriSectionPosType((SCHIRI_SECTION_POS_TYPE) SchiriSectionPos) << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}
} // GetGenericSplitFieldsForField

bool schiri::GetBooleanTargetFieldForEnumVal (const int SpielerSplitSectionPos, const int EnumPos, int& BooleanTargetField)
{
	bool FieldFound = false;
	BooleanTargetField = SCHIRI_SECTION_POS_UNKNOWN;

	switch ((SCHIRI_SECTION_POS_TYPE) SpielerSplitSectionPos)
	{
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		switch ((SCHIRI_EIGENSCHAFTEN_TYPE) EnumPos)
		{
		case SCHIRI_EIGENSCHAFTEN_HEIMSCHIEDSRICHTER:
			BooleanTargetField = SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER;
			break;

		case SCHIRI_EIGENSCHAFTEN_GASTSCHIEDSRICHTER:
			BooleanTargetField = SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER;
			break;

		case SCHIRI_EIGENSCHAFTEN_HASST_MECKERN:
			BooleanTargetField = SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN;
			break;

		case SCHIRI_EIGENSCHAFTEN_HASST_ZEITSPIEL:
			BooleanTargetField = SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL;
			break;

		case SCHIRI_EIGENSCHAFTEN_HASST_COACHING:
			BooleanTargetField = SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING;
			break;

		default:
			std::stringstream ErrorText;
			ErrorText << "Unexpected " << EnumPos << " (" << 
				GetNameFromSchiriEigenschaftenType((SCHIRI_EIGENSCHAFTEN_TYPE) EnumPos) << ") -> " <<__FUNCTION__;
			programError (ErrorText.str());	
		} // switch spieler field bart type
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SpielerSplitSectionPos << " (" << 
			GetNameFromSchiriSectionPosType((SCHIRI_SECTION_POS_TYPE) SpielerSplitSectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	} // switch spieler split section pos
	
	if (BooleanTargetField != SCHIRI_SECTION_POS_UNKNOWN)
		FieldFound = true;

	return(FieldFound);
} // GetBooleanTargetFieldForEnumVal

static bool IncludeSectionPosIntoA3Db (SCHIRI_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case SCHIRI_SECTION_POS_VORNAHME:
	case SCHIRI_SECTION_POS_NACHNAHME:
	case SCHIRI_SECTION_POS_KOMPETENZ:
	case SCHIRI_SECTION_POS_HAERTE:
	case SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN:
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case SCHIRI_SECTION_POS_PARENT_SECTION:
	case SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN_EXPANDED:
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER:
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER:
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN:
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL:
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromSchiriSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (SCHIRI_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case SCHIRI_SECTION_POS_VORNAHME:
	case SCHIRI_SECTION_POS_NACHNAHME:
	case SCHIRI_SECTION_POS_KOMPETENZ:
	case SCHIRI_SECTION_POS_HAERTE:
	case SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN_EXPANDED:
	case SCHIRI_SECTION_POS_PARENT_SECTION:
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER:
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER:
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN:
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL:
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING:
		IncludeIntoXml = true;
		break;
		
	case SCHIRI_SECTION_POS_UNBELIEBTER_VEREIN:
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		IncludeIntoXml = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromSchiriSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static SCHIRI_SECTION_POS_TYPE GetSchiriSectionPosTypeFromString (const std::string& TypeString)
{
	SCHIRI_SECTION_POS_TYPE FoundPos = SCHIRI_SECTION_POS_UNKNOWN;

	for (int TempPos = SCHIRI_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_SCHIRI_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromSchiriSectionPosType ((SCHIRI_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (SCHIRI_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetSchiriSectionPosTypeFromString

void AssignSchiriField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<schiri>(SectionList, SectionLineCount, Line);
} // AssignSchiriField

std::string GetSchiriCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = SCHIRI_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_SCHIRI_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromSchiriSectionPosType ((SCHIRI_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetSchiriCsvHeader

SCHIRI_BOOLEAN_TYPE GetSchiriBooleanTypeFromPosition (SCHIRI_SECTION_POS_TYPE SectionPos)
{
	SCHIRI_BOOLEAN_TYPE BooleanType = SCHIRI_BOOLEAN_UNKNOWN;
	switch (SectionPos)
	{		
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER: 
		BooleanType = SCHIRI_BOOLEAN_GASTSCHIEDSRICHTER;
		break;
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING: 
		BooleanType = SCHIRI_BOOLEAN_HASST_COACHING;
		break;
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN: 
		BooleanType = SCHIRI_BOOLEAN_HASST_MECKERN;
		break;
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL: 
		BooleanType = SCHIRI_BOOLEAN_HASST_ZEITSPIEL;
		break;
	case SCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER: 
		BooleanType = SCHIRI_BOOLEAN_HEIMSCHIEDSRICHTER;
		break;

	default:
		//do nothing
		break;
	} // switch section pos

	return (BooleanType);
} // GetSchiriBooleanTypeFromPosition

void GetSchiriAllowedValues (std::vector<FIELD_VALUE_STRUCT>& AllowedValues)
{
	for (int SectionPos = SCHIRI_SECTION_POS_UNKNOWN + 1; SectionPos < NO_OF_SCHIRI_SECTION_POS_TYPES; SectionPos++)
	{
		ENUM_FUNC EnumFunc = nullptr;
		int EnumLow = 0;
		int EnumHigh = 0;
		SCHIRI_BOOLEAN_TYPE SchiriBoolean = SCHIRI_BOOLEAN_UNKNOWN;
		bool DetailsFound = false;

		// No Enums
		if ((SchiriBoolean = GetSchiriBooleanTypeFromPosition ((SCHIRI_SECTION_POS_TYPE) SectionPos)) != SCHIRI_BOOLEAN_UNKNOWN)
		{
			GetBooleanEnumDetails (EnumFunc, EnumLow, EnumHigh);
			DetailsFound = true;
		} // if boolean field

		// Add Values
		if (DetailsFound)
		{
			// Add the Value Entry to the List
			AddFieldValueEntryToList (AllowedValues, GetNameFromSchiriSectionPosType((SCHIRI_SECTION_POS_TYPE) SectionPos));

			// Add allowed Values
			AddFieldValuesForLastEntry (AllowedValues, EnumLow, EnumHigh, EnumFunc);
		} // if got a function
	} // for each section pos
} // GetSchiriAllowedValues
