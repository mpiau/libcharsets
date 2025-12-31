#pragma once

#include "macro_indexed_enum.h"

#include <stdint.h>
typedef int32_t codepoint;
typedef char ascii;

#define sizeofA(array) (sizeof(array) / sizeof(*array))

#define STRINGIFY( x )  #x
#define TO_STRING( x )  STRINGIFY( x )

static constexpr codepoint INVALID_CODEPOINT = INT32_MAX;
static constexpr codepoint FIRST_PLANE_RANGE_FIRST = 0x0000;
static constexpr codepoint FIRST_PLANE_RANGE_LAST  = 0xFFFF;
