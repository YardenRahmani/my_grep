#include "lines_linked.h"
#include <stdio.h>
#include <stdlib.h>

void start_linked_lines_info(lines_linked** linesInfoPtr)
{

  if (NULL == ((*linesInfoPtr) = (lines_linked*)malloc(sizeof(lines_linked)))) {
    printf("Memory allocation failed, unable to get printing info.\n");
    exit(1);
  }
  (*linesInfoPtr)->head = NULL;
  (*linesInfoPtr)->tail = NULL;
  (*linesInfoPtr)->totalMatchNum = 0;
  (*linesInfoPtr)->totalLinesToPrint = 0;
}

void add_end_linked_lines_info(lines_linked* linesInfo, line_info* newLine)
{

  if (linesInfo->head == NULL) {
    linesInfo->head = newLine;
    linesInfo->tail = newLine;
  } else {
    linesInfo->tail->next = newLine;
    newLine->prev = linesInfo->tail;
    linesInfo->tail = newLine;
  }
}

void free_lines_info(lines_linked* linesInfo)
{
  line_info *iter, *prev;

  iter = linesInfo->head;
  while (iter != NULL) {
    free(iter->lineStr);
    prev = iter;
    iter = iter->next;
    free(prev);
  }
  free(linesInfo);
}