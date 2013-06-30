CC=gcc
CFLAGS=-c -Wall --std=c99
LDFLAGS=-lasound -ljack -lportaudio -lm
SOURCES=main.c oscillator.c waveshape_sine.c waveshape_wav.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=audio

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
