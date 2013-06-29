CC=gcc
CFLAGS=-c -Wall --std=c99
LDFLAGS=-lasound -ljack
SOURCES=main.c libportaudio.a
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=audio

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
