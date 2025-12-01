#include "Audio.h"
#include "Loader.h"
#include <iostream>

void Audio::Load()
{
    MainMenuMusic = &Loader::MainMenuBGM;
    // LevelMusic = &Loader::LevelBGM;

    // AttackSFX = &Loader::AttackSFx;
    // HurtSFX = &Loader::HurtSFx;
    // JumpSFX = &Loader::JumpSFx;

    ButtonClicked = &Loader::ButtonClickSFX;
    // HoverButton = &Loader::HoverButtonSFx;
}

void Audio::Init()
{
    InitAudioDevice();

    if (!IsAudioDeviceReady())
    {
        // TODO(demon_slayer): Handle audio device not ready
    }

    SetMasterVolume(masterVolume);
}

void Audio::Update()
{
    if (currentMusic != nullptr)
    {
        UpdateMusicStream(*currentMusic);
        if (fadingIn)
        {
            musicVolume += fadeSpeed * GetFrameTime();
            if (musicVolume >= 1.0f)
            {
                musicVolume = 1.0f;
                fadingIn = false;
            }
            SetMusicVolume(musicVolume);
        }
    }
}

void Audio::Clean()
{
    CloseAudioDevice();
}

void Audio::Play(GMusic ref)
{
    if (currentMusic)
        StopMusicStream(*currentMusic);

    switch (ref)
    {
    case MAIN_MENU_MUSIC:
        currentMusic = MainMenuMusic;
        break;

    case LEVEL_MUSIC:
        currentMusic = LevelMusic;
        break;

    default:
        break;
    }
    if (!currentMusic)
    {
        std::cerr << "Audio::Play(): Music reference was nullptr!\n";
        return;
    }

    currentMusic->looping = true;

    // Fade-in logic
    musicVolume = 0.0f;
    fadingIn = true;

    SetMusicVolume(musicVolume);
    PlayMusicStream(*currentMusic);
}

void Audio::StopMusic()
{
    if (currentMusic)
        StopMusicStream(*currentMusic);
    currentMusic = nullptr;
}

void Audio::PlaySFx(SFx ref)
{
    Sound *sound = nullptr;

    switch (ref)
    {
    case BUTTON_CLICKED:
        sound = ButtonClicked;
        break;

    case ATTACK_SFX:
        sound = AttackSFX;
        break;

    case HURT_SFX:
        sound = HurtSFX;
        break;

    case JUMP_SFX:
        sound = JumpSFX;
        break;

    default:
        // std::cerr << "Audio::PlaySFx(): Invalid SFx enum!\n";
        return;
    }

    if (!sound)
    {
        // std::cerr << "Audio::PlaySFx(): SFX reference was nullptr!\n";
        return;
    }

    SetSoundVolume(*sound, sfxVolume);
    PlaySound(*sound);
}

void Audio::SetMasterVolume(float vol)
{
    masterVolume = vol;
    ::SetMasterVolume(vol);
}

void Audio::SetSFxVolume(float vol)
{
    sfxVolume = vol;

    if (AttackSFX)
        SetSoundVolume(*AttackSFX, vol);
    if (HurtSFX)
        SetSoundVolume(*HurtSFX, vol);
    if (JumpSFX)
        SetSoundVolume(*JumpSFX, vol);
}

void Audio::SetMusicVolume(float vol)
{
    musicVolume = vol;

    if (currentMusic)
        ::SetMusicVolume(*currentMusic, vol);
}