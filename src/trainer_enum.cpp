#include "trainer_enum.h"

#include "error_handling.h"
#include "boost/assign.hpp"
#include "bimap.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM VALUE LOOKUP MAPS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// Map for Ruf Type
const static INT_HASHBIMAP_TYPE gMap_TRAINER_ENUM_RUF = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(TRAINER_RUF_KUMPELTYP,				0)
	(TRAINER_RUF_LUSTIGER_GESELLE,		1)
	(TRAINER_RUF_MOTIVATIONSKUENSTLER,	2)
	(TRAINER_RUF_PR_MANN,				3)
	(TRAINER_RUF_SCHLEIFER,				4)
	(TRAINER_RUF_WISSENSCHAFTLER,		5)
	(TRAINER_RUF_KEINER,				6);

int GetTrainerEnumValue (int EnumType, ENUM_VALUE_SIDE_TYPE LookupSide, int EnumVal)
{
	int EnumPos = -1;

	switch((TRAINER_ENUM_TYPE) EnumType)
	{
	case TRAINER_ENUM_RUF:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_TRAINER_ENUM_RUF);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Split Field Type: " << EnumType << "(" << GetNameFromTrainerEnumType((TRAINER_ENUM_TYPE) EnumType) << ")" << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(EnumPos);
} // GetTrainerEnumValue

ENUM_VALUE_LIST& GetTrainerEnumValueList (TRAINER_ENUM_TYPE SplitField, ENUM_VALUE_LIST& ValueList)
{
	ValueList.clear();

	switch(SplitField)
	{
	case TRAINER_ENUM_RUF:
		T_GetAllBimapValues(gMap_TRAINER_ENUM_RUF, ValueList);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Split Field Type: " << SplitField << "(" << GetNameFromTrainerEnumType(SplitField) << ")" << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(ValueList);
} // GetTrainerEnumValueList

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM STRING FUNCTIONS ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

std::string GetNameFromTrainerEnumType (TRAINER_ENUM_TYPE EnumType)
{
	switch (EnumType)
	{
	case TRAINER_ENUM_RUF:
		return ("TRAINER_ENUM_RUF");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Split Field Type " << EnumType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerEnumType

std::string GetNameFromTrainerRufType (int HaarType)
{
	switch ((TRAINER_RUF_TYPE) HaarType)
	{
	case TRAINER_RUF_KUMPELTYP:
		return ("Kumpeltyp");
	case TRAINER_RUF_LUSTIGER_GESELLE:
		return ("LustigerGeselle");
	case TRAINER_RUF_MOTIVATIONSKUENSTLER:
		return ("Motivationskuenstler");
	case TRAINER_RUF_PR_MANN:
		return ("PrMann");
	case TRAINER_RUF_SCHLEIFER:
		return ("Schleifer");
	case TRAINER_RUF_WISSENSCHAFTLER:
		return ("Wissenschaftler");
	case TRAINER_RUF_KEINER:
		return ("Keiner");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << HaarType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromTrainerRufType
