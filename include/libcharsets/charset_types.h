#pragma once

typedef unsigned _BitInt(8) byte;

typedef char                 ascii;
typedef unsigned _BitInt( 8) utf8;
typedef unsigned _BitInt(16) utf16;
typedef unsigned _BitInt(32) utf32;
typedef unsigned _BitInt(32) codepoint;

enum CharsetCompare : char
{
     CharsetCompare_LESS_THAN    = -1
   , CharsetCompare_EQUAL        =  0
   , CharsetCompare_GREATER_THAN =  1
};
typedef enum CharsetCompare CharsetCompare;
