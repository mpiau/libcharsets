#!/bin/bash

# 1: Download the file that we want from unicode website if not already downloaded.
# 2: Compile the executable if some modifications are needed.
# 3: Execute the executable with the path to the unicode data file.
# 4: All generated files will be in the folder generated/ (everything will be overridden inside)

generate()
{
   local -r version="15.0.0"
   local -r filename="UnicodeData.txt"
   local -r url="https://www.unicode.org/Public/${version}/ucd/${filename}"
   local -r localFilename="UnicodeData_${version}.txt"

   if [[ ! -e $localFilename ]]; then
      # -nH: Do not save the file in the hostname folder. 
      wget -nH $url
      mv $filename $localFilename
   fi

   gcc main.c -I. -o generate_codepoints
   ./generate_codepoints $localFilename
}

generate

unset -f generate