#include "reporter_enum.h"

#include "error_handling.h"
#include "boost/assign.hpp"
#include "bimap.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM VALUE LOOKUP MAPS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// Map for BoeseLieb Type
const static INT_HASHBIMAP_TYPE gMap_REPORTER_ENUM_BOESE_LIEB = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(REPORTER_BOESE_LIEB_BOESE,		0)
	(REPORTER_BOESE_LIEB_NEUTRAL,	1)
	(REPORTER_BOESE_LIEB_LIEB,		2);

int GetReporterEnumValue (int EnumType, ENUM_VALUE_SIDE_TYPE LookupSide, int EnumVal)
{
	int EnumPos = -1;

	switch((REPORTER_ENUM_TYPE) EnumType)
	{
	case REPORTER_ENUM_BOESE_LIEB:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_REPORTER_ENUM_BOESE_LIEB);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Split Field Type: " << EnumType << "(" << GetNameFromReporterEnumType((REPORTER_ENUM_TYPE) EnumType) << ")" << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(EnumPos);
} // GetReporterEnumValue

ENUM_VALUE_LIST& GetReporterEnumValueList (REPORTER_ENUM_TYPE SplitField, ENUM_VALUE_LIST& ValueList)
{
	ValueList.clear();

	switch(SplitField)
	{
	case REPORTER_ENUM_BOESE_LIEB:
		T_GetAllBimapValues(gMap_REPORTER_ENUM_BOESE_LIEB, ValueList);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Split Field Type: " << SplitField << "(" << GetNameFromReporterEnumType(SplitField) << ")" << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(ValueList);
} // GetReporterEnumValueList

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM STRING FUNCTIONS ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

std::string GetNameFromReporterEnumType (REPORTER_ENUM_TYPE EnumType)
{
	switch (EnumType)
	{
	case REPORTER_ENUM_BOESE_LIEB:
		return ("REPORTER_ENUM_BOESE_LIEB");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Split Field Type " << EnumType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerEnumType

std::string GetNameFromReporterBoeseLiebType (int HaarType)
{
	switch ((REPORTER_BOESE_LIEB_TYPE) HaarType)
	{
	case REPORTER_BOESE_LIEB_BOESE:
		return ("Boese");
	case REPORTER_BOESE_LIEB_NEUTRAL:
		return ("Neutral");
	case REPORTER_BOESE_LIEB_LIEB:
		return ("Lieb");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << HaarType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromReporterBoeseLiebType
