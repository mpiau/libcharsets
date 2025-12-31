#pragma once

#include "core.h"

// Change the "SMALL TEXT TO SHOW THE ISSUE" into "Small Text To Show The Issue"
void utils_update_case(char *str);

// Implementing my own strsep because it strtok doesn't support empty fields
// and it seems that strsep doesn't exist for me. However I used a char instead of
// a char * for the delimiter as we don't need to handle a string delimiter.
char *utils_strsep(char **strPtr, char sep);
