#include "MenuNewGame.h"
#include "Loader.h"
#include "Engine.h"
#include "PlayState.h"
#include "Audio.h"

MenuNewGame::MenuNewGame()
{
    // Initialize hover tracking for all characters
    hoveredKnight1 = false;
    hoveredKnight2 = false;
    hoveredKnight3 = false;
    hoveredSamurai1 = false;
    hoveredSamurai2 = false;
    hoveredSamurai3 = false;
}

MenuNewGame::~MenuNewGame()
{
    // Empty destructor
}

void MenuNewGame::Draw()
{
    DrawTextureEx(Loader::SelectionMenuBackground, {0, 0}, 0, 0.45f, WHITE);
    selectcharacter.text = "SELECT CHARACTER";
    selectcharacter.position = {398, 10};
    selectcharacter.fontSize = 40;
    selectcharacter.Draw(YELLOW);
    
    int screenWidth = 1100;
    int screenHeight = 700;

    float scale = 0.12f;

    float itemW = Loader::Knight1Potrait.width * scale;
    float itemH = Loader::Knight1Potrait.height * scale;

    float paddingX = 30.0f;
    float paddingY = 40.0f;

    float totalContentWidth = (itemW * 3) + (paddingX * 2);
    float totalContentHeight = (itemH * 2) + (paddingY);

    float startX = (screenWidth - totalContentWidth) / 2.0f;
    float startY = (screenHeight - totalContentHeight) / 2.0f;

    float stepX = itemW + paddingX;
    float stepY = itemH + paddingY;

    // Helper function to make card prominent on hover
    auto DrawCardWithEffects = [&](Texture2D tex, float x, float y, bool isHovered)
    {
        Rectangle cardRect = {x, y, (float)tex.width * scale, (float)tex.height * scale};
        
        if (isHovered)
        {
            // Glowing shadow/aura effect
            DrawRectangle(x - 8, y - 8, cardRect.width + 16, cardRect.height + 16, 
                         (Color){255, 200, 100, 60});
            DrawRectangle(x - 5, y - 5, cardRect.width + 10, cardRect.height + 10, 
                         (Color){255, 200, 100, 100});
            
            // Draw card slightly enlarged
            float hoverScale = scale * 1.05f;
            float offsetX = (cardRect.width * 1.05f - cardRect.width) / 2.0f;
            float offsetY = (cardRect.height * 1.05f - cardRect.height) / 2.0f;
            DrawTextureEx(tex, {x - offsetX, y - offsetY}, 0, hoverScale, WHITE);
            
            // Bright glowing border
            Rectangle glowRect = {x - offsetX, y - offsetY, 
                                 (float)tex.width * hoverScale, 
                                 (float)tex.height * hoverScale};
            DrawRectangleLinesEx(glowRect, 3, (Color){255, 200, 100, 255});
            DrawRectangleLinesEx((Rectangle){glowRect.x + 3, glowRect.y + 3, 
                                            glowRect.width - 6, glowRect.height - 6}, 
                                2, (Color){255, 220, 150, 180});
            
            // Corner accent triangles for extra flair
            float cornerSize = 15.0f;
            Color cornerColor = (Color){255, 200, 100, 220};
            
            // Top-left
            DrawTriangle((Vector2){glowRect.x, glowRect.y},
                        (Vector2){glowRect.x + cornerSize, glowRect.y},
                        (Vector2){glowRect.x, glowRect.y + cornerSize},
                        cornerColor);
            
            // Top-right
            DrawTriangle((Vector2){glowRect.x + glowRect.width, glowRect.y},
                        (Vector2){glowRect.x + glowRect.width, glowRect.y + cornerSize},
                        (Vector2){glowRect.x + glowRect.width - cornerSize, glowRect.y},
                        cornerColor);
            
            // Bottom-left
            DrawTriangle((Vector2){glowRect.x, glowRect.y + glowRect.height},
                        (Vector2){glowRect.x, glowRect.y + glowRect.height - cornerSize},
                        (Vector2){glowRect.x + cornerSize, glowRect.y + glowRect.height},
                        cornerColor);
            
            // Bottom-right
            DrawTriangle((Vector2){glowRect.x + glowRect.width, glowRect.y + glowRect.height},
                        (Vector2){glowRect.x + glowRect.width - cornerSize, glowRect.y + glowRect.height},
                        (Vector2){glowRect.x + glowRect.width, glowRect.y + glowRect.height - cornerSize},
                        cornerColor);
            
            return Rectangle{x - offsetX, y - offsetY, glowRect.width, glowRect.height};
        }
        else
        {
            // Normal state - just draw the texture
            DrawTextureEx(tex, {x, y}, 0, scale, WHITE);
            return cardRect;
        }
    };

    Vector2 mouse = GetMousePosition();
    
    // Check hover states first
    bool isHoveringKnight1 = CheckCollisionPointRec(mouse, {startX, startY, itemW, itemH});
    bool isHoveringKnight2 = CheckCollisionPointRec(mouse, {startX + stepX, startY, itemW, itemH});
    bool isHoveringKnight3 = CheckCollisionPointRec(mouse, {startX + stepX * 2, startY, itemW, itemH});
    bool isHoveringSamurai1 = CheckCollisionPointRec(mouse, {startX, startY + stepY, itemW, itemH});
    bool isHoveringSamurai2 = CheckCollisionPointRec(mouse, {startX + stepX, startY + stepY, itemW, itemH});
    bool isHoveringSamurai3 = CheckCollisionPointRec(mouse, {startX + stepX * 2, startY + stepY, itemW, itemH});

    // Draw all cards with hover effects
    rectKnight1 = DrawCardWithEffects(Loader::Knight1Potrait, startX, startY, isHoveringKnight1);
    rectKnight2 = DrawCardWithEffects(Loader::Knight2Potrait, startX + stepX, startY, isHoveringKnight2);
    rectKnight3 = DrawCardWithEffects(Loader::Knight3Potrait, startX + stepX * 2, startY, isHoveringKnight3);
    
    float row2Y = startY + stepY;
    
    rectSamurai1 = DrawCardWithEffects(Loader::SamuraiPotrait, startX, row2Y, isHoveringSamurai1);
    rectSamurai2 = DrawCardWithEffects(Loader::SamuraiCommanderPotrait, startX + stepX, row2Y, isHoveringSamurai2);
    rectSamurai3 = DrawCardWithEffects(Loader::SamuraiArcherPotrait, startX + stepX * 2, row2Y, isHoveringSamurai3);

    // Handle hover sound effects
    auto CheckHoverSound = [&](bool isHovering, bool& wasHovered)
    {
        if (isHovering && !wasHovered)
        {
            wasHovered = true;
            Audio::PlaySFx(BUTTON_HOVER);
        }
        else if (!isHovering)
        {
            wasHovered = false;
        }
    };

    CheckHoverSound(isHoveringKnight1, hoveredKnight1);
    CheckHoverSound(isHoveringKnight2, hoveredKnight2);
    CheckHoverSound(isHoveringKnight3, hoveredKnight3);
    CheckHoverSound(isHoveringSamurai1, hoveredSamurai1);
    CheckHoverSound(isHoveringSamurai2, hoveredSamurai2);
    CheckHoverSound(isHoveringSamurai3, hoveredSamurai3);
}

void MenuNewGame::HandleInput(Engine &engine)
{
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, rectKnight1))
            engine.ChangeState(new PlayState(1));

        if (CheckCollisionPointRec(mouse, rectKnight2))
            engine.ChangeState(new PlayState(2));

        if (CheckCollisionPointRec(mouse, rectKnight3))
            engine.ChangeState(new PlayState(3));

        if (CheckCollisionPointRec(mouse, rectSamurai1))
            engine.ChangeState(new PlayState(4));

        if (CheckCollisionPointRec(mouse, rectSamurai2))
            engine.ChangeState(new PlayState(5));

        if (CheckCollisionPointRec(mouse, rectSamurai3))
            engine.ChangeState(new PlayState(6));
    }
}