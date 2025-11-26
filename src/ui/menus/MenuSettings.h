#pragma once
#include "Menu.h"
#include "ui/ui_elements/Button.h"
#include "ui/ui_elements/Label.h"

class MenuSettings : public Menu
{
private:
    // UI Elements defined in the .cpp file
    Label titleLabel;

    // Volume Control Buttons
    Button MasterMinus_btn, MasterPlus_btn;
    Button MusicMinus_btn, MusicPlus_btn;
    Button SFXMinus_btn, SFXPlus_btn;

    // Labels
    Label Music_lbl, Master_lbl, SFX_lbl;

    // Navigation
    Button Back_btn;

public:
    MenuSettings();
    void Draw(); // Virtual is likely handled in parent Menu class
    void HandleInput(Engine &);
};