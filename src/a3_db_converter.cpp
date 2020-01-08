#include "a3_db_converter.h"

#include <fstream>
#include <sstream>
#include <memory>
#include <iostream>

#include "a3_ui_text.h"
#include "value_pair.h"
#include "xml_io.h"
#include "error_handling.h"
#include "os_lib.h"
#include "sub_sections.h"

void WriteAllowedValueList (const SECTION_TYPE SectionType, const std::string MatrixArray [MAX_ALLOWED_FIELD_VALUES][NO_OF_SECTION_TYPES],
							const int MaxCol, const int MaxRow)
{
	// HEADER
	TiXmlDocument doc;  
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );  
	doc.LinkEndChild( decl );

	// SECTION CLASS
	TiXmlElement * root = new TiXmlElement((GetNameFromSectionType((SECTION_TYPE) SectionType) + std::string("_VALUES")).c_str() );  
	doc.LinkEndChild( root );  

	// Write the Data
	// Row 0 holds the header data
	for (int Row = 1; Row < MaxRow; Row++)
	{
		std::vector<std::shared_ptr<value_pair>> ValuesValuePairs;
		for (int Col = 0; Col < MaxCol; Col++)
		{
			std::string ElementName = MatrixArray [0][Col];
			std::string Value = MatrixArray [Row][Col];
			if (Value.size() > 0)
			{
				ValuesValuePairs.push_back(std::shared_ptr<value_pair> (new value_pair(ElementName, MatrixArray [Row][Col])));
			} // if have a row value
		} // for each column

		// Write to XML
		WriteA3XmlData(root, std::string ("VALUE_LINE"), ValuesValuePairs);
	} // for each row

	// Write the File
	doc.SaveFile(GetA3StorageFileName(std::string("ERLAUBTE_WERTE") + std::string("_") + GetNameFromSectionType (SectionType)).c_str());
		
} // WriteAllowedValueList

void WriteA3DbExternalFile (const std::string& BaseFileName, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES],
							size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	showTextMsg("  Schreibe Daten zu XML");
	
	// Ensure Output directory exists
	EnsureDirectoryExists(XML_STORAGE_DIR);

	for (int SectionInt = SECTION_TYPE_UNKNOWN + 1; SectionInt < NO_OF_SECTION_TYPES; SectionInt++)
	{
		if (SectionList [SectionInt].size() > LastSectionCount [SectionInt])
		{
			// HEADER
			TiXmlDocument doc;  
			TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );  
			doc.LinkEndChild( decl );

			// SECTION CLASS
			TiXmlElement * root = new TiXmlElement( (GetNameFromSectionType((SECTION_TYPE) SectionInt) + std::string("_LIST")).c_str() );  
			doc.LinkEndChild( root );  

			std::vector<std::shared_ptr<section>>::iterator Iterator;
			std::vector<std::shared_ptr<section>> SectionVector = SectionList[SectionInt];
			for(Iterator = SectionVector.begin() + LastSectionCount [SectionInt]; Iterator != SectionVector.end(); ++Iterator)
			{
				std::vector<std::shared_ptr<value_pair>> ObjectValuePairs;

				// Convert Vector to Value Pair Vector
				PopulateValuePairsFromSection ((SECTION_TYPE) SectionInt, Iterator, ObjectValuePairs, BaseFileName);

				WriteA3XmlData(root, GetNameFromSectionType((SECTION_TYPE) SectionInt), ObjectValuePairs);
				//WriteA3Data (FileHandle, ObjectValuePairs, ObjectWriteCount);
			} // for each item in vector

			doc.SaveFile( FormXmlStorageName (BaseFileName, (SECTION_TYPE) SectionInt).c_str() );  
		} // if something written since last time 
	} // for each section type

} // WriteA3DbExternalFile

bool ReadA3DbExternalFile (const std::string& BaseFileName, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES])
{
	bool ImportOkForFile = true;
	bool RequiredSectionList [NO_OF_SECTION_TYPES] = {false};
	int  NoOfExternalFilesRead = 0;
	GetSectionsRequiredForFile (BaseFileName, SECTION_TYPE_UNKNOWN, RequiredSectionList, true, true);

	for (int SectionInt = SECTION_TYPE_UNKNOWN + 1; SectionInt < NO_OF_SECTION_TYPES; SectionInt++)
	{
		std::string FileName (FormXmlStorageName (BaseFileName, (SECTION_TYPE) SectionInt));

		TiXmlDocument XMLdoc(FileName.c_str());
		bool loadOkay = XMLdoc.LoadFile();
		if (loadOkay)
		{
			NoOfExternalFilesRead++;

			showTextMsg(std::string("  Lese XML fuer ") + FileName);
		
			// Tick of file as found
			RequiredSectionList [SectionInt] = false;

			std::vector<std::shared_ptr<value_pair>> ObjectValuePairs;
			std::string	Line;

			TiXmlElement *pRoot;
			std::string ElementName (GetNameFromSectionType((SECTION_TYPE) SectionInt));
			pRoot = XMLdoc.FirstChildElement((ElementName + std::string("_LIST")).c_str());

			TiXmlElement *pParm;
			pParm = pRoot->FirstChildElement(ElementName.c_str());

#if DEBUG_ENABLED
std::cout << "  - Reading FIRST Element: \"" << ElementName.c_str() << "\"" << std::endl;
#endif

//std::cout << " Reading First Child '" << ElementName.c_str() << "'" << std::endl;
			while(pParm)
			{
				// Clear the Vector
				ObjectValuePairs.erase (ObjectValuePairs.begin(), ObjectValuePairs.end());

// TODO, maybe pass a list of expected attributes

//std::cout << "  ReadA3XmlData" << std::endl;
#if DEBUG_ENABLED
std::cout << "  - Reading XML Data into Value Pairs, prev Size = " << ObjectValuePairs.size() << std::endl;
#endif
				ReadA3XmlData(pParm, ObjectValuePairs);

#if DEBUG_ENABLED
std::cout << "  - Read " <<  ObjectValuePairs.size() << " Value Pairs" << std::endl;
PrintValuePairs (ObjectValuePairs);
#endif

//std::cout << "  PopulateSectionFromValuePairs" << std::endl;
				PopulateSectionFromValuePairs ((SECTION_TYPE) SectionInt, SectionList [SectionInt], ObjectValuePairs);
//std::cout << "  PairsFound: " << ObjectValuePairs.size() << std::endl;

				pParm = pParm->NextSiblingElement(ElementName.c_str());


#if DEBUG_ENABLED
				std::cout << "  - Reading NEXT Element: \"" << ElementName.c_str() << "\"" << std::endl;
#endif
			} // While More Sections
		} // if file loaded ok

//std::cout << "SECTION: " << GetNameFromSectionType((SECTION_TYPE) SectionInt) << ", COUNT: " << SectionList[SectionInt].size() << std::endl;
	} // for each section type

	// Check if anything read at all
	if (NoOfExternalFilesRead == 0)
		ImportOkForFile = false;

	// Check if any sections missing
	for (int i = 0; i < NO_OF_SECTION_TYPES; i++)
	{
		if (RequiredSectionList[i])
		{
			showTextMsg(std::string("  Datei nicht gefunden: ") + FormXmlStorageName (BaseFileName, (SECTION_TYPE) i));
			ImportOkForFile = false;
		} // if file still needed
	} // for each file required

	return (ImportOkForFile);
} // ReadA3DbExternalFile

static void PopulateValuePairsFromSection (SECTION_TYPE SectionType, std::vector<std::shared_ptr<section>>::iterator& SectionIter, 
											std::vector<std::shared_ptr<value_pair>>& ObjectValuePairs, const std::string& BaseFileName)
{
	switch (SectionType)
	{
	case SECTION_TYPE_LAND:
		std::static_pointer_cast<land>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_VEREIN:
		std::static_pointer_cast<verein>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_SPIELER:
		std::static_pointer_cast<spieler>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs, BaseFileName);
		break;

	case SECTION_TYPE_MANAGER:
		std::static_pointer_cast<manager>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_IVEREIN:
		std::static_pointer_cast<iverein>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_TRAINER:
		std::static_pointer_cast<trainer>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_STADION:
		std::static_pointer_cast<stadion>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_AMATEURV:
		std::static_pointer_cast<amateurv>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_AJUGEND:
		std::static_pointer_cast<ajugend>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_TWTRAINER:
		std::static_pointer_cast<twtrainer>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_SCHIRI:
		std::static_pointer_cast<schiri>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_SPONSOR:
		std::static_pointer_cast<sponsor>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_PROMI:
		std::static_pointer_cast<promi>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_REPORTER:
		std::static_pointer_cast<reporter>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_KRITIKER:
		std::static_pointer_cast<kritiker>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_VPRAESID:
		std::static_pointer_cast<vpraesid>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_ASPIELER:
		std::static_pointer_cast<aspieler>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_ISCHIRI:
		std::static_pointer_cast<ischiri>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_EUROSIEGER:
		std::static_pointer_cast<eurosieger>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_NATION:
		std::static_pointer_cast<nation>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_CLEAGUEGRP:
		std::static_pointer_cast<cleaguegrp>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_TURNIERGRP:
		std::static_pointer_cast<turniergrp>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_SPIEL_HIDDEN:
		std::static_pointer_cast<spiel>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_LIGA:
		std::static_pointer_cast<liga>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	case SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN:
		std::static_pointer_cast<spielplan_verein>(*SectionIter)->PopulateValuePairVectorForExport (ObjectValuePairs);
		break;

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Section Type: " << SectionType << ": " << GetNameFromSectionType(SectionType) << " -> " << __FILE__ << ":" << __FUNCTION__;
		programError (ErrorText.str());	
	}
} // PopulateValuePairsFromSection

static void PopulateSectionFromValuePairs (SECTION_TYPE SectionType, std::vector<std::shared_ptr<section>>& SectionList, 
											std::vector<std::shared_ptr<value_pair>>& ObjectValuePairs)
{
	switch (SectionType)
	{		

	case SECTION_TYPE_LAND:
		SectionList.push_back (std::shared_ptr<land> (new land()));
		std::static_pointer_cast<land> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;

	case SECTION_TYPE_VEREIN:
		SectionList.push_back (std::shared_ptr<verein> (new verein()));
		std::static_pointer_cast<verein> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;

	case SECTION_TYPE_SPIELER:
		SectionList.push_back (std::shared_ptr<spieler> (new spieler()));
		std::static_pointer_cast<spieler> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_MANAGER:
		SectionList.push_back (std::shared_ptr<manager> (new manager()));
		std::static_pointer_cast<manager> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;		

	case SECTION_TYPE_CLEAGUEGRP:
		SectionList.push_back (std::shared_ptr<cleaguegrp> (new cleaguegrp()));
		std::static_pointer_cast<cleaguegrp> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;

	case SECTION_TYPE_IVEREIN:
		SectionList.push_back (std::shared_ptr<iverein> (new iverein()));
		std::static_pointer_cast<iverein> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_TRAINER:
		SectionList.push_back (std::shared_ptr<trainer> (new trainer()));
		std::static_pointer_cast<trainer> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_STADION:
		SectionList.push_back (std::shared_ptr<stadion> (new stadion()));
		std::static_pointer_cast<stadion> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_AMATEURV:
		SectionList.push_back (std::shared_ptr<amateurv> (new amateurv()));
		std::static_pointer_cast<amateurv> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_AJUGEND:
		SectionList.push_back (std::shared_ptr<ajugend> (new ajugend()));
		std::static_pointer_cast<ajugend> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_TWTRAINER:
		SectionList.push_back (std::shared_ptr<twtrainer> (new twtrainer()));
		std::static_pointer_cast<twtrainer> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_SCHIRI:
		SectionList.push_back (std::shared_ptr<schiri> (new schiri()));
		std::static_pointer_cast<schiri> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_SPONSOR:
		SectionList.push_back (std::shared_ptr<sponsor> (new sponsor()));
		std::static_pointer_cast<sponsor> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_PROMI:
		SectionList.push_back (std::shared_ptr<promi> (new promi()));
		std::static_pointer_cast<promi> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_REPORTER:
		SectionList.push_back (std::shared_ptr<reporter> (new reporter()));
		std::static_pointer_cast<reporter> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_KRITIKER:
		SectionList.push_back (std::shared_ptr<kritiker> (new kritiker()));
		std::static_pointer_cast<kritiker> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_VPRAESID:
		SectionList.push_back (std::shared_ptr<vpraesid> (new vpraesid()));
		std::static_pointer_cast<vpraesid> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_ASPIELER:
		SectionList.push_back (std::shared_ptr<aspieler> (new aspieler()));
		std::static_pointer_cast<aspieler> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_EUROSIEGER:
		SectionList.push_back (std::shared_ptr<eurosieger> (new eurosieger()));
		std::static_pointer_cast<eurosieger> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_ISCHIRI:
		SectionList.push_back (std::shared_ptr<ischiri> (new ischiri()));
		std::static_pointer_cast<ischiri> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_NATION:
		SectionList.push_back (std::shared_ptr<nation> (new nation()));
		std::static_pointer_cast<nation> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_TURNIERGRP:
		SectionList.push_back (std::shared_ptr<turniergrp> (new turniergrp()));
		std::static_pointer_cast<turniergrp> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_SPIEL_HIDDEN:
		SectionList.push_back (std::shared_ptr<spiel> (new spiel()));
		std::static_pointer_cast<spiel> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_LIGA:
		SectionList.push_back (std::shared_ptr<liga> (new liga()));
		std::static_pointer_cast<liga> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	case SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN:
		SectionList.push_back (std::shared_ptr<spielplan_verein> (new spielplan_verein()));
		std::static_pointer_cast<spielplan_verein> (SectionList.back())->PopulateFromValuePairs(ObjectValuePairs);
		break;	

	default:
		std::stringstream ErrorText;
		ErrorText << "Unexpected Section Type: " << SectionType << ": " << GetNameFromSectionType(SectionType) << " -> " << __FILE__ << ":" <<__FUNCTION__;
		programError (ErrorText.str());	
	}
	
} // PopulateSectionFromValuePairs

static std::string FormXmlStorageName (const std::string& BaseFileName, SECTION_TYPE SectionType)
{
	return (std::string(XML_STORAGE_DIR) + GetA3StorageFileName(BaseFileName + std::string("_") + GetNameFromSectionType (SectionType)));
} // FormCsvFileName
