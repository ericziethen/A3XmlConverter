#include "misc_lib.h"

#include <sstream>
#include <iostream>
#include <cctype>
#include <algorithm>

#define ENUM_NOT_FOUND_VAL -1

int StringToEnum (const std::string& EnumString, int MinBorder, int MaxBorder, ENUM_FUNC EnumToStringFunc)
{
	int FoundEnumVal = ENUM_NOT_FOUND_VAL;

//std::cout << __FUNCTION__ << " - Min:Max:String -> " << MinBorder << "::" << MaxBorder << "::" << EnumString << std::endl;
	for (int EnumVal = MinBorder + 1; (EnumVal < MaxBorder) && (FoundEnumVal == ENUM_NOT_FOUND_VAL); EnumVal++)
	{
//std::cout << "  COMPARING: Val:String -> " << EnumToStringFunc(EnumVal) << "::" << EnumString << std::endl;
		if (EnumToStringFunc(EnumVal).compare(EnumString) == 0)
		{
			FoundEnumVal = EnumVal;
		}
	} // for each possible val

	// FOR NOW GIVE AN ERROR IF WE CANNOT FIND THE ENUM
	if (FoundEnumVal == ENUM_NOT_FOUND_VAL)
	{
		std::stringstream ErrorText;
		ErrorText << "Cannot Find String from " << EnumString;
		programError (ErrorText.str());
	}

	return (FoundEnumVal);
} // StringToEnum

std::string GetNameFromBooleanType (int Boolean)
{
	switch ((BOOLEAN_TYPE) Boolean)
	{
	case BOOLEAN_NO:
		return ("Nein");
	case BOOLEAN_YES:
		return ("Ja");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << Boolean << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
	break;
	} // switch types
} // GetNameFromBooleanType

bool isPrefix (const std::string& a, const std::string& b) 
{
	if (a.empty() || b.empty())
	{
		return(false);
	} // if either string is empty it is not a prefix
	else if (a.size() > b.size()) 
	{
		return a.substr(0,b.size()) == b;
	}
	else 
	{
		return b.substr(0,a.size()) == a;
	}
} /* isPrefix */

void AddFieldValueEntryToList (std::vector<FIELD_VALUE_STRUCT>& ValueList, const std::string& EnumString)
{
	FIELD_VALUE_STRUCT FieldValue;
	FieldValue.EnumNameString = EnumString;

	ValueList.push_back(FieldValue);
} // AddFieldValueEntryToList

void AddFieldValuesForLastEntry (std::vector<FIELD_VALUE_STRUCT>& ValueList, int EnumLow, int EnumHigh, ENUM_FUNC EnumFunc)
{
	for(int EnumVal = EnumLow + 1; EnumVal < EnumHigh; EnumVal++)
	{
		ValueList.back().AllowedValueList.push_back(EnumFunc(EnumVal));
	} // for each enum val
} // AddFieldValue

int GetValueFromBooleanMap (int LeftVal, const INT_BOOLEAN_MAP& Map)
{
	int	FoundVal = -1;
	INT_BOOLEAN_MAP::const_iterator FoundIter = Map.find (LeftVal);

	if ( FoundIter == Map.end())
	{
		std::stringstream ErrorText;
		ErrorText << "No Value found for index \"" << LeftVal << " -> " << __FUNCTION__;
		programError (ErrorText.str());
	}
	else
	{
		FoundVal = FoundIter->second;
	}

	return (FoundVal);
} // GetValueFromBooleanMap

// copied from http://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool StringIsNumber (const std::string& TestString)
{
	return !TestString.empty() && std::find_if(TestString.begin(), 
		TestString.end(), [](char c) { return !std::isdigit(c); }) == TestString.end();
} // StringIsNumber

void GetBooleanEnumDetails (ENUM_FUNC& EnumFunc, int& EnumLow, int& EnumHigh)
{
	EnumFunc = GetNameFromBooleanType;
	EnumLow = BOOLEAN_UNKNOWN;
	EnumHigh = NO_OF_BOOLEAN_TYPES;
} // GetBooleanEnumDetails
