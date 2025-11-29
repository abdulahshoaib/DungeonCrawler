#include "MenuNewGame.h"
#include "Loader.h"
#include "Engine.h"
#include "PlayState.h"

MenuNewGame::MenuNewGame()
{
}

void MenuNewGame::Draw()
{
    DrawTextureEx(Loader::SelectionMenuBackground, {0, 0}, 0, 0.45f, WHITE);
    selectcharacter.text = "SELECT CHARACTER";
    // int size = GetMeasurement
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

    auto DrawPortrait = [&](Texture2D tex, float x, float y)
    {
        DrawTextureEx(tex, {x, y}, 0, scale, WHITE);
        return Rectangle{x, y, (float)tex.width * scale, (float)tex.height * scale};
    };

    rectKnight1 = DrawPortrait(Loader::Knight1Potrait, startX, startY);
    rectKnight2 = DrawPortrait(Loader::Knight2Potrait, startX + stepX, startY);
    rectKnight3 = DrawPortrait(Loader::Knight3Potrait, startX + stepX * 2, startY);

    float row2Y = startY + stepY;

    rectSamurai1 = DrawPortrait(Loader::SamuraiPotrait, startX, row2Y);
    rectSamurai2 = DrawPortrait(Loader::SamuraiCommanderPotrait, startX + stepX, row2Y);
    rectSamurai3 = DrawPortrait(Loader::SamuraiArcherPotrait, startX + stepX * 2, row2Y);

    Vector2 mouse = GetMousePosition();

    auto Hover = [&](Rectangle r)
    {
        if (CheckCollisionPointRec(mouse, r))
            DrawRectangleLinesEx(r, 3, YELLOW);
    };

    Hover(rectKnight1);
    Hover(rectKnight2);
    Hover(rectKnight3);
    Hover(rectSamurai1);
    Hover(rectSamurai2);
    Hover(rectSamurai3);
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