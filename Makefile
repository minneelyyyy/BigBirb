INCLUDES=-I./src/include
DEFINES=-DJSMN_STATIC

LIBS=-ldiscord -lcurl -lpthread

SOURCES=$(shell find src/ -type f -name "*.c")
OBJECTS=$(patsubst src/%.c,build/%.o,$(SOURCES))

.PHONY: all clean

all: BigBirb

BigBirb: $(OBJECTS)
	$(LD) -o $@ $^ $(LIBS)

$(OBJECTS): build/%.o : src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -c -o $@ $<

clean:
	rm -f $(OBJECTS)
	rm -f BigBirb
	rm -f *.log
