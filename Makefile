
CC = g++
CFLAGS = -Wall  --std=c++11 -g
SRC = main.cpp src/Effects/FIR.cpp src/Effects/Reverb.cpp src/GUI/Knob.cpp src/Effects/Tremolo.cpp src/Effects/Vibrato.cpp src/GUI/Listener.cpp src/GUI/Oscilloscope.cpp src/GUI/Widget.cpp src/Tones/Sawtooth.cpp src/Effects/Downsample.cpp src/GUI/Slider.cpp src/GUI/Button.cpp src/App.cpp src/Device.cpp src/Tones/Square.cpp src/Tones/Sine.cpp src/Track.cpp src/Tones/Tone.cpp src/Tones/PCMTone.cpp src/Effects/DecayEffect.cpp src/Tones/Triangle.cpp 
DEPS = include/App.hpp include/Effects/FIR.hpp include/Effects/Reverb.hpp include/GUI/Knob.hpp include/Effects/Tremolo.hpp include/Effects/Vibrato.hpp include/GUI/Listener.hpp include/GUI/Widget.hpp include/Tones/Sawtooth.hpp include/GUI/Oscilloscope.hpp include/Effects/Downsample.hpp include/GUI/Slider.hpp include/GUI/Button.hpp include/Device.hpp include/Tones/Sine.hpp include/Tones/Tone.hpp include/Track.hpp include/Tones/PCMTone.hpp include/Effects/Effect.hpp include/Effects/DecayEffect.hpp include/Tones/Square.hpp include/Tones/Triangle.hpp 
OBJDIR = ./obj
OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o,$(SRC))
EXECUTABLE = app


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
	rm -f $(EXECUTABLE) $(wildcard *.o) debug a.csv $(wildcard $(OBJDIR)/*/*.o) $(wildcard $(OBJDIR)/Tones/*.o) $(wildcard $(OBJDIR)/Effects/*.o)
