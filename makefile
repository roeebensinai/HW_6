CC     = gcc
CFLAGS = -Wall -g -std=c99
CCLINK = $(CC)
OBJS   = ransom.o
EXEC = prog.exe
RM = rm -fr *.exe $(OBJS)

$(EXEC): $(OBJS)
	$(CCLINK) -o $@ $^


ransom.o: ransom.c


clean:
	$(RM)
