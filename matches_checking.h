#ifndef MATCHES_CHECKING_H
#define MATCHES_CHECKING_H

#include "chars_linked.h"
#include "lines_linked.h"
#include "parsing_args.h"
#include <stdbool.h>
#include <stdio.h>

void read_lines(FILE* fRead, chars_linked* phrase, lines_linked* linesInfoHead, grep_switches* switchesPtr);

#endif
