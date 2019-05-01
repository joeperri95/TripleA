
CC = g++
CFLAGS = -Wall --std=c++11 
SRC = main.cpp Device.cpp Sine.cpp Track.cpp Tone.cpp 
OBJECTS = $(patsubst %.cpp,%.o,$(SRC))
EXECUTABLE = run
DEPS = Device.hpp Sine.hpp Tone.hpp Track.hpp

ALSA = $(shell pkg-config --cflags --libs alsa)

LIBS = -lm 

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(CFLAGS) $(LIBS) $(ALSA)

debug: $(OBJECTS)
	$(CC) $(OBJECTS) -o debug -g $(CFLAGS) $(LIBS) $(ALSA)
 

%.o: %.cpp $(DEPS)
	$(CC) $(SRC) $(CFLAGS) -c

.PHONY: clean

clean: 
	rm -f $(EXECUTABLE) $(wildcard *.o) debug