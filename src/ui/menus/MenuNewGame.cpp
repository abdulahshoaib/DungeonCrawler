#include "MenuNewGame.h"
#include "Loader.h"
#include "Engine.h"
#include "PlayState.h"

MenuNewGame::MenuNewGame()
{
}

void MenuNewGame::Draw()
{

    float scale = 0.15f;
    const int nameFontSize = 20;
    const int spacing = 2;

    int startX = 150;
    int startY = 100;

    int spacingX = 200;
    int spacingY = 200;

    Font font = Loader::TitleFont;

    auto DrawPortrait = [&](Texture2D tex, const char *name, int x, int y)
    {
        DrawTextureEx(tex, {(float)x, (float)y}, 0, scale, WHITE);

        float scaledWidth = tex.width * scale;
        float textWidth = MeasureTextEx(font, name, nameFontSize, spacing).x;

        float textX = x + (scaledWidth / 2) - (textWidth / 2);
        float textY = y + tex.height * scale + 10;

        DrawTextEx(font, name, {textX, textY}, nameFontSize, spacing, WHITE);

        return Rectangle{(float)x, (float)y, scaledWidth, tex.height * scale};
    };

    // ROW 1
    rectKnight1 = DrawPortrait(Loader::knight1Potrait, "Aldric", startX, startY);
    rectKnight2 = DrawPortrait(Loader::knight2Potrait, "Garron", startX + spacingX, startY);
    rectKnight3 = DrawPortrait(Loader::knight3Potrait, "Varek", startX + spacingX * 2, startY);

    // ROW 2
    int row2Y = startY + spacingY;

    rectSamurai1 = DrawPortrait(Loader::samuraiPotrait, "Hiro", startX, row2Y);
    rectSamurai2 = DrawPortrait(Loader::samuraiCommanderPotrait, "Shogun Raiken", startX + spacingX, row2Y);
    rectSamurai3 = DrawPortrait(Loader::samuraiArcherPotrait, "Hayato", startX + spacingX * 2, row2Y);

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