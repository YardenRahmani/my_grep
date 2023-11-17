#ifndef CHARS_LINKED_H
#define CHARS_LINKED_H

#include <stdbool.h>

enum grep_indicator { linkingNode, specific, smuggled, dot, square, round };

union grep_option {
  char specific;
  char charRange[2];
};

typedef struct grep_char {
  union grep_option option;
  enum grep_indicator indicator;
  struct grep_char* next;
  struct grep_char* orNext;
  bool endOfBranch;
} grep_char;

typedef struct chars_linked {
  grep_char* head;
  grep_char* tail;
  grep_char* branchedTail;
} chars_linked;

enum grep_indicator create_indicator(char prefix);

void initialize_grep_char(grep_char** newCharPtr);

void start_linked_phrase(chars_linked** newPhrasePtr);

void merge_branched_phrase(chars_linked* main, chars_linked* branch1, chars_linked* branch2);

void add_end_linked_phrase(chars_linked* phrase, grep_char* newChar);

void free_linked_phrase(chars_linked* phrase);

enum grep_indicator create_indicator(char prefix);

#endif
