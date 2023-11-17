.PHONY: all clean test

my_grep: main.o chars_linked.o lines_linked.o matches_checking.o parsing_args.o printing_matches.o
	@gcc -Wall -Wextra *.o -o my_grep

main.o: main.c chars_linked.c chars_linked.h lines_linked.c lines_linked.h parsing_args.c parsing_args.h matches_checking.h matches_checking.c printing_matches.c printing_matches.h
	@gcc -Wall -Wextra main.c -c

printing_matches.o: printing_matches.c printing_matches.h parsing_args.c parsing_args.h lines_linked.c lines_linked.h
	@gcc -Wall -Wextra printing_matches.c -c

matches_checking.o: matches_checking.c matches_checking.h parsing_args.c parsing_args.h chars_linked.c chars_linked.h lines_linked.c lines_linked.h
	@gcc -Wall -Wextra matches_checking.c -c

parsing_args.o: parsing_args.c parsing_args.h chars_linked.c chars_linked.h
	@gcc -Wall -Wextra parsing_args.c -c

lines_linked.o: lines_linked.c lines_linked.h
	@gcc -Wall -Wextra lines_linked.c -c

chars_linked.o: chars_linked.c chars_linked.h
	@gcc -Wall -Wextra chars_linked.c -c

clean:
	@-rm -f  my_grep *.o

all: my_grep

test: all
	@~nimrodav/grep_tests/run_all.sh
