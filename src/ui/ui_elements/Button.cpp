
#include "Button.h"
#include "Loader.h"

Button::Button() : UIElement()
{
}

void Button::Draw(Color normalColor, Color hoverColor)
{
    if (CheckCollisionPointRec(GetMousePosition(), rect))
    {
        DrawRectangleRec(rect, hoverColor);
    }
    else
    {
        DrawRectangleRec(rect, normalColor);
    }

    label.fontSize = 32.0f;

    // Center the label text within the button rectangle
    Vector2 textSize = MeasureTextEx(label.font, label.text.c_str(), label.fontSize, label.spacing);
    label.position = {rect.x + (rect.width - textSize.x) / 2, rect.y + (rect.height - textSize.y) / 2};
    label.Draw(WHITE);
}
