#include "a3_db_file_lib.h"

#include "error_handling.h"
#include <sstream>
#include <iostream>

std::string GetNameFromA3FileNameType (A3_FILE_NAME_TYPE FileNameType)
{
	switch (FileNameType)
	{
	case A3_FILE_NAME_AVEREINE:
		return ("AVereine.sav");
	case A3_FILE_NAME_BONUS1:
		return ("Bonus1.sav");
	case A3_FILE_NAME_CLEAGUE:
		return ("CLeague.sav");
	case A3_FILE_NAME_EMWM:
		return ("EMWM.sav");
	case A3_FILE_NAME_EXSPIEL:
		return ("ExSpiel.sav");
	case A3_FILE_NAME_FANGESA:
		return ("Fangesa.sav");
	case A3_FILE_NAME_FANWAVES:
		return ("Fanwaves.sav");
	case A3_FILE_NAME_INTERNAT:
		return ("Internat.sav");
	case A3_FILE_NAME_ISCHIRIS:
		return ("ISchiris.sav");
	case A3_FILE_NAME_JUGEND1:
		return ("Jugend1.sav");
	case A3_FILE_NAME_JUGEND10:
		return ("Jugend10.sav");
	case A3_FILE_NAME_JUGEND11:
		return ("Jugend11.sav");
	case A3_FILE_NAME_JUGEND12:
		return ("Jugend12.sav");
	case A3_FILE_NAME_JUGEND13:
		return ("Jugend13.sav");
	case A3_FILE_NAME_JUGEND14:
		return ("Jugend14.sav");
	case A3_FILE_NAME_JUGEND15:
		return ("Jugend15.sav");
	case A3_FILE_NAME_JUGEND16:
		return ("Jugend16.sav");
	case A3_FILE_NAME_JUGEND17:
		return ("Jugend17.sav");
	case A3_FILE_NAME_JUGEND18:
		return ("Jugend18.sav");
	case A3_FILE_NAME_JUGEND2:
		return ("Jugend2.sav");
	case A3_FILE_NAME_JUGEND3:
		return ("Jugend3.sav");
	case A3_FILE_NAME_JUGEND4:
		return ("Jugend4.sav");
	case A3_FILE_NAME_JUGEND5:
		return ("Jugend5.sav");
	case A3_FILE_NAME_JUGEND6:
		return ("Jugend6.sav");
	case A3_FILE_NAME_JUGEND7:
		return ("Jugend7.sav");
	case A3_FILE_NAME_JUGEND8:
		return ("Jugend8.sav");
	case A3_FILE_NAME_JUGEND9:
		return ("Jugend9.sav");
	case A3_FILE_NAME_KLEINIG:
		return ("Kleinig.sav");
	case A3_FILE_NAME_LAENDER:
		return ("Laender.sav");
	case A3_FILE_NAME_LANDDEUT:
		return ("LandDeut.sav");
	case A3_FILE_NAME_LANDENGL:
		return ("LandEngl.sav");
	case A3_FILE_NAME_LANDFRAN:
		return ("LandFran.sav");
	case A3_FILE_NAME_LANDHOLL:
		return ("LandHoll.sav");
	case A3_FILE_NAME_LANDITAL:
		return ("LandItal.sav");
	case A3_FILE_NAME_LANDOEST:
		return ("LandOest.sav");
	case A3_FILE_NAME_LANDPORT:
		return ("LandPort.sav");
	case A3_FILE_NAME_LANDSCHO:
		return ("LandScho.sav");
	case A3_FILE_NAME_LANDSCHW:
		return ("LandSchw.sav");
	case A3_FILE_NAME_LANDSPAN:
		return ("LandSpan.sav");
	case A3_FILE_NAME_LANDTUER:
		return ("LandTuer.sav");
	case A3_FILE_NAME_LIGA1BON:
		return ("liga1bon.sav");
	case A3_FILE_NAME_LIGA1DEU:
		return ("Liga1Deu.sav");
	case A3_FILE_NAME_LIGA1ENG:
		return ("Liga1Eng.sav");
	case A3_FILE_NAME_LIGA1FRA:
		return ("Liga1Fra.sav");
	case A3_FILE_NAME_LIGA1HOL:
		return ("liga1hol.sav");
	case A3_FILE_NAME_LIGA1ITA:
		return ("Liga1Ita.sav");
	case A3_FILE_NAME_LIGA1OES:
		return ("liga1oes.sav");
	case A3_FILE_NAME_LIGA1POR:
		return ("liga1por.sav");
	case A3_FILE_NAME_LIGA1SCH:
		return ("liga1sch.sav");
	case A3_FILE_NAME_LIGA1SPA:
		return ("Liga1Spa.sav");
	case A3_FILE_NAME_LIGA1SWZ:
		return ("liga1swz.sav");
	case A3_FILE_NAME_LIGA1TUE:
		return ("liga1tue.sav");
	case A3_FILE_NAME_LIGA2DEU:
		return ("Liga2Deu.sav");
	case A3_FILE_NAME_LIGA2ENG:
		return ("Liga2Eng.sav");
	case A3_FILE_NAME_LIGA2FRA:
		return ("Liga2Fra.sav");
	case A3_FILE_NAME_LIGA2ITA:
		return ("liga2ita.sav");
	case A3_FILE_NAME_LIGA2SPA:
		return ("liga2spa.sav");
	case A3_FILE_NAME_LIGA3ENG:
		return ("Liga3Eng.sav");
	case A3_FILE_NAME_LIGA3ITA:
		return ("Liga3Ita.sav");
	case A3_FILE_NAME_LIGA4ENG:
		return ("liga4eng.sav");
	case A3_FILE_NAME_LIGARLNO:
		return ("LigaRLNo.sav");
	case A3_FILE_NAME_LIGARLOS:
		return ("LigaRLOs.sav");
	case A3_FILE_NAME_LIGARLSU:
		return ("LigaRLSu.sav");
	case A3_FILE_NAME_LIGARLSW:
		return ("LigaRLSW.sav");
	case A3_FILE_NAME_SONSPIEL:
		return ("SonSpiel.sav");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected FileNameType: " << FileNameType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return("");
	} // switch file name types
} // GetNameFromFileNameType

std::string GetNameFromA3FileGroupType (A3_FILE_GROUP_TYPE FileGroupType)
{
	switch (FileGroupType)
	{
// ERIC - std::cout
// Allow Unknown at least for know since not all coded yet
case A3_FILE_NAME_UNKNOWN:
	return("UNKNOWN");

	case A3_FILE_GROUP_LANDXXX:
		return("LANDXXX");

	case A3_FILE_GROUP_IVEREINE:
		return("IVEREINE");

	case A3_FILE_GROUP_JUGENDXXX:
		return("JUGENDXXX");

	case A3_FILE_GROUP_INTERNAT:
		return("INTERNAT");

	case A3_FILE_GROUP_SONSPIELER:
		return("SONSPIELER");

	case A3_FILE_GROUP_CLEAGUE:
		return("CLEAGUE");

	case A3_FILE_GROUP_EMWM:
		return("EMWM");

	case A3_FILE_GROUP_LIGAYXXX:
		return("LIGAYXXX");

	case A3_FILE_GROUP_EXSPIEL:
		return("EXSPIEL");

	case A3_FILE_GROUP_LAENDER:
		return("LAENDER");

	case A3_FILE_GROUP_ISCHIRI:
		return("ISCHIRI");

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected FileGroupType: " << FileGroupType << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		return("");
	}
} // GetNameFromA3FileNameType

static A3_FILE_GROUP_TYPE GetA3FileGroupFromA3FileNameType (A3_FILE_NAME_TYPE FileNameType)
{
	A3_FILE_GROUP_TYPE FileGroup = A3_FILE_GROUP_UNKNOWN;
	
	switch (FileNameType)
	{
	case A3_FILE_NAME_LANDDEUT:
	case A3_FILE_NAME_LANDENGL:
	case A3_FILE_NAME_LANDFRAN:
	case A3_FILE_NAME_LANDHOLL:
	case A3_FILE_NAME_LANDITAL:
	case A3_FILE_NAME_LANDOEST:
	case A3_FILE_NAME_LANDPORT:
	case A3_FILE_NAME_LANDSCHO:
	case A3_FILE_NAME_LANDSCHW:
	case A3_FILE_NAME_LANDSPAN:
	case A3_FILE_NAME_LANDTUER:
		FileGroup = A3_FILE_GROUP_LANDXXX;
		break;

	case A3_FILE_NAME_INTERNAT:
		FileGroup = A3_FILE_GROUP_INTERNAT;
		break;

	case A3_FILE_NAME_AVEREINE:
		FileGroup = A3_FILE_GROUP_IVEREINE;
		break;

	case A3_FILE_NAME_JUGEND1:
	case A3_FILE_NAME_JUGEND10:
	case A3_FILE_NAME_JUGEND11:
	case A3_FILE_NAME_JUGEND12:
	case A3_FILE_NAME_JUGEND13:
	case A3_FILE_NAME_JUGEND14:
	case A3_FILE_NAME_JUGEND15:
	case A3_FILE_NAME_JUGEND16:
	case A3_FILE_NAME_JUGEND17:
	case A3_FILE_NAME_JUGEND18:
	case A3_FILE_NAME_JUGEND2:
	case A3_FILE_NAME_JUGEND3:
	case A3_FILE_NAME_JUGEND4:
	case A3_FILE_NAME_JUGEND5:
	case A3_FILE_NAME_JUGEND6:
	case A3_FILE_NAME_JUGEND7:
	case A3_FILE_NAME_JUGEND8:
	case A3_FILE_NAME_JUGEND9:
		FileGroup = A3_FILE_GROUP_JUGENDXXX;
		break;

	case A3_FILE_NAME_SONSPIEL:
		FileGroup = A3_FILE_GROUP_SONSPIELER;
		break;

	case A3_FILE_NAME_CLEAGUE:
		FileGroup = A3_FILE_GROUP_CLEAGUE;
		break;

	case A3_FILE_NAME_EMWM:
		FileGroup = A3_FILE_GROUP_EMWM;
		break;

	case A3_FILE_NAME_EXSPIEL:
		FileGroup = A3_FILE_GROUP_EXSPIEL;
		break;

	case A3_FILE_NAME_LAENDER:
		FileGroup = A3_FILE_GROUP_LAENDER;
		break;

	case A3_FILE_NAME_ISCHIRIS:
		FileGroup = A3_FILE_GROUP_ISCHIRI;
		break;

	case A3_FILE_NAME_LIGA1DEU:
	case A3_FILE_NAME_LIGA1ENG:
	case A3_FILE_NAME_LIGA1FRA:
	case A3_FILE_NAME_LIGA1HOL:
	case A3_FILE_NAME_LIGA1ITA:
	case A3_FILE_NAME_LIGA1OES:
	case A3_FILE_NAME_LIGA1POR:
	case A3_FILE_NAME_LIGA1SCH:
	case A3_FILE_NAME_LIGA1SPA:
	case A3_FILE_NAME_LIGA1SWZ:
	case A3_FILE_NAME_LIGA1TUE:
	case A3_FILE_NAME_LIGA2DEU:
	case A3_FILE_NAME_LIGA2ENG:
	case A3_FILE_NAME_LIGA2FRA:
	case A3_FILE_NAME_LIGA2ITA:
	case A3_FILE_NAME_LIGA2SPA:
	case A3_FILE_NAME_LIGA3ENG:
	case A3_FILE_NAME_LIGA3ITA:
	case A3_FILE_NAME_LIGA4ENG:
	case A3_FILE_NAME_LIGARLNO:
	case A3_FILE_NAME_LIGARLOS:
	case A3_FILE_NAME_LIGARLSU:
	case A3_FILE_NAME_LIGARLSW:
	case A3_FILE_NAME_LIGA1BON:
		FileGroup = A3_FILE_GROUP_LIGAYXXX;
		break;

	case A3_FILE_NAME_BONUS1:
	case A3_FILE_NAME_FANGESA:
	case A3_FILE_NAME_FANWAVES:
	case A3_FILE_NAME_KLEINIG:
		// Unknown Code, to break later on but keep the list for easy sorting while finishing this function
		FileGroup = A3_FILE_GROUP_UNKNOWN;
		break;
	
	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected FileNameType: " << FileNameType << " (" << GetNameFromA3FileNameType(FileNameType) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		break;
	} // switch file name types

	return(FileGroup);
} // GetFileGroupFromFileNameType

A3_FILE_NAME_TYPE GetLandDefiningFileNameType (A3_FILE_NAME_TYPE FileNameType)
{
	A3_FILE_NAME_TYPE LandDefiningFileType = A3_FILE_NAME_UNKNOWN;

	switch (FileNameType)
	{
	// All which Define themselves or no definition
	case A3_FILE_NAME_LAENDER:
	case A3_FILE_NAME_AVEREINE:
	case A3_FILE_NAME_CLEAGUE:
	case A3_FILE_NAME_FANGESA:
	case A3_FILE_NAME_FANWAVES:
	case A3_FILE_NAME_INTERNAT:
	case A3_FILE_NAME_ISCHIRIS:
	case A3_FILE_NAME_JUGEND1:
	case A3_FILE_NAME_JUGEND10:
	case A3_FILE_NAME_JUGEND11:
	case A3_FILE_NAME_JUGEND12:
	case A3_FILE_NAME_JUGEND13:
	case A3_FILE_NAME_JUGEND14:
	case A3_FILE_NAME_JUGEND15:
	case A3_FILE_NAME_JUGEND16:
	case A3_FILE_NAME_JUGEND17:
	case A3_FILE_NAME_JUGEND18:
	case A3_FILE_NAME_JUGEND2:
	case A3_FILE_NAME_JUGEND3:
	case A3_FILE_NAME_JUGEND4:
	case A3_FILE_NAME_JUGEND5:
	case A3_FILE_NAME_JUGEND6:
	case A3_FILE_NAME_JUGEND7:
	case A3_FILE_NAME_JUGEND8:
	case A3_FILE_NAME_JUGEND9:
	case A3_FILE_NAME_KLEINIG:
	case A3_FILE_NAME_SONSPIEL:
	case A3_FILE_NAME_EXSPIEL:
	case A3_FILE_NAME_EMWM:
		LandDefiningFileType = FileNameType;
		break;

	case A3_FILE_NAME_LANDDEUT:
	case A3_FILE_NAME_LIGA1DEU:
	case A3_FILE_NAME_LIGA2DEU:
	case A3_FILE_NAME_LIGARLNO:
	case A3_FILE_NAME_LIGARLOS:
	case A3_FILE_NAME_LIGARLSU:
	case A3_FILE_NAME_LIGARLSW:
		LandDefiningFileType = A3_FILE_NAME_LANDDEUT;
		break;
		
	case A3_FILE_NAME_LANDENGL:
	case A3_FILE_NAME_LIGA1ENG:
	case A3_FILE_NAME_LIGA2ENG:
	case A3_FILE_NAME_LIGA3ENG:
	case A3_FILE_NAME_LIGA4ENG:
		LandDefiningFileType = A3_FILE_NAME_LANDENGL;
		break;

	case A3_FILE_NAME_LANDSPAN:
	case A3_FILE_NAME_LIGA1SPA:
	case A3_FILE_NAME_LIGA2SPA:
		LandDefiningFileType = A3_FILE_NAME_LANDSPAN;
		break;

	case A3_FILE_NAME_LANDITAL:
	case A3_FILE_NAME_LIGA1ITA:
	case A3_FILE_NAME_LIGA2ITA:
	case A3_FILE_NAME_LIGA3ITA:
		LandDefiningFileType = A3_FILE_NAME_LANDITAL;
		break;

	case A3_FILE_NAME_BONUS1:
	case A3_FILE_NAME_LIGA1BON:
		LandDefiningFileType = A3_FILE_NAME_BONUS1;
		break;

	case A3_FILE_NAME_LANDFRAN:
	case A3_FILE_NAME_LIGA1FRA:
	case A3_FILE_NAME_LIGA2FRA:
		LandDefiningFileType = A3_FILE_NAME_LANDFRAN;
		break;

	case A3_FILE_NAME_LANDHOLL:
	case A3_FILE_NAME_LIGA1HOL:
		LandDefiningFileType = A3_FILE_NAME_LANDHOLL;
		break;

	case A3_FILE_NAME_LANDOEST:
	case A3_FILE_NAME_LIGA1OES:
		LandDefiningFileType = A3_FILE_NAME_LANDOEST;
		break;

	case A3_FILE_NAME_LANDPORT:
	case A3_FILE_NAME_LIGA1POR:
		LandDefiningFileType = A3_FILE_NAME_LANDPORT;
		break;

	case A3_FILE_NAME_LANDSCHO:
	case A3_FILE_NAME_LIGA1SCH:
		LandDefiningFileType = A3_FILE_NAME_LANDSCHO;
		break;

	case A3_FILE_NAME_LANDSCHW:
	case A3_FILE_NAME_LIGA1SWZ:
		LandDefiningFileType = A3_FILE_NAME_LANDSCHW;
		break;

	case A3_FILE_NAME_LANDTUER:
	case A3_FILE_NAME_LIGA1TUE:
		LandDefiningFileType = A3_FILE_NAME_LANDTUER;
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected FileNameType: " << FileNameType << " (" << GetNameFromA3FileNameType(FileNameType) << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());	
		break;
	} // switch FileNameType

	return (LandDefiningFileType);
} // GetLandDefiningFileNameType

A3_FILE_NAME_TYPE GetA3FileNameTypeFromFileName (std::string FileName)
{
	A3_FILE_NAME_TYPE FileNameType = A3_FILE_NAME_UNKNOWN;

	for (int i = A3_FILE_NAME_UNKNOWN + 1; i < NO_OF_A3_FILE_NAME_TYPES; i++)
	{
		if(GetNameFromA3FileNameType((A3_FILE_NAME_TYPE) i).compare(FileName) == 0)
		{
			FileNameType = (A3_FILE_NAME_TYPE) i;
			break;
		}
	}
	
	return(FileNameType);
} // GetFileNameTypeFromFileName

A3_FILE_GROUP_TYPE GetA3FileGroupFromFileName (std::string FileName)
{
	return (GetA3FileGroupFromA3FileNameType(GetA3FileNameTypeFromFileName(FileName)));
} // GetFileGroupFromFileName

void GetListOfA3DbFiles (std::vector<std::string>& FileNameList)
{
	for (int i = A3_FILE_NAME_UNKNOWN + 1; i < NO_OF_A3_FILE_NAME_TYPES; i++)
		FileNameList.push_back(GetNameFromA3FileNameType((A3_FILE_NAME_TYPE) i));
} // GetListOfA3Files
