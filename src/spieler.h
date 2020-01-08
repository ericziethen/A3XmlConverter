#pragma once

#include <string>
#include "section.h"
#include "spieler_enum.h"
#include <memory>

#define CONVERT_EX_SPIELER_REFERENCE_ERRORS 1

typedef enum
{
	SPIELER_SECTION_POS_UNKNOWN,
	SPIELER_SECTION_POS_NACHNAHME, 
	SPIELER_SECTION_POS_VORNAHME, 
	SPIELER_SECTION_POS_UNKNOWN_3, 
	SPIELER_SECTION_POS_HAUTFARBE, 
	SPIELER_SECTION_POS_HAARFARBE, 
	SPIELER_SECTION_POS_ALTER, 
	SPIELER_SECTION_POS_STAERKE, 
	SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER, 
	SPIELER_SECTION_POS_HAUPTPOSITION, 
	SPIELER_SECTION_POS_NEBEN_POSITION_1, 
	SPIELER_SECTION_POS_NEBEN_POSITION_2, 
	SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN, 
	SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN,	  
	SPIELER_SECTION_POS_EIGENSCHAFTEN, 
	SPIELER_SECTION_POS_CHARAKTER, 
	SPIELER_SECTION_POS_HATKUENSTLERNAHME, 
	SPIELER_SECTION_POS_KUENSTLERNAHME,
	SPIELER_SECTION_POS_FUSS, 
	SPIELER_SECTION_POS_TALENT, 
	SPIELER_SECTION_POS_GESUNDHEIT, 
	SPIELER_SECTION_POS_PUBLIKUM, 
	SPIELER_SECTION_POS_GEBURTSDATUM, 
	SPIELER_SECTION_POS_UNKNOWN_23, 
	SPIELER_SECTION_POS_LANDZWEI, 
	SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT, 
	SPIELER_SECTION_POS_UNKNOWN_26, 
	SPIELER_SECTION_POS_UNKNOWN_27, 
	SPIELER_SECTION_POS_KAPITAENRUECKTRITT, 
	SPIELER_SECTION_POS_RUECKENNUMMER,
	SPIELER_SECTION_POS_HAAR_UND_BART, 
	SPIELER_SECTION_POS_UNKNOWN_31, 
	SPIELER_SECTION_POS_UNKNOWN_32, 
	SPIELER_SECTION_POS_UNKNOWN_33,    // LAST A3 Db Field

	// Special Field for ExSpiel Section
	SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND,
	SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN,

	// Split Fields
	SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND, 
	SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_FUSSBALLINLAENDER, 
	SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_HAAR, 
	SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART, 	

	// Split Bitmasks	
	SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_NATIONALSPIELER, 
	SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_RUECKTRITT, 
	SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT1, 	  
	SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT2, 
	SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER1, 
	SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER2, 
	SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_UNRASIERT, 
	SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_BART, 
	SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_SCHNURBART, 
	SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_ZIEGENBART, 

	SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1, 
	SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2, 
	SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3, 
	SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1,	
	SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2,	
	SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3,

	// Expanded Fields
	SPIELER_SECTION_POS_LANDZWEI_EXPANDED, 
	SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND_EXPANDED,
	SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN_EXPANDED,
	SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND_EXPANDED, 

	// Combined Fields
	SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_1,
	SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_2,
	SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_3,
	SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_1,
	SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_2,
	SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_3,
	
	SPIELER_SECTION_POS_VEREIN, // Should that be Verein, or general parent???

	NO_OF_SPIELER_SECTION_POS_TYPES
} SPIELER_SECTION_POS_TYPE;

// Position Polarity Type
typedef enum
{
	SPIELER_POSITION_POLARITY_UNKNOWN,
	SPIELER_POSITION_POLARITY_POSITIVE,
	SPIELER_POSITION_POLARITY_NEGATIVE,
	NO_OF_SPIELER_POSITION_POLARITY_TYPES
} SPIELER_POSITION_POLARITY_TYPE;

class spieler :
	public section
{
public:

	spieler(void);
	~spieler(void);

	std::string spieler::GetUniqueId ();
	std::string GetValueAtSectionPos (int SectionPos);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&);
	void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&, const std::string&);
	void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&);
	void AssignField (int, const std::string&);
	void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&);
	SECTION_TYPE GetSectionType ();
	void DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void PostSavSplitCombinedFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void PostExternalMergeSplitFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void SplitBitmaskFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void MergeBitmaskFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void GetGenericSplitFieldsForField (int, std::vector<int>&);
	void GetGenericCombineFieldsForField (int, std::vector<int>&);
	bool GetBooleanTargetFieldForEnumVal (const int, const int, int&);
	void DecodeBooleansFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeBooleansToA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void DecodeEnumsFromA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void EncodeEnumsToA3Db (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	SPIELER_ENUM_TYPE GetPositionEnum ();
	void MixFaehigkeiten();
	void UnMixFaehigkeiten();
	void MixFaehigkeitenForSectionPos (int);
	void UnMixFaehigkeitenForSectionPos (int);

	std::string Nachnahme;
	std::string Vornahme;
	std::string PLAYER_FIELD_UNKNOWN_3;
	std::string Hautfarbe;
	std::string Haarfarbe;
	std::string Alter;
	std::string Staerke;
	std::string Land_Und_FussballInlaender;
	std::string HauptPosition;
	std::string NebenPosition1;
	std::string NebenPosition2;
	std::string PositiveFaehigkeiten;
	std::string NegativeFaehigkeiten;
	std::string Eigenschaften;
	std::string Charakter;
	std::string HatKuenstlerNahme;
	std::string KuenstlerNahme;
	std::string Fuss;
	std::string Talent;
	std::string Gesundheit;
	std::string Publikum;
	std::string Geburtsdatum;
	std::string PLAYER_FIELD_UNKNOWN_23;
	std::string LandZwei;
	std::string Nationalspieler_Und_Ruecktritt;
	std::string PLAYER_FIELD_UNKNOWN_26;
	std::string PLAYER_FIELD_UNKNOWN_27;
	std::string KapitaenRuecktritt;
	std::string RueckenNummer;
	std::string Haar_Und_Bart;
	std::string PLAYER_FIELD_UNKNOWN_31;
	std::string PLAYER_FIELD_UNKNOWN_32;
	std::string PLAYER_FIELD_UNKNOWN_33;

	// Ex Spieler
	std::string LetztesLand;
	std::string LetzterVerein;

	// Split Fields
	std::string Land_Und_FussballInlaender_Split_Land;
	std::string Land_Und_FussballInlaender_Split_FussballInlaender;
	std::string Nationalspieler_Und_Ruecktritt_Split_Nationalspieler;
	std::string Nationalspieler_Und_Ruecktritt_Split_Ruecktritt;
	std::string Haar_Und_Bart_Split_Haar;
	std::string Haar_Und_Bart_Split_Bart;

	// Split Bitmasks
	std::string Eigenschaft_Split_Bitmask_Eigenschaft1;
	std::string Eigenschaft_Split_Bitmask_Eigenschaft2;
	std::string Charakter_Split_Bitmask_Charakter1;
	std::string Charakter_Split_Bitmask_Charakter2;
	std::string Haar_Und_Bart_Split_Bart_Split_Bitmask_Unrasiert;
	std::string Haar_Und_Bart_Split_Bart_Split_Bitmask_Bart;
	std::string Haar_Und_Bart_Split_Bart_Split_Bitmask_Schnurbart;
	std::string Haar_Und_Bart_Split_Bart_Split_Bitmask_Ziegenbart;

	std::string PositiveFaehigkeiten_Split_Bitmask_Faehigkeit1;
	std::string PositiveFaehigkeiten_Split_Bitmask_Faehigkeit2;
	std::string PositiveFaehigkeiten_Split_Bitmask_Faehigkeit3;
	std::string NegativeFaehigkeiten_Split_Bitmask_Faehigkeit1;
	std::string NegativeFaehigkeiten_Split_Bitmask_Faehigkeit2;
	std::string NegativeFaehigkeiten_Split_Bitmask_Faehigkeit3;
	
	// Expanded Fields
	std::string LandZwei_Expanded;
	std::string LetztesLand_Expanded;
	std::string LetzterVerein_Expanded;
	std::string Land_Und_FussballInlaender_Split_Land_Expanded;

	// Combined Fields
	std::string Faehigkeiten_SpielerFaehigkeit1;
	std::string Faehigkeiten_SpielerFaehigkeit2;
	std::string Faehigkeiten_SpielerFaehigkeit3;
	std::string Faehigkeiten_TorwartFaehigkeit1;
	std::string Faehigkeiten_TorwartFaehigkeit2;
	std::string Faehigkeiten_TorwartFaehigkeit3;
};

void AssignSpielerField (std::vector<std::shared_ptr<section>>&, int, std::string&);
std::string GetNameFromSpielerSectionPosType (SPIELER_SECTION_POS_TYPE);
static SPIELER_SECTION_POS_TYPE GetPlayerSectionPosTypeFromString (const std::string&);
static bool IncludeSectionPosIntoA3Db (SPIELER_SECTION_POS_TYPE, SECTION_TYPE);
static bool IncludeSectionPosIntoXml (SPIELER_SECTION_POS_TYPE, const std::string&);
std::string GetPlayerCsvHeader ();
int GetSpielerHiddenOffset ();
void ConvertIllegalExSpielerReferences (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
static SPIELER_POSITION_POLARITY_TYPE GetSpielerPositionPolarityFromSectionPos (SPIELER_SECTION_POS_TYPE);
static SPIELER_POSITION_POLARITY_TYPE GetSpielerPositionPolarityFromString (const std::string&);
void MixSpielerFaehigkeiten(std::vector<std::shared_ptr<section>>);
void UnMixSpielerFaehigkeiten(std::vector<std::shared_ptr<section>>);
static void GetEnumDetails (int, int, ENUM_FUNC&, int&, int&);
static SPIELER_ENUM_TYPE GetSpielerEnumTypeFromPosition (SPIELER_SECTION_POS_TYPE);
SPIELER_BOOLEAN_TYPE GetSpielerBooleanTypeFromPosition (SPIELER_SECTION_POS_TYPE);
void GetSpielerAllowedValues (std::vector<FIELD_VALUE_STRUCT>&);
