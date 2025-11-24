
#include "Audio.h"


Audio::Audio(char *audio_name) {
  InitAudioDevice();

  // TODO(demon_slayer): change this so that when I change
  // to using an array for audio and sound then it loads them
  // one by one
  wave = LoadWave(audio_name);
  sound = LoadSoundFromWave(wave);
}

Audio::Audio() { InitAudioDevice(); }

Audio::~Audio() {
  UnloadSound(sound);
  UnloadWave(wave);
  CloseAudioDevice();
}
