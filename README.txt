## My_grep

my_grep is a command-line utility written in C that simulates the behavior of the well-known 'grep' command.
This program allows users to search for a specified pattern in files, supporting various command-line options.


## Skills Demonstrated in the Project

- C programming (Under Linux)
- Dynamic memory management and Complex data structures implementation
- Text matching algorithms
- Modular programming
- Clean and maintainable code ensuring ease of future modifications and scalability


## Project Structure

The project consists of six modules:

1. Main Module (main.c):
Responsible for the main program execution, serves as the entry point for the program.

2. Chars Linked Module (chars_linked.h, chars_linked.c):
Manages linked lists of characters for constructing and representing search patterns.
Supports the creation, merging, and freeing of linked lists of characters.
Handles special characters like escape sequences, dots, square brackets, and parentheses.

3. Lines Linked Module (lines_linked.h, lines_linked.c):
Manages linked lists of line information, including the actual line content and metadata.
Keeps track of line numbers, bytes until the line, whether it's a match, and whether it should be printed.
Provides functions for initializing, adding, and freeing lines linked lists.

4. Args Processing Module (args_processing.h, args_processing.c):
Deals with parsing and interpreting command-line arguments.
Creates and manages the data structure (grep_switches) that stores various options specified by the user.
Handles the parsing of the searched pattern.

5. Matches Checking Module (matches_checking.h, matches_checking.c):
Implements the logic for checking if a line matches the specified pattern.
Handles special cases like exact phrase matches, dot (any character) matches, square bracket character ranges, etc.
Determines whether a line should be considered a match based on the pattern and user-specified options.

6. Matches Printing Module (matches_printing.h, matches_printing.c):
Prints the lines that match the search criteria, considering various options.
Handles special cases like printing line numbers, bytes until the line, and printing the total number of matches.
Manages the output format based on user-specified options.


## Build and Run Instructions

1. Compile Source Codes:
   A Makefile is provided for the project.
   Commands available are make, clean and test (test was used in the develop process).

2. Execution Notes:
   Once the executable is built, you can use the following command to run your my_grep program:
   
   "./my_grep [OPTIONS] PATTERN [FILE...]"
   
   OPTIONS and FILE are both optional.
   If no file is provided, the program will operate in interactive mode, taking input from the command line.
   
   Options:
   -i: Ignore case distinctions during the search.
   -v: Invert the sense of matching, selecting non-matching lines.
   -c: Print only a count of matching lines.
   -n: Display line numbers alongside output lines.
   -b: Display the byte offset within the input file before each line.
   -x: Match only whole lines.
   -A NUM: Print NUM lines of trailing context after matching lines.
   -E: Interpret the pattern as an extended regular expression.

4. Adjustment:
   - Adjustments my be needed, based on your development environment. Developed for Linux (Ubuntu).
