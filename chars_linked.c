#include "chars_linked.h"
#include <stdio.h>
#include <stdlib.h>

void initialize_grep_char(grep_char** newCharPtr)
{
  if (NULL == ((*newCharPtr) = (grep_char*)malloc(sizeof(grep_char)))) {
    printf("Memory allocation failed, unable to get a phrase unit.\n");
    exit(1);
  }
  (*newCharPtr)->next = NULL;
  (*newCharPtr)->orNext = NULL;
  (*newCharPtr)->endOfBranch = false;
}

void start_linked_phrase(chars_linked** newPhrasePtr)
{
  grep_char* headNode;

  initialize_grep_char(&headNode);
  headNode->indicator = linkingNode;
  if (NULL == ((*newPhrasePtr) = (chars_linked*)malloc(sizeof(chars_linked)))) {
    printf("Memory allocation failed, unable to get phrase.\n");
    exit(1);
  }
  (*newPhrasePtr)->head = headNode;
  (*newPhrasePtr)->tail = headNode;
  (*newPhrasePtr)->branchedTail = NULL;
  return;
}

void merge_branched_phrase(chars_linked* main, chars_linked* branch1, chars_linked* branch2)
{
  grep_char* branchEndLink = NULL;

  initialize_grep_char(&branchEndLink);
  branchEndLink->indicator = linkingNode;
  main->tail->next = branch1->head;
  main->tail->orNext = branch2->head;
  branch1->tail->next = branchEndLink;
  branch2->tail->next = branchEndLink;
  branch2->tail->endOfBranch = true;
  main->tail = branchEndLink;
  free(branch1);
  free(branch2);
}

void add_end_linked_phrase(chars_linked* phrase, grep_char* newChar)
{

  phrase->tail->next = newChar;
  phrase->tail = newChar;
  if (phrase->branchedTail != NULL) {
    phrase->branchedTail->next = newChar;
    phrase->branchedTail = NULL;
  }
}

void free_linked_chars(grep_char* curChar)
{
  grep_char* prev;

  while (curChar != NULL) {
    if (curChar->orNext != NULL && curChar->endOfBranch != true) {
      free_linked_chars(curChar->orNext);
    }
    if (curChar->endOfBranch == true && curChar->orNext == NULL) {
      free(curChar);
      return;
    }
    prev = curChar;
    curChar = curChar->next;
    free(prev);
  }
}

void free_linked_phrase(chars_linked* phrase)
{
  free_linked_chars(phrase->head);
  free(phrase);
}

enum grep_indicator create_indicator(char prefix)
{
  enum grep_indicator newIndicator;

  switch (prefix) {
    case '\\':
      newIndicator = smuggled;
      break;
    case '.':
      newIndicator = dot;
      break;
    case '(':
      newIndicator = round;
      break;
    case '[':
      newIndicator = square;
      break;
    default:
      newIndicator = specific;
      break;
  }
  return newIndicator;
}
