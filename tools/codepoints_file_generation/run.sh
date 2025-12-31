#!/bin/bash

# 1: Download the file that we want from unicode website if not already downloaded.
# 2: Compile the executable if some modifications are needed.
# 3: Execute the executable with the path to the unicode data file.
# 4: All generated files will be in the folder generated/ (everything will be overridden inside)

download_unicode_datafile()
{
   local -r version="17.0.0"
   local -r localFilename="data/$1_${version}.txt"

   if [[ ! -e $localFilename ]]; then
      local -r filename="$1.txt"
      local -r url="https://www.unicode.org/Public/${version}/ucd/${filename}"
      # -nH: Do not save the file in the hostname folder. 
      wget -nH $url
      mv $filename $localFilename
   fi
}

run()
{
   # Create needed folders if they don't already exist.
   mkdir -p ./data
   mkdir -p ./generated

   # Download all the necessary files from Unicode
   download_unicode_datafile "UnicodeData"
   download_unicode_datafile "Blocks"

   # Compile & Run
   gcc main.c codepoint_categories.c -I. -o generate_codepoints
   ./generate_codepoints "data/UnicodeData_17.0.0.txt"
}

run

unset -f run