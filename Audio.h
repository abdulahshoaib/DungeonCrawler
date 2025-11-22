#pragma once
#include <raylib.h>

class Audio {
  Sound sound;
  Wave wave;
  enum SoundNames {};
public:
  Audio();
  Audio(char *);
  ~Audio();
};