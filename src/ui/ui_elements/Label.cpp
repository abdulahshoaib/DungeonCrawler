#include "Loader.h"
#include "Label.h"

Label::Label()
{
}

Label::~Label()
{
}

void Label::Draw(Color color)
{
    if (text == "-" || text == "+")
        DrawText(text.c_str(), position.x - 4, position.y, fontSize, color);

    else
        DrawTextEx(Loader::TitleFont, text.c_str(), position, fontSize, spacing, color);
}
