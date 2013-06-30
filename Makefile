CC=gcc
CFLAGS=-c -Wall --std=c99
LDFLAGS=-lm -lrt -lpthread -lasound -ljack -lportaudio
SOURCES=main.c oscillator.c waveshape_sine.c waveshape_wav.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=audio

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm -f *.o $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
