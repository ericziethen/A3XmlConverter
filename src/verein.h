#pragma once

#include "section.h"
#include "nation.h"
#include "verein_enum.h"

typedef enum
{
	VEREIN_SECTION_POS_UNKNOWN = 0,
	VEREIN_SECTION_POS_LAND,
	VEREIN_SECTION_POS_VEREINSNAHME,
	VEREIN_SECTION_POS_KUERZL,
	VEREIN_SECTION_POS_ANFEUERUNG,
	VEREIN_SECTION_POS_FANBEZEICHNUNG,

	// Hidden Section Part
	VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER,
	VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE2,
	VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_HOSENFARBE,
	VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN,
	VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER,
	VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE2,
	VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_HOSENFARBE,
	VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN,
	VEREIN_SECTION_POS_HIDDEN_GUTHABEN_BEI_SPIELBEGINN,
	VEREIN_SECTION_POS_HIDDEN_KUERZEL_ARTIKEL,
	VEREIN_SECTION_POS_HIDDEN_FANAUFKOMMEN,
	VEREIN_SECTION_POS_HIDDEN_ART_DER_FANS,
	VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT,
	VEREIN_SECTION_POS_HIDDEN_ERZRIVALE,
	VEREIN_SECTION_POS_HIDDEN_VORSTAND,
	VEREIN_SECTION_POS_HIDDEN_POKALMANNSCHAFT,
	VEREIN_SECTION_POS_HIDDEN_UNKNOWN_17,
	VEREIN_SECTION_POS_HIDDEN_UNKNOWN_18,
	VEREIN_SECTION_POS_HIDDEN_UNKNOWN_19,
	VEREIN_SECTION_POS_HIDDEN_UNKNOWN_20,
	VEREIN_SECTION_POS_HIDDEN_UNKNOWN_21,
	VEREIN_SECTION_POS_HIDDEN_OPPOSITION,
	VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON,
	VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON,
	VEREIN_SECTION_POS_HIDDEN_FINANZKRAFT,
	VEREIN_SECTION_POS_HIDDEN_MAX_FANAUFKOMMEN,
	VEREIN_SECTION_POS_HIDDEN_HOOLIGANS,
	VEREIN_SECTION_POS_HIDDEN_MEDIENSTADT,
	VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_ERZIELTE_TORE,
	VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_KASSIERTE_TORE,
	VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_SPIELE,
	VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_PUNKTE,
	VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_NACHNAHME,
	VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_VORNAHME,
	VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_GEBURTSDATUM,
	VEREIN_SECTION_POS_HIDDEN_AKTIENGESELLSCHAFT,
	VEREIN_SECTION_POS_HIDDEN_TITEL_MEISTERSCHAFTEN,
	VEREIN_SECTION_POS_HIDDEN_TITEL_POKALE,
	VEREIN_SECTION_POS_HIDDEN_TITEL_LIGAPOKALE,
	VEREIN_SECTION_POS_HIDDEN_TITEL_EUROPA_LEAGUES,
	VEREIN_SECTION_POS_HIDDEN_TITEL_CHAMPIONS_LEAGUES,
	VEREIN_SECTION_POS_HIDDEN_TITEL_WELTPOKALE,
	VEREIN_SECTION_POS_HIDDEN_REGIONALLIGA_AB_2000,
	VEREIN_SECTION_POS_HIDDEN_GRUENDUNGSJAHR,
	VEREIN_SECTION_POS_HIDDEN_UNKNOWN_45,
	VEREIN_SECTION_POS_HIDDEN_UNKNOWN_46,
	VEREIN_SECTION_POS_HIDDEN_UNKNOWN_47,
	VEREIN_SECTION_POS_HIDDEN_UNKNOWN_48,
	VEREIN_SECTION_POS_HIDDEN_UNKNOWN_49,
	VEREIN_SECTION_POS_HIDDEN_UNKNOWN_50,
	VEREIN_SECTION_POS_HIDDEN_UNKNOWN_51,
	
	// Special Fields
	VEREIN_SECTION_POS_VEREIN_LAND_INDEX,

	// Split Fields
	VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1,
	VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER,
	VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE,
	VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN,
	VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1,
	VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER,
	VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE,
	VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN,

	// Expanded Fields
	VEREIN_SECTION_POS_LAND_EXPANDED,
	VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT_EXPANDED,
	VEREIN_SECTION_POS_HIDDEN_ERZRIVALE_EXPANDED,
	VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON_EXPANDED,
	VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON_EXPANDED,

	NO_OF_VEREIN_SECTION_POS_TYPES
} VEREIN_SECTION_POS_TYPE;

class verein :
	public section
{
public:
	verein(void);
	~verein(void);

	std::string GetUniqueId ();
	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	SECTION_TYPE verein::GetSectionType ();
	void DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void PostSavSplitCombinedFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void PostExternalMergeSplitFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void CalcVereinLandIndex (std::shared_ptr<nation>);
	void GetGenericSplitFieldsForField (int, std::vector<int>&);
	void DecodeBooleansFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeBooleansToA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void DecodeEnumsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeEnumsToA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	
	//std::string Land; -> STORED ALREADY AS PARENT ID
	std::string Vereinsnahme;
	std::string Kuerzl;
	std::string Anfeuerung;
	std::string Fanbezeichnung;

	// Hidden Verein
	std::string Heimtrikot_Farbe1_UndMuster;
	std::string Heimtrikot_Farbe2;
	std::string Heimtrikot_HosenFarbe;
	std::string Heimtrikot_StutzenFarbe_UndRingelsocken;
	std::string Auswaertztrikot_Farbe1_UndMuster;
	std::string Auswaertztrikot_Farbe2;
	std::string Auswaertztrikot_HosenFarbe;
	std::string Auswaertztrikot_StutzenFarbe_UndRingelsocken;
	std::string GuthabenBeiSpielbeginn;
	std::string KuerzelArtikel;
	std::string Fanaufkommen;
	std::string ArtDerFans;
	std::string FanfreundschaftMit;
	std::string Erzrivale;
	std::string Vorstand;
	std::string Pokalmannschaft;
	std::string VEREIN_FIELD_HIDDEN_UNKNOWN_17;
	std::string VEREIN_FIELD_HIDDEN_UNKNOWN_18;
	std::string VEREIN_FIELD_HIDDEN_UNKNOWN_19;
	std::string VEREIN_FIELD_HIDDEN_UNKNOWN_20;
	std::string VEREIN_FIELD_HIDDEN_UNKNOWN_21;
	std::string Opposition;
	std::string AmateurabteilungVon;
	std::string ProfiabteilungVon;
	std::string Finanzkraft;
	std::string MaxFanaufkommen;
	std::string Hooligans;
	std::string Medienstadt;
	std::string EwigeTabelle_ErzielteTore;
	std::string EwigeTabelle_KassierteTore;
	std::string EwigeTabelle_Spiele;
	std::string EwigeTabelle_Punkte;
	std::string Vorsitzender_Nachnahme;
	std::string Vorsitzender_Vornahme;
	std::string Vorsitzender_Geburtdatum;
	std::string Aktiengesellschaft;
	std::string Titel_Meisterschaften;
	std::string Titel_Pokale;
	std::string Titel_Ligapokale;
	std::string Titel_EuropaLeagues;
	std::string Titel_ChampionsLeagues;
	std::string Titel_Weltpokale;
	std::string RegionalligaAb2000;
	std::string Gruendungsjahr;
	std::string VEREIN_FIELD_HIDDEN_UNKNOWN_45;
	std::string VEREIN_FIELD_HIDDEN_UNKNOWN_46;
	std::string VEREIN_FIELD_HIDDEN_UNKNOWN_47;
	std::string VEREIN_FIELD_HIDDEN_UNKNOWN_48;
	std::string VEREIN_FIELD_HIDDEN_UNKNOWN_49;
	std::string VEREIN_FIELD_HIDDEN_UNKNOWN_50;
	std::string VEREIN_FIELD_HIDDEN_UNKNOWN_51;

	// Special Fields
	std::string VereinLandIndex;

	// Split Fields
	std::string Heimtrikot_Farbe1_UndMuster_Split_Farbe1;
	std::string Heimtrikot_Farbe1_UndMuster_Split_Muster;
	std::string Heimtrikot_StutzenFarbe_UndRingelsocken_Split_StutzenFarbe;
	std::string Heimtrikot_StutzenFarbe_UndRingelsocken_Split_Ringelsocken;
	std::string Auswaertztrikot_Farbe1_UndMuster_Split_Farbe1;
	std::string Auswaertztrikot_Farbe1_UndMuster_Split_Muster;
	std::string Auswaertztrikot_StutzenFarbe_UndRingelsocken_Split_StutzenFarbe;
	std::string Auswaertztrikot_StutzenFarbe_UndRingelsocken_Split_Ringelsocken;

	// Expanded Fields
	std::string Land_Expanded;
	std::string FanfreundschaftMit_Expanded;
	std::string Erzrivale_Expanded;
	std::string AmateurabteilungVon_Expanded;
	std::string ProfiabteilungVon_Expanded;

};

void AssignVereinField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromVereinSectionPosType (const VEREIN_SECTION_POS_TYPE);
static VEREIN_SECTION_POS_TYPE GetVereinSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (VEREIN_SECTION_POS_TYPE, SECTION_TYPE);
static bool IncludeSectionPosIntoXml (VEREIN_SECTION_POS_TYPE);
std::string GetVereinCsvHeader ();
int GetVereinHiddenOffset ();
std::string VereinValueToVereinString (const std::string&, const std::string&, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
std::string VereinStringToVereinValue (const std::string&, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
void CalculateVereinIndices (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
bool FindVereinFromVereinList (const std::string&, const std::string&, std::vector<std::shared_ptr<section>>, std::string&);
static void GetEnumDetails (int, int, ENUM_FUNC&, int&, int&);
static VEREIN_ENUM_TYPE GetVereinEnumTypeFromPosition (VEREIN_SECTION_POS_TYPE);
VEREIN_BOOLEAN_TYPE GetVereinBooleanTypeFromPosition (VEREIN_SECTION_POS_TYPE);
void GetVereinAllowedValues (std::vector<FIELD_VALUE_STRUCT>&);
