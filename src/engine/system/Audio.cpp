#include "Audio.h"

Audio::Audio() {
    // Constructor is empty. 
    // We use Init() explicitly in Engine.cpp to ensure the device is ready.
}

Audio::~Audio() {
    Clean();
}

void Audio::Init() {
    InitAudioDevice();
    
    if (!IsAudioDeviceReady()) {
        std::cerr << "Audio Error: Device failed to initialize!" << std::endl;
    } else {
        std::cout << "Audio System Initialized Successfully." << std::endl;
    }
}

void Audio::Clean() {
    // 1. Unload all Sounds
    for (auto const& [key, val] : m_sounds) {
        UnloadSound(val);
    }
    m_sounds.clear();

    // 2. Unload all Music
    for (auto const& [key, val] : m_music) {
        UnloadMusicStream(val);
    }
    m_music.clear();

    CloseAudioDevice();
}

void Audio::Update() {
    if (m_currentMusic != nullptr) {
        UpdateMusicStream(*m_currentMusic);

        // Handle Fade-In Logic
        if (m_fadingIn) {
            m_currentMusicVol += m_fadeSpeed * GetFrameTime();
            
            if (m_currentMusicVol >= 1.0f) {
                m_currentMusicVol = 1.0f;
                m_fadingIn = false;
            }
            SetMusicVolume(*m_currentMusic, m_currentMusicVol);
        }
    }
}

// --- LOADING ASSETS ---

// RENAMED: LoadSound -> LoadSFX
void Audio::LoadSFX(std::string id, std::string fileName) {
    Sound sound = ::LoadSound(fileName.c_str());
    
    if (sound.stream.buffer != nullptr) {
        m_sounds[id] = sound;
    } else {
        std::cerr << "Failed to load SFX: " << fileName << std::endl;
    }
}

void Audio::LoadMusic(std::string id, std::string fileName) {
    Music music = LoadMusicStream(fileName.c_str());
    
    if (music.stream.buffer != nullptr) {
        m_music[id] = music;
    } else {
        std::cerr << "Failed to load Music: " << fileName << std::endl;
    }
}

// --- PLAYBACK CONTROLS ---

// RENAMED: PlaySound -> PlaySFX
void Audio::PlaySFX(std::string id) {
    if (m_sounds.find(id) != m_sounds.end()) {
        ::PlaySound(m_sounds[id]);
    } else {
        std::cerr << "Warning: SFX ID not found -> " << id << std::endl;
    }
}

void Audio::PlayMusic(std::string id, bool loop, bool fadeIn) {
    if (m_music.find(id) != m_music.end()) {
        
        if (m_currentMusic != nullptr) {
            StopMusicStream(*m_currentMusic);
        }

        m_currentMusic = &m_music[id];
        m_currentMusic->looping = loop;

        if (fadeIn) {
            m_currentMusicVol = 0.0f;
            m_fadingIn = true;
        } else {
            m_currentMusicVol = 1.0f;
            m_fadingIn = false;
        }

        SetMusicVolume(*m_currentMusic, m_currentMusicVol);
        PlayMusicStream(*m_currentMusic);
    } else {
        std::cerr << "Warning: Music ID not found -> " << id << std::endl;
    }
}

void Audio::StopMusic() {
    if (m_currentMusic != nullptr) {
        StopMusicStream(*m_currentMusic);
    }
}

void Audio::SetMasterVolume(float vol) {
    m_masterVolume = vol;
    ::SetMasterVolume(vol);
}