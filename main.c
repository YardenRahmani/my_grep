#include <stdio.h>
#include <stdlib.h>

#include "chars_linked.h"
#include "lines_linked.h"
#include "matches_checking.h"
#include "parsing_args.h"
#include "printing_matches.h"
#define NOT_FOUND -1

int main(int argc, char* argv[])
{
  FILE* fRead = NULL;
  int filePlace = NOT_FOUND;
  chars_linked* phrase = NULL;
  grep_switches* switchesPtr = NULL;
  lines_linked* linesInfo = NULL;

  create_grep_switches(&switchesPtr);
  start_linked_phrase(&phrase);
  parse_args(argc, argv, &filePlace, phrase, switchesPtr);
  if (filePlace != NOT_FOUND) {
    if (NULL == (fRead = fopen(argv[filePlace], "r"))) {
      printf("Failed to open the file\n");
      exit(1);
    }
  } else {
    fRead = stdin;
  }
  start_linked_lines_info(&linesInfo);
  read_lines(fRead, phrase, linesInfo, switchesPtr);
  free_linked_phrase(phrase);
  if (filePlace != NOT_FOUND) {
    fclose(fRead);
  }
  print_lines(linesInfo, switchesPtr);
  free_lines_info(linesInfo);
  free(switchesPtr);
  exit(0);
}
