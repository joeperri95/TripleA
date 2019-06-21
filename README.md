# TripleA

A digital signal processing library that has gone too far.

Currently only supports linux sound with ALSA

# TODO
* create launcher class that will act as main window and can launch applets
* figure out how to implement nondeterministic effects
* refactor + commit piano applet and create more applets
* implement knob controls
* implement portaudio device for windows users
* create demo app for github
* give widgets dedicated textures instead of basic colors
* filter builder (low priority)
* update button for arbitrary shape


# UPDATES

## 2019-06-18

Switched to a callback style audio architecture.
Effects are also now based on phase

Tones now generate a sample based on phase. 
Tracks are a container for these tones

Cleaned up makefile

Reorganized folders
