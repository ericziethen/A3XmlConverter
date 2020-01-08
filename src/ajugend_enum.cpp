#include "ajugend_enum.h"

#include "error_handling.h"
#include "boost/assign.hpp"
#include "bimap.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM VALUE LOOKUP MAPS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// Map for Position Type
const static INT_HASHBIMAP_TYPE gMap_AJUGEND_ENUM_POSITION = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(AJUGEND_POSITION_TORWART,					0)
	(AJUGEND_POSITION_LIBERO,					1)
	(AJUGEND_POSITION_INNENVERTEIDIGER,			2)
	(AJUGEND_POSITION_LINKER_VERTEIDIGER,		3)
	(AJUGEND_POSITION_RECHTER_VERTEIDIGER,		4)
	(AJUGEND_POSITION_DEFENSIVES_MITTELFELD,	5)
	(AJUGEND_POSITION_LINKES_MITTELFELD,		6)
	(AJUGEND_POSITION_RECHTES_MITTELFELD,		7)
	(AJUGEND_POSITION_OFFENSIVES_MITTELFELD,	8)
	(AJUGEND_POSITION_STUERMER,					9);

int GetAjugendEnumValue (int EnumType, ENUM_VALUE_SIDE_TYPE LookupSide, int EnumVal)
{
	int EnumPos = -1;

	switch((AJUGEND_ENUM_TYPE) EnumType)
	{
	case AJUGEND_ENUM_POSITION:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_AJUGEND_ENUM_POSITION);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Split Field Type: " << EnumType << "(" << GetNameFromAjugendEnumType((AJUGEND_ENUM_TYPE) EnumType) << ")" << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(EnumPos);
} // GetAjugendEnumValue

ENUM_VALUE_LIST& GetAjugendEnumValueList (AJUGEND_ENUM_TYPE SplitField, ENUM_VALUE_LIST& ValueList)
{
	ValueList.clear();

	switch(SplitField)
	{
	case AJUGEND_ENUM_POSITION:
		T_GetAllBimapValues(gMap_AJUGEND_ENUM_POSITION, ValueList);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Split Field Type: " << SplitField << "(" << GetNameFromAjugendEnumType(SplitField) << ")" << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(ValueList);
} // GetAjugendEnumValueList

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM STRING FUNCTIONS ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

std::string GetNameFromAjugendEnumType (AJUGEND_ENUM_TYPE EnumType)
{
	switch (EnumType)
	{
	case AJUGEND_ENUM_POSITION:
		return ("AJUGEND_ENUM_POSITION");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Split Field Type " << EnumType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerEnumType

std::string GetNameFromAjugendPositionType (int HaarType)
{
	switch ((AJUGEND_POSITION_TYPE) HaarType)
	{
	case AJUGEND_POSITION_TORWART:
		return ("Torwart");
	case AJUGEND_POSITION_LIBERO:
		return ("Libero");
	case AJUGEND_POSITION_INNENVERTEIDIGER:
		return ("Innenverteidiger");
	case AJUGEND_POSITION_LINKER_VERTEIDIGER:
		return ("LinkerVerteidiger");
	case AJUGEND_POSITION_RECHTER_VERTEIDIGER:
		return ("RechterVerteidiger");
	case AJUGEND_POSITION_DEFENSIVES_MITTELFELD:
		return ("DefensivesMittelfeld");
	case AJUGEND_POSITION_LINKES_MITTELFELD:
		return ("LinkesMittelfeld");
	case AJUGEND_POSITION_RECHTES_MITTELFELD:
		return ("RechtesMittelfeld");
	case AJUGEND_POSITION_OFFENSIVES_MITTELFELD:
		return ("OffensivesMittelfeld");
	case AJUGEND_POSITION_STUERMER:
		return ("Stuermer");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << HaarType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromAjugendPositionType
