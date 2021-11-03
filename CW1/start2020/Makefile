CC=clang
EXE=tldmonitor

CFLAGS=-g -Wall -Werror

ADRESSSANITIZERFLAGS=-fsanitize=address -fno-omit-frame-pointer -O1 
LEAKSANITIZERFLAGS=-fsanitize=leak -fno-omit-frame-pointer

OBJ=tldmonitor.o date.o tldlist.o

# Default target
all: $(EXE)

# Sanitizers
address: CFLAGS+=$(ADRESSSANITIZERFLAGS)
address: $(EXE)

leak: CFLAGS+=$(LEAKSANITIZERFLAGS)
leak: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

date.o: date.h date.c
	$(CC) $(CFLAGS) -o $@ -c date.c 

tldlist.o: tldlist.h tldlist.c
	$(CC) $(CFLAGS) -o $@ -c tldlist.c 

tldmonitor.o: tldmonitor.c date.h tldlist.h
	$(CC) $(CFLAGS) -o $@ -c tldmonitor.c





# tldmonitor: tldmonitor.o date.o tldlist.o
# 	clang -Wall -Werror -g -o tldmonitor tldmonitor.o date.o tldlist.o

# date.o: date.h date.c
# 	clang -Wall -Werror -g -o date.o -c date.c

# tldlist.o: tldlist.h tldlist.c
# 	clang -Wall -Werror -g -o tldlist.o -c tldlist.c

# tldmonitor.o: tldmonitor.c date.h tldlist.h
# 	clang -Wall -Werror -g -o tldmonitor.o -c tldmonitor.c

.PHONY: clean small large

clean:
	rm -f *.o tldmonitor

small:
	./tldmonitor 01/01/1900 31/12/2100 small.txt

large:
	./tldmonitor 01/01/1900 31/12/2100 large.txt