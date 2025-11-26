#pragma once
#include "GameState.h" // <--- 1. Essential Include
#include "UIElement.h"
#include "utils/utils.h"

class Engine;

// 2. Inherit from GameState (Must be PUBLIC)
class Menu : public GameState 
{
public:
    Menu();
    virtual ~Menu();

    // --- THE BRIDGE ---
    // The Engine calls Update/Draw(engine), so we must implement them here
    // and redirect them to your Menu functions.
    
    void Update(Engine& engine) override 
    { 
        HandleInput(engine); 
    }

    void Draw(Engine& engine) override 
    { 
        Draw(); // Menus don't need the engine for drawing
    }

    // --- THE MENU CONTRACT ---
    // Specific menus (MenuMain, Settings) will implement these
    virtual void Draw() = 0;
    virtual void HandleInput(Engine &) = 0;
};