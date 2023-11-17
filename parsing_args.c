#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsing_args.h"

#define INITIAL_DYNAMIC_READ_SIZE 5
#define ONE_INDEX_SHIFT 1
#define TWO_INDEX_SHIFT 2

void get_phrase(char* phraseInput, chars_linked* phrase);

void create_grep_switches(grep_switches** newSwitchesPtr)
{

  if (NULL == ((*newSwitchesPtr) = (grep_switches*)malloc(sizeof(grep_switches)))) {
    printf("Memory allocation failed, unable to get grep arguments.\n");
    exit(1);
  }
  (*newSwitchesPtr)->ignoreCaps = false;
  (*newSwitchesPtr)->reverse = false;
  (*newSwitchesPtr)->matchesNumOnly = false;
  (*newSwitchesPtr)->inputLineNum = false;
  (*newSwitchesPtr)->printBytes = false;
  (*newSwitchesPtr)->exactPhrase = false;
  (*newSwitchesPtr)->printNLines = false;
  (*newSwitchesPtr)->Anum = 0;
  (*newSwitchesPtr)->eSwitch = false;
  return;
}

void get_ANum(char* argPtr, grep_switches* switchesPtr)
{
  int i;

  for (i = 0; argPtr[i] != '\0'; i++) {
    if (isdigit(argPtr[i]) == 0) {
      printf("Numerical value was not given for Anum\n-A will be ignored ");
      printf("and grep might not function properly\n");
      return;
    }
  }
  switchesPtr->Anum = atoi(argPtr);
  switchesPtr->printNLines = true;
}

void set_grep_switch(char* argPtr, grep_switches* switchesPtr, int curArgNum, bool* ANeedPtr)
{

  switch (*argPtr) {
    case 'i':
      switchesPtr->ignoreCaps = true;
      break;
    case 'v':
      switchesPtr->reverse = true;
      break;
    case 'c':
      switchesPtr->matchesNumOnly = true;
      break;
    case 'n':
      switchesPtr->inputLineNum = true;
      break;
    case 'b':
      switchesPtr->printBytes = true;
      break;
    case 'x':
      switchesPtr->exactPhrase = true;
      break;
    case 'A':
      if (*(argPtr + 1) != '\0') {
        get_ANum(argPtr + 1, switchesPtr);
      } else {
        *ANeedPtr = true;
      }
      break;
    case 'E':
      switchesPtr->eSwitch = true;
      break;
    default:
      printf("I don't know argument #%d, ignoring it.\n", curArgNum);
      break;
  }
}

char* get_square_phrase(grep_char* newChar, char* input)
{
  char c1, c2;

  c1 = *input;
  input++;
  if (*input == '-') {
    input++;
  }
  c2 = *input;
  newChar->option.charRange[0] = c1;
  newChar->option.charRange[1] = c2;
  input++;
  if (*input == ']') {
    input++;
  }
  return input;
}

void get_one_branch(char* strForBranch, chars_linked** branchAddress)
{
  start_linked_phrase(branchAddress);
  get_phrase(strForBranch, *branchAddress);
  free(strForBranch);
}

char* get_round_phrase(chars_linked* phrase, char* input)
{
  chars_linked *branch1 = NULL, *branch2 = NULL;
  char *s1 = NULL, *s2 = NULL;
  int counter1 = 0, counter2 = 0;

  if (NULL == (s1 = (char*)malloc(strlen(input) * sizeof(char)))) {
    printf("allocation failed for or phrased input, dont trust output\n");
    exit(1);
  }
  if (NULL == (s2 = (char*)malloc(strlen(input) * sizeof(char)))) {
    printf("allocation failed for or phrased input, dont trust output\n");
    exit(1);
  }
  while (input[counter1] != '|' && input[counter1] != '\0') {
    s1[counter1] = input[counter1];
    counter1++;
  }
  s1[counter1] = '\0';
  while (input[counter1 + counter2 + ONE_INDEX_SHIFT] != ')' && input[counter1 + counter2 + ONE_INDEX_SHIFT] != '\0') {
    s2[counter2] = input[counter1 + counter2 + ONE_INDEX_SHIFT];
    counter2++;
  }
  s2[counter2] = '\0';
  get_one_branch(s1, &branch1);
  get_one_branch(s2, &branch2);
  merge_branched_phrase(phrase, branch1, branch2);
  return input + counter1 + counter2 + TWO_INDEX_SHIFT;
}

void get_phrase(char* phraseInput, chars_linked* phrase)
{
  grep_char* newChar = NULL;
  enum grep_indicator curIndicator;

  while (*phraseInput != '\0' && *phraseInput != '\n') {
    curIndicator = create_indicator(*phraseInput);
    if (curIndicator != round) {
      initialize_grep_char(&newChar);
      newChar->indicator = curIndicator;
    }
    switch (curIndicator) {
      case specific:
        newChar->option.specific = *phraseInput;
        phraseInput++;
        break;
      case smuggled:
        newChar->option.specific = *(phraseInput + ONE_INDEX_SHIFT);
        phraseInput += TWO_INDEX_SHIFT;
        break;
      case dot:
        phraseInput++;
        break;
      case square:
        phraseInput = get_square_phrase(newChar, phraseInput + ONE_INDEX_SHIFT);
        break;
      case round:
        phraseInput = get_round_phrase(phrase, phraseInput + ONE_INDEX_SHIFT /*, specialPhrase*/);
        continue;
      default:
        break;
    }
    add_end_linked_phrase(phrase, newChar);
  }
}

void parse_args(int argsNum, char* args[], int* filePlace, chars_linked* phrase, grep_switches* switchesPtr)
{

  int i;
  char* ptr;
  bool gotPhrase = false, gotFile = false, ANeedNext = false;

  for (i = 1; i < argsNum; i++) {
    ptr = args[i];
    if (ANeedNext) {
      get_ANum(args[i], switchesPtr);
      ANeedNext = false;
    } else if (*ptr == '-') {
      set_grep_switch(ptr + 1, switchesPtr, i + 1, &ANeedNext);
    } else {
      if (gotPhrase == false) {
        get_phrase(args[i], phrase);
        gotPhrase = true;
      } else if (gotFile == false) {
        *filePlace = i;
        gotFile = true;
      } else {
        printf("too many arguments without '-', some ignored.\n");
        continue;
      }
    }
  }
  if (ANeedNext) {
    printf("Numerical value was not given for Anum\n-A will be ignored ");
    printf("and grep might not function properly\n");
  }
  return;
}
