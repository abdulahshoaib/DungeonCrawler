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
    // 1. Measure the text width first
    // (We use the same Font, Text, Font Size, and Spacing as the Draw call)
    Vector2 textSize = MeasureTextEx(Loader::TitleFont, typedName.c_str(), 32, 1);

    // 2. Calculate the X coordinate
    // Formula: Box_X + (Box_Width / 2) - (Text_Width / 2)
    float centerPosX = inputBox.x + (inputBox.width / 2) - (textSize.x / 2);
    float centerOfBox = inputBox.x + (inputBox.width / 2);

    // 3. Draw the text at the new calculated X position
    DrawTextEx(Loader::TitleFont, typedName.c_str(), (Vector2){centerPosX, inputBox.y + 15}, 32, 1, YELLOW);
    // 4. Draw the Cursor (Center + Half Width)
    if (typingActive)
    {
        // The cursor sits at the center + half the text width + a tiny padding (2px)
        float cursorX = centerOfBox + (textSize.x / 2) + 2;

        if (((int)(GetTime() * 2)) % 2 == 0)
        {
            // Using DrawTextEx for the cursor ensures it matches the height/style of your font
            DrawTextEx(Loader::TitleFont, "|", (Vector2){cursorX, inputBox.y + 15}, 32, 1, GREEN);
        }
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
