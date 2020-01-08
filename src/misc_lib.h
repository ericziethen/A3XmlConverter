#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <memory>

#include "error_handling.h"
#include "enum_value.h"

#include <functional>
#include <unordered_map>

#define DEBUG_ENABLED 0

#define BITMASK_VALUE_NONE 0

#define MAX_ALLOWED_FIELD_VALUES	100

typedef std::vector<std::shared_ptr<enum_value>> ENUM_VALUE_LIST;
typedef std::unordered_map<int, int> INT_BOOLEAN_MAP;
typedef std::function<std::string(int)> ENUM_FUNC;
typedef std::function<void(int, int, ENUM_FUNC&, int&, int&)> ENUM_DETAILS_LOOKUP_FUNC;

typedef enum
{
	BOOLEAN_UNKNOWN,
	BOOLEAN_NO,
	BOOLEAN_YES,
	NO_OF_BOOLEAN_TYPES
} BOOLEAN_TYPE;
#define BOOLEAN_NO_VALUE	0

typedef enum
{
	FIELD_TYPE_UNKNOWN,
	FIELD_TYPE_ENUM,
	FIELD_TYPE_BITMASK,
	FIELD_TYPE_BOOLEAN,
	NO_OF_FIELD_TYPE_TYPES
} FIELD_TYPE_TYPE;

typedef struct 
{
	std::string					EnumNameString;
	std::vector<std::string>	AllowedValueList;
} FIELD_VALUE_STRUCT;

int StringToEnum (const std::string&, int, int, std::function<std::string(int)>);
std::string GetNameFromBooleanType (int);
bool isPrefix (const std::string&, const std::string&);
void AddFieldValueEntryToList (std::vector<FIELD_VALUE_STRUCT>&, const std::string&);
void AddFieldValuesForLastEntry (std::vector<FIELD_VALUE_STRUCT>&, int, int, ENUM_FUNC);
int GetValueFromBooleanMap (int, const INT_BOOLEAN_MAP&);
bool StringIsNumber (const std::string&);
void GetBooleanEnumDetails (ENUM_FUNC&, int&, int&);

///////////////////////////////////////////
//// TEMPLATES ////////////////////////////
///////////////////////////////////////////

template <typename T> T T_StringToNumber (const std::string &Text)//Text not by const reference so that the function can be used with a character array as argument
{
	std::stringstream StringStream(Text);
	T Result;

	if (!(StringStream >> Result))//give the value to Result using the characters in the string
	{
		Result = 0;
		std::stringstream ErrorText;
		ErrorText << "Error converting string (" << Text << ") to " << typeid(T).name() << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return (Result);
}

template <typename T> std::string T_IncrementStringNumber (std::string &NumberString, T Increment)
{
	// Get the number from the string
	T Number = T_StringToNumber<T>(NumberString);

	// Increment the Number
	Number += Increment;

	// Write the String
	NumberString = std::to_string(Number);
	
	return (NumberString);
} // T_IncrementStringNumber

