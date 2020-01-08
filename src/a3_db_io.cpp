#include "a3_db_io.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <iomanip> 

#include "windows.h"
#include "a3_ui_text.h"
#include "error_handling.h"
#include "a3_db_converter.h"
#include "charset_text_convert.h"
#include "utf8.h"
#include "os_lib.h"
#include "a3_db_file_lib.h"

#include "sub_sections.h"

#define FILE_OPENING_NUMBER	"17373592"



static void InitializeLocalData (std::vector<std::shared_ptr<section>> SectionList[NO_OF_SECTION_TYPES],
								size_t SectionLastCount[NO_OF_SECTION_TYPES], size_t InternatSavLastSectionCount[NO_OF_SECTION_TYPES],
								FILE_LAND_ID_STRUCT FileLandIds[NO_OF_A3_FILE_NAME_TYPES])
{
	// Initialise our Land Ids
	InitializeLandIds (FileLandIds);

	// Clear All sections, even persistent ones
	ResetSectionList (SectionList, SectionLastCount, false, InternatSavLastSectionCount);
} // InitializeLocalData

void importA3DbFiles ()
{
	// Declare the List of Sections
	std::vector<std::shared_ptr<section>> SectionList[NO_OF_SECTION_TYPES];
	size_t SectionLastCount[NO_OF_SECTION_TYPES];
	// HACK - ERIC - Ideally we find a better solution, this is too specific, but needed as we need to update this foe Internat.sav files
	size_t InternatSavLastSectionCount[NO_OF_SECTION_TYPES];
	FILE_LAND_ID_STRUCT FileLandIds[NO_OF_A3_FILE_NAME_TYPES];

	// Initialize local data
	InitializeLocalData (SectionList, SectionLastCount, InternatSavLastSectionCount, FileLandIds);

	// Initialize File List
	std::vector<std::string> FileList;
	GetListOfA3DbFiles(FileList);

	//for each file to read (a static list) (a3_db_io.cpp)
	for (std::vector<std::string>::const_iterator FileNameIterator = FileList.begin ();
		FileNameIterator != FileList.end();
		FileNameIterator++)
	{
#if 1 // ERIC - Ignore unhandled files
if (((*FileNameIterator).compare("Bonus1.sav") == 0) ||
	((*FileNameIterator).compare("liga1bon.sav") == 0) ||
	((*FileNameIterator).compare("Fangesa.sav") == 0) ||
	((*FileNameIterator).compare("Fanwaves.sav") == 0) ||
	((*FileNameIterator).compare("Kleinig.sav") == 0) ||
	((*FileNameIterator).compare("Quiz.sav") == 0) ||
	// Ignore Liga 3, doesn't exist in the game, not correct
	((*FileNameIterator).compare("Liga3Ita.sav") == 0))
{
	showTextMsg(std::string("IGNORIERE NOCH NICHT INTEGRIERTE DATEI - ") + *FileNameIterator);
	continue;
}
#endif
				

		showTextMsg(std::string("Importiere Datei: ") + *FileNameIterator);

		// initialize vector list to 0 (a3_db_io.cpp)
		ResetSectionList (SectionList, SectionLastCount, true, InternatSavLastSectionCount);

		// import this file

		if (importFileFromA3Db (*FileNameIterator, SectionList, InternatSavLastSectionCount))
		{
			// Post processing of imported data
			PostSavImportProcessing (*FileNameIterator, SectionList, SectionLastCount, FileLandIds);

			// Write File Data to CSV

	/*
	NEED TO PASS IN THE RANGES AS TO WHICH OBJECTS WE READ, OR WHICH SECTIONS
		  - Currently NATION is persistent, so the Writing Code writes it for every FILE because it always exist, only can have 1 version
			- Maybe
	*/
			WriteA3DbExternalFile (*FileNameIterator, SectionList, SectionLastCount);

			// Update the last section count after we used it to write the fields
			UpdateLastSectionCount (SectionList, SectionLastCount);
		}
		else
		{
			showTextMsg(std::string("  Ignoriere nicht Existierende Datei: ") + *FileNameIterator);
		}
	} // For each File in List
} // importA3DbFiles

static bool importFileFromA3Db (const std::string& FileName, std::vector<std::shared_ptr<section>> SectionList[NO_OF_SECTION_TYPES],
								size_t InternatSavLastSectionCount[NO_OF_SECTION_TYPES])
{
	bool FileRead = false;

	// Read the File
	std::ifstream FileHandle (FileName.c_str(), std::ifstream::in);

	if (FileHandle.fail())
	{
		FileRead = false;
	}
	else
	{
		FileRead = true;
		std::string	Line;
		std::string LastLine = "";

		SECTION_TYPE	OpenSection = SECTION_TYPE_UNKNOWN;
		std::vector<SECTION_TYPE> SectionStack;
		int				SectionLineCount = 0;
		bool			SectionEndReached = false; // Knowing when we reached the end of a section without it being openly closed

		// ASSUMPTION: Max 1 Hidden Section per Section
		// Initialize Section Vector to always have on in there
		SectionStack.push_back(SECTION_TYPE_UNKNOWN);
		SECTION_TYPE ParentSection = SectionStack.back();
		bool IgnoreNextDataLine = false;

		while (std::getline (FileHandle, Line))
		{
			SectionLineCount++;

	#if DEBUG_ENABLED // ERIC
	std::cout << GetNameFromSectionType(OpenSection) << ":::" << SectionLineCount << ":::" << "\"" << Line << "\"" << std::endl;
	#endif

			// Convert any invalid utf-8 strings
			SECTION_TYPE DataSection;
			SECTION_TYPE A3Section;
			std::string::iterator end_it = utf8::find_invalid(Line.begin(), Line.end());
			if (end_it != Line.end()) 
			{
				ConvertStringToUtf8Unicode (Line);
			} // if not valid utf-8

			if (StringIsSectionStart (Line))
			{
				if(LastLine.compare(Line) != 0)
				{
					SectionEndReached = false;
					OpenSection = GetSectionTypeFromString (Line);
					ParentSection = SectionStack.back();
					SectionStack.push_back(OpenSection);

					DataSection = OpenSection;
					A3Section = OpenSection;

					// Create Object for a visible data section
					if (SectionContainsData(OpenSection))
						CreateObjectForSection (SectionList, OpenSection, SectionLineCount, OpenSection, ParentSection);

					// Check if we need to ignore the next line, e.g. being a Count
					// SEEMS a bit lick a hack in the moment, but might get away with it for now
					IgnoreNextDataLine = IgnoreSavLine (OpenSection, Line, SectionLineCount);
					
					// Finally Reset the Line Count as Starting from 0 (i.e. 1 once the next line is read)
					SectionLineCount = 0;
				} // if not opened same section twice
				else
				{
					// reduce previous incremented line count as ignoring the duplicate opening line
					SectionLineCount--;
				}
			} // Section start	
			else if (StringIsSectionEnd (Line))
			{
				if(LastLine.compare(Line) != 0)
				{
					SECTION_TYPE ClosedSection = SectionStack.back();

					SectionEndReached = true;
					OpenSection = SECTION_TYPE_UNKNOWN;
					SectionStack.pop_back();
					ParentSection = SectionStack.back();
					SectionLineCount = 0;

					DataSection = SECTION_TYPE_UNKNOWN;
					A3Section = SECTION_TYPE_UNKNOWN;	
					
					// Do Open Section Knockons
					CloseSectionKnockOns (ClosedSection, FileName, SectionList, InternatSavLastSectionCount);
				} // if not closed same section twice
				else
				{
					// reduce previous incremented line count as ignoring the duplicate opening line
					SectionLineCount--;		
				}
			} // Not section end
			else
			{
				if (!IgnoreNextDataLine)
				{
					// By Default our section is the open section
					DataSection = OpenSection;
					A3Section = OpenSection;

		#if DEBUG_ENABLED // ERIC
		std::cout << "  " << GetNameFromSectionType(OpenSection) << "::" << "(" << SectionLineCount << ") - " << Line << std::endl; 
		#endif

					if (!Line.empty())
					{				
						if ((OpenSection != SECTION_TYPE_UNKNOWN) && (!SectionEndReached))
						{
							if(!SectionContainsData(OpenSection))
							{
								DataSection = GetHiddenSection(OpenSection, SectionList);
								A3Section = OpenSection;
							} // Open section has no data
						} // If we are in the last open section
						else
						{
	#if 1 // IF ACTUALLY KEEPING SPIELS
							// If section is open but we have reached it's end we need to fin the hidden data from the open section
							// This part is to Accomodate the LIGA section, maybe a bit of a hack, or maybe the code just needs a bit cleaning up
							if ((OpenSection != SECTION_TYPE_UNKNOWN) && (SectionEndReached))
							{
								DataSection = GetHiddenSection(OpenSection, SectionList);
								A3Section = GetDataSectionFromHiddenSection(DataSection);
	// DO WE NEED TO SET A PARENT SECTION HERE OR WHENEVER WE ENTER A HIDDEN SECTION???
							}
	#endif 
							// If we have a parent section, otherwise something is wrong if no open section and no parent section
							else if(ParentSection != SECTION_TYPE_UNKNOWN)
							{
								DataSection = GetHiddenSection(ParentSection, SectionList);
								A3Section = GetDataSectionFromHiddenSection(DataSection);
							}


	/* THINK OF THESE EXAMPLES, HOW TO DETERMINE WHAT TO PASS AS A3?, MA
		CreateObjectForSection(STADION, STADION, LAND)
		CreateObjectForSection(VEREIN_HIDDEN, VEREIN, VEREIN)
	CURRENTLY
		CreateObjectForSection(SPIELER_HIDDEN, EXSPIELER, EXSPIELER)
	WANT
		CreateObjectForSection(SPIELER_HIDDEN, SPIELER, EXSPIELER)
	*/

						} // previously closed a section without opening
					} // if line has content

					if ((DataSection != SECTION_TYPE_UNKNOWN) && 
						(SectionContainsData(DataSection))) 
					{
	//if(DataSection == SECTION_TYPE_EUROSIEGER)
	//	continue;

		#if DEBUG_ENABLED
						std::cout << "  " << GetNameFromSectionType(DataSection) << ":::" << "SetField: (" << SectionLineCount << ") " << Line << std::endl;
		#endif









	#if 0
	NEED TO GIVE IT A PROPER PARENT FOR HIDDEN SECTIONS
		CASE1: VEREIN_HIDDEN - DataSection is Verein, No Open Section 
		CASE2: SPIELPLAN_VEREIN - DataSection is SPIELPLAN_VEREIN, Have Open Section, Parent is UNKNOWN
		MAYBE NEED TO HAVE A HIDDEN PARENT SECTION????
		HOW WILL IT BE APPLIED TO BOTH CASES???
	#endif 

		/*
		MAYBE HAVE AN OPEN SECTION AND CLOSE SECTION MACRO
		- OPEN SECTION WHEN HAVING HIDDEN SECTION???
		- THEN HAVE PROPER PARENT AS IN OPEN SECTION???
		*/
	#if 0
						if((SectionLineCount == 1) && (!SectionIsVisible(DataSection)))
								CreateObjectForSection(DataSection, SectionLineCount, A3Section, ParentSection);
	#endif


	// SUPER HACK HERE, 
	// Referencing Specific Section Type
	// This Function needs refactoring to make it simpler, all sections (Hidden or not) should be properly opened and closed
	//
	#if 1
						if((SectionLineCount == 1) && (!SectionIsVisible(DataSection)))
						{
							if (OpenSection == SECTION_TYPE_LIGA)
								CreateObjectForSection (SectionList, DataSection, SectionLineCount, A3Section, OpenSection);
							else
								CreateObjectForSection (SectionList, DataSection, SectionLineCount, A3Section, ParentSection);
						}
	#endif












	#if DEBUG_ENABLED
					std::cout << "    DataSection:A3Section:ParentSection => " << GetNameFromSectionType(DataSection) << "::" << 
						GetNameFromSectionType(A3Section) << "::" << GetNameFromSectionType(ParentSection) << std::endl;
	#endif

						// Set field for Section, Can be hidden section and must have data
						SetFieldForSection (SectionList, DataSection, Line, SectionLineCount);

						// If after setting the LineCount reached the Max Allowed fields, start from 0 to account for special
						// sections like AJugend which write everything together
						if (SectionLineCount >= GetNoOfFieldsInA3Section (DataSection))
						{
							SectionLineCount = 0;
							SectionEndReached = true;
	#if DEBUG_ENABLED
							std::cout << "    Section End Reached of " << GetNameFromSectionType(DataSection) << std::endl;
	#endif
						}

					} // If have a section for the data
				} // if need to ignore the line
				else
				{
					// if we ignore the line reset it
					IgnoreNextDataLine = false;

					// Also reset the Linecount as we start again
					SectionLineCount = 0;
				} // if ignoring the line
			} // Data Line

			LastLine = Line;
		} // while more lines in file
	
		FileHandle.close();
	}

	return (FileRead);
} // importFileFromA3Db

static bool IgnoreSavLine (SECTION_TYPE DataSection, const std::string& Line, int LineNr)
{
	bool IgnoreLine = false;

	switch (DataSection)
	{
	case SECTION_TYPE_EUROSIEGER:
	case SECTION_TYPE_SONSPIELER:
	case SECTION_TYPE_EXSPIEL:
	case SECTION_TYPE_CLEAGUE:
	case SECTION_TYPE_EMGRP:
	case SECTION_TYPE_WMGRP:
		// Ignore Count Lines
		IgnoreLine = true;
		break;

	default:
		break;
	} // switch section type

	return(IgnoreLine);
} // IgnoreSavLine

static void AssignParent (std::vector<std::shared_ptr<section>> SectionList[NO_OF_SECTION_TYPES],
							SECTION_TYPE DataSectionType,
							SECTION_TYPE ParentSectionType, std::vector<std::shared_ptr<section>> ParentSectionList, 
							SECTION_TYPE ChildSectionType, std::vector<std::shared_ptr<section>> ChildSectionList)
{
#if DEBUG_ENABLED
std::cout << __FUNCTION__ << " PARENT(Data?, ptr)::CHILD(Data?, ptr) ==>> " << GetNameFromSectionType(ParentSectionType) << "(";
if(ParentSectionType != SECTION_TYPE_UNKNOWN)
	std::cout << SectionContainsData(ParentSectionType) << ", ";
if(ParentSectionList.size() > 0)
	std::cout << ParentSectionList.back();
std::cout << "):::" << GetNameFromSectionType(ChildSectionType) << "(";
if (ChildSectionType != SECTION_TYPE_UNKNOWN)
	std::cout << SectionContainsData(ChildSectionType) << ", ";
if (ChildSectionList.size() > 0)
	std::cout << ChildSectionList.back() << ")";
std::cout << ")" << std::endl;
#endif

	bool ParentFound = false;
	std::string ParentString;

/* ERIC - LETS THINK

Different Cases
  PARENT			CHILD				POSSIBILITY					PARENT STRING
  ======			======				===========					=============
  Unknown			Unknown				Not, no Section				N/A						
  Unknown			Data				U-LAND						No parent									
  Unknown			No Data				U-EXSPIEL					No Parent				
  Data				Data				VEREIN-SPIELER				Normal Case, Parent from Parent ID					
  Data				No Data				LAND-MANAGERP				Child has no Data, No Parent to Set					
  No Data			Data				ManagerP-MANAGER			No Parent, Generic Parent						
  No Data			No Data				???							No Parent, No Child, nothing to set		
  Data/NoData		SPECIAL CASE(Data)	STADION (VEREIN)			Special Handling before anything else
  Data/NoData		SPECIAL CASE(Data)	SPIELER_HIDDEN (EXSPIEL)	Special Handling before anything else

  HOW ABOUT:
  LAND		AJUGEND		AJUGEND_HIDDEN
  Data		No Data		Data

  if have parent
	  if Child has Data
			if/switch special cases

		if no parent found
				if parent has data
					from parent
				else
					generic from parent

	  else
		// Nothing to Do
  
   */
	if (ParentSectionType != SECTION_TYPE_UNKNOWN)
	{
		if (SectionContainsData(DataSectionType))
		{
			if (ChildSectionType == SECTION_TYPE_STADION)
			{
				// Stadion used not the Parent but the Last Verein written
				ParentString = std::static_pointer_cast<section>(SectionList[SECTION_TYPE_VEREIN].back())->GetUniqueId();
				ParentFound = true;
			} // if child is parent
			else
			{
				if(SectionContainsData(ParentSectionType))
				{
					ParentString = ParentSectionList.back()->GetUniqueId();
					ParentFound = true;
				} // parent has data
				else
				{
					// Generic Parent Case
					ParentString = GetGenericParentIdentifier (ParentSectionType);
					ParentFound = true;
				} // parent no data
			} // default case
		} // if child has data
		else
		{
			// Nothing to Do, nothing to set a parent to
		} // no data in child
	} // if we have parentRese
	
	if(ParentFound)
	{
		ChildSectionList.back()->SetParentId(ParentString);
	} // if parent found

} // AssignParent


static void CreateObjectForSection (std::vector<std::shared_ptr<section>> SectionList[NO_OF_SECTION_TYPES],
									SECTION_TYPE CurrentSectionType, int SectionLineCount,
									SECTION_TYPE ChildSection, SECTION_TYPE ParentSection)
{
#if DEBUG_ENABLED
	std::cout << __FUNCTION__ << "->CURRENT:::PARENT:::CHILD ==>> " << GetNameFromSectionType(CurrentSectionType) << ":::" <<
						GetNameFromSectionType(ParentSection) << ":::" <<
						GetNameFromSectionType(ChildSection) << ":::" << std::endl;
#endif

	bool NeedAssignParent = true;
	switch (CurrentSectionType)
	{
	case SECTION_TYPE_SPIELER:
		T_AddNewSection<spieler>(SectionList[CurrentSectionType]);
		break;

	case SECTION_TYPE_LAND:
		T_AddNewSection<land>(SectionList[CurrentSectionType]);
		break;

	case SECTION_TYPE_VEREIN:
		// Add new Verein
		T_AddNewSection<verein>(SectionList[CurrentSectionType]);
		break;

	case SECTION_TYPE_VEREIN_HIDDEN:
		// Don't create for Hidden sections which belong to a main data section
		// Don't need to assign a parent, Verein already assigned to Land
		NeedAssignParent = false;
		break;

	case SECTION_TYPE_SPIELER_HIDDEN:
		// Don't create for Hidden sections which belong to a main data section
		// Special Case, Assign Parent of Spieler
//		ChildSection = ParentSection = SECTION_TYPE_SPIELER;
		NeedAssignParent = false;
		break;

	case SECTION_TYPE_MANAGER:
		T_AddNewSection<manager>(SectionList[CurrentSectionType]);		
		break;

	case SECTION_TYPE_CLEAGUEGRP:
		T_AddNewSection<cleaguegrp>(SectionList[CurrentSectionType]);		
		break;

	case SECTION_TYPE_IVEREIN:
		T_AddNewSection<iverein>(SectionList[CurrentSectionType]);		
		break;

	case SECTION_TYPE_TRAINER:
		T_AddNewSection<trainer>(SectionList[CurrentSectionType]);		
		break;

	case SECTION_TYPE_STADION:
		T_AddNewSection<stadion>(SectionList[CurrentSectionType]);			
		break;

	case SECTION_TYPE_AMATEURV:
		T_AddNewSection<amateurv>(SectionList[CurrentSectionType]);		
		break;

	case SECTION_TYPE_AJUGEND_HIDDEN:
		// write to the Ajugend instead
		T_AddNewSection<ajugend>(SectionList[SECTION_TYPE_AJUGEND]);
		break;

	case SECTION_TYPE_TWTRAINER:
		T_AddNewSection<twtrainer>(SectionList[CurrentSectionType]);		
		break;

	case SECTION_TYPE_SCHIRI:
		T_AddNewSection<schiri>(SectionList[CurrentSectionType]);		
		break;

	case SECTION_TYPE_SPONSOR:
		T_AddNewSection<sponsor>(SectionList[CurrentSectionType]);		
		break;

	case SECTION_TYPE_PROMI:
		T_AddNewSection<promi>(SectionList[CurrentSectionType]);		
		break;

	case SECTION_TYPE_REPORTER:
		T_AddNewSection<reporter>(SectionList[CurrentSectionType]);		
		break;

	case SECTION_TYPE_KRITIKER:
		T_AddNewSection<kritiker>(SectionList[CurrentSectionType]);		
		break;

	case SECTION_TYPE_VPRAESID:
		T_AddNewSection<vpraesid>(SectionList[CurrentSectionType]);		
		break;

	case SECTION_TYPE_ASPIELER_HIDDEN:
		T_AddNewSection<aspieler>(SectionList[SECTION_TYPE_ASPIELER]);			
		break;

	case SECTION_TYPE_SPIEL_HIDDEN:
		T_AddNewSection<spiel>(SectionList[CurrentSectionType]);	
		std::static_pointer_cast<spiel>(SectionList[CurrentSectionType].back())->CalculateMatchDay(
			std::static_pointer_cast<liga>(SectionList[SECTION_TYPE_LIGA].back())->GetValueAtSectionPos(LIGA_SECTION_POS_VEREINSANZAHL),
			SectionList[CurrentSectionType].size());
		break;

	case SECTION_TYPE_EUROSIEGER_HIDDEN:
		T_AddNewSection<eurosieger>(SectionList[SECTION_TYPE_EUROSIEGER]);			
		break;

	case SECTION_TYPE_ISCHIRI_HIDDEN:
		T_AddNewSection<ischiri>(SectionList[SECTION_TYPE_ISCHIRI]);			
		break;

	case SECTION_TYPE_NATION:
		T_AddNewSection<nation>(SectionList[CurrentSectionType]);	
		break;

	case SECTION_TYPE_LIGA:
		T_AddNewSection<liga>(SectionList[CurrentSectionType]);			
		break;

	case SECTION_TYPE_TURNIERGRP:
		T_AddNewSection<turniergrp>(SectionList[CurrentSectionType]);			
		break;

	case SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN:
		T_AddNewSection<spielplan_verein>(SectionList[CurrentSectionType]);			
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Section Type: " << CurrentSectionType << ": " << GetNameFromSectionType(CurrentSectionType) << " -> " <<__FUNCTION__;
		programError (ErrorText.str());	
	} // Switch CurrentSectionType

	// Assign the Parent if it's for the first line
	if(NeedAssignParent)
		AssignParent (SectionList, CurrentSectionType, ParentSection, SectionList[ParentSection], ChildSection, SectionList[ChildSection]);
} // CreateObjectForSection



static void SetFieldForSection (std::vector<std::shared_ptr<section>> SectionList[NO_OF_SECTION_TYPES],
								SECTION_TYPE CurrentSectionType, std::string& Line, int SectionLineCount)
{
#if 0
std::cout << __FUNCTION__ << "->Section:Line:Count ==>> " << GetNameFromSectionType(CurrentSectionType) << "::"
			<< Line << "::" << SectionLineCount << std::endl;
#endif

	switch (CurrentSectionType)
	{
		case SECTION_TYPE_SPIELER:
			AssignSpielerField(SectionList[CurrentSectionType], SectionLineCount, Line);
			break;

		case SECTION_TYPE_LAND:
			AssignLandField(SectionList[CurrentSectionType], SectionLineCount, Line);
			break;

		case SECTION_TYPE_VEREIN:
			AssignVereinField(SectionList[CurrentSectionType], SectionLineCount, Line);
			// Update the Land Id if Needed
			if (SectionLineCount == VEREIN_SECTION_POS_LAND)
			{
				// Update Land Id
				std::static_pointer_cast<land>(SectionList[SECTION_TYPE_LAND].back())->UpdateLandIdIfNeeded(
					std::static_pointer_cast<verein>(SectionList[CurrentSectionType].back())->GetValueAtSectionPos(
						VEREIN_SECTION_POS_LAND));
			} // if verein id
			break;

		case SECTION_TYPE_VEREIN_HIDDEN:
			// Hidden Section needs to Access the Parent Section
			AssignVereinField(SectionList[SECTION_TYPE_VEREIN], SectionLineCount + GetVereinHiddenOffset(), Line);			
			break;

		case SECTION_TYPE_SPIELER_HIDDEN:
			// Hidden Section needs to Access the Parent Section
			AssignSpielerField(SectionList[SECTION_TYPE_SPIELER], SectionLineCount + GetSpielerHiddenOffset(), Line);			
			break;

		case SECTION_TYPE_MANAGER:
			AssignManagerField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_CLEAGUEGRP:
			AssignCleagueGrpField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_IVEREIN:
			AssignIVereinField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_TRAINER:
			AssignTrainerField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_STADION:
			AssignStadionField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_AMATEURV:
			AssignAmateurvField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_AJUGEND_HIDDEN:
			// write to the Ajugend instead
			AssignAJugendField(SectionList[SECTION_TYPE_AJUGEND], SectionLineCount, Line);	
			break;

		case SECTION_TYPE_TWTRAINER:
			AssignTwTrainerField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_SCHIRI:
			AssignSchiriField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_SPONSOR:
			AssignSponsorField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_PROMI:
			AssignPromiField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_REPORTER:
			AssignReporterField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_KRITIKER:
			AssignKritikerField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_VPRAESID:
			AssignVpraesidField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_ASPIELER_HIDDEN:
			AssignASpielerField(SectionList[SECTION_TYPE_ASPIELER], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_SPIEL_HIDDEN:
			AssignSpielField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_EUROSIEGER_HIDDEN:
			AssignEurosiegerField(SectionList[SECTION_TYPE_EUROSIEGER], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_ISCHIRI_HIDDEN:
			AssignISchiriField(SectionList[SECTION_TYPE_ISCHIRI], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_NATION:
			AssignNationField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_TURNIERGRP:
			AssignTurnierGrpField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_LIGA:
			AssignLigaField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		case SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN:
			AssignSpielplan_VereinField(SectionList[CurrentSectionType], SectionLineCount, Line);			
			break;

		default:
			std::stringstream ErrorText;
			ErrorText << "Unexpected Section Type: " << CurrentSectionType << ": " << GetNameFromSectionType(CurrentSectionType) << " -> " <<__FUNCTION__;
			programError (ErrorText.str());	
	} // Switch CurrentSectionType
} // SetFieldForSection

static void UpdateLastSectionCount (std::vector<std::shared_ptr<section>> SectionList[NO_OF_SECTION_TYPES],
									size_t LastSectionCount[NO_OF_SECTION_TYPES])
{
	for (int i = SECTION_TYPE_UNKNOWN; i < NO_OF_SECTION_TYPES; i++)
	{
		LastSectionCount[i] = SectionList[i].size();
	} // for each section
} // UpdateLastSectionCount

static void ResetSectionList (std::vector<std::shared_ptr<section>> SectionList[NO_OF_SECTION_TYPES], 
								size_t SectionLastCount[NO_OF_SECTION_TYPES], bool KeepPersistantSections,
								size_t InternatSavLastSectionCount[NO_OF_SECTION_TYPES])
{
	for (int i = SECTION_TYPE_UNKNOWN; i < NO_OF_SECTION_TYPES; i++)
	{
		if ((!KeepPersistantSections) || (!SectionNeededForOtherSections ((SECTION_TYPE) i)))
		{
			SectionList[i].erase (SectionList[i].begin(), SectionList[i].end());
			SectionLastCount[i] = 0;
			InternatSavLastSectionCount[i] = 0;
		}
	} // for each section type
} // ResetSectionList

static void InitializeLandIds (FILE_LAND_ID_STRUCT FileLandIds[NO_OF_A3_FILE_NAME_TYPES])
{
	for (int i = 0; i < NO_OF_A3_FILE_NAME_TYPES; i++)
	{
		FileLandIds[i].LandId = BLANK_LAND_ID;
		FileLandIds[i].LandId_Expanded = BLANK_LAND_ID;
	} // for each file name
} // InitializeLandIds

void exportA3DbFiles (bool ShouldAutogenerateFixtures)
{
	// Declare local lists
	std::vector<std::shared_ptr<section>> SectionList[NO_OF_SECTION_TYPES];
	size_t SectionLastCount[NO_OF_SECTION_TYPES];
	// HACK - ERIC - Ideally we find a better solution, this is too specific, but needed as we need to update this foe Internat.sav files
	size_t InternatSavLastSectionCount[NO_OF_SECTION_TYPES];
	FILE_LAND_ID_STRUCT FileLandIds[NO_OF_A3_FILE_NAME_TYPES];

	// Initialize local Data
	InitializeLocalData (SectionList, SectionLastCount, InternatSavLastSectionCount, FileLandIds);

	// Initialize File List
	std::vector<std::string> FileList;
	GetListOfA3DbFiles(FileList);

	for (std::vector<std::string>::const_iterator FileNameIterator = FileList.begin ();
		FileNameIterator != FileList.end(); ++FileNameIterator)
	{
		showTextMsg(std::string("Lese XML Datei fuer: ") + *FileNameIterator);

		// Reset the List
		ResetSectionList (SectionList, SectionLastCount, true, InternatSavLastSectionCount);

		// Read External XML files
		// If not all read ignore as output will not be ok
		if (ReadA3DbExternalFile (*FileNameIterator, SectionList))
		{
			// Process any Data after importing from XML (e.g. setting counters if needed)
			PostExternalImportProcessing (*FileNameIterator, SectionList, SectionLastCount, ShouldAutogenerateFixtures, FileLandIds);

			// Sort any Vectors needed
			SortSectionLists (SectionList);

			std::vector<std::string> A3DbOutList;
			// Add file initializing data
			AddFileInitializers(*FileNameIterator, A3DbOutList);

			showTextMsg(std::string("  Erstelle A3 Daten fuer: " + std::string(*FileNameIterator)));
			// Export the XML Data
			ExportSectionToA3 (SECTION_TYPE_UNKNOWN, nullptr, SECTION_TYPE_UNKNOWN,	nullptr, std::string(*FileNameIterator), SectionList, A3DbOutList);

			// Add trailing information to the file
			AddFileTrailingData(*FileNameIterator, A3DbOutList);


			// Only Need to Write to File if we actually have something to write
			if (A3DbOutList.size() > 0)
			{
				showTextMsg(std::string("  Schreibe Datei: ") + *FileNameIterator);
				WriteDataToA3Db (*FileNameIterator, A3DbOutList);
			} // If added elements to the list

			UpdateLastSectionCount (SectionList, SectionLastCount);
		} // if read the external files ok
	} // For each File 
} // exportToA3Db

#if DEBUG_ENABLED
#include <iomanip>
static int gLevel = 0;
#endif
static void ExportRelatedSections (bool SubSections, 
								   SECTION_TYPE DataSectionType, section* DataSectionPtr,
								   SECTION_TYPE ParentSectionType, section* ParentSectionPtr, 
								   const std::string& FileName, 
								   const std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES],
								   std::vector<std::string>& A3DbOutList)
{
#if DEBUG_ENABLED
	gLevel++;
	std::cout << std::right << std::setw(3*gLevel) << "(" << gLevel << ")" << "RECURSIVE_CALL TO " << __FUNCTION__
		<< "SubNotFollow(" << SubSections << ")>:" << std::endl;
	std::cout << std::right << std::setw(3*gLevel) << "    " <<"DataSectionType:   " << GetNameFromSectionType(DataSectionType) << ", SectionPtr: " << DataSectionPtr << std::endl;
	std::cout << std::right << std::setw(3*gLevel) << "    " << "ParentSectionType: " << GetNameFromSectionType(ParentSectionType) << ", SectionPtr: " << ParentSectionPtr << std::endl;
#endif

	// Get all SubSections
	std::vector<SECTION_TYPE> NextSectionTypesList;
	if(SubSections)
		GetSubLevelSections(FileName, DataSectionType, NextSectionTypesList);
	else
		GetFollowUpSections(FileName, DataSectionType, NextSectionTypesList);

	// Process Each Subsection
	for (std::vector<SECTION_TYPE>::const_iterator SectionTypeIterator = NextSectionTypesList.begin();
		SectionTypeIterator != NextSectionTypesList.end(); ++SectionTypeIterator)
	{
		if (SectionContainsData(*SectionTypeIterator))
		{
			// Go through Each Section for Data
			std::vector<std::shared_ptr<section>>::iterator SectionIterator;
			std::vector<std::shared_ptr<section>> SectionVector;

			// If a hidden section, use it's data section
			if(SectionIsVisible (*SectionTypeIterator))
				SectionVector = SectionList[*SectionTypeIterator];
			else
				SectionVector = SectionList[GetDataSectionFromHiddenSection(*SectionTypeIterator)];

			for(SectionIterator = SectionVector.begin(); SectionIterator != SectionVector.end(); ++SectionIterator)
			{
#if DEBUG_ENABLED
std::cout << std::right << std::setw(3*gLevel) << "     " << "==>> PROCESS_SECTION: " << GetNameFromSectionType(std::static_pointer_cast<section>(*SectionIterator)->GetSectionType()) <<
	":::" << std::static_pointer_cast<section>(*SectionIterator)->GetUniqueId() << std::endl;
#endif

			section* WorkDataSectionPtr = std::static_pointer_cast<section>(*SectionIterator).get();
			SECTION_TYPE WorkParentSectionType = DataSectionType;
			section* WorkParantSectionPtr = DataSectionPtr;

			// If invisible section and parent doesn't contain data, take original parent
			if ((!SectionIsVisible(*SectionTypeIterator)) && (!SectionContainsData(DataSectionType)))
			{
				WorkParentSectionType = ParentSectionType;
				WorkParantSectionPtr = ParentSectionPtr;
			}

			ExportSectionToA3(*SectionTypeIterator, WorkDataSectionPtr, WorkParentSectionType, WorkParantSectionPtr,
				FileName, SectionList, A3DbOutList);
			} // for each section
		} // section has no data
		else
		{
			// no data, export section with currect section as parent but no current pointer
			ExportSectionToA3(*SectionTypeIterator, nullptr, DataSectionType, DataSectionPtr,
								FileName, SectionList, A3DbOutList);
		} // section has data
	} // For each sub section
#if DEBUG_ENABLED
gLevel--;
#endif
} // ExportRelatedSections

static void ExportSectionToA3 (SECTION_TYPE DataSectionType, section* DataSectionPtr, 
							   SECTION_TYPE ParentSectionType, section* ParentSectionPtr, 
							   const std::string& FileName, 
							   const std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES],
							   std::vector<std::string>& A3DbOutList)
{
//ERIC
#if DEBUG_ENABLED
	gLevel++;
	std::cout << std::right << std::setw(3*gLevel) << "(" << gLevel << ")" << "RECURSIVE_CALL TO " << __FUNCTION__ << ":" << std::endl;
	std::cout << std::right << std::setw(3*gLevel) << "     " << "DataSectionType:   " << GetNameFromSectionType(DataSectionType) << ", SectionPtr: " << DataSectionPtr << std::endl;
	std::cout << std::right << std::setw(3*gLevel) << "     " << "ParentSectionType: " << GetNameFromSectionType(ParentSectionType) << ", SectionPtr: " << ParentSectionPtr << std::endl;

//	std::cout << "  ==>>" << __FUNCTION__ << ", DataSection: " << GetNameFromSectionType(DataSectionType) << std::endl;
#endif

	if (DataSectionType != SECTION_TYPE_UNKNOWN)
	{
		bool SectionVisible = SectionIsVisible (DataSectionType);
		
		if (SectionMatchesParent (ParentSectionType, ParentSectionPtr, DataSectionType, DataSectionPtr))
		{
			// Section Start
			if (SectionVisible)
				A3DbOutList.push_back(FormSectionStart(DataSectionType));	

			//ERIC
#if DEBUG_ENABLED
			std::cout << "WRITING DATA " << __FUNCTION__ << ":" << std::endl;
			std::cout << "    DataSectionType:   " << GetNameFromSectionType(DataSectionType) << ", SectionPtr: " << DataSectionPtr << std::endl;
#endif

#if DEBUG_ENABLED
std::cout << std::right << std::setw(3*gLevel) << "     " << "Writing Data for " << GetNameFromSectionType(DataSectionType) << std::endl;
int OldFields = A3DbOutList.size();
#endif

			// Check if we need to add any fields like Counters
			AddSpecialFieldsBeforeData (A3DbOutList, DataSectionType, DataSectionPtr, FileName, SectionList);

			// Add Section Data
			if(SectionContainsData(DataSectionType))
				DataSectionPtr->AddFieldsToA3DbList (A3DbOutList, DataSectionType, FileName);
#if DEBUG_ENABLED
std::cout << std::right << std::setw(3*gLevel) << "     " << "Fields Written: " << A3DbOutList.size() - OldFields << std::endl;
#endif

			// Pass in the Original Data Type incl. hidden
			ExportRelatedSections (true, DataSectionType, DataSectionPtr, ParentSectionType, ParentSectionPtr, FileName, SectionList, A3DbOutList);

			// Section End
			if (SectionVisible)
				A3DbOutList.push_back(FormSectionEnd(DataSectionType));			

			// Pass in the Original Data Type incl. hidden
			ExportRelatedSections (false, DataSectionType, DataSectionPtr, ParentSectionType, ParentSectionPtr, FileName, SectionList, A3DbOutList);
		} // if section matches the parent
	} // if have a section
	else
	{
		ExportRelatedSections (true, SECTION_TYPE_UNKNOWN, nullptr, SECTION_TYPE_UNKNOWN, nullptr, FileName, SectionList, A3DbOutList);
	} // no section yet

#if DEBUG_ENABLED
gLevel--;
#endif
} // ExportSectionToA3

void AddSpecialFieldsBeforeData (std::vector<std::string>& A3DbOutList, SECTION_TYPE DataSectionType, 
								 section*, const std::string& FileName,
								const std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	int SubSectionCount = 0;
	std::vector<std::shared_ptr<section>>::iterator Iterator;
	std::vector<std::shared_ptr<section>> SectionVector;
	switch (DataSectionType)
	{
	case SECTION_TYPE_EUROSIEGER:
		// All data will be written, no parent relationship
		A3DbOutList.push_back(std::to_string(SectionList[DataSectionType].size()));
		break;

	case SECTION_TYPE_SONSPIELER:
	case SECTION_TYPE_EXSPIEL:
		// All data will be written, no parent relationship
		A3DbOutList.push_back(std::to_string(SectionList[SECTION_TYPE_SPIELER].size()));
		break;
		
	case SECTION_TYPE_CLEAGUE:
		// All data will be written, no parent relationship
		A3DbOutList.push_back(std::to_string(SectionList[SECTION_TYPE_CLEAGUEGRP].size()));
		break;

	case SECTION_TYPE_EMGRP:
	case SECTION_TYPE_WMGRP:
		SubSectionCount = 0;
		SectionVector = SectionList[SECTION_TYPE_TURNIERGRP];
		for(Iterator = SectionVector.begin(); Iterator != SectionVector.end(); ++Iterator)
		{
			if(SectionMatchesParent(DataSectionType, nullptr, SECTION_TYPE_TURNIERGRP, 
									std::static_pointer_cast<turniergrp>(*Iterator).get()))
			{
				SubSectionCount++;
			} // If group for the right type
		} // for each turniergroup

		A3DbOutList.push_back(std::to_string(SubSectionCount));
	break;

	default:
		break;
	}
} // AddSpecialFieldsBeforeData

static void AddFileInitializers (const std::string& FileName, std::vector<std::string>& A3DbOutList)
{
	// File Opener
	A3DbOutList.push_back (FILE_OPENING_NUMBER);

	// Do specific handling
	A3_FILE_GROUP_TYPE FileGroupType = GetA3FileGroupFromFileName(FileName);

	switch(FileGroupType)
	{
	case A3_FILE_GROUP_LAENDER:
		// Additional %SECT%NATION
		A3DbOutList.push_back ("%SECT%NATION");
		break;

	default:
		break;
	}

} // AddFileInitializers

static void AddFileTrailingData (const std::string& FileName, std::vector<std::string>& A3DbOutList)
{

	// Do specific handling
	A3_FILE_GROUP_TYPE FileGroupType = GetA3FileGroupFromFileName(FileName);

	switch(FileGroupType)
	{
	case A3_FILE_GROUP_LAENDER:
		// Additional %ENDSECT%NATION
		A3DbOutList.push_back ("%ENDSECT%NATION");
		break;

	default:
		break;
	}

} // AddFileTrailingData

static bool SectionMatchesParent (SECTION_TYPE ParentSectionType, section* ParentSectionPtr, 
								  SECTION_TYPE ChildSectionType, section* ChildSectionPtr)

{
/*
POSSIBLE INPUT AND SITUATIONS

	ParentSectionType	- Only initially Unknown, after that always a Parent Section 
		-> Base Case, ParentSectionType = UNKNOWN, match ok
	ParentSectionPtr	- null only if ParentSectionType has no Data, -> ManagerP->Manager
	ChildSectionPtr		- null if dealing with unknown Child, e.g. No Data Child -> Land-ManagerP


  - Base Case (Land, Unknown Parent, All other will have a Parent)
		-> if ParentSectionType = UNKNOWN, match ok

  CALLS:
	ChildSectionPtr->SectionMatchesParent(PARENT_SECTION_TYPE)	- Match Non Data Parents
	ChildSectionPtr->SectionMatchesParent(ParentSection)		- Match Data Parents

	*/
#if DEBUG_ENABLED
std::cout << "ParentPtr::ChildPtr => " << ParentSectionPtr << ":::" << ChildSectionPtr << std::endl;
std::cout << "COMPARE CHILD(ID)::PARENT(ID)";

if (ChildSectionPtr != nullptr)
	std::cout << GetNameFromSectionType(ChildSectionPtr->GetSectionType()) << "(";
	
if (ParentSectionPtr != nullptr)
	std::cout << ParentSectionPtr->GetParentId();

std::cout << "):::" << GetNameFromSectionType(ParentSectionType) << "(";

if (ParentSectionPtr != nullptr)
	std::cout << ParentSectionPtr->GetUniqueId();
	
std::cout << ")" << std::endl;
#endif

	bool SectionForParent = false;
	
	if (ParentSectionType == SECTION_TYPE_UNKNOWN)
	{
		SectionForParent = true;
	} // base case, no parent yet


#if 1
	/*
	KEEP IT GENERIC BUT CAPTURE OUR CASE

		- We Have 2 SECTIONS (SPIELER + SPIELER_HIDDEN)
		- One is the DataSection pf the other
		*/


	else if ((!SectionIsVisible(ChildSectionType)) &&
			 (GetDataSectionFromHiddenSection(ChildSectionType) == ParentSectionType))
	{
/*
THIS SEEMS TO NEARLY WORK,
	LOOKS UGLY,
	WHEN RUNNING, THE FIRST OBJECT HAS MULTIPLE, THE OTHER ONES ARE OK
*/
		// expect the same pointers if belonging together
		SectionForParent = (ChildSectionPtr == ParentSectionPtr);
/*
WE GET SPIELER AND SPIELER_HIDDEN with either the same or different Pointers,
	just need to figure out how to express this somewhere here,
	if its different Pointers the normal compare will 
		VISIBILITY??? CHILE IS NOT VISIBLE
*/
	}
#endif
	else
	{
		if ((ChildSectionPtr == NULL) || (ChildSectionPtr == ParentSectionPtr))
		{
			SectionForParent = true;
		} // no child section, MUST be non data section
		else
		{
			if (SectionContainsData(ParentSectionType))
			{
				SectionForParent = ChildSectionPtr->SectionMatchesParent(ParentSectionPtr);
			} // data parent
			else
			{
				SectionForParent = ChildSectionPtr->SectionMatchesParent(ParentSectionType);
			} // no data parent
		}
	} // have parent
	return (SectionForParent);
} // SectionMatchesParent


static void WriteDataToA3Db (const std::string& FileName, std::vector<std::string>& A3DbOutList)
{	
	// Ensure Output directory exists
	EnsureDirectoryExists(SAV_STORAGE_DIR);

	// Collect the data
	std::stringstream FileStream;
	FileStream.str(std::string());
	for (std::vector<std::string>::iterator ListIter = A3DbOutList.begin();
		ListIter != A3DbOutList.end(); ++ListIter)
	{
		std::string CurrentLine = *ListIter;
		ConvertUtf8ToLocalCharSet(CurrentLine);
		FileStream << CurrentLine << std::endl;
	} // for each entry

	// Write to file
	std::ofstream FileHandle (FormSavStoragePath(FileName), std::ofstream::out);

    FileHandle << FileStream.rdbuf();
	FileHandle.close();
} // WriteDataToA3Db

static std::string FormSavStoragePath (const std::string& BaseFileName)
{
	return (std::string(SAV_STORAGE_DIR) + BaseFileName);
} // FormSavStoragePath

void SortSectionLists (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	for (int TempSectionInt = SECTION_TYPE_UNKNOWN + 1; TempSectionInt < NO_OF_SECTION_TYPES; TempSectionInt++)
	{
		switch(TempSectionInt)
		{
		case SECTION_TYPE_SPIEL_HIDDEN:
			SortMatchesByMatchDay(SectionList [TempSectionInt]);
			break;

		default:
			// do nothing
			break;
		}
	} // for each section
} // SortSectionLists

static void CloseSectionKnockOns (SECTION_TYPE ClosedSection, const std::string& FileName,
					std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES],
					size_t InternatSavLastSectionCount[NO_OF_SECTION_TYPES])
{
#if DEBUG_ENABLED
std::cout << __FUNCTION__ << ", ClosesdSection: " << GetNameFromSectionType(ClosedSection) << ", FileName: " << FileName <<
	", FileNameType: " << GetNameFromA3FileNameType(GetA3FileNameTypeFromFileName(FileName)) << std::endl;
#endif

	/* A BIT OF A HACK FOR NOW, MAYBE CLEAN UP FUNCTION LATER */
	if ((ClosedSection == SECTION_TYPE_LAND) &&
		(GetA3FileNameTypeFromFileName(FileName) == A3_FILE_NAME_INTERNAT))
	{
		// Get the Land Ids
		std::string LandId = std::static_pointer_cast<land>(SectionList[SECTION_TYPE_LAND].back())->GetValueAtSectionPos(LAND_SECTION_POS_LAND_ID);;
		std::string LandId_Expanded = NationValueToNationString (LandId, SectionList);

		// Set the Land Ids
		SetSectionLandIds (LandId, LandId_Expanded, SectionList, InternatSavLastSectionCount);

		// Update the Last section Count
		UpdateLastSectionCount (SectionList, InternatSavLastSectionCount);

	} // if closing a land in Internat.sav
} // CloseSectionKnockOns

static void PostSavDataPostImportProcessing (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Section Type Specific Processing
	for (int SectionType = 0; SectionType < NO_OF_SECTION_TYPES; SectionType++)
	{
		switch (SectionType)
		{
		case SECTION_TYPE_SPIELER:
			#if CONVERT_EX_SPIELER_REFERENCE_ERRORS
				ConvertIllegalExSpielerReferences (SectionList);
			#endif
			break;

		default:
			break;
		} // switch section type
	} // for each section
} // PostSavDataPostImportProcessing

static void PostSavFinalDataProcessing (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Section Type Specific Processing
	for (int SectionType = 0; SectionType < NO_OF_SECTION_TYPES; SectionType++)
	{
		switch (SectionType)
		{
		case SECTION_TYPE_SPIELER:
			MixSpielerFaehigkeiten(SectionList [SECTION_TYPE_SPIELER]);
			break;

		default:
			break;
		} // switch section type
	} // for each section
} // PostSavFinalDataProcessing

static void PostExternalFirstDataProcessing (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	// Section Type Specific Processing
	for (int SectionType = 0; SectionType < NO_OF_SECTION_TYPES; SectionType++)
	{
		switch (SectionType)
		{
		case SECTION_TYPE_SPIELER:
			UnMixSpielerFaehigkeiten(SectionList [SECTION_TYPE_SPIELER]);
			break;

		default:
			break;
		} // switch section type
	} // for each section
} // PostExternalFirstDataProcessing

static void PostSavImportProcessing (const std::string& BaseFileName, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES],
	size_t LastSectionCount[NO_OF_SECTION_TYPES], FILE_LAND_ID_STRUCT FileLandIds[NO_OF_A3_FILE_NAME_TYPES])
{
	// First need to Prepare Reference Prerequisits e.g. setting Section Data
TIMING_START
	PostSavPrepareReferencePrerequisits (BaseFileName, SectionList, LastSectionCount, FileLandIds);
TIMING_END(PostSavPrepareReferencePrerequisits)

	// Split Fields if Needed
TIMING_START
	PostSavSplitCombinedFields (SectionList, LastSectionCount);
TIMING_END(PostSavSplitCombinedFields)

	// Expand Bitmask Fields
TIMING_START
	PostSavExpandBitmaskFields (SectionList, LastSectionCount);
TIMING_END(PostSavExpandBitmaskFields)

	// Convert Booleans to Text
TIMING_START
	PostSavConvertBooleansToText (SectionList, LastSectionCount);
TIMING_END(PostSavConvertBooleansToText)

	// Calculate Verein Indices
TIMING_START
	CalculateVereinIndices (SectionList);
TIMING_END(CalculateVereinIndices)

	// Do Data Post-Processing (e.g. Verein Index Numbers for Mixed Vereine from various countries)
TIMING_START
	PostSavDataPostImportProcessing (SectionList);
TIMING_END(PostSavDataPostImportProcessing)

#if DEBUG_ENABLED
std::cout << "CURRENT SECTION STATUS" << std::endl;
for (int i = 0; i < NO_OF_SECTION_TYPES; i++)
{
	std::cout << " SECTION(Count, LastCount) == " << GetNameFromSectionType((SECTION_TYPE)i) << "(" << SectionList[i].size() << ", " << LastSectionCount[i] << ")" << std::endl; 
}
#endif 

#if DEBUG_ENABLED
std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRE - EXPAND BEGIN @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
PrintSectionListContent(SECTION_TYPE_LAND, SectionList);
PrintSectionListContent(SECTION_TYPE_NATION, SectionList);
PrintSectionListContent(SECTION_TYPE_VEREIN, SectionList);
PrintSectionListContent(SECTION_TYPE_SPIELER, SectionList);
std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRE - EXPAND END @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
#endif

	// Now Can Expand References and other Values
TIMING_START
	PostSavExpandDecodedFields (SectionList, LastSectionCount);
TIMING_END(PostSavExpandDecodedFields)

#if DEBUG_ENABLED
std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ POST - EXPAND BEGIN @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
PrintSectionListContent(SECTION_TYPE_LAND, SectionList);
PrintSectionListContent(SECTION_TYPE_NATION, SectionList);
PrintSectionListContent(SECTION_TYPE_VEREIN, SectionList);
PrintSectionListContent(SECTION_TYPE_SPIELER, SectionList);
std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ POST - EXPAND END @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
#endif



	// Decode Enums
TIMING_START
	PostSavDecodeEnumFields (SectionList, LastSectionCount);
TIMING_END(PostSavDecodeEnumFields)

	// Final Data Conversion
TIMING_START
	PostSavFinalDataProcessing (SectionList);
TIMING_END(PostSavFinalDataProcessing)
} // PostSavImportProcessing

static void PostSavPrepareReferencePrerequisits (const std::string& BaseFileName, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES],
	size_t LastSectionCount[NO_OF_SECTION_TYPES], FILE_LAND_ID_STRUCT FileLandIds[NO_OF_A3_FILE_NAME_TYPES])
{
    // Identify Land Ids for Setting all sections
	std::string LandId;
	std::string LandId_Expanded;
	if (CalcLandIdForFile (BaseFileName, SectionList, LandId, LandId_Expanded, FileLandIds))
	{
#if DEBUG_ENABLED
std::cout << __FUNCTION__ << ", Land for " << BaseFileName << " -> \"" << LandId_Expanded << "\"(" << LandId << ")" << std::endl;
#endif
		// Update all Written sections with our Identified Land Id
		SetSectionLandIds (LandId, LandId_Expanded, SectionList, LastSectionCount);
	} // if we identified land id
#if DEBUG_ENABLED
else
{
	std::cout << __FUNCTION__ << ", Cannot Identify Land for " << BaseFileName << std::endl;
}
#endif
} // PostSavPrepareReferencePrerequisits

static void PostExternalImportProcessing (std::string FileName, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES],
	size_t LastSectionCount[NO_OF_SECTION_TYPES], bool ShouldAutogenerateFixtures, FILE_LAND_ID_STRUCT FileLandIds[NO_OF_A3_FILE_NAME_TYPES])
{
	// First Data Processing
TIMING_START
	PostExternalFirstDataProcessing (SectionList);
TIMING_END(PostExternalFirstDataProcessing)

	// Encode Enums
TIMING_START
	PostExternalEncodeEnumFields (SectionList, LastSectionCount);
TIMING_END(PostExternalEncodeEnumFields)

	// Decode all Country References (Possible as soon as Nations are read)
TIMING_START
PostExternalEncodeExpandedFields (FIELD_REFERENCE_LAND, SectionList, LastSectionCount, ShouldAutogenerateFixtures);
TIMING_END(PostExternalEncodeExpandedFields)

#if DEBUG_ENABLED
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ POST - IMPORT BEGIN @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	PrintSectionListContent(SECTION_TYPE_LAND, SectionList);
	PrintSectionListContent(SECTION_TYPE_NATION, SectionList);
	PrintSectionListContent(SECTION_TYPE_VEREIN, SectionList);
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ POST - IMPORT END @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
#endif

	// First need to Prepare Reference Prerequisits e.g. setting Section Land (working for some files)
TIMING_START
	PostSavPrepareReferencePrerequisits (FileName, SectionList, LastSectionCount, FileLandIds);
TIMING_END(PostSavPrepareReferencePrerequisits)

    // Some Special Requirements are Needed e.g. for Internat.sav which has multiple sets of Laender and so we need to set them more clever
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//	SLOW - SLOW - SLOW
TIMING_START
	SetPostExportImportFileSpecificData (FileName, SectionList, LastSectionCount);
TIMING_END(SetPostExportImportFileSpecificData)
	
#if DEBUG_ENABLED
	std::cout << "CURRENT SECTION STATUS" << std::endl;
	for (int i = 0; i < NO_OF_SECTION_TYPES; i++)
	{
		std::cout << " SECTION(Count) == " << GetNameFromSectionType((SECTION_TYPE)i) << "(" << SectionList[i].size() << ")" << std::endl; 
	}
#endif 

#if DEBUG_ENABLED
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRE - COMPRESS BEGIN @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	PrintSectionListContent(SECTION_TYPE_LAND, SectionList);
	PrintSectionListContent(SECTION_TYPE_NATION, SectionList);
	PrintSectionListContent(SECTION_TYPE_VEREIN, SectionList);
	PrintSectionListContent(SECTION_TYPE_PROMI, SectionList);
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRE - COMPRESS END @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
#endif

	// Calculate Verein indices
TIMING_START
	CalculateVereinIndices (SectionList);
TIMING_END(CalculateVereinIndices)
	
	// Encode Verein Reference Fields
TIMING_START
PostExternalEncodeExpandedFields (FIELD_REFERENCE_VEREIN, SectionList, LastSectionCount, ShouldAutogenerateFixtures);
TIMING_END(PostExternalEncodeExpandedFields)

#if DEBUG_ENABLED
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ POST - COMPRESS BEGIN @@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	PrintSectionListContent(SECTION_TYPE_LAND, SectionList);
	PrintSectionListContent(SECTION_TYPE_NATION, SectionList);
	PrintSectionListContent(SECTION_TYPE_VEREIN, SectionList);
	PrintSectionListContent(SECTION_TYPE_PROMI, SectionList);
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ POST - COMPRESS END @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
#endif
	
	// Filegroup Specific Processing
	A3_FILE_GROUP_TYPE 	FileGroupType = GetA3FileGroupFromFileName(FileName);
	switch (FileGroupType)
	{
	case A3_FILE_GROUP_LANDXXX:
		// Set the Land Counters	
		AssignVereinCountsForLand (SectionList);
		break;

	default:
		break;
	} // switch section type

	// Convert Booleans from Text
TIMING_START
	PostExternalConvertBooleansFromText (SectionList, LastSectionCount);
TIMING_END(PostExternalConvertBooleansFromText)

	// Combine Bitmask fields
TIMING_START
	PostExternalCombineBitmaskFields(SectionList, LastSectionCount);
TIMING_END(PostExternalCombineBitmaskFields)

	// Merge fields 
TIMING_START
	PostExternalMergeSplitFields(SectionList, LastSectionCount);
TIMING_END(PostExternalMergeSplitFields)
} // PostExternalImportProcessing

static void SetPostExportImportFileSpecificData (const std::string& FileName, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], 
									size_t LastSectionCount[NO_OF_SECTION_TYPES])
{
	if (GetA3FileNameTypeFromFileName(FileName) == A3_FILE_NAME_INTERNAT)
	{
//std::cout << "SETTING LAND IDS FOR INTERNAT.SAV" << std::endl;

		std::vector<std::shared_ptr<section>>::iterator LandIterator;
		std::vector<std::shared_ptr<section>> LandVector = SectionList [SECTION_TYPE_LAND];
		for (LandIterator = LandVector.begin() + LastSectionCount [SECTION_TYPE_LAND]; LandIterator != LandVector.end(); ++LandIterator)
		{
//std::cout << "  - Land: " << (*LandIterator)->GetUniqueId() << std::endl;
			// Get the Land Ids for this Land
			std::string LandIdExpanded = std::static_pointer_cast<land>(*LandIterator)->GetValueAtSectionPos(LAND_SECTION_POS_LAND_ID_EXPANDED);
			std::string LandId = NationStringToNationValue(LandIdExpanded, SectionList);

//std::cout << "    - LandId: \"" << LandId << "\", LandIdExpanded: \"" << LandIdExpanded << "\"" << std::endl;
			// Set Land Ids for Vereine
			SECTION_TYPE TargetSection = SECTION_TYPE_VEREIN;
			(*LandIterator)->SetA3LandIdsForMatchingSection(LandId, LandIdExpanded, SectionList[TargetSection], LastSectionCount [TargetSection]);
//std::cout << "      - Verein: " << (*VereinIterator)->GetUniqueId();

			// Set Land Ids for Vereine
			TargetSection = SECTION_TYPE_SPIELER;
			(*LandIterator)->SetA3LandIdsForMatchingSection(LandId, LandIdExpanded, SectionList[TargetSection], LastSectionCount [TargetSection]);

			// Set Land Ids for Vereine
			TargetSection = SECTION_TYPE_MANAGER;
			(*LandIterator)->SetA3LandIdsForMatchingSection(LandId, LandIdExpanded, SectionList[TargetSection], LastSectionCount [TargetSection]);

			// Set Land Ids for Vereine
			TargetSection = SECTION_TYPE_TRAINER;
			(*LandIterator)->SetA3LandIdsForMatchingSection(LandId, LandIdExpanded, SectionList[TargetSection], LastSectionCount [TargetSection]);

			// Set Land Ids for Vereine
			TargetSection = SECTION_TYPE_STADION;
			(*LandIterator)->SetA3LandIdsForMatchingSection(LandId, LandIdExpanded, SectionList[TargetSection], LastSectionCount [TargetSection]);
		} // for each land
	} // if for Internat.sav file

} // SetPostExportImportFileSpecificData

static bool CalcLandIdForFile (const std::string& FileName, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], 
	std::string& FoundLandId, std::string& FoundLandId_Expanded, FILE_LAND_ID_STRUCT FileLandIds[NO_OF_A3_FILE_NAME_TYPES])
{	
	// Get the Land from the File Name or from list
	A3_FILE_NAME_TYPE FileNameType = GetA3FileNameTypeFromFileName(FileName);
	A3_FILE_NAME_TYPE LandFileNameType = GetLandDefiningFileNameType (FileNameType);
	bool LandIdFound = false;


	if (FileLandIds[LandFileNameType].LandId.compare(BLANK_LAND_ID) != 0)
	{
		if (FileLandIds[FileNameType].LandId.compare(BLANK_LAND_ID) == 0)
		{
			FileLandIds[FileNameType] = FileLandIds[LandFileNameType];
			LandIdFound = true;
		} // if not set for this file, only for dependent file
	} // if Land Set for LandFileNameType
	else
	{
		if (FileNameType == LandFileNameType)
		{
			std::string LandId, LandIdExpanded;
			if (GetLandIdFromSectionList (FileNameType, LandId, LandIdExpanded, SectionList))
			{
				if (LandId.compare(BLANK_LAND_ID) == 0)
					LandId = NationStringToNationValue(LandIdExpanded, SectionList);
				else if (LandIdExpanded.compare(BLANK_LAND_ID) == 0)
					LandIdExpanded = NationValueToNationString (LandId, SectionList);


				// Update the Land
				FileLandIds [FileNameType].LandId = LandId;
				FileLandIds [FileNameType].LandId_Expanded = LandIdExpanded;

				LandIdFound = true;
			} // if land id found
		} // if file not depending on another file
		else
		{
			std::stringstream ErrorText;
			ErrorText << "Depending File " << GetNameFromA3FileNameType(LandFileNameType) << " should be imported before " <<
				GetNameFromA3FileNameType (FileNameType) << " -> " <<__FUNCTION__;
			programError (ErrorText.str());		
		}
	} // land not set

	if (LandIdFound)
	{
		// Set Found Land Ids
		FoundLandId = FileLandIds [FileNameType].LandId;
		FoundLandId_Expanded = FileLandIds [FileNameType].LandId_Expanded;
	} // if land id found
	else
	{
#if DEBUG_ENABLED
		std::cout << "LAND_ID NOT FOUND - File: " << FileName << ", DependentFileType: " << GetNameFromA3FileNameType(LandFileNameType) << std::endl;
#endif // DEBUG_ENABLED
	} // no land id found

	return(LandIdFound);
} // GetLandIdsFromSectionList

static void SetSectionLandIds (const std::string& LandId, const std::string& LandId_Expanded, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], 
								size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	for (int SectionTypeInt = SECTION_TYPE_UNKNOWN; SectionTypeInt < NO_OF_SECTION_TYPES; SectionTypeInt++)
	{
		if (SectionList[SectionTypeInt].size() > LastSectionCount [SectionTypeInt])
		{
			std::vector<std::shared_ptr<section>>::iterator SectionIterator;
			std::vector<std::shared_ptr<section>> SectionVector = SectionList[SectionTypeInt];
			for(SectionIterator = SectionVector.begin() + LastSectionCount [SectionTypeInt]; SectionIterator != SectionVector.end(); ++SectionIterator)
			{
				std::static_pointer_cast<section>(*SectionIterator)->SetA3FileLandIds(LandId, LandId_Expanded);

#if DEBUG_ENABLED
std::cout << "SET_SECTION_LAND_IDS for " << GetNameFromSectionType((SECTION_TYPE) SectionTypeInt) << " at Pos: " << 
		std::setw(5) << (SectionIterator - SectionVector.begin()) << ", Land:::Expanded" << "\"" << LandId << "\":::" << "\"" << LandId_Expanded << "\"" << std::endl;
#endif

			} // for each section since the last update
		} // if have more sections than last time
	} // for each section type
} // SetSectionLandIds

static bool GetLandIdFromSectionList (A3_FILE_NAME_TYPE FileNameType, std::string& LandId, std::string& LandId_Expanded,
										std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	bool LandIdFound = false;
	std::stringstream ErrorText;
	switch (FileNameType)
	{
	case A3_FILE_NAME_BONUS1:
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
		// Look in the Last Land Created
		LandId = std::static_pointer_cast<land>(SectionList[SECTION_TYPE_LAND].back())->GetValueAtSectionPos(LAND_SECTION_POS_LAND_ID);
		LandId_Expanded = std::static_pointer_cast<land>(SectionList[SECTION_TYPE_LAND].back())->GetValueAtSectionPos(LAND_SECTION_POS_LAND_ID_EXPANDED);
		LandIdFound = true;
		break;

	// Entries which Just don't have any meaning of Land for the File
	case A3_FILE_NAME_LAENDER:
	case A3_FILE_NAME_AVEREINE:
	case A3_FILE_NAME_CLEAGUE:
	case A3_FILE_NAME_FANGESA:
	case A3_FILE_NAME_FANWAVES:
	case A3_FILE_NAME_INTERNAT: // This does have multiple Laender so not 1 specific 1
	case A3_FILE_NAME_ISCHIRIS:
	case A3_FILE_NAME_KLEINIG:
	case A3_FILE_NAME_SONSPIEL:
	case A3_FILE_NAME_EXSPIEL:
	case A3_FILE_NAME_EMWM:
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
		LandIdFound = false;;
		break;

    // Entries which Cannot Find the Land by itself
	case A3_FILE_NAME_LIGA1BON:
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
		ErrorText << "FileNameType: " << FileNameType << " (" << GetNameFromA3FileNameType(FileNameType) << ") Cannot identify the Land -> " <<__FUNCTION__;
		programError(ErrorText.str());
		break;

	default:
		ErrorText << "Unexpected FileNameType: " << FileNameType << " (" << GetNameFromA3FileNameType(FileNameType) << ") -> " <<__FUNCTION__;
		programError(ErrorText.str());
	} // switch filenametype

	return (LandIdFound);
} // GetLandIdFromSectionList


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// FIELD MANIPULATION FUNCTIONS ////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void PostSavExpandDecodedFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	// Section Type Specific Processing
	for (int SectionType = 0; SectionType < NO_OF_SECTION_TYPES; SectionType++)
	{
		if (SectionList [SectionType].size() > LastSectionCount [SectionType])
		{
			switch (SectionType)
			{
			case SECTION_TYPE_IVEREIN:
				T_DecodeAllFieldsFromA3Db<iverein>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_SCHIRI:
				T_DecodeAllFieldsFromA3Db<schiri>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_AJUGEND:
				T_DecodeAllFieldsFromA3Db<ajugend>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_PROMI:
				T_DecodeAllFieldsFromA3Db<promi>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN:
				T_DecodeAllFieldsFromA3Db<spielplan_verein>(SectionType, SectionList, LastSectionCount);

				// Once Spielplan is decoded can decode SPIEL
				ConvertAllSpielTeams (SectionList, SPIEL_VEREIN_CONVERT_TO_STRING);
				break;

			case SECTION_TYPE_TURNIERGRP:
				T_DecodeAllFieldsFromA3Db<turniergrp>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_VEREIN:
				T_DecodeAllFieldsFromA3Db<verein>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_SPIELER:
				T_DecodeAllFieldsFromA3Db<spieler>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_CLEAGUEGRP:
				T_DecodeAllFieldsFromA3Db<cleaguegrp>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_LAND:
				T_DecodeAllFieldsFromA3Db<land>(SectionType, SectionList, LastSectionCount);
				break;

			default:
				break;
			} // switch section type
		} // if section updated
	} // for each section
} // PostSavExpandDecodedFields

static void PostExternalEncodeExpandedFields (FIELD_REFERENCE_TYPE ReferenceType, 
	std::vector<std::shared_ptr<section>> SectionList[NO_OF_SECTION_TYPES], size_t LastSectionCount[NO_OF_SECTION_TYPES], bool ShouldAutogenerateFixtures)
{
	// Section Type Specific Processing
	for (int SectionType = 0; SectionType < NO_OF_SECTION_TYPES; SectionType++)
	{
		if (SectionList [SectionType].size() > LastSectionCount [SectionType])
		{
			switch (SectionType)
			{
			case SECTION_TYPE_IVEREIN:
				T_EncodeAllFieldsToA3Db<iverein>(ReferenceType, SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_SCHIRI:
				T_EncodeAllFieldsToA3Db<schiri>(ReferenceType, SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_AJUGEND:
				T_EncodeAllFieldsToA3Db<ajugend>(ReferenceType, SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_PROMI:
				T_EncodeAllFieldsToA3Db<promi>(ReferenceType, SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN:
				T_EncodeAllFieldsToA3Db<spielplan_verein>(ReferenceType, SectionType, SectionList, LastSectionCount);

				// Once Spielplan is decoded can decode SPIEL for Verein Values
				if (ReferenceType == FIELD_REFERENCE_VEREIN)
				{
					ConvertAllSpielTeams (SectionList, SPIEL_VEREIN_CONVERT_FROM_STRING);

					// if option choosen autoenerate fixtures
					if (ShouldAutogenerateFixtures)
						AutogenerateFixtures (SectionList);
				}

				break;

			case SECTION_TYPE_TURNIERGRP:
				T_EncodeAllFieldsToA3Db<turniergrp>(ReferenceType, SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_VEREIN:
				T_EncodeAllFieldsToA3Db<verein>(ReferenceType, SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_SPIELER:
				T_EncodeAllFieldsToA3Db<spieler>(ReferenceType, SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_CLEAGUEGRP:
				T_EncodeAllFieldsToA3Db<cleaguegrp>(ReferenceType, SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_LAND:
				T_EncodeAllFieldsToA3Db<land>(ReferenceType, SectionType, SectionList, LastSectionCount);
				break;

			default:
				break;
			} // switch section type
		} // if section updated
	} // for each section
} // PostExternalEncodeExpandedFields

static void PostSavSplitCombinedFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	// Section Type Specific Processing
	for (int SectionType = 0; SectionType < NO_OF_SECTION_TYPES; SectionType++)
	{
		if (SectionList [SectionType].size() > LastSectionCount [SectionType])
		{
			switch (SectionType)
			{
			case SECTION_TYPE_SPIELER:
				T_SplitAllFieldsFromA3Db<spieler>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_VEREIN:
				T_SplitAllFieldsFromA3Db<verein>(SectionType, SectionList, LastSectionCount);
				break;

			default:
				break;
			} // switch section type
		} // if section updated
	} // for each section
} // PostSavSplitCombinedFields

static void PostExternalMergeSplitFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	// Section Type Specific Processing
	for (int SectionType = 0; SectionType < NO_OF_SECTION_TYPES; SectionType++)
	{
		if (SectionList [SectionType].size() > LastSectionCount [SectionType])
		{
			switch (SectionType)
			{
			case SECTION_TYPE_SPIELER:
				T_MergeAllFieldsToA3Db<spieler>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_VEREIN:
				T_MergeAllFieldsToA3Db<verein>(SectionType, SectionList, LastSectionCount);
				break;

			default:
				break;
			} // switch section type
		} // if section updated
	} // for each section
} // PostExternalMergeSplitFields

static void PostSavExpandBitmaskFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	// Section Type Specific Processing
	for (int SectionType = 0; SectionType < NO_OF_SECTION_TYPES; SectionType++)
	{
		if (SectionList [SectionType].size() > LastSectionCount [SectionType])
		{
			switch (SectionType)
			{
			case SECTION_TYPE_SPIELER:
				T_SplitAllBitmaskieldsFromA3Db<spieler>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_STADION:
				T_SplitAllBitmaskieldsFromA3Db<stadion>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_SCHIRI:
				T_SplitAllBitmaskieldsFromA3Db<schiri>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_ISCHIRI:
				T_SplitAllBitmaskieldsFromA3Db<ischiri>(SectionType, SectionList, LastSectionCount);
				break;

			default:
				break;
			} // switch section type
		} // if section updated
	} // for each section
} // PostSavExpandBitmaskFields

static void PostExternalCombineBitmaskFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	// Section Type Specific Processing
	for (int SectionType = 0; SectionType < NO_OF_SECTION_TYPES; SectionType++)
	{
		if (SectionList [SectionType].size() > LastSectionCount [SectionType])
		{
			switch (SectionType)
			{
			case SECTION_TYPE_SPIELER:
				T_MergeAllBitmaskieldsFromA3Db<spieler>(SectionType, SectionList, LastSectionCount);
				break;				

			case SECTION_TYPE_STADION:
				T_MergeAllBitmaskieldsFromA3Db<stadion>(SectionType, SectionList, LastSectionCount);
				break;				

			case SECTION_TYPE_SCHIRI:
				T_MergeAllBitmaskieldsFromA3Db<schiri>(SectionType, SectionList, LastSectionCount);
				break;				

			case SECTION_TYPE_ISCHIRI:
				T_MergeAllBitmaskieldsFromA3Db<ischiri>(SectionType, SectionList, LastSectionCount);
				break;

			default:
				break;
			} // switch section type
		} // if section updated
	} // for each section
} // PostExternalCombineBitmaskFields

static void PostSavConvertBooleansToText (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	// Section Type Specific Processing
	for (int SectionType = 0; SectionType < NO_OF_SECTION_TYPES; SectionType++)
	{
		if (SectionList [SectionType].size() > LastSectionCount [SectionType])
		{
			switch (SectionType)
			{
			case SECTION_TYPE_VEREIN:
				T_DecodeAllBooleansFromA3Db<verein>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_SPIELER:
				T_DecodeAllBooleansFromA3Db<spieler>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_SCHIRI:
				T_DecodeAllBooleansFromA3Db<schiri>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_ISCHIRI:
				T_DecodeAllBooleansFromA3Db<ischiri>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_STADION:
				T_DecodeAllBooleansFromA3Db<stadion>(SectionType, SectionList, LastSectionCount);
				break;

			default:
				break;
			} // switch section type
		} // if section updated
	} // for each section
} // PostSavConvertBooleansToText

static void PostExternalConvertBooleansFromText (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	// Section Type Specific Processing
	for (int SectionType = 0; SectionType < NO_OF_SECTION_TYPES; SectionType++)
	{
		if (SectionList [SectionType].size() > LastSectionCount [SectionType])
		{
			switch (SectionType)
			{
			case SECTION_TYPE_VEREIN:
				T_EncodeAllBooleansToA3Db<verein>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_SPIELER:
				T_EncodeAllBooleansToA3Db<spieler>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_SCHIRI:
				T_EncodeAllBooleansToA3Db<schiri>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_ISCHIRI:
				T_EncodeAllBooleansToA3Db<ischiri>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_STADION:
				T_EncodeAllBooleansToA3Db<stadion>(SectionType, SectionList, LastSectionCount);
				break;

			default:
				break;
			} // switch section type
		} // if section updated
	} // for each section
} // PostExternalConvertBooleansFromText

static void PostSavDecodeEnumFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	// Section Type Specific Processing
	for (int SectionType = 0; SectionType < NO_OF_SECTION_TYPES; SectionType++)
	{
		if (SectionList [SectionType].size() > LastSectionCount [SectionType])
		{
			switch (SectionType)
			{
			case SECTION_TYPE_STADION:
				T_DecodeAllEnumsFromA3Db<stadion>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_VEREIN:
				T_DecodeAllEnumsFromA3Db<verein>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_SPIELER:
				T_DecodeAllEnumsFromA3Db<spieler>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_TRAINER:
				T_DecodeAllEnumsFromA3Db<trainer>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_AJUGEND:
				T_DecodeAllEnumsFromA3Db<ajugend>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_REPORTER:
				T_DecodeAllEnumsFromA3Db<reporter>(SectionType, SectionList, LastSectionCount);
				break;

			default:
				break;
			} // switch section type
		} // if section updated
	} // for each section
} // PostSavDecodeEnumFields

static void PostExternalEncodeEnumFields (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	// Section Type Specific Processing
	for (int SectionType = 0; SectionType < NO_OF_SECTION_TYPES; SectionType++)
	{
		if (SectionList [SectionType].size() > LastSectionCount [SectionType])
		{
			switch (SectionType)
			{
			case SECTION_TYPE_STADION:
				T_EncodeAllEnumsToA3Db<stadion>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_VEREIN:
				T_EncodeAllEnumsToA3Db<verein>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_SPIELER:
				T_EncodeAllEnumsToA3Db<spieler>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_TRAINER:
				T_EncodeAllEnumsToA3Db<trainer>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_AJUGEND:
				T_EncodeAllEnumsToA3Db<ajugend>(SectionType, SectionList, LastSectionCount);
				break;

			case SECTION_TYPE_REPORTER:
				T_EncodeAllEnumsToA3Db<reporter>(SectionType, SectionList, LastSectionCount);
				break;

			default:
				break;
			} // switch section type
		} // if section updated
	} // for each section
} // PostExternalEncodeEnumFields

static size_t GetSectionAllowedValues (SECTION_TYPE SectionType, std::vector<FIELD_VALUE_STRUCT>& AllowedValues)
{
	// Fill the list
	switch (SectionType)
	{
	case SECTION_TYPE_SPIELER:
		GetSpielerAllowedValues (AllowedValues);
		break;

	case SECTION_TYPE_VEREIN:
		GetVereinAllowedValues (AllowedValues);
		break;

	case SECTION_TYPE_STADION:
		GetStadionAllowedValues (AllowedValues);
		break;

	case SECTION_TYPE_SCHIRI:
		GetSchiriAllowedValues (AllowedValues);
		break;

	case SECTION_TYPE_ISCHIRI:
		GetISchiriAllowedValues (AllowedValues);
		break;

	case SECTION_TYPE_AJUGEND:
		GetAJugendAllowedValues (AllowedValues);
		break;

	case SECTION_TYPE_REPORTER:
		GetReporterAllowedValues (AllowedValues);
		break;

	case SECTION_TYPE_TRAINER:
		GetTrainerAllowedValues (AllowedValues);
		break;

	default:
		break;
	} // switch section types

	return (AllowedValues.size());
} // GetSectionAllowedValues

static void PrintSectionAllowedValues (SECTION_TYPE SectionType, const std::vector<FIELD_VALUE_STRUCT>& AllowedValues)
{
	// Print Header
	showTextMsg("=============================");

	// Print Section Type
	showTextMsg(GetNameFromSectionType(SectionType));

	// Print Section Fields
	std::vector<FIELD_VALUE_STRUCT>::const_iterator FieldIter;
	for(FieldIter = AllowedValues.begin(); FieldIter != AllowedValues.end(); ++FieldIter)
	{
		// Print Field Value
		showTextMsg(std::string("  ") + (*FieldIter).EnumNameString);

		// Print each Allowed Value
		std::vector<std::string>::iterator ValueIterator;
		std::vector<std::string> ValueList = (*FieldIter).AllowedValueList;
		for (ValueIterator = ValueList.begin(); ValueIterator != ValueList.end(); ++ValueIterator)
		{
			// Print Value
			showTextMsg(std::string("    ") + (*ValueIterator));
		} // For Each Value
	} // for each Field

} // PrintSectionAllowedValues

void PrintSectionFieldAllowedValues ()
{
	std::vector<FIELD_VALUE_STRUCT> AllowedValues;
	
	std::vector<std::vector<std::string>> MatrixList (NO_OF_SECTION_TYPES);
	for (int SectionInt = SECTION_TYPE_UNKNOWN + 1; SectionInt < NO_OF_SECTION_TYPES; SectionInt++)
	{
		// Clear the List for the Next one
		AllowedValues.clear();

		// Get and print allowed values
		if (GetSectionAllowedValues((SECTION_TYPE) SectionInt, AllowedValues) > 0)
		{
			// Print Section Values
			PrintSectionAllowedValues((SECTION_TYPE) SectionInt, AllowedValues);

			if(AllowedValues.size() > 0)
			{
				std::string MatrixArray [MAX_ALLOWED_FIELD_VALUES][NO_OF_SECTION_TYPES];

				for (int Row = 0; Row < MAX_ALLOWED_FIELD_VALUES; Row++)
					for (int Col = 0; Col < NO_OF_SECTION_TYPES; Col++)
						MatrixArray[Row][Col] = "";

				int RowCount = 0;
				int MaxRow = 0;
				int ColCount = 0;

				// Build up Matrix
				std::vector<FIELD_VALUE_STRUCT>::iterator ValueIter;
				for(ValueIter = AllowedValues.begin(); ValueIter != AllowedValues.end(); ++ValueIter)
				{
					RowCount = 0;
					// Create a Column
					std::vector<std::string> Column;

					// Add a column header
					Column.push_back((*ValueIter).EnumNameString);
					MatrixArray[RowCount++][ColCount] = (*ValueIter).EnumNameString;

					// Allow the Values
					std::vector<std::string>::iterator AllowedValueIter;
					for(AllowedValueIter = (*ValueIter).AllowedValueList.begin(); 
							AllowedValueIter != (*ValueIter).AllowedValueList.end(); 
								++AllowedValueIter)
					{
						Column.push_back(*AllowedValueIter);
						MatrixArray[RowCount++][ColCount] = *AllowedValueIter;
					} // for each allowed value

					// Add the List
					MatrixList.push_back(Column);

					if (RowCount > MaxRow)
						MaxRow = RowCount;
					ColCount++;
				} // for each value

				// Print the List to XML
				WriteAllowedValueList ((SECTION_TYPE) SectionInt, MatrixArray, ColCount, MaxRow);
			} // if have something
		} // if found some values	
	} // for each section
} // PrintSectionFieldAllowedValues
