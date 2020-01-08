#include "a3_ui_text.h"
#include "error_handling.h"
#include "a3_db_io.h"
#include "xml_io.h"
#include <iostream>

#define IMPORT_TEXT						"import"
#define EXPORT_TEXT						"export"
#define EXPORT_GENERATE_FIXTURES_TEXT	"export_autogenerate"
#define ALLOWED_VALUE_TEXT				"allowed_values"

#define MENU_IMPORT_OPTION						1
#define MENU_EXPORT_OPTION						3
#define MENU_EXPORT_GENERATE_FIXTURES_OPTION	4
#define MENU_ALLOWED_FIELD_VALUE_OPTION			6
#define MENU_QUIT_OPTION						9

static void DrawMenuOption(int OptionValue, std::string MenuText)
{
	showTextMsg(std::string("(") + std::to_string(OptionValue) + std::string(") - ") + MenuText);
} // DrawMenuOption

static void MainMenu ()
{
	int Input;
	bool KeepRunning = true;
	while (KeepRunning) 
	{
		DrawMenuOption(MENU_IMPORT_OPTION, "Importiere Daten von Anstoss 3 *.sav Dateien");
		DrawMenuOption(MENU_EXPORT_OPTION, "Exportiere zu Anstoss 3 *.sav Dateien");
		DrawMenuOption(MENU_EXPORT_GENERATE_FIXTURES_OPTION, "Exportiere zu Anstoss 3 *.sav Dateien - Autogeneriere Spielplan");
		DrawMenuOption(MENU_ALLOWED_FIELD_VALUE_OPTION, "Erlaubte Werte");
		DrawMenuOption(MENU_QUIT_OPTION, "Beende Program");

		std::cin >> Input;
		switch (Input) 
		{
		case (MENU_IMPORT_OPTION): 
			importA3DbFiles();
			break;

		case (MENU_EXPORT_OPTION):
			exportA3DbFiles(false);
			break;

		case (MENU_EXPORT_GENERATE_FIXTURES_OPTION):
			exportA3DbFiles(true);
			break;

		case (MENU_ALLOWED_FIELD_VALUE_OPTION):
			PrintSectionFieldAllowedValues();
			break;

		case (MENU_QUIT_OPTION): 
			KeepRunning = false;
			break;

		default:
			showTextMsg("Unexpected Menu Option, Try Again");   
			std::cin.sync();
			std::cin.clear();
			break;
		} // switch input
	} // while no option selected

} // MainMenu

#include "boost/date_time/posix_time/posix_time.hpp"
void main (int argc, char* argv[])
{	
	boost::posix_time::ptime StartTime = boost::posix_time::microsec_clock::local_time();

	if (argc >= 2)
	{
		if (std::string(argv[1]).compare(IMPORT_TEXT) == 0)
			importA3DbFiles();
		else if (std::string(argv[1]).compare(EXPORT_TEXT) == 0)
			exportA3DbFiles(false);
		else if (std::string(argv[1]).compare(EXPORT_GENERATE_FIXTURES_TEXT) == 0)
			exportA3DbFiles(true);		
		else if (std::string(argv[1]).compare(ALLOWED_VALUE_TEXT) == 0)
			PrintSectionFieldAllowedValues();
		else
		{
			showTextMsg("##########################################");
			showTextMsg(std::string ("Unerwartetes Argument: \"") + std::string(argv[1]) + std::string("\"")) ;
		}
	}
	else
	{
		MainMenu();
	}

	boost::posix_time::ptime EndTime = boost::posix_time::second_clock::local_time();
	boost::posix_time::time_duration TimeDiff = EndTime - StartTime;
	std::cout << "Program Time: " << TimeDiff.total_milliseconds() << "ms" << std::endl;
} // main