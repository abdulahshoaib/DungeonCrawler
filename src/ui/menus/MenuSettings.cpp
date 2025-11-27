#include "MenuSettings.h"
#include "MenuMain.h"
#include "Engine.h"
#include "MainMenuState.h"
#include "Loader.h"
#include <string>

static int masterVolume = 50;
static int musicVolume = 75;
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
    float cy = 100.0f; // Starting Y height

    // 2. Draw Title
    int titleFontSize = 72;
    Font titleFont = Loader::TitleFont;
    std::string title = "SETTINGS";
    Vector2 size = MeasureTextEx(titleFont, title.c_str(), titleFontSize, 2);
    Vector2 titleTextPos = {cx - (size.x / 2.0f), cy};

    titleLabel.fontSize = titleFontSize;
    titleLabel.text = title;
    titleLabel.position = titleTextPos;
    titleLabel.Draw(WHITE);

    // 3. Define Layout Constants
    float startY = cy + 120;
    float rowHeight = 60.0f;
    float btnSize = 40.0f;
    int textSize = 30;

    // --- MASTER VOLUME ---
    // Label
    Master_lbl.text = "Master";
    Master_lbl.fontSize = textSize;
    Master_lbl.position = {cx - 200, startY + 5};
    Master_lbl.Draw(WHITE);

    // Minus Button
    Rectangle mMinusRect = {cx - 20, startY, btnSize, btnSize};
    MasterMinus_btn.label.text = "-";
    MasterMinus_btn.rect = mMinusRect;
    MasterMinus_btn.Draw(GRAY, RED);

    // Value Display
    std::string masterVal = std::to_string(masterVolume);
    DrawText(masterVal.c_str(), cx + 40, startY + 5, textSize, WHITE);

    // Plus Button
    Rectangle mPlusRect = {cx + 100, startY, btnSize, btnSize};
    MasterPlus_btn.label.text = "+";
    MasterPlus_btn.rect = mPlusRect;
    MasterPlus_btn.Draw(GRAY, GREEN);

    // --- MUSIC VOLUME ---
    float musicY = startY + rowHeight;
    Music_lbl.text = "Music";
    Music_lbl.fontSize = textSize;
    Music_lbl.position = {cx - 200, musicY + 5};
    Music_lbl.Draw(WHITE);

    Rectangle musicMinusRect = {cx - 20, musicY, btnSize, btnSize};
    MusicMinus_btn.label.text = "-";
    MusicMinus_btn.rect = musicMinusRect;
    MusicMinus_btn.Draw(GRAY, RED);

    std::string musicVal = std::to_string(musicVolume);
    DrawText(musicVal.c_str(), cx + 40, musicY + 5, textSize, WHITE);

    Rectangle musicPlusRect = {cx + 100, musicY, btnSize, btnSize};
    MusicPlus_btn.label.text = "+";
    MusicPlus_btn.rect = musicPlusRect;
    MusicPlus_btn.Draw(GRAY, GREEN);

    // --- SFX VOLUME ---
    float sfxY = musicY + rowHeight;
    SFX_lbl.text = "SFx";
    SFX_lbl.fontSize = textSize;
    SFX_lbl.position = {cx - 200, sfxY + 5};
    SFX_lbl.Draw(WHITE);

    Rectangle sfxMinusRect = {cx - 20, sfxY, btnSize, btnSize};
    SFXMinus_btn.label.text = "-";
    SFXMinus_btn.rect = sfxMinusRect;
    SFXMinus_btn.Draw(GRAY, RED);

    std::string sfxVal = std::to_string(sfxVolume);
    DrawText(sfxVal.c_str(), cx + 40, sfxY + 5, textSize, WHITE);

    Rectangle sfxPlusRect = {cx + 100, sfxY, btnSize, btnSize};
    SFXPlus_btn.label.text = "+";
    SFXPlus_btn.rect = sfxPlusRect;
    SFXPlus_btn.Draw(GRAY, GREEN);

    // --- CONTROLS HINT ---
    float hintY = sfxY + rowHeight + 20;
    const char *controlsText = "Controls: WASD to Move, SPACE to Jump";
    int hintWidth = MeasureText(controlsText, 20);
    DrawText(controlsText, cx - (hintWidth / 2), hintY, 20, LIGHTGRAY);

    // --- BACK BUTTON ---
    Rectangle BackRect = {cx - (200 / 2), hintY + 60, 200, 50};
    Back_btn.label.text = "BACK";
    Back_btn.rect = BackRect;
    Back_btn.Draw(GRAY, BLACK);
}

void MenuSettings::HandleInput(Engine &engine)
{
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    Vector2 mousePoint = GetMousePosition();

    // Handle Volume Adjustments (Clamped 0-100)
    // TODO: Hook these into your Audio System (e.g. Audio::SetMasterVolume(masterVolume / 100.0f))
    if (clicked && CheckCollisionPointRec(mousePoint, MasterMinus_btn.rect))
        if (masterVolume >= 10)
            masterVolume -= 10;

    if (clicked && CheckCollisionPointRec(mousePoint, MasterPlus_btn.rect))
        if (masterVolume <= 90)
            masterVolume += 10;

    if (clicked && CheckCollisionPointRec(mousePoint, MusicMinus_btn.rect))
        if (musicVolume >= 10)
            musicVolume -= 10;

    if (clicked && CheckCollisionPointRec(mousePoint, MusicPlus_btn.rect))
        if (musicVolume <= 90)
            musicVolume += 10;

    if (clicked && CheckCollisionPointRec(mousePoint, SFXMinus_btn.rect))
        if (sfxVolume >= 10)
            sfxVolume -= 10;

    if (clicked && CheckCollisionPointRec(mousePoint, SFXPlus_btn.rect))
        if (sfxVolume <= 90)
            sfxVolume += 10;

    if (clicked && CheckCollisionPointRec(mousePoint, Back_btn.rect))
    {
        engine.ChangeState(new MainMenuState());
    }
}