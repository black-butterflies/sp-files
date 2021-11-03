tldmonitor: tldmonitor.o date.o tldlist.o
	clang -Wall -Werror -g -o tldmonitor tldmonitor.o date.o tldlist.o

date.o: date.h date.c
	clang -Wall -Werror -g -o date.o -c date.c

tldlist.o: tldlist.h tldlist.c
	clang -Wall -Werror -g -o tldlist.o -c tldlist.c

tldmonitor.o: tldmonitor.c date.h tldlist.h
	clang -Wall -Werror -g -o tldmonitor.o -c tldmonitor.c

.PHONY: clean

clean:
	rm -f *.o tldmonitor
