#pragma once

#include <string>
#include <vector>
#include <memory>
#include "value_pair.h"
#include "misc_lib.h"
#include "bimap.h"

#define XML_PARENT_SECTION_STRING	"PARENT_SECTION"

typedef enum
{
	SECTION_TYPE_UNKNOWN,
	SECTION_TYPE_LAND,
	SECTION_TYPE_VEREIN,
	SECTION_TYPE_IVEREIN,
	SECTION_TYPE_SPIELER,
	SECTION_TYPE_AJUGEND,
	SECTION_TYPE_AMATEURV,
	SECTION_TYPE_KRITIKER,
	SECTION_TYPE_KRITIP,
	SECTION_TYPE_MANAGER,
	SECTION_TYPE_MANAGERP,
	SECTION_TYPE_MEDIAP,
	SECTION_TYPE_PROMI,
	SECTION_TYPE_PROMIP,
	SECTION_TYPE_REPORTER,
	SECTION_TYPE_SCHIRI,
	SECTION_TYPE_SCHIRIP,
	SECTION_TYPE_SPONSOR,
	SECTION_TYPE_SPONSORP,
	SECTION_TYPE_STADION,
	SECTION_TYPE_TRAINER,
	SECTION_TYPE_TRAINERP,
	SECTION_TYPE_TWTRAINER,
	SECTION_TYPE_TWTRAINP,
	SECTION_TYPE_VPRAESID,
	SECTION_TYPE_ASPIELER,
	SECTION_TYPE_AUSRUESTER,
	SECTION_TYPE_BONUS,
	SECTION_TYPE_CLEAGUE,
	SECTION_TYPE_CLEAGUEGRP,
	SECTION_TYPE_EFANGES,
	SECTION_TYPE_EMGRP,
	SECTION_TYPE_EMWM,
	SECTION_TYPE_EUROSIEGER,
	SECTION_TYPE_EXSPIEL,
	SECTION_TYPE_FANGES,
	SECTION_TYPE_HALBZEIT,
	SECTION_TYPE_ISCHIRI,
	SECTION_TYPE_IVEREINE,
	SECTION_TYPE_LIGA,
	SECTION_TYPE_MISC,
	SECTION_TYPE_NATION,
	SECTION_TYPE_QUIZ,
	SECTION_TYPE_SONSPIELER,
	SECTION_TYPE_TURNIERGRP,
	SECTION_TYPE_UEFA,
	SECTION_TYPE_WMGRP,

	// Special Sections, not directly as such in file
	SECTION_TYPE_VEREIN_HIDDEN, // Hidden Verein Fields, not directly after opening of VEREIN but when no other section open
	SECTION_TYPE_SPIELER_HIDDEN, // Hidden Spieler Fields, in some files, follow up section
	SECTION_TYPE_AJUGEND_HIDDEN, // multiple entries in AJUGEND section
	SECTION_TYPE_ASPIELER_HIDDEN, // multiple entries in ASPIELER section
	SECTION_TYPE_INTERNAT_VEREIN, // Same as VEREIN but parent LAND different, but need to set field in parent
	SECTION_TYPE_EUROSIEGER_HIDDEN, // multiple entries in EUROSIEGER section
	SECTION_TYPE_ISCHIRI_HIDDEN, // hidden, multiple entries in ISCHIRI section
	SECTION_TYPE_SPIEL_HIDDEN, // Also Hidden, but not hidden of a Main Section
	SECTION_TYPE_SPIELPLAN_VEREIN_HIDDEN,
	NO_OF_SECTION_TYPES
} SECTION_TYPE;

typedef enum
{
	FIELD_REFERENCE_UNKNOWN,
	FIELD_REFERENCE_LAND,
	FIELD_REFERENCE_VEREIN,
	NO_OF_FIELD_REFERENCE_TYPES
} FIELD_REFERENCE_TYPE;

typedef enum
{
	SECTION_EXPANSION_UNKNOWN,
	SECTION_EXPANSION_FROM_A3DB_LAND,
	SECTION_EXPANSION_TO_A3DB_LAND,
	SECTION_EXPANSION_FROM_A3DB_VEREIN,
	SECTION_EXPANSION_TO_A3DB_VEREIN,
	NO_OF_SECTION_EXPANSION_TYPES
} SECTION_EXPANSION_TYPE;

class section
{
public:
	section(void);
	~section(void);

	std::string ParentId;
	std::string A3FileLand;
	std::string A3FileLand_Expanded;

	virtual void PopulateValuePairVectorForExport (std::vector<std::shared_ptr<value_pair>>&) = 0;
	virtual void PopulateFromValuePairs (const std::vector<std::shared_ptr<value_pair>>&) = 0;
	virtual void AddFieldsToA3DbList (std::vector<std::string>&, SECTION_TYPE, const std::string&) = 0;
	virtual void AssignField (int, const std::string&) = 0;
	virtual std::string GetUniqueId () = 0;
	virtual SECTION_TYPE GetSectionType () = 0;
	virtual std::string GetValueAtSectionPos (int) = 0;
	virtual void GetGenericSplitFieldsForField (int, std::vector<int>&);
	virtual bool GetBooleanTargetFieldForEnumVal (const int, const int, int&);
	virtual void SplitJoinedField (const std::string&, ENUM_VALUE_LIST&, int, int);
	virtual void MergeSplitField (int);
	virtual void SplitBitmaskField (int, ENUM_VALUE_LIST&);
	virtual void MergeBitmaskField (int, ENUM_VALUE_LIST&);
	virtual void DecodeBooleanFromA3Db (int);
	virtual void EncodeBooleanToA3Db (int, int);
	virtual void InitializeFields (const std::vector<int>&, const std::string&);

	std::string GetParentId();
	void SetParentId (std::string);
	bool SectionParentMatchesString (const std::string&);
	bool SectionMatchesParent (section*);
	bool SectionMatchesParent (SECTION_TYPE);
	int GetMatchingSectionsFromList (std::vector<std::shared_ptr<section>>&);
	void ConvertLandField (SECTION_EXPANSION_TYPE, int, int, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void ConvertVereinField (SECTION_EXPANSION_TYPE, int, int, const std::string&, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
	void SetA3FileLandIds (const std::string&, const std::string&);
	std::string GetA3FileLandId ();
	std::string GetA3FileLandId_Expanded ();
	void SetA3LandIdsForMatchingSection(const std::string&, const std::string, std::vector<std::shared_ptr<section>>, size_t);
	void DecodeEnumFromA3Db (int, int, ENUM_MAP_LOOKUP_FUNC, ENUM_DETAILS_LOOKUP_FUNC);
	void EncodeEnumToA3Db (int, int, ENUM_MAP_LOOKUP_FUNC, ENUM_DETAILS_LOOKUP_FUNC);
};

bool StringIsSectionStart (const std::string);
bool StringIsSectionEnd (const std::string);
std::string FormSectionStart (SECTION_TYPE);
std::string FormSectionEnd (SECTION_TYPE);

const std::string GetSectionIdentifierFromSectionType (const SECTION_TYPE);
SECTION_TYPE GetSectionTypeFromString (const std::string);
const char* GetNameFromSectionType (const SECTION_TYPE);
const char* GetNameFromSectionExpansionType (const SECTION_EXPANSION_TYPE);
bool SectionContainsData (SECTION_TYPE);
void GetSubLevelSections (const std::string&, SECTION_TYPE, std::vector<SECTION_TYPE>&);
void GetFollowUpSections (const std::string&, SECTION_TYPE, std::vector<SECTION_TYPE>&);
bool SectionIsVisible (const SECTION_TYPE&);
std::string GetGenericParentIdentifier (SECTION_TYPE);
int GetNoOfFieldsInA3Section (SECTION_TYPE);
SECTION_TYPE GetHiddenSection (SECTION_TYPE, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
SECTION_TYPE GetDataSectionFromHiddenSection (SECTION_TYPE);
void GetSectionsRequiredForFile (const std::string&, SECTION_TYPE, bool [NO_OF_SECTION_TYPES], bool, bool);
bool SectionNeededForOtherSections (SECTION_TYPE);
bool SectionRequiresSection (SECTION_TYPE, SECTION_TYPE);
void PrintSectionListContent (SECTION_TYPE, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
static void GetEnumDetails (int, int, ENUM_FUNC&, int&, int&);

///////////////////////////////////////////
//// TEMPLATES ////////////////////////////
///////////////////////////////////////////

// Add a New Section
template<class TemplateClass> void T_AddNewSection(std::vector<std::shared_ptr<section>>& SectionList)
{
	SectionList.push_back (std::shared_ptr<TemplateClass> (new TemplateClass()));
} // T_CreateSection

// Assign a Section Field
template<class TemplateClass> void T_AssignSectionField(std::vector<std::shared_ptr<section>>& SectionList, int SectionLineCount, std::string& Line)
{
	std::static_pointer_cast<TemplateClass> (SectionList.back())->AssignField (SectionLineCount, Line);
} // T_AssignSectionField

// Decoding of Reference Fields
template<class TemplateClass> void T_DecodeAllFieldsFromA3Db(
	int SectionType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	std::vector<std::shared_ptr<section>> SectionVector = SectionList [SectionType];
	for(SectionIterator = SectionVector.begin() + LastSectionCount [SectionType]; SectionIterator != SectionVector.end(); ++SectionIterator)
	{
#if DEBUG_ENABLED
		std::cout << "DECODE Fields for Section: " << GetNameFromSectionType((*SectionIterator)->GetSectionType()) << 
			", ID: " << (*SectionIterator)->GetUniqueId() << " -> " << __FUNCTION__ << std::endl;
#endif
		std::static_pointer_cast<TemplateClass> (*SectionIterator)->DecodeFieldsFromA3Db(SectionList);
	} // for each section object
} // T_AssignSectionField

// Encoding of Reference fields
template<class TemplateClass> void T_EncodeAllFieldsToA3Db(
	FIELD_REFERENCE_TYPE ReferenceType, int SectionType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], 
	size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	std::vector<std::shared_ptr<section>> SectionVector = SectionList [SectionType];
	for(SectionIterator = SectionVector.begin() + LastSectionCount [SectionType]; SectionIterator != SectionVector.end(); ++SectionIterator)
	{
#if DEBUG_ENABLED
		std::cout << "ENCODE " << ReferenceType << ", Fields for Section: " << GetNameFromSectionType((*SectionIterator)->GetSectionType()) << 
			", ID: " << (*SectionIterator)->GetUniqueId() << " -> " << __FUNCTION__ << std::endl;
#endif
		std::static_pointer_cast<TemplateClass> (*SectionIterator)->EncodeFieldsToA3Db(ReferenceType, SectionList);
	} // for each section object
} // T_EncodeAllFieldsToA3Db

// Split Fields
template<class TemplateClass> void T_SplitAllFieldsFromA3Db(
	int SectionType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	std::vector<std::shared_ptr<section>> SectionVector = SectionList [SectionType];
	for(SectionIterator = SectionVector.begin() + LastSectionCount [SectionType]; SectionIterator != SectionVector.end(); ++SectionIterator)
	{
#if DEBUG_ENABLED
		std::cout << "DECODE Fields for Section: " << GetNameFromSectionType((*SectionIterator)->GetSectionType()) << 
			", ID: " << (*SectionIterator)->GetUniqueId() << " -> " << __FUNCTION__ << std::endl;
#endif
		std::static_pointer_cast<TemplateClass> (*SectionIterator)->PostSavSplitCombinedFields(SectionList);
	} // for each section object
} // T_SplitAllFieldsFromA3Db

// Merge Fields
template<class TemplateClass> void T_MergeAllFieldsToA3Db(
	int SectionType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	std::vector<std::shared_ptr<section>> SectionVector = SectionList [SectionType];
	for(SectionIterator = SectionVector.begin() + LastSectionCount [SectionType]; SectionIterator != SectionVector.end(); ++SectionIterator)
	{
#if DEBUG_ENABLED
		std::cout << "ENCODE Fields for Section: " << GetNameFromSectionType((*SectionIterator)->GetSectionType()) << 
			", ID: " << (*SectionIterator)->GetUniqueId() << " -> " << __FUNCTION__ << std::endl;
#endif
		std::static_pointer_cast<TemplateClass> (*SectionIterator)->PostExternalMergeSplitFields(SectionList);
	} // for each section object
} // T_MergeAllFieldsToA3Db

// Split Bitmask Fields
template<class TemplateClass> void T_SplitAllBitmaskieldsFromA3Db(
	int SectionType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	std::vector<std::shared_ptr<section>> SectionVector = SectionList [SectionType];
	for(SectionIterator = SectionVector.begin() + LastSectionCount [SectionType]; SectionIterator != SectionVector.end(); ++SectionIterator)
	{
#if DEBUG_ENABLED
		std::cout << "SPLIT Bitmask Fields for Section: " << GetNameFromSectionType((*SectionIterator)->GetSectionType()) << 
			", ID: " << (*SectionIterator)->GetUniqueId() << " -> " << __FUNCTION__ << std::endl;
#endif
		std::static_pointer_cast<TemplateClass> (*SectionIterator)->SplitBitmaskFields(SectionList);
	} // for each section object
} // T_SplitAllBitmaskieldsFromA3Db

// Merge Bitmask Fields
template<class TemplateClass> void T_MergeAllBitmaskieldsFromA3Db(
	int SectionType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	std::vector<std::shared_ptr<section>> SectionVector = SectionList [SectionType];
	for(SectionIterator = SectionVector.begin() + LastSectionCount [SectionType]; SectionIterator != SectionVector.end(); ++SectionIterator)
	{
#if DEBUG_ENABLED
		std::cout << "MERGE Bitmask Fields for Section: " << GetNameFromSectionType((*SectionIterator)->GetSectionType()) << 
			", ID: " << (*SectionIterator)->GetUniqueId() << " -> " << __FUNCTION__ << std::endl;
#endif
		std::static_pointer_cast<TemplateClass> (*SectionIterator)->MergeBitmaskFields(SectionList);
	} // for each section object
} // T_MergeAllBitmaskieldsFromA3Db

// Decoding of Boolean Fields
template<class TemplateClass> void T_DecodeAllBooleansFromA3Db(
	int SectionType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	std::vector<std::shared_ptr<section>> SectionVector = SectionList [SectionType];
	for(SectionIterator = SectionVector.begin() + LastSectionCount [SectionType]; SectionIterator != SectionVector.end(); ++SectionIterator)
	{
#if DEBUG_ENABLED
		std::cout << "DECODE Boolean for Section: " << GetNameFromSectionType((*SectionIterator)->GetSectionType()) << 
			", ID: " << (*SectionIterator)->GetUniqueId() << " -> " << __FUNCTION__ << std::endl;
#endif
		std::static_pointer_cast<TemplateClass> (*SectionIterator)->DecodeBooleansFromA3Db(SectionList);
	} // for each section object
} // T_DecodeAllBooleansFromA3Db

// Encoding of Boolean fields
template<class TemplateClass> void T_EncodeAllBooleansToA3Db(
	int SectionType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	std::vector<std::shared_ptr<section>> SectionVector = SectionList [SectionType];
	for(SectionIterator = SectionVector.begin() + LastSectionCount [SectionType]; SectionIterator != SectionVector.end(); ++SectionIterator)
	{
#if DEBUG_ENABLED
		std::cout << "ENCODE Boolean for Section: " << GetNameFromSectionType((*SectionIterator)->GetSectionType()) << 
			", ID: " << (*SectionIterator)->GetUniqueId() << " -> " << __FUNCTION__ << std::endl;
#endif
		std::static_pointer_cast<TemplateClass> (*SectionIterator)->EncodeBooleansToA3Db(SectionList);
	} // for each section object
} // T_EncodeAllBooleansToA3Db

// Expanding of Enum Fields
template<class TemplateClass> void T_DecodeAllEnumsFromA3Db(
	int SectionType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	std::vector<std::shared_ptr<section>> SectionVector = SectionList [SectionType];
	for(SectionIterator = SectionVector.begin() + LastSectionCount [SectionType]; SectionIterator != SectionVector.end(); ++SectionIterator)
	{
#if DEBUG_ENABLED
		std::cout << "DECODE Enums for Section: " << GetNameFromSectionType((*SectionIterator)->GetSectionType()) << 
			", ID: " << (*SectionIterator)->GetUniqueId() << " -> " << __FUNCTION__ << std::endl;
#endif
		std::static_pointer_cast<TemplateClass> (*SectionIterator)->DecodeEnumsFromA3Db(SectionList);
	} // for each section object
} // T_ExpandAllEnumsFromA3Db

// Encoding of Boolean fields
template<class TemplateClass> void T_EncodeAllEnumsToA3Db(
	int SectionType, std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES], size_t LastSectionCount [NO_OF_SECTION_TYPES])
{
	std::vector<std::shared_ptr<section>>::iterator SectionIterator;
	std::vector<std::shared_ptr<section>> SectionVector = SectionList [SectionType];
	for(SectionIterator = SectionVector.begin() + LastSectionCount [SectionType]; SectionIterator != SectionVector.end(); ++SectionIterator)
	{
#if DEBUG_ENABLED
		std::cout << "ENCODE Enums for Section: " << GetNameFromSectionType((*SectionIterator)->GetSectionType()) << 
			", ID: " << (*SectionIterator)->GetUniqueId() << " -> " << __FUNCTION__ << std::endl;
#endif
		std::static_pointer_cast<TemplateClass> (*SectionIterator)->EncodeEnumsToA3Db(SectionList);
	} // for each section object
} // T_EncodeAllEnumsToA3Db