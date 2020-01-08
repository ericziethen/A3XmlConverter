#include "csv_io.h"
#include <sstream>
#include <iterator>

#include <boost/tokenizer.hpp>

#define CSV_SEP ","

csv_io::csv_io(void)
{
}


csv_io::~csv_io(void)
{
}

#if 1
void OpenExternalFileForWriting (const std::string& FileName, std::ofstream& FileHandle)
{
	FileHandle.open(FileName.c_str(), std::ofstream::out);
} // OpenExternalFileForWriting

std::string GetA3StorageFileName (std::string BaseFileName)
{
	return (BaseFileName + std::string(".csv"));
} // GetA3StorageFileName

void ReadA3Data (const std::string& CsvLine, std::vector<std::shared_ptr<value_pair>>& ObjectValuePairs, 
					int& ObjectReadCount, bool& HeaderRead)
{
	// Write Header if needed
	if (!HeaderRead)
	{
		ReadRawCsv (CsvLine, ObjectValuePairs, true);
		HeaderRead = true;
	}
	else
	{
		ReadRawCsv (CsvLine, ObjectValuePairs, false);
		ObjectReadCount++;
	}	

} // ReadA3Data


static void ReadRawCsv (const std::string& CsvLine, std::vector<std::shared_ptr<value_pair>>& ObjectValuePairs, bool ReadCsvHeader)
{

	boost::tokenizer<> CsvTokenizer(CsvLine);
	int TokenCount = 0;

	boost::char_separator<char> CharSeparator(CSV_SEP,CSV_SEP,boost::keep_empty_tokens);
	boost::tokenizer<boost::char_separator<char>> TokenList(CsvLine, CharSeparator);
 
	for(boost::tokenizer<boost::char_separator<char>>::iterator Token=TokenList.begin(); Token != TokenList.end(); ++Token)
	{
		if ((*Token).compare (CSV_SEP) == 0)
			continue;

		if (ReadCsvHeader)
			ObjectValuePairs.push_back(std::shared_ptr<value_pair> (new value_pair(*Token, "")));
		else
			ObjectValuePairs.at(TokenCount)->Value = *Token;

			TokenCount++;	
	} // for each token in string

} // ReadRawCsv

void WriteA3Data (std::ofstream& FileHandle, const std::vector<std::shared_ptr<value_pair>>& ObjectValuePairs, int& ObjectWriteCount)
{
	// Write Header if needed
	if (ObjectWriteCount == 0)
		WriteRawCsv (FileHandle, ObjectValuePairs, true);

	WriteRawCsv (FileHandle, ObjectValuePairs, false);
	
	ObjectWriteCount++;
} // WriteA3Data

static void WriteRawCsv (std::ofstream& FileHandle, const std::vector<std::shared_ptr<value_pair>>& ObjectValuePairs, bool WriteCsvHeader)
{
	std::stringstream CsvLine;
	CsvLine.str(std::string());

	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = ObjectValuePairs.begin();
		Iterator != ObjectValuePairs.end(); ++Iterator)
	{
		if ((Iterator - ObjectValuePairs.begin()) > 0)
		{
			CsvLine << ",";
		} // if not first object

		if (WriteCsvHeader)
			CsvLine << (*Iterator)->Tag;
		else
			CsvLine << (*Iterator)->Value;
		// Write to CSV Line
	}

	CsvLine << "\n";

	FileHandle << CsvLine.rdbuf();	
} // WriteRawCsv
#endif