#include "Button.h"
#include "Loader.h"

Button::Button()
{
    labelColor = WHITE;
    labelNormalColor = WHITE;
    labelHoverColor = WHITE;
}

void Button::Draw(Color normalColor, Color hoverColor)
{
    if (CheckCollisionPointRec(GetMousePosition(), rect))
    {
        DrawRectangleRec(rect, hoverColor);
        labelColor = labelHoverColor;
    }
    else
    {
        DrawRectangleRec(rect, normalColor);
        labelColor = labelNormalColor;
    }

    label.fontSize = 26.0f;

    // Center the label text within the button rectangle
    Vector2 textSize = MeasureTextEx(Loader::TitleFont, label.text.c_str(), label.fontSize, label.spacing);
    label.position = {rect.x + (rect.width - textSize.x) / 2, rect.y + (rect.height - textSize.y) / 2};
    label.Draw(labelColor);
}