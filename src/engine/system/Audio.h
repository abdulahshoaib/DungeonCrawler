#pragma once
#include <raylib.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>

class Audio {
private:
    std::map<std::string, Sound> m_sounds;
    std::map<std::string, Music> m_music;
    
    Music* m_currentMusic = nullptr;
    float m_masterVolume = 1.0f;

    bool m_fadingIn = false;
    float m_fadeSpeed = 1.0f;
    float m_currentMusicVol = 1.0f;

public:
    Audio();
    ~Audio();

    void Init();   
    void Clean();  
    void Update(); 

    // RENAMED: LoadSound -> LoadSFX
    void LoadSFX(std::string id, std::string fileName);
    void LoadMusic(std::string id, std::string fileName);

    // RENAMED: PlaySound -> PlaySFX
    void PlaySFX(std::string id);
    void PlayMusic(std::string id, bool loop = true, bool fadeIn = false);
    void StopMusic();

    void SetMasterVolume(float vol);
};