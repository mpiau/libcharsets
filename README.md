# Overview

**libcharsets** is a small static library written in C23 in order to handle multiple character sets such as **ascii**, **utf-8** and **utf-16**.

This library does not claim to be faster/more efficient than any other library or than the standard (I didn't run any benchmark anyway), it is mainly a learning experience consisting of reinventing the wheel (again) for my personal usage.  

Using a static library here allows me to create that dedicated repository for that subject.

# Status

Work In Progress. The library is in very early stage of development and the entire API can change tomorrow without any warning.

# Documentation

## Terminology  

One of the earliest issues that can arise when developing a library/system is confusing the users due to inconsistent naming conventions. If we want to name things properly, the first step is to describe them.  

<ins>**Character**</ins>  
A character is a human readable letter, number or symbol. 

<ins>**Glyph**</ins>  
A glyph is basically the visual representation of a character. It's what you see on the screen and a single character can have an infinite number of glyphs as each font define their own glyphs.

<ins>**Allograph**</ins>  
An allograph is using a glyph variant to represent the same character.  
'*A*' and '**A**' are both allographs of 'A'.

<ins>**Code point**</ins>  
A code point is an unique identifier used to represent an entity.  
U+0041 is the code point for the entity "Latin Capital Letter A". Written with the prefix "U+" and in hexadecimal, the smallest code point is U+0000 (the null character) and the largest is U+10FFFF (1 114 112 code points in total).  
Each code point can have a different binary representation depending of the encoding used (ascii, utf8, utf16, utf32, ...). A code point can be stored into one or multiple bytes (up to 4).

<ins>**Grapheme Cluster**</ins>  
A sequence of one or more code points, treated as a single unit with a dedicated glyph. We could also say that a grapheme cluster is a character.
Example: The Irish flag "🇮🇪" is composed of 2 different code points :
| Entity | Code point | Glyph |
| :---: | :---: | :---: |
|REGIONAL INDICATOR SYMBOL LETTER I | U+1F1EE | 🇮 |
|REGIONAL INDICATOR SYMBOL LETTER E | U+1F1EA | 🇪 |

<ins>**Text**</ins>  
A text is a sequence of one or more grapheme clusters.

<ins>**Charset**</ins>  
A Charset (or Character Set) is an encoding system that defines a collection of characters and the rules used to convert each character into binary data.

<ins>**ASCII**</ins>  
ASCII (American Standard Code for Information Interchange) is one of the earliest encoding system used in computer programming. Using only 1 byte, it has enough space to cover all english letters (upper/lowercase), numerals, punctuation and controls.  
Easy to use and memory efficient, but lacks support for the other languages.  

<ins>**UTF-8**</ins>  
UTF-8 (Unicode Transformation Format - 8 bits) is a variable length encoding (from 1 to 4 bytes).  
Compatible with ASCII.

<ins>**UTF-16**</ins>  
UTF-16 (Unicode Transformation Format - 16 bits) is a variable length encoding (2 or 4 bytes).  
Working on non-latin datasets, UTF-16 could be more space efficient as it only uses 2 bytes to encode asian characters while 3 are needed for UTF-8.  
Often used on Windows as "Wide characters".

<ins>**UTF-32**</ins>  
UTF-32 (Unicode Transformation Format - 32 bits) uses a fixed 4 bytes of space to easily encode every code point.  
Because every 4 bytes equals one code point, it can makes text related operations easier and faster but consumes more memory (up to 4x than UTF-8).


## Libcharsets Types

The library implements 6 new types:  

**byte** (*unsigned _BitInt(8)*)  
Represents a flow of bytes in memory that has not been identified to anything.  

**ascii** (*char*)  
Specify that the underlying bytes are encoded in ASCII.

**utf8** (*char8_t*)  
Specify that the underlying bytes are encoded in UTF-8.

**utf16** (*char16_t*)  
Specify that the underlying bytes are encoded in UTF-16.

**utf32** (*char32_t*)  
Specify that the underlying bytes are encoded in UTF-32.

**codepoint** (*_BitInt(32)*)  
Represents one code point in memory, following Unicode notation.


## Download & Build instructions

Please don't. Use a correct library instead.  
Don't make your code unsafe on purpose.
