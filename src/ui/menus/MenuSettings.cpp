#include "MenuSettings.h"
#include "MenuMain.h"
#include "Engine.h"
#include "MainMenuState.h"
#include "Loader.h"
#include "Audio.h"
#include "../UITheme.h"
#include <string>

static int masterVolume = 50;
static int musicVolume = 70;
static int sfxVolume = 100;

MenuSettings::MenuSettings()
{
}

void MenuSettings::Draw()
{
    // 1. Setup Background and Scaling
    float scale = 0.8f;
    Vector2 bgPosition = {0, 0};
    Texture2D bgTex = Loader::MainMenuBackground;
    DrawTextureEx(bgTex, bgPosition, 0.0f, scale, WHITE);

    int screenWidth = 1100;
    float cx = screenWidth / 2.0f;
    float cy = 100.0f;

    // 2. Draw Title with consistent styling
    int titleFontSize = 72;
    Font titleFont = Loader::TitleFont;
    std::string title = "SETTINGS";
    Vector2 size = MeasureTextEx(titleFont, title.c_str(), titleFontSize, 2);
    Vector2 titleTextPos = {cx - (size.x / 2.0f), cy};

    UITheme::TextEffects::DrawTextWithShadow(titleFont, title, titleTextPos, titleFontSize, 2.0f, UITheme::Colors::TEXT_TITLE);

    // 3. Define Layout Constants
    float startY = cy + 120;
    float rowHeight = 60.0f;
    float btnSize = 40.0f;
    int fontSize = 30;

    // --- MASTER VOLUME ---
    Master_lbl.text = "Master";
    Master_lbl.fontSize = fontSize;
    Master_lbl.position = {cx - 200, startY + 5};
    Master_lbl.Draw(UITheme::Colors::TEXT_PRIMARY);

    // Minus Button
    Rectangle mMinusRect = {cx - 20, startY, btnSize, btnSize};
    MasterMinus_btn.label.text = "-";
    MasterMinus_btn.rect = mMinusRect;
    MasterMinus_btn.Draw(GRAY, RED);

    // Value Display
    std::string masterVal = std::to_string(masterVolume);
    DrawTextEx(Loader::TitleFont, masterVal.c_str(), {cx + 40, startY + 5}, fontSize, 2, UITheme::Colors::TEXT_PRIMARY);

    // Plus Button
    Rectangle mPlusRect = {cx + 100, startY, btnSize, btnSize};
    MasterPlus_btn.label.text = "+";
    MasterPlus_btn.rect = mPlusRect;
    MasterPlus_btn.Draw(GRAY, GREEN);

    // --- MUSIC VOLUME ---
    float musicY = startY + rowHeight;
    Music_lbl.text = "Music";
    Music_lbl.fontSize = fontSize;
    Music_lbl.position = {cx - 200, musicY + 5};
    Music_lbl.Draw(UITheme::Colors::TEXT_PRIMARY);

    Rectangle musicMinusRect = {cx - 20, musicY, btnSize, btnSize};
    MusicMinus_btn.label.text = "-";
    MusicMinus_btn.rect = musicMinusRect;
    MusicMinus_btn.Draw(GRAY, RED);

    std::string musicVal = std::to_string(musicVolume);
    DrawTextEx(Loader::TitleFont, musicVal.c_str(), {cx + 40, musicY + 5}, fontSize, 2, UITheme::Colors::TEXT_PRIMARY);

    Rectangle musicPlusRect = {cx + 100, musicY, btnSize, btnSize};
    MusicPlus_btn.label.text = "+";
    MusicPlus_btn.rect = musicPlusRect;
    MusicPlus_btn.Draw(GRAY, GREEN);

    // --- SFX VOLUME ---
    float sfxY = musicY + rowHeight;
    SFX_lbl.text = "SFx";
    SFX_lbl.fontSize = fontSize;
    SFX_lbl.position = {cx - 200, sfxY + 5};
    SFX_lbl.Draw(UITheme::Colors::TEXT_PRIMARY);

    Rectangle sfxMinusRect = {cx - 20, sfxY, btnSize, btnSize};
    SFXMinus_btn.label.text = "-";
    SFXMinus_btn.rect = sfxMinusRect;
    SFXMinus_btn.Draw(GRAY, RED);

    std::string sfxVal = std::to_string(sfxVolume);
    DrawTextEx(Loader::TitleFont, sfxVal.c_str(), {cx + 40, sfxY + 5}, fontSize, 2, UITheme::Colors::TEXT_PRIMARY);

    Rectangle sfxPlusRect = {cx + 100, sfxY, btnSize, btnSize};
    SFXPlus_btn.label.text = "+";
    SFXPlus_btn.rect = sfxPlusRect;
    SFXPlus_btn.Draw(GRAY, GREEN);

    // --- CONTROLS HINT ---
    float hintY = sfxY + rowHeight + 20;
    const char *controlsText = "Controls: WASD to Move, SPACE to Jump";
    int hintWidth = MeasureText(controlsText, 20);
    DrawTextEx(Loader::TitleFont, controlsText, {cx - (hintWidth / 2), hintY}, 20, 2, UITheme::Colors::TEXT_PRIMARY);

    // --- BACK BUTTON ---
    Rectangle BackRect = {cx - (200 / 2), hintY + 60, 200, 50};
    Back_btn.label.text = "BACK";
    Back_btn.rect = BackRect;
    Back_btn.Draw(GRAY, ORANGE);
}

void MenuSettings::HandleInput(Engine &engine)
{
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    Vector2 mousePoint = GetMousePosition();

    if (clicked && CheckCollisionPointRec(mousePoint, MasterMinus_btn.rect))
        if (masterVolume >= 10)
        {
            masterVolume -= 10;
            Audio::SetMasterVolume(masterVolume / 100.0f);
        }

    if (clicked && CheckCollisionPointRec(mousePoint, MasterPlus_btn.rect))
        if (masterVolume <= 90)
        {
            masterVolume += 10;
            Audio::SetMasterVolume(masterVolume / 100.0f);
        }

    if (clicked && CheckCollisionPointRec(mousePoint, MusicMinus_btn.rect))
        if (musicVolume >= 10)
        {
            musicVolume -= 10;
            Audio::SetMusicVolume(musicVolume / 100.0f);
        }

    if (clicked && CheckCollisionPointRec(mousePoint, MusicPlus_btn.rect))
        if (musicVolume <= 90)
        {
            musicVolume += 10;
            Audio::SetMusicVolume(musicVolume / 100.0f);
        }

    if (clicked && CheckCollisionPointRec(mousePoint, SFXMinus_btn.rect))
        if (sfxVolume >= 10)
        {
            sfxVolume -= 10;
            Audio::SetSFxVolume(sfxVolume / 100.0f);
        }

    if (clicked && CheckCollisionPointRec(mousePoint, SFXPlus_btn.rect))
        if (sfxVolume <= 90)
        {
            sfxVolume += 10;
            Audio::SetSFxVolume(sfxVolume / 100.0f);
        }

    if (clicked && CheckCollisionPointRec(mousePoint, Back_btn.rect))
    {
        engine.ChangeState(new MainMenuState());
    }
}