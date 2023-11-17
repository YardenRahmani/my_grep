#ifndef PARSING_ARGS_H
#define PARSING_ARGS_H

#include "chars_linked.h"
#include <stdbool.h>

typedef struct grep_switches {
  bool ignoreCaps;
  bool reverse;
  bool matchesNumOnly;
  bool inputLineNum;
  bool printBytes;
  bool exactPhrase;
  bool printNLines;
  int Anum;
  bool eSwitch;
} grep_switches;

void create_grep_switches(grep_switches** newSwitchesPtr);

void parse_args(int argsNum, char* args[], int* filePlace, chars_linked* phrase, grep_switches* switchesPtr);

#endif
