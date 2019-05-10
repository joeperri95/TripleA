
CC = g++
CFLAGS = -Wall --std=c++11 
SRC = main.cpp Device.cpp Tones/Sine.cpp Track.cpp Tones/Tone.cpp Tones/PCMTone.cpp Effects/DecayEffect.cpp
OBJDIR = ./obj
OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o,$(SRC))
EXECUTABLE = run
DEPS = Device.hpp Tones/Sine.hpp Tones/Tone.hpp Track.hpp Tones/PCMTone.hpp Effects/Effect.hpp Effects/DecayEffect.hpp

ALSA = $(shell pkg-config --cflags --libs alsa)

LIBS = -lm 

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(CFLAGS) $(LIBS) $(ALSA)

debug: $(OBJECTS)
	$(CC) $(OBJECTS) -o debug -g $(CFLAGS) $(LIBS) $(ALSA)
 

$(OBJDIR)/%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean: 
	rm -f $(EXECUTABLE) $(wildcard *.o) debug a.csv $(wildcard $(OBJDIR)/*.o) $(wildcard $(OBJDIR)/Tones/*.o) $(wildcard $(OBJDIR)/Effects/*.o)
