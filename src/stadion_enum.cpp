#include "stadion_enum.h"

#include "error_handling.h"
#include "boost/assign.hpp"
#include "bimap.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM VALUE LOOKUP MAPS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// Map for Anzeigetafel
const static INT_HASHBIMAP_TYPE gMap_STADION_ENUM_ANZEIGETAFEL = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(STADION_ANZEIGETAFEL_KEINE_TAFEL,		0)
	(STADION_ANZEIGETAFEL_TORSCHILDER,		1)
	(STADION_ANZEIGETAFEL_KLEINE_LED_TAFEL, 2)
	(STADION_ANZEIGETAFEL_GROSSE_LED_TAFEL, 3)
	(STADION_ANZEIGETAFEL_VIDEOWAND,		4);

// Map for Tribuene
const static INT_HASHBIMAP_TYPE gMap_STADION_ENUM_TRIBUENE = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(STADION_TRIBUENE_HAUPT,	0)
	(STADION_TRIBUENE_GEGEN,	1)
	(STADION_TRIBUENE_LINKS,	2)
	(STADION_TRIBUENE_RECHTS,	3);

// Map for Zustand
const static INT_HASHBIMAP_TYPE gMap_STADION_ENUM_ZUSTAND = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(STADION_ZUSTAND_NEU,			1)
	(STADION_ZUSTAND_FAST_NEU,		2)
	(STADION_ZUSTAND_UNMODERN,		3)
	(STADION_ZUSTAND_ANGESTAUBT,	4)
	(STADION_ZUSTAND_BAUFAELLIG,	5)
	(STADION_ZUSTAND_VERMODERT,		6)
	(STADION_ZUSTAND_VERFALLEN,		7);

// Map for Dach/Waermestrahler
const static INT_HASHBIMAP_TYPE gMap_STADION_ENUM_DACH_WAERMESTRAHLER = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(STADION_DACH_WAERMESTRAHLER_KEIN,		0)
	(STADION_DACH_WAERMESTRAHLER_HAUPT,		1)
	(STADION_DACH_WAERMESTRAHLER_GEGEN,		2)
	(STADION_DACH_WAERMESTRAHLER_LINKS,		4)
	(STADION_DACH_WAERMESTRAHLER_RECHTS,	8);

// Map for Boolean Type
const static INT_BOOLEAN_MAP gMap_STADION_BOOLEAN_FIELDS = boost::assign::map_list_of 
	(STADION_BOOLEAN_AUSFAHRBARESSPIELFELD, 1)
	(STADION_BOOLEAN_AUTOBAHNANBINDUNG,		1)
	(STADION_BOOLEAN_BEHEIZBARESITZE,		1)
	(STADION_BOOLEAN_BERGE,					1)
	(STADION_BOOLEAN_BURG,					1)
	(STADION_BOOLEAN_CITYLAGE,				1)
	(STADION_BOOLEAN_FERNSEHTURM,			1)
	(STADION_BOOLEAN_FLUTLICHT,				1)
	(STADION_BOOLEAN_IMBESITZDESVEREINS,	1)
	(STADION_BOOLEAN_LAUFBAHN,				1)
	(STADION_BOOLEAN_LUXUSKABINEN,			1)
	(STADION_BOOLEAN_RASENHEIZUNG,			1)
	(STADION_BOOLEAN_SCHLOSS,				1)
	(STADION_BOOLEAN_SITZKISSEN,			1)
	(STADION_BOOLEAN_DACH_HAUPT,			1)
	(STADION_BOOLEAN_DACH_GEGEN,			2)
	(STADION_BOOLEAN_DACH_LINKS,			4)
	(STADION_BOOLEAN_DACH_RECHTS,			8)
	(STADION_BOOLEAN_WAERMESTRAHLER_HAUPT,	1)
	(STADION_BOOLEAN_WAERMESTRAHLER_GEGEN,	2)
	(STADION_BOOLEAN_WAERMESTRAHLER_LINKS,	4)
	(STADION_BOOLEAN_WAERMESTRAHLER_RECHTS, 8);

int GetValueFromStadionBooleanType (STADION_BOOLEAN_TYPE Bool)
{
	return (GetValueFromBooleanMap (Bool, gMap_STADION_BOOLEAN_FIELDS));
} // GetValueFromSpielerBooleanType

int GetStadionEnumValue (int EnumType, ENUM_VALUE_SIDE_TYPE LookupSide, int EnumVal)
{
	int EnumPos = -1;

	switch((STADION_ENUM_TYPE) EnumType)
	{
	case STADION_ENUM_ANZEIGETAFEL:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_STADION_ENUM_ANZEIGETAFEL);
		break;

	case STADION_ENUM_TRIBUENE:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_STADION_ENUM_TRIBUENE);
		break;

	case STADION_ENUM_ZUSTAND:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_STADION_ENUM_ZUSTAND);
		break;

	case STADION_ENUM_DACH_WAERMESTRAHLER:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_STADION_ENUM_DACH_WAERMESTRAHLER);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Split Field Type: " << EnumType << "(" << GetNameFromStadionEnumType((STADION_ENUM_TYPE) EnumType) << ")" << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(EnumPos);
} // GetStadionEnumValue

ENUM_VALUE_LIST& GetStadionEnumValueList (STADION_ENUM_TYPE SplitField, ENUM_VALUE_LIST& ValueList)
{
	ValueList.clear();

	switch(SplitField)
	{
	case STADION_ENUM_ANZEIGETAFEL:
		T_GetAllBimapValues<int>(gMap_STADION_ENUM_ANZEIGETAFEL, ValueList);
		break;

	case STADION_ENUM_TRIBUENE:
		T_GetAllBimapValues<int>(gMap_STADION_ENUM_TRIBUENE, ValueList);
		break;

	case STADION_ENUM_ZUSTAND:
		T_GetAllBimapValues<int>(gMap_STADION_ENUM_ZUSTAND, ValueList);
		break;

	case STADION_ENUM_DACH_WAERMESTRAHLER:
		T_GetAllBimapValues<int>(gMap_STADION_ENUM_DACH_WAERMESTRAHLER, ValueList);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Split Field Type: " << SplitField << "(" << GetNameFromStadionEnumType(SplitField) << ")" << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(ValueList);
} // GetStadionEnumValueList

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM STRING FUNCTIONS ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
std::string GetNameFromStadionBooleanType (STADION_BOOLEAN_TYPE Bool)
{
	switch (Bool)
	{
	case STADION_BOOLEAN_AUSFAHRBARESSPIELFELD:
		return ("STADION_BOOLEAN_AUSFAHRBARESSPIELFELD");

	case STADION_BOOLEAN_AUTOBAHNANBINDUNG:
		return ("STADION_BOOLEAN_AUTOBAHNANBINDUNG");

	case STADION_BOOLEAN_BEHEIZBARESITZE:
		return ("STADION_BOOLEAN_BEHEIZBARESITZE");

	case STADION_BOOLEAN_BERGE:
		return ("STADION_BOOLEAN_BERGE");

	case STADION_BOOLEAN_BURG:
		return ("STADION_BOOLEAN_BURG");

	case STADION_BOOLEAN_CITYLAGE:
		return ("STADION_BOOLEAN_CITYLAGE");

	case STADION_BOOLEAN_FERNSEHTURM:
		return ("STADION_BOOLEAN_FERNSEHTURM");

	case STADION_BOOLEAN_FLUTLICHT:
		return ("STADION_BOOLEAN_FLUTLICHT");

	case STADION_BOOLEAN_IMBESITZDESVEREINS:
		return ("STADION_BOOLEAN_IMBESITZDESVEREINS");

	case STADION_BOOLEAN_LAUFBAHN:
		return ("STADION_BOOLEAN_LAUFBAHN");

	case STADION_BOOLEAN_LUXUSKABINEN:
		return ("STADION_BOOLEAN_LUXUSKABINEN");

	case STADION_BOOLEAN_RASENHEIZUNG:
		return ("STADION_BOOLEAN_RASENHEIZUNG");

	case STADION_BOOLEAN_SCHLOSS:
		return ("STADION_BOOLEAN_SCHLOSS");

	case STADION_BOOLEAN_SITZKISSEN:
		return ("STADION_BOOLEAN_SITZKISSEN");

	case STADION_BOOLEAN_DACH_HAUPT:
		return ("STADION_BOOLEAN_DACH_HAUPT");

	case STADION_BOOLEAN_DACH_GEGEN:
		return ("STADION_BOOLEAN_DACH_GEGEN");

	case STADION_BOOLEAN_DACH_LINKS:
		return ("STADION_BOOLEAN_DACH_LINKS");

	case STADION_BOOLEAN_DACH_RECHTS:
		return ("STADION_BOOLEAN_DACH_RECHTS");

	case STADION_BOOLEAN_WAERMESTRAHLER_HAUPT:
		return ("STADION_BOOLEAN_WAERMESTRAHLER_HAUPT");

	case STADION_BOOLEAN_WAERMESTRAHLER_GEGEN:
		return ("STADION_BOOLEAN_WAERMESTRAHLER_GEGEN");

	case STADION_BOOLEAN_WAERMESTRAHLER_LINKS:
		return ("STADION_BOOLEAN_WAERMESTRAHLER_LINKS");

	case STADION_BOOLEAN_WAERMESTRAHLER_RECHTS:
		return ("STADION_BOOLEAN_WAERMESTRAHLER_RECHTS");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Bool Field: " << Bool << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return("");
	} // switch types
} // GetNameFromStadionBooleanType

std::string GetNameFromStadionEnumType (int EnumType)
{
	switch (EnumType)
	{
	case STADION_ENUM_ANZEIGETAFEL:
		return ("STADION_ENUM_FIELD_ANZEIGETAFEL");
	case STADION_ENUM_TRIBUENE:
		return ("STADION_ENUM_FIELD_TRIBUENE");
	case STADION_ENUM_ZUSTAND:
		return ("STADION_ENUM_FIELD_ZUSTAND");
	case STADION_ENUM_DACH_WAERMESTRAHLER:
		return ("STADION_ENUM_FIELD_DACH_WAERMESTRAHLER");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Split Field Type " << EnumType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromStadionEnumType

std::string GetNameFromStadionAnzeigetafelType (int AnzeigetafelType)
{
	switch (AnzeigetafelType)
	{
	case STADION_ANZEIGETAFEL_KEINE_TAFEL:
		return ("KeineTafel");
	case STADION_ANZEIGETAFEL_TORSCHILDER:
		return ("Torschilder");
	case STADION_ANZEIGETAFEL_KLEINE_LED_TAFEL:
		return ("KleineLedTafel");
	case STADION_ANZEIGETAFEL_GROSSE_LED_TAFEL:
		return ("GrosseLedTafel");
	case STADION_ANZEIGETAFEL_VIDEOWAND:
		return ("Videowand");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Split Field Type " << AnzeigetafelType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromStadionAnzeigetafelType

std::string GetNameFromStadionTribueneType (int TribueneType)
{
	switch (TribueneType)
	{
	case STADION_TRIBUENE_HAUPT:
		return ("Haupt");
	case STADION_TRIBUENE_GEGEN:
		return ("Gegen");
	case STADION_TRIBUENE_LINKS:
		return ("Links");
	case STADION_TRIBUENE_RECHTS:
		return ("Rechts");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Split Field Type " << TribueneType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromStadionTribueneType

std::string GetNameFromStadionZustandType (int ZustandType)
{
	switch (ZustandType)
	{
	case STADION_ZUSTAND_NEU:
		return ("Neu");
	case STADION_ZUSTAND_FAST_NEU:
		return ("FastNeu");
	case STADION_ZUSTAND_UNMODERN:
		return ("Unmodern");
	case STADION_ZUSTAND_ANGESTAUBT:
		return ("Angestaubt");
	case STADION_ZUSTAND_BAUFAELLIG:
		return ("Baufaellig");
	case STADION_ZUSTAND_VERMODERT:
		return ("Vermodert");
	case STADION_ZUSTAND_VERFALLEN:
		return ("Verfallen");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Split Field Type " << ZustandType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromStadionZustandType

std::string GetNameFromStadionDachWaermestrahlerType (int DachWaermestrahlerType)
{
	switch (DachWaermestrahlerType)
	{
	case STADION_DACH_WAERMESTRAHLER_KEIN:
		return ("Kein");
	case STADION_DACH_WAERMESTRAHLER_HAUPT:
		return ("Haupt");
	case STADION_DACH_WAERMESTRAHLER_GEGEN:
		return ("Gegen");
	case STADION_DACH_WAERMESTRAHLER_LINKS:
		return ("Links");
	case STADION_DACH_WAERMESTRAHLER_RECHTS:
		return ("Rechts");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Split Field Type " << DachWaermestrahlerType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} //  GetNameFromStadionDachWaermestrahlerType
