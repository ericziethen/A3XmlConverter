#include "stadion.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

stadion::stadion()
{
}

stadion::~stadion(void)
{
}

std::string stadion::GetUniqueId ()
{
	return(this->Stadionnahme);
} // GetUniqueId

SECTION_TYPE stadion::GetSectionType ()
{
	return(SECTION_TYPE_STADION);
} // GetSectionType

std::string stadion::GetValueAtSectionPos (int SectionPos)
{
	switch (SectionPos)
	{
	case STADION_SECTION_POS_STADIONNAHME:
		return (this->Stadionnahme);
	case STADION_SECTION_POS_ORT:
		return (this->Ort);
	case STADION_SECTION_POS_ANZEIGETAFEL:
		return (this->Anzeigetafel);
	case STADION_SECTION_POS_RASENHEIZUNG:
		return (this->Rasenheizung);
	case STADION_SECTION_POS_UNKNOWN_05:
		return (this->STADION_FIELD_UNKNOWN_05);
	case STADION_SECTION_POS_UNKNOWN_06:
		return (this->STADION_FIELD_UNKNOWN_06);
	case STADION_SECTION_POS_FLUTLICHT:
		return (this->Flutlicht);
	case STADION_SECTION_POS_HEIMTRIBUENE:
		return (this->Heimtribuene);
	case STADION_SECTION_POS_GEGENTRIBUENE:
		return (this->Gegentribuene);
	case STADION_SECTION_POS_CITYLAGE:
		return (this->Citylage);
	case STADION_SECTION_POS_IM_BESITZ_DES_VEREINS:
		return (this->ImBesitzDesVereins);
	case STADION_SECTION_POS_AUTOBAHNANBINDUNG:
		return (this->Autobahnanbindung);
	case STADION_SECTION_POS_FERNSEHTURM:
		return (this->Fernsehturm);
	case STADION_SECTION_POS_HAUPTTRIBUENE_STEH:
		return (this->Haupttribuene_STEH);
	case STADION_SECTION_POS_HAUPTTRIBUENE_SITZ:
		return (this->Haupttribuene_SITZ);
	case STADION_SECTION_POS_HAUPTTRIBUENE_VIP:
		return (this->Haupttribuene_VIP);
	case STADION_SECTION_POS_HAUPTTRIBUENE_ZUSTAND:
		return (this->Haupttribuene_ZUSTAND);
	case STADION_SECTION_POS_GEGENTRIBUENE_STEH:
		return (this->Gegentribuene_STEH);
	case STADION_SECTION_POS_GEGENTRIBUENE_SITZ:
		return (this->Gegentribuene_SITZ);
	case STADION_SECTION_POS_GEGENTRIBUENE_VIP:
		return (this->Gegentribuene_VIP);
	case STADION_SECTION_POS_GEGENTRIBUENE_ZUSTAND:
		return (this->Gegentribuene_ZUSTAND);
	case STADION_SECTION_POS_TRIBUENE_LINKS_STEH:
		return (this->TribueneLinks_STEH);
	case STADION_SECTION_POS_TRIBUENE_LINKS_SITZ:
		return (this->TribueneLinks_SITZ);
	case STADION_SECTION_POS_TRIBUENE_LINKS_VIP:
		return (this->TribueneLinks_VIP);
	case STADION_SECTION_POS_TRIBUENE_LINKS_ZUSTAND:
		return (this->TribueneLinks_ZUSTAND);
	case STADION_SECTION_POS_TRIBUENE_RECHTS_STEH:
		return (this->TribueneRechts_STEH);
	case STADION_SECTION_POS_TRIBUENE_RECHTS_SITZ:
		return (this->TribueneRechts_SITZ);
	case STADION_SECTION_POS_TRIBUENE_RECHTS_VIP:
		return (this->TribueneRechts_VIP);
	case STADION_SECTION_POS_TRIBUENE_RECHTS_ZUSTAND:
		return (this->TribueneRechts_ZUSTAND);
	case STADION_SECTION_POS_DACH:
		return (this->Dach);
	case STADION_SECTION_POS_LAUFBAHN:
		return (this->Laufbahn);
	case STADION_SECTION_POS_WAERMESTRAHLER:
		return (this->Waermestrahler);
	case STADION_SECTION_POS_LUXUSKABINEN:
		return (this->Luxuskabinen);
	case STADION_SECTION_POS_SITZKISSEN:
		return (this->Sitzkissen);
	case STADION_SECTION_POS_BEHEIZBARE_SITZE:
		return (this->BeheizbareSitze);
	case STADION_SECTION_POS_AUSFAHRBARES_SPIELFELD:
		return (this->AusfahrbaresSpielfeld);
	case STADION_SECTION_POS_BERGE:
		return (this->Berge);
	case STADION_SECTION_POS_BURG:
		return (this->Burg);
	case STADION_SECTION_POS_SCHLOSS:
		return (this->Schloss);

	// Bitmask Fields
	case STADION_SECTION_POS_DACH_SPLIT_HAUPT:
		return (this->Dach_Split_Haupt);
	case STADION_SECTION_POS_DACH_SPLIT_GEGEN:
		return (this->Dach_Split_Gegen);
	case STADION_SECTION_POS_DACH_SPLIT_LINKS:
		return (this->Dach_Split_Links);
	case STADION_SECTION_POS_DACH_SPLIT_RECHTS:
		return (this->Dach_Split_Rechts);

	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_HAUPT:
		return (this->Waermestrahler_Split_Haupt);
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_GEGEN:
		return (this->Waermestrahler_Split_Gegen);
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_LINKS:
		return (this->Waermestrahler_Split_Links);
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_RECHTS:
		return (this->Waermestrahler_Split_Rechts);

			// Parent Section
	case STADION_SECTION_POS_REFERENCE_SECTION:
		return (this->GetParentId());	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return(ErrorText.str());
	}
} // GetValueAtSectionPos

static std::string GetNameFromStadionSectionPosType (const STADION_SECTION_POS_TYPE StadionSectionPosType)
{
	switch (StadionSectionPosType)
	{
	case STADION_SECTION_POS_STADIONNAHME:
		return ("Stadionnahme");
	case STADION_SECTION_POS_ORT:
		return ("Ort");
	case STADION_SECTION_POS_ANZEIGETAFEL:
		return ("Anzeigetafel");
	case STADION_SECTION_POS_RASENHEIZUNG:
		return ("Rasenheizung");
	case STADION_SECTION_POS_UNKNOWN_05:
		return ("STADION_FIELD_UNKNOWN_05");
	case STADION_SECTION_POS_UNKNOWN_06:
		return ("STADION_FIELD_UNKNOWN_06");
	case STADION_SECTION_POS_FLUTLICHT:
		return ("Flutlicht");
	case STADION_SECTION_POS_HEIMTRIBUENE:
		return ("Heimtribuene");
	case STADION_SECTION_POS_GEGENTRIBUENE:
		return ("Gegentribuene");
	case STADION_SECTION_POS_CITYLAGE:
		return ("Citylage");
	case STADION_SECTION_POS_IM_BESITZ_DES_VEREINS:
		return ("ImBesitzDesVereins");
	case STADION_SECTION_POS_AUTOBAHNANBINDUNG:
		return ("Autobahnanbindung");
	case STADION_SECTION_POS_FERNSEHTURM:
		return ("Fernsehturm");
	case STADION_SECTION_POS_HAUPTTRIBUENE_STEH:
		return ("Haupttribuene_STEH");
	case STADION_SECTION_POS_HAUPTTRIBUENE_SITZ:
		return ("Haupttribuene_SITZ");
	case STADION_SECTION_POS_HAUPTTRIBUENE_VIP:
		return ("Haupttribuene_VIP");
	case STADION_SECTION_POS_HAUPTTRIBUENE_ZUSTAND:
		return ("Haupttribuene_ZUSTAND");
	case STADION_SECTION_POS_GEGENTRIBUENE_STEH:
		return ("Gegentribuene_STEH");
	case STADION_SECTION_POS_GEGENTRIBUENE_SITZ:
		return ("Gegentribuene_SITZ");
	case STADION_SECTION_POS_GEGENTRIBUENE_VIP:
		return ("Gegentribuene_VIP");
	case STADION_SECTION_POS_GEGENTRIBUENE_ZUSTAND:
		return ("Gegentribuene_ZUSTAND");
	case STADION_SECTION_POS_TRIBUENE_LINKS_STEH:
		return ("TribueneLinks_STEH");
	case STADION_SECTION_POS_TRIBUENE_LINKS_SITZ:
		return ("TribueneLinks_SITZ");
	case STADION_SECTION_POS_TRIBUENE_LINKS_VIP:
		return ("TribueneLinks_VIP");
	case STADION_SECTION_POS_TRIBUENE_LINKS_ZUSTAND:
		return ("TribueneLinks_ZUSTAND");
	case STADION_SECTION_POS_TRIBUENE_RECHTS_STEH:
		return ("TribueneRechts_STEH");
	case STADION_SECTION_POS_TRIBUENE_RECHTS_SITZ:
		return ("TribueneRechts_SITZ");
	case STADION_SECTION_POS_TRIBUENE_RECHTS_VIP:
		return ("TribueneRechts_VIP");
	case STADION_SECTION_POS_TRIBUENE_RECHTS_ZUSTAND:
		return ("TribueneRechts_ZUSTAND");
	case STADION_SECTION_POS_DACH:
		return ("Dach_UNSPLIT_BISMASK");
	case STADION_SECTION_POS_LAUFBAHN:
		return ("Laufbahn");
	case STADION_SECTION_POS_WAERMESTRAHLER:
		return ("Waermestrahler_UNSPLIT_BISMASK");
	case STADION_SECTION_POS_LUXUSKABINEN:
		return ("Luxuskabinen");
	case STADION_SECTION_POS_SITZKISSEN:
		return ("Sitzkissen");
	case STADION_SECTION_POS_BEHEIZBARE_SITZE:
		return ("BeheizbareSitze");
	case STADION_SECTION_POS_AUSFAHRBARES_SPIELFELD:
		return ("AusfahrbaresSpielfeld");
	case STADION_SECTION_POS_BERGE:
		return ("Berge");
	case STADION_SECTION_POS_BURG:
		return ("Burg");
	case STADION_SECTION_POS_SCHLOSS:
		return ("Schloss");

	case STADION_SECTION_POS_REFERENCE_SECTION:
		return (XML_PARENT_SECTION_STRING);	

	// Split Bitmask
	case STADION_SECTION_POS_DACH_SPLIT_HAUPT:
		return ("Dach_Haupt");
	case STADION_SECTION_POS_DACH_SPLIT_GEGEN:
		return ("Dach_Gegen");
	case STADION_SECTION_POS_DACH_SPLIT_LINKS:
		return ("Dach_Links");
	case STADION_SECTION_POS_DACH_SPLIT_RECHTS:
		return ("Dach_Rechts");

	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_HAUPT:
		return ("Waermestrahler_Haupt");
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_GEGEN:
		return ("Waermestrahler_Gegen");
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_LINKS:
		return ("Waermestrahler_Links");
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_RECHTS:
		return ("Waermestrahler_Rechts");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unhandled Section Pos" << StadionSectionPosType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
		return (ErrorText.str().c_str());

	} // switch
} // GetNameFromStadionSectionPosType

void stadion::AssignField (int SectionPos, const std::string& FieldValue)
{	
	switch (SectionPos)
	{
	case STADION_SECTION_POS_STADIONNAHME:
		this->Stadionnahme = FieldValue;
		break;
	case STADION_SECTION_POS_ORT:
		this->Ort = FieldValue;
		break;
	case STADION_SECTION_POS_ANZEIGETAFEL:
		this->Anzeigetafel = FieldValue;
		break;
	case STADION_SECTION_POS_RASENHEIZUNG:
		this->Rasenheizung = FieldValue;
		break;
	case STADION_SECTION_POS_UNKNOWN_05:
		this->STADION_FIELD_UNKNOWN_05 = FieldValue;
		break;
	case STADION_SECTION_POS_UNKNOWN_06:
		this->STADION_FIELD_UNKNOWN_06 = FieldValue;
		break;
	case STADION_SECTION_POS_FLUTLICHT:
		this->Flutlicht = FieldValue;
		break;
	case STADION_SECTION_POS_HEIMTRIBUENE:
		this->Heimtribuene = FieldValue;
		break;
	case STADION_SECTION_POS_GEGENTRIBUENE:
		this->Gegentribuene = FieldValue;
		break;
	case STADION_SECTION_POS_CITYLAGE:
		this->Citylage = FieldValue;
		break;
	case STADION_SECTION_POS_IM_BESITZ_DES_VEREINS:
		this->ImBesitzDesVereins = FieldValue;
		break;
	case STADION_SECTION_POS_AUTOBAHNANBINDUNG:
		this->Autobahnanbindung = FieldValue;
		break;
	case STADION_SECTION_POS_FERNSEHTURM:
		this->Fernsehturm = FieldValue;
		break;
	case STADION_SECTION_POS_HAUPTTRIBUENE_STEH:
		this->Haupttribuene_STEH = FieldValue;
		break;
	case STADION_SECTION_POS_HAUPTTRIBUENE_SITZ:
		this->Haupttribuene_SITZ = FieldValue;
		break;
	case STADION_SECTION_POS_HAUPTTRIBUENE_VIP:
		this->Haupttribuene_VIP = FieldValue;
		break;
	case STADION_SECTION_POS_HAUPTTRIBUENE_ZUSTAND:
		this->Haupttribuene_ZUSTAND = FieldValue;
		break;
	case STADION_SECTION_POS_GEGENTRIBUENE_STEH:
		this->Gegentribuene_STEH = FieldValue;
		break;
	case STADION_SECTION_POS_GEGENTRIBUENE_SITZ:
		this->Gegentribuene_SITZ = FieldValue;
		break;
	case STADION_SECTION_POS_GEGENTRIBUENE_VIP:
		this->Gegentribuene_VIP = FieldValue;
		break;
	case STADION_SECTION_POS_GEGENTRIBUENE_ZUSTAND:
		this->Gegentribuene_ZUSTAND = FieldValue;
		break;
	case STADION_SECTION_POS_TRIBUENE_LINKS_STEH:
		this->TribueneLinks_STEH = FieldValue;
		break;
	case STADION_SECTION_POS_TRIBUENE_LINKS_SITZ:
		this->TribueneLinks_SITZ = FieldValue;
		break;
	case STADION_SECTION_POS_TRIBUENE_LINKS_VIP:
		this->TribueneLinks_VIP = FieldValue;
		break;
	case STADION_SECTION_POS_TRIBUENE_LINKS_ZUSTAND:
		this->TribueneLinks_ZUSTAND = FieldValue;
		break;
	case STADION_SECTION_POS_TRIBUENE_RECHTS_STEH:
		this->TribueneRechts_STEH = FieldValue;
		break;
	case STADION_SECTION_POS_TRIBUENE_RECHTS_SITZ:
		this->TribueneRechts_SITZ = FieldValue;
		break;
	case STADION_SECTION_POS_TRIBUENE_RECHTS_VIP:
		this->TribueneRechts_VIP = FieldValue;
		break;
	case STADION_SECTION_POS_TRIBUENE_RECHTS_ZUSTAND:
		this->TribueneRechts_ZUSTAND = FieldValue;
		break;
	case STADION_SECTION_POS_DACH:
		this->Dach = FieldValue;
		break;
	case STADION_SECTION_POS_LAUFBAHN:
		this->Laufbahn = FieldValue;
		break;
	case STADION_SECTION_POS_WAERMESTRAHLER:
		this->Waermestrahler = FieldValue;
		break;
	case STADION_SECTION_POS_LUXUSKABINEN:
		this->Luxuskabinen = FieldValue;
		break;
	case STADION_SECTION_POS_SITZKISSEN:
		this->Sitzkissen = FieldValue;
		break;
	case STADION_SECTION_POS_BEHEIZBARE_SITZE:
		this->BeheizbareSitze = FieldValue;
		break;
	case STADION_SECTION_POS_AUSFAHRBARES_SPIELFELD:
		this->AusfahrbaresSpielfeld = FieldValue;
		break;
	case STADION_SECTION_POS_BERGE:
		this->Berge = FieldValue;
		break;
	case STADION_SECTION_POS_BURG:
		this->Burg = FieldValue;
		break;
	case STADION_SECTION_POS_SCHLOSS:
		this->Schloss = FieldValue;
		break;

			// Parent Section	
	case STADION_SECTION_POS_REFERENCE_SECTION:
		this->SetParentId(FieldValue);
		break;

	// Bitmask Fields
	case STADION_SECTION_POS_DACH_SPLIT_HAUPT:
		this->Dach_Split_Haupt = FieldValue;
		break;
	case STADION_SECTION_POS_DACH_SPLIT_GEGEN:
		this->Dach_Split_Gegen = FieldValue;
		break;
	case STADION_SECTION_POS_DACH_SPLIT_LINKS:
		this->Dach_Split_Links = FieldValue;
		break;
	case STADION_SECTION_POS_DACH_SPLIT_RECHTS:
		this->Dach_Split_Rechts = FieldValue;
		break;

	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_HAUPT:
		this->Waermestrahler_Split_Haupt = FieldValue;
		break;
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_GEGEN:
		this->Waermestrahler_Split_Gegen = FieldValue;
		break;
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_LINKS:
		this->Waermestrahler_Split_Links = FieldValue;
		break;
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_RECHTS:
		this->Waermestrahler_Split_Rechts = FieldValue;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

} // AssignField

void stadion::PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>& ValuePairVector)
{
	ValuePairVector.erase (ValuePairVector.begin(), ValuePairVector.end());

	for (int StadionPos = STADION_SECTION_POS_UNKNOWN + 1; StadionPos < NO_OF_STADION_SECTION_POS_TYPES; StadionPos++)
	{
		if (IncludeSectionPosIntoXml ((STADION_SECTION_POS_TYPE) StadionPos))
		{
			ValuePairVector.push_back(std::shared_ptr<value_pair> (
				new value_pair(GetNameFromStadionSectionPosType ((STADION_SECTION_POS_TYPE) StadionPos), 			
				this->GetValueAtSectionPos(StadionPos))));
		}
	}

} // PopulateValuePairVectorForExport

void stadion::PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>& StadionValuePairs)
{
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = StadionValuePairs.begin(); 
		Iterator != StadionValuePairs.end(); ++Iterator)
	{
		STADION_SECTION_POS_TYPE FieldPos = GetStadionSectionPosTypeFromString((*Iterator)->Tag);
		if (FieldPos != STADION_SECTION_POS_UNKNOWN)
		{
			this->AssignField(FieldPos, (*Iterator)->Value);			
		} // if tag found
	} // for each value pair
} // PopulateFromValuePairs

void stadion::AddFieldsToA3DbList (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSection, const std::string& FileName)
{
	for (int TempPos = STADION_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_STADION_SECTION_POS_TYPES; TempPos++)
	{
		if (IncludeSectionPosIntoA3Db((STADION_SECTION_POS_TYPE) TempPos))
		{
			A3DbOutList.push_back(this->GetValueAtSectionPos(TempPos));
		} // If include in A3Db
	} // for each position
} // AddFieldsToA3DbList

void stadion::SplitBitmaskFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	ENUM_VALUE_LIST BitmaskFields;

	// Split Dach
	this->SplitBitmaskField (STADION_SECTION_POS_DACH, GetStadionEnumValueList(STADION_ENUM_DACH_WAERMESTRAHLER, BitmaskFields));

	// Split Waermestrahler
	this->SplitBitmaskField (STADION_SECTION_POS_WAERMESTRAHLER, GetStadionEnumValueList(STADION_ENUM_DACH_WAERMESTRAHLER, BitmaskFields));

} // SplitBitmaskFields

void stadion::MergeBitmaskFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	ENUM_VALUE_LIST BitmaskFields;

	// Merge Dach
	this->MergeBitmaskField (STADION_SECTION_POS_DACH, GetStadionEnumValueList(STADION_ENUM_DACH_WAERMESTRAHLER, BitmaskFields));

	// Merge Waermestrahler
	this->MergeBitmaskField (STADION_SECTION_POS_WAERMESTRAHLER, GetStadionEnumValueList(STADION_ENUM_DACH_WAERMESTRAHLER, BitmaskFields));

} // MergeBitmaskFields

void stadion::GetGenericSplitFieldsForField (int SpielerSectionPos, std::vector<int>& SplitFields)
{
	// No Generic Split Fields so far for Stadion
} // GetGenericSplitFieldsForField

void stadion::DecodeBooleansFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Boolean AusfahrbaresSpielfeld
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_AUSFAHRBARES_SPIELFELD);

	// Decode Boolean Autobahnanbindung
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_AUTOBAHNANBINDUNG);

	// Decode Boolean BeheizbareSitze
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_BEHEIZBARE_SITZE);

	// Decode Boolean Berge
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_BERGE);

	// Decode Boolean Burg
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_BURG);

	// Decode Boolean Citylage
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_CITYLAGE);

	// Decode Boolean Fernsehturm
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_FERNSEHTURM);

	// Decode Boolean Flutlicht
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_FLUTLICHT);

	// Decode Boolean ImBesitzDesVereins
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_IM_BESITZ_DES_VEREINS);

	// Decode Boolean Laufbahn
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_LAUFBAHN);

	// Decode Boolean Luxuskabinen
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_LUXUSKABINEN);

	// Decode Boolean Rasenheizung
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_RASENHEIZUNG);

	// Decode Boolean Schloss
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_SCHLOSS);

	// Decode Boolean Sitzkissen
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_SITZKISSEN);

	// Decode Boolean Dach_Gegen
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_DACH_SPLIT_GEGEN);

	// Decode Boolean Dach_Haupt
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_DACH_SPLIT_HAUPT);

	// Decode Boolean Dach_Links
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_DACH_SPLIT_LINKS);

	// Decode Boolean Dach_Rechts
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_DACH_SPLIT_RECHTS);

	// Decode Boolean Waermestrahler_Gegen
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_GEGEN);

	// Decode Boolean Waermestrahler_Haupt
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_HAUPT);

	// Decode Boolean Waermestrahler_Links
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_LINKS);

	// Decode Boolean Waermestrahler_Rechts
	this->DecodeBooleanFromA3Db(STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_RECHTS);

} // DecodeBooleansFromA3Db

void stadion::EncodeBooleansToA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Encode Boolean AusfahrbaresSpielfeld
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_AUSFAHRBARES_SPIELFELD, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_AUSFAHRBARESSPIELFELD));

	// Encode Boolean Autobahnanbindung
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_AUTOBAHNANBINDUNG, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_AUTOBAHNANBINDUNG));

	// Encode Boolean BeheizbareSitze
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_BEHEIZBARE_SITZE, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_BEHEIZBARESITZE));

	// Encode Boolean Berge
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_BERGE, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_BERGE));

	// Encode Boolean Burg
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_BURG, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_BURG));

	// Encode Boolean Citylage
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_CITYLAGE, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_CITYLAGE));

	// Encode Boolean Fernsehturm
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_FERNSEHTURM, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_FERNSEHTURM));

	// Encode Boolean Flutlicht
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_FLUTLICHT, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_FLUTLICHT));

	// Encode Boolean ImBesitzDesVereins
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_IM_BESITZ_DES_VEREINS, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_IMBESITZDESVEREINS));

	// Encode Boolean Laufbahn
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_LAUFBAHN, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_LAUFBAHN));

	// Encode Boolean Luxuskabinen
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_LUXUSKABINEN, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_LUXUSKABINEN));

	// Encode Boolean Rasenheizung
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_RASENHEIZUNG, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_RASENHEIZUNG));

	// Encode Boolean Schloss
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_SCHLOSS, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_SCHLOSS));

	// Encode Boolean Sitzkissen
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_SITZKISSEN, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_SITZKISSEN));

	// Encode Boolean Dach_Gegen
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_DACH_SPLIT_GEGEN, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_DACH_GEGEN));

	// Encode Boolean Dach_Haupt
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_DACH_SPLIT_HAUPT, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_DACH_HAUPT));

	// Encode Boolean Dach_Links
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_DACH_SPLIT_LINKS, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_DACH_LINKS));

	// Encode Boolean Dach_Rechts
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_DACH_SPLIT_RECHTS, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_DACH_RECHTS));

	// Encode Boolean Waermestrahler_Gegen
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_GEGEN, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_WAERMESTRAHLER_GEGEN));

	// Encode Boolean Waermestrahler_Haupt
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_HAUPT, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_WAERMESTRAHLER_HAUPT));

	// Encode Boolean Waermestrahler_Links
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_LINKS, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_WAERMESTRAHLER_LINKS));

	// Encode Boolean Waermestrahler_Rechts
	this->EncodeBooleanToA3Db(STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_RECHTS, 
		GetValueFromStadionBooleanType (STADION_BOOLEAN_WAERMESTRAHLER_RECHTS));

} // EncodeBooleansToA3Db

void stadion::DecodeEnumsFromA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Decode Enum Anzeigetafel
	this->DecodeEnumFromA3Db(STADION_SECTION_POS_ANZEIGETAFEL, STADION_ENUM_ANZEIGETAFEL, GetStadionEnumValue, GetEnumDetails);

	// Decode Enum Heimtribuene
	this->DecodeEnumFromA3Db(STADION_SECTION_POS_HEIMTRIBUENE, STADION_ENUM_TRIBUENE, GetStadionEnumValue, GetEnumDetails);

	// Decode Enum Gasttribuene
	this->DecodeEnumFromA3Db(STADION_SECTION_POS_GEGENTRIBUENE, STADION_ENUM_TRIBUENE, GetStadionEnumValue, GetEnumDetails);

	// Decode Enum Tribuene Haupt Zustand
	this->DecodeEnumFromA3Db(STADION_SECTION_POS_HAUPTTRIBUENE_ZUSTAND, STADION_ENUM_ZUSTAND, GetStadionEnumValue, GetEnumDetails);

	// Decode Enum Tribuene Gegen Zustand
	this->DecodeEnumFromA3Db(STADION_SECTION_POS_GEGENTRIBUENE_ZUSTAND, STADION_ENUM_ZUSTAND, GetStadionEnumValue, GetEnumDetails);

	// Decode Enum Tribuene Links Zustand
	this->DecodeEnumFromA3Db(STADION_SECTION_POS_TRIBUENE_LINKS_ZUSTAND, STADION_ENUM_ZUSTAND, GetStadionEnumValue, GetEnumDetails);

	// Decode Enum Tribuene Rechts Zustand
	this->DecodeEnumFromA3Db(STADION_SECTION_POS_TRIBUENE_RECHTS_ZUSTAND, STADION_ENUM_ZUSTAND, GetStadionEnumValue, GetEnumDetails);

} // DecodeEnumsFromA3Db

void stadion::EncodeEnumsToA3Db (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Encode Enum Anzeigetafel
	this->EncodeEnumToA3Db(STADION_SECTION_POS_ANZEIGETAFEL, STADION_ENUM_ANZEIGETAFEL, GetStadionEnumValue, GetEnumDetails);

	// Encode Enum Heimtribuene
	this->EncodeEnumToA3Db(STADION_SECTION_POS_HEIMTRIBUENE, STADION_ENUM_TRIBUENE, GetStadionEnumValue, GetEnumDetails);

	// Encode Enum Gasttribuene
	this->EncodeEnumToA3Db(STADION_SECTION_POS_GEGENTRIBUENE, STADION_ENUM_TRIBUENE, GetStadionEnumValue, GetEnumDetails);

	// Encode Enum Tribuene Haupt Zustand
	this->EncodeEnumToA3Db(STADION_SECTION_POS_HAUPTTRIBUENE_ZUSTAND, STADION_ENUM_ZUSTAND, GetStadionEnumValue, GetEnumDetails);

	// Encode Enum Tribuene Gegen Zustand
	this->EncodeEnumToA3Db(STADION_SECTION_POS_GEGENTRIBUENE_ZUSTAND, STADION_ENUM_ZUSTAND, GetStadionEnumValue, GetEnumDetails);

	// Encode Enum Tribuene Links Zustand
	this->EncodeEnumToA3Db(STADION_SECTION_POS_TRIBUENE_LINKS_ZUSTAND, STADION_ENUM_ZUSTAND, GetStadionEnumValue, GetEnumDetails);

	// Encode Enum Tribuene Rechts Zustand
	this->EncodeEnumToA3Db(STADION_SECTION_POS_TRIBUENE_RECHTS_ZUSTAND, STADION_ENUM_ZUSTAND, GetStadionEnumValue, GetEnumDetails);

} // EncodeEnumsToA3Db

void GetEnumDetails (int SectionPos, int EnumType, ENUM_FUNC& EnumFunc, int& EnumLow, int& EnumHigh)
{
	switch ((STADION_ENUM_TYPE) EnumType)
	{
	case STADION_ENUM_ANZEIGETAFEL:
		EnumFunc = GetNameFromStadionAnzeigetafelType;
		EnumLow = STADION_ANZEIGETAFEL_UNKNOWN;
		EnumHigh = NO_OF_STADION_ANZEIGETAFEL_TYPES;
		break;

	case STADION_ENUM_TRIBUENE:
		EnumFunc = GetNameFromStadionTribueneType;
		EnumLow = STADION_TRIBUENE_UNKNOWN;
		EnumHigh = NO_OF_STADION_TRIBUENE_TYPES;
		break;

	case STADION_ENUM_ZUSTAND:
		EnumFunc = GetNameFromStadionZustandType;
		EnumLow = STADION_ZUSTAND_UNKNOWN;
		EnumHigh = NO_OF_STADION_ZUSTAND_TYPES;
		break;

	case STADION_ENUM_DACH_WAERMESTRAHLER:
		EnumFunc = GetNameFromStadionDachWaermestrahlerType;
		EnumLow = STADION_DACH_WAERMESTRAHLER_UNKNOWN;
		EnumHigh = NO_OF_STADION_DACH_WAERMESTRAHLER_TYPES;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << EnumType << " (" << 
			GetNameFromStadionEnumType((STADION_ENUM_TYPE) EnumType) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	} // switch enum type
} // GetEnumDetails

bool stadion::GetBooleanTargetFieldForEnumVal (const int SpielerSplitSectionPos, const int EnumPos, int& BooleanTargetField)
{
	bool FieldFound = false;
	BooleanTargetField = STADION_SECTION_POS_UNKNOWN;

	switch ((STADION_SECTION_POS_TYPE) SpielerSplitSectionPos)
	{
	case STADION_SECTION_POS_WAERMESTRAHLER:
		switch ((STADION_DACH_WAERMESTRAHLER_TYPE) EnumPos)
		{
		case STADION_DACH_WAERMESTRAHLER_GEGEN:
			BooleanTargetField = STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_GEGEN;
			break;

		case STADION_DACH_WAERMESTRAHLER_HAUPT:
			BooleanTargetField = STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_HAUPT;
			break;

		case STADION_DACH_WAERMESTRAHLER_LINKS:
			BooleanTargetField = STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_LINKS;
			break;

		case STADION_DACH_WAERMESTRAHLER_RECHTS:
			BooleanTargetField = STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_RECHTS;
			break;

	// No Generic Split Fields but Bitmask
		case STADION_DACH_WAERMESTRAHLER_KEIN:
			break;

		default:
			std::stringstream ErrorText;
			ErrorText << "Unexpected Type " << EnumPos << " (" << 
				GetNameFromStadionDachWaermestrahlerType((STADION_DACH_WAERMESTRAHLER_TYPE) EnumPos) << ") -> " <<__FUNCTION__;
			programError (ErrorText.str());	
		} // switch spieler field bart type
		break;

	case STADION_SECTION_POS_DACH:
		switch ((STADION_DACH_WAERMESTRAHLER_TYPE) EnumPos)
		{
		case STADION_DACH_WAERMESTRAHLER_GEGEN:
			BooleanTargetField = STADION_SECTION_POS_DACH_SPLIT_GEGEN;
			break;

		case STADION_DACH_WAERMESTRAHLER_HAUPT:
			BooleanTargetField = STADION_SECTION_POS_DACH_SPLIT_HAUPT;
			break;

		case STADION_DACH_WAERMESTRAHLER_LINKS:
			BooleanTargetField = STADION_SECTION_POS_DACH_SPLIT_LINKS;
			break;

		case STADION_DACH_WAERMESTRAHLER_RECHTS:
			BooleanTargetField = STADION_SECTION_POS_DACH_SPLIT_RECHTS;
			break;
			
			// No Generic Split Fields but Bitmask
		case STADION_DACH_WAERMESTRAHLER_KEIN:
			break;

		default:
			std::stringstream ErrorText;
			ErrorText << "Unexpected Type " << EnumPos << " (" << 
				GetNameFromStadionDachWaermestrahlerType((STADION_DACH_WAERMESTRAHLER_TYPE) EnumPos) << ") -> " <<__FUNCTION__;
			programError (ErrorText.str());	
		} // switch spieler field bart type
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SpielerSplitSectionPos << " (" << 
			GetNameFromStadionSectionPosType((STADION_SECTION_POS_TYPE) SpielerSplitSectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	} // switch spieler split section pos
	
	if (BooleanTargetField != STADION_SECTION_POS_UNKNOWN)
		FieldFound = true;

	return(FieldFound);
} // GetBooleanTargetFieldForEnumVal

static bool IncludeSectionPosIntoA3Db (STADION_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoA3Db = false;

	switch (SectionPos)
	{
	case STADION_SECTION_POS_STADIONNAHME:
	case STADION_SECTION_POS_ORT:
	case STADION_SECTION_POS_ANZEIGETAFEL:
	case STADION_SECTION_POS_RASENHEIZUNG:
	case STADION_SECTION_POS_UNKNOWN_05:
	case STADION_SECTION_POS_UNKNOWN_06:
	case STADION_SECTION_POS_FLUTLICHT:
	case STADION_SECTION_POS_HEIMTRIBUENE:
	case STADION_SECTION_POS_GEGENTRIBUENE:
	case STADION_SECTION_POS_CITYLAGE:
	case STADION_SECTION_POS_IM_BESITZ_DES_VEREINS:
	case STADION_SECTION_POS_AUTOBAHNANBINDUNG:
	case STADION_SECTION_POS_FERNSEHTURM:
	case STADION_SECTION_POS_HAUPTTRIBUENE_STEH:
	case STADION_SECTION_POS_HAUPTTRIBUENE_SITZ:
	case STADION_SECTION_POS_HAUPTTRIBUENE_VIP:
	case STADION_SECTION_POS_HAUPTTRIBUENE_ZUSTAND:
	case STADION_SECTION_POS_GEGENTRIBUENE_STEH:
	case STADION_SECTION_POS_GEGENTRIBUENE_SITZ:
	case STADION_SECTION_POS_GEGENTRIBUENE_VIP:
	case STADION_SECTION_POS_GEGENTRIBUENE_ZUSTAND:
	case STADION_SECTION_POS_TRIBUENE_LINKS_STEH:
	case STADION_SECTION_POS_TRIBUENE_LINKS_SITZ:
	case STADION_SECTION_POS_TRIBUENE_LINKS_VIP:
	case STADION_SECTION_POS_TRIBUENE_LINKS_ZUSTAND:
	case STADION_SECTION_POS_TRIBUENE_RECHTS_STEH:
	case STADION_SECTION_POS_TRIBUENE_RECHTS_SITZ:
	case STADION_SECTION_POS_TRIBUENE_RECHTS_VIP:
	case STADION_SECTION_POS_TRIBUENE_RECHTS_ZUSTAND:
	case STADION_SECTION_POS_DACH:
	case STADION_SECTION_POS_LAUFBAHN:
	case STADION_SECTION_POS_WAERMESTRAHLER:
	case STADION_SECTION_POS_LUXUSKABINEN:
	case STADION_SECTION_POS_SITZKISSEN:
	case STADION_SECTION_POS_BEHEIZBARE_SITZE:
	case STADION_SECTION_POS_AUSFAHRBARES_SPIELFELD:
	case STADION_SECTION_POS_BERGE:
	case STADION_SECTION_POS_BURG:
	case STADION_SECTION_POS_SCHLOSS:		
		IncludeIntoA3Db = true;
		break;

	case STADION_SECTION_POS_REFERENCE_SECTION: // Parent
	case STADION_SECTION_POS_DACH_SPLIT_HAUPT:
	case STADION_SECTION_POS_DACH_SPLIT_GEGEN:
	case STADION_SECTION_POS_DACH_SPLIT_LINKS:
	case STADION_SECTION_POS_DACH_SPLIT_RECHTS:
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_HAUPT:
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_GEGEN:
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_LINKS:
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_RECHTS:
		IncludeIntoA3Db = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromStadionSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoA3Db);
} // IncludeSectionPosIntoA3Db

static bool IncludeSectionPosIntoXml (STADION_SECTION_POS_TYPE SectionPos)
{
	bool IncludeIntoXml = false;

	switch (SectionPos)
	{
	case STADION_SECTION_POS_STADIONNAHME:
	case STADION_SECTION_POS_ORT:
	case STADION_SECTION_POS_ANZEIGETAFEL:
	case STADION_SECTION_POS_RASENHEIZUNG:
	case STADION_SECTION_POS_UNKNOWN_05:
	case STADION_SECTION_POS_UNKNOWN_06:
	case STADION_SECTION_POS_FLUTLICHT:
	case STADION_SECTION_POS_HEIMTRIBUENE:
	case STADION_SECTION_POS_GEGENTRIBUENE:
	case STADION_SECTION_POS_CITYLAGE:
	case STADION_SECTION_POS_IM_BESITZ_DES_VEREINS:
	case STADION_SECTION_POS_AUTOBAHNANBINDUNG:
	case STADION_SECTION_POS_FERNSEHTURM:
	case STADION_SECTION_POS_HAUPTTRIBUENE_STEH:
	case STADION_SECTION_POS_HAUPTTRIBUENE_SITZ:
	case STADION_SECTION_POS_HAUPTTRIBUENE_VIP:
	case STADION_SECTION_POS_HAUPTTRIBUENE_ZUSTAND:
	case STADION_SECTION_POS_GEGENTRIBUENE_STEH:
	case STADION_SECTION_POS_GEGENTRIBUENE_SITZ:
	case STADION_SECTION_POS_GEGENTRIBUENE_VIP:
	case STADION_SECTION_POS_GEGENTRIBUENE_ZUSTAND:
	case STADION_SECTION_POS_TRIBUENE_LINKS_STEH:
	case STADION_SECTION_POS_TRIBUENE_LINKS_SITZ:
	case STADION_SECTION_POS_TRIBUENE_LINKS_VIP:
	case STADION_SECTION_POS_TRIBUENE_LINKS_ZUSTAND:
	case STADION_SECTION_POS_TRIBUENE_RECHTS_STEH:
	case STADION_SECTION_POS_TRIBUENE_RECHTS_SITZ:
	case STADION_SECTION_POS_TRIBUENE_RECHTS_VIP:
	case STADION_SECTION_POS_TRIBUENE_RECHTS_ZUSTAND:
	case STADION_SECTION_POS_LAUFBAHN:
	case STADION_SECTION_POS_LUXUSKABINEN:
	case STADION_SECTION_POS_SITZKISSEN:
	case STADION_SECTION_POS_BEHEIZBARE_SITZE:
	case STADION_SECTION_POS_AUSFAHRBARES_SPIELFELD:
	case STADION_SECTION_POS_BERGE:
	case STADION_SECTION_POS_BURG:
	case STADION_SECTION_POS_SCHLOSS:	
	case STADION_SECTION_POS_REFERENCE_SECTION:
	case STADION_SECTION_POS_DACH_SPLIT_HAUPT:
	case STADION_SECTION_POS_DACH_SPLIT_GEGEN:
	case STADION_SECTION_POS_DACH_SPLIT_LINKS:
	case STADION_SECTION_POS_DACH_SPLIT_RECHTS:
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_HAUPT:
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_GEGEN:
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_LINKS:
	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_RECHTS:
		IncludeIntoXml = true;
		break;

	case STADION_SECTION_POS_DACH:
	case STADION_SECTION_POS_WAERMESTRAHLER:
		IncludeIntoXml = false;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Field Pos: " << SectionPos << " (" << GetNameFromStadionSectionPosType(SectionPos) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	}

	return(IncludeIntoXml);
} // IncludeSectionPosIntoXml

static STADION_SECTION_POS_TYPE GetStadionSectionPosTypeFromString (const std::string& TypeString)
{
	STADION_SECTION_POS_TYPE FoundPos = STADION_SECTION_POS_UNKNOWN;

	for (int TempPos = STADION_SECTION_POS_UNKNOWN + 1; TempPos < NO_OF_STADION_SECTION_POS_TYPES; TempPos++)
	{
		if (GetNameFromStadionSectionPosType ((STADION_SECTION_POS_TYPE) TempPos).compare(TypeString) == 0)
		{
			FoundPos = (STADION_SECTION_POS_TYPE) TempPos;
			break;
		} // if found position
	} // for each position

	return(FoundPos);
} // GetStadionSectionPosTypeFromString

void AssignStadionField (std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	T_AssignSectionField<stadion>(SectionList, SectionLineCount, Line);
} // AssignStadionField

std::string GetStadionCsvHeader ()
{
	int EnumVal;
	std::stringstream CsvLine;

	CsvLine.str (std::string());
	for (EnumVal = STADION_SECTION_POS_UNKNOWN + 1; EnumVal < NO_OF_STADION_SECTION_POS_TYPES; EnumVal++)
	{
		CsvLine << GetNameFromStadionSectionPosType ((STADION_SECTION_POS_TYPE) EnumVal) << ", ";  
	}

	return (CsvLine.str());
} // GetStadionCsvHeader

static STADION_ENUM_TYPE GetStadionEnumTypeFromPosition (STADION_SECTION_POS_TYPE SectionPos)
{
	STADION_ENUM_TYPE EnumType = STADION_ENUM_UNKNOWN;
	switch ((STADION_SECTION_POS_TYPE) SectionPos)
	{
	case STADION_SECTION_POS_ANZEIGETAFEL:
		EnumType = STADION_ENUM_ANZEIGETAFEL;
		break;

	case STADION_SECTION_POS_GEGENTRIBUENE:
	case STADION_SECTION_POS_HEIMTRIBUENE:
		EnumType = STADION_ENUM_TRIBUENE;
		break;

	case STADION_SECTION_POS_GEGENTRIBUENE_ZUSTAND:
	case STADION_SECTION_POS_HAUPTTRIBUENE_ZUSTAND:
	case STADION_SECTION_POS_TRIBUENE_LINKS_ZUSTAND:
	case STADION_SECTION_POS_TRIBUENE_RECHTS_ZUSTAND:
		EnumType = STADION_ENUM_ZUSTAND;
		break;

	default:
		//do nothing
		break;
	} // switch section pos

	return (EnumType);
} // GetStadionEnumTypeFromPosition

STADION_BOOLEAN_TYPE GetStadionBooleanTypeFromPosition (STADION_SECTION_POS_TYPE SectionPos)
{
	STADION_BOOLEAN_TYPE BooleanType = STADION_BOOLEAN_UNKNOWN;
	switch (SectionPos)
	{		
	case STADION_SECTION_POS_AUSFAHRBARES_SPIELFELD:  
		BooleanType = STADION_BOOLEAN_AUSFAHRBARESSPIELFELD;
		break;

	case STADION_SECTION_POS_AUTOBAHNANBINDUNG:  
		BooleanType = STADION_BOOLEAN_AUTOBAHNANBINDUNG;
		break;

	case STADION_SECTION_POS_BEHEIZBARE_SITZE:  
		BooleanType = STADION_BOOLEAN_BEHEIZBARESITZE;
		break;

	case STADION_SECTION_POS_BERGE:  
		BooleanType = STADION_BOOLEAN_BERGE;
		break;

	case STADION_SECTION_POS_BURG:  
		BooleanType = STADION_BOOLEAN_BURG;
		break;

	case STADION_SECTION_POS_CITYLAGE:  
		BooleanType = STADION_BOOLEAN_CITYLAGE;
		break;

	case STADION_SECTION_POS_DACH_SPLIT_GEGEN:  
		BooleanType = STADION_BOOLEAN_DACH_GEGEN;
		break;

	case STADION_SECTION_POS_DACH_SPLIT_HAUPT:  
		BooleanType = STADION_BOOLEAN_DACH_HAUPT;
		break;

	case STADION_SECTION_POS_DACH_SPLIT_LINKS:  
		BooleanType = STADION_BOOLEAN_DACH_LINKS;
		break;

	case STADION_SECTION_POS_DACH_SPLIT_RECHTS:  
		BooleanType = STADION_BOOLEAN_DACH_RECHTS;
		break;

	case STADION_SECTION_POS_FERNSEHTURM:  
		BooleanType = STADION_BOOLEAN_FERNSEHTURM;
		break;

	case STADION_SECTION_POS_FLUTLICHT:  
		BooleanType = STADION_BOOLEAN_FLUTLICHT;
		break;

	case STADION_SECTION_POS_IM_BESITZ_DES_VEREINS:  
		BooleanType = STADION_BOOLEAN_IMBESITZDESVEREINS;
		break;

	case STADION_SECTION_POS_LAUFBAHN:  
		BooleanType = STADION_BOOLEAN_LAUFBAHN;
		break;

	case STADION_SECTION_POS_LUXUSKABINEN:  
		BooleanType = STADION_BOOLEAN_LUXUSKABINEN;
		break;

	case STADION_SECTION_POS_RASENHEIZUNG:  
		BooleanType = STADION_BOOLEAN_RASENHEIZUNG;
		break;

	case STADION_SECTION_POS_SCHLOSS:  
		BooleanType = STADION_BOOLEAN_SCHLOSS;
		break;

	case STADION_SECTION_POS_SITZKISSEN:  
		BooleanType = STADION_BOOLEAN_SITZKISSEN;
		break;

	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_GEGEN:  
		BooleanType = STADION_BOOLEAN_WAERMESTRAHLER_GEGEN;
		break;

	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_HAUPT:  
		BooleanType = STADION_BOOLEAN_WAERMESTRAHLER_HAUPT;
		break;

	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_LINKS:  
		BooleanType = STADION_BOOLEAN_WAERMESTRAHLER_LINKS;
		break;

	case STADION_SECTION_POS_WAERMESTRAHLER_SPLIT_RECHTS: 
		BooleanType = STADION_BOOLEAN_WAERMESTRAHLER_RECHTS;
		break;

	default:
		//do nothing
		break;
	} // switch section pos

	return (BooleanType);
} // GetStadionBooleanTypeFromPosition

void GetStadionAllowedValues (std::vector<FIELD_VALUE_STRUCT>& AllowedValues)
{
	for (int SectionPos = STADION_SECTION_POS_UNKNOWN + 1; SectionPos < NO_OF_STADION_SECTION_POS_TYPES; SectionPos++)
	{
		ENUM_FUNC EnumFunc = nullptr;
		int EnumLow = 0;
		int EnumHigh = 0;
		STADION_ENUM_TYPE StadionEnum = STADION_ENUM_UNKNOWN;
		STADION_BOOLEAN_TYPE StadionBoolean = STADION_BOOLEAN_UNKNOWN;
		bool DetailsFound = false;

		if ((StadionEnum = GetStadionEnumTypeFromPosition ((STADION_SECTION_POS_TYPE) SectionPos)) != STADION_ENUM_UNKNOWN)
		{
			// Ignore this for special case handled below
			GetEnumDetails(SectionPos, StadionEnum, EnumFunc, EnumLow, EnumHigh);
			DetailsFound = true;
		} // if enum field
		else if ((StadionBoolean = GetStadionBooleanTypeFromPosition ((STADION_SECTION_POS_TYPE) SectionPos)) != STADION_BOOLEAN_UNKNOWN)
		{
			GetBooleanEnumDetails (EnumFunc, EnumLow, EnumHigh);
			DetailsFound = true;
		} // if boolean field

		// Add Values
		if (DetailsFound)
		{
			// Add the Value Entry to the List
			AddFieldValueEntryToList (AllowedValues, GetNameFromStadionSectionPosType((STADION_SECTION_POS_TYPE) SectionPos));

			// Add allowed Values
			AddFieldValuesForLastEntry (AllowedValues, EnumLow, EnumHigh, EnumFunc);
		} // if got a function
	} // for each section pos
} // GetStadionAllowedValues
