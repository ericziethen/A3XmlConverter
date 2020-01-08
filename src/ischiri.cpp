#include "ischiri.h"

#include "error_handling.h"
#include "schiri_enum.h"
#include <sstream>
#include <iostream>

ischiri::ischiri(void)
{
}

ischiri::~ischiri(void)
{
}

std::string ischiri::GetUniqueId ()
{
	return(this->Nachnahme + this->Vornahme);
} // GetUniqueId

SECTION_TYPE ischiri::GetSectionType ()
{
	return(SECTION_TYPE_ISCHIRI);
} // GetSectionType

std::string ischiri::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case ISCHIRI_SECTION_POS_NACHNAHME:
		return (this->Nachnahme);
	case ISCHIRI_SECTION_POS_VORNAHME:
		return (this->Vornahme);
	case ISCHIRI_SECTION_POS_KOMPETENZ:
		return (this->Kompetenz);
	case ISCHIRI_SECTION_POS_HAERTE:
		return (this->Haerte);
	case ISCHIRI_SECTION_POS_NATIONALITAET:
		return (this->Nationalitaet);
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		return (this->Schiedsrichtereigenschaften);

			// Parent Section
	case ISCHIRI_SECTION_POS_PARENT_SECTION:
		return (this->GetParentId());	

		// Split Bitmask Fields 
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER:
		return (this->Schiedsrichtereigenschaften_Split_Bitmask_HeimSchiedsrichter);
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER:
		return (this->Schiedsrichtereigenschaften_Split_Bitmask_GastSchiedsrichter);
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN:
		return (this->Schiedsrichtereigenschaften_Split_Bitmask_HasstMeckern);
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL:
		return (this->Schiedsrichtereigenschaften_Split_Bitmask_HasstZeitspiel);
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING:
		return (this->Schiedsrichtereigenschaften_Split_Bitmask_HasstCoaching);

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromISchiriSectionPosType (const ISCHIRI_SECTION_POS_TYPE ISchiriSectionPosType)
{
	switch (ISchiriSectionPosType)
	{
	case ISCHIRI_SECTION_POS_NACHNAHME:
		return ("Nachnahme");
	case ISCHIRI_SECTION_POS_VORNAHME:
		return ("Vornahme");
	case ISCHIRI_SECTION_POS_KOMPETENZ:
		return ("Kompetenz");
	case ISCHIRI_SECTION_POS_HAERTE:
		return ("Haerte");
	case ISCHIRI_SECTION_POS_NATIONALITAET:
		return ("Nationalitaet");
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		return ("Schiedsrichtereigenschaften");

	case ISCHIRI_SECTION_POS_PARENT_SECTION:
		return (XML_PARENT_SECTION_STRING);	

		// Split Bitmask Fields	
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER:
		return("Heimschiedsrichter");
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER:
		return("Gastschiedsrichter");
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN:
		return("HasstMeckern");
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL:
		return("HasstZeitspiel");
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING:
		return("HasstCoaching");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << ISchiriSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromISchiriSectionPosType

void ischiri::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case ISCHIRI_SECTION_POS_NACHNAHME:
		this->Nachnahme = FieldValue;
		break;
	case ISCHIRI_SECTION_POS_VORNAHME:
		this->Vornahme = FieldValue;
		break;
	case ISCHIRI_SECTION_POS_KOMPETENZ:
		this->Kompetenz = FieldValue;
		break;
	case ISCHIRI_SECTION_POS_HAERTE:
		this->Haerte = FieldValue;
		break;
	case ISCHIRI_SECTION_POS_NATIONALITAET:
		this->Nationalitaet = FieldValue;
		break;
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		this->Schiedsrichtereigenschaften = FieldValue;
		break;

			// Parent Section	
	case ISCHIRI_SECTION_POS_PARENT_SECTION:
		this->SetParentId(FieldValue);
		break;

		// Split Bismark Fields
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER:
		this->Schiedsrichtereigenschaften_Split_Bitmask_HeimSchiedsrichter = FieldValue;
		break;
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER:
		this->Schiedsrichtereigenschaften_Split_Bitmask_GastSchiedsrichter = FieldValue;
		break;
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN:
		this->Schiedsrichtereigenschaften_Split_Bitmask_HasstMeckern = FieldValue;
		break;
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL:
		this->Schiedsrichtereigenschaften_Split_Bitmask_HasstZeitspiel = FieldValue;
		break;
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING:
		this->Schiedsrichtereigenschaften_Split_Bitmask_HasstCoaching = FieldValue;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void ischiri::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int ISchiriPos = ISCHIRI_SECTION_POS_UNKNOWN + 1; ISchiriPos < NO_OF_ISCHIRI_SECTION_POS_TYPES; ISchiriPos++)
	{
		if (IncludeSectionPosIntoXml ((ISCHIRI_SECTION_POS_TYPE) ISchiriPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromISchiriSectionPosType ((ISCHIRI_SECTION_POS_TYPE) ISchiriPos), 			
				this->GetValueAtSectionPos(ISchiriPos))));
		}
	}

} // PopulateValuePairVectorForExport

void ischiri::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& ISchiriValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = ISchiriValuePairs.begin(); 
		Iterator != ISchiriValuePairs.end(); ++Iterator)
	{
		ISCHIRI_SECTION_POS_TYPE FieldPos = GetISchiriSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != ISCHIRI_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void ischiri::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = ISCHIRI_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_ISCHIRI_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((ISCHIRI_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void ischiri::SplitBitmaskFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	ENUM_VALUE_LIST BitmaskFields;

	// Split Eigenschaften und Heim/Gast Field
	this->SplitBitmaskField (ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN, 
		GetEnumValueList(SCHIRI_ENUM_EIGENSCHAFTEN_UND_HEIM_GAST, BitmaskFields));

} // SplitBitmaskFields

void ischiri::MergeBitmaskFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	ENUM_VALUE_LIST BitmaskFields;

	// Merge Eigenschaften
	this->MergeBitmaskField (ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN, 
		GetEnumValueList(SCHIRI_ENUM_EIGENSCHAFTEN_UND_HEIM_GAST, BitmaskFields));

} // MergeBitmaskFields

void ischiri::DecodeBooleansFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Boolean HeimSchiedsrichter
	this->DecodeBooleanFromA3Db(ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER);

	// Decode Boolean Auswaertsschidsrichter
	this->DecodeBooleanFromA3Db(ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER);

	// Decode Boolean Hasst Meckern
	this->DecodeBooleanFromA3Db(ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN);

	// Decode Boolean Hasst Coaching
	this->DecodeBooleanFromA3Db(ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING);

	// Decode Boolean Hasst Zeitspiel
	this->DecodeBooleanFromA3Db(ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL);

} // DecodeBooleansFromA3Db

void ischiri::EncodeBooleansToA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Encode Boolean HeimSchiedsrichter
	this->EncodeBooleanToA3Db(ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER, 
		GetValueFromSchiriBooleanType(SCHIRI_BOOLEAN_HEIMSCHIEDSRICHTER));

	// Encode Boolean Auswaertsschidsrichter
	this->EncodeBooleanToA3Db(ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER, 
		GetValueFromSchiriBooleanType(SCHIRI_BOOLEAN_GASTSCHIEDSRICHTER));

	// Encode Boolean  Hasst Meckern
	this->EncodeBooleanToA3Db(ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN, 
		GetValueFromSchiriBooleanType(SCHIRI_BOOLEAN_HASST_MECKERN));

	// Encode Boolean Hasst Coaching
	this->EncodeBooleanToA3Db(ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING, 
		GetValueFromSchiriBooleanType(SCHIRI_BOOLEAN_HASST_COACHING));

	// Encode Boolean Hasst Zeitspiel
	this->EncodeBooleanToA3Db(ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL, 
		GetValueFromSchiriBooleanType(SCHIRI_BOOLEAN_HASST_ZEITSPIEL));

} // EncodeBooleansToA3Db

void ischiri::GetGenericSplitFieldsForField (int SchiriSectionPos, std::vector<int>& SplitFields)
{
	switch ((ISCHIRI_SECTION_POS_TYPE) SchiriSectionPos)
	{
		// No Generic Split Fields but Bitmask
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SchiriSectionPos << "-" << 
			GetNameFromISchiriSectionPosType((ISCHIRI_SECTION_POS_TYPE) SchiriSectionPos) << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}
} // GetGenericSplitFieldsForField

bool ischiri::GetBooleanTargetFieldForEnumVal (const int SpielerSplitSectionPos, const int EnumPos, int& BooleanTargetField)
{
	bool FieldFound = false;
	BooleanTargetField = ISCHIRI_SECTION_POS_UNKNOWN;

	switch ((ISCHIRI_SECTION_POS_TYPE) SpielerSplitSectionPos)
	{
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		switch ((SCHIRI_EIGENSCHAFTEN_TYPE) EnumPos)
		{
		case SCHIRI_EIGENSCHAFTEN_HEIMSCHIEDSRICHTER:
			BooleanTargetField = ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER;
			break;

		case SCHIRI_EIGENSCHAFTEN_GASTSCHIEDSRICHTER:
			BooleanTargetField = ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER;
			break;

		case SCHIRI_EIGENSCHAFTEN_HASST_MECKERN:
			BooleanTargetField = ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN;
			break;

		case SCHIRI_EIGENSCHAFTEN_HASST_ZEITSPIEL:
			BooleanTargetField = ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL;
			break;

		case SCHIRI_EIGENSCHAFTEN_HASST_COACHING:
			BooleanTargetField = ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING;
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
			GetNameFromISchiriSectionPosType((ISCHIRI_SECTION_POS_TYPE) SpielerSplitSectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	} // switch spieler split section pos

	if (BooleanTargetField != ISCHIRI_SECTION_POS_UNKNOWN)
		FieldFound = true;

	return(FieldFound);
} // GetBooleanTargetFieldForEnumVal

static bool IncludeSectionPosIntoA3Db (ISCHIRI_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case ISCHIRI_SECTION_POS_NACHNAHME:
	case ISCHIRI_SECTION_POS_VORNAHME:
	case ISCHIRI_SECTION_POS_KOMPETENZ:
	case ISCHIRI_SECTION_POS_HAERTE:
	case ISCHIRI_SECTION_POS_NATIONALITAET:
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		IncludeIntoA3Db = true;
		break;

		// Parent Section
	case ISCHIRI_SECTION_POS_PARENT_SECTION:
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER:
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER:
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN:
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL:
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromISchiriSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (ISCHIRI_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case ISCHIRI_SECTION_POS_NACHNAHME:
	case ISCHIRI_SECTION_POS_VORNAHME:
	case ISCHIRI_SECTION_POS_KOMPETENZ:
	case ISCHIRI_SECTION_POS_HAERTE:
	case ISCHIRI_SECTION_POS_NATIONALITAET:
	case ISCHIRI_SECTION_POS_PARENT_SECTION:
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER:
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER:
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN:
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL:
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING:
		IncludeIntoXml = true;
		break;

	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN:
		IncludeIntoXml = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromISchiriSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static ISCHIRI_SECTION_POS_TYPE GetISchiriSectionPosTypeFromString (const std::string& TypeString)
{
	ISCHIRI_SECTION_POS_TYPE FoundPos = ISCHIRI_SECTION_POS_UNKNOWN;

	for (int TempPos = ISCHIRI_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_ISCHIRI_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromISchiriSectionPosType ((ISCHIRI_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (ISCHIRI_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetISchiriSectionPosTypeFromString

void AssignISchiriField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<ischiri>(SectionList, SectionLineCount, Line);
} // AssignISchiriField

std::string GetISchiriCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = ISCHIRI_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_ISCHIRI_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromISchiriSectionPosType ((ISCHIRI_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetISchiriCsvHeader

SCHIRI_BOOLEAN_TYPE GetISchiriBooleanTypeFromPosition (ISCHIRI_SECTION_POS_TYPE SectionPos)
{
	SCHIRI_BOOLEAN_TYPE BooleanType = SCHIRI_BOOLEAN_UNKNOWN;
	switch (SectionPos)
	{		
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_GASTSCHIEDSRICHTER: 
		BooleanType = SCHIRI_BOOLEAN_GASTSCHIEDSRICHTER;
		break;
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_COACHING: 
		BooleanType = SCHIRI_BOOLEAN_HASST_COACHING;
		break;
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_MECKERN: 
		BooleanType = SCHIRI_BOOLEAN_HASST_MECKERN;
		break;
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HASST_ZEITSPIEL: 
		BooleanType = SCHIRI_BOOLEAN_HASST_ZEITSPIEL;
		break;
	case ISCHIRI_SECTION_POS_SCHIEDSRICHTEREIGENSCHAFTEN_SPLIT_BITMASK_HEIMSCHIEDSRICHTER: 
		BooleanType = SCHIRI_BOOLEAN_HEIMSCHIEDSRICHTER;
		break;

	default:
		//do nothing
		break;
	} // switch section pos

	return (BooleanType);
} // GetISchiriBooleanTypeFromPosition

void GetISchiriAllowedValues (std::vector<FIELD_VALUE_STRUCT>& AllowedValues)
{
	for (int SectionPos = ISCHIRI_SECTION_POS_UNKNOWN + 1; SectionPos < NO_OF_ISCHIRI_SECTION_POS_TYPES; SectionPos++)
	{
		ENUM_FUNC EnumFunc = nullptr;
		int EnumLow = 0;
		int EnumHigh = 0;
		SCHIRI_BOOLEAN_TYPE ISchiriBoolean = SCHIRI_BOOLEAN_UNKNOWN;
		bool DetailsFound = false;

		// No Enums
		if ((ISchiriBoolean = GetISchiriBooleanTypeFromPosition ((ISCHIRI_SECTION_POS_TYPE) SectionPos)) != SCHIRI_BOOLEAN_UNKNOWN)
		{
			GetBooleanEnumDetails (EnumFunc, EnumLow, EnumHigh);
			DetailsFound = true;
		} // if boolean field

		// Add Values
		if (DetailsFound)
		{
			// Add the Value Entry to the List
			AddFieldValueEntryToList (AllowedValues, GetNameFromISchiriSectionPosType((ISCHIRI_SECTION_POS_TYPE) SectionPos));

			// Add allowed Values
			AddFieldValuesForLastEntry (AllowedValues, EnumLow, EnumHigh, EnumFunc);
		} // if got a function
	} // for each section pos
} // GetISchiriAllowedValues
