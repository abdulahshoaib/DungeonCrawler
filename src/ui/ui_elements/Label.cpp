#include "Loader.h"
#include "Label.h"

Label::Label() : UIElement()
{
}

void Label::Draw(Color color)
{
    font = Loader::ButtonFont;
    DrawTextEx(font, text.c_str(), position, fontSize, spacing, color);
}
