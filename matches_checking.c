#include "matches_checking.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool is_exact_match(char* dynamicStr, grep_char* curPhraseChar, grep_switches* switchesPtr);

bool check_next_char(char* dynamicStr, grep_char* curPhraseChar, grep_switches* switchesPtr)
{
  bool match;
  int lenOfCurChar;

  if (curPhraseChar->indicator == linkingNode) {
    lenOfCurChar = 0;
  } else {
    lenOfCurChar = 1;
  }
  match = is_exact_match(dynamicStr + lenOfCurChar, curPhraseChar->next, switchesPtr);
  if (match != true && curPhraseChar->orNext != NULL) {
    match = is_exact_match(dynamicStr + lenOfCurChar, curPhraseChar->orNext, switchesPtr);
  }
  return match;
}

bool is_exact_match(char* dynamicStr, grep_char* curPhraseChar, grep_switches* switchesPtr)
{
  char cIn, cPhrase, cMax, cMin;

  cIn = *dynamicStr;
  if (curPhraseChar == NULL) {
    if (switchesPtr->exactPhrase == true && cIn != '\0' && cIn != '\n') {
      return false;
    }
    return true;
  }
  switch (curPhraseChar->indicator) {
    case linkingNode:
      return check_next_char(dynamicStr, curPhraseChar, switchesPtr);
      break;
    case dot:
      if (cIn != '\0' && cIn != '\n') {
        return check_next_char(dynamicStr, curPhraseChar, switchesPtr);
      }
      break;
    case square:
      cMin = curPhraseChar->option.charRange[0];
      cMax = curPhraseChar->option.charRange[1];
      if (switchesPtr->ignoreCaps) {
        cIn = tolower(cIn);
        cMin = tolower(cMin);
        cMax = tolower(cMax);
      }
      if (cMin <= cIn && cIn <= cMax && cIn != '\0' && cIn != '\n') {
        return check_next_char(dynamicStr, curPhraseChar, switchesPtr);
      }
      break;
    default:
      cPhrase = curPhraseChar->option.specific;
      if (switchesPtr->ignoreCaps) {
        cIn = tolower(cIn);
        cPhrase = tolower(cPhrase);
      }
      if (cIn == cPhrase && cIn != '\0' && cIn != '\n') {
        return check_next_char(dynamicStr, curPhraseChar, switchesPtr);
      }
      break;
  }
  return false;
}

bool is_line_match(char* dynamicStr, chars_linked* phrase, grep_switches* switchesPtr)
{

  if (switchesPtr->exactPhrase) {
    return is_exact_match(dynamicStr, phrase->head, switchesPtr) ^ (switchesPtr->reverse);
  }
  while (*dynamicStr != '\0' && *dynamicStr != '\n') {
    if (is_exact_match(dynamicStr, phrase->head, switchesPtr)) {
      return true ^ (switchesPtr->reverse);
    }
    dynamicStr++;
  }
  return false ^ (switchesPtr->reverse);
}

void set_line(lines_linked* linesInfo, char* source, int lineNum, int bytes, bool match, grep_switches* switchesPtr)
{
  line_info *newLine = NULL, *linesIter = NULL;
  int counter;

  if (NULL == (newLine = (line_info*)malloc(sizeof(line_info)))) {
    printf("Memory allocation failed, unable to get a single line printing info.\n");
    exit(1);
  }
  if (NULL == (newLine->lineStr = (char*)malloc((1 + strlen(source)) * sizeof(char)))) {
    printf("allocation failure for saving line information, cannot give output.\n");
    exit(1);
  }
  strcpy(newLine->lineStr, source);
  newLine->lineNum = lineNum;
  newLine->bytesUntilLine = bytes;
  newLine->match = match;
  newLine->printLine = false;
  if (newLine->match) {
    newLine->printLine = true;
    linesInfo->totalLinesToPrint++;
  } else if (switchesPtr->printNLines) {
    counter = 1;
    linesIter = linesInfo->tail;
    while (linesIter != NULL && counter <= switchesPtr->Anum) {
      if (linesIter->match) {
        newLine->printLine = true;
        linesInfo->totalLinesToPrint++;
        break;
      }
      linesIter = linesIter->prev;
      counter++;
    }
  }
  newLine->next = NULL;
  newLine->prev = NULL;
  add_end_linked_lines_info(linesInfo, newLine);
}

void read_lines(FILE* fRead, chars_linked* phrase, lines_linked* linesInfo, grep_switches* switchesPtr)
{
  char* dynamicStr = NULL;
  int counter, istatus = !EOF;
  int lineNum = 0, bytes = 0;
  size_t size = 0;
  bool match;

  while (istatus != EOF) {
    counter = getline(&dynamicStr, &size, fRead);
    if (counter == -1) {
      istatus = EOF;
      continue;
    }
    match = false;
    lineNum++;
    if (is_line_match(dynamicStr, phrase, switchesPtr)) {
      match = true;
      linesInfo->totalMatchNum++;
    }
    set_line(linesInfo, dynamicStr, lineNum, bytes, match, switchesPtr);
    bytes += counter;
  }
  free(dynamicStr);
}
