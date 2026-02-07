#pragma once

typedef unsigned _BitInt(8) byte;

enum CharsetCompare : char
{
     CharsetCompare_LESS_THAN    = -1
   , CharsetCompare_EQUAL        =  0
   , CharsetCompare_GREATER_THAN =  1
};
typedef enum CharsetCompare CharsetCompare;
