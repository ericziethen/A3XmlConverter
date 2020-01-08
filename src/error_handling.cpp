#include "error_handling.h"

#include "a3_ui_text.h"
#include <stdlib.h>
#include <iostream>

void programError (const std::string& ErrorText)
{
	showTextMsg (ErrorText);

	exit (EXIT_FAILURE);
} /* programError */