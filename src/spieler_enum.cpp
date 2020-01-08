#include "spieler_enum.h"

#include "error_handling.h"
#include "boost/assign.hpp"
#include "bimap.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM VALUE LOOKUP MAPS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// Map for Haar Type
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_HAAR = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_HAAR_EXTREM_KURZ,	0)
	(SPIELER_HAAR_KURZ,			65536)
	(SPIELER_HAAR_WUSCHELKOPF,	131072)
	(SPIELER_HAAR_LANG,			196608);

// Map for Bart Type
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_BART = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_BART_KEIN,			0)
	(SPIELER_BART_UNRASIERT,	1)
	(SPIELER_BART_BART,			2)
	(SPIELER_BART_SCHNURBART,	4)
	(SPIELER_BART_ZIEGENBART,	8);

// Map for Nationalspieler Type
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_NATIONALSPIELER_UND_RUECKTRITT = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_NATIONALSPIELER_UND_RUECKTRITT_NEIN,						0)
	(SPIELER_NATIONALSPIELER_UND_RUECKTRITT_IST_NATIONALSPIELER,		1)
	(SPIELER_NATIONALSPIELER_UND_RUECKTRITT_RUECKTRITT,					2);

// Map for Fussballinlaender Type
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_FUSSBALLINLAENDER = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_FUSSBALLINLAENDER_NEIN,	0)
	(SPIELER_FUSSBALLINLAENDER_JA,		128);

// Map for Spielereigenschaften
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_EIGENSCHAFTEN = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_EIGENSCHAFTEN_KEINE,					0)
	(SPIELER_EIGENSCHAFTEN_KAEMPFERNATUR,			2)
	(SPIELER_EIGENSCHAFTEN_TRAININGSWELTMEISTER,	4)
	(SPIELER_EIGENSCHAFTEN_TRAININGSFAULERSPIELER,	8)
	(SPIELER_EIGENSCHAFTEN_TRETER,					16)
	(SPIELER_EIGENSCHAFTEN_FAIRERSPIELER,			32)
	(SPIELER_EIGENSCHAFTEN_MIMOSE,					64)
	(SPIELER_EIGENSCHAFTEN_SCHLITZOHR,				128)
	(SPIELER_EIGENSCHAFTEN_SPEZIALIST,				256)
	(SPIELER_EIGENSCHAFTEN_ALLROUNDER,				512)
	(SPIELER_EIGENSCHAFTEN_FLEXIBLERSPIELER,		1024)
	(SPIELER_EIGENSCHAFTEN_SCHIRILIEBLING,			2048)
	(SPIELER_EIGENSCHAFTEN_HEIMSPIELER,				4096)
	(SPIELER_EIGENSCHAFTEN_SCHOENWETTERFUSSBALLER,	8192)
	(SPIELER_EIGENSCHAFTEN_JOKER,					16384)
	(SPIELER_EIGENSCHAFTEN_EGOIST,					32768)
	(SPIELER_EIGENSCHAFTEN_BRUDERLEICHTFUSS,		65536);

// Map for Torwartfaehigkeiten
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_TORWARTFAEHIGKEITEN = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_TORWARTFAEHIGKEITEN_KEINE,				0)
	(SPIELER_TORWARTFAEHIGKEITEN_ELFMETERTOETER,	2)
	(SPIELER_TORWARTFAEHIGKEITEN_STARKE_REFLEXE,	4)
	(SPIELER_TORWARTFAEHIGKEITEN_HERAUSLAUFEN,		8)
	(SPIELER_TORWARTFAEHIGKEITEN_FLANKEN,			16)
	(SPIELER_TORWARTFAEHIGKEITEN_FAUSTEN,			32)
	(SPIELER_TORWARTFAEHIGKEITEN_BALLSICHERHEIT,	64)
	(SPIELER_TORWARTFAEHIGKEITEN_SCHNELLIGKEIT,		128)
	(SPIELER_TORWARTFAEHIGKEITEN_WEITE_ABSCHLAEGE,	256)
	(SPIELER_TORWARTFAEHIGKEITEN_WEITE_ABWUERFE,	512);

// Map for Spielerfaehigkeiten
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_SPIELERFAEHIGKEITEN = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_SPIELERFAEHIGKEITEN_KEINE,				0)
	(SPIELER_SPIELERFAEHIGKEITEN_KOPFBALL,			2)
	(SPIELER_SPIELERFAEHIGKEITEN_ZWEIKAMPF,			4)
	(SPIELER_SPIELERFAEHIGKEITEN_SCHNELLIGKEIT,		8)
	(SPIELER_SPIELERFAEHIGKEITEN_SCHUSSKRAFT,		16)
	(SPIELER_SPIELERFAEHIGKEITEN_ELFMETER,			32)
	(SPIELER_SPIELERFAEHIGKEITEN_FREISTOESSE,		64)
	(SPIELER_SPIELERFAEHIGKEITEN_FLANKEN,			128)
	(SPIELER_SPIELERFAEHIGKEITEN_TORINSTINKT,		256)
	(SPIELER_SPIELERFAEHIGKEITEN_LAUFSTAREKE,		512)
	(SPIELER_SPIELERFAEHIGKEITEN_TECHNICK,			1024)
	(SPIELER_SPIELERFAEHIGKEITEN_BALLZAUBERER,		2048)
	(SPIELER_SPIELERFAEHIGKEITEN_SPIELMACHER,		4096)
	(SPIELER_SPIELERFAEHIGKEITEN_VIERERKETTE,		8192)
	(SPIELER_SPIELERFAEHIGKEITEN_SPIELUEBERSICHT,	16384)
	(SPIELER_SPIELERFAEHIGKEITEN_BALL_HALTEN,		32768)
	(SPIELER_SPIELERFAEHIGKEITEN_DRIBBLING,			65536);

// Map for Spielerfaehigkeiten
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_CHARAKTER = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_CHARAKTER_KEINE,				0)
	(SPIELER_CHARAKTER_FUEHRUNGSPERSON,		2)
	(SPIELER_CHARAKTER_HITZKOPF,			4)
	(SPIELER_CHARAKTER_FROHNATUR,			8)
	(SPIELER_CHARAKTER_MANNOHNENERVEN,		16)
	(SPIELER_CHARAKTER_NERVENBUENDEL,		32)
	(SPIELER_CHARAKTER_PHLEGMATIKER,		64)
	(SPIELER_CHARAKTER_GELDGEIER,			128)
	(SPIELER_CHARAKTER_VEREINSANHAENGER,	256)
	(SPIELER_CHARAKTER_MUSTERPROFI,			512)
	(SPIELER_CHARAKTER_SKANDALNUDEL,		1024)
	(SPIELER_CHARAKTER_SENSIBELCHEN,		2048)
	(SPIELER_CHARAKTER_STARALUEREN,			4096)
	(SPIELER_CHARAKTER_TEENIE_STAR,			8192)
	(SPIELER_CHARAKTER_UNRUHESTIFTER,		16384)
	(SPIELER_CHARAKTER_LEBERWURST,			32768)
	(SPIELER_CHARAKTER_INTEGRATIONSFIGUR,	65536);

// Map for Hautfarbe
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_HAUTFARBE = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_HAUTFARBE_HELL,		0)
	(SPIELER_HAUTFARBE_DUNKEL,		1)
	(SPIELER_HAUTFARBE_SCHWARZ,		2)
	(SPIELER_HAUTFARBE_ASIATISCH,	3);

// Map for Haarfarbe
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_HAARFARBE = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_HAARFARBE_HELLBLOND,	0)
	(SPIELER_HAARFARBE_BLOND,		1)
	(SPIELER_HAARFARBE_BRAUN,		2)
	(SPIELER_HAARFARBE_ROT,			3)
	(SPIELER_HAARFARBE_SCHWARZ,		4)
	(SPIELER_HAARFARBE_GLATZE,		5)
	(SPIELER_HAARFARBE_GRAU,		6);

// Map for Position
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_POSITION = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_POSITION_KEINE,				0)
	(SPIELER_POSITION_TORWART,				1)
	(SPIELER_POSITION_LIBERO,				2)
	(SPIELER_POSITION_INNENVERTEIDIGER,		3)
	(SPIELER_POSITION_LINKERVERTEIDIGER,	4)
	(SPIELER_POSITION_RECHTERVERTEIDIGER,	5)
	(SPIELER_POSITION_DEFENSIVESMITTELFELD, 6)
	(SPIELER_POSITION_LINKESMITTELFELD,		7)
	(SPIELER_POSITION_RECHTESMITTELFELD,	8)
	(SPIELER_POSITION_OFFENSIVESMITTELFELD, 9)
	(SPIELER_POSITION_STUERMER,				10);

// Map for Fuss
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_FUSS = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_FUSS_RECHTS,	1)
	(SPIELER_FUSS_LINKS,	2)
	(SPIELER_FUSS_BEIDE,	3);

// Map for Talent
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_TALENT = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_TALENT_MEGATALENT,			1)
	(SPIELER_TALENT_TALENT,				2)
	(SPIELER_TALENT_NORMAL,				3)
	(SPIELER_TALENT_WENIGBEGABT,		4)
	(SPIELER_TALENT_ZWEILINKEFUESSE,	5);

// Map for Gesundheit
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_GESUNDHEIT = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_GESUNDHEIT_NORMAL,				1)
	(SPIELER_GESUNDHEIT_ROBUST,				2)
	(SPIELER_GESUNDHEIT_ANFAELLIG,			3)
	(SPIELER_GESUNDHEIT_KNIEPROBLEME,		4)
	(SPIELER_GESUNDHEIT_SCHNELLWIEDERFIT,	5)
	(SPIELER_GESUNDHEIT_DAUERTBISWIEDERFIT, 6)
	(SPIELER_GESUNDHEIT_WEHLEIDIG,			7);

// Map for Publikum
const static INT_HASHBIMAP_TYPE gMap_SPIELER_ENUM_PUBLIKUM = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_PUBLIKUM_NORMAL,		1)
	(SPIELER_PUBLIKUM_LIEBLING,		2)
	(SPIELER_PUBLIKUM_HASSFIGUR,	3);

// Map for Boolean Type
const static INT_BOOLEAN_MAP gMap_SPIELER_BOOLEAN_FIELDS = boost::assign::map_list_of 
	(SPIELER_BOOLEAN_HAT_KUENSTLERNAHME,			1)
	(SPIELER_BOOLEAN_KAPITAEN_RUECKTRITT,			1)
	(SPIELER_BOOLEAN_IST_NATIONALSPIELER,			1)
	(SPIELER_BOOLEAN_NATIONALSPIELER_RUECKTRITT,	2)
	(SPIELER_BOOLEAN_BART_UNRASIERT,				1)
	(SPIELER_BOOLEAN_BART_BART,						2)
	(SPIELER_BOOLEAN_BART_SCHNURBART,				4)
	(SPIELER_BOOLEAN_BART_ZIEGENBART,				8)
	(SPIELER_BOOLEAN_FUSSBALLINLAENDER,				128);

int GetValueFromSpielerBooleanType (SPIELER_BOOLEAN_TYPE Bool)
{
	return (GetValueFromBooleanMap (Bool, gMap_SPIELER_BOOLEAN_FIELDS));
} // GetValueFromSpielerBooleanType

int GetSpielerEnumValue (int EnumType, ENUM_VALUE_SIDE_TYPE LookupSide, int EnumVal)
{
	int EnumPos = -1;

	switch(EnumType)
	{
	case SPIELER_ENUM_FUSSBALLINLAENDER:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_FUSSBALLINLAENDER);
		break;

	case SPIELER_ENUM_NATIONALSPIELER_UND_RUECKTRITT:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_NATIONALSPIELER_UND_RUECKTRITT);
		break;

	case SPIELER_ENUM_HAAR:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_HAAR);
		break;

	case SPIELER_ENUM_BART:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_BART);
		break;

	case SPIELER_ENUM_EIGENSCHAFTEN:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_EIGENSCHAFTEN);
		break;

	case SPIELER_ENUM_TORWARTFAEHIGKEITEN:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_TORWARTFAEHIGKEITEN);
		break;

	case SPIELER_ENUM_SPIELERFAEHIGKEITEN:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_SPIELERFAEHIGKEITEN);
		break;

	case SPIELER_ENUM_CHARAKTER:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_CHARAKTER);
		break;

	case SPIELER_ENUM_HAUTFARBE:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_HAUTFARBE);
		break;

	case SPIELER_ENUM_HAARFARBE:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_HAARFARBE);
		break;

	case SPIELER_ENUM_POSITION:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_POSITION);
		break;

	case SPIELER_ENUM_FUSS:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_FUSS);
		break;

	case SPIELER_ENUM_TALENT:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_TALENT);
		break;

	case SPIELER_ENUM_GESUNDHEIT:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_GESUNDHEIT);
		break;

	case SPIELER_ENUM_PUBLIKUM:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_SPIELER_ENUM_PUBLIKUM);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Split Field Type: " << EnumType << "(" << GetNameFromSpielerEnumType((SPIELER_ENUM_TYPE) EnumType) << ")" << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(EnumPos);
} // GetSpielerEnumValue

ENUM_VALUE_LIST& GetSpielerEnumValueList (SPIELER_ENUM_TYPE SplitField, ENUM_VALUE_LIST& ValueList)
{
	ValueList.clear();

	switch(SplitField)
	{
	case SPIELER_ENUM_FUSSBALLINLAENDER:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_FUSSBALLINLAENDER, ValueList);
		break;

	case SPIELER_ENUM_NATIONALSPIELER_UND_RUECKTRITT:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_NATIONALSPIELER_UND_RUECKTRITT, ValueList);
		break;

	case SPIELER_ENUM_HAAR:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_HAAR, ValueList);
		break;

	case SPIELER_ENUM_BART:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_BART, ValueList);
		break;

	case SPIELER_ENUM_EIGENSCHAFTEN:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_EIGENSCHAFTEN, ValueList);
		break;

	case SPIELER_ENUM_TORWARTFAEHIGKEITEN:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_TORWARTFAEHIGKEITEN, ValueList);
		break;

	case SPIELER_ENUM_SPIELERFAEHIGKEITEN:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_SPIELERFAEHIGKEITEN, ValueList);
		break;

	case SPIELER_ENUM_CHARAKTER:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_CHARAKTER, ValueList);
		break;
			
	case SPIELER_ENUM_HAUTFARBE:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_HAUTFARBE, ValueList);
		break;

	case SPIELER_ENUM_HAARFARBE:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_HAARFARBE, ValueList);
		break;

	case SPIELER_ENUM_POSITION:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_POSITION, ValueList);
		break;

	case SPIELER_ENUM_FUSS:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_FUSS, ValueList);
		break;

	case SPIELER_ENUM_TALENT:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_TALENT, ValueList);
		break;

	case SPIELER_ENUM_GESUNDHEIT:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_GESUNDHEIT, ValueList);
		break;

	case SPIELER_ENUM_PUBLIKUM:
		T_GetAllBimapValues(gMap_SPIELER_ENUM_PUBLIKUM, ValueList);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Split Field Type: " << SplitField << "(" << GetNameFromSpielerEnumType(SplitField) << ")" << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(ValueList);
} // GetSpielerEnumValueList

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM STRING FUNCTIONS ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

std::string GetNameFromSpielerBooleanType (SPIELER_BOOLEAN_TYPE Bool)
{
	switch (Bool)
	{
	case SPIELER_BOOLEAN_HAT_KUENSTLERNAHME:
		return ("HatKuenstlernahme");

	case SPIELER_BOOLEAN_KAPITAEN_RUECKTRITT:
		return ("KapitaenRuecktritt");

	case SPIELER_BOOLEAN_IST_NATIONALSPIELER:
		return ("IstNationalspieler");

	case SPIELER_BOOLEAN_NATIONALSPIELER_RUECKTRITT:
		return ("NationalspielerRuecktritt");

	case SPIELER_BOOLEAN_BART_UNRASIERT:
		return ("Unrasiert");

	case SPIELER_BOOLEAN_BART_BART:
		return ("Bart");

	case SPIELER_BOOLEAN_BART_SCHNURBART:
		return ("Schnurbart");

	case SPIELER_BOOLEAN_BART_ZIEGENBART:
		return ("Ziegenbart");

	case SPIELER_BOOLEAN_FUSSBALLINLAENDER:
		return ("Fussballinlaender");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Bool Field: " << Bool << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return("");
	}
} // GetNameFromSpielerBooleanType

std::string GetNameFromSpielerEnumType (SPIELER_ENUM_TYPE EnumType)
{
	switch (EnumType)
	{
	case SPIELER_ENUM_UNKNOWN:
		return ("SPIELER_ENUM_FIELD_UNKNOWN");
	case SPIELER_ENUM_FUSSBALLINLAENDER:
		return ("Fussballinlaender");
	case SPIELER_ENUM_HAAR:
		return ("Haar");
	case SPIELER_ENUM_BART:
		return ("Bart");
	case SPIELER_ENUM_NATIONALSPIELER_UND_RUECKTRITT:
		return ("NationalspielerUndRuecktritt");
	case SPIELER_ENUM_EIGENSCHAFTEN:
		return ("Eigenschaften");
	case SPIELER_ENUM_HAUTFARBE:
		return ("Hautfarbe");
	case SPIELER_ENUM_HAARFARBE:
		return ("Haarfarbe");
	case SPIELER_ENUM_POSITION:
		return ("Position");
	case SPIELER_ENUM_FUSS:
		return ("Fuss");
	case SPIELER_ENUM_TALENT:
		return ("Talent");
	case SPIELER_ENUM_GESUNDHEIT:
		return ("Gesundheit");
	case SPIELER_ENUM_PUBLIKUM:
		return ("Publikum");
	case SPIELER_ENUM_TORWARTFAEHIGKEITEN:
		return ("TorwartFaehigkeiten");
	case SPIELER_ENUM_SPIELERFAEHIGKEITEN:
		return ("SpielerFaehigkeiten");
	case SPIELER_ENUM_CHARAKTER:
		return ("Charakter");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Split Field Type " << EnumType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerEnumType

std::string GetNameFromSpielerHaarType (int HaarType)
{
	switch ((SPIELER_HAAR_TYPE) HaarType)
	{
	case SPIELER_HAAR_UNKNOWN:
		return ("SPIELER_HAAR_FIELD_UNKNOWN");
	case SPIELER_HAAR_EXTREM_KURZ:
		return ("ExtremKurz");
	case SPIELER_HAAR_KURZ:
		return ("Kurz");
	case SPIELER_HAAR_WUSCHELKOPF:
		return ("Wuschelkopf");
	case SPIELER_HAAR_LANG:
		return ("Lang");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << HaarType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerHaarType

std::string GetNameFromSpielerBartType (int BartType)
{
	switch ((SPIELER_BART_TYPE) BartType)
	{
	case SPIELER_BART_UNKNOWN:
		return ("SPIELER_BART_FIELD_UNKNOWN");
	case SPIELER_BART_UNRASIERT:
		return ("Unrasiert");
	case SPIELER_BART_KEIN:
		return ("Kein");
	case SPIELER_BART_BART:
		return ("Bart");
	case SPIELER_BART_SCHNURBART:
		return ("Schnurbart");
	case SPIELER_BART_ZIEGENBART:
		return ("Ziegenbart");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << BartType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerBartType

std::string GetNameFromSpielerNationalspielerUndRuecktrittType (int NationalspielerType)
{
	switch ((SPIELER_NATIONALSPIELER_UND_RUECKTRITT_TYPE) NationalspielerType)
	{
	case SPIELER_NATIONALSPIELER_UND_RUECKTRITT_NEIN:
		return("KeinNationalspieler");
	case SPIELER_NATIONALSPIELER_UND_RUECKTRITT_IST_NATIONALSPIELER:
		return ("Nationalspieler");
	case SPIELER_NATIONALSPIELER_UND_RUECKTRITT_RUECKTRITT:
		return ("RuecktrittNationalmannschaft");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << NationalspielerType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerNationalspielerUndRuecktrittType

std::string GetNameFromSpielerFussballInlaenderType (int FussballInlaenderType)
{
	switch ((SPIELER_FUSSBALLINLAENDER_TYPE) FussballInlaenderType)
	{
	case SPIELER_FUSSBALLINLAENDER_NEIN:
		return ("Nein");

	case SPIELER_FUSSBALLINLAENDER_JA:
		return ("Ja");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << FussballInlaenderType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerFussballInlaenderType

std::string GetNameFromSpielerEigenschaftenType (int Spielereigenschaft)
{
	switch ((SPIELER_EIGENSCHAFTEN_TYPE) Spielereigenschaft)
	{
	case SPIELER_EIGENSCHAFTEN_KEINE:
		return ("Keine");
	case SPIELER_EIGENSCHAFTEN_KAEMPFERNATUR:
		return ("Kaempfernatur");
	case SPIELER_EIGENSCHAFTEN_TRAININGSWELTMEISTER:
		return ("Trainingsweltmeister");
	case SPIELER_EIGENSCHAFTEN_TRAININGSFAULERSPIELER:
		return ("TrainingsfaulerSpieler");
	case SPIELER_EIGENSCHAFTEN_TRETER:
		return ("Treter");
	case SPIELER_EIGENSCHAFTEN_FAIRERSPIELER:
		return ("FairerSpieler");
	case SPIELER_EIGENSCHAFTEN_MIMOSE:
		return ("Mimose");
	case SPIELER_EIGENSCHAFTEN_SCHLITZOHR:
		return ("Schlitzohr");
	case SPIELER_EIGENSCHAFTEN_SPEZIALIST:
		return ("Spezialist");
	case SPIELER_EIGENSCHAFTEN_ALLROUNDER:
		return ("Allrounder");
	case SPIELER_EIGENSCHAFTEN_FLEXIBLERSPIELER:
		return ("FlexiblerSpieler");
	case SPIELER_EIGENSCHAFTEN_SCHIRILIEBLING:
		return ("Schiriliebling");
	case SPIELER_EIGENSCHAFTEN_HEIMSPIELER:
		return ("Heimspieler");
	case SPIELER_EIGENSCHAFTEN_SCHOENWETTERFUSSBALLER:
		return ("Schoenwetterfussballer");
	case SPIELER_EIGENSCHAFTEN_JOKER:
		return ("Joker");
	case SPIELER_EIGENSCHAFTEN_EGOIST:
		return ("Egoist");
	case SPIELER_EIGENSCHAFTEN_BRUDERLEICHTFUSS:
		return ("BruderLeichtfuss");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << Spielereigenschaft << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerEigenschaftenType

std::string GetNameFromSpielerCharakter (int SpielerCharakter)
{
	switch ((SPIELER_CHARAKTER_TYPE) SpielerCharakter)
	{       
	case SPIELER_CHARAKTER_KEINE:
		return ("Keine");
	case SPIELER_CHARAKTER_FUEHRUNGSPERSON:
		return ("Fuehrungsperson");
	case SPIELER_CHARAKTER_HITZKOPF:
		return ("Hitzkopf");
	case SPIELER_CHARAKTER_FROHNATUR:
		return ("Frohnatur");
	case SPIELER_CHARAKTER_MANNOHNENERVEN:
		return ("MannOhneNerven");
	case SPIELER_CHARAKTER_NERVENBUENDEL:
		return ("Nervenbuendel");
	case SPIELER_CHARAKTER_PHLEGMATIKER:
		return ("Phlegmatiker");
	case SPIELER_CHARAKTER_GELDGEIER:
		return ("Geldgeier");
	case SPIELER_CHARAKTER_VEREINSANHAENGER:
		return ("Vereinsanhaenger");
	case SPIELER_CHARAKTER_MUSTERPROFI:
		return ("Musterprofi");
	case SPIELER_CHARAKTER_SKANDALNUDEL:
		return ("Skandalnudel");
	case SPIELER_CHARAKTER_SENSIBELCHEN:
		return ("Sensibelchen");
	case SPIELER_CHARAKTER_STARALUEREN:
		return ("Staralueren");
	case SPIELER_CHARAKTER_TEENIE_STAR:
		return ("TeenieStar");
	case SPIELER_CHARAKTER_UNRUHESTIFTER:
		return ("Unruhestifter");
	case SPIELER_CHARAKTER_LEBERWURST:
		return ("Leberwurst");
	case SPIELER_CHARAKTER_INTEGRATIONSFIGUR:
		return ("Integrationsfigur");
			  
	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << SpielerCharakter << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpieler

std::string GetNameFromSpielerCharakterType (int SpielerCharakterType)
{
	switch ((SPIELER_CHARAKTER_TYPE) SpielerCharakterType)
	{
	case SPIELER_CHARAKTER_KEINE:
		return ("Keine");
	case SPIELER_CHARAKTER_FUEHRUNGSPERSON:
		return ("Fuehrungsperson");
	case SPIELER_CHARAKTER_HITZKOPF:
		return ("Hitzkopf");
	case SPIELER_CHARAKTER_FROHNATUR:
		return ("Frohnatur");
	case SPIELER_CHARAKTER_MANNOHNENERVEN:
		return ("MannOhneNerven");
	case SPIELER_CHARAKTER_NERVENBUENDEL:
		return ("Nervenbuendel");
	case SPIELER_CHARAKTER_PHLEGMATIKER:
		return ("Phlegmatiker");
	case SPIELER_CHARAKTER_GELDGEIER:
		return ("Geldgeier");
	case SPIELER_CHARAKTER_VEREINSANHAENGER:
		return ("Vereinsanhaenger");
	case SPIELER_CHARAKTER_MUSTERPROFI:
		return ("Musterprofi");
	case SPIELER_CHARAKTER_SKANDALNUDEL:
		return ("Skandalnudel");
	case SPIELER_CHARAKTER_SENSIBELCHEN:
		return ("Sensibelchen");
	case SPIELER_CHARAKTER_STARALUEREN:
		return ("Staralueren");
	case SPIELER_CHARAKTER_TEENIE_STAR:
		return ("TeenieStar");
	case SPIELER_CHARAKTER_UNRUHESTIFTER:
		return ("Unruhestifter");
	case SPIELER_CHARAKTER_LEBERWURST:
		return ("Leberwurst");
	case SPIELER_CHARAKTER_INTEGRATIONSFIGUR:
		return ("Integrationsfigur");
		
	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << SpielerCharakterType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerCharakterType

std::string GetNameFromSpielerFussballinlaenderType (int SpielerFussballinlaenderType)
{
	switch ((SPIELER_FUSSBALLINLAENDER_TYPE) SpielerFussballinlaenderType)
	{
	case SPIELER_FUSSBALLINLAENDER_NEIN:
		return ("Nein");

	case SPIELER_FUSSBALLINLAENDER_JA:
		return ("Ja");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << SpielerFussballinlaenderType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerFussballinlaenderType

std::string GetNameFromSpielerHautfarbeType (int SpielerHautfarbeType)
{
	switch ((SPIELER_HAUTFARBE_TYPE) SpielerHautfarbeType)
	{
	case SPIELER_HAUTFARBE_HELL:
		return ("Hell");
	case SPIELER_HAUTFARBE_DUNKEL:
		return ("Dunkel");
	case SPIELER_HAUTFARBE_SCHWARZ:
		return ("Schwarz");
	case SPIELER_HAUTFARBE_ASIATISCH:
		return ("Asiatisch");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << SpielerHautfarbeType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerHautfarbeType

std::string GetNameFromSpielerHaarfarbeType (int SpielerHaarfarbeType)
{
	switch ((SPIELER_HAARFARBE_TYPE) SpielerHaarfarbeType)
	{
	case SPIELER_HAARFARBE_HELLBLOND:
		return ("Hellblond");
	case SPIELER_HAARFARBE_BLOND:
		return ("Blond");
	case SPIELER_HAARFARBE_BRAUN:
		return ("Braun");
	case SPIELER_HAARFARBE_ROT:
		return ("Rot");
	case SPIELER_HAARFARBE_SCHWARZ:
		return ("Schwarz");
	case SPIELER_HAARFARBE_GLATZE:
		return ("Glatze");
	case SPIELER_HAARFARBE_GRAU:
		return ("Grau");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << SpielerHaarfarbeType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerHaarfarbeType

std::string GetNameFromSpielerPositionType (int SpielerPositionType)
{
	switch ((SPIELER_POSITION_TYPE) SpielerPositionType)
	{
	case SPIELER_POSITION_KEINE:
		return ("Keine");
	case SPIELER_POSITION_TORWART:
		return ("Torwart");
	case SPIELER_POSITION_LIBERO:
		return ("Libero");
	case SPIELER_POSITION_INNENVERTEIDIGER:
		return ("Innenverteidiger");
	case SPIELER_POSITION_LINKERVERTEIDIGER:
		return ("LinkerVerteidiger");
	case SPIELER_POSITION_RECHTERVERTEIDIGER:
		return ("RechterVerteidiger");
	case SPIELER_POSITION_DEFENSIVESMITTELFELD:
		return ("DefensivesMittelfeld");
	case SPIELER_POSITION_LINKESMITTELFELD:
		return ("LinkesMittelfeld");
	case SPIELER_POSITION_RECHTESMITTELFELD:
		return ("RechtesMittelfeld");
	case SPIELER_POSITION_OFFENSIVESMITTELFELD:
		return ("OffensivesMittelfeld");
	case SPIELER_POSITION_STUERMER:
		return ("Stuermer");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << SpielerPositionType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerPositionType

std::string GetNameFromSpielerFussType (int SpielerFussType)
{
	switch ((SPIELER_FUSS_TYPE) SpielerFussType)
	{
	case SPIELER_FUSS_LINKS:
		return ("Links");
	case SPIELER_FUSS_RECHTS:
		return ("Rechts");
	case SPIELER_FUSS_BEIDE:
		return ("Beide");
		
	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << SpielerFussType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerFussType

std::string GetNameFromSpielerTalentType (int SpielerTalentType)
{
	switch ((SPIELER_TALENT_TYPE) SpielerTalentType)
	{
	case SPIELER_TALENT_MEGATALENT:
		return ("Megatalent");
	case SPIELER_TALENT_TALENT:
		return ("Talent");
	case SPIELER_TALENT_NORMAL:
		return ("Normal");
	case SPIELER_TALENT_WENIGBEGABT:
		return ("WenigBegabt");
	case SPIELER_TALENT_ZWEILINKEFUESSE:
		return ("ZweiLinkeFuesse");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << SpielerTalentType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerTalentType

std::string GetNameFromSpielerGesundheitType (int SpielerGesundheitType)
{
	switch ((SPIELER_GESUNDHEIT_TYPE) SpielerGesundheitType)
	{
	case SPIELER_GESUNDHEIT_NORMAL:
		return ("Normal");
	case SPIELER_GESUNDHEIT_ROBUST:
		return ("Robust");
	case SPIELER_GESUNDHEIT_ANFAELLIG:
		return ("Anfaellig");
	case SPIELER_GESUNDHEIT_KNIEPROBLEME:
		return ("Knieprobleme");
	case SPIELER_GESUNDHEIT_SCHNELLWIEDERFIT:
		return ("SchnellWiederFit");
	case SPIELER_GESUNDHEIT_DAUERTBISWIEDERFIT:
		return ("DauertBisWiederFit");
	case SPIELER_GESUNDHEIT_WEHLEIDIG:
		return ("Wehleidig");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << SpielerGesundheitType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerGesundheitType

std::string GetNameFromSpielerPublikumType (int SpielerPublikumType)
{
	switch ((SPIELER_PUBLIKUM_TYPE) SpielerPublikumType)
	{
	case SPIELER_PUBLIKUM_NORMAL:
		return ("Normal");
	case SPIELER_PUBLIKUM_LIEBLING:
		return ("Liebling");
	case SPIELER_PUBLIKUM_HASSFIGUR:
		return ("Hassfigur");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << SpielerPublikumType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerPublikumType

std::string GetPositiveNameFromSpielerTorwartFaehigkeitenType (int TorwartFaehigkeitenType)
{
	if (((SPIELER_TORWARTFAEHIGKEITEN_TYPE) TorwartFaehigkeitenType) == SPIELER_TORWARTFAEHIGKEITEN_KEINE)
		return (GetNameForSpielerKeineFaehigkeit());
	else
		return (GetNameFromSpielerTorwartFaehigkeitenType ((SPIELER_TORWARTFAEHIGKEITEN_TYPE) TorwartFaehigkeitenType, POSITIVE_FAEHIGKEITEN_PREFIX));
} // GetPositiveNameFromSpielerTorwartFaehigkeitenType

std::string GetNegativeNameFromSpielerTorwartFaehigkeitenType (int TorwartFaehigkeitenType)
{
	if (((SPIELER_TORWARTFAEHIGKEITEN_TYPE) TorwartFaehigkeitenType) == SPIELER_TORWARTFAEHIGKEITEN_KEINE)
		return (GetNameForSpielerKeineFaehigkeit());
	else
		return (GetNameFromSpielerTorwartFaehigkeitenType ((SPIELER_TORWARTFAEHIGKEITEN_TYPE) TorwartFaehigkeitenType, NEGATIVE_FAEHIGKEITEN_PREFIX));
} // GetNegativeNameFromSpielerTorwartFaehigkeitenType

std::string GetPositiveNameFromSpielerFaehigkeitenType (int SpielerFaehigkeitenType)
{
	if (((SPIELER_TORWARTFAEHIGKEITEN_TYPE) SpielerFaehigkeitenType) == SPIELER_SPIELERFAEHIGKEITEN_KEINE)
		return (GetNameForSpielerKeineFaehigkeit());
	else
		return (GetNameFromSpielerFaehigkeitenType ((SPIELER_SPIELERFAEHIGKEITEN_TYPE) SpielerFaehigkeitenType, POSITIVE_FAEHIGKEITEN_PREFIX));
} // GetPositiveNameFromSpielerFaehigkeitenType

std::string GetNegativeNameFromSpielerFaehigkeitenType (int SpielerFaehigkeitenType)
{
	if (((SPIELER_TORWARTFAEHIGKEITEN_TYPE) SpielerFaehigkeitenType) == SPIELER_SPIELERFAEHIGKEITEN_KEINE)
		return (GetNameForSpielerKeineFaehigkeit());
	else
		return (GetNameFromSpielerFaehigkeitenType ((SPIELER_SPIELERFAEHIGKEITEN_TYPE) SpielerFaehigkeitenType, NEGATIVE_FAEHIGKEITEN_PREFIX));
} // GetNegativeNameFromSpielerFaehigkeitenType

static std::string GetNameFromSpielerTorwartFaehigkeitenType (SPIELER_TORWARTFAEHIGKEITEN_TYPE TorwartFaehigkeitenType, const std::string& Prefix)
{
	return (Prefix + GetNameFromSpielerTorwartFaehigkeitenTypeUnPrefixed (TorwartFaehigkeitenType));
} // GetNameFromSpielerTorwartFaehigkeitenType

static std::string GetNameFromSpielerFaehigkeitenType (SPIELER_SPIELERFAEHIGKEITEN_TYPE SpielerFaehigkeitenType, const std::string& Prefix)
{
	return (Prefix + GetNameFromSpielerFaehigkeitenTypeUnPrefixed (SpielerFaehigkeitenType));
} // GetNameFromSpielerFaehigkeitenType

static std::string GetNameFromSpielerTorwartFaehigkeitenTypeUnPrefixed (SPIELER_TORWARTFAEHIGKEITEN_TYPE TorwartFaehigkeitenType)
{
	switch (TorwartFaehigkeitenType)
	{
	case SPIELER_TORWARTFAEHIGKEITEN_KEINE:
		return ("Keine");
	case SPIELER_TORWARTFAEHIGKEITEN_ELFMETERTOETER:
		return ("Elfmetertoeter");
	case SPIELER_TORWARTFAEHIGKEITEN_STARKE_REFLEXE:
		return ("StarkeReflexe");
	case SPIELER_TORWARTFAEHIGKEITEN_HERAUSLAUFEN:
		return ("Herauslaufen");
	case SPIELER_TORWARTFAEHIGKEITEN_FLANKEN:
		return ("Flanken");
	case SPIELER_TORWARTFAEHIGKEITEN_FAUSTEN:
		return ("Fausten");
	case SPIELER_TORWARTFAEHIGKEITEN_BALLSICHERHEIT:
		return ("Ballsicherheit");
	case SPIELER_TORWARTFAEHIGKEITEN_SCHNELLIGKEIT:
		return ("Schnelligkeit");
	case SPIELER_TORWARTFAEHIGKEITEN_WEITE_ABSCHLAEGE:
		return ("WeiteAbschlaege");
	case SPIELER_TORWARTFAEHIGKEITEN_WEITE_ABWUERFE:
		return ("WeiteAbwuerfe");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << TorwartFaehigkeitenType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerTorwartFaehigkeitenTypeUnPrefixed

static std::string GetNameFromSpielerFaehigkeitenTypeUnPrefixed (SPIELER_SPIELERFAEHIGKEITEN_TYPE SpielerFaehigkeitenType)
{
	switch (SpielerFaehigkeitenType)
	{
	case SPIELER_SPIELERFAEHIGKEITEN_KEINE:
		return ("Keine");
	case SPIELER_SPIELERFAEHIGKEITEN_KOPFBALL:
		return ("Kopfball");
	case SPIELER_SPIELERFAEHIGKEITEN_ZWEIKAMPF:
		return ("Zweikampf");
	case SPIELER_SPIELERFAEHIGKEITEN_SCHNELLIGKEIT:
		return ("Schnelligkeit");
	case SPIELER_SPIELERFAEHIGKEITEN_SCHUSSKRAFT:
		return ("Schusskraft");
	case SPIELER_SPIELERFAEHIGKEITEN_ELFMETER:
		return ("Elfmeter");
	case SPIELER_SPIELERFAEHIGKEITEN_FREISTOESSE:
		return ("Freistoesse");
	case SPIELER_SPIELERFAEHIGKEITEN_FLANKEN:
		return ("Flanken");
	case SPIELER_SPIELERFAEHIGKEITEN_TORINSTINKT:
		return ("Torinstinkt");
	case SPIELER_SPIELERFAEHIGKEITEN_LAUFSTAREKE:
		return ("Laufstaerke");
	case SPIELER_SPIELERFAEHIGKEITEN_TECHNICK:
		return ("Technick");
	case SPIELER_SPIELERFAEHIGKEITEN_BALLZAUBERER:
		return ("Ballzauberer");
	case SPIELER_SPIELERFAEHIGKEITEN_SPIELMACHER:
		return ("Spielmacher");
	case SPIELER_SPIELERFAEHIGKEITEN_VIERERKETTE:
		return ("Viererkette");
	case SPIELER_SPIELERFAEHIGKEITEN_SPIELUEBERSICHT :
		return ("Spieluebersicht");
	case SPIELER_SPIELERFAEHIGKEITEN_BALL_HALTEN:
		return ("BallHalten");
	case SPIELER_SPIELERFAEHIGKEITEN_DRIBBLING:
		return ("Dribbling");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << SpielerFaehigkeitenType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromSpielerFaehigkeitenTypeUnPrefixed

static std::string GetNameForSpielerKeineFaehigkeit ()
{
	return (SPIELER_NO_FAEHIGKEIT_STRING);
} // GetNameForSpielerKeineFaehigkeit










/*

static int GetBimapValue (ENUM_VALUE_SIDE_TYPE LookupSide, int LookupIndex, const INT_HASHBIMAP_TYPE& Bimap)
{
	int Type = -1;

	try
	{
		switch (LookupSide)
		{
		case ENUM_VALUE_SIDE_LEFT:
			Type = Bimap.left.find(LookupIndex)->second;
			break;

		case ENUM_VALUE_SIDE_RIGHT:
			Type = Bimap.right.find(LookupIndex)->second;
			break;

		default:
			std::stringstream ErrorText;
			ErrorText << "Unexpected Side Type Value \"" << LookupSide << "\" -> " <<__FUNCTION__;
			programError (ErrorText.str());
			break;
		} // switch return side type
	}
	catch( std::out_of_range & e ) 
	{
		std::stringstream ErrorText;
		ErrorText << "No Value found for index \"" << LookupIndex << "\" (" << e.what() << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

	return (Type);
} // GetBimapValue


// Map for Bart Type
#include "boost/bimap/unordered_set_of.hpp"
typedef boost::bimap<boost::bimaps::unordered_set_of<int>,boost::bimaps::unordered_set_of<std::string>> INT_STRING_HASHBIMAP_TYPE;
typedef boost::bimap<boost::bimaps::unordered_set_of<int>,boost::bimaps::unordered_set_of<int>> INT_HASHBIMAP_TYPE;


template <typename BIMAP_TYPE> BIMAP_TYPE T_GetHashBimapValue (
	const ENUM_VALUE_SIDE_TYPE& LookupSide, const BIMAP_TYPE& LookupIndex, const INT_HASHBIMAP_TYPE& Bimap)
{
	BIMAP_TYPE Type = -1;
	try
	{
		switch (LookupSide)
		{
		case ENUM_VALUE_SIDE_LEFT:
			Type = Bimap.left.find(LookupIndex)->second;
			break;

		case ENUM_VALUE_SIDE_RIGHT:
			Type = Bimap.right.find(LookupIndex)->second;
			break;

		default:
			std::stringstream ErrorText;
			ErrorText << "Unexpected Side Type Value \"" << LookupSide << "\" -> " <<__FUNCTION__;
			programError (ErrorText.str());
			break;
		} // switch return side type
	}
	catch( std::out_of_range & e ) 
	{
		std::stringstream ErrorText;
		ErrorText << "No Value found for index \"" << LookupIndex << "\" (" << e.what() << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

	return (Type);
} // T_GetHashBimapValue

const static INT_HASHBIMAP_TYPE gMapHash_SPIELER_ENUM_SPIELERFAEHIGKEITEN = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(SPIELER_SPIELERFAEHIGKEITEN_KEINE,				0)
	(SPIELER_SPIELERFAEHIGKEITEN_KOPFBALL,			2)
	(SPIELER_SPIELERFAEHIGKEITEN_ZWEIKAMPF,			4)
	(SPIELER_SPIELERFAEHIGKEITEN_SCHNELLIGKEIT,		8)
	(SPIELER_SPIELERFAEHIGKEITEN_SCHUSSKRAFT,		16)
	(SPIELER_SPIELERFAEHIGKEITEN_ELFMETER,			32)
	(SPIELER_SPIELERFAEHIGKEITEN_FREISTOESSE,		64)
	(SPIELER_SPIELERFAEHIGKEITEN_FLANKEN,			128)
	(SPIELER_SPIELERFAEHIGKEITEN_TORINSTINKT,		256)
	(SPIELER_SPIELERFAEHIGKEITEN_LAUFSTAREKE,		512)
	(SPIELER_SPIELERFAEHIGKEITEN_TECHNICK,			1024)
	(SPIELER_SPIELERFAEHIGKEITEN_BALLZAUBERER,		2048)
	(SPIELER_SPIELERFAEHIGKEITEN_SPIELMACHER,		4096)
	(SPIELER_SPIELERFAEHIGKEITEN_VIERERKETTE,		8192)
	(SPIELER_SPIELERFAEHIGKEITEN_SPIELUEBERSICHT,	16384)
	(SPIELER_SPIELERFAEHIGKEITEN_BALL_HALTEN,		32768)
	(SPIELER_SPIELERFAEHIGKEITEN_DRIBBLING,			65536);

const static int gArray_SPIELER_ENUM_SPIELERFAEHIGKEITEN [NO_OF_SPIELER_SPIELERFAEHIGKEITEN_TYPES] = 
{0, 0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};

#include "a3_db_io.h"
void SPIELER_TEST ()
{
#define	NUM_OF_TEST_RUNS	500000
	int Max = NO_OF_SPIELER_SPIELERFAEHIGKEITEN_TYPES - 1;

	int EnumVal = 10;
	int RevVal = gArray_SPIELER_ENUM_SPIELERFAEHIGKEITEN [EnumVal];
	// List
	TIMING_START
	for (int i = 0; i < NUM_OF_TEST_RUNS; i++)
		int Val = T_GetBimapValue<int>(ENUM_VALUE_SIDE_LEFT, EnumVal, gMap_SPIELER_ENUM_SPIELERFAEHIGKEITEN);
	TIMING_END(LIST)
	// List Function
	TIMING_START
	for (int i = 0; i < NUM_OF_TEST_RUNS; i++)
		int Val = GetBimapValue(ENUM_VALUE_SIDE_LEFT, EnumVal, gMap_SPIELER_ENUM_SPIELERFAEHIGKEITEN);
	TIMING_END(LIST_FUNCTION)
	// ReverseList
	TIMING_START
	for (int i = 0; i < NUM_OF_TEST_RUNS; i++)
		int Val = T_GetBimapValue<int>(ENUM_VALUE_SIDE_RIGHT, RevVal, gMap_SPIELER_ENUM_SPIELERFAEHIGKEITEN);
	TIMING_END(LIST_REVERSE)
	// List Direct Access Map
	TIMING_START
	for (int i = 0; i < NUM_OF_TEST_RUNS; i++)
		int Val = gMap_SPIELER_ENUM_SPIELERFAEHIGKEITEN.left.find(EnumVal)->second;
	TIMING_END(LIST_DIRECT_MAP_ACCESS)


	// Hash Map
	TIMING_START
	for (int i = 0; i < NUM_OF_TEST_RUNS; i++)
		int Val = T_GetHashBimapValue<int>(ENUM_VALUE_SIDE_LEFT, EnumVal, gMapHash_SPIELER_ENUM_SPIELERFAEHIGKEITEN);
	TIMING_END(HASH)
	// Reverse Hash Map
	TIMING_START
	for (int i = 0; i < NUM_OF_TEST_RUNS; i++)
		int Val = T_GetHashBimapValue<int>(ENUM_VALUE_SIDE_RIGHT, RevVal, gMapHash_SPIELER_ENUM_SPIELERFAEHIGKEITEN);
	TIMING_END(HASH_REVERSE)

	// Array
	TIMING_START
	for (int i = 0; i < NUM_OF_TEST_RUNS; i++)
		int Val = gArray_SPIELER_ENUM_SPIELERFAEHIGKEITEN [EnumVal];
	TIMING_END(ARRAY)
	// Array
	TIMING_START
	for (int i = 0; i < NUM_OF_TEST_RUNS; i++)
	{
		int Val = gArray_SPIELER_ENUM_SPIELERFAEHIGKEITEN [EnumVal];
		for (int j = 0; j < NO_OF_SPIELER_SPIELERFAEHIGKEITEN_TYPES; j++)
		{
			if (gArray_SPIELER_ENUM_SPIELERFAEHIGKEITEN[j] == RevVal)
			{
				int Val = j;
				break;
			}
		}
	}
	TIMING_END(ARRAY_REVERSE)

} // SPIELER_TEST

template <typename BIMAP_TYPE> BIMAP_TYPE T_GetHashBimapValue (
	const ENUM_VALUE_SIDE_TYPE& LookupSide, const BIMAP_TYPE& LookupIndex, const boost::bimap<BIMAP_TYPE, BIMAP_TYPE>& Bimap)
{
	BIMAP_TYPE Type = -1;
	try
	{
		switch (LookupSide)
		{
		case ENUM_VALUE_SIDE_LEFT:
			Type = Bimap.left.find(LookupIndex)->second;
			break;

		case ENUM_VALUE_SIDE_RIGHT:
			Type = Bimap.right.find(LookupIndex)->second;
			break;

		default:
			std::stringstream ErrorText;
			ErrorText << "Unexpected Side Type Value \"" << LookupSide << "\" -> " <<__FUNCTION__;
			programError (ErrorText.str());
			break;
		} // switch return side type
	}
	catch( std::out_of_range & e ) 
	{
		std::stringstream ErrorText;
		ErrorText << "No Value found for index \"" << LookupIndex << "\" (" << e.what() << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

	return (Type);
} // T_GetBimapValue
*/
