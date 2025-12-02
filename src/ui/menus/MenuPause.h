// MenuPause.h
#ifndef MENUPAUSE_H
#define MENUPAUSE_H

#include "Button.h"
#include "Engine.h"
#include <vector>

class MenuPause
{
private:
    Button resumeButton;
    Button saveGameButton;
    Button mainMenuButton;
    Button quitButton;
    
    std::vector<Button*> buttons;
    
    void SetupButtons();
    void DrawPauseHeader();
    void DrawPlayerInfo();

public:
    MenuPause();
    void Draw();
    void HandleInput(Engine &engine);
};

#endif // MENUPAUSE_H