#pragma once
#include "Menu.h"
#include "ui/ui_elements/Button.h"
#include "ui/ui_elements/Label.h"

class MenuSettings : public Menu
{
private:
    Button Vol_btn;
    Label Settings_lbl;

public:
    MenuSettings();
    void Draw();
    void HandleInput(Engine &);
};