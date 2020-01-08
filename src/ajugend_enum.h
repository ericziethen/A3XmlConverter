#pragma once

#include <string>
#include "misc_lib.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUMS ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum 
{
	AJUGEND_ENUM_UNKNOWN,
	AJUGEND_ENUM_POSITION,
	NO_OF_AJUGEND_ENUM_TYPES
} AJUGEND_ENUM_TYPE;

typedef enum
{
	AJUGEND_POSITION_UNKNOWN,
	AJUGEND_POSITION_TORWART,
	AJUGEND_POSITION_LIBERO,
	AJUGEND_POSITION_INNENVERTEIDIGER,
	AJUGEND_POSITION_LINKER_VERTEIDIGER,
	AJUGEND_POSITION_RECHTER_VERTEIDIGER,
	AJUGEND_POSITION_DEFENSIVES_MITTELFELD,
	AJUGEND_POSITION_LINKES_MITTELFELD,
	AJUGEND_POSITION_RECHTES_MITTELFELD,
	AJUGEND_POSITION_OFFENSIVES_MITTELFELD,
	AJUGEND_POSITION_STUERMER,
	NO_OF_AJUGEND_POSITION_TYPES
} AJUGEND_POSITION_TYPE;

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// FUNCTION FORWARD DECLARATIONS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

ENUM_VALUE_LIST& GetAjugendEnumValueList (AJUGEND_ENUM_TYPE, ENUM_VALUE_LIST&);
int GetAjugendEnumValue (int, ENUM_VALUE_SIDE_TYPE, int);
std::string GetNameFromAjugendEnumType (AJUGEND_ENUM_TYPE);
std::string GetNameFromAjugendPositionType (int);
