#include "parser.h"

#include <stdlib.h>
#include <stdio.h>


int main(int const argc, char **const argv)
{
   if (argc != 3)
   {
      fprintf(stderr,
         "Wrong numbers of arguments received.\n"
         "[./executable] [Blocks.txt path] [unicodeData.txt path]\n"
      );
      return EXIT_FAILURE;
   }

   if (parse_blocks(argv[1]) != EXIT_SUCCESS)
   {
      return EXIT_FAILURE;
   }
   return parse_codepoints(argv[2]);
}
