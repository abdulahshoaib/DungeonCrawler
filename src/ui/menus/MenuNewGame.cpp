#include "MenuNewGame.h"
#include "Loader.h"

MenuNewGame::MenuNewGame()
{
}

void MenuNewGame::Draw()
{
    float scale = 0.15f;
    const int nameFontSize = 20;
    const int spacing = 2; // spacing between letters for DrawTextEx

    int startX = 150;
    int startY = 100;

    int spacingX = 200;
    int spacingY = 200;

    Font font = Loader::TitleFont;

    DrawTextureEx(Loader::knight1Potrait, {(float)startX, (float)startY}, 0, scale, WHITE);
    DrawTextEx(font, "Aldric",
               {(float)(startX + 20),
                (float)(startY + Loader::knight1Potrait.height * scale + 10)},
               nameFontSize, spacing, WHITE);

    DrawTextureEx(Loader::knight2Potrait, {(float)(startX + spacingX), (float)startY}, 0, scale, WHITE);
    DrawTextEx(font, "Garron",
               {(float)(startX + spacingX + 20),
                (float)(startY + Loader::knight2Potrait.height * scale + 10)},
               nameFontSize, spacing, WHITE);

    DrawTextureEx(Loader::knight3Potrait, {(float)(startX + spacingX * 2), (float)startY}, 0, scale, WHITE);
    DrawTextEx(font, "Varek",
               {(float)(startX + spacingX * 2 + 25),
                (float)(startY + Loader::knight3Potrait.height * scale + 10)},
               nameFontSize, spacing, WHITE);

    int row2Y = startY + spacingY;

    DrawTextureEx(Loader::samuraiPotrait, {(float)startX, (float)row2Y}, 0, scale, WHITE);
    DrawTextEx(font, "Hiro",
               {(float)(startX + 35),
                (float)(row2Y + Loader::samuraiPotrait.height * scale + 10)},
               nameFontSize, spacing, WHITE);

    DrawTextureEx(Loader::samuraiCommanderPotrait, {(float)(startX + spacingX), (float)row2Y}, 0, scale, WHITE);
    DrawTextEx(font, "Shogun Raiken",
               {(float)(startX + spacingX + 20),
                (float)(row2Y + Loader::samuraiCommanderPotrait.height * scale + 10)},
               nameFontSize, spacing, WHITE);

    DrawTextureEx(Loader::samuraiArcherPotrait, {(float)(startX + spacingX * 2), (float)row2Y}, 0, scale, WHITE);
    DrawTextEx(font, "Hayato", {(float)(startX + spacingX * 2 + 20), (float)(row2Y + Loader::samuraiArcherPotrait.height * scale + 10)},
               nameFontSize, spacing, WHITE);
}

void MenuNewGame::HandleInput(Engine &)
{
}
