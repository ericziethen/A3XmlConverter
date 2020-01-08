#include "verein.h"

#include "error_handling.h"
#include "misc_lib.h"
#include <sstream>
#include <iostream>

#define A3DB_NO_VEREIN_STRING "0"
#define A3DB_NO_VEREIN_EXPANDED_STRING ""

#define VEREIN_LAND_INDEX_NOT_SET "0"

verein::verein(void)
{
	this->AssignField(VEREIN_SECTION_POS_VEREIN_LAND_INDEX, VEREIN_LAND_INDEX_NOT_SET);
}

verein::~verein(void)
{
}

std::string verein::GetUniqueId ()
{
	return(this->Vereinsnahme);
} // GetUniqueId

SECTION_TYPE verein::GetSectionType ()
{
	return(SECTION_TYPE_VEREIN);
} // GetSectionType

std::string verein::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case VEREIN_SECTION_POS_LAND:
		return (this->GetParentId());
	case VEREIN_SECTION_POS_VEREINSNAHME:
		return (this->Vereinsnahme);
	case VEREIN_SECTION_POS_KUERZL:
		return (this->Kuerzl);
	case VEREIN_SECTION_POS_ANFEUERUNG:
		return (this->Anfeuerung);
	case VEREIN_SECTION_POS_FANBEZEICHNUNG:
		return (this->Fanbezeichnung);
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER:
		return (this->Heimtrikot_Farbe1_UndMuster);
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE2:
		return (this->Heimtrikot_Farbe2);
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_HOSENFARBE:
		return (this->Heimtrikot_HosenFarbe);
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN:
		return (this->Heimtrikot_StutzenFarbe_UndRingelsocken);
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER:
		return (this->Auswaertztrikot_Farbe1_UndMuster);
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE2:
		return (this->Auswaertztrikot_Farbe2);
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_HOSENFARBE:
		return (this->Auswaertztrikot_HosenFarbe);
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN:
		return (this->Auswaertztrikot_StutzenFarbe_UndRingelsocken);
	case VEREIN_SECTION_POS_HIDDEN_GUTHABEN_BEI_SPIELBEGINN:
		return (this->GuthabenBeiSpielbeginn);
	case VEREIN_SECTION_POS_HIDDEN_KUERZEL_ARTIKEL:
		return (this->KuerzelArtikel);
	case VEREIN_SECTION_POS_HIDDEN_FANAUFKOMMEN:
		return (this->Fanaufkommen);
	case VEREIN_SECTION_POS_HIDDEN_ART_DER_FANS:
		return (this->ArtDerFans);
	case VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT:
		return (this->FanfreundschaftMit);
	case VEREIN_SECTION_POS_HIDDEN_ERZRIVALE:
		return (this->Erzrivale);
	case VEREIN_SECTION_POS_HIDDEN_VORSTAND:
		return (this->Vorstand);
	case VEREIN_SECTION_POS_HIDDEN_POKALMANNSCHAFT:
		return (this->Pokalmannschaft);
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_17:
		return (this->VEREIN_FIELD_HIDDEN_UNKNOWN_17);
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_18:
		return (this->VEREIN_FIELD_HIDDEN_UNKNOWN_18);
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_19:
		return (this->VEREIN_FIELD_HIDDEN_UNKNOWN_19);
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_20:
		return (this->VEREIN_FIELD_HIDDEN_UNKNOWN_20);
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_21:
		return (this->VEREIN_FIELD_HIDDEN_UNKNOWN_21);
	case VEREIN_SECTION_POS_HIDDEN_OPPOSITION:
		return (this->Opposition);
	case VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON:
		return (this->AmateurabteilungVon);
	case VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON:
		return (this->ProfiabteilungVon);
	case VEREIN_SECTION_POS_HIDDEN_FINANZKRAFT:
		return (this->Finanzkraft);
	case VEREIN_SECTION_POS_HIDDEN_MAX_FANAUFKOMMEN:
		return (this->MaxFanaufkommen);
	case VEREIN_SECTION_POS_HIDDEN_HOOLIGANS:
		return (this->Hooligans);
	case VEREIN_SECTION_POS_HIDDEN_MEDIENSTADT:
		return (this->Medienstadt);
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_ERZIELTE_TORE:
		return (this->EwigeTabelle_ErzielteTore);
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_KASSIERTE_TORE:
		return (this->EwigeTabelle_KassierteTore);
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_SPIELE:
		return (this->EwigeTabelle_Spiele);
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_PUNKTE:
		return (this->EwigeTabelle_Punkte);
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_NACHNAHME:
		return (this->Vorsitzender_Nachnahme);
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_VORNAHME:
		return (this->Vorsitzender_Vornahme);
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_GEBURTSDATUM:
		return (this->Vorsitzender_Geburtdatum);
	case VEREIN_SECTION_POS_HIDDEN_AKTIENGESELLSCHAFT:
		return (this->Aktiengesellschaft);
	case VEREIN_SECTION_POS_HIDDEN_TITEL_MEISTERSCHAFTEN:
		return (this->Titel_Meisterschaften);
	case VEREIN_SECTION_POS_HIDDEN_TITEL_POKALE:
		return (this->Titel_Pokale);
	case VEREIN_SECTION_POS_HIDDEN_TITEL_LIGAPOKALE:
		return (this->Titel_Ligapokale);
	case VEREIN_SECTION_POS_HIDDEN_TITEL_EUROPA_LEAGUES:
		return (this->Titel_EuropaLeagues);
	case VEREIN_SECTION_POS_HIDDEN_TITEL_CHAMPIONS_LEAGUES:
		return (this->Titel_ChampionsLeagues);
	case VEREIN_SECTION_POS_HIDDEN_TITEL_WELTPOKALE:
		return (this->Titel_Weltpokale);
	case VEREIN_SECTION_POS_HIDDEN_REGIONALLIGA_AB_2000:
		return (this->RegionalligaAb2000);
	case VEREIN_SECTION_POS_HIDDEN_GRUENDUNGSJAHR:
		return (this->Gruendungsjahr);
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_45:
		return (this->VEREIN_FIELD_HIDDEN_UNKNOWN_45);
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_46:
		return (this->VEREIN_FIELD_HIDDEN_UNKNOWN_46);
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_47:
		return (this->VEREIN_FIELD_HIDDEN_UNKNOWN_47);
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_48:
		return (this->VEREIN_FIELD_HIDDEN_UNKNOWN_48);
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_49:
		return (this->VEREIN_FIELD_HIDDEN_UNKNOWN_49);
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_50:
		return (this->VEREIN_FIELD_HIDDEN_UNKNOWN_50);
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_51:
		return (this->VEREIN_FIELD_HIDDEN_UNKNOWN_51);

	case VEREIN_SECTION_POS_LAND_EXPANDED:
		return (this->Land_Expanded);
	case VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT_EXPANDED:
		return (this->FanfreundschaftMit_Expanded);
	case VEREIN_SECTION_POS_HIDDEN_ERZRIVALE_EXPANDED:
		return (this->Erzrivale_Expanded);
	case VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON_EXPANDED:
		return (this->AmateurabteilungVon_Expanded);
	case VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON_EXPANDED:
		return (this->ProfiabteilungVon_Expanded);

	case VEREIN_SECTION_POS_VEREIN_LAND_INDEX:
		return (this->VereinLandIndex);

	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1:
		return(this->Heimtrikot_Farbe1_UndMuster_Split_Farbe1);
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER:
		return(this->Heimtrikot_Farbe1_UndMuster_Split_Muster);
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE:
		return(this->Heimtrikot_StutzenFarbe_UndRingelsocken_Split_StutzenFarbe);
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN:
		return(this->Heimtrikot_StutzenFarbe_UndRingelsocken_Split_Ringelsocken);
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1:
		return(this->Auswaertztrikot_Farbe1_UndMuster_Split_Farbe1);
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER:
		return(this->Auswaertztrikot_Farbe1_UndMuster_Split_Muster);
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE:
		return(this->Auswaertztrikot_StutzenFarbe_UndRingelsocken_Split_StutzenFarbe);
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN:
		return(this->Auswaertztrikot_StutzenFarbe_UndRingelsocken_Split_Ringelsocken);

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromVereinSectionPosType (const VEREIN_SECTION_POS_TYPE VereinSectionPosType)
{
	switch (VereinSectionPosType)
	{
	case VEREIN_SECTION_POS_LAND:
		return ("Land_UNEXPANDED");
	case VEREIN_SECTION_POS_VEREINSNAHME:
		return ("Vereinsnahme");
	case VEREIN_SECTION_POS_KUERZL:
		return ("Kuerzl");
	case VEREIN_SECTION_POS_ANFEUERUNG:
		return ("Anfeuerung");
	case VEREIN_SECTION_POS_FANBEZEICHNUNG:
		return ("Fanbezeichnung");

	// Hidden Section
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER:
		return ("Heimtrikot_Farbe1_UndMuster_UNSPLIT");
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE2:
		return ("Heimtrikot_Farbe2");
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_HOSENFARBE:
		return ("Heimtrikot_HosenFarbe");
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN:
		return ("Heimtrikot_StutzenFarbe_UndRingelsocken_UNSPLIT");
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER:
		return ("Auswaertztrikot_Farbe1_UndMuster_UNSPLIT");
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE2:
		return ("Auswaertztrikot_Farbe2");
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_HOSENFARBE:
		return ("Auswaertztrikot_HosenFarbe");
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN:
		return ("Auswaertztrikot_StutzenFarbe_UndRingelsocken_UNSPLIT");
	case VEREIN_SECTION_POS_HIDDEN_GUTHABEN_BEI_SPIELBEGINN:
		return ("GuthabenBeiSpielbeginn");
	case VEREIN_SECTION_POS_HIDDEN_KUERZEL_ARTIKEL:
		return ("KuerzelArtikel");
	case VEREIN_SECTION_POS_HIDDEN_FANAUFKOMMEN:
		return ("Fanaufkommen");
	case VEREIN_SECTION_POS_HIDDEN_ART_DER_FANS:
		return ("ArtDerFans");
	case VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT:
		return ("FanfreundschaftMit_UNEXPANDED");
	case VEREIN_SECTION_POS_HIDDEN_ERZRIVALE:
		return ("Erzrivale_UNEXPANDED");
	case VEREIN_SECTION_POS_HIDDEN_VORSTAND:
		return ("Vorstand");
	case VEREIN_SECTION_POS_HIDDEN_POKALMANNSCHAFT:
		return ("Pokalmannschaft");
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_17:
		return ("VEREIN_FIELD_HIDDEN_UNKNOWN_17");
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_18:
		return ("VEREIN_FIELD_HIDDEN_UNKNOWN_18");
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_19:
		return ("VEREIN_FIELD_HIDDEN_UNKNOWN_19");
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_20:
		return ("VEREIN_FIELD_HIDDEN_UNKNOWN_20");
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_21:
		return ("VEREIN_FIELD_HIDDEN_UNKNOWN_21");
	case VEREIN_SECTION_POS_HIDDEN_OPPOSITION:
		return ("Opposition");
	case VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON:
		return ("AmateurabteilungVon_UNEXPANDED");
	case VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON:
		return ("ProfiabteilungVon_UNEXPANDED");
	case VEREIN_SECTION_POS_HIDDEN_FINANZKRAFT:
		return ("Finanzkraft");
	case VEREIN_SECTION_POS_HIDDEN_MAX_FANAUFKOMMEN:
		return ("MaxFanaufkommen");
	case VEREIN_SECTION_POS_HIDDEN_HOOLIGANS:
		return ("Hooligans");
	case VEREIN_SECTION_POS_HIDDEN_MEDIENSTADT:
		return ("Medienstadt");
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_ERZIELTE_TORE:
		return ("EwigeTabelle_ErzielteTore");
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_KASSIERTE_TORE:
		return ("EwigeTabelle_KassierteTore");
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_SPIELE:
		return ("EwigeTabelle_Spiele");
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_PUNKTE:
		return ("EwigeTabelle_Punkte");
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_NACHNAHME:
		return ("Vorsitzender_Nachnahme");
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_VORNAHME:
		return ("Vorsitzender_Vornahme");
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_GEBURTSDATUM:
		return ("Vorsitzender_Geburtdatum");
	case VEREIN_SECTION_POS_HIDDEN_AKTIENGESELLSCHAFT:
		return ("Aktiengesellschaft");
	case VEREIN_SECTION_POS_HIDDEN_TITEL_MEISTERSCHAFTEN:
		return ("Titel_Meisterschaften");
	case VEREIN_SECTION_POS_HIDDEN_TITEL_POKALE:
		return ("Titel_Pokale");
	case VEREIN_SECTION_POS_HIDDEN_TITEL_LIGAPOKALE:
		return ("Titel_Ligapokale");
	case VEREIN_SECTION_POS_HIDDEN_TITEL_EUROPA_LEAGUES:
		return ("Titel_EuropaLeagues");
	case VEREIN_SECTION_POS_HIDDEN_TITEL_CHAMPIONS_LEAGUES:
		return ("Titel_ChampionsLeagues");
	case VEREIN_SECTION_POS_HIDDEN_TITEL_WELTPOKALE:
		return ("Titel_Weltpokale");
	case VEREIN_SECTION_POS_HIDDEN_REGIONALLIGA_AB_2000:
		return ("RegionalligaAb2000");
	case VEREIN_SECTION_POS_HIDDEN_GRUENDUNGSJAHR:
		return ("Gruendungsjahr");
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_45:
		return ("VEREIN_FIELD_HIDDEN_UNKNOWN_45");
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_46:
		return ("VEREIN_FIELD_HIDDEN_UNKNOWN_46");
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_47:
		return ("VEREIN_FIELD_HIDDEN_UNKNOWN_47");
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_48:
		return ("VEREIN_FIELD_HIDDEN_UNKNOWN_48");
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_49:
		return ("VEREIN_FIELD_HIDDEN_UNKNOWN_49");
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_50:
		return ("VEREIN_FIELD_HIDDEN_UNKNOWN_50");
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_51:
		return ("VEREIN_FIELD_HIDDEN_UNKNOWN_51");

	case VEREIN_SECTION_POS_LAND_EXPANDED:
		return ("Land");
	case VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT_EXPANDED:
		return ("FanfreundschaftMit");
	case VEREIN_SECTION_POS_HIDDEN_ERZRIVALE_EXPANDED:
		return ("Erzrivale");
	case VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON_EXPANDED:
		return ("AmateurabteilungVon");
	case VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON_EXPANDED:
		return ("ProfiabteilungVon");

	case VEREIN_SECTION_POS_VEREIN_LAND_INDEX:
		return ("VereinLandIndex");

	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1:
		return ("Heimtrikot_Farbe1");
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER:
		return ("Heimtrikot_Muster");
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE:
		return ("Heimtrikot_StutzenFarbe");
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN:
		return ("Heimtrikot_Ringelsocke");
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1:
		return ("Auswaertztrikot_Farbe1");
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER:
		return ("Auswaertztrikot_Muster");
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE:
		return ("Auswaertztrikot_StutzenFarbe");
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN:
		return ("Auswaertztrikot_Ringelsocken");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << VereinSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromVereinSectionPosType

void verein::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case VEREIN_SECTION_POS_LAND:
		this->SetParentId(FieldValue);
		break;
	case VEREIN_SECTION_POS_VEREINSNAHME:
		this->Vereinsnahme = FieldValue;
		break;
	case VEREIN_SECTION_POS_KUERZL:
		this->Kuerzl = FieldValue;
		break;
	case VEREIN_SECTION_POS_ANFEUERUNG:
		this->Anfeuerung = FieldValue;
		break;
	case VEREIN_SECTION_POS_FANBEZEICHNUNG:
		this->Fanbezeichnung = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER:
		this->Heimtrikot_Farbe1_UndMuster = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE2:
		this->Heimtrikot_Farbe2 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_HOSENFARBE:
		this->Heimtrikot_HosenFarbe = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN:
		this->Heimtrikot_StutzenFarbe_UndRingelsocken = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER:
		this->Auswaertztrikot_Farbe1_UndMuster = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE2:
		this->Auswaertztrikot_Farbe2 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_HOSENFARBE:
		this->Auswaertztrikot_HosenFarbe = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN:
		this->Auswaertztrikot_StutzenFarbe_UndRingelsocken = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_GUTHABEN_BEI_SPIELBEGINN:
		this->GuthabenBeiSpielbeginn = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_KUERZEL_ARTIKEL:
		this->KuerzelArtikel = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_FANAUFKOMMEN:
		this->Fanaufkommen = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_ART_DER_FANS:
		this->ArtDerFans = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT:
		this->FanfreundschaftMit = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_ERZRIVALE:
		this->Erzrivale = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_VORSTAND:
		this->Vorstand = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_POKALMANNSCHAFT:
		this->Pokalmannschaft = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_17:
		this->VEREIN_FIELD_HIDDEN_UNKNOWN_17 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_18:
		this->VEREIN_FIELD_HIDDEN_UNKNOWN_18 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_19:
		this->VEREIN_FIELD_HIDDEN_UNKNOWN_19 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_20:
		this->VEREIN_FIELD_HIDDEN_UNKNOWN_20 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_21:
		this->VEREIN_FIELD_HIDDEN_UNKNOWN_21 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_OPPOSITION:
		this->Opposition = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON:
		this->AmateurabteilungVon = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON:
		this->ProfiabteilungVon = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_FINANZKRAFT:
		this->Finanzkraft = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_MAX_FANAUFKOMMEN:
		this->MaxFanaufkommen = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_HOOLIGANS:
		this->Hooligans = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_MEDIENSTADT:
		this->Medienstadt = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_ERZIELTE_TORE:
		this->EwigeTabelle_ErzielteTore = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_KASSIERTE_TORE:
		this->EwigeTabelle_KassierteTore = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_SPIELE:
		this->EwigeTabelle_Spiele = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_PUNKTE:
		this->EwigeTabelle_Punkte = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_NACHNAHME:
		this->Vorsitzender_Nachnahme = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_VORNAHME:
		this->Vorsitzender_Vornahme = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_GEBURTSDATUM:
		this->Vorsitzender_Geburtdatum = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_AKTIENGESELLSCHAFT:
		this->Aktiengesellschaft = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_TITEL_MEISTERSCHAFTEN:
		this->Titel_Meisterschaften = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_TITEL_POKALE:
		this->Titel_Pokale = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_TITEL_LIGAPOKALE:
		this->Titel_Ligapokale = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_TITEL_EUROPA_LEAGUES:
		this->Titel_EuropaLeagues = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_TITEL_CHAMPIONS_LEAGUES:
		this->Titel_ChampionsLeagues = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_TITEL_WELTPOKALE:
		this->Titel_Weltpokale = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_REGIONALLIGA_AB_2000:
		this->RegionalligaAb2000 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_GRUENDUNGSJAHR:
		this->Gruendungsjahr = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_45:
		this->VEREIN_FIELD_HIDDEN_UNKNOWN_45 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_46:
		this->VEREIN_FIELD_HIDDEN_UNKNOWN_46 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_47:
		this->VEREIN_FIELD_HIDDEN_UNKNOWN_47 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_48:
		this->VEREIN_FIELD_HIDDEN_UNKNOWN_48 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_49:
		this->VEREIN_FIELD_HIDDEN_UNKNOWN_49 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_50:
		this->VEREIN_FIELD_HIDDEN_UNKNOWN_50 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_51:
		this->VEREIN_FIELD_HIDDEN_UNKNOWN_51 = FieldValue;
		break;

	case VEREIN_SECTION_POS_LAND_EXPANDED:
		this->Land_Expanded = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT_EXPANDED:
		this->FanfreundschaftMit_Expanded = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_ERZRIVALE_EXPANDED:
		this->Erzrivale_Expanded = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON_EXPANDED:
		this->AmateurabteilungVon_Expanded = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON_EXPANDED:
		this->ProfiabteilungVon_Expanded = FieldValue;
		break;

	case VEREIN_SECTION_POS_VEREIN_LAND_INDEX:
		this->VereinLandIndex = FieldValue;
		break;

	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1:
		this->Heimtrikot_Farbe1_UndMuster_Split_Farbe1 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER:
		this->Heimtrikot_Farbe1_UndMuster_Split_Muster = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE:
		this->Heimtrikot_StutzenFarbe_UndRingelsocken_Split_StutzenFarbe = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN:
		this->Heimtrikot_StutzenFarbe_UndRingelsocken_Split_Ringelsocken = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1:
		this->Auswaertztrikot_Farbe1_UndMuster_Split_Farbe1 = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER:
		this->Auswaertztrikot_Farbe1_UndMuster_Split_Muster = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE:
		this->Auswaertztrikot_StutzenFarbe_UndRingelsocken_Split_StutzenFarbe = FieldValue;
		break;
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN:
		this->Auswaertztrikot_StutzenFarbe_UndRingelsocken_Split_Ringelsocken = FieldValue;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void verein::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int VereinPos = VEREIN_SECTION_POS_UNKNOWN + 1; VereinPos < NO_OF_VEREIN_SECTION_POS_TYPES; VereinPos++)
	{
		if (IncludeSectionPosIntoXml ((VEREIN_SECTION_POS_TYPE) VereinPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromVereinSectionPosType ((VEREIN_SECTION_POS_TYPE) VereinPos), 			
				this->GetValueAtSectionPos(VereinPos))));
		}
	}
} // PopulateValuePairVectorForExport

void verein::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& VereinValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = VereinValuePairs.begin(); 
		Iterator != VereinValuePairs.end(); ++Iterator)
	{
		VEREIN_SECTION_POS_TYPE FieldPos = GetVereinSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != VEREIN_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void verein::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = VEREIN_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_VEREIN_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((VEREIN_SECTION_POS_TYPE) TempPos, DataSection))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void verein::DecodeFieldsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Land Fields
	this->ConvertLandField(SECTION_EXPANSION_FROM_A3DB_LAND, VEREIN_SECTION_POS_LAND, VEREIN_SECTION_POS_LAND_EXPANDED, SectionList);

	// Decode Verein Fields
	this->ConvertVereinField(SECTION_EXPANSION_FROM_A3DB_VEREIN, VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT, VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT_EXPANDED, 
								this->GetA3FileLandId(), SectionList);
	this->ConvertVereinField(SECTION_EXPANSION_FROM_A3DB_VEREIN, VEREIN_SECTION_POS_HIDDEN_ERZRIVALE, VEREIN_SECTION_POS_HIDDEN_ERZRIVALE_EXPANDED, 
								this->GetA3FileLandId(), SectionList);
	this->ConvertVereinField(SECTION_EXPANSION_FROM_A3DB_VEREIN, VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON, VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON_EXPANDED, 
								this->GetA3FileLandId(), SectionList);
	this->ConvertVereinField(SECTION_EXPANSION_FROM_A3DB_VEREIN, VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON, VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON_EXPANDED, 
								this->GetA3FileLandId(), SectionList);
} // DecodeFieldsFromA3Db

void verein::EncodeFieldsToA3Db (FIELD_REFERENCE_TYPE ReferenceType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	switch (ReferenceType)
	{
	case FIELD_REFERENCE_LAND:
		this->ConvertLandField(SECTION_EXPANSION_TO_A3DB_LAND, VEREIN_SECTION_POS_LAND_EXPANDED, VEREIN_SECTION_POS_LAND, SectionList);
		break;

	case FIELD_REFERENCE_VEREIN:
		this->ConvertVereinField(SECTION_EXPANSION_TO_A3DB_VEREIN, VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT_EXPANDED, VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT, 
			this->GetA3FileLandId(), SectionList);
		this->ConvertVereinField(SECTION_EXPANSION_TO_A3DB_VEREIN, VEREIN_SECTION_POS_HIDDEN_ERZRIVALE_EXPANDED, VEREIN_SECTION_POS_HIDDEN_ERZRIVALE, 
			this->GetA3FileLandId(), SectionList);
		this->ConvertVereinField(SECTION_EXPANSION_TO_A3DB_VEREIN, VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON_EXPANDED, VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON, 
			this->GetA3FileLandId(), SectionList);
		this->ConvertVereinField(SECTION_EXPANSION_TO_A3DB_VEREIN, VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON_EXPANDED, VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON, 
			this->GetA3FileLandId(), SectionList);
		break;

	default:
		break;
	} // switch reference types
} // EncodeFieldsToA3Db 

void verein::PostSavSplitCombinedFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	ENUM_VALUE_LIST ValueList;

	// Split Heim Farbe 1 und Muster
	ValueList.clear();
	this->SplitJoinedField (this->GetValueAtSectionPos(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER),
		GetVereinEnumValueList(VEREIN_ENUM_TRIKOT_MUSTER, ValueList), 
		VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER, VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1);

	// Split Heim Ringelsocken und Stutzten
	ValueList.clear();
	this->SplitJoinedField (this->GetValueAtSectionPos(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN), 
		GetVereinEnumValueList(VEREIN_ENUM_TRIKOT_RINGELSOCKEN, ValueList), 
		VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN, VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE);

	// Split Auswaertz Farbe 1 und Muster
	ValueList.clear();
	this->SplitJoinedField (this->GetValueAtSectionPos(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER), 
		GetVereinEnumValueList(VEREIN_ENUM_TRIKOT_MUSTER, ValueList), 
		VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER, VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1);

	// Split Auswaertz Ringelsocken und Stutzten
	ValueList.clear();
	this->SplitJoinedField (this->GetValueAtSectionPos(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN), 
		GetVereinEnumValueList(VEREIN_ENUM_TRIKOT_RINGELSOCKEN, ValueList), 
		VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN, VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE);

} // PostSavSplitCombinedFields

void verein::PostExternalMergeSplitFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Merge Heim Farbe 1 und Muster
	this->MergeSplitField (VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER);

	// Merge Heim Ringelsocken und Stutzten
	this->MergeSplitField (VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN);

	// Merge Auswaertz Farbe 1 und Muster
	this->MergeSplitField (VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER);

	// Merge Auswaertz Ringelsocken und Stutzten
	this->MergeSplitField (VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN);

} // PostExternalMergeSplitFields

void verein::DecodeBooleansFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Boolean Pokalmannschaft
	this->DecodeBooleanFromA3Db(VEREIN_SECTION_POS_HIDDEN_POKALMANNSCHAFT);

	// Decode Boolean Medienstadt
	this->DecodeBooleanFromA3Db(VEREIN_SECTION_POS_HIDDEN_MEDIENSTADT);

	// Decode Boolean Aktiengesellschaft
	this->DecodeBooleanFromA3Db(VEREIN_SECTION_POS_HIDDEN_AKTIENGESELLSCHAFT);

	// Decode Boolean Heim Ringelsocken
	this->DecodeBooleanFromA3Db(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN);

	// Decode Boolean Auswaertz Ringelsocken
	this->DecodeBooleanFromA3Db(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN);

} // DecodeBooleansFromA3Db

void verein::EncodeBooleansToA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Boolean Pokalmannschaft
	this->EncodeBooleanToA3Db(VEREIN_SECTION_POS_HIDDEN_POKALMANNSCHAFT, 
		GetValueFromVereinBooleanType(VEREIN_BOOLEAN_POKALMANNSCHAFT));

	// Decode Boolean Medienstadt
	this->EncodeBooleanToA3Db(VEREIN_SECTION_POS_HIDDEN_MEDIENSTADT, 
		GetValueFromVereinBooleanType(VEREIN_BOOLEAN_MEDIENSTADT));

	// Decode Boolean Aktiengesellschaft
	this->EncodeBooleanToA3Db(VEREIN_SECTION_POS_HIDDEN_AKTIENGESELLSCHAFT, 
		GetValueFromVereinBooleanType(VEREIN_BOOLEAN_AKTIENGESELLSCHAFT));

	// Decode Boolean Heim Ringelsocken
	this->EncodeBooleanToA3Db(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN, 
		GetValueFromVereinBooleanType(VEREIN_BOOLEAN_RINGELSOCKEN));

	// Decode Boolean Auswaertz Ringelsocken
	this->EncodeBooleanToA3Db(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN, 
		GetValueFromVereinBooleanType(VEREIN_BOOLEAN_RINGELSOCKEN));

} // EncodeBooleansToA3Db

void verein::DecodeEnumsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Enum Heim Trikot Farbe 1
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Heim Trikot Farbe 2
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE2, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Heim Trikot Muster
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER, VEREIN_ENUM_TRIKOT_MUSTER, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Heim Hose Farbe
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_HOSENFARBE, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Heim Stutzen Farbe
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Auswaerts Trikot Farbe 1
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Auswaerts Trikot Farbe 2
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE2, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Auswaerts Trikot Muster
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER, VEREIN_ENUM_TRIKOT_MUSTER, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Auswaerts Hose Farbe
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_HOSENFARBE, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Auswaerts Stutzen Farbe
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Kuerzl
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_KUERZEL_ARTIKEL, VEREIN_ENUM_KUERZL, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Fanaufkommen
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_FANAUFKOMMEN, VEREIN_ENUM_FANAUFKOMMEN, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Max Fanaufkommen
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_MAX_FANAUFKOMMEN, VEREIN_ENUM_FANAUFKOMMEN, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum ArtDerFans
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_ART_DER_FANS, VEREIN_ENUM_ARTDERFANS, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Vorstand
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_VORSTAND, VEREIN_ENUM_VORSTAND, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Opposition
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_OPPOSITION, VEREIN_ENUM_OPPOSITION, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Finanzkraft
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_FINANZKRAFT, VEREIN_ENUM_FINANZKRAFT, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Hooligans
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_HOOLIGANS, VEREIN_ENUM_HOOLIGANS, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum RegionalligaAb2000
	this->DecodeEnumFromA3Db(VEREIN_SECTION_POS_HIDDEN_REGIONALLIGA_AB_2000, VEREIN_ENUM_REGIONALLIGAAB2000, GetVereinEnumValue, GetEnumDetails);

} // DecodeEnumsFromA3Db

void verein::EncodeEnumsToA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Encode Enum Heim Trikot Farbe 1
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Heim Trikot Farbe 2
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE2, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Heim Trikot Muster
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER, VEREIN_ENUM_TRIKOT_MUSTER, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Heim Hose Farbe
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_HOSENFARBE, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Heim Stutzen Farbe
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Auswaerts Trikot Farbe 1
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Auswaerts Trikot Farbe 2
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE2, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Auswaerts Trikot Muster
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER, VEREIN_ENUM_TRIKOT_MUSTER, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Auswaerts Hose Farbe
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_HOSENFARBE, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Auswaerts Stutzen Farbe
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE, VEREIN_ENUM_TRIKOT_FARBE, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Kuerzl
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_KUERZEL_ARTIKEL, VEREIN_ENUM_KUERZL, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Fanaufkommen
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_FANAUFKOMMEN, VEREIN_ENUM_FANAUFKOMMEN, GetVereinEnumValue, GetEnumDetails);

	// Decode Enum Max Fanaufkommen
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_MAX_FANAUFKOMMEN, VEREIN_ENUM_FANAUFKOMMEN, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum ArtDerFans
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_ART_DER_FANS, VEREIN_ENUM_ARTDERFANS, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Vorstand
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_VORSTAND, VEREIN_ENUM_VORSTAND, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Opposition
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_OPPOSITION, VEREIN_ENUM_OPPOSITION, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Finanzkraft
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_FINANZKRAFT, VEREIN_ENUM_FINANZKRAFT, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum Hooligans
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_HOOLIGANS, VEREIN_ENUM_HOOLIGANS, GetVereinEnumValue, GetEnumDetails);

	// Encode Enum RegionalligaAb2000
	this->EncodeEnumToA3Db(VEREIN_SECTION_POS_HIDDEN_REGIONALLIGA_AB_2000, VEREIN_ENUM_REGIONALLIGAAB2000, GetVereinEnumValue, GetEnumDetails);

} // EncodeEnumsToA3Db

void GetEnumDetails (int SectionPos, int EnumType, ENUM_FUNC& EnumFunc, int& EnumLow, int& EnumHigh)
{
	switch ((VEREIN_ENUM_TYPE) EnumType)
	{
	case VEREIN_ENUM_TRIKOT_FARBE:
		EnumFunc = GetNameFromVereinTrikotFarbeType;
		EnumLow = VEREIN_TRIKOT_FARBE_UNKNOWN;
		EnumHigh = NO_OF_VEREIN_TRIKOT_FARBE_TYPES;
		break;

	case VEREIN_ENUM_TRIKOT_MUSTER:
		EnumFunc = GetNameFromVereinTrikotMusterType;
		EnumLow = VEREIN_TRIKOT_MUSTER_UNKNOWN;
		EnumHigh = NO_OF_VEREIN_TRIKOT_MUSTER_TYPES;
		break;

	case VEREIN_ENUM_TRIKOT_RINGELSOCKEN:
		EnumFunc = GetNameFromVereinTrikotRingelsockenType;
		EnumLow = VEREIN_TRIKOT_RINGELSOCKEN_UNKNOWN;
		EnumHigh = NO_OF_VEREIN_TRIKOT_RINGELSOCKEN_TYPES;
		break;

	case VEREIN_ENUM_KUERZL:
		EnumFunc = GetNameFromVereinKuerzlType;
		EnumLow = VEREIN_KUERZL_UNKNOWN;
		EnumHigh = NO_OF_VEREIN_KUERZL_TYPES;
		break;

	case VEREIN_ENUM_FANAUFKOMMEN:
		EnumFunc = GetNameFromVereinFanaufkommenType;
		EnumLow = VEREIN_FANAUFKOMMEN_UNKNOWN;
		EnumHigh = NO_OF_VEREIN_FANAUFKOMMEN_TYPES;
		break;

	case VEREIN_ENUM_ARTDERFANS:
		EnumFunc = GetNameFromVereinArtDerFansType;
		EnumLow = VEREIN_ARTDERFANS_UNKNOWN;
		EnumHigh = NO_OF_VEREIN_ARTDERFANS_TYPES;
		break;

	case VEREIN_ENUM_VORSTAND:
		EnumFunc = GetNameFromVereinVorstandType;
		EnumLow = VEREIN_VORSTAND_UNKNOWN;
		EnumHigh = NO_OF_VEREIN_VORSTAND_TYPES;
		break;

	case VEREIN_ENUM_OPPOSITION:
		EnumFunc = GetNameFromVereinOppositionType;
		EnumLow = VEREIN_OPPOSITION_UNKNOWN;
		EnumHigh = NO_OF_VEREIN_OPPOSITION_TYPES;
		break;

	case VEREIN_ENUM_FINANZKRAFT:
		EnumFunc = GetNameFromVereinFinanzkraftType;
		EnumLow = VEREIN_FINANZKRAFT_UNKNOWN;
		EnumHigh = NO_OF_VEREIN_FINANZKRAFT_TYPES;
		break;

	case VEREIN_ENUM_HOOLIGANS:
		EnumFunc = GetNameFromVereinHooligansType;
		EnumLow = VEREIN_HOOLIGANS_UNKNOWN;
		EnumHigh = NO_OF_VEREIN_HOOLIGANS_TYPES;
		break;

	case VEREIN_ENUM_REGIONALLIGAAB2000:
		EnumFunc = GetNameFromVereinRegionalligaAb2000Type;
		EnumLow = VEREIN_REGIONALLIGAAB2000_UNKNOWN;
		EnumHigh = NO_OF_VEREIN_REGIONALLIGAAB2000_TYPES;
		break;
		
	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << EnumType << " (" << 
			GetNameFromVereinEnumType((VEREIN_ENUM_TYPE) EnumType) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	} // switch enum type
} // GetEnumDetails

void verein::GetGenericSplitFieldsForField (int VereinSectionPos, std::vector<int>& SplitFields)
{
	switch ((VEREIN_SECTION_POS_TYPE) VereinSectionPos)
	{
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER:
		SplitFields.push_back(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1);
		SplitFields.push_back(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER);
		break;

	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN:
		SplitFields.push_back(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE);
		SplitFields.push_back(VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN);
		break;

	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER:
		SplitFields.push_back(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1);
		SplitFields.push_back(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER);
		break;

	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN:
		SplitFields.push_back(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE);
		SplitFields.push_back(VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << VereinSectionPos << "-" << 
			GetNameFromVereinSectionPosType((VEREIN_SECTION_POS_TYPE) VereinSectionPos) << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}
} // GetGenericSplitFieldsForField

void verein::CalcVereinLandIndex (std::shared_ptr<nation> NationReference)
{
	// Increment Vereinszahl
	NationReference->IncrementVereinCount(1);

	// Set Verein Index
	this->AssignField(VEREIN_SECTION_POS_VEREIN_LAND_INDEX, NationReference->GetValueAtSectionPos(NATION_SECTION_POS_VEREINSANZAHL));
} // CalcVereinLandIndex

std::string VereinValueToVereinString (const std::string& VereinValue, const std::string& LandId, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
#if DEBUG_ENABLED
	std::cout << __FUNCTION__ << " - \"Verein\":::\"Land\" -> " << "\"" << VereinValue << "\"" << ":::" << "\"" << LandId << "\"" << std::endl;
#endif

	std::string VereinString = "";

	// Since the index is based
	if(VereinValue.size() > 0)
	{
		// subtract 1 from index as linked with values starting with 1 (list index starting with 0
		int VereinInt = T_StringToNumber<int>(VereinValue) - 1;

		if (VereinInt >= 0)
		{
			size_t VereinIndex = VereinInt;
			if (VereinValue.compare(A3DB_NO_VEREIN_STRING) == 0)
			{
				VereinString = A3DB_NO_VEREIN_EXPANDED_STRING;
			} // if no verein
			else if (SectionList[SECTION_TYPE_VEREIN].size() >= VereinIndex)
			{
				// Lookup the right Verein, based on the right land
//				std::vector<std::shared_ptr<section>>::iterator VereinIterator;
				std::vector<std::shared_ptr<section>> VereinVector = SectionList [SECTION_TYPE_VEREIN];
				bool VereinFound = false;

				VereinFound = FindVereinFromVereinList (VereinValue, LandId, VereinVector, VereinString);
	
				if (!VereinFound)
				{
					std::stringstream ErrorText;
					ErrorText << "No Verein Found with Land(LandId, VereinIndex): " << NationValueToNationString(LandId, SectionList) << 
						"(" <<  "\"" <<LandId << "\"" << ", " << "\"" << VereinValue << "\"" << ") -> " << __FUNCTION__;
					programError (ErrorText.str());	
				} // if no verein found
			} // if have at least enough vereins
			else
			{		
				std::stringstream ErrorText;
				ErrorText << "Only " << SectionList[SECTION_TYPE_VEREIN].size() << " Vereins found, trying to access Verein " << VereinIndex  << " -> " << __FUNCTION__;
				programError (ErrorText.str());	
			}
		} // if have a valid index
	} // if have valid string
#if DEBUG_ENABLED
	else
	{
		std::cout << __FUNCTION__ << "::: Ignore, Input Size only " << VereinValue.size() << std::endl;
	}
#endif

	return (VereinString);
} // VereinValueToVereinString

bool FindVereinFromVereinList (const std::string& VereinValue, const std::string& LandId, std::vector<std::shared_ptr<section>> VereinList, 
								std::string& FoundVereinString)
{
	bool VereinFound = false;

	std::vector<std::shared_ptr<section>>::iterator VereinIterator;
	for (VereinIterator = VereinList.begin(); (VereinIterator != VereinList.end()) && (!VereinFound); ++VereinIterator)
	{
#if DEBUG_ENABLED
		std::cout << "  @ Comparing Verein-Land-LandExpanded-VereinLandIndex -> " <<
			"\"" << std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_VEREINSNAHME) << "\"" << "," <<
			"\"" << std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_LAND) << "\"" << "," <<
			"\"" << std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_LAND_EXPANDED) << "\"" << "," <<
			"\"" << std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_VEREIN_LAND_INDEX) << std::endl;
#endif

		if ((std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_LAND).compare(LandId) == 0) &&
			(std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_VEREIN_LAND_INDEX).compare(VereinValue) == 0))
		{
			FoundVereinString = std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_VEREINSNAHME);
			VereinFound = true;
		} // if land and verein index match
	} // for each Verein

	return (VereinFound);
} // FindVereinFromVereinList

std::string VereinStringToVereinValue (const std::string& VereinString, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
#if DEBUG_ENABLED
	std::cout << __FUNCTION__ << "::: " << VereinString << std::endl;
#endif

	std::string VereinValue = "";
	bool VereinFound = false;

	if (VereinString.compare(A3DB_NO_VEREIN_EXPANDED_STRING) == 0)
	{
		VereinFound = true;
		VereinValue = A3DB_NO_VEREIN_STRING;

#if DEBUG_ENABLED
		std::cout << "  @ No Verein, setting to No Verein Value -> \"" << A3DB_NO_VEREIN_STRING << "\"" << std::endl;
#endif
	} // if no verein
	else
	{
		std::vector<std::shared_ptr<section>>::iterator VereinIterator;
		std::vector<std::shared_ptr<section>> VereinVector = SectionList [SECTION_TYPE_VEREIN];
		for (VereinIterator = VereinVector.begin(); (VereinIterator != VereinVector.end()) && (!VereinFound); ++VereinIterator)
		{
#if DEBUG_ENABLED
			std::cout << "  @ Comparing Verein-Land-LandExpanded-VereinLandIndex -> " <<
				"\"" << std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_VEREINSNAHME) << "\"" << "," <<
				"\"" << std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_LAND) << "\"" << "," <<
				"\"" << std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_LAND_EXPANDED) << "\"" << "," <<
				"\"" << std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_VEREIN_LAND_INDEX) << std::endl;
#endif

			if (std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_VEREINSNAHME).compare(VereinString) == 0)
			{
				VereinFound = true;

				// Set the Value as the VereinLandIndex
				VereinValue = std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_VEREIN_LAND_INDEX);
			}
		} // for each verein
	} // if have verein

	if (!VereinFound)
	{
		std::stringstream ErrorText;
		ErrorText << "No verein found with Value \"" << VereinString << "\"" << std::endl;
		programError (ErrorText.str());	
	}
	// If not found Give an Error

	return (VereinValue);
} // VereinStringToVereinValue

static bool IncludeSectionPosIntoA3Db (VEREIN_SECTION_POS_TYPE SectionPos, SECTION_TYPE DataSection)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case VEREIN_SECTION_POS_LAND:
	case VEREIN_SECTION_POS_VEREINSNAHME:
	case VEREIN_SECTION_POS_KUERZL:
	case VEREIN_SECTION_POS_ANFEUERUNG:
	case VEREIN_SECTION_POS_FANBEZEICHNUNG:
		if(SectionIsVisible(DataSection))
			IncludeIntoA3Db = true;
		else
			IncludeIntoA3Db = false;
		break;

	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE2:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_HOSENFARBE:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE2:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_HOSENFARBE:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN:
	case VEREIN_SECTION_POS_HIDDEN_GUTHABEN_BEI_SPIELBEGINN:
	case VEREIN_SECTION_POS_HIDDEN_KUERZEL_ARTIKEL:
	case VEREIN_SECTION_POS_HIDDEN_FANAUFKOMMEN:
	case VEREIN_SECTION_POS_HIDDEN_ART_DER_FANS:
	case VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT:
	case VEREIN_SECTION_POS_HIDDEN_ERZRIVALE:
	case VEREIN_SECTION_POS_HIDDEN_VORSTAND:
	case VEREIN_SECTION_POS_HIDDEN_POKALMANNSCHAFT:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_17:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_18:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_19:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_20:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_21:
	case VEREIN_SECTION_POS_HIDDEN_OPPOSITION:
	case VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON:
	case VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON:
	case VEREIN_SECTION_POS_HIDDEN_FINANZKRAFT:
	case VEREIN_SECTION_POS_HIDDEN_MAX_FANAUFKOMMEN:
	case VEREIN_SECTION_POS_HIDDEN_HOOLIGANS:
	case VEREIN_SECTION_POS_HIDDEN_MEDIENSTADT:
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_ERZIELTE_TORE:
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_KASSIERTE_TORE:
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_SPIELE:
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_PUNKTE:
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_NACHNAHME:
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_VORNAHME:
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_GEBURTSDATUM:
	case VEREIN_SECTION_POS_HIDDEN_AKTIENGESELLSCHAFT:
	case VEREIN_SECTION_POS_HIDDEN_TITEL_MEISTERSCHAFTEN:
	case VEREIN_SECTION_POS_HIDDEN_TITEL_POKALE:
	case VEREIN_SECTION_POS_HIDDEN_TITEL_LIGAPOKALE:
	case VEREIN_SECTION_POS_HIDDEN_TITEL_EUROPA_LEAGUES:
	case VEREIN_SECTION_POS_HIDDEN_TITEL_CHAMPIONS_LEAGUES:
	case VEREIN_SECTION_POS_HIDDEN_TITEL_WELTPOKALE:
	case VEREIN_SECTION_POS_HIDDEN_REGIONALLIGA_AB_2000:
	case VEREIN_SECTION_POS_HIDDEN_GRUENDUNGSJAHR:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_45:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_46:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_47:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_48:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_49:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_50:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_51:
		if(SectionIsVisible(DataSection))
			IncludeIntoA3Db = false;
		else
			IncludeIntoA3Db = true;
		break;
		
	case VEREIN_SECTION_POS_LAND_EXPANDED:
	case VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT_EXPANDED:
	case VEREIN_SECTION_POS_HIDDEN_ERZRIVALE_EXPANDED:
	case VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON_EXPANDED:
	case VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON_EXPANDED:
	case VEREIN_SECTION_POS_VEREIN_LAND_INDEX:	
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromVereinSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (VEREIN_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case VEREIN_SECTION_POS_VEREINSNAHME:
	case VEREIN_SECTION_POS_KUERZL:
	case VEREIN_SECTION_POS_ANFEUERUNG:
	case VEREIN_SECTION_POS_FANBEZEICHNUNG:	
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE2:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_HOSENFARBE:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE2:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_HOSENFARBE:
	case VEREIN_SECTION_POS_HIDDEN_GUTHABEN_BEI_SPIELBEGINN:
	case VEREIN_SECTION_POS_HIDDEN_KUERZEL_ARTIKEL:
	case VEREIN_SECTION_POS_HIDDEN_FANAUFKOMMEN:
	case VEREIN_SECTION_POS_HIDDEN_ART_DER_FANS:
	case VEREIN_SECTION_POS_HIDDEN_VORSTAND:
	case VEREIN_SECTION_POS_HIDDEN_POKALMANNSCHAFT:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_17:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_18:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_19:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_20:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_21:
	case VEREIN_SECTION_POS_HIDDEN_OPPOSITION:
	case VEREIN_SECTION_POS_HIDDEN_FINANZKRAFT:
	case VEREIN_SECTION_POS_HIDDEN_MAX_FANAUFKOMMEN:
	case VEREIN_SECTION_POS_HIDDEN_HOOLIGANS:
	case VEREIN_SECTION_POS_HIDDEN_MEDIENSTADT:
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_ERZIELTE_TORE:
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_KASSIERTE_TORE:
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_SPIELE:
	case VEREIN_SECTION_POS_HIDDEN_EWIGE_TABELLE_PUNKTE:
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_NACHNAHME:
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_VORNAHME:
	case VEREIN_SECTION_POS_HIDDEN_VORSITZENDER_GEBURTSDATUM:
	case VEREIN_SECTION_POS_HIDDEN_AKTIENGESELLSCHAFT:
	case VEREIN_SECTION_POS_HIDDEN_TITEL_MEISTERSCHAFTEN:
	case VEREIN_SECTION_POS_HIDDEN_TITEL_POKALE:
	case VEREIN_SECTION_POS_HIDDEN_TITEL_LIGAPOKALE:
	case VEREIN_SECTION_POS_HIDDEN_TITEL_EUROPA_LEAGUES:
	case VEREIN_SECTION_POS_HIDDEN_TITEL_CHAMPIONS_LEAGUES:
	case VEREIN_SECTION_POS_HIDDEN_TITEL_WELTPOKALE:
	case VEREIN_SECTION_POS_HIDDEN_REGIONALLIGA_AB_2000:
	case VEREIN_SECTION_POS_HIDDEN_GRUENDUNGSJAHR:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_45:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_46:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_47:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_48:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_49:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_50:
	case VEREIN_SECTION_POS_HIDDEN_UNKNOWN_51:		
	case VEREIN_SECTION_POS_LAND_EXPANDED:
	case VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT_EXPANDED:
	case VEREIN_SECTION_POS_HIDDEN_ERZRIVALE_EXPANDED:
	case VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON_EXPANDED:
	case VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON_EXPANDED:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN:
		IncludeIntoXml = true;
		break;
		
	case VEREIN_SECTION_POS_LAND:
	case VEREIN_SECTION_POS_HIDDEN_FANFREUNDSCHAFT_MIT:
	case VEREIN_SECTION_POS_HIDDEN_ERZRIVALE:
	case VEREIN_SECTION_POS_HIDDEN_AMATEURABTEILUNG_VON:
	case VEREIN_SECTION_POS_HIDDEN_PROFIABTEILUNG_VON:
	case VEREIN_SECTION_POS_VEREIN_LAND_INDEX:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN:
		IncludeIntoXml = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromVereinSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static VEREIN_SECTION_POS_TYPE GetVereinSectionPosTypeFromString (const std::string& TypeString)
{
	VEREIN_SECTION_POS_TYPE FoundPos = VEREIN_SECTION_POS_UNKNOWN;

	for (int TempPos = VEREIN_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_VEREIN_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromVereinSectionPosType ((VEREIN_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (VEREIN_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetVereinSectionPosTypeFromString

void AssignVereinField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<verein>(SectionList, SectionLineCount, Line);
} // AssignVereinField

std::string GetVereinCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = VEREIN_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_VEREIN_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromVereinSectionPosType ((VEREIN_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetVereinCsvHeader

int GetVereinHiddenOffset ()
{
	return (GetNoOfFieldsInA3Section(SECTION_TYPE_VEREIN));
} // GetVereinHiddenOffset

void CalculateVereinIndices (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator VereinIterator;
	std::vector<std::shared_ptr<section>> VereinVector = SectionList[SECTION_TYPE_VEREIN];
	for (VereinIterator = VereinVector.begin(); VereinIterator != VereinVector.end(); ++VereinIterator)
	{
		if (std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_VEREIN_LAND_INDEX).compare(VEREIN_LAND_INDEX_NOT_SET) == 0)
		{
#if DEBUG_ENABLED
std::cout << __FUNCTION__ << " - Convert Land: \"" << std::static_pointer_cast<verein>(*VereinIterator)->GetA3FileLandId() << "\" for " <<
	std::static_pointer_cast<verein>(*VereinIterator)->GetValueAtSectionPos(VEREIN_SECTION_POS_VEREINSNAHME) << std::endl;
#endif
			int NationIndex = T_StringToNumber<int>(std::static_pointer_cast<verein>(*VereinIterator)->GetA3FileLandId());

			std::static_pointer_cast<verein>(*VereinIterator)->CalcVereinLandIndex(std::static_pointer_cast<nation>(SectionList[SECTION_TYPE_NATION].at(NationIndex)));
		} // if index not yet set		
	} // for each verein
} // CalculateVereinIndices

static VEREIN_ENUM_TYPE GetVereinEnumTypeFromPosition (VEREIN_SECTION_POS_TYPE SectionPos)
{
	VEREIN_ENUM_TYPE EnumType = VEREIN_ENUM_UNKNOWN;
	switch ((VEREIN_SECTION_POS_TYPE) SectionPos)
	{
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE2:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_HOSENFARBE:
	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_FARBE1:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE2:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_HOSENFARBE:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_STUTZENFARBE:
		EnumType = VEREIN_ENUM_TRIKOT_FARBE;
		break;
		
	case VEREIN_SECTION_POS_HIDDEN_ART_DER_FANS:
		EnumType = VEREIN_ENUM_ARTDERFANS;
		break;

	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER:
	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_FARBE1_UND_MUSTER_SPLIT_MUSTER:
		EnumType = VEREIN_ENUM_TRIKOT_MUSTER;
		break;

	case VEREIN_SECTION_POS_HIDDEN_FANAUFKOMMEN:
		EnumType = VEREIN_ENUM_FANAUFKOMMEN;
		break;

	case VEREIN_SECTION_POS_HIDDEN_FINANZKRAFT:
		EnumType = VEREIN_ENUM_FINANZKRAFT;
		break;

	case VEREIN_SECTION_POS_HIDDEN_HOOLIGANS:
		EnumType = VEREIN_ENUM_HOOLIGANS;
		break;

	case VEREIN_SECTION_POS_HIDDEN_KUERZEL_ARTIKEL:
		EnumType = VEREIN_ENUM_KUERZL;
		break;

	case VEREIN_SECTION_POS_HIDDEN_MAX_FANAUFKOMMEN:
		EnumType = VEREIN_ENUM_FANAUFKOMMEN;
		break;

	case VEREIN_SECTION_POS_HIDDEN_OPPOSITION:
		EnumType = VEREIN_ENUM_OPPOSITION;
		break;

	case VEREIN_SECTION_POS_HIDDEN_REGIONALLIGA_AB_2000:
		EnumType = VEREIN_ENUM_REGIONALLIGAAB2000;
		break;

	case VEREIN_SECTION_POS_HIDDEN_VORSTAND:
		EnumType = VEREIN_ENUM_VORSTAND;
		break;
		
	default:
		//do nothing
		break;
	} // switch section pos

	return (EnumType);
} // GetVereinEnumTypeFromPosition

VEREIN_BOOLEAN_TYPE GetVereinBooleanTypeFromPosition (VEREIN_SECTION_POS_TYPE SectionPos)
{
	VEREIN_BOOLEAN_TYPE BooleanType = VEREIN_BOOLEAN_UNKNOWN;
	switch (SectionPos)
	{		
	case VEREIN_SECTION_POS_HIDDEN_POKALMANNSCHAFT:
		BooleanType = VEREIN_BOOLEAN_POKALMANNSCHAFT;
		break;

	case VEREIN_SECTION_POS_HIDDEN_MEDIENSTADT:
		BooleanType = VEREIN_BOOLEAN_MEDIENSTADT;
		break;

	case VEREIN_SECTION_POS_HIDDEN_AKTIENGESELLSCHAFT:
		BooleanType = VEREIN_BOOLEAN_AKTIENGESELLSCHAFT;
		break;

	case VEREIN_SECTION_POS_HIDDEN_HEIMTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN:
		BooleanType = VEREIN_BOOLEAN_RINGELSOCKEN;
		break;

	case VEREIN_SECTION_POS_HIDDEN_AUSWAERTSTRIKOT_STUTZENFARBE_UND_RINGELSOCKEN_SPLIT_RINGELSOCKEN:
		BooleanType = VEREIN_BOOLEAN_RINGELSOCKEN;
		break;

	default:
		//do nothing
		break;
	} // switch section pos

	return (BooleanType);
} // GetVereinBooleanTypeFromPosition

void GetVereinAllowedValues (std::vector<FIELD_VALUE_STRUCT>& AllowedValues)
{
	for (int SectionPos = VEREIN_SECTION_POS_UNKNOWN + 1; SectionPos < NO_OF_VEREIN_SECTION_POS_TYPES; SectionPos++)
	{
		ENUM_FUNC EnumFunc = nullptr;
		int EnumLow = 0;
		int EnumHigh = 0;
		VEREIN_ENUM_TYPE VereinEnum = VEREIN_ENUM_UNKNOWN;
		VEREIN_BOOLEAN_TYPE VereinBoolean = VEREIN_BOOLEAN_UNKNOWN;
		bool DetailsFound = false;

		if ((VereinEnum = GetVereinEnumTypeFromPosition ((VEREIN_SECTION_POS_TYPE) SectionPos)) != VEREIN_ENUM_UNKNOWN)
		{
			// Ignore this for special case handled below
			GetEnumDetails(SectionPos, VereinEnum, EnumFunc, EnumLow, EnumHigh);
			DetailsFound = true;
		} // if enum field
		else if ((VereinBoolean = GetVereinBooleanTypeFromPosition ((VEREIN_SECTION_POS_TYPE) SectionPos)) != VEREIN_BOOLEAN_UNKNOWN)
		{
			GetBooleanEnumDetails (EnumFunc, EnumLow, EnumHigh);
			DetailsFound = true;
		} // if boolean field

		// Add Values
		if (DetailsFound)
		{
			// Add the Value Entry to the List
			AddFieldValueEntryToList (AllowedValues, GetNameFromVereinSectionPosType((VEREIN_SECTION_POS_TYPE) SectionPos));

			// Add allowed Values
			AddFieldValuesForLastEntry (AllowedValues, EnumLow, EnumHigh, EnumFunc);
		} // if got a function
	} // for each section pos
} // GetVereinAllowedValues
