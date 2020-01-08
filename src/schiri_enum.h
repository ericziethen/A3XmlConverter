#pragma once

#include <string>
#include "misc_lib.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUMS ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum 
{
	SCHIRI_ENUM_UNKNOWN,
	SCHIRI_ENUM_EIGENSCHAFTEN_UND_HEIM_GAST,
	NO_OF_SCHIRI_ENUM_TYPE_TYPES
} SCHIRI_ENUM_TYPE;

typedef enum
{
	SCHIRI_BOOLEAN_UNKNOWN,
	SCHIRI_BOOLEAN_HEIMSCHIEDSRICHTER,
	SCHIRI_BOOLEAN_GASTSCHIEDSRICHTER,
	SCHIRI_BOOLEAN_HASST_MECKERN,
	SCHIRI_BOOLEAN_HASST_ZEITSPIEL,
	SCHIRI_BOOLEAN_HASST_COACHING,
	NO_OF_SCHIRI_BOOLEAN_TYPES
} SCHIRI_BOOLEAN_TYPE;

typedef enum 
{
	SCHIRI_EIGENSCHAFTEN_UNKNOWN,
	SCHIRI_EIGENSCHAFTEN_HEIMSCHIEDSRICHTER,
	SCHIRI_EIGENSCHAFTEN_GASTSCHIEDSRICHTER,
	SCHIRI_EIGENSCHAFTEN_HASST_MECKERN,
	SCHIRI_EIGENSCHAFTEN_HASST_ZEITSPIEL,
	SCHIRI_EIGENSCHAFTEN_HASST_COACHING,
	NO_OF_SCHIRI_EIGENSCHAFTEN_TYPES
} SCHIRI_EIGENSCHAFTEN_TYPE;

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// FUNCTION FORWARD DECLARATIONS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

ENUM_VALUE_LIST& GetEnumValueList (SCHIRI_ENUM_TYPE, ENUM_VALUE_LIST&);
std::string GetNameFromSchiriEnumType (SCHIRI_ENUM_TYPE);
std::string GetNameFromSchiriEigenschaftenType (SCHIRI_EIGENSCHAFTEN_TYPE);

int GetValueFromSchiriBooleanType (SCHIRI_BOOLEAN_TYPE);
std::string GetNameFromSchiriBooleanType (SCHIRI_BOOLEAN_TYPE);
