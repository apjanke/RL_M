CC=gcc
LIBS= -Os -pipe -Wall -fomit-frame-pointer -DLINUX -DMULTIPLE_SCORE_ENTRY -Wl,-O1 -lm -lncurses
DEPS=*.h
STRIP_BINARY=yes
larn: $(DEPS) *.c
	$(CC) *.c -o larn13_gnulinux $(LIBS)