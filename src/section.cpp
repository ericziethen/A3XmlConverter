#include "section.h"

#include <sstream>
#include <iomanip> 
#include "error_handling.h"
#include "a3_db_file_lib.h"
#include <iostream>
#include <algorithm>

#include "sub_sections.h"
#include "misc_lib.h"
#include "a3_ui_text.h"

#define SECT_PREFIX "%SECT%"
#define END_SECT_PREFIX "%ENDSECT%"

section::section(void)
{
#if DEBUG_ENABLED
showTextMsg("CREATE SECTION");
#endif
}

section::~section(void)
{
}

void section::SetParentId (std::string NewParentId)
{
	this->ParentId = NewParentId;
} // SetParentId

std::string section::GetParentId()
{
	return (this->ParentId);
} // GetParentId

void section::SetA3FileLandIds (const std::string& FileLandId, const std::string& FileLandIdExpanded)
{
	this->A3FileLand = FileLandId;
	this->A3FileLand_Expanded = FileLandIdExpanded;
} // SetA3FileLandIds

std::string section::GetA3FileLandId ()
{
	return (this->A3FileLand);
} // GetA3FileLandId

std::string section::GetA3FileLandId_Expanded ()
{
	return (this->A3FileLand_Expanded);
} // GetA3FileLandId_Expanded

const std::string GetSectionIdentifierFromSectionType (const SECTION_TYPE SectionType)
{
	std::stringstream SectionIdentifier;
	SectionIdentifier << "%SECT%" << GetNameFromSectionType (SectionType);
	return (SectionIdentifier.str());

} /* GetSectionIdentifierFromSectionType */

bool StringIsSectionStart (const std::string Line)
{
	return (isPrefix (SECT_PREFIX, Line));
} /* StringIsSectionStart */

bool StringIsSectionEnd (const std::string Line)
{
	return (isPrefix (END_SECT_PREFIX, Line));
} /* StringIsSectionEnd */

std::string FormSectionStart (SECTION_TYPE SectionType)
{
	return (std::string(SECT_PREFIX) + GetNameFromSectionType(SectionType));
} // FormSectionStart

std::string FormSectionEnd (SECTION_TYPE SectionType)
{
	return (std::string(END_SECT_PREFIX) + GetNameFromSectionType(SectionType));
} // FormSectionEnd

bool section::SectionParentMatchesString (const std::string& CheckString)
{
	return ((this->GetParentId().compare(CheckString)) == 0);
} // SectionParentMatchesString

bool section::SectionMatchesParent (section* ParentSection)
{	
	return (this->SectionParentMatchesString(ParentSection->GetUniqueId()));
} // SectionMatchesParent

bool section::SectionMatchesParent (SECTION_TYPE SectionType)
{
	return (this->SectionParentMatchesString(GetGenericParentIdentifier(SectionType)));
} // SectionMatchesParent

void section::ConvertLandField (SECTION_EXPANSION_TYPE SectionExpansionType, int ConvertFromSectionPos, int ConvertToSectionPos,
								   std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
#if DEBUG_ENABLED
	std::cout << GetNameFromSectionExpansionType(SectionExpansionType) << " - " << "Fields for Section: " << 
		GetNameFromSectionType(this->GetSectionType()) << ", ID: " << this->GetUniqueId() << ", Value: " << 
		this->GetValueAtSectionPos(ConvertFromSectionPos) << ", To Field Number: " << ConvertToSectionPos <<
		" -> " << __FUNCTION__ << std::endl;
#endif

	switch (SectionExpansionType)
	{
	case SECTION_EXPANSION_FROM_A3DB_LAND:
		this->AssignField(ConvertToSectionPos, NationValueToNationString (this->GetValueAtSectionPos(ConvertFromSectionPos), SectionList));
		break;

	case SECTION_EXPANSION_TO_A3DB_LAND:
		this->AssignField(ConvertToSectionPos, NationStringToNationValue(this->GetValueAtSectionPos(ConvertFromSectionPos), SectionList));
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Expansion Type: " << GetNameFromSectionExpansionType (SectionExpansionType) << "(" <<
						SectionExpansionType << ")" <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

} // ConvertLandField

void section::ConvertVereinField (SECTION_EXPANSION_TYPE SectionExpansionType, int ConvertFromSectionPos, int ConvertToSectionPos,
								  const std::string& LandId, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
#if DEBUG_ENABLED
	std::cout << GetNameFromSectionExpansionType(SectionExpansionType) << " - " << "Fields for Section: " << 
		GetNameFromSectionType(this->GetSectionType()) << ", ID: " << this->GetUniqueId() << ", Value: " << 
		this->GetValueAtSectionPos(ConvertFromSectionPos) << ", To Field Number: " << ConvertToSectionPos <<
		" -> " << __FUNCTION__ << std::endl;
#endif

	switch (SectionExpansionType)
	{
	case SECTION_EXPANSION_FROM_A3DB_VEREIN:										 
		this->AssignField(ConvertToSectionPos, VereinValueToVereinString (this->GetValueAtSectionPos(ConvertFromSectionPos), LandId, SectionList));
		break;

	case SECTION_EXPANSION_TO_A3DB_VEREIN:
		this->AssignField(ConvertToSectionPos, VereinStringToVereinValue (this->GetValueAtSectionPos(ConvertFromSectionPos), SectionList));
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Expansion Type: " << GetNameFromSectionExpansionType (SectionExpansionType) << "(" <<
			SectionExpansionType << ")" <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

} // ConvertVereinField

void section::SplitJoinedField (const std::string& FieldValueStr, ENUM_VALUE_LIST& Target1BaseValues, int SplitField1, int SplitField2)
{
	// Sort the list if not already sorted
	if (!std::is_sorted(Target1BaseValues.begin(), Target1BaseValues.end()))
		std::sort (Target1BaseValues.begin(), Target1BaseValues.end());

	// Convert the Field Value, ASSUME always set and always a number
	int FieldValue = T_StringToNumber<int>(FieldValueStr);

	int LowValue = 0; // start low value from 0
	int HighValue = 0;
	int TargetValue1 = -1;
	int TargetValue2 = -1;
	bool ValuesFound = false;

	ENUM_VALUE_LIST::iterator BaseIterator;
	for(BaseIterator = Target1BaseValues.begin(); (BaseIterator != Target1BaseValues.end()) && (!ValuesFound); ++BaseIterator)
	{
		ENUM_VALUE_LIST::iterator LastIterator = Target1BaseValues.end();
		--LastIterator;

		// Get the High Value
		HighValue = (*BaseIterator)->EnumVal;

		if (FieldValue < LowValue)
		{
			std::stringstream ErrorText;
			ErrorText << "Unexpected Value \"" << FieldValue << "\"" ", (Low,High) = (" << LowValue << ", " << HighValue << ") -> " <<__FUNCTION__;
			programError (ErrorText.str());
		} // if the Field Value is lower than the low value (not allowed)
		else if ((BaseIterator == LastIterator) || (FieldValue < HighValue))
		{
			if (FieldValue < HighValue)
			{
				TargetValue1 = LowValue;
				TargetValue2 = FieldValue - LowValue;
			} // if below the high value
			else
			{
				TargetValue1 = HighValue;
				TargetValue2 = FieldValue - HighValue;
			} // at least high value

			ValuesFound = true;
		} // if at the end or in range
		
		LowValue = HighValue;
	} // for each value in the list

	if (ValuesFound)
	{		
		this->AssignField (SplitField1, std::to_string(TargetValue1));
		this->AssignField (SplitField2, std::to_string(TargetValue2));
	} // found the split values
	else
	{
		std::stringstream ErrorText;
		ErrorText << "No Values Found for FieldValue " << FieldValueStr << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}
} // SplitJoinedField

void section::MergeSplitField (int TargetField)
{
	int Sum = 0;
	std::vector<int> TargetFieldList;
	this->GetGenericSplitFieldsForField(TargetField, TargetFieldList);

	// Add Values from Generic Fields
	std::vector<int>::const_iterator SplitFieldIterator;
	for (SplitFieldIterator = TargetFieldList.begin(); SplitFieldIterator != TargetFieldList.end(); ++SplitFieldIterator)
	{
		Sum += T_StringToNumber<int>(this->GetValueAtSectionPos(*SplitFieldIterator));
	}

	// Set the Combined Value
	this->AssignField(TargetField, std::to_string(Sum));
} //MergeSplitField

void section::InitializeFields (const std::vector<int>& SectionPosS, const std::string& InitValue)
{
	std::vector<int>::const_iterator SectionPosIter;
	for(SectionPosIter = SectionPosS.begin(); SectionPosIter != SectionPosS.end(); ++SectionPosIter)
	{
		this->AssignField((*SectionPosIter), InitValue);
	} // for each section pos
} // InitializeFields

void section::SplitBitmaskField (int SectionPos, ENUM_VALUE_LIST& BitmaskValues)
{
	// There are 2 kinds of Bitmasks to Consider when Splitting (and merging???)
	// 1st - The bitmask which holds multiple values of the same type (e.g. Eigenschaften)
	// 2nd - The bitmask which holds multiple boolean values, e.g Dach, where each has it's own value
	std::vector<int> GenericSplitFieldList;
	this->GetGenericSplitFieldsForField(SectionPos, GenericSplitFieldList);	
	const std::string& FieldValueStr = this->GetValueAtSectionPos(SectionPos);

	// if we have at least 1 generic field it's a generic bitmask, could that be mixed???
	bool IsGenericBitmask = (GenericSplitFieldList.size() > 0);

	// Sort the list if not already sorted
	if (!std::is_sorted(BitmaskValues.begin(), BitmaskValues.end()))
		std::sort (BitmaskValues.begin(), BitmaskValues.end());

	// Convert the Field Value, ASSUME always set and always a number
	int FieldValue = T_StringToNumber<int>(FieldValueStr);

	ENUM_VALUE_LIST::reverse_iterator BitmaskIterator;
	size_t NextGenericSplitField = 0;

	// Check all Bitmask values, set Generic fields and Flag other (e.g. boolean) fields
	for (BitmaskIterator = BitmaskValues.rbegin(); (BitmaskIterator != BitmaskValues.rend()); ++BitmaskIterator)
	{
		int EnumVal = std::static_pointer_cast<enum_value>(*BitmaskIterator)->EnumVal;
		if (FieldValue >= EnumVal)
		{
			// Decrement the Lookup Value
			FieldValue -= EnumVal;

			if ((NextGenericSplitField + 1) <= GenericSplitFieldList.size())
			{
				// Set the Generic Field and increment Generic Field index
				this->AssignField(GenericSplitFieldList.at(NextGenericSplitField++), std::to_string(EnumVal));
			} // if we have a generic field
			else
			{
				// Flag field for set so we can deal with it later if possible
				std::static_pointer_cast<enum_value>(*BitmaskIterator)->ValueSet = true;
			} // No Generic Field			
		} // if this enum value is larger than whats left of the FieldValue
	} // for each bitmask value

	// Initialize any Generic Split Fields
	std::vector<int>::iterator TargetFieldIterator;
	for (TargetFieldIterator = GenericSplitFieldList.begin() + NextGenericSplitField; TargetFieldIterator != GenericSplitFieldList.end(); ++TargetFieldIterator)
	{
		this->AssignField(GenericSplitFieldList.at(NextGenericSplitField), ENUM_NULL_VALUE_STRING);
		NextGenericSplitField++;
	}

	if (!IsGenericBitmask)
	{	
		// Set Boolean Fields if they have an own field
		for (BitmaskIterator = BitmaskValues.rbegin(); (BitmaskIterator != BitmaskValues.rend()); ++BitmaskIterator)
		{
			int TargetBooleanField;
			if (this->GetBooleanTargetFieldForEnumVal (SectionPos, std::static_pointer_cast<enum_value>(*BitmaskIterator)->EnumPos, TargetBooleanField))
			{
				// Only set if the Target Value is > 0 since that is the default Case and will not have a separate Field in the DB but rather
				// is calculated if the others are not set

				if (std::static_pointer_cast<enum_value>(*BitmaskIterator)->ValueSet)
					this->AssignField(TargetBooleanField, std::to_string(std::static_pointer_cast<enum_value>(*BitmaskIterator)->EnumVal));
				else
					this->AssignField(TargetBooleanField, std::to_string(BITMASK_VALUE_NONE));
			} // if have a special field
		} // For each bitmask value
	} // if not a generic bitmask 

} // SplitBitmaskField

void section::MergeBitmaskField (int TargetField, ENUM_VALUE_LIST& BitmaskValues)
{
	int Sum = 0;
	std::vector<int> TargetFieldList;
	this->GetGenericSplitFieldsForField(TargetField, TargetFieldList);

	// if we have at least 1 generic field it's a generic bitmask, could that be mixed???
	bool IsGenericBitmask = (TargetFieldList.size() > 0);


	if (IsGenericBitmask)
	{
		// Add Values from Generic Fields
		std::vector<int>::const_iterator SplitFieldIterator;
		for (SplitFieldIterator = TargetFieldList.begin(); SplitFieldIterator != TargetFieldList.end(); ++SplitFieldIterator)
		{
			// if we have at least 1 generic field it's a generic bitmask, could that be mixed???
			IsGenericBitmask = true;

			Sum += T_StringToNumber<int>(this->GetValueAtSectionPos(*SplitFieldIterator));
		}
	}// if generic split field
	else
	{
		ENUM_VALUE_LIST::reverse_iterator BitmaskIterator;
		// Check all Bitmask values, set Generic fields and Flag other (e.g. boolean) fields
		for (BitmaskIterator = BitmaskValues.rbegin(); (BitmaskIterator != BitmaskValues.rend()); ++BitmaskIterator)
		{	
			int TargetBooleanField;
			if (this->GetBooleanTargetFieldForEnumVal (TargetField, std::static_pointer_cast<enum_value>(*BitmaskIterator)->EnumPos, TargetBooleanField))
			{
				Sum += T_StringToNumber<int>(this->GetValueAtSectionPos(TargetBooleanField));
			} // if found a boolean field		
		} // For each Bitmask Value
	} // if it is not a generic bitmask

	// Set the Combined Value
	this->AssignField(TargetField, std::to_string(Sum));
} // MergeBitmaskField

void section::DecodeBooleanFromA3Db (int SectionPos)
{
	int FieldValue = T_StringToNumber<int>(this->GetValueAtSectionPos(SectionPos));
	std::string NewValue;
	if (FieldValue > BOOLEAN_NO_VALUE)
		NewValue = GetNameFromBooleanType (BOOLEAN_YES);
	else
		NewValue = GetNameFromBooleanType (BOOLEAN_NO);

	this->AssignField(SectionPos, NewValue);
} // DecodeBooleanFromA3Db

void section::EncodeBooleanToA3Db (int SectionPos, int BooleanFieldValue)
{
	BOOLEAN_TYPE Boolean = (BOOLEAN_TYPE) StringToEnum (this->GetValueAtSectionPos (SectionPos), BOOLEAN_UNKNOWN, NO_OF_BOOLEAN_TYPES,
														GetNameFromBooleanType);

	std::string NewValue;
	if (Boolean == BOOLEAN_YES)
		NewValue = std::to_string(BooleanFieldValue);
	else
		NewValue = std::to_string(BOOLEAN_NO_VALUE);

	this->AssignField(SectionPos, NewValue);
} // EncodeBooleanToA3Db

void section::DecodeEnumFromA3Db (int SectionPos, int EnumType, ENUM_MAP_LOOKUP_FUNC EnumPosLookup, ENUM_DETAILS_LOOKUP_FUNC EnumDetailsLookup)
{
//std::cout << __FUNCTION__ << " for " << this->GetSectionType() << "::" << this->GetUniqueId() << "::" << this->GetParentId() 
//	<< ", SectionPos: " << SectionPos << ", EnumType: " << EnumType << std::endl;
	int EnumLow, EnumHigh;
	ENUM_FUNC EnumFunc;
	EnumDetailsLookup (SectionPos, EnumType, EnumFunc, EnumLow, EnumHigh);

	// Get the Value representing the Enum Entry
//std::cout << "  StringValue: " <<  this->GetValueAtSectionPos(SectionPos) << std::endl; 
	int EnumVal = T_StringToNumber<int>(this->GetValueAtSectionPos(SectionPos));
//std::cout << "  IntValue: " <<  EnumVal << std::endl; 

	// Convert the Value to it's Enum Value
	int EnumPos = EnumPosLookup (EnumType, ENUM_VALUE_SIDE_RIGHT, EnumVal);

	// Assign the String of the Enum Value
	this->AssignField(SectionPos, EnumFunc(EnumPos));
} // DecodeEnumFromA3Db

void section::EncodeEnumToA3Db (int SectionPos, int EnumType, ENUM_MAP_LOOKUP_FUNC EnumValLookup, ENUM_DETAILS_LOOKUP_FUNC EnumDetailsLookup)
{
	int EnumLow, EnumHigh;
	ENUM_FUNC EnumFunc;
	EnumDetailsLookup (SectionPos, EnumType, EnumFunc, EnumLow, EnumHigh);

	// Lookup the Enum Value of the String
	int EnumPos = StringToEnum (this->GetValueAtSectionPos (SectionPos), EnumLow, EnumHigh, EnumFunc);

	// Convert the Enum Value to its Integer Value
	int EnumVal = EnumValLookup (EnumType, ENUM_VALUE_SIDE_LEFT, EnumPos);

	// Set the Value 
	this->AssignField(SectionPos, std::to_string(EnumVal));
	
} // DecodeEnumFromA3Db

void section::SetA3LandIdsForMatchingSection(const std::string& LandId, const std::string LandId_Expanded, 
												std::vector<std::shared_ptr<section>> TargetSectionList, size_t LastSectionCount)
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	for (SectionIterator = TargetSectionList.begin() + LastSectionCount; SectionIterator != TargetSectionList.end(); ++SectionIterator)
	{
//std::cout << "        - Section: " << GetNameFromSectionType((*SectionIterator)->GetSectionType()) << " ID: " << (*SectionIterator)->GetUniqueId() << ", Parent: " << (*SectionIterator)->GetParentId() << std::endl;
		if ((*SectionIterator)->SectionMatchesParent(this))
		{
// std::cout << "          MATCH!!!!!" << std::endl;
			(*SectionIterator)->SetA3FileLandIds(LandId, LandId_Expanded);
		} // if section matches
	} // for each section
} // SetA3LandIdsForMatchingSection

void section::GetGenericSplitFieldsForField (int SpielerSectionPos, std::vector<int>& SplitFields)
{
	std::stringstream ErrorText;
	ErrorText << "Abstract Function call from " << GetNameFromSectionType(this->GetSectionType()) << 
			", subclass must implement function themselves so it can be called -> " <<__FUNCTION__;
	programError (ErrorText.str());
} // GetGenericSplitFieldsForField

bool section::GetBooleanTargetFieldForEnumVal (const int SectionPos, const int EnumPos, int& BooleanTargetField)
{
	std::stringstream ErrorText;
	ErrorText << "Abstract Function call from " << GetNameFromSectionType(this->GetSectionType()) << 
		", subclass must implement function themselves so it can be called -> " <<__FUNCTION__;
	programError (ErrorText.str());

	return(false);
} // GetBooleanTargetFieldForEnumVal

std::string GetGenericParentIdentifier (SECTION_TYPE SectionType)
{
	return(GetNameFromSectionType(SectionType));
} // GetGenericParentIdentifier

SECTION_TYPE GetSectionTypeFromString (const std::string SectionString)
{
	int TempSection = 0;
	SECTION_TYPE FoundSection = SECTION_TYPE_UNKNOWN;

	for (TempSection = SECTION_TYPE_UNKNOWN + 1; TempSection < NO_OF_SECTION_TYPES; TempSection++)
	{
		if (GetSectionIdentifierFromSectionType ((SECTION_TYPE) TempSection).compare (SectionString) == 0)
		{
			FoundSection = (SECTION_TYPE) TempSection;
			break;
		}
	}

	return (FoundSection);
} /* GetSectionTypeFromString */

const char* GetNameFromSectionExpansionType (const SECTION_EXPANSION_TYPE SectionExpansionType)
{
	switch (SectionExpansionType)
	{
	case SECTION_EXPANSION_FROM_A3DB_LAND:
		return ("FROM_A3DB_LAND");
	case SECTION_EXPANSION_TO_A3DB_LAND:
		return ("TO_A3DB_LAND");

	case SECTION_EXPANSION_FROM_A3DB_VEREIN:
		return ("FROM_A3DB_VEREIN");
	case SECTION_EXPANSION_TO_A3DB_VEREIN:
		return ("TO_A3DB_VEREIN");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Expansion Type " << SectionExpansionType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
	}
} // GetNameFromSectionExpansionType

const char* GetNameFromSectionType (const SECTION_TYPE SectionType)
{
	switch (SectionType)
	{
	case SECTION_TYPE_UNKNOWN:
		return ("UNKNOWN");
	case SECTION_TYPE_SPIELER:
		return ("SPIELER");
	case SECTION_TYPE_IVEREIN:
		return ("IVEREIN");
	case SECTION_TYPE_AJUGEND:
		return ("AJUGEND");
	case SECTION_TYPE_AMATEURV:
		return ("AMATEURV");
	case SECTION_TYPE_KRITIKER:
		return ("KRITIKER");
	case SECTION_TYPE_KRITIP:
		return ("KRITIP");
	case SECTION_TYPE_LAND:
		return ("LAND");
	case SECTION_TYPE_MANAGER:
		return ("MANAGER");
	case SECTION_TYPE_MANAGERP:
		return ("MANAGERP");
	case SECTION_TYPE_MEDIAP:
		return ("MEDIAP");
	case SECTION_TYPE_PROMI:
		return ("PROMI");
	case SECTION_TYPE_PROMIP:
		return ("PROMIP");
	case SECTION_TYPE_REPORTER:
		return ("REPORTER");
	case SECTION_TYPE_SCHIRI:
		return ("SCHIRI");
	case SECTION_TYPE_SCHIRIP:
		return ("SCHIRIP");
	case SECTION_TYPE_SPONSOR:
		return ("SPONSOR");
	case SECTION_TYPE_SPONSORP:
		return ("SPONSORP");
	case SECTION_TYPE_STADION:
		return ("STADION");
	case SECTION_TYPE_TRAINER:
		return ("TRAINER");
	case SECTION_TYPE_TRAINERP:
		return ("TRAINERP");
	case SECTION_TYPE_TWTRAINER:
		return ("TWTRAINER");
	case SECTION_TYPE_TWTRAINP:
		return ("TWTRAINP");
	case SECTION_TYPE_VEREIN:
		return ("VEREIN");
	case SECTION_TYPE_VPRAESID:
		return ("VPRAESID");
	case SECTION_TYPE_ASPIELER:
		return ("ASPIELER");
	case SECTION_TYPE_AUSRUESTER:
		return ("AUSRUESTER");
	case SECTION_TYPE_BONUS:
		return ("BONUS");
	case SECTION_TYPE_CLEAGUE:
		return ("CLEAGUE");
	case SECTION_TYPE_CLEAGUEGRP:
		return ("CLEAGUEGRP");
	case SECTION_TYPE_EFANGES:
		return ("EFANGES");
	case SECTION_TYPE_EMGRP:
		return ("EMGRP");
	case SECTION_TYPE_EMWM:
		return ("EMWM");
	case SECTION_TYPE_EUROSIEGER:
		return ("EUROSIEGER");
	case SECTION_TYPE_EXSPIEL:
		return ("EXSPIEL");
	case SECTION_TYPE_FANGES:
		return ("FANGES");
	case SECTION_TYPE_HALBZEIT:
		return ("HALBZEIT");
	case SECTION_TYPE_ISCHIRI:
		return ("ISCHIRI");
	case SECTION_TYPE_IVEREINE:
		return ("IVEREINE");
	case SECTION_TYPE_LIGA:
		return ("LIGA");
	case SECTION_TYPE_MISC:
		return ("MISC");
	case SECTION_TYPE_NATION:
		return ("NATION");
	case SECTION_TYPE_QUIZ:
		return ("QUIZ");
	case SECTION_TYPE_SONSPIELER:
		return ("SONSPIELER");
	case SECTION_TYPE_TURNIERGRP:
		return ("TURNIERGRP");
	case SECTION_TYPE_UEFA:
		return ("UEFA");
	case SECTION_TYPE_WMGRP:
		return ("WMGRP");

    // special cases
	case SECTION_TYPE_VEREIN_HIDDEN:
		return ("VEREIN_HIDDEN");
	case SECTION_TYPE_AJUGEND_HIDDEN:
		return ("AJUGEND_HIDDEN");
	case SECTION_TYPE_ASPIELER_HIDDEN:
		return("ASPIELER_HIDDEN");
	case SECTION_TYPE_INTERNAT_VEREIN:
		return("INTERNAT_VEREIN");
	case SECTION_TYPE_EUROSIEGER_HIDDEN:
		return("EUROSIEGER_HIDDEN");
	case SECTION_TYPE_ISCHIRI_HIDDEN:
		return("ISCHIRI_HIDDEN");
	case SECTION_TYPE_SPIELER_HIDDEN:
		return("SPIELER_HIDDEN");
	case SECTION_TYPE_SPIEL_HIDDEN:
		return("SPIEL");
	case SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN:
		return("SPIELPLAN_VEREIN");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Type " << SectionType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
	}
} /* GetStringFromSectionType */

bool SectionIsVisible (const SECTION_TYPE& SectionType)
{
	bool SectionIsVisible = false;

	switch (SectionType)
	{
	case SECTION_TYPE_SPIELER:
	case SECTION_TYPE_IVEREIN:
	case SECTION_TYPE_AJUGEND:
	case SECTION_TYPE_AMATEURV:
	case SECTION_TYPE_KRITIKER:
	case SECTION_TYPE_LAND:
	case SECTION_TYPE_MANAGER:
	case SECTION_TYPE_PROMI:
	case SECTION_TYPE_REPORTER:
	case SECTION_TYPE_SCHIRI:
	case SECTION_TYPE_SPONSOR:
	case SECTION_TYPE_STADION:
	case SECTION_TYPE_TRAINER:
	case SECTION_TYPE_TWTRAINER:
	case SECTION_TYPE_VEREIN:
	case SECTION_TYPE_VPRAESID:
	case SECTION_TYPE_ASPIELER:
	case SECTION_TYPE_AUSRUESTER:
	case SECTION_TYPE_BONUS:
	case SECTION_TYPE_CLEAGUE:
	case SECTION_TYPE_EFANGES:
	case SECTION_TYPE_EMGRP:
	case SECTION_TYPE_EMWM:
	case SECTION_TYPE_EUROSIEGER:
	case SECTION_TYPE_EXSPIEL:
	case SECTION_TYPE_FANGES:
	case SECTION_TYPE_HALBZEIT:
	case SECTION_TYPE_ISCHIRI:
	case SECTION_TYPE_IVEREINE:
	case SECTION_TYPE_LIGA:
	case SECTION_TYPE_MISC:
	case SECTION_TYPE_NATION:
	case SECTION_TYPE_QUIZ:
	case SECTION_TYPE_SONSPIELER:
	case SECTION_TYPE_TURNIERGRP:
	case SECTION_TYPE_UEFA:
	case SECTION_TYPE_WMGRP:
	case SECTION_TYPE_CLEAGUEGRP:
	case SECTION_TYPE_KRITIP:
	case SECTION_TYPE_MANAGERP:
	case SECTION_TYPE_MEDIAP:
	case SECTION_TYPE_PROMIP:
	case SECTION_TYPE_SCHIRIP:
	case SECTION_TYPE_SPONSORP:
	case SECTION_TYPE_TRAINERP:
	case SECTION_TYPE_TWTRAINP:
		SectionIsVisible = true;
		break;

	case SECTION_TYPE_VEREIN_HIDDEN:
	case SECTION_TYPE_AJUGEND_HIDDEN:
	case SECTION_TYPE_ASPIELER_HIDDEN:
	case SECTION_TYPE_EUROSIEGER_HIDDEN:
	case SECTION_TYPE_ISCHIRI_HIDDEN:
	case SECTION_TYPE_SPIELER_HIDDEN:
	case SECTION_TYPE_SPIEL_HIDDEN:
	case SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN:
		SectionIsVisible = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Type " << GetNameFromSectionType (SectionType) << " -> " << __FUNCTION__;
		programError (ErrorText.str());
	}

	return (SectionIsVisible);
} // SectionIsVisible

int GetNoOfFieldsInA3Section (SECTION_TYPE SectionType)
{
	int NoOfFields = 0;
	
	switch (SectionType)
	{
	case SECTION_TYPE_VEREIN:
		NoOfFields = 5;
		break;
		
	case SECTION_TYPE_LAND:
		NoOfFields = 6;
		break;

	case SECTION_TYPE_TRAINER:
		NoOfFields = 8;
		break;

	case SECTION_TYPE_MANAGER:
		NoOfFields = 5;
		break;

	case SECTION_TYPE_CLEAGUEGRP:
		NoOfFields = 10;
		break;

	case SECTION_TYPE_TURNIERGRP:
		NoOfFields = 10;
		break;

	case SECTION_TYPE_IVEREIN:
		NoOfFields = 2;
		break;

	case SECTION_TYPE_SPIELER:
		NoOfFields = 33;
		break;

	case SECTION_TYPE_STADION:
		NoOfFields = 39;
		break;

	case SECTION_TYPE_AMATEURV:
		NoOfFields = 1;
		break;

	case SECTION_TYPE_TWTRAINER:
		NoOfFields = 7;
		break;

	case SECTION_TYPE_SCHIRI:
		NoOfFields = 6;
		break;

	case SECTION_TYPE_SPONSOR:
		NoOfFields = 19;
		break;

	case SECTION_TYPE_PROMI:
		NoOfFields = 3;
		break;

	case SECTION_TYPE_REPORTER:
		NoOfFields = 4;
		break;

	case SECTION_TYPE_KRITIKER:
		NoOfFields = 2;
		break;

	case SECTION_TYPE_VPRAESID:
		NoOfFields = 3;
		break;

	case SECTION_TYPE_VEREIN_HIDDEN:
		NoOfFields = 51;
		break;

	case SECTION_TYPE_AJUGEND_HIDDEN:
		NoOfFields = 4;
		break;

	case SECTION_TYPE_ASPIELER_HIDDEN:
		NoOfFields = 2;
		break;

	case SECTION_TYPE_SPIEL_HIDDEN:
		NoOfFields = 2;
		break;

	case SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN:
		NoOfFields = 1;
		break;

	case SECTION_TYPE_EUROSIEGER_HIDDEN:
		NoOfFields = 3;
		break;

	case SECTION_TYPE_ISCHIRI_HIDDEN:
		NoOfFields = 6;
		break;

	case SECTION_TYPE_SPIELER_HIDDEN:
		NoOfFields = 2;
		break;

	case SECTION_TYPE_NATION:
		NoOfFields = 11;
		break;

	case SECTION_TYPE_LIGA:
		NoOfFields = 3;
			break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Type " << GetNameFromSectionType (SectionType) << " -> " << __FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(NoOfFields);
} // GetNoOfFieldsInA3Section

bool SectionContainsData (SECTION_TYPE SectionType)
{
	bool ContainsData = false;

	switch (SectionType)
	{
		case SECTION_TYPE_SPIELER:
		case SECTION_TYPE_IVEREIN:
		case SECTION_TYPE_AMATEURV:
		case SECTION_TYPE_KRITIKER:
		case SECTION_TYPE_LAND:
		case SECTION_TYPE_MANAGER:
		case SECTION_TYPE_PROMI:
		case SECTION_TYPE_REPORTER:
		case SECTION_TYPE_SCHIRI:
		case SECTION_TYPE_SPONSOR:
		case SECTION_TYPE_STADION:
		case SECTION_TYPE_TRAINER:
		case SECTION_TYPE_TWTRAINER:
		case SECTION_TYPE_VEREIN:
		case SECTION_TYPE_VPRAESID:
		case SECTION_TYPE_AUSRUESTER:
		case SECTION_TYPE_BONUS:
		case SECTION_TYPE_EFANGES:
		case SECTION_TYPE_EMWM:
		case SECTION_TYPE_FANGES:
		case SECTION_TYPE_HALBZEIT:
		case SECTION_TYPE_LIGA:
		case SECTION_TYPE_MISC:
		case SECTION_TYPE_NATION:
		case SECTION_TYPE_QUIZ:
		case SECTION_TYPE_TURNIERGRP:
		case SECTION_TYPE_UEFA:
		case SECTION_TYPE_CLEAGUEGRP:
		case SECTION_TYPE_VEREIN_HIDDEN:
		case SECTION_TYPE_AJUGEND_HIDDEN:
		case SECTION_TYPE_ASPIELER_HIDDEN:
		case SECTION_TYPE_EUROSIEGER_HIDDEN:
		case SECTION_TYPE_ISCHIRI_HIDDEN:
		case SECTION_TYPE_SPIELER_HIDDEN:
		case SECTION_TYPE_SPIEL_HIDDEN:
		case SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN:
			ContainsData = true;
			break;

		case SECTION_TYPE_AJUGEND: // Hidden Sub Sections
		case SECTION_TYPE_ASPIELER: // Hidden Sub Sections
		case SECTION_TYPE_EUROSIEGER: // Hidden Sub Section
		case SECTION_TYPE_SONSPIELER: // Sub Sections Spieler
		case SECTION_TYPE_ISCHIRI: // Hidden Sub section
		case SECTION_TYPE_KRITIP:
		case SECTION_TYPE_MANAGERP:
		case SECTION_TYPE_IVEREINE:
		case SECTION_TYPE_MEDIAP:
		case SECTION_TYPE_PROMIP:
		case SECTION_TYPE_SCHIRIP:
		case SECTION_TYPE_SPONSORP:
		case SECTION_TYPE_TRAINERP:
		case SECTION_TYPE_TWTRAINP:
		case SECTION_TYPE_EXSPIEL:
		case SECTION_TYPE_CLEAGUE:
		case SECTION_TYPE_EMGRP:
		case SECTION_TYPE_WMGRP:
			ContainsData = false;
			break;

		default:
			std::stringstream ErrorText;
			ErrorText << "Unhandled Section Type " << GetNameFromSectionType (SectionType) << " -> " << __FUNCTION__;
			programError (ErrorText.str());
	}

	return (ContainsData);
} /* SectionContainsData */

void GetFollowUpSections (const std::string& FileName, SECTION_TYPE ParentSectionType, std::vector<SECTION_TYPE>& FollowupSectionList)
{
	A3_FILE_GROUP_TYPE FileGroupType;

	switch (ParentSectionType)
	{
	case SECTION_TYPE_VEREIN:
		FollowupSectionList.push_back(SECTION_TYPE_STADION);
		break;

	case SECTION_TYPE_SPIELER:
		FileGroupType = GetA3FileGroupFromFileName(FileName);
		if(FileGroupType == A3_FILE_GROUP_EXSPIEL)
			FollowupSectionList.push_back(SECTION_TYPE_SPIELER_HIDDEN);
		break;

	case SECTION_TYPE_UNKNOWN:
	case SECTION_TYPE_LAND:
	case SECTION_TYPE_TRAINERP:
	case SECTION_TYPE_TWTRAINP:
	case SECTION_TYPE_MANAGERP:
	case SECTION_TYPE_SCHIRIP:
	case SECTION_TYPE_SPONSORP:
	case SECTION_TYPE_PROMIP:
	case SECTION_TYPE_MEDIAP:
	case SECTION_TYPE_KRITIP:
	case SECTION_TYPE_TRAINER:
	case SECTION_TYPE_MANAGER:
	case SECTION_TYPE_STADION:
	case SECTION_TYPE_AMATEURV:
	case SECTION_TYPE_AJUGEND:
	case SECTION_TYPE_TWTRAINER:
	case SECTION_TYPE_SCHIRI:
	case SECTION_TYPE_SPONSOR:
	case SECTION_TYPE_PROMI:
	case SECTION_TYPE_REPORTER:
	case SECTION_TYPE_KRITIKER:
	case SECTION_TYPE_VPRAESID:
	case SECTION_TYPE_ASPIELER:
	case SECTION_TYPE_EUROSIEGER:
	case SECTION_TYPE_SONSPIELER:
	case SECTION_TYPE_ISCHIRI:
	case SECTION_TYPE_EXSPIEL:
	case SECTION_TYPE_NATION:
	case SECTION_TYPE_IVEREINE:
	case SECTION_TYPE_IVEREIN:
	case SECTION_TYPE_CLEAGUE:
	case SECTION_TYPE_CLEAGUEGRP:
	case SECTION_TYPE_EMGRP:
	case SECTION_TYPE_WMGRP:
	case SECTION_TYPE_TURNIERGRP:
	case SECTION_TYPE_LIGA:
	case SECTION_TYPE_VEREIN_HIDDEN:
	case SECTION_TYPE_AJUGEND_HIDDEN:
	case SECTION_TYPE_ASPIELER_HIDDEN:
	case SECTION_TYPE_EUROSIEGER_HIDDEN:
	case SECTION_TYPE_ISCHIRI_HIDDEN:
	case SECTION_TYPE_SPIELER_HIDDEN:
	case SECTION_TYPE_SPIEL_HIDDEN:
	case SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN:
		// No Follow Up Sections to add
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Type " << GetNameFromSectionType (ParentSectionType) << " -> " << __FUNCTION__;
		programError (ErrorText.str());
		break;
	}
} // GetFollowUpSections

void GetSubLevelSections (const std::string& FileName, SECTION_TYPE ParentSectionType, std::vector<SECTION_TYPE>& SubLevelSectionList)
{
	A3_FILE_GROUP_TYPE FileGroupType;

	switch (ParentSectionType)
	{
	// File Specific Handling, UNKNOWN if first section
	case SECTION_TYPE_UNKNOWN:
		FileGroupType = GetA3FileGroupFromFileName(FileName);
		switch(FileGroupType)
		{
// ERIC - std::cout
case A3_FILE_GROUP_UNKNOWN:
	// INCLUDE UNKNOWN FOR NOW, NOT ALL CODED
	break;

		case A3_FILE_GROUP_LANDXXX:
			SubLevelSectionList.push_back(SECTION_TYPE_LAND);
			break;
			
		case A3_FILE_GROUP_IVEREINE:
			SubLevelSectionList.push_back(SECTION_TYPE_IVEREINE);
			break;

		case A3_FILE_GROUP_INTERNAT:
			SubLevelSectionList.push_back(SECTION_TYPE_LAND);
			SubLevelSectionList.push_back(SECTION_TYPE_EUROSIEGER);
			break;

		case A3_FILE_GROUP_JUGENDXXX:
			SubLevelSectionList.push_back(SECTION_TYPE_ASPIELER);
			break;

		case A3_FILE_GROUP_SONSPIELER:
			SubLevelSectionList.push_back(SECTION_TYPE_SONSPIELER);
			break;

		case A3_FILE_GROUP_CLEAGUE:
			SubLevelSectionList.push_back(SECTION_TYPE_CLEAGUE);
			break;

		case A3_FILE_GROUP_EMWM:
			SubLevelSectionList.push_back(SECTION_TYPE_EMGRP);
			SubLevelSectionList.push_back(SECTION_TYPE_WMGRP);
			break;

		case A3_FILE_GROUP_LIGAYXXX:
			SubLevelSectionList.push_back(SECTION_TYPE_LIGA);
			break;

		case A3_FILE_GROUP_EXSPIEL:
			SubLevelSectionList.push_back(SECTION_TYPE_EXSPIEL);
			break;

		case A3_FILE_GROUP_LAENDER:
			SubLevelSectionList.push_back(SECTION_TYPE_NATION);
			break;

		case A3_FILE_GROUP_ISCHIRI:
			SubLevelSectionList.push_back(SECTION_TYPE_ISCHIRI);
			break;

		default:
			std::stringstream ErrorText;
			ErrorText << "Unexpected FileGroupType: " << FileGroupType << " (" << GetNameFromA3FileGroupType(FileGroupType) << ") -> " <<__FUNCTION__;
			programError (ErrorText.str());	
			break;
		}
		break;

	case SECTION_TYPE_LAND:
		FileGroupType = GetA3FileGroupFromFileName(FileName);
		switch(FileGroupType)
		{
		case A3_FILE_GROUP_LANDXXX:
			SubLevelSectionList.push_back(SECTION_TYPE_VEREIN);
			SubLevelSectionList.push_back(SECTION_TYPE_AMATEURV);
			SubLevelSectionList.push_back(SECTION_TYPE_TRAINER);
			SubLevelSectionList.push_back(SECTION_TYPE_AJUGEND);
			SubLevelSectionList.push_back(SECTION_TYPE_TRAINERP);
			SubLevelSectionList.push_back(SECTION_TYPE_TWTRAINP);
			SubLevelSectionList.push_back(SECTION_TYPE_MANAGERP);
			SubLevelSectionList.push_back(SECTION_TYPE_SCHIRIP);
			SubLevelSectionList.push_back(SECTION_TYPE_SPONSORP);
			SubLevelSectionList.push_back(SECTION_TYPE_PROMIP);
			SubLevelSectionList.push_back(SECTION_TYPE_MEDIAP);
			SubLevelSectionList.push_back(SECTION_TYPE_KRITIP);
			SubLevelSectionList.push_back(SECTION_TYPE_VPRAESID);
			break;

		case A3_FILE_GROUP_INTERNAT:
			SubLevelSectionList.push_back(SECTION_TYPE_VEREIN);
			SubLevelSectionList.push_back(SECTION_TYPE_TRAINER);
			break;

		default:
			std::stringstream ErrorText;
			ErrorText << "Unexpected FileGroupType: " << FileGroupType << " (" << GetNameFromA3FileGroupType(FileGroupType) << ") -> " <<__FUNCTION__;
			programError (ErrorText.str());	
			break;
		}
		break;

	case SECTION_TYPE_VEREIN:
		SubLevelSectionList.push_back(SECTION_TYPE_TRAINER);
		SubLevelSectionList.push_back(SECTION_TYPE_MANAGER);
		SubLevelSectionList.push_back(SECTION_TYPE_VEREIN_HIDDEN);
		SubLevelSectionList.push_back(SECTION_TYPE_SPIELER);
		break;

	case SECTION_TYPE_TRAINERP:
		SubLevelSectionList.push_back(SECTION_TYPE_TRAINER);
		break;

	case SECTION_TYPE_TWTRAINP:
		SubLevelSectionList.push_back(SECTION_TYPE_TWTRAINER);
		break;

	case SECTION_TYPE_MANAGERP:
		SubLevelSectionList.push_back(SECTION_TYPE_MANAGER);
		break;

	case SECTION_TYPE_SCHIRIP:
		SubLevelSectionList.push_back(SECTION_TYPE_SCHIRI);
		break;

	case SECTION_TYPE_SPONSORP:
		SubLevelSectionList.push_back(SECTION_TYPE_SPONSOR);
		break;

	case SECTION_TYPE_PROMIP:
		SubLevelSectionList.push_back(SECTION_TYPE_PROMI);
		break;

	case SECTION_TYPE_MEDIAP:
		SubLevelSectionList.push_back(SECTION_TYPE_REPORTER);
		break;

	case SECTION_TYPE_KRITIP:
		SubLevelSectionList.push_back(SECTION_TYPE_KRITIKER);
		break;

	case SECTION_TYPE_AJUGEND:
		SubLevelSectionList.push_back(SECTION_TYPE_AJUGEND_HIDDEN);
		break;

	case SECTION_TYPE_ASPIELER:
		SubLevelSectionList.push_back(SECTION_TYPE_ASPIELER_HIDDEN);
		break;

	case SECTION_TYPE_LIGA:
		SubLevelSectionList.push_back(SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN);
		SubLevelSectionList.push_back(SECTION_TYPE_SPIEL_HIDDEN);
		break;

	case SECTION_TYPE_EUROSIEGER:
		SubLevelSectionList.push_back(SECTION_TYPE_EUROSIEGER_HIDDEN);
		break;

	case SECTION_TYPE_ISCHIRI:
		SubLevelSectionList.push_back(SECTION_TYPE_ISCHIRI_HIDDEN);
		break;

	case SECTION_TYPE_SONSPIELER:
		SubLevelSectionList.push_back(SECTION_TYPE_SPIELER);
		break;

	case SECTION_TYPE_CLEAGUE:
		SubLevelSectionList.push_back(SECTION_TYPE_CLEAGUEGRP);
		break;

	case SECTION_TYPE_WMGRP:
	case SECTION_TYPE_EMGRP:
		SubLevelSectionList.push_back(SECTION_TYPE_TURNIERGRP);
		break;

	case SECTION_TYPE_EXSPIEL:
		SubLevelSectionList.push_back(SECTION_TYPE_SPIELER);
		break;

	case SECTION_TYPE_IVEREINE:
		SubLevelSectionList.push_back(SECTION_TYPE_IVEREIN);
		break;

	case SECTION_TYPE_TRAINER:
	case SECTION_TYPE_EMWM:
	case SECTION_TYPE_MANAGER:
	case SECTION_TYPE_SPIELER:
	case SECTION_TYPE_STADION:
	case SECTION_TYPE_AMATEURV:
	case SECTION_TYPE_TWTRAINER:
	case SECTION_TYPE_SCHIRI:
	case SECTION_TYPE_SPONSOR:
	case SECTION_TYPE_PROMI:
	case SECTION_TYPE_REPORTER:
	case SECTION_TYPE_KRITIKER:
	case SECTION_TYPE_VPRAESID:
	case SECTION_TYPE_NATION:
	case SECTION_TYPE_IVEREIN:
	case SECTION_TYPE_CLEAGUEGRP:
	case SECTION_TYPE_TURNIERGRP:
	case SECTION_TYPE_VEREIN_HIDDEN:
	case SECTION_TYPE_AJUGEND_HIDDEN:
	case SECTION_TYPE_ASPIELER_HIDDEN:
	case SECTION_TYPE_EUROSIEGER_HIDDEN:
	case SECTION_TYPE_ISCHIRI_HIDDEN:
	case SECTION_TYPE_SPIELER_HIDDEN:
	case SECTION_TYPE_SPIEL_HIDDEN:
	case SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN:
		// No Sub Sections to add
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Type " << GetNameFromSectionType (ParentSectionType) << " -> " << __FUNCTION__;
		programError (ErrorText.str());
		break;
	}
} // GetSubLevelSections

SECTION_TYPE GetHiddenSection (SECTION_TYPE ParentLevelSection, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	SECTION_TYPE HiddenSection = SECTION_TYPE_UNKNOWN;
	
	std::stringstream ErrorText;
	switch (ParentLevelSection)
	{
	case SECTION_TYPE_VEREIN:
		HiddenSection = SECTION_TYPE_VEREIN_HIDDEN;
		break;

	case SECTION_TYPE_EXSPIEL:
		HiddenSection = SECTION_TYPE_SPIELER_HIDDEN;
		break;

	case SECTION_TYPE_AJUGEND:
		HiddenSection = SECTION_TYPE_AJUGEND_HIDDEN;
		break;

	case SECTION_TYPE_ASPIELER:
		HiddenSection = SECTION_TYPE_ASPIELER_HIDDEN;
		break;

	case SECTION_TYPE_EUROSIEGER:
		HiddenSection = SECTION_TYPE_EUROSIEGER_HIDDEN;
		break;

	case SECTION_TYPE_ISCHIRI:
		HiddenSection = SECTION_TYPE_ISCHIRI_HIDDEN;
		break;

	case SECTION_TYPE_LIGA:
		// Return the Number the Last Liga has stored for Vereine otherwise give an error as we are assuming we already have it
		if (SectionList[SECTION_TYPE_LIGA].size() >= 1)
		{
			if ((SectionList[SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN].size()) < 
				(T_StringToNumber<size_t> (std::static_pointer_cast<liga>(
				SectionList[SECTION_TYPE_LIGA].back())->GetValueAtSectionPos(LIGA_SECTION_POS_VEREINSANZAHL))))
			{
				HiddenSection = SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN;
			} // if not read all teams
			else
			{
				HiddenSection = SECTION_TYPE_SPIEL_HIDDEN;
			} // all teams read
		} // If already have a liga
		else
		{
			HiddenSection = SECTION_TYPE_UNKNOWN;
			ErrorText << "No Lige Record found in DB" << " -> " << __FUNCTION__;
			programError (ErrorText.str());
		} // 
		break;

	default:
		ErrorText << "Unexpected Section Type: " << ParentLevelSection << ": " << GetNameFromSectionType(ParentLevelSection) << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(HiddenSection);
} // GetHiddenSection

SECTION_TYPE GetDataSectionFromHiddenSection (SECTION_TYPE HiddenSection)
{
	SECTION_TYPE DataSection = SECTION_TYPE_UNKNOWN;

	switch (HiddenSection)
	{
	case SECTION_TYPE_VEREIN_HIDDEN:
		DataSection = SECTION_TYPE_VEREIN;
		break;

	case SECTION_TYPE_SPIELER_HIDDEN:
		DataSection = SECTION_TYPE_SPIELER;
		break;

	case SECTION_TYPE_AJUGEND_HIDDEN:
		DataSection = SECTION_TYPE_AJUGEND;
		break;

	case SECTION_TYPE_ASPIELER_HIDDEN:
		DataSection = SECTION_TYPE_ASPIELER;
		break;

	case SECTION_TYPE_EUROSIEGER_HIDDEN:
		DataSection = SECTION_TYPE_EUROSIEGER;
		break;

	case SECTION_TYPE_ISCHIRI_HIDDEN:
		DataSection = SECTION_TYPE_ISCHIRI;
		break;

	case SECTION_TYPE_SPIEL_HIDDEN:
		// Special case as no related section
		DataSection = SECTION_TYPE_SPIEL_HIDDEN;
		break;

	case SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN:
		// Special case as no related section
		DataSection = SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Section Type: " << HiddenSection << ": " << GetNameFromSectionType(HiddenSection) << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(DataSection);
} // GetDataSectionFromHiddenSection

int section::GetMatchingSectionsFromList (std::vector<std::shared_ptr<section>>& SectionSubList)
{
	int ChildCount = 0;
	std::string ParentId = this->GetUniqueId();
	std::vector<std::shared_ptr<section>>::iterator ChildIterator;

//std::cout << "COMPARE LIST OF SECTIONS FOR: " << GetNameFromSectionType(this->GetSectionType()) << ":::" << this->GetUniqueId() << std::endl;
	for(ChildIterator = SectionSubList.begin(); ChildIterator != SectionSubList.end(); ++ChildIterator)
	{
//std::cout << "  - Checking Child - " << (*ChildIterator)->GetUniqueId() << ", ChildParent: " << (*ChildIterator)->GetParentId() << std::endl;
		if((*ChildIterator)->SectionParentMatchesString(ParentId))
		{
			ChildCount++;
//std::cout << "    - MATCH YES - Count: " << ChildCount << std::endl;
		} // if verein matches land
	} // for each verein

	return(ChildCount);
} // GetMatchingSectionsFromList

void GetSectionsRequiredForFile (const std::string& FileName, SECTION_TYPE LevelSection, bool RequiredSectionList [NO_OF_SECTION_TYPES], 
								 bool SubLevel, bool OnlyDataSections)
{
	std::vector<SECTION_TYPE> SectionList;

	if(SubLevel)
		GetSubLevelSections (FileName, LevelSection, SectionList);
	else
		GetFollowUpSections (FileName, LevelSection, SectionList);

	// Enable each section in bool
	for (std::vector<SECTION_TYPE>::iterator Iterator = SectionList.begin(); Iterator != SectionList.end(); ++Iterator)
	{
		SECTION_TYPE TestSection = *Iterator;

		// If it is a hidden section we need to find the data section for it
		if (!SectionIsVisible(TestSection))
			TestSection = GetDataSectionFromHiddenSection(TestSection);

		if (!OnlyDataSections || SectionContainsData (TestSection))
		{
			// Add the data section
			RequiredSectionList[TestSection] = true;

			// Add all sub level sections for this sections
			GetSectionsRequiredForFile(FileName, *Iterator, RequiredSectionList, true, OnlyDataSections);

			// Add all follow up sections for this section
			GetSectionsRequiredForFile(FileName, *Iterator, RequiredSectionList, false, OnlyDataSections);
		} // if not only data sections or it contains data
	} // for each found section
} // GetSectionsRequiredForFile

bool SectionNeededForOtherSections (SECTION_TYPE SectionType)
{
	bool SectionNeededForReferences = false;

	switch (SectionType)
	{
	case SECTION_TYPE_NATION:
	case SECTION_TYPE_VEREIN:
		SectionNeededForReferences = true;

	default:
		break;
	}

	return (SectionNeededForReferences);
} // SectionNeededForOtherSections

void PrintSectionListContent (SECTION_TYPE SectionType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	std::vector<std::shared_ptr<section>> SectionVector = SectionList[SectionType];
	showTextMsg(std::string("CONTENT: ") + std::to_string(SectionList[SectionType].size()) + std::string(" Entries of Section ") + GetNameFromSectionType(SectionType));

	for(SectionIterator = SectionVector.begin(); SectionIterator != SectionVector.end(); ++SectionIterator)
	{
		std::stringstream Text;
		Text.str("");

		// print general stuff
		Text << std::setw(5) << (SectionIterator - SectionVector.begin()) << " - ID: " << (*SectionIterator)->GetUniqueId() << 
			", Land(LandInt): " << (*SectionIterator)->GetA3FileLandId_Expanded() << "(" << (*SectionIterator)->GetA3FileLandId() << ")";
		showTextMsg(Text.str());

		// Print specific stuff
		Text.str("");
		switch(SectionType)
		{
		case SECTION_TYPE_VEREIN:
			Text << "          " << "LandVereinIndex: " << std::static_pointer_cast<verein>(*SectionIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_VEREIN_LAND_INDEX) <<
				", HeimFarbe1 :" << std::static_pointer_cast<land>(*SectionIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1) <<
				", HeimMuster :" << std::static_pointer_cast<land>(*SectionIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER) <<
				", HeimStutzen :" << std::static_pointer_cast<land>(*SectionIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE) <<
				", HeimRingelsocken:" << std::static_pointer_cast<land>(*SectionIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN) <<
				", AuswaertsFarbe1:" << std::static_pointer_cast<land>(*SectionIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1) <<
				", AuswaertsMuster:" << std::static_pointer_cast<land>(*SectionIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER) <<
				", AuswaertzStutzen:" << std::static_pointer_cast<land>(*SectionIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE) <<
				", AuswaertsRingelsocken:" << std::static_pointer_cast<land>(*SectionIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN);
			break;

		case SECTION_TYPE_LAND:
			Text << "          " << "LandId: " << std::static_pointer_cast<land>(*SectionIterator)->GetValueAtSectionPos(LAND_SECTION_POS_LAND_ID) <<
				", VereinCount: " << std::static_pointer_cast<land>(*SectionIterator)->GetValueAtSectionPos(LAND_SECTION_POS_VEREINSZAHL);
			break;

		case SECTION_TYPE_NATION:
			Text << "          " << "VereinsAnzahl: " << std::static_pointer_cast<nation>(*SectionIterator)->GetValueAtSectionPos(NATION_SECTION_POS_VEREINSANZAHL);
			break;

		case SECTION_TYPE_PROMI:
			Text << "          " << "Lieblingsverein: \"" << std::static_pointer_cast<promi>(*SectionIterator)->GetValueAtSectionPos(PROMI_SECTION_POS_LIEBLINGSVEREIN_EXPANDED) << "\"-\"" <<
				std::static_pointer_cast<promi>(*SectionIterator)->GetValueAtSectionPos(PROMI_SECTION_POS_LIEBLINGSVEREIN) << "\"";
			break;

		case SECTION_TYPE_SPIELER:
			Text << "          " << "Land+Inlander: \"" << std::static_pointer_cast<spieler>(*SectionIterator)->GetValueAtSectionPos(SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER) << "\"" <<
				", Split_Land: \"" << std::static_pointer_cast<spieler>(*SectionIterator)->GetValueAtSectionPos(SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND) << "\"" <<
				", Split_Inlander: \"" << std::static_pointer_cast<spieler>(*SectionIterator)->GetValueAtSectionPos(SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_FUSSBALLINLAENDER) << "\"" <<
				", Split_Land_Expanded: \"" << std::static_pointer_cast<spieler>(*SectionIterator)->GetValueAtSectionPos(SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND_EXPANDED) << "\"";
			break;

		default:
			break;
		}
		showTextMsg(Text.str());

	} // for each section

} // PrintSectionListContent
