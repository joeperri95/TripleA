CC = g++

MAINNAME = 

SRCPATH = src/
INCLUDEPATH = include/

AUDIOPATH = Audio/
AUDIOSRCFILES = AlsaDevice.cpp PCMTone.cpp Sawtooth.cpp Sine.cpp Square.cpp Triangle.cpp Tone.cpp
AUDIOSRC = $(addprefix $(addprefix $(SRCPATH), $(AUDIOPATH)), $(AUDIOSRCFILES))

EFFECTPATH = Audio/Effects/
EFFECTSRCFILES = DecayEffect.cpp Downsample.cpp FIR.cpp Reverb.cpp Tremolo.cpp Vibrato.cpp 
EFFECTSRC  = $(addprefix $(addprefix $(SRCPATH), $(EFFECTPATH)), $(EFFECTSRCFILES))

GUIPATH = GUI/
GUISRCFILES = App.cpp Button.cpp DropDownItem.cpp DropDownMenu.cpp DropDownMenuBar.cpp Knob.cpp Listener.cpp Oscilloscope.cpp Slider.cpp Widget.cpp 
GUISRC = $(addprefix $(addprefix $(SRCPATH), $(GUIPATH)), $(GUISRCFILES))

SRC = main2.cpp $(AUDIOSRC) $(GUISRC) $(EFFECTSRC)

AUDIODEPFILES = AlsaDevice.hpp AudioObject.hpp Notes.hpp PCMTone.hpp Sawtooth.hpp Sine.hpp Square.hpp Triangle.hpp Tone.hpp
AUDIODEPS = $(addprefix $(addprefix $(INCLUDEPATH), $(AUDIOPATH)), $(AUDIODEPFILES))

GUIDEPFILES = App.hpp Button.hpp DropDownItem.hpp DropDownMenu.hpp DropDownMenuBar.hpp Knob.hpp Listener.hpp Oscilloscope.hpp Slider.hpp Widget.hpp 
GUIDEPS = $(addprefix $(addprefix $(INCLUDEPATH), $(GUIPATH)), $(GUIDEPFILES))

EFFECTDEPFILES = DecayEffect.hpp Downsample.hpp FIR.hpp Reverb.hpp Tremolo.hpp Vibrato.hpp 
EFFECTDEPS = $(addprefix $(addprefix $(INCLUDEPATH), $(EFFECTPATH)), $(EFFECTDEPFILES))

DEPS = $(MAINNAME) $(AUDIODEPS) $(GUIDEPS) $(EFFECTDEPS) 
CFLAGS = -Wall  --std=c++11 -I$(INCLUDEPATH)

OBJDIR = ./obj
OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))
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
	rm -f $(EXECUTABLE) $(wildcard *.o) debug $(wildcard $(OBJDIR)/*/*.o) $(wildcard $(OBJDIR)/*.o) $(wildcard $(OBJDIR)/src/Tones/*.o) $(wildcard $(OBJDIR)/src/GUI/*.o)
