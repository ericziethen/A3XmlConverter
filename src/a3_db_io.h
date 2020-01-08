#pragma once

#include <string>
#include <vector>
#include "section.h"
#include "a3_db_file_lib.h"

typedef struct {
	std::string		LandId;
	std::string		LandId_Expanded;
}FILE_LAND_ID_STRUCT;

void importA3DbFiles ();
static bool importFileFromA3Db (const std::string&, std::vector<std::shared_ptr<section>>[NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);
void exportA3DbFiles (bool);
static void UpdateLastSectionCount (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t[NO_OF_SECTION_TYPES]);
static void ResetSectionList (std::vector<std::shared_ptr<section>>[NO_OF_SECTION_TYPES], size_t[NO_OF_SECTION_TYPES], bool, size_t [NO_OF_SECTION_TYPES]);
static void InitializeLandIds (FILE_LAND_ID_STRUCT [NO_OF_A3_FILE_NAME_TYPES]);
static void SetFieldForSection (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], SECTION_TYPE, std::string&, int);
static bool SectionMatchesParent (SECTION_TYPE, section*, SECTION_TYPE, section*);
static void AddFileSurroundingData(const std::string&, std::vector<std::string>&);
static void AddFileInitializers (const std::string&, std::vector<std::string>&);
static void AddFileTrailingData (const std::string&, std::vector<std::string>&);
static void WriteDataToA3Db (const std::string&, std::vector<std::string>&);
static void AssignParent (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], SECTION_TYPE, SECTION_TYPE, 
	std::vector<std::shared_ptr<section>>, SECTION_TYPE , std::vector<std::shared_ptr<section>>);
static void ExportRelatedSections (bool, section*, SECTION_TYPE, section*, SECTION_TYPE, const std::string&, 
								   const std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], 
								   std::vector<std::string>&);
static void ExportSectionToA3 (SECTION_TYPE, section*, SECTION_TYPE, section*, const std::string&, 
							   const std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES],
							   std::vector<std::string>&);
static std::string FormSavStoragePath (const std::string&);
static void CreateObjectForSection (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], SECTION_TYPE, int, SECTION_TYPE, SECTION_TYPE);
static bool IgnoreSavLine (SECTION_TYPE, const std::string&, int);
void AddSpecialFieldsBeforeData (std::vector<std::string>&, SECTION_TYPE, section*, const std::string&,
								 const std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
void SortSectionLists (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
static void PostExternalImportProcessing (std::string, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES], 
	bool, FILE_LAND_ID_STRUCT [NO_OF_A3_FILE_NAME_TYPES]);
static void PostSavImportProcessing (const std::string&, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES],
	FILE_LAND_ID_STRUCT [NO_OF_A3_FILE_NAME_TYPES]);
static void PostSavPrepareReferencePrerequisits (const std::string&, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], 
	size_t[NO_OF_SECTION_TYPES], FILE_LAND_ID_STRUCT [NO_OF_A3_FILE_NAME_TYPES]);
static void SetSectionLandIds (const std::string&, const std::string&, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);
static bool GetLandIdFromSectionList (A3_FILE_NAME_TYPE, std::string&, std::string&, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
static bool CalcLandIdForFile (const std::string&, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], std::string&, std::string&,
	FILE_LAND_ID_STRUCT [NO_OF_A3_FILE_NAME_TYPES]);
static void CloseSectionKnockOns (SECTION_TYPE, const std::string&, std::vector<std::shared_ptr<section>>[NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);
static void InitializeLocalData (std::vector<std::shared_ptr<section>>[NO_OF_SECTION_TYPES], size_t[NO_OF_SECTION_TYPES], 
	size_t[NO_OF_SECTION_TYPES], FILE_LAND_ID_STRUCT [NO_OF_A3_FILE_NAME_TYPES]);
static void PostSavDataPostImportProcessing (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
static void SetPostExportImportFileSpecificData (const std::string&, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);

// Fields Manipulation Functions
static void PostSavExpandDecodedFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);
static void PostExternalEncodeExpandedFields (FIELD_REFERENCE_TYPE, std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES], bool);
static void PostSavSplitCombinedFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);
static void PostExternalMergeSplitFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);
static void PostSavExpandBitmaskFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);
static void PostExternalCombineBitmaskFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);
static void PostSavConvertBooleansToText (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);
static void PostExternalConvertBooleansFromText (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);
static void PostSavDecodeEnumFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);
static void PostExternalEncodeEnumFields (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES], size_t [NO_OF_SECTION_TYPES]);
static void PostSavFinalDataProcessing (std::vector<std::shared_ptr<section>> SectionList [NO_OF_SECTION_TYPES]);
static void PostExternalFirstDataProcessing (std::vector<std::shared_ptr<section>> [NO_OF_SECTION_TYPES]);
void PrintSectionFieldAllowedValues ();
static size_t GetSectionAllowedValues (SECTION_TYPE, std::vector<FIELD_VALUE_STRUCT>&);
static void PrintSectionAllowedValues (SECTION_TYPE, const std::vector<FIELD_VALUE_STRUCT>&);

// TIMING MACRO
#include "boost/date_time/posix_time/posix_time.hpp"

static boost::posix_time::ptime gStartTime;
#define TIMING_START\
	gStartTime = boost::posix_time::microsec_clock::local_time();

static boost::posix_time::ptime gEndTime;
static boost::posix_time::time_duration gTimeDiff;
#define TIMING_END(NAME)\
	gEndTime = boost::posix_time::second_clock::local_time();\
	gTimeDiff = gEndTime - gStartTime;\
	std::cout << "TIMING: " << gTimeDiff.total_seconds() << "s << (" << gTimeDiff.total_milliseconds() << ") for " << #NAME << std::endl;

// Quickly disable timing for release
///*
#pragma warning(disable:4005)
#define TIMING_START
#define TIMING_END(NAME)
#pragma warning(default:4005)
//*/