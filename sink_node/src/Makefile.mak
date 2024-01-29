CFLAGS = -Wall
LDFLAGS = -lpigpio

all: blink

blink: blink.c
        $(CC) $(CFLAGS) -o '$@' '$<' $(LDFLAGS)

clean:
        -rm blink
