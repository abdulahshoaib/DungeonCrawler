#pragma once
#include <raylib.h>

enum GMusic
{
    MAIN_MENU_MUSIC,
    LEVEL_MUSIC
};

enum SFx
{
    HOVER_BUTTON,
    BUTTON_CLICKED,

    ATTACK_SFX,
    HURT_SFX,
    JUMP_SFX
};

class Audio
{
private:
    // ======== MUSIC REFERENCES ========
    inline static Music *MainMenuMusic = nullptr;
    inline static Music *LevelMusic = nullptr;

    // ======== SFX REFERENCES ========
    inline static Sound *HoverButton = nullptr;
    inline static Sound *ButtonClicked = nullptr;
    inline static Sound *AttackSFX = nullptr;
    inline static Sound *HurtSFX = nullptr;
    inline static Sound *JumpSFX = nullptr;

    // ======== CURRENT STREAM ========
    inline static Music *currentMusic = nullptr;

    // ======== VOLUME + FADE ========
    inline static float masterVolume = 1.0f;
    inline static float sfxVolume = 1.0f;
    inline static float musicVolume = 1.0f;

    inline static float fadeSpeed = 1.0f;
    inline static bool fadingIn = false;

public:
    static void Load();
    static void Init();
    static void Update();
    static void Clean();

    static void Play(GMusic ref);
    static void StopMusic();
    static void PlaySFx(SFx ref);

    static void SetMasterVolume(float vol);
    static void SetSFxVolume(float vol);
    static void SetMusicVolume(float vol);
};
