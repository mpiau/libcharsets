#pragma once

#include <stddef.h>


//================================================================================================
// Definition
//================================================================================================

// Used when checking for the validity of a character/sequence.
// If invalid, invalidCharPos will be set to invalid CHARACTER (not byte) position.

struct CharsetValidity
{
   bool   valid;
   size_t invalidCharPos;
};

typedef struct CharsetValidity CharsetValidity;


//================================================================================================
// Assumptions
//================================================================================================

// Ensures that our 'valid' boolean will always be the first element of the structure.
// Code can rely on the ability to cast the structure into a boolean to retrieve that value.

static_assert(sizeof((CharsetValidity *)0)->valid == sizeof(bool));
static_assert(offsetof(CharsetValidity, valid) == 0);
