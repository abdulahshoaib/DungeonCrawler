#include "MenuEnterName.h"
#include "Loader.h"
#include "Engine.h"
#include "PlayState.h"
#include "NewGameState.h"

// Shared variables for both Draw() and HandleInput()
static Rectangle inputBox = {(1100 - 400) / 2, (700 - 60) / 2, 400, 60};
static std::string typedName = "";
static bool typingActive = false;
Font InputFont = LoadFont("assets\fonts\titleFont.otf");

MenuEnterName::MenuEnterName()
{
}

void MenuEnterName::Draw()
{
    // Background
    DrawTextureEx(Loader::SelectionMenuBackground, {0, 0}, 0, 0.45f, WHITE);

    // Heading
    Label enter;
    enter.text = "ENTER YOUR NAME";
    enter.position = {368, 230};
    enter.fontSize = 40;
    enter.Draw(YELLOW);

    Vector2 mouse = GetMousePosition();

    // Highlight if mouse is over
    Color border = DARKGRAY;
    if (CheckCollisionPointRec(mouse, inputBox))
        border = YELLOW;

    // DrawRectangleLinesEx(inputBox, 3, border);
    //  Draw input box background
    DrawRectangleRec(inputBox, BLACK);

        // Draw text inside
    DrawText(typedName.c_str(), inputBox.x + 15, inputBox.y + 15, 32, YELLOW); // was 100 → 32

    // Blinking cursor if active
    if (typingActive)
    {
        float cx = inputBox.x + 18 + MeasureText(typedName.c_str(), 32);
        if (((int)(GetTime() * 2)) % 2 == 0)
            DrawText("|", cx, inputBox.y + 15, 32, GREEN); // was WHITE → BLACK
    }

    // Store values for HandleInput
    // No pointers — just static references
}
void MenuEnterName::HandleInput(Engine &engine)
{

    Vector2 mouse = GetMousePosition();

    // Mouse click activates input
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        typingActive = CheckCollisionPointRec(mouse, inputBox);
    }

    // Typed input only when active
    if (typingActive)
    {
        int key = GetCharPressed();
        while (key > 0)
        {
            if (key >= 32 && key <= 125 && typedName.length() < 20)
                typedName.push_back((char)key);

            key = GetCharPressed();
        }

        // Backspace
        if (IsKeyPressed(KEY_BACKSPACE) && !typedName.empty())
            typedName.pop_back();

        // ENTER → go to next screen
        if (IsKeyPressed(KEY_ENTER) && !typedName.empty())
        {
            engine.ChangeState(new NewGameState());
        }
    }
}
