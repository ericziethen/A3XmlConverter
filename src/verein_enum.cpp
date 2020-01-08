#include "verein_enum.h"
#include "error_handling.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM VALUE LOOKUP MAPS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// Map for Trikot Farbe
const static INT_HASHBIMAP_TYPE gMap_VEREIN_TRIKOT_FARBE = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(VEREIN_TRIKOT_FARBE_WEISS,		0)
	(VEREIN_TRIKOT_FARBE_ROT,		1)
	(VEREIN_TRIKOT_FARBE_GELB,		2)
	(VEREIN_TRIKOT_FARBE_BLAU,		3)
	(VEREIN_TRIKOT_FARBE_HELLGRUEN,	4)
	(VEREIN_TRIKOT_FARBE_GRUEN,		5)
	(VEREIN_TRIKOT_FARBE_TUERKIS,	6)
	(VEREIN_TRIKOT_FARBE_HELLBLAU,	7)
	(VEREIN_TRIKOT_FARBE_BRAUN,		8)
	(VEREIN_TRIKOT_FARBE_LILA,		9)
	(VEREIN_TRIKOT_FARBE_ORANGE,	10)
	(VEREIN_TRIKOT_FARBE_SCHWARZ,	11)
	(VEREIN_TRIKOT_FARBE_WEINROT,	12);

// Map for Trikot Muster
const static INT_HASHBIMAP_TYPE gMap_VEREIN_TRIKOT_MUSTER = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(VEREIN_TRIKOT_MUSTER_NEUTRAL,		0)
	(VEREIN_TRIKOT_MUSTER_LAENGS,		16)
	(VEREIN_TRIKOT_MUSTER_QUER,			32)
	(VEREIN_TRIKOT_MUSTER_HALB_HALB,	48)
	(VEREIN_TRIKOT_MUSTER_SCHULTER,		64)
	(VEREIN_TRIKOT_MUSTER_BRUSTRING,	80)
	(VEREIN_TRIKOT_MUSTER_AERMEL,		96)
	(VEREIN_TRIKOT_MUSTER_MITTELSTR,	112)
	(VEREIN_TRIKOT_MUSTER_KARIERT,		128)
	(VEREIN_TRIKOT_MUSTER_SCHRAEG,		144);

// Map for Trikot Ringelsocken
const static INT_HASHBIMAP_TYPE gMap_VEREIN_TRIKOT_RINGELSOCKEN = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(VEREIN_TRIKOT_RINGELSOCKEN_NEIN,	0)
	(VEREIN_TRIKOT_RINGELSOCKEN_JA,		16);

// Map for Kuerzl
const static INT_HASHBIMAP_TYPE gMap_VEREIN_KUERZL = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(VEREIN_KUERZL_KEINS,	0)
	(VEREIN_KUERZL_DER,		1)
	(VEREIN_KUERZL_DIE,		2);

// Map for Fanaufkommen
const static INT_HASHBIMAP_TYPE gMap_VEREIN_FANAUFKOMMEN = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(VEREIN_FANAUFKOMMEN_WAHRE_HORDEN,		0)
	(VEREIN_FANAUFKOMMEN_SEHR_HOCH,			1)
	(VEREIN_FANAUFKOMMEN_HOCH,				2)
	(VEREIN_FANAUFKOMMEN_DURCHSCHNITTLICH,	3)
	(VEREIN_FANAUFKOMMEN_BESCHEIDEN,		4)
	(VEREIN_FANAUFKOMMEN_AERMLICH,			5)
	(VEREIN_FANAUFKOMMEN_FANS,				6);

// Map for ArtDerFans
const static INT_HASHBIMAP_TYPE gMap_VEREIN_ARTDERFANS = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(VEREIN_ARTDERFANS_NORMAL,			0)
	(VEREIN_ARTDERFANS_LAUTSTARK,		1)
	(VEREIN_ARTDERFANS_VERWOEHNT,		2)
	(VEREIN_ARTDERFANS_ANSPRUCHSVOLL,	3)
	(VEREIN_ARTDERFANS_TREU,			4)
	(VEREIN_ARTDERFANS_ERFOLGSHUNGRIG,	5)
	(VEREIN_ARTDERFANS_FRUSTRIERT,		6)
	(VEREIN_ARTDERFANS_EUPHORISCH,		7);

// Map for Vorstand
const static INT_HASHBIMAP_TYPE gMap_VEREIN_VORSTAND = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(VEREIN_VORSTAND_PULVERFASS,	0)
	(VEREIN_VORSTAND_SCHLEUDERSITZ,	1)
	(VEREIN_VORSTAND_NERVOES,		2)
	(VEREIN_VORSTAND_NORMAL,		3)
	(VEREIN_VORSTAND_SOUVERAEN,		4)
	(VEREIN_VORSTAND_TREU,			5);

// Map for Opposition
const static INT_HASHBIMAP_TYPE gMap_VEREIN_OPPOSITION = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(VEREIN_OPPOSITION_NICHT_VORHANDEN,			0)
	(VEREIN_OPPOSITION_NUR_STUEMPER,			1)
	(VEREIN_OPPOSITION_FORMIERT_SICH,			2)
	(VEREIN_OPPOSITION_DURCHAUS_VORHANDEN,		3)
	(VEREIN_OPPOSITION_KONKURENZFAEHIG,			4)
	(VEREIN_OPPOSITION_SEHR_STARK,				5)
	(VEREIN_OPPOSITION_MAECHTIG_UND_KOMPETENT,	6);

// Map for Finanzkraft
const static INT_HASHBIMAP_TYPE gMap_VEREIN_FINANZKRAFT = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(VEREIN_FINANZKRAFT_MINIMAL,	0)
	(VEREIN_FINANZKRAFT_SCHLECHT,	1)
	(VEREIN_FINANZKRAFT_WENIG,		2)
	(VEREIN_FINANZKRAFT_SOLIDE,		3)
	(VEREIN_FINANZKRAFT_GUT,		4)
	(VEREIN_FINANZKRAFT_REICH,		5)
	(VEREIN_FINANZKRAFT_GESEGNET,	6);

// Map for Hooligans
const static INT_HASHBIMAP_TYPE gMap_VEREIN_HOOLIGANS = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(VEREIN_HOOLIGANS_NICHT_VORHANDEN,			0)
	(VEREIN_HOOLIGANS_WENIGE_UND_FEIGE,			1)
	(VEREIN_HOOLIGANS_EIN_PAAR_ABER_KRAEFTIGE,	2)
	(VEREIN_HOOLIGANS_VIELE_UND_SCHLIMME,		3);

// Map for RegionalligaAb2000
const static INT_HASHBIMAP_TYPE gMap_VEREIN_REGIONALLIGAAB2000 = boost::assign::list_of<INT_HASHBIMAP_TYPE::relation>
	(VEREIN_REGIONALLIGAAB2000_NORD, 2)
	(VEREIN_REGIONALLIGAAB2000_SUED, 5);

// Map for Boolean Type
const static INT_BOOLEAN_MAP gMap_VEREIN_BOOLEAN_FIELDS = boost::assign::map_list_of 
	(VEREIN_BOOLEAN_POKALMANNSCHAFT,	1)
	(VEREIN_BOOLEAN_MEDIENSTADT,		1)
	(VEREIN_BOOLEAN_AKTIENGESELLSCHAFT,	1)
	(VEREIN_BOOLEAN_RINGELSOCKEN,		16);

int GetValueFromVereinBooleanType (VEREIN_BOOLEAN_TYPE Bool)
{
	return (GetValueFromBooleanMap (Bool, gMap_VEREIN_BOOLEAN_FIELDS));
} // GetValueFromSpielerBooleanType

int GetVereinEnumValue (int EnumType, ENUM_VALUE_SIDE_TYPE LookupSide, int EnumVal)
{
	int EnumPos = -1;

	switch((VEREIN_ENUM_TYPE) EnumType)
	{
	case VEREIN_ENUM_TRIKOT_MUSTER:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_VEREIN_TRIKOT_MUSTER);
		break;

	case VEREIN_ENUM_TRIKOT_FARBE:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_VEREIN_TRIKOT_FARBE);
		break;

	case VEREIN_ENUM_TRIKOT_RINGELSOCKEN:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_VEREIN_TRIKOT_RINGELSOCKEN);
		break;

	case VEREIN_ENUM_KUERZL:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_VEREIN_KUERZL);
		break;

	case VEREIN_ENUM_FANAUFKOMMEN:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_VEREIN_FANAUFKOMMEN);
		break;

	case VEREIN_ENUM_ARTDERFANS:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_VEREIN_ARTDERFANS);
		break;

	case VEREIN_ENUM_VORSTAND:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_VEREIN_VORSTAND);
		break;

	case VEREIN_ENUM_OPPOSITION:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_VEREIN_OPPOSITION);
		break;

	case VEREIN_ENUM_FINANZKRAFT:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_VEREIN_FINANZKRAFT);
		break;

	case VEREIN_ENUM_HOOLIGANS:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_VEREIN_HOOLIGANS);
		break;

	case VEREIN_ENUM_REGIONALLIGAAB2000:
		EnumPos = T_GetBimapValue<int>(LookupSide, EnumVal, gMap_VEREIN_REGIONALLIGAAB2000);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Split Field Type: " << EnumType << "(" << GetNameFromVereinEnumType((VEREIN_ENUM_TYPE) EnumType) << ")" << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(EnumPos);
} // GetVereinEnumValue

ENUM_VALUE_LIST& GetVereinEnumValueList (VEREIN_ENUM_TYPE SplitField, ENUM_VALUE_LIST& ValueList)
{
	std::stringstream ErrorText;
	switch(SplitField)
	{
	case VEREIN_ENUM_TRIKOT_MUSTER:
		T_GetAllBimapValues(gMap_VEREIN_TRIKOT_MUSTER, ValueList);
		break;

	case VEREIN_ENUM_TRIKOT_FARBE:
		T_GetAllBimapValues(gMap_VEREIN_TRIKOT_FARBE, ValueList);
		break;

	case VEREIN_ENUM_TRIKOT_RINGELSOCKEN:
		T_GetAllBimapValues(gMap_VEREIN_TRIKOT_RINGELSOCKEN, ValueList);
		break;

	case VEREIN_ENUM_KUERZL:
		T_GetAllBimapValues(gMap_VEREIN_KUERZL, ValueList);
		break;

	case VEREIN_ENUM_FANAUFKOMMEN:
		T_GetAllBimapValues(gMap_VEREIN_FANAUFKOMMEN, ValueList);
		break;

	case VEREIN_ENUM_ARTDERFANS:
		T_GetAllBimapValues(gMap_VEREIN_ARTDERFANS, ValueList);
		break;

	case VEREIN_ENUM_VORSTAND:
		T_GetAllBimapValues(gMap_VEREIN_VORSTAND, ValueList);
		break;

	case VEREIN_ENUM_OPPOSITION:
		T_GetAllBimapValues(gMap_VEREIN_OPPOSITION, ValueList);
		break;

	case VEREIN_ENUM_FINANZKRAFT:
		T_GetAllBimapValues(gMap_VEREIN_FINANZKRAFT, ValueList);
		break;

	case VEREIN_ENUM_HOOLIGANS:
		T_GetAllBimapValues(gMap_VEREIN_HOOLIGANS, ValueList);
		break;

	case VEREIN_ENUM_REGIONALLIGAAB2000:
		T_GetAllBimapValues(gMap_VEREIN_REGIONALLIGAAB2000, ValueList);
		break;

	default:
		ErrorText << "Unexpected Split Field Type: " << SplitField << "(" << GetNameFromVereinEnumType(SplitField) << ")" << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		break;
	}

	return(ValueList);
} // GetVereinEnumValueList

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENUM STRING FUNCTIONS ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

std::string GetNameFromVereinBooleanType (VEREIN_BOOLEAN_TYPE Bool)
{
	switch (Bool)
	{
	case VEREIN_BOOLEAN_POKALMANNSCHAFT:
		return ("Pokalmannschaft");
	case VEREIN_BOOLEAN_MEDIENSTADT:
		return ("Medienstadt");
	case VEREIN_BOOLEAN_AKTIENGESELLSCHAFT:
		return ("Aktiengesellschaft");
	case VEREIN_BOOLEAN_RINGELSOCKEN:
		return ("Ringelsocken");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Bool Field: " << Bool << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return("");
	} // switch types
} // GetNameFromVereinBooleanType

std::string GetNameFromVereinEnumType (VEREIN_ENUM_TYPE EnumType)
{
	switch (EnumType)
	{
	case VEREIN_ENUM_TRIKOT_FARBE:
		return ("VEREIN_ENUM_TRIKOT_FARBE1");
	case VEREIN_ENUM_TRIKOT_MUSTER:
		return ("VEREIN_ENUM_TRIKOT_MUSTER");
	case VEREIN_ENUM_TRIKOT_RINGELSOCKEN:
		return ("VEREIN_ENUM_TRIKOT_RINGELSOCKEN");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Split Field Type " << EnumType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromVereinEnumType

std::string GetNameFromVereinTrikotFarbeType (int TrikotFarbeType)
{
	switch ((VEREIN_TRIKOT_FARBE_TYPE) TrikotFarbeType)
	{
	case VEREIN_TRIKOT_FARBE_WEISS:
		return ("Weiss");
	case VEREIN_TRIKOT_FARBE_ROT:
		return ("Rot");
	case VEREIN_TRIKOT_FARBE_GELB:
		return ("Gelb");
	case VEREIN_TRIKOT_FARBE_BLAU:
		return ("Blau");
	case VEREIN_TRIKOT_FARBE_HELLGRUEN:
		return ("Hellgruen");
	case VEREIN_TRIKOT_FARBE_GRUEN:
		return ("Gruen");
	case VEREIN_TRIKOT_FARBE_TUERKIS:
		return ("Tuerkis");
	case VEREIN_TRIKOT_FARBE_HELLBLAU:
		return ("Hellblau");
	case VEREIN_TRIKOT_FARBE_BRAUN:
		return ("Braun");
	case VEREIN_TRIKOT_FARBE_LILA:
		return ("Lila");
	case VEREIN_TRIKOT_FARBE_ORANGE:
		return ("Orange");
	case VEREIN_TRIKOT_FARBE_SCHWARZ:
		return ("Schwarz");
	case VEREIN_TRIKOT_FARBE_WEINROT:
		return ("Weinrot");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Trikot Farbe Type " << TrikotFarbeType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromVereinTrikotFarbeType

std::string GetNameFromVereinTrikotMusterType (int TrikotMusterType)
{
	switch ((VEREIN_TRIKOT_MUSTER_TYPE) TrikotMusterType)
	{
	case VEREIN_TRIKOT_MUSTER_NEUTRAL:
		return ("Neutral");
	case VEREIN_TRIKOT_MUSTER_LAENGS:
		return ("Laengs");
	case VEREIN_TRIKOT_MUSTER_QUER:
		return ("Quer");
	case VEREIN_TRIKOT_MUSTER_HALB_HALB:
		return ("HalbHalb");
	case VEREIN_TRIKOT_MUSTER_SCHULTER:
		return ("Schulter");
	case VEREIN_TRIKOT_MUSTER_BRUSTRING:
		return ("Brustring");
	case VEREIN_TRIKOT_MUSTER_AERMEL:
		return ("Aermel");
	case VEREIN_TRIKOT_MUSTER_MITTELSTR:
		return ("Mittelstreifen.");
	case VEREIN_TRIKOT_MUSTER_KARIERT:
		return ("Kariert");
	case VEREIN_TRIKOT_MUSTER_SCHRAEG:
		return ("Schraeg");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Trikot Muster Type " << TrikotMusterType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromVereinTrikotMusterType

std::string GetNameFromVereinTrikotRingelsockenType (int TrikotRingelsockenType)
{
	switch ((VEREIN_TRIKOT_RINGELSOCKEN_TYPE) TrikotRingelsockenType)
	{
	case VEREIN_TRIKOT_RINGELSOCKEN_JA:
		return ("VEREIN_TRIKOT_RINGELSOCKEN_FIELD_JA");
	case VEREIN_TRIKOT_RINGELSOCKEN_NEIN:
		return ("VEREIN_TRIKOT_RINGELSOCKEN_FIELD_NEIN");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Trikot Ringelsocken Type " << TrikotRingelsockenType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromVereinTrikotRingelsockenType

std::string GetNameFromVereinKuerzlType (int VereinKuerzlType)
{
	switch ((VEREIN_KUERZL_TYPE) VereinKuerzlType)
	{
	case VEREIN_KUERZL_KEINS:
		return ("Keins");
	case VEREIN_KUERZL_DER:
		return ("Der");
	case VEREIN_KUERZL_DIE:
		return ("Die");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << VereinKuerzlType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromVereinKuerzlType

std::string GetNameFromVereinFanaufkommenType (int VereinFanaufkommenType)
{
	switch ((VEREIN_FANAUFKOMMEN_TYPE) VereinFanaufkommenType)
	{
	case VEREIN_FANAUFKOMMEN_WAHRE_HORDEN:
		return ("WahreHorden");
	case VEREIN_FANAUFKOMMEN_SEHR_HOCH:
		return ("SehrHoch");
	case VEREIN_FANAUFKOMMEN_HOCH:
		return ("Hoch");
	case VEREIN_FANAUFKOMMEN_DURCHSCHNITTLICH:
		return ("Durchschnittlich");
	case VEREIN_FANAUFKOMMEN_BESCHEIDEN:
		return ("Bescheiden");
	case VEREIN_FANAUFKOMMEN_AERMLICH:
		return ("Aermlich");
	case VEREIN_FANAUFKOMMEN_FANS:
		return ("Fans?");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << VereinFanaufkommenType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromVereinFanaufkommenType

std::string GetNameFromVereinArtDerFansType (int VereinArtDerFansType)
{
	switch ((VEREIN_ARTDERFANS_TYPE) VereinArtDerFansType)
	{
	case VEREIN_ARTDERFANS_NORMAL:
		return ("Normal");
	case VEREIN_ARTDERFANS_LAUTSTARK:
		return ("Lautstark");
	case VEREIN_ARTDERFANS_VERWOEHNT:
		return ("Verwoehnt");
	case VEREIN_ARTDERFANS_ANSPRUCHSVOLL:
		return ("Anspruchsvoll");
	case VEREIN_ARTDERFANS_TREU:
		return ("Treu");
	case VEREIN_ARTDERFANS_ERFOLGSHUNGRIG:
		return ("Erfolgshungrig");
	case VEREIN_ARTDERFANS_FRUSTRIERT:
		return ("Frustriert");
	case VEREIN_ARTDERFANS_EUPHORISCH:
		return ("Euphorisch");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << VereinArtDerFansType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromVereinArtDerFansType

std::string GetNameFromVereinVorstandType (int VereinVorstandType)
{
	switch ((VEREIN_VORSTAND_TYPE) VereinVorstandType)
	{
	case VEREIN_VORSTAND_PULVERFASS:
		return ("Pulverfass");
	case VEREIN_VORSTAND_SCHLEUDERSITZ:
		return ("Schleudersitz");
	case VEREIN_VORSTAND_NERVOES:
		return ("Nervoes");
	case VEREIN_VORSTAND_NORMAL:
		return ("Normal");
	case VEREIN_VORSTAND_SOUVERAEN:
		return ("Souveraen");
	case VEREIN_VORSTAND_TREU:
		return ("Treu");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << VereinVorstandType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromVereinVorstandType

std::string GetNameFromVereinOppositionType (int VereinOppositionType)
{
	switch ((VEREIN_OPPOSITION_TYPE) VereinOppositionType)
	{
	case VEREIN_OPPOSITION_NICHT_VORHANDEN:
		return ("NichtVorhanden");
	case VEREIN_OPPOSITION_NUR_STUEMPER:
		return ("NurStuemper");
	case VEREIN_OPPOSITION_FORMIERT_SICH:
		return ("FormiertSich");
	case VEREIN_OPPOSITION_DURCHAUS_VORHANDEN:
		return ("DurchausVorhanden");
	case VEREIN_OPPOSITION_KONKURENZFAEHIG:
		return ("Konkurenzfaehig");
	case VEREIN_OPPOSITION_SEHR_STARK:
		return ("SehrStark");
	case VEREIN_OPPOSITION_MAECHTIG_UND_KOMPETENT:
		return ("MaechtigUndKompetent");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << VereinOppositionType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromVereinOppositionType

std::string GetNameFromVereinFinanzkraftType (int VereinFinanzkraftType)
{
	switch ((VEREIN_FINANZKRAFT_TYPE) VereinFinanzkraftType)
	{
	case VEREIN_FINANZKRAFT_MINIMAL:
		return ("Minimal");
	case VEREIN_FINANZKRAFT_SCHLECHT:
		return ("Schlecht");
	case VEREIN_FINANZKRAFT_WENIG:
		return ("Wenig");
	case VEREIN_FINANZKRAFT_SOLIDE:
		return ("Solide");
	case VEREIN_FINANZKRAFT_GUT:
		return ("Gut");
	case VEREIN_FINANZKRAFT_REICH:
		return ("Reich");
	case VEREIN_FINANZKRAFT_GESEGNET:
		return ("Gesegnet");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << VereinFinanzkraftType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromVereinFinanzkraftType

std::string GetNameFromVereinHooligansType (int VereinHooligansType)
{
	switch ((VEREIN_HOOLIGANS_TYPE) VereinHooligansType)
	{
	case VEREIN_HOOLIGANS_NICHT_VORHANDEN:
		return ("NichtVorhanden");
	case VEREIN_HOOLIGANS_WENIGE_UND_FEIGE:
		return ("WenigeUndFeige");
	case VEREIN_HOOLIGANS_EIN_PAAR_ABER_KRAEFTIGE:
		return ("EinPaarAberKraeftige");
	case VEREIN_HOOLIGANS_VIELE_UND_SCHLIMME:
		return ("VieleUndSchlimme");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << VereinHooligansType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromVereinHooligansType

std::string GetNameFromVereinRegionalligaAb2000Type (int VereinRegionalligaAb2000Type)
{
	switch ((VEREIN_REGIONALLIGAAB2000_TYPE) VereinRegionalligaAb2000Type)
	{
	case VEREIN_REGIONALLIGAAB2000_NORD:
		return ("Nord");
	case VEREIN_REGIONALLIGAAB2000_SUED:
		return ("Sued");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Type " << VereinRegionalligaAb2000Type << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());
		break;
	} // switch types
} // GetNameFromVereinRegionalligaAb2000Type
