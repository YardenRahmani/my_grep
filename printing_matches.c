#include "printing_matches.h"
#include <stdbool.h>
#include <stdio.h>

void print_single_line(line_info* curLine, grep_switches* switchesPtr)
{
  char joint;

  if (curLine->match) {
    joint = ':';
  } else {
    joint = '-';
  }
  if (switchesPtr->inputLineNum) {
    printf("%d%c", curLine->lineNum, joint);
  }
  if (switchesPtr->printBytes) {
    printf("%d%c", curLine->bytesUntilLine, joint);
  }
  printf("%s", curLine->lineStr);
}

void print_lines(lines_linked* linesInfo, grep_switches* switchesPtr)
{
  line_info* iter;
  bool breakLastPrinted = false;
  int linesPrinted = 0;

  if (switchesPtr->matchesNumOnly) {
    printf("%d\n", linesInfo->totalMatchNum);
    return;
  }
  iter = linesInfo->head;
  while (iter != NULL) {
    if (iter->printLine) {
      print_single_line(iter, switchesPtr);
      linesPrinted++;
      breakLastPrinted = false;
    } else if (switchesPtr->printNLines) {
      if (linesInfo->totalLinesToPrint > linesPrinted && linesPrinted > 0 && !breakLastPrinted) {
        printf("--\n");
        breakLastPrinted = true;
      }
    }
    iter = iter->next;
  }
}