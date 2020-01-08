#include "schiri_enum.h"

#include "error_handling.h"
#include "boost/assign.hpp"
#include "bimap.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM VALUE LOOKUP MAPS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// Map for Heim und Gast Schiri
const static INT_HASHBIMAP_TYPE gMap_SCHIRI_ENUM_HEIM_GAST = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SCHIRI_EIGENSCHAFTEN_HEIMSCHIEDSRICHTER,	1)
	(SCHIRI_EIGENSCHAFTEN_GASTSCHIEDSRICHTER,	2);

// Map for Eigenschaften Type
const static INT_HASHBIMAP_TYPE gMap_SCHIRI_ENUM_EIGENSCHAFTEN = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SCHIRI_EIGENSCHAFTEN_HASST_MECKERN,		4)
	(SCHIRI_EIGENSCHAFTEN_HASST_ZEITSPIEL,		8)
	(SCHIRI_EIGENSCHAFTEN_HASST_COACHING,		16);

// Map for Boolean Type
const static INT_BOOLEAN_MAP gMap_SCHIRI_BOOLEAN_FIELDS = boost::assign::map_list_of 
	(SCHIRI_BOOLEAN_HEIMSCHIEDSRICHTER, 1)
	(SCHIRI_BOOLEAN_GASTSCHIEDSRICHTER, 2)
	(SCHIRI_BOOLEAN_HASST_MECKERN,		4)
	(SCHIRI_BOOLEAN_HASST_ZEITSPIEL,	8)
	(SCHIRI_BOOLEAN_HASST_COACHING,		16);

int GetValueFromSchiriBooleanType (SCHIRI_BOOLEAN_TYPE Bool)
{
	return (GetValueFromBooleanMap (Bool, gMap_SCHIRI_BOOLEAN_FIELDS));
} // GetValueFromSpielerBooleanType

ENUM_VALUE_LIST& GetEnumValueList (SCHIRI_ENUM_TYPE SplitField, ENUM_VALUE_LIST& ValueList)
{
	ValueList.clear();

	switch(SplitField)
	{
	case SCHIRI_ENUM_EIGENSCHAFTEN_UND_HEIM_GAST:
		T_GetAllBimapValues(gMap_SCHIRI_ENUM_HEIM_GAST, ValueList);
		T_GetAllBimapValues(gMap_SCHIRI_ENUM_EIGENSCHAFTEN, ValueList);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Split Field Type: " << SplitField << "(" << GetNameFromSchiriEnumType(SplitField) << ")" << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(ValueList);
} // GetEnumValueList

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM STRING FUNCTIONS ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

std::string GetNameFromSchiriBooleanType (SCHIRI_BOOLEAN_TYPE Bool)
{
	switch (Bool)
	{
	case SCHIRI_BOOLEAN_HEIMSCHIEDSRICHTER:
		return("SCHIRI_BOOLEAN_HEIMSCHIEDSRICHTER");
	case SCHIRI_BOOLEAN_GASTSCHIEDSRICHTER:
		return("SCHIRI_BOOLEAN_GASTSCHIEDSRICHTER");
	case SCHIRI_BOOLEAN_HASST_MECKERN:
		return("SCHIRI_BOOLEAN_HASST_MECKERN");
	case SCHIRI_BOOLEAN_HASST_ZEITSPIEL:
		return("SCHIRI_BOOLEAN_HASST_ZEITSPIEL");
	case SCHIRI_BOOLEAN_HASST_COACHING:
		return("SCHIRI_BOOLEAN_HASST_COACHING");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Bool Field: " << Bool << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return("");
	} // switch types
} // GetNameFromSchiriBooleanType

std::string GetNameFromSchiriEnumType (SCHIRI_ENUM_TYPE SchiriEnumType)
{
	switch (SchiriEnumType)
	{
	case SCHIRI_ENUM_EIGENSCHAFTEN_UND_HEIM_GAST:
		return ("SCHIRI_ENUM_FIELD_EIGENSCHAFTEN");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << SchiriEnumType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSchiriEnumType

std::string GetNameFromSchiriEigenschaftenType (SCHIRI_EIGENSCHAFTEN_TYPE SchiriEigenschaftenType)
{
	switch (SchiriEigenschaftenType)
	{
	case SCHIRI_EIGENSCHAFTEN_HEIMSCHIEDSRICHTER:
		return ("Heimschiedsrichter");
	case SCHIRI_EIGENSCHAFTEN_GASTSCHIEDSRICHTER:
		return ("Gastschiedsrichter");
	case SCHIRI_EIGENSCHAFTEN_HASST_MECKERN:
		return ("HasstMeckern");
	case SCHIRI_EIGENSCHAFTEN_HASST_ZEITSPIEL:
		return ("HasstZeitspiel");
	case SCHIRI_EIGENSCHAFTEN_HASST_COACHING:
		return ("HasstCoaching");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << SchiriEigenschaftenType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSchiriEigenschaftenType
