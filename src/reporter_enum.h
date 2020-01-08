#pragma once

#include <string>
#include "misc_lib.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUMS ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum 
{
	REPORTER_ENUM_UNKNOWN,
	REPORTER_ENUM_BOESE_LIEB,
	NO_OF_REPORTER_ENUM_TYPES
} REPORTER_ENUM_TYPE;

typedef enum
{
	REPORTER_BOESE_LIEB_UNKNOWN,
	REPORTER_BOESE_LIEB_BOESE,
	REPORTER_BOESE_LIEB_NEUTRAL,
	REPORTER_BOESE_LIEB_LIEB,
	NO_OF_REPORTER_BOESE_LIEB_TYPES
} REPORTER_BOESE_LIEB_TYPE;

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// FUNCTION FORWARD DECLARATIONS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

ENUM_VALUE_LIST& GetReporterEnumValueList (REPORTER_ENUM_TYPE, ENUM_VALUE_LIST&);
int GetReporterEnumValue (int, ENUM_VALUE_SIDE_TYPE, int);
std::string GetNameFromReporterEnumType (REPORTER_ENUM_TYPE);
std::string GetNameFromReporterBoeseLiebType (int);