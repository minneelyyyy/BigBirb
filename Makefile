CC=gcc
CFLAGS=-g
LIBS=-ldiscord -lcurl -lpthread

OBJS=src/main.o \
	src/commands/ping.o

.PHONY: all clean

all: BigBirb

BigBirb: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJS): src/%.o : src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	rm -f BigBirb
	rm -f *.log
