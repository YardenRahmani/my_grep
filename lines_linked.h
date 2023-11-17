#ifndef LINES_LINKED_H
#define LINES_LINKED_H

#include <stdbool.h>

typedef struct line_info {
  char* lineStr;
  int lineNum;
  int bytesUntilLine;
  bool match;
  bool printLine;
  struct line_info* next;
  struct line_info* prev;
} line_info;

typedef struct lines_linked {
  line_info* head;
  line_info* tail;
  int totalMatchNum;
  int totalLinesToPrint;
} lines_linked;

void start_linked_lines_info(lines_linked** linesInfoPtr);

void add_end_linked_lines_info(lines_linked* linesInfo, line_info* newLine);

void free_lines_info(lines_linked* linesInfoPtr);

#endif
