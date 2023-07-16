
CC      := gcc
LDFLAGS := -lShlwapi -mwindows
CFLAGS  := -O2 -Wall
SRC      = hootdnd.c
RC       = resource.rc
PROG     = hootdnd.exe
WINDRES  = $(RC:.rc=.o)
OBJS     = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all:$(PROG)

$(PROG): $(OBJS) $(WINDRES)
	$(CC) $(OBJS) $(WINDRES) $(LDFLAGS) -o $@

$(WINDRES): resource.rc
	windres $(RC) $(WINDRES)

clean:
	rm *.exe *.o

