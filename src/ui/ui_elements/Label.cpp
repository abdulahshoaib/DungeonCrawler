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
    DrawTextEx(Loader::TitleFont, text.c_str(), position, fontSize, spacing, color);
}
