CC=gcc
CFLAGS=-c -Wall --std=c99 -g
LDFLAGS=-lm -lrt -lpthread -lasound -ljack -lportaudio -g
SOURCES=main.c mixer.c node.c node_oscillator.c node_reverb.c oscillator.c waveshape_sine.c waveshape_wav.c waveshape_test.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=audio

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm -f *.o $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
