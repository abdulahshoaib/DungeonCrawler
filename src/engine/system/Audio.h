#pragma once
#include <raylib.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>

class Audio
{
private:
    static Music *MainMenuBGM;

    inline static Music *m_currentMusic = nullptr;
    inline static float m_masterVolume = 1.0f;

    inline static bool m_fadingIn = false;
    inline static float m_fadeSpeed = 1.0f;
    inline static float m_currentMusicVol = 1.0f;

public:
    Audio();
    ~Audio();

    static void Init();
    static void Clean();
    static void Update();

    // RENAMED: LoadSound -> LoadSFX
    static void LoadSFX(std::string id, std::string fileName);
    static void LoadMusic(std::string id, std::string fileName);

    // RENAMED: PlaySound -> PlaySFX
    static void PlaySFX();
    static void PlayMusic(int);
    static void StopMusic();

    static void SetMasterVolume(float vol);
};