#include "Audio.h"
#include <iostream>

void Audio::Load()
{
    // --- MUSIC ---
    MainMenuMusic = LoadMusicStream("assets/audio/music.mp3");
    // LevelMusic    = LoadMusicStream("assets/audio/music/level_theme.mp3");

    // MainMenuMusic.looping = true;
    // LevelMusic.looping = true;

    // // --- SFX ---
    // HoverButton  = LoadSound("assets/audio/sfx/hover.wav");
    ButtonClicked = LoadSound("assets/audio/click.mp3");

    // AttackSFX = LoadSound("assets/audio/sfx/attack.wav");
    // HurtSFX   = LoadSound("assets/audio/sfx/hurt.wav");
    // JumpSFX   = LoadSound("assets/audio/sfx/jump.wav");

    currentMusic = MainMenuMusic;
}

void Audio::Init()
{
    InitAudioDevice();

    if (!IsAudioDeviceReady())
    {
        std::cerr << "ERROR: Audio device not ready!\n";
        return;
    }

    SetMasterVolume(masterVolume);
}

void Audio::Clean()
{
    UnloadMusicStream(MainMenuMusic);
    UnloadMusicStream(LevelMusic);

    UnloadSound(HoverButton);
    UnloadSound(ButtonClicked);
    UnloadSound(AttackSFX);
    UnloadSound(HurtSFX);
    UnloadSound(JumpSFX);

    CloseAudioDevice();
}

void Audio::Play(GMusic ref)
{
    switch (ref)
    {
    case MAIN_MENU_MUSIC:
        currentMusic = MainMenuMusic;
        break;

    case LEVEL_MUSIC:
        currentMusic = LevelMusic;
        break;
    }

    PlayMusicStream(currentMusic);
}

void Audio::Update()
{
    UpdateMusicStream(currentMusic);
}

void Audio::StopMusic()
{
    if (currentMusic.stream.buffer != nullptr)
        StopMusicStream(currentMusic);
}

void Audio::PlaySFx(SFx ref)
{
    Sound *sound = nullptr;

    switch (ref)
    {
    case HOVER_BUTTON:
        sound = &HoverButton;
        break;
    case BUTTON_HOVER:
        sound = &ButtonClicked;
        break;

    case ATTACK_SFX:
        sound = &AttackSFX;
        break;
    case HURT_SFX:
        sound = &HurtSFX;
        break;
    case JUMP_SFX:
        sound = &JumpSFX;
        break;

    default:
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

    SetSoundVolume(AttackSFX, vol);
    SetSoundVolume(HurtSFX, vol);
    SetSoundVolume(JumpSFX, vol);
    SetSoundVolume(ButtonClicked, vol);
    SetSoundVolume(HoverButton, vol);
}

void Audio::SetMusicVolume(float vol)
{
    musicVolume = vol;
    ::SetMusicVolume(currentMusic, vol);
}