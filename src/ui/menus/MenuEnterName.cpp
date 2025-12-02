#include "MenuEnterName.h"
#include "Loader.h"
#include "Engine.h"
#include "PlayState.h"
#include "NewGameState.h"
#include "GameProgress.h"

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
    // Draw retro dungeon-style input box with layered stone effect
    // Outer shadow for depth
    DrawRectangleRec((Rectangle){inputBox.x + 4, inputBox.y + 4, inputBox.width, inputBox.height}, 
                     (Color){20, 15, 10, 180});

    // Main stone border (dark weathered stone)
    DrawRectangleRec(inputBox, (Color){45, 38, 32, 255});

    // Inner darker groove
    DrawRectangleRec((Rectangle){inputBox.x + 3, inputBox.y + 3, 
                     inputBox.width - 6, inputBox.height - 6}, 
                     (Color){28, 22, 18, 255});

    // Actual input area (aged parchment/stone interior)
    DrawRectangleRec((Rectangle){inputBox.x + 6, inputBox.y + 6, 
                     inputBox.width - 12, inputBox.height - 12}, 
                     (Color){65, 55, 45, 255});

    // Top highlight edge (simulates worn stone catching light)
    DrawRectangle(inputBox.x + 6, inputBox.y + 6, inputBox.width - 12, 2, 
                  (Color){85, 75, 60, 120});

    // Bottom shadow groove (depth effect)
    DrawRectangle(inputBox.x + 6, inputBox.y + inputBox.height - 8, 
                  inputBox.width - 12, 2, (Color){20, 15, 10, 160});

    // Corner accent stones (left top and right bottom)
    DrawRectangle(inputBox.x, inputBox.y, 8, 8, (Color){60, 50, 40, 255});
    DrawRectangle(inputBox.x + inputBox.width - 8, inputBox.y + inputBox.height - 8, 
                  8, 8, (Color){35, 28, 22, 255});

    // Decorative rivets/bolts in corners
    DrawCircle(inputBox.x + 10, inputBox.y + 10, 3, (Color){40, 35, 30, 255});
    DrawCircle(inputBox.x + 10, inputBox.y + 10, 2, (Color){55, 48, 40, 255});
    DrawCircle(inputBox.x + inputBox.width - 10, inputBox.y + 10, 3, (Color){40, 35, 30, 255});
    DrawCircle(inputBox.x + inputBox.width - 10, inputBox.y + 10, 2, (Color){55, 48, 40, 255});
    DrawCircle(inputBox.x + 10, inputBox.y + inputBox.height - 10, 3, (Color){40, 35, 30, 255});
    DrawCircle(inputBox.x + 10, inputBox.y + inputBox.height - 10, 2, (Color){55, 48, 40, 255});
    DrawCircle(inputBox.x + inputBox.width - 10, inputBox.y + inputBox.height - 10, 3, (Color){40, 35, 30, 255});
    DrawCircle(inputBox.x + inputBox.width - 10, inputBox.y + inputBox.height - 10, 2, (Color){55, 48, 40, 255});

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
            DrawTextEx(Loader::TitleFont, "|", (Vector2){cursorX, inputBox.y + 15}, 32, 1, YELLOW);
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
            GameProgress::SetUsername(typedName);
            engine.ChangeState(new NewGameState());
        }
    }
}
