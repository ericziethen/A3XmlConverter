#include "spieler.h"

#include "error_handling.h"
#include "a3_db_file_lib.h"
#include "bimap.h"
#include "nation.h"
#include "verein.h"
#include "a3_ui_text.h"

#include <sstream>
#include <iostream>

#define EXSPIELER_LAST_LAND_NONE "0"
#define EXSPIELER_LAST_LAND_VEREIN "0" 

spieler::spieler(void)
{
	// Default Letzter Verein
	this->LetztesLand = EXSPIELER_LAST_LAND_NONE;
	this->LetzterVerein = EXSPIELER_LAST_LAND_VEREIN;

	// Default Spielerfaehigkeiten
	this->PositiveFaehigkeiten_Split_Bitmask_Faehigkeit1 = SPIELER_NO_FAEHIGKEIT_STRING;
	this->PositiveFaehigkeiten_Split_Bitmask_Faehigkeit2 = SPIELER_NO_FAEHIGKEIT_STRING;
	this->PositiveFaehigkeiten_Split_Bitmask_Faehigkeit3 = SPIELER_NO_FAEHIGKEIT_STRING;
	this->NegativeFaehigkeiten_Split_Bitmask_Faehigkeit1 = SPIELER_NO_FAEHIGKEIT_STRING;
	this->NegativeFaehigkeiten_Split_Bitmask_Faehigkeit2 = SPIELER_NO_FAEHIGKEIT_STRING;
	this->NegativeFaehigkeiten_Split_Bitmask_Faehigkeit3 = SPIELER_NO_FAEHIGKEIT_STRING;	

	this->Faehigkeiten_SpielerFaehigkeit1 = SPIELER_NO_FAEHIGKEIT_STRING;
	this->Faehigkeiten_SpielerFaehigkeit2 = SPIELER_NO_FAEHIGKEIT_STRING;
	this->Faehigkeiten_SpielerFaehigkeit3 = SPIELER_NO_FAEHIGKEIT_STRING;
	this->Faehigkeiten_TorwartFaehigkeit1 = SPIELER_NO_FAEHIGKEIT_STRING;
	this->Faehigkeiten_TorwartFaehigkeit2 = SPIELER_NO_FAEHIGKEIT_STRING;
	this->Faehigkeiten_TorwartFaehigkeit3 = SPIELER_NO_FAEHIGKEIT_STRING;
}

spieler::~spieler(void)
{
}

std::string spieler::GetUniqueId ()
{
	return(this->GetParentId() + this->Nachnahme + this->Vornahme);
} // GetUniqueId

SECTION_TYPE spieler::GetSectionType ()
{
	return(SECTION_TYPE_SPIELER);
} // GetSectionType

std::string GetNameFromSpielerSectionPosType (SPIELER_SECTION_POS_TYPE PlayerSectionPosType)
{
  switch (PlayerSectionPosType)
  {
	case SPIELER_SECTION_POS_NACHNAHME:
		return ("Nachnahme");
	case SPIELER_SECTION_POS_VORNAHME:
		return ("Vornahme");
	case SPIELER_SECTION_POS_UNKNOWN_3:
		return ("PLAYER_FIELD_UNKNOWN_3");
	case SPIELER_SECTION_POS_HAUTFARBE:
		return ("Hautfarbe");
	case SPIELER_SECTION_POS_HAARFARBE:
		return ("Haarfarbe");
	case SPIELER_SECTION_POS_ALTER:
		return ("Alter");
	case SPIELER_SECTION_POS_STAERKE:
		return ("Staerke");
	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER:
		return ("Land_Und_FussballInlaender_UNSPLIT");
	case SPIELER_SECTION_POS_HAUPTPOSITION:
		return ("HauptPosition");
	case SPIELER_SECTION_POS_NEBEN_POSITION_1:
		return ("NebenPosition1");
	case SPIELER_SECTION_POS_NEBEN_POSITION_2:
		return ("NebenPosition2");
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN:
		return ("PositiveFaehigkeiten_UNSPLIT_BITMASK");
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN:
		return ("NegativeFaehigkeiten_UNSPLIT_BITMASK");
	case SPIELER_SECTION_POS_EIGENSCHAFTEN:
		return ("Eigenschaften_UNSPLIT_BITMASK");
	case SPIELER_SECTION_POS_CHARAKTER:
		return ("Charakter_UNSPLIT_BITMASK");
	case SPIELER_SECTION_POS_HATKUENSTLERNAHME:
		return ("HatKuenstlerNahme");
	case SPIELER_SECTION_POS_KUENSTLERNAHME:
		return ("KuenstlerNahme");
	case SPIELER_SECTION_POS_FUSS:
		return ("Fuss");
	case SPIELER_SECTION_POS_TALENT:
		return ("Talent");
	case SPIELER_SECTION_POS_GESUNDHEIT:
		return ("Gesundheit");
	case SPIELER_SECTION_POS_PUBLIKUM:
		return ("Publikum");
	case SPIELER_SECTION_POS_GEBURTSDATUM:
		return ("Geburtsdatum");
	case SPIELER_SECTION_POS_UNKNOWN_23:
		return ("PLAYER_FIELD_UNKNOWN_23");
	case SPIELER_SECTION_POS_LANDZWEI:
		return ("LandZwei_UNEXPANDED");
	case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT:
		return ("Nationalspieler_Und_Ruecktritt_UNSPLIT_BITMASK");
	case SPIELER_SECTION_POS_UNKNOWN_26:
		return ("PLAYER_FIELD_UNKNOWN_26");
	case SPIELER_SECTION_POS_UNKNOWN_27:
		return ("PLAYER_FIELD_UNKNOWN_27");
	case SPIELER_SECTION_POS_KAPITAENRUECKTRITT:
		return ("KapitaenRuecktritt");
	case SPIELER_SECTION_POS_RUECKENNUMMER:
		return ("RueckenNummer");
	case SPIELER_SECTION_POS_HAAR_UND_BART:
		return ("Haar_Und_Bart_UNSPLIT");
	case SPIELER_SECTION_POS_UNKNOWN_31:
		return ("PLAYER_FIELD_UNKNOWN_31");
	case SPIELER_SECTION_POS_UNKNOWN_32:
		return ("PLAYER_FIELD_UNKNOWN_32");
	case SPIELER_SECTION_POS_UNKNOWN_33:
		return ("PLAYER_FIELD_UNKNOWN_33");

	// Ex Spieler
	case SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND:
		return("LetztesLand_UNEXPANDED");
	case SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN:
		return("LetzterVerein_UNEXPANDED");

	// Split Fields		
	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND:
		return ("Nationalitaet_UNEXPANDED");
	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_FUSSBALLINLAENDER:
		return ("FussballInlaender");
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_HAAR: 
		return ("Haar");
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART: 
		return ("Bart_UNSPLIT_BITMASK");

	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1: 
		return ("PositiveFaehigkeit1_UNCOMBINED");
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2: 
		return ("PositiveFaehigkeit2_UNCOMBINED");
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3: 
		return ("PositiveFaehigkeit3_UNCOMBINED");
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1:
		return ("NegativeFaehigkeit1_UNCOMBINED");	
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2:	
		return ("NegativeFaehigkeit2_UNCOMBINED");	
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3:	
		return ("NegativeFaehigkeit3_UNCOMBINED");	

		// Split Bitmasks
	case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_NATIONALSPIELER: 
		return ("Nationalspieler");
	case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_RUECKTRITT:
		return ("RuecktrittNationalmannschaft");
	case SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT1:
		return ("Eigenschaft1");
	case SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT2:
		return ("Eigenschaft2");
	case SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER1:
		return ("Charakter1");
	case SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER2:
		return ("Charakter2");

	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_UNRASIERT:
		return ("Unrasiert");
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_BART:
		return ("Bart");
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_SCHNURBART: 
		return ("Schnurbart");
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_ZIEGENBART: 
		return ("Ziegenbart");

	// Expanded Fields
	case SPIELER_SECTION_POS_LANDZWEI_EXPANDED:
		return ("ZweiteNationalitaet");
	case SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND_EXPANDED:
		return("LetztesLand");
	case SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN_EXPANDED:
		return("LetzterVerein");
	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND_EXPANDED:
		return ("Nationalitaet");

		// Combined Fields
	case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_1:
		return ("SpielerFaehigkeit1");
	case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_2:
		return ("SpielerFaehigkeit2");
	case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_3:
		return ("SpielerFaehigkeit3");
	case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_1:
		return ("TorwartFaehigkeit1");
	case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_2:
		return ("TorwartFaehigkeit2");
	case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_3:
		return ("TorwartFaehigkeit3");

	case SPIELER_SECTION_POS_VEREIN:
		return ("Verein");

	default:
      std::stringstream ErrorText;
	  ErrorText << "Unhandled Player Section Pos Type " << PlayerSectionPosType << " -> " <<__FUNCTION__;
      programError (ErrorText.str());
	  return (ErrorText.str().c_str());
  } // switch
} // GetNameFromSpielerSectionPosType

SPIELER_ENUM_TYPE spieler::GetPositionEnum ()
{
	// Get the Position String
	std::string PositionStr = this->GetValueAtSectionPos(SPIELER_SECTION_POS_HAUPTPOSITION);

	SPIELER_POSITION_TYPE Position;
	if (StringIsNumber(PositionStr))
	{
		int PositionStrInt = T_StringToNumber<int>(PositionStr);

		// Convert the Position string into its Value
		Position = (SPIELER_POSITION_TYPE) GetSpielerEnumValue (SPIELER_ENUM_POSITION, ENUM_VALUE_SIDE_RIGHT, PositionStrInt);
	} // Pos not converted
	else
	{
		Position = (SPIELER_POSITION_TYPE) StringToEnum (PositionStr, SPIELER_POSITION_UNKNOWN, NO_OF_SPIELER_POSITION_TYPES, GetNameFromSpielerPositionType);
	} // Pos converted

	SPIELER_ENUM_TYPE PositionEnum;
	if (Position == SPIELER_POSITION_TORWART)
		PositionEnum = SPIELER_ENUM_TORWARTFAEHIGKEITEN;
	else
		PositionEnum = SPIELER_ENUM_SPIELERFAEHIGKEITEN;

	// Return the position enum
	return (PositionEnum);

} // GetPositionEnum

std::string GetPlayerCsvHeader ()
{
  int EnumVal;
  std::stringstream CsvLine;

  CsvLine.str (std::string());
  for (EnumVal = SPIELER_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_SPIELER_SECTION_POS_TYPES; EnumVal++)
  {
	  CsvLine << GetNameFromSpielerSectionPosType ((SPIELER_SECTION_POS_TYPE) EnumVal) << ", ";  
  }

  return (CsvLine.str());
} // GetPlayerCsvHeader

void spieler::AssignField (int SectionPos, const std::string& FieldValue)
{	
  switch (SectionPos)
  {
		case SPIELER_SECTION_POS_UNKNOWN:
			break;

		case SPIELER_SECTION_POS_VEREIN:
			this->SetParentId(FieldValue);
			break;

		case SPIELER_SECTION_POS_NACHNAHME: 
			this->Nachnahme = FieldValue;
			break;

		case SPIELER_SECTION_POS_VORNAHME: 
			this->Vornahme = FieldValue;
			break;

		case SPIELER_SECTION_POS_UNKNOWN_3: 
			this->PLAYER_FIELD_UNKNOWN_3 = FieldValue;
			break;

		case SPIELER_SECTION_POS_HAUTFARBE: 
			this->Hautfarbe = FieldValue;
			break;

		case SPIELER_SECTION_POS_HAARFARBE: 
			this->Haarfarbe = FieldValue;
			break;

		case SPIELER_SECTION_POS_ALTER: 
			this->Alter = FieldValue;
			break;

		case SPIELER_SECTION_POS_STAERKE: 
			this->Staerke = FieldValue;
			break;

		case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER: 
			this->Land_Und_FussballInlaender = FieldValue;
			break;

		case SPIELER_SECTION_POS_HAUPTPOSITION: 
			this->HauptPosition = FieldValue;
			break;

		case SPIELER_SECTION_POS_NEBEN_POSITION_1: 
			this->NebenPosition1 = FieldValue;
			break;

		case SPIELER_SECTION_POS_NEBEN_POSITION_2: 
			this->NebenPosition2 = FieldValue;
			break;

		case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN: 
			this->PositiveFaehigkeiten = FieldValue;
			break;

		case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN: 
			this->NegativeFaehigkeiten = FieldValue;
			break;

		case SPIELER_SECTION_POS_EIGENSCHAFTEN: 
			this->Eigenschaften = FieldValue;
			break;

		case SPIELER_SECTION_POS_CHARAKTER: 
			this->Charakter = FieldValue;
			break;

		case SPIELER_SECTION_POS_HATKUENSTLERNAHME: 
			this->HatKuenstlerNahme = FieldValue;
			break;

		case SPIELER_SECTION_POS_KUENSTLERNAHME: 
			this->KuenstlerNahme = FieldValue;
			break;

		case SPIELER_SECTION_POS_FUSS: 
			this->Fuss = FieldValue;
			break;

		case SPIELER_SECTION_POS_TALENT: 
			this->Talent = FieldValue;
			break;

		case SPIELER_SECTION_POS_GESUNDHEIT: 
			this->Gesundheit = FieldValue;
			break;

		case SPIELER_SECTION_POS_PUBLIKUM: 
			this->Publikum = FieldValue;
			break;

		case SPIELER_SECTION_POS_GEBURTSDATUM: 
			this->Geburtsdatum = FieldValue;
			break;

		case SPIELER_SECTION_POS_UNKNOWN_23: 
			this->PLAYER_FIELD_UNKNOWN_23 = FieldValue;
			break;

		case SPIELER_SECTION_POS_LANDZWEI: 
			this->LandZwei = FieldValue;
			break;

		case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT: 
			this->Nationalspieler_Und_Ruecktritt = FieldValue;
			break;

		case SPIELER_SECTION_POS_UNKNOWN_26: 
			this->PLAYER_FIELD_UNKNOWN_26 = FieldValue;
			break;

		case SPIELER_SECTION_POS_UNKNOWN_27: 
			this->PLAYER_FIELD_UNKNOWN_27 = FieldValue;
			break;

		case SPIELER_SECTION_POS_KAPITAENRUECKTRITT: 
			this->KapitaenRuecktritt = FieldValue;
			break;

		case SPIELER_SECTION_POS_RUECKENNUMMER: 
			this->RueckenNummer = FieldValue;
			break;

		case SPIELER_SECTION_POS_HAAR_UND_BART: 
			this->Haar_Und_Bart = FieldValue;
			break;

		case SPIELER_SECTION_POS_UNKNOWN_31: 
			this->PLAYER_FIELD_UNKNOWN_31 = FieldValue;
			break;

		case SPIELER_SECTION_POS_UNKNOWN_32: 
			this->PLAYER_FIELD_UNKNOWN_32 = FieldValue;
			break;

		case SPIELER_SECTION_POS_UNKNOWN_33: 
			this->PLAYER_FIELD_UNKNOWN_33 = FieldValue;
			break;

		case SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND:
			this->LetztesLand = FieldValue;
			break;

		case SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN:
			this->LetzterVerein = FieldValue;
			break;

		case SPIELER_SECTION_POS_LANDZWEI_EXPANDED:
			this->LandZwei_Expanded = FieldValue;
			break;

		case SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND_EXPANDED:
			this->LetztesLand_Expanded = FieldValue;
			break;

		case SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN_EXPANDED:
			this->LetzterVerein_Expanded = FieldValue;
			break;

		case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND:
			this->Land_Und_FussballInlaender_Split_Land = FieldValue;
			break;

		case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_FUSSBALLINLAENDER:
			this->Land_Und_FussballInlaender_Split_FussballInlaender = FieldValue;
			break;

		case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_HAAR: 
			this->Haar_Und_Bart_Split_Haar = FieldValue;
			break;

		case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART: 
			this->Haar_Und_Bart_Split_Bart = FieldValue;
			break;

		case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_NATIONALSPIELER: 
			this->Nationalspieler_Und_Ruecktritt_Split_Nationalspieler = FieldValue;
			break;

		case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_RUECKTRITT:
			this->Nationalspieler_Und_Ruecktritt_Split_Ruecktritt = FieldValue;
			break;

		case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND_EXPANDED:
			this->Land_Und_FussballInlaender_Split_Land_Expanded = FieldValue;
			break;

		case SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT1:
			this->Eigenschaft_Split_Bitmask_Eigenschaft1 = FieldValue;
			break;

		case SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT2:
			this->Eigenschaft_Split_Bitmask_Eigenschaft2 = FieldValue;
			break;

		case SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER1:
			this->Charakter_Split_Bitmask_Charakter1 = FieldValue;
			break;
		case SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER2:
			this->Charakter_Split_Bitmask_Charakter2 = FieldValue;
			break;

		case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_UNRASIERT:
			this->Haar_Und_Bart_Split_Bart_Split_Bitmask_Unrasiert = FieldValue;
			break;
		case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_BART:
			this->Haar_Und_Bart_Split_Bart_Split_Bitmask_Bart = FieldValue;
			break;
		case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_SCHNURBART: 
			this->Haar_Und_Bart_Split_Bart_Split_Bitmask_Schnurbart = FieldValue;
			break;
		case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_ZIEGENBART: 
			this->Haar_Und_Bart_Split_Bart_Split_Bitmask_Ziegenbart = FieldValue;
			break;

		case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1: 
			this->PositiveFaehigkeiten_Split_Bitmask_Faehigkeit1 = FieldValue;
			break;
		case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2: 
			this->PositiveFaehigkeiten_Split_Bitmask_Faehigkeit2 = FieldValue;
			break;
		case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3: 
			this->PositiveFaehigkeiten_Split_Bitmask_Faehigkeit3 = FieldValue;
			break;
		case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1:	
			this->NegativeFaehigkeiten_Split_Bitmask_Faehigkeit1 = FieldValue;
			break;
		case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2:
			this->NegativeFaehigkeiten_Split_Bitmask_Faehigkeit2 = FieldValue;	
			break;
		case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3:
			this->NegativeFaehigkeiten_Split_Bitmask_Faehigkeit3 = FieldValue;
			break;

		// Special 
		case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_1:
			this->Faehigkeiten_SpielerFaehigkeit1 = FieldValue;
			break;
		case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_2:
			this->Faehigkeiten_SpielerFaehigkeit2 = FieldValue;
			break;
		case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_3:
			this->Faehigkeiten_SpielerFaehigkeit3 = FieldValue;
			break;
		case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_1:
			this->Faehigkeiten_TorwartFaehigkeit1 = FieldValue;
			break;
		case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_2:
			this->Faehigkeiten_TorwartFaehigkeit2 = FieldValue;
			break;
		case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_3:
			this->Faehigkeiten_TorwartFaehigkeit3 = FieldValue;
			break;

	  default:
		  std::stringstream ErrorText;
		  ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		  programError (ErrorText.str());
  }

} /* AssignField */

std::string spieler::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
		case SPIELER_SECTION_POS_VEREIN:
			return (this->GetParentId());

		case SPIELER_SECTION_POS_NACHNAHME: 
			return (this->Nachnahme);

		case SPIELER_SECTION_POS_VORNAHME: 
			return (this->Vornahme);

		case SPIELER_SECTION_POS_UNKNOWN_3: 
			return (this->PLAYER_FIELD_UNKNOWN_3);

		case SPIELER_SECTION_POS_HAUTFARBE: 
			return (this->Hautfarbe);

		case SPIELER_SECTION_POS_HAARFARBE: 
			return (this->Haarfarbe);

		case SPIELER_SECTION_POS_ALTER: 
			return (this->Alter);

		case SPIELER_SECTION_POS_STAERKE: 
			return (this->Staerke);

		case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER: 
			return (this->Land_Und_FussballInlaender);

		case SPIELER_SECTION_POS_HAUPTPOSITION: 
			return (this->HauptPosition);

		case SPIELER_SECTION_POS_NEBEN_POSITION_1: 
			return (this->NebenPosition1);

		case SPIELER_SECTION_POS_NEBEN_POSITION_2: 
			return (this->NebenPosition2);

		case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN: 
			return (this->PositiveFaehigkeiten);

		case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN: 
			return (this->NegativeFaehigkeiten);

		case SPIELER_SECTION_POS_EIGENSCHAFTEN: 
			return (this->Eigenschaften);

		case SPIELER_SECTION_POS_CHARAKTER: 
			return (this->Charakter);

		case SPIELER_SECTION_POS_HATKUENSTLERNAHME: 
			return (this->HatKuenstlerNahme);

		case SPIELER_SECTION_POS_KUENSTLERNAHME: 
			return (this->KuenstlerNahme);

		case SPIELER_SECTION_POS_FUSS: 
			return (this->Fuss);

		case SPIELER_SECTION_POS_TALENT: 
			return (this->Talent);

		case SPIELER_SECTION_POS_GESUNDHEIT: 
			return (this->Gesundheit);

		case SPIELER_SECTION_POS_PUBLIKUM: 
			return (this->Publikum);

		case SPIELER_SECTION_POS_GEBURTSDATUM: 
			return (this->Geburtsdatum);

		case SPIELER_SECTION_POS_UNKNOWN_23: 
			return (this->PLAYER_FIELD_UNKNOWN_23);

		case SPIELER_SECTION_POS_LANDZWEI: 
			return (this->LandZwei);

		case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT: 
			return (this->Nationalspieler_Und_Ruecktritt);

		case SPIELER_SECTION_POS_UNKNOWN_26: 
			return (this->PLAYER_FIELD_UNKNOWN_26);

		case SPIELER_SECTION_POS_UNKNOWN_27: 
			return (this->PLAYER_FIELD_UNKNOWN_27);

		case SPIELER_SECTION_POS_KAPITAENRUECKTRITT: 
			return (this->KapitaenRuecktritt);

		case SPIELER_SECTION_POS_RUECKENNUMMER: 
			return (this->RueckenNummer);

		case SPIELER_SECTION_POS_HAAR_UND_BART: 
			return (this->Haar_Und_Bart);

		case SPIELER_SECTION_POS_UNKNOWN_31: 
			return (this->PLAYER_FIELD_UNKNOWN_31);

		case SPIELER_SECTION_POS_UNKNOWN_32: 
			return (this->PLAYER_FIELD_UNKNOWN_32);

		case SPIELER_SECTION_POS_UNKNOWN_33: 
			return (this->PLAYER_FIELD_UNKNOWN_33);

		case SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND:
			return(this->LetztesLand);

		case SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN:
			return(this->LetzterVerein);

		case SPIELER_SECTION_POS_LANDZWEI_EXPANDED:
			return(this->LandZwei_Expanded);

		case SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND_EXPANDED:
			return(this->LetztesLand_Expanded);

		case SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN_EXPANDED:
			return(this->LetzterVerein_Expanded);

		case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND:
			return(this->Land_Und_FussballInlaender_Split_Land);

		case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_FUSSBALLINLAENDER:
			return(this->Land_Und_FussballInlaender_Split_FussballInlaender);

		case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_HAAR: 
			return(this->Haar_Und_Bart_Split_Haar);

		case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART: 
			return(this->Haar_Und_Bart_Split_Bart);

		case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_NATIONALSPIELER: 
			return(this->Nationalspieler_Und_Ruecktritt_Split_Nationalspieler);

		case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_RUECKTRITT:
			return(this->Nationalspieler_Und_Ruecktritt_Split_Ruecktritt);
			
		case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND_EXPANDED:
			return(this->Land_Und_FussballInlaender_Split_Land_Expanded);

		case SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT1:
			return(this->Eigenschaft_Split_Bitmask_Eigenschaft1);

		case SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT2:
			return(this->Eigenschaft_Split_Bitmask_Eigenschaft2);

		case SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER1:
			return(this->Charakter_Split_Bitmask_Charakter1);

		case SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER2:
			return(this->Charakter_Split_Bitmask_Charakter2);

		case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_UNRASIERT:
			return(this->Haar_Und_Bart_Split_Bart_Split_Bitmask_Unrasiert);
		case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_BART:
			return(this->Haar_Und_Bart_Split_Bart_Split_Bitmask_Bart);
		case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_SCHNURBART: 
			return(this->Haar_Und_Bart_Split_Bart_Split_Bitmask_Schnurbart);
		case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_ZIEGENBART: 
			return(this->Haar_Und_Bart_Split_Bart_Split_Bitmask_Ziegenbart);

		case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1: 
			return(this->PositiveFaehigkeiten_Split_Bitmask_Faehigkeit1);
		case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2: 
			return(this->PositiveFaehigkeiten_Split_Bitmask_Faehigkeit2);
		case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3: 
			return(this->PositiveFaehigkeiten_Split_Bitmask_Faehigkeit3);
		case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1:	
			return(this->NegativeFaehigkeiten_Split_Bitmask_Faehigkeit1);
		case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2:
			return(this->NegativeFaehigkeiten_Split_Bitmask_Faehigkeit2);	
		case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3:
			return(this->NegativeFaehigkeiten_Split_Bitmask_Faehigkeit3);

		case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_1:
			return(this->Faehigkeiten_SpielerFaehigkeit1);
		case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_2:
			return(this->Faehigkeiten_SpielerFaehigkeit2);
		case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_3:
			return(this->Faehigkeiten_SpielerFaehigkeit3);
		case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_1:
			return(this->Faehigkeiten_TorwartFaehigkeit1);
		case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_2:
			return(this->Faehigkeiten_TorwartFaehigkeit2);
		case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_3:
			return(this->Faehigkeiten_TorwartFaehigkeit3);

		default:
			std::stringstream ErrorText;
			ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
			programError (ErrorText.str());	
			return(ErrorText.str());
	}

} // GetValueAtSectionPos

void spieler::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	std::stringstream ErrorText;
	ErrorText << "Unexpected Execution of this Version of the function: " << " -> " <<__FUNCTION__;
	programError (ErrorText.str());	
} // PopulateValuePairVectorForExport

void spieler::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector, const std::string& A3DbFilename)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int PlayerPos = SPIELER_SECTION_POS_UNKNOWN + 1; PlayerPos < NO_OF_SPIELER_SECTION_POS_TYPES; PlayerPos++)
	{
		if (IncludeSectionPosIntoXml ((SPIELER_SECTION_POS_TYPE) PlayerPos, A3DbFilename))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromSpielerSectionPosType ((SPIELER_SECTION_POS_TYPE) PlayerPos), 			
				this->GetValueAtSectionPos(PlayerPos))));
		}
	}

} // PopulateValuePairVectorForExport

void spieler::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& PlayerValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = PlayerValuePairs.begin(); 
		Iterator != PlayerValuePairs.end(); ++Iterator)
	{
		SPIELER_SECTION_POS_TYPE FieldPos = GetPlayerSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != SPIELER_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void spieler::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = SPIELER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_SPIELER_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((SPIELER_SECTION_POS_TYPE) TempPos, DataSection))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void spieler::DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Land Field
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, SPIELER_SECTION_POS_LANDZWEI, SPIELER_SECTION_POS_LANDZWEI_EXPANDED, SectionList);
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND, SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND_EXPANDED, SectionList);
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND, 
							SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND_EXPANDED, SectionList);	

	// Decode Verein Field
	this->ConvertVereinField(SECTION_EXPANSION_FROM_A3DB_VEREIN, SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN, SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN_EXPANDED, 
								this->GetValueAtSectionPos(SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND), SectionList);
} // DecodeFieldsFromA3Db

void spieler::EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE ReferenceType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	switch (ReferenceType)
	{
	case FIELD_REFERENCE_LAND:
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, SPIELER_SECTION_POS_LANDZWEI_EXPANDED, SPIELER_SECTION_POS_LANDZWEI, SectionList);
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND_EXPANDED, SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND, SectionList);
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND_EXPANDED, 
			SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND, SectionList);
		break;

	case FIELD_REFERENCE_VEREIN:
		this->ConvertVereinField(SECTION_EXPANSION_TO_A3DB_VEREIN, SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN_EXPANDED, SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN, 
			this->GetValueAtSectionPos(SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND), SectionList);
		break;

	default:
		break;
	} // switch reference types
} // EncodeFieldsToA3Db 

void spieler::PostSavSplitCombinedFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	ENUM_VALUE_LIST ValueList;
	
	// Split Land and Fussballinlaender
	ValueList.clear();
	this->SplitJoinedField (this->GetValueAtSectionPos(SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER), GetSpielerEnumValueList(SPIELER_ENUM_FUSSBALLINLAENDER, ValueList), 
		SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_FUSSBALLINLAENDER, SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND);

	// Split Haar und Bart
	ValueList.clear();
	this->SplitJoinedField (this->GetValueAtSectionPos(SPIELER_SECTION_POS_HAAR_UND_BART), GetSpielerEnumValueList(SPIELER_ENUM_HAAR, ValueList), 
		SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_HAAR, SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART);
	
} // PostSavSplitCombinedFields

void spieler::PostExternalMergeSplitFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Merge Land and Fussballinlaender
	this->MergeSplitField (SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER);

	// Merge Haar und Bart
	this->MergeSplitField (SPIELER_SECTION_POS_HAAR_UND_BART);

} // PostExternalMergeSplitFields

void spieler::SplitBitmaskFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	ENUM_VALUE_LIST BitmaskFields;

	// Split Eigenschaften
	this->SplitBitmaskField (SPIELER_SECTION_POS_EIGENSCHAFTEN, GetSpielerEnumValueList(SPIELER_ENUM_EIGENSCHAFTEN, BitmaskFields));

	// Split Charakter
	this->SplitBitmaskField (SPIELER_SECTION_POS_CHARAKTER, GetSpielerEnumValueList(SPIELER_ENUM_CHARAKTER, BitmaskFields));

	// Split Bart
	this->SplitBitmaskField (SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART, GetSpielerEnumValueList(SPIELER_ENUM_BART, BitmaskFields));

	// Split Nationalspieler und Ruecktritt
	this->SplitBitmaskField (SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT, GetSpielerEnumValueList(SPIELER_ENUM_NATIONALSPIELER_UND_RUECKTRITT, BitmaskFields));

	// Split Positive Eigenschaften
	this->SplitBitmaskField (SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN, GetSpielerEnumValueList(this->GetPositionEnum(), BitmaskFields));

	// Split Negative Eigenschaften
	this->SplitBitmaskField (SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN, GetSpielerEnumValueList(this->GetPositionEnum(), BitmaskFields));

} // SplitBitmaskFields

void spieler::MergeBitmaskFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	ENUM_VALUE_LIST BitmaskFields;

	// Merge Eigenschaften
	this->MergeBitmaskField (SPIELER_SECTION_POS_EIGENSCHAFTEN, GetSpielerEnumValueList(SPIELER_ENUM_EIGENSCHAFTEN, BitmaskFields));

	// Merge Charakter
	this->MergeBitmaskField (SPIELER_SECTION_POS_CHARAKTER, GetSpielerEnumValueList(SPIELER_ENUM_CHARAKTER, BitmaskFields));

	// Merge Bart
	this->MergeBitmaskField (SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART, GetSpielerEnumValueList(SPIELER_ENUM_BART, BitmaskFields));

	// Merge Nationalspieler und Ruecktritt
	this->MergeBitmaskField (SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT, GetSpielerEnumValueList(SPIELER_ENUM_NATIONALSPIELER_UND_RUECKTRITT, BitmaskFields));

	// Merge Positive Eigenschaften
	this->MergeBitmaskField (SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN, GetSpielerEnumValueList(this->GetPositionEnum(), BitmaskFields));

	// Merge Negative Eigenschaften
	this->MergeBitmaskField (SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN, GetSpielerEnumValueList(this->GetPositionEnum(), BitmaskFields));

} // MergeBitmaskFields

void spieler::DecodeBooleansFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Boolean HatKuenstlernahme
	this->DecodeBooleanFromA3Db(SPIELER_SECTION_POS_HATKUENSTLERNAHME);

	// Decode Boolean IstNationalspieler
	this->DecodeBooleanFromA3Db(SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_NATIONALSPIELER);

	// Decode Boolean NationalspielerRuecktritt
	this->DecodeBooleanFromA3Db(SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_RUECKTRITT);

	// Decode Boolean KapitaenRuecktritt
	this->DecodeBooleanFromA3Db(SPIELER_SECTION_POS_KAPITAENRUECKTRITT);

	// Decode Boolean BartUnrasiert
	this->DecodeBooleanFromA3Db(SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_UNRASIERT);

	// Decode Boolean BartBart
	this->DecodeBooleanFromA3Db(SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_BART);

	// Decode Boolean BartSchnurbart
	this->DecodeBooleanFromA3Db(SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_SCHNURBART);

	// Decode Boolean BartZiegenbart
	this->DecodeBooleanFromA3Db(SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_ZIEGENBART);

	// Decode Boolean Fussballinlaender
	this->DecodeBooleanFromA3Db(SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_FUSSBALLINLAENDER);

} // DecodeBooleansFromA3Db

void spieler::EncodeBooleansToA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Boolean HatKuenstlernahme
	this->EncodeBooleanToA3Db(SPIELER_SECTION_POS_HATKUENSTLERNAHME, 
		GetValueFromSpielerBooleanType(SPIELER_BOOLEAN_HAT_KUENSTLERNAHME));

	// Encode Boolean IstNationalspieler
	this->EncodeBooleanToA3Db(SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_NATIONALSPIELER, 
		GetValueFromSpielerBooleanType(SPIELER_BOOLEAN_IST_NATIONALSPIELER));

	// Encode Boolean NationalspielerRuecktritt
	this->EncodeBooleanToA3Db(SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_RUECKTRITT, 
		GetValueFromSpielerBooleanType(SPIELER_BOOLEAN_NATIONALSPIELER_RUECKTRITT));

	// Encode Boolean KapitaenRuecktritt
	this->EncodeBooleanToA3Db(SPIELER_SECTION_POS_KAPITAENRUECKTRITT, 
		GetValueFromSpielerBooleanType(SPIELER_BOOLEAN_KAPITAEN_RUECKTRITT));

	// Encode Boolean BartUnrasiert
	this->EncodeBooleanToA3Db(SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_UNRASIERT, 
		GetValueFromSpielerBooleanType(SPIELER_BOOLEAN_BART_UNRASIERT));

	// Encode Boolean BartBart
	this->EncodeBooleanToA3Db(SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_BART, 
		GetValueFromSpielerBooleanType(SPIELER_BOOLEAN_BART_BART));

	// Encode Boolean BartSchnurbart
	this->EncodeBooleanToA3Db(SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_SCHNURBART, 
		GetValueFromSpielerBooleanType(SPIELER_BOOLEAN_BART_SCHNURBART));

	// Encode Boolean BartZiegenbart
	this->EncodeBooleanToA3Db(SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_ZIEGENBART, 
		GetValueFromSpielerBooleanType(SPIELER_BOOLEAN_BART_ZIEGENBART));

	// Encode Boolean Fussballinlaender
	this->EncodeBooleanToA3Db(SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_FUSSBALLINLAENDER, 
		GetValueFromSpielerBooleanType(SPIELER_BOOLEAN_FUSSBALLINLAENDER));
	
} // EncodeBooleansToA3Db

void spieler::DecodeEnumsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Enum Hautfarbe
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_HAUTFARBE, SPIELER_ENUM_HAUTFARBE, GetSpielerEnumValue, GetEnumDetails);
	
	// Decode Enum Haarfarbe
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_HAARFARBE, SPIELER_ENUM_HAARFARBE, GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Nebenposition 1
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_NEBEN_POSITION_1, SPIELER_ENUM_POSITION, GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Nebenposition 2
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_NEBEN_POSITION_2, SPIELER_ENUM_POSITION, GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Eigenschaft1
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT1, SPIELER_ENUM_EIGENSCHAFTEN, GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Eigenschaft2
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT2, SPIELER_ENUM_EIGENSCHAFTEN, GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Charakter1
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER1, SPIELER_ENUM_CHARAKTER, GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Charakter2
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER2, SPIELER_ENUM_CHARAKTER, GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Fuss
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_FUSS, SPIELER_ENUM_FUSS, GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Talent
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_TALENT, SPIELER_ENUM_TALENT, GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Gesundheit
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_GESUNDHEIT, SPIELER_ENUM_GESUNDHEIT, GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Publikum
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_PUBLIKUM, SPIELER_ENUM_PUBLIKUM, GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Haar
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_HAAR, SPIELER_ENUM_HAAR, GetSpielerEnumValue, GetEnumDetails);




	// Decode Enum Positive Faehigkeit1
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1, this->GetPositionEnum(), GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Positive Faehigkeit2
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2, this->GetPositionEnum(), GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Positive Faehigkeit3
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3, this->GetPositionEnum(), GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Negative Faehigkeit1
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1, this->GetPositionEnum(), GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Negative Faehigkeit2
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2, this->GetPositionEnum(), GetSpielerEnumValue, GetEnumDetails);

	// Decode Enum Negative Faehigkeit3
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3, this->GetPositionEnum(), GetSpielerEnumValue, GetEnumDetails);




	// LAST FIELD - Hauoptposition is used for looking up other values, decode last
	// Decode Enum Hauptposition
	this->DecodeEnumFromA3Db(SPIELER_SECTION_POS_HAUPTPOSITION, SPIELER_ENUM_POSITION, GetSpielerEnumValue, GetEnumDetails);
} // DecodeEnumsFromA3Db

void spieler::EncodeEnumsToA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{

	// FIRST FIELD - Hauoptposition is used for looking up other values, encode first
	// Encode Enum Hauptposition
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_HAUPTPOSITION, SPIELER_ENUM_POSITION, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Hautfarbe
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_HAUTFARBE, SPIELER_ENUM_HAUTFARBE, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Haarfarbe
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_HAARFARBE, SPIELER_ENUM_HAARFARBE, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Nebenposition 1
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_NEBEN_POSITION_1, SPIELER_ENUM_POSITION, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Nebenposition 2
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_NEBEN_POSITION_2, SPIELER_ENUM_POSITION, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Eigenschaft1
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT1, SPIELER_ENUM_EIGENSCHAFTEN, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Eigenschaft2
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT2, SPIELER_ENUM_EIGENSCHAFTEN, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Charakter1
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER1, SPIELER_ENUM_CHARAKTER, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Charakter2
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER2, SPIELER_ENUM_CHARAKTER, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Fuss
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_FUSS, SPIELER_ENUM_FUSS, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Talent
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_TALENT, SPIELER_ENUM_TALENT, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Gesundheit
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_GESUNDHEIT, SPIELER_ENUM_GESUNDHEIT, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Publikum
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_PUBLIKUM, SPIELER_ENUM_PUBLIKUM, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Haar
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_HAAR, SPIELER_ENUM_HAAR, GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Positive Faehigkeit1
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1, this->GetPositionEnum(), GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Positive Faehigkeit2
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2, this->GetPositionEnum(), GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Positive Faehigkeit3
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3, this->GetPositionEnum(), GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Negative Faehigkeit1
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1, this->GetPositionEnum(), GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Negative Faehigkeit2
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2, this->GetPositionEnum(), GetSpielerEnumValue, GetEnumDetails);

	// Encode Enum Negative Faehigkeit3
	this->EncodeEnumToA3Db(SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3, this->GetPositionEnum(), GetSpielerEnumValue, GetEnumDetails);

} // EncodeEnumsToA3Db

void GetEnumDetails (int SectionPos, int EnumType, ENUM_FUNC& EnumFunc, int& EnumLow, int& EnumHigh)
{
	SPIELER_POSITION_POLARITY_TYPE PositionPolarity;
	switch ((SPIELER_ENUM_TYPE) EnumType)
	{
	case SPIELER_ENUM_FUSSBALLINLAENDER:
		EnumFunc = GetNameFromSpielerFussballinlaenderType;
		EnumLow = SPIELER_FUSSBALLINLAENDER_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_FUSSBALLINLAENDER_TYPES;
		break;

	case SPIELER_ENUM_HAAR:
		EnumFunc = GetNameFromSpielerHaarType;
		EnumLow = SPIELER_HAARFARBE_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_HAAR_TYPES;
		break;

	case SPIELER_ENUM_BART:
		EnumFunc = GetNameFromSpielerBartType;
		EnumLow = SPIELER_BART_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_BART_TYPES;
		break;

	case SPIELER_ENUM_NATIONALSPIELER_UND_RUECKTRITT:
		EnumFunc = GetNameFromSpielerNationalspielerUndRuecktrittType;
		EnumLow = SPIELER_NATIONALSPIELER_UND_RUECKTRITT_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_NATIONALSPIELER_UND_RUECKTRITT_TYPES;
		break;

	case SPIELER_ENUM_EIGENSCHAFTEN:
		EnumFunc = GetNameFromSpielerEigenschaftenType;
		EnumLow = SPIELER_EIGENSCHAFTEN_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_EIGENSCHAFTEN_TYPES;
		break;

	case SPIELER_ENUM_TORWARTFAEHIGKEITEN:
		PositionPolarity = GetSpielerPositionPolarityFromSectionPos ((SPIELER_SECTION_POS_TYPE) SectionPos);
		if (PositionPolarity == SPIELER_POSITION_POLARITY_POSITIVE)
			EnumFunc = GetPositiveNameFromSpielerTorwartFaehigkeitenType;
		else // else ok, as we Checked validity earlier and don't use triple nested switch
			EnumFunc = GetNegativeNameFromSpielerTorwartFaehigkeitenType;

		EnumLow = SPIELER_TORWARTFAEHIGKEITEN_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_TORWARTFAEHIGKEITEN_TYPES;
		break;

	case SPIELER_ENUM_SPIELERFAEHIGKEITEN:
		PositionPolarity = GetSpielerPositionPolarityFromSectionPos ((SPIELER_SECTION_POS_TYPE) SectionPos);
		if (PositionPolarity == SPIELER_POSITION_POLARITY_POSITIVE)
			EnumFunc = GetPositiveNameFromSpielerFaehigkeitenType;
		else // else ok, as we Checked validity earlier and don't use triple nested switch
			EnumFunc = GetNegativeNameFromSpielerFaehigkeitenType;

		EnumLow = SPIELER_SPIELERFAEHIGKEITEN_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_SPIELERFAEHIGKEITEN_TYPES;
		break;

	case SPIELER_ENUM_CHARAKTER:
		EnumFunc = GetNameFromSpielerCharakterType;
		EnumLow = SPIELER_CHARAKTER_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_CHARAKTER_TYPES;
		break;

	case SPIELER_ENUM_HAUTFARBE:
		EnumFunc = GetNameFromSpielerHautfarbeType;
		EnumLow = SPIELER_HAUTFARBE_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_HAUTFARBE_TYPES;
		break;

	case SPIELER_ENUM_HAARFARBE:
		EnumFunc = GetNameFromSpielerHaarfarbeType;
		EnumLow = SPIELER_HAARFARBE_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_HAARFARBE_TYPES;
		break;

	case SPIELER_ENUM_POSITION:
		EnumFunc = GetNameFromSpielerPositionType;
		EnumLow = SPIELER_POSITION_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_POSITION_TYPES;
		break;

	case SPIELER_ENUM_FUSS:
		EnumFunc = GetNameFromSpielerFussType;
		EnumLow = SPIELER_FUSS_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_FUSS_TYPES;
		break;

	case SPIELER_ENUM_TALENT:
		EnumFunc = GetNameFromSpielerTalentType;
		EnumLow = SPIELER_TALENT_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_TALENT_TYPES;
		break;

	case SPIELER_ENUM_GESUNDHEIT:
		EnumFunc = GetNameFromSpielerGesundheitType;
		EnumLow = SPIELER_GESUNDHEIT_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_GESUNDHEIT_TYPES;
		break;

	case SPIELER_ENUM_PUBLIKUM:
		EnumFunc = GetNameFromSpielerPublikumType;
		EnumLow = SPIELER_PUBLIKUM_UNKNOWN;
		EnumHigh = NO_OF_SPIELER_PUBLIKUM_TYPES;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << EnumType << " (" << 
			GetNameFromSpielerEnumType((SPIELER_ENUM_TYPE) EnumType) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	} // switch enum type
} // GetEnumDetails

void spieler::GetGenericCombineFieldsForField (int SpielerSectionPos, std::vector<int>& CombineFields)
{
	switch ((SPIELER_SECTION_POS_TYPE) SpielerSectionPos)
	{
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN:
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN:
		if (this->GetPositionEnum() == SPIELER_ENUM_TORWARTFAEHIGKEITEN)
		{
			CombineFields.push_back(SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_1);
			CombineFields.push_back(SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_2);
			CombineFields.push_back(SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_3);
		} // if Torwart
		else
		{
			CombineFields.push_back(SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_1);
			CombineFields.push_back(SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_2);
			CombineFields.push_back(SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_3);
		} // Spieler
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SpielerSectionPos << "-" << 
			GetNameFromSpielerSectionPosType((SPIELER_SECTION_POS_TYPE) SpielerSectionPos) << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}
} // GetGenericCombineFieldsForField

void spieler::GetGenericSplitFieldsForField (int SpielerSectionPos, std::vector<int>& SplitFields)
{
	switch ((SPIELER_SECTION_POS_TYPE) SpielerSectionPos)
	{
	case SPIELER_SECTION_POS_EIGENSCHAFTEN:
		SplitFields.push_back(SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT1);
		SplitFields.push_back(SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT2);
		break;

	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER:
		SplitFields.push_back(SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND);
		SplitFields.push_back(SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_FUSSBALLINLAENDER);
		break; 

	case SPIELER_SECTION_POS_HAAR_UND_BART:
		SplitFields.push_back(SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART);
		SplitFields.push_back(SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_HAAR);
		break;

	case SPIELER_SECTION_POS_CHARAKTER:
		SplitFields.push_back(SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER1);
		SplitFields.push_back(SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER2);
		break;

	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN:
		SplitFields.push_back(SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1);
		SplitFields.push_back(SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2);
		SplitFields.push_back(SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3);
		break;

	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN:
		SplitFields.push_back(SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1);
		SplitFields.push_back(SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2);
		SplitFields.push_back(SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3);
		break;

	// No Generic Split Fields but Bitmask
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART:
	case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT:
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SpielerSectionPos << "-" << 
			GetNameFromSpielerSectionPosType((SPIELER_SECTION_POS_TYPE) SpielerSectionPos) << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}
} // GetGenericSplitFieldsForField

bool spieler::GetBooleanTargetFieldForEnumVal (const int SpielerSplitSectionPos, const int EnumPos, int& BooleanTargetField)
{
	bool FieldFound = false;
	BooleanTargetField = SPIELER_SECTION_POS_UNKNOWN;

	switch ((SPIELER_SECTION_POS_TYPE) SpielerSplitSectionPos)
	{
	case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT:
		switch ((SPIELER_NATIONALSPIELER_UND_RUECKTRITT_TYPE) EnumPos)
		{
		case SPIELER_NATIONALSPIELER_UND_RUECKTRITT_IST_NATIONALSPIELER:
			BooleanTargetField = SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_NATIONALSPIELER;
			break;

		case SPIELER_NATIONALSPIELER_UND_RUECKTRITT_RUECKTRITT:
			BooleanTargetField = SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_RUECKTRITT;
			break;

			// Enum without Value
		case SPIELER_NATIONALSPIELER_UND_RUECKTRITT_NEIN:
			break;

		default:
			std::stringstream ErrorText;
			ErrorText << "Unexpected Spieler Nationalspieler und Ruecktritt Type " << EnumPos << " (" << 
				GetNameFromSpielerNationalspielerUndRuecktrittType((SPIELER_NATIONALSPIELER_UND_RUECKTRITT_TYPE) EnumPos) << ") -> " <<__FUNCTION__;
			programError (ErrorText.str());	
		} // switch spieler field bart type
		break;

	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART:
		switch ((SPIELER_BART_TYPE) EnumPos)
		{
		case SPIELER_BART_UNRASIERT:
			BooleanTargetField = SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_UNRASIERT;
			break;

		case SPIELER_BART_ZIEGENBART:
			BooleanTargetField = SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_ZIEGENBART;
			break;

		case SPIELER_BART_BART:
			BooleanTargetField = SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_BART;
			break;

		case SPIELER_BART_SCHNURBART:
			BooleanTargetField = SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_SCHNURBART;
			break;

		// Enum without Value
		case SPIELER_BART_KEIN:
			break;

		default:
			std::stringstream ErrorText;
			ErrorText << "Unexpected Spieler Haar Type " << EnumPos << " (" << 
				GetNameFromSpielerBartType((SPIELER_BART_TYPE) EnumPos) << ") -> " <<__FUNCTION__;
			programError (ErrorText.str());	
		} // switch spieler field bart type
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SpielerSplitSectionPos << " (" << 
			GetNameFromSpielerSectionPosType((SPIELER_SECTION_POS_TYPE) SpielerSplitSectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	} // switch spieler split section pos


	if (BooleanTargetField != SPIELER_SECTION_POS_UNKNOWN)
		FieldFound = true;

	return(FieldFound);
} // GetBooleanTargetFieldForEnumVal

static bool IncludeSectionPosIntoA3Db (SPIELER_SECTION_POS_TYPE SectionPos, SECTION_TYPE DataSection)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case SPIELER_SECTION_POS_VEREIN:
		IncludeIntoA3Db = false;
		break;

	case SPIELER_SECTION_POS_NACHNAHME: 
	case SPIELER_SECTION_POS_VORNAHME: 
	case SPIELER_SECTION_POS_UNKNOWN_3: 
	case SPIELER_SECTION_POS_HAUTFARBE: 
	case SPIELER_SECTION_POS_HAARFARBE: 
	case SPIELER_SECTION_POS_ALTER: 
	case SPIELER_SECTION_POS_STAERKE: 
	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER:
	case SPIELER_SECTION_POS_HAUPTPOSITION:
	case SPIELER_SECTION_POS_NEBEN_POSITION_1: 
	case SPIELER_SECTION_POS_NEBEN_POSITION_2: 
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN: 
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN: 
	case SPIELER_SECTION_POS_EIGENSCHAFTEN: 
	case SPIELER_SECTION_POS_CHARAKTER: 
	case SPIELER_SECTION_POS_HATKUENSTLERNAHME: 
	case SPIELER_SECTION_POS_KUENSTLERNAHME: 
	case SPIELER_SECTION_POS_FUSS: 
	case SPIELER_SECTION_POS_TALENT: 
	case SPIELER_SECTION_POS_GESUNDHEIT: 
	case SPIELER_SECTION_POS_PUBLIKUM: 
	case SPIELER_SECTION_POS_GEBURTSDATUM: 
	case SPIELER_SECTION_POS_UNKNOWN_23: 
	case SPIELER_SECTION_POS_LANDZWEI: 
	case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT: 
	case SPIELER_SECTION_POS_UNKNOWN_26: 
	case SPIELER_SECTION_POS_UNKNOWN_27: 
	case SPIELER_SECTION_POS_KAPITAENRUECKTRITT: 
	case SPIELER_SECTION_POS_RUECKENNUMMER: 
	case SPIELER_SECTION_POS_HAAR_UND_BART: 
	case SPIELER_SECTION_POS_UNKNOWN_31: 
	case SPIELER_SECTION_POS_UNKNOWN_32: 
	case SPIELER_SECTION_POS_UNKNOWN_33: 
		if(SectionIsVisible(DataSection))
			IncludeIntoA3Db = true;
		else
			IncludeIntoA3Db = false;
		break;

	case SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND:
	case SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN: 
		if(SectionIsVisible(DataSection))
			IncludeIntoA3Db = false;
		else
			IncludeIntoA3Db = true;
		break;

	case SPIELER_SECTION_POS_LANDZWEI_EXPANDED:
	case SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND_EXPANDED:
	case SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN_EXPANDED:
	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND:
	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_FUSSBALLINLAENDER:
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_HAAR: 
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART: 
	case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_NATIONALSPIELER: 
	case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_RUECKTRITT:
	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND_EXPANDED:		
	case SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT1:
	case SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT2:		
	case SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER1:
	case SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER2:		
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_UNRASIERT:
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_BART:
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_SCHNURBART: 
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_ZIEGENBART: 
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1: 
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2: 
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3: 
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1:	
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2:	
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3:	
	case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_1:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_2:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_3:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_1:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_2:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_3:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromSpielerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (SPIELER_SECTION_POS_TYPE SectionPos, const std::string& A3DbFilename)
{
	bool IncludeIntoXml = false;

	A3_FILE_GROUP_TYPE FileGroupType;
	switch (SectionPos)
	{
	case SPIELER_SECTION_POS_VEREIN:
	case SPIELER_SECTION_POS_NACHNAHME: 
	case SPIELER_SECTION_POS_VORNAHME: 
	case SPIELER_SECTION_POS_UNKNOWN_3: 
	case SPIELER_SECTION_POS_HAUTFARBE: 
	case SPIELER_SECTION_POS_HAARFARBE: 
	case SPIELER_SECTION_POS_ALTER: 
	case SPIELER_SECTION_POS_STAERKE: 
	case SPIELER_SECTION_POS_HAUPTPOSITION:
	case SPIELER_SECTION_POS_NEBEN_POSITION_1: 
	case SPIELER_SECTION_POS_NEBEN_POSITION_2: 
	case SPIELER_SECTION_POS_HATKUENSTLERNAHME: 
	case SPIELER_SECTION_POS_KUENSTLERNAHME: 
	case SPIELER_SECTION_POS_FUSS: 
	case SPIELER_SECTION_POS_TALENT: 
	case SPIELER_SECTION_POS_GESUNDHEIT: 
	case SPIELER_SECTION_POS_PUBLIKUM: 
	case SPIELER_SECTION_POS_GEBURTSDATUM: 
	case SPIELER_SECTION_POS_UNKNOWN_23: 
	case SPIELER_SECTION_POS_UNKNOWN_26: 
	case SPIELER_SECTION_POS_UNKNOWN_27:  
	case SPIELER_SECTION_POS_RUECKENNUMMER: 
	case SPIELER_SECTION_POS_UNKNOWN_31: 
	case SPIELER_SECTION_POS_UNKNOWN_32: 
	case SPIELER_SECTION_POS_UNKNOWN_33: 	
	case SPIELER_SECTION_POS_LANDZWEI_EXPANDED:
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_HAAR: 
	case SPIELER_SECTION_POS_KAPITAENRUECKTRITT:
	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_FUSSBALLINLAENDER:	
	case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_NATIONALSPIELER: 
	case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_RUECKTRITT:
	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND_EXPANDED:	
	case SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT1:
	case SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT2:	
	case SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER1:
	case SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER2:
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_UNRASIERT:
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_BART:
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_SCHNURBART: 
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_ZIEGENBART: 
	case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_1:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_2:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_3:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_1:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_2:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_3:
		IncludeIntoXml = true;
		break;

	case SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND_EXPANDED:
	case SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN_EXPANDED:
		FileGroupType = GetA3FileGroupFromFileName(A3DbFilename);
		if(FileGroupType == A3_FILE_GROUP_EXSPIEL)
			IncludeIntoXml = true;
		else
			IncludeIntoXml = false;
		break;
		
	case SPIELER_SECTION_POS_LANDZWEI: 
	case SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND:
	case SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN:
	case SPIELER_SECTION_POS_HAAR_UND_BART: 
	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_LAND:
	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER: 
	case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT: 	
	case SPIELER_SECTION_POS_EIGENSCHAFTEN: 
	case SPIELER_SECTION_POS_CHARAKTER: 
	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART: 
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN: 
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN: 
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1: 
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2: 
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3: 
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1:	
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2:	
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3:	
		IncludeIntoXml = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromSpielerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static SPIELER_SECTION_POS_TYPE GetPlayerSectionPosTypeFromString (const std::string& TypeString)
{
	SPIELER_SECTION_POS_TYPE FoundPos = SPIELER_SECTION_POS_UNKNOWN;

	for (int TempPos = SPIELER_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_SPIELER_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromSpielerSectionPosType ((SPIELER_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (SPIELER_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetPlayerSectionPosTypeFromString

static SPIELER_POSITION_POLARITY_TYPE GetSpielerPositionPolarityFromString (const std::string& StringVal)
{
	SPIELER_POSITION_POLARITY_TYPE	PositionPolarity = SPIELER_POSITION_POLARITY_UNKNOWN;

	if (isPrefix(POSITIVE_FAEHIGKEITEN_PREFIX, StringVal))
		PositionPolarity = SPIELER_POSITION_POLARITY_POSITIVE;
	else if (isPrefix(NEGATIVE_FAEHIGKEITEN_PREFIX, StringVal))
		PositionPolarity = SPIELER_POSITION_POLARITY_NEGATIVE;
	else
		PositionPolarity = SPIELER_POSITION_POLARITY_UNKNOWN;

	return (PositionPolarity);
} // GetSpielerPositionPolarityFromString

static SPIELER_POSITION_POLARITY_TYPE GetSpielerPositionPolarityFromSectionPos (SPIELER_SECTION_POS_TYPE SectionPos)
{
	SPIELER_POSITION_POLARITY_TYPE	PositionPolarity = SPIELER_POSITION_POLARITY_UNKNOWN;

	switch (SectionPos)
	{
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN:
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1: 
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2: 
	case SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3: 
		PositionPolarity = SPIELER_POSITION_POLARITY_POSITIVE;
		break;

	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN:
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_1:	
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_2:	
	case SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN_SPLIT_BITMASK_FAEHIGKEIT_3:
		PositionPolarity = SPIELER_POSITION_POLARITY_NEGATIVE;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Position Field: " << SectionPos << " (" << GetNameFromSpielerSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	} // switch section pos

	return (PositionPolarity);
} // GetSpielerPositionPolarityFromSectionPos

void AssignSpielerField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<spieler>(SectionList, SectionLineCount, Line);
} // AssignSpielerField

int GetSpielerHiddenOffset ()
{
	return (GetNoOfFieldsInA3Section(SECTION_TYPE_SPIELER));
} // GetSpielerHiddenOffset

void ConvertIllegalExSpielerReferences (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator SpielerIterator;
	std::vector<std::shared_ptr<section>> SpielerList = SectionList [SECTION_TYPE_SPIELER];

	for(SpielerIterator = SpielerList.begin(); SpielerIterator != SpielerList.end(); ++SpielerIterator)
	{
		bool NeedResetLetzterVerein = false;
		std::string LetzterVerein = std::static_pointer_cast<spieler>(*SpielerIterator)->GetValueAtSectionPos(SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN);

		// don't check for blank land as we cannot set it to 0 as not allowed by A3, if blank sav file is broken
		if (LetzterVerein.size() == 0)
		{
			NeedResetLetzterVerein = true;
		} // if verein blank
		else
		{
			if (LetzterVerein.compare(EXSPIELER_LAST_LAND_VEREIN) != 0)
			{
				std::string LetztesLand = std::static_pointer_cast<spieler>(*SpielerIterator)->GetValueAtSectionPos(SPIELER_SECTION_POS_EXSPIEL_LETZTES_LAND);

				std::string FoundVereinString;
				if (!FindVereinFromVereinList (LetzterVerein, LetztesLand, SectionList [SECTION_TYPE_VEREIN], FoundVereinString))
				{
					NeedResetLetzterVerein = true;
				} 
			} // if not blank verein
		} // if have verein

		if (NeedResetLetzterVerein)
		{
			std::static_pointer_cast<spieler>(*SpielerIterator)->AssignField(SPIELER_SECTION_POS_EXSPIEL_LETZTER_VEREIN, EXSPIELER_LAST_LAND_VEREIN);

			std::stringstream Text;
			Text << "ACHTUNG - Ehemaliger Spieler \"" << std::static_pointer_cast<spieler>(*SpielerIterator)->GetValueAtSectionPos(SPIELER_SECTION_POS_NACHNAHME) <<
				", " << std::static_pointer_cast<spieler>(*SpielerIterator)->GetValueAtSectionPos(SPIELER_SECTION_POS_VORNAHME) <<
				"\" hat illegalen letzten Verein - Setzte es zu Kein Verein";
			showTextMsg(Text.str());	

		} // if need to reset Letzter Verein
	} // for each spieler
} // ConvertIllegalExSpielerReferences

void spieler::MixFaehigkeitenForSectionPos (int SectionPos)
{
//std::cout << __FUNCTION__ << " - Mix Spieler " << this->GetUniqueId() << " at " << this->GetParentId() << std::endl;

	std::vector<int> CombineFields;
	std::vector<int> SplitFields;

	this->GetGenericSplitFieldsForField (SectionPos, SplitFields);
	this->GetGenericCombineFieldsForField (SectionPos, CombineFields);

	std::vector<int>::const_iterator SplitFieldIterator = SplitFields.begin();
	std::vector<int>::const_iterator CombinedFieldIterator;
	for (CombinedFieldIterator = CombineFields.begin(); 
			(CombinedFieldIterator != CombineFields.end()) && (SplitFieldIterator != SplitFields.end()); ++CombinedFieldIterator)
	{
//std::cout << "  CombineField::" << GetNameFromSpielerSectionPosType((SPIELER_SECTION_POS_TYPE) *CombinedFieldIterator) << " -> " 
//	<< this->GetValueAtSectionPos(*CombinedFieldIterator) << std::endl;
		if (this->GetValueAtSectionPos(*CombinedFieldIterator).compare(SPIELER_NO_FAEHIGKEIT_STRING) == 0)
		{
//std::cout << "  SplitField::" << GetNameFromSpielerSectionPosType((SPIELER_SECTION_POS_TYPE) *SplitFieldIterator) << " -> " 
//	<< this->GetValueAtSectionPos(*SplitFieldIterator) << std::endl;
			std::string SplitFieldVal = this->GetValueAtSectionPos(*SplitFieldIterator);
			if (SplitFieldVal.compare(SPIELER_NO_FAEHIGKEIT_STRING) != 0)
			{
				this->AssignField(*CombinedFieldIterator, SplitFieldVal);
				++SplitFieldIterator;
			} // if faehigkeit is set
		} // if no faehigkeit set
	} // for each combined field
} // MixFaehigkeitenForSectionPos

void spieler::MixFaehigkeiten()
{
	// Trying to Combine Positive Faehigkeiten
	this->MixFaehigkeitenForSectionPos (SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN);

	// Trying to Combine Negative Faehigkeiten
	this->MixFaehigkeitenForSectionPos (SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN);

} // MixFaehigkeiten

void spieler::UnMixFaehigkeitenForSectionPos (int SectionPos)
{
//std::cout << __FUNCTION__ << " - Unmix Spieler " << this->GetUniqueId() << " at " << this->GetParentId() << std::endl;

	std::vector<int> CombineFields;
	std::vector<int> SplitFields;
	
	this->GetGenericSplitFieldsForField (SectionPos, SplitFields);
	this->GetGenericCombineFieldsForField (SectionPos, CombineFields);

	std::vector<int>::const_iterator SplitFieldIterator = SplitFields.begin();
	std::vector<int>::const_iterator CombinedFieldIterator;
	for (CombinedFieldIterator = CombineFields.begin(); 
			(CombinedFieldIterator != CombineFields.end()) && (SplitFieldIterator != SplitFields.end()); ++CombinedFieldIterator)
	{
//std::cout << "  Check Combine Field: " << GetNameFromSpielerSectionPosType((SPIELER_SECTION_POS_TYPE) *CombinedFieldIterator) << " with " <<
//	this->GetValueAtSectionPos(*CombinedFieldIterator) << std::endl;
//std::cout << "  CombinePolarity::StringPolarity -> " << GetSpielerPositionPolarityFromString (this->GetValueAtSectionPos(*CombinedFieldIterator)) <<
//	"::" << GetSpielerPositionPolarityFromSectionPos ((SPIELER_SECTION_POS_TYPE) SectionPos) << std::endl;
		if (GetSpielerPositionPolarityFromString (this->GetValueAtSectionPos(*CombinedFieldIterator)) ==
				GetSpielerPositionPolarityFromSectionPos ((SPIELER_SECTION_POS_TYPE) SectionPos))
		{

//std::cout << "    Setting Split Field " << GetNameFromSpielerSectionPosType((SPIELER_SECTION_POS_TYPE) *SplitFieldIterator) << " to \"" <<
//	this->GetValueAtSectionPos(*CombinedFieldIterator) << "\"" << std::endl;
			this->AssignField(*SplitFieldIterator, this->GetValueAtSectionPos(*CombinedFieldIterator));
			++SplitFieldIterator;

		} // if combine field same polarity as section pos
	} // for each combine field
} // UnMixFaehigkeitenForSectionPos

void spieler::UnMixFaehigkeiten()
{
	// Trying to Separate Positive Faehigkeiten
	this->UnMixFaehigkeitenForSectionPos (SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN);

	// Trying to Separate Negative Faehigkeiten
	this->UnMixFaehigkeitenForSectionPos (SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN);
} // UnMixFaehigkeiten

void MixSpielerFaehigkeiten(std::vector<std::shared_ptr<section>> PlayerList)
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	for (SectionIterator = PlayerList.begin(); SectionIterator != PlayerList.end(); ++SectionIterator)
	{
		std::static_pointer_cast<spieler>(*SectionIterator)->MixFaehigkeiten();
	} // for each player
} // MixSpielerFaehigkeiten

void UnMixSpielerFaehigkeiten(std::vector<std::shared_ptr<section>> PlayerList)
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	for (SectionIterator = PlayerList.begin(); SectionIterator != PlayerList.end(); ++SectionIterator)
	{
		std::static_pointer_cast<spieler>(*SectionIterator)->UnMixFaehigkeiten();
	} // for each player
} // UnMixSpielerFaehigkeiten

static SPIELER_ENUM_TYPE GetSpielerEnumTypeFromPosition (SPIELER_SECTION_POS_TYPE SectionPos)
{
	SPIELER_ENUM_TYPE EnumType = SPIELER_ENUM_UNKNOWN;
	switch ((SPIELER_SECTION_POS_TYPE) SectionPos)
	{
	case SPIELER_SECTION_POS_HAUTFARBE:
		EnumType = SPIELER_ENUM_HAUTFARBE;
		break;

	case SPIELER_SECTION_POS_HAARFARBE:
		EnumType = SPIELER_ENUM_HAARFARBE;
		break;

	case SPIELER_SECTION_POS_HAUPTPOSITION:
	case SPIELER_SECTION_POS_NEBEN_POSITION_1:
	case SPIELER_SECTION_POS_NEBEN_POSITION_2:
		EnumType = SPIELER_ENUM_POSITION;
		break;

	case SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT1:
	case SPIELER_SECTION_POS_EIGENSCHAFTEN_SPLIT_BITMASK_EIGENSCHAFT2:
		EnumType = SPIELER_ENUM_EIGENSCHAFTEN;
		break;

	case SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER1:
	case SPIELER_SECTION_POS_CHARAKTER_SPLIT_BITMASK_CHARAKTER2:
		EnumType = SPIELER_ENUM_CHARAKTER;
		break;

	case SPIELER_SECTION_POS_FUSS:
		EnumType = SPIELER_ENUM_FUSS;
		break;

	case SPIELER_SECTION_POS_TALENT:
		EnumType = SPIELER_ENUM_TALENT;
		break;

	case SPIELER_SECTION_POS_GESUNDHEIT:
		EnumType = SPIELER_ENUM_GESUNDHEIT;
		break;

	case SPIELER_SECTION_POS_PUBLIKUM:
		EnumType = SPIELER_ENUM_PUBLIKUM;
		break;

	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_HAAR:
		EnumType = SPIELER_ENUM_HAAR;
		break;

	case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_1:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_2:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_SPIELER_FAEHIGKEIT_3:
		EnumType = SPIELER_ENUM_SPIELERFAEHIGKEITEN;
		break;

	case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_1:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_2:
	case SPIELER_SECTION_POS_FAEHIGKEITEN_TORWART_FAEHIGKEIT_3:
		EnumType = SPIELER_ENUM_TORWARTFAEHIGKEITEN;
		break;

	default:
		//do nothing
		break;
	} // switch section pos

	return (EnumType);
} // GetSpielerEnumTypeFromPosition

SPIELER_BOOLEAN_TYPE GetSpielerBooleanTypeFromPosition (SPIELER_SECTION_POS_TYPE SectionPos)
{
	SPIELER_BOOLEAN_TYPE BooleanType = SPIELER_BOOLEAN_UNKNOWN;
	switch (SectionPos)
	{
	case SPIELER_SECTION_POS_HATKUENSTLERNAHME:
		BooleanType = SPIELER_BOOLEAN_HAT_KUENSTLERNAHME;
		break;

	case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_NATIONALSPIELER:
		BooleanType = SPIELER_BOOLEAN_IST_NATIONALSPIELER;
		break;

	case SPIELER_SECTION_POS_NATIONALSPIELER_UND_RUECKTRITT_SPLIT_BITMASK_RUECKTRITT:
		BooleanType = SPIELER_BOOLEAN_NATIONALSPIELER_RUECKTRITT;
		break;

	case SPIELER_SECTION_POS_KAPITAENRUECKTRITT:
		BooleanType = SPIELER_BOOLEAN_KAPITAEN_RUECKTRITT;
		break;

	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_UNRASIERT:
		BooleanType = SPIELER_BOOLEAN_BART_UNRASIERT;
		break;

	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_BART:
		BooleanType = SPIELER_BOOLEAN_BART_BART;
		break;

	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_SCHNURBART:
		BooleanType = SPIELER_BOOLEAN_BART_SCHNURBART;
		break;

	case SPIELER_SECTION_POS_HAAR_UND_BART_SPLIT_BART_SPLIT_BITMASK_ZIEGENBART:
		BooleanType = SPIELER_BOOLEAN_BART_ZIEGENBART;
		break;
		
	case SPIELER_SECTION_POS_LAND_UND_FUSSBALLINLAENDER_SPLIT_FUSSBALLINLAENDER:
		BooleanType = SPIELER_BOOLEAN_FUSSBALLINLAENDER;
		break;

	default:
		//do nothing
		break;
	} // switch section pos

	return (BooleanType);
} // GetSpielerBooleanTypeFromPosition

void GetSpielerAllowedValues (std::vector<FIELD_VALUE_STRUCT>& AllowedValues)
{
	for (int SectionPos = SPIELER_SECTION_POS_UNKNOWN + 1; SectionPos < NO_OF_SPIELER_SECTION_POS_TYPES; SectionPos++)
	{
		ENUM_FUNC EnumFunc = nullptr;
		int EnumLow = 0;
		int EnumHigh = 0;
		SPIELER_ENUM_TYPE SpielerEnum = SPIELER_ENUM_UNKNOWN;
		SPIELER_BOOLEAN_TYPE SpielerBoolean = SPIELER_BOOLEAN_UNKNOWN;
		bool DetailsFound = false;

		if ((SpielerEnum = GetSpielerEnumTypeFromPosition ((SPIELER_SECTION_POS_TYPE) SectionPos)) != SPIELER_ENUM_UNKNOWN)
		{
			// Ignore this for special case handled below
			if ((SpielerEnum != SPIELER_ENUM_TORWARTFAEHIGKEITEN) && (SpielerEnum != SPIELER_ENUM_SPIELERFAEHIGKEITEN))
				GetEnumDetails(SectionPos, SpielerEnum, EnumFunc, EnumLow, EnumHigh);
			DetailsFound = true;
		} // if enum field
		else if ((SpielerBoolean = GetSpielerBooleanTypeFromPosition ((SPIELER_SECTION_POS_TYPE) SectionPos)) != SPIELER_BOOLEAN_UNKNOWN)
		{
			GetBooleanEnumDetails (EnumFunc, EnumLow, EnumHigh);
			DetailsFound = true;
		} // if boolean field

		// Add Values
		if (DetailsFound)
		{
			// Add the Value Entry to the List
			AddFieldValueEntryToList (AllowedValues, GetNameFromSpielerSectionPosType((SPIELER_SECTION_POS_TYPE) SectionPos));

			// Add allowed Values
			if ((SpielerEnum == SPIELER_ENUM_TORWARTFAEHIGKEITEN) || (SpielerEnum == SPIELER_ENUM_SPIELERFAEHIGKEITEN))
			{
				GetEnumDetails(SPIELER_SECTION_POS_POSITIVE_FAEHIGKEITEN, SpielerEnum, EnumFunc, EnumLow, EnumHigh);
				AddFieldValuesForLastEntry (AllowedValues, EnumLow, EnumHigh, EnumFunc);

				GetEnumDetails(SPIELER_SECTION_POS_NEGATIVE_FAEHIGKEITEN, SpielerEnum, EnumFunc, EnumLow, EnumHigh);
				AddFieldValuesForLastEntry (AllowedValues, EnumLow+1, EnumHigh, EnumFunc); // ignore Keine (HACK)
			} // Special Case Faehigkeiten
			else
			{
				AddFieldValuesForLastEntry (AllowedValues, EnumLow, EnumHigh, EnumFunc);
			}

		} // if got a function
	} // for each section pos
} // GetSpielerAllowedValues
