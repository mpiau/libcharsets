#pragma once

//================================================================================================
// Definition
//================================================================================================

// Used when comparing 2 characters/sequences.
// Follows a similar logic as the standard 'strcmp' but with named values to make the code
// easier to follow.

enum charsetCompare : int
{
     charsetCompare_LESS_THAN    = -1
   , charsetCompare_EQUAL        =  0
   , charsetCompare_GREATER_THAN =  1
};

typedef enum charsetCompare charsetCompare;
