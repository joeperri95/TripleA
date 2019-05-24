
CC = g++
CFLAGS = -Wall --std=c++11 
SRC = main.cpp Effects/Downsample.cpp Slider.cpp Button.cpp App.cpp Device.cpp Tones/Square.cpp Tones/Sine.cpp Track.cpp Tones/Tone.cpp Tones/PCMTone.cpp Effects/DecayEffect.cpp Tones/Triangle.cpp 
DEPS = App.hpp Effects/Downsample.hpp Slider.hpp Button.hpp Device.hpp Tones/Sine.hpp Tones/Tone.hpp Track.hpp Tones/PCMTone.hpp Effects/Effect.hpp Effects/DecayEffect.hpp Tones/Square.hpp Tones/Triangle.hpp 
OBJDIR = ./obj
OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o,$(SRC))
EXECUTABLE = run


SFML = $(shell pkg-config --cflags --libs sfml-all)
ALSA = $(shell pkg-config --cflags --libs alsa)

LIBS = -lm -lpthread

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(CFLAGS) $(LIBS) $(ALSA) $(SFML)

debug: $(OBJECTS)
	$(CC) $(OBJECTS) -o debug -g $(CFLAGS) $(LIBS) $(ALSA) $(SFML)

$(OBJDIR)/%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean: 
	rm -f $(EXECUTABLE) $(wildcard *.o) debug a.csv $(wildcard $(OBJDIR)/*.o) $(wildcard $(OBJDIR)/Tones/*.o) $(wildcard $(OBJDIR)/Effects/*.o)
