#pragma once

// Prerequisites:
// ==============
// Enum needs to be contiguous between given first and last.


// ===============================================================================================
// Code Generation (CG)
// ===============================================================================================

// This macro will generate the members:
// [...]_Count (Number of members in the enum)
// [...]_First -> [...]_Last
#define CG_ENUM_INDEXED_MEMBERS(name, first, last) \
   , name##_Count         \
   , name##_First = first \
   , name##_Last  = last


// ===============================================================================================
// Helpers
// ===============================================================================================

// Iterate through indexed enum values.
#define foreach_enum_indexed(var, enumName) \
   for (enumName var = enumName##_First; var <= enumName##_Last; ++var)

// Validate if the given value is inside the indexed enum range.
#define enum_indexed_in_range(var, enumName) \
   ( !(var < enumName##_First || var > enumName##_Last) )
