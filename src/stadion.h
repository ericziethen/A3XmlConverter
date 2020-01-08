#pragma once

#include "section.h"
#include "stadion_enum.h"

typedef enum
{
	STADION_SECTION_POS_UNKNOWN = 0,
	STADION_SECTION_POS_STADIONNAHME,
	STADION_SECTION_POS_ORT,
	STADION_SECTION_POS_ANZEIGETAFEL,
	STADION_SECTION_POS_RASENHEIZUNG,
	STADION_SECTION_POS_UNKNOWN_05,
	STADION_SECTION_POS_UNKNOWN_06,
	STADION_SECTION_POS_FLUTLICHT,
	STADION_SECTION_POS_HEIMTRIBUENE,
	STADION_SECTION_POS_GEGENTRIBUENE,
	STADION_SECTION_POS_CITYLAGE,
	STADION_SECTION_POS_IM_BESITZ_DES_VEREINS,
	STADION_SECTION_POS_AUTOBAHNANBINDUNG,
	STADION_SECTION_POS_FERNSEHTURM,
	STADION_SECTION_POS_HAUPTTRIBUENE_STEH,
	STADION_SECTION_POS_HAUPTTRIBUENE_SITZ,
	STADION_SECTION_POS_HAUPTTRIBUENE_VIP,
	STADION_SECTION_POS_HAUPTTRIBUENE_ZUSTAND,
	STADION_SECTION_POS_GEGENTRIBUENE_STEH,
	STADION_SECTION_POS_GEGENTRIBUENE_SITZ,
	STADION_SECTION_POS_GEGENTRIBUENE_VIP,
	STADION_SECTION_POS_GEGENTRIBUENE_ZUSTAND,
	STADION_SECTION_POS_TRIBUENE_LINKS_STEH,
	STADION_SECTION_POS_TRIBUENE_LINKS_SITZ,
	STADION_SECTION_POS_TRIBUENE_LINKS_VIP,
	STADION_SECTION_POS_TRIBUENE_LINKS_ZUSTAND,
	STADION_SECTION_POS_TRIBUENE_RECHTS_STEH,
	STADION_SECTION_POS_TRIBUENE_RECHTS_SITZ,
	STADION_SECTION_POS_TRIBUENE_RECHTS_VIP,
	STADION_SECTION_POS_TRIBUENE_RECHTS_ZUSTAND,
	STADION_SECTION_POS_DACH,
	STADION_SECTION_POS_LAUFBAHN,
	STADION_SECTION_POS_WAERMESTRAHLER,
	STADION_SECTION_POS_LUXUSKABINEN,
	STADION_SECTION_POS_SITZKISSEN,
	STADION_SECTION_POS_BEHEIZBARE_SITZE,
	STADION_SECTION_POS_AUSFAHRBARES_SPIELFELD,
	STADION_SECTION_POS_BERGE,
	STADION_SECTION_POS_BURG,
	STADION_SECTION_POS_SCHLOSS,

	// Parent Position, after Section Positions
	STADION_SECTION_POS_REFERENCE_SECTION,

	// Split Bitmasks	
	STADION_SECTION_POS_DACH_SPLIT_HAUPT,
	STADION_SECTION_POS_DACH_SPLIT_GEGEN,
	STADION_SECTION_POS_DACH_SPLIT_LINKS,
	STADION_SECTION_POS_DACH_SPLIT_RECHTS,
	STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_HAUPT,
	STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_GEGEN,
	STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_LINKS,
	STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_RECHTS,

	NO_OF_STADION_SECTION_POS_TYPES
} STADION_SECTION_POS_TYPE;

class stadion :
	public section
{
public:
	stadion(void);
	~stadion(void);

	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	std::string GetUniqueId ();
	SECTION_TYPE GetSectionType ();
	void SplitBitmaskFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void MergeBitmaskFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void GetGenericSplitFieldsForField (int, std::vector<int>&);
	virtual bool GetBooleanTargetFieldForEnumVal (const int, const int, int&);
	void DecodeBooleansFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeBooleansToA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void DecodeEnumsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeEnumsToA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);


	std::string Stadionnahme;
	std::string Ort;
	std::string Anzeigetafel;
	std::string Rasenheizung;
	std::string STADION_FIELD_UNKNOWN_05;
	std::string STADION_FIELD_UNKNOWN_06;
	std::string Flutlicht;
	std::string Heimtribuene;
	std::string Gegentribuene;
	std::string Citylage;
	std::string ImBesitzDesVereins;
	std::string Autobahnanbindung;
	std::string Fernsehturm;
	std::string Haupttribuene_STEH;
	std::string Haupttribuene_SITZ;
	std::string Haupttribuene_VIP;
	std::string Haupttribuene_ZUSTAND;
	std::string Gegentribuene_STEH;
	std::string Gegentribuene_SITZ;
	std::string Gegentribuene_VIP;
	std::string Gegentribuene_ZUSTAND;
	std::string TribueneLinks_STEH;
	std::string TribueneLinks_SITZ;
	std::string TribueneLinks_VIP;
	std::string TribueneLinks_ZUSTAND;
	std::string TribueneRechts_STEH;
	std::string TribueneRechts_SITZ;
	std::string TribueneRechts_VIP;
	std::string TribueneRechts_ZUSTAND;
	std::string Dach;
	std::string Laufbahn;
	std::string Waermestrahler;
	std::string Luxuskabinen;
	std::string Sitzkissen;
	std::string BeheizbareSitze;
	std::string AusfahrbaresSpielfeld;
	std::string Berge;
	std::string Burg;
	std::string Schloss;
	std::string STADION_FIELD_VEREIN;

	// Split Bitmasks
	std::string Dach_Split_Haupt;
	std::string Dach_Split_Gegen;
	std::string Dach_Split_Links;
	std::string Dach_Split_Rechts;
	std::string Waermestrahler_Split_Haupt;
	std::string Waermestrahler_Split_Gegen;
	std::string Waermestrahler_Split_Links;
	std::string Waermestrahler_Split_Rechts;
};

void AssignStadionField (std::vector<std::shared_ptr<section>>&, int, std::string&);
static std::string GetNameFromStadionSectionPosType (const STADION_SECTION_POS_TYPE);
static STADION_SECTION_POS_TYPE GetStadionSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (STADION_SECTION_POS_TYPE);
static bool IncludeSectionPosIntoXml (STADION_SECTION_POS_TYPE);
std::string GetStadionCsvHeader ();
static void GetEnumDetails (int, int, ENUM_FUNC&, int&, int&);

static STADION_ENUM_TYPE GetStadionEnumTypeFromPosition (STADION_SECTION_POS_TYPE);
STADION_BOOLEAN_TYPE GetStadionBooleanTypeFromPosition (STADION_SECTION_POS_TYPE);
void GetStadionAllowedValues (std::vector<FIELD_VALUE_STRUCT>&);
