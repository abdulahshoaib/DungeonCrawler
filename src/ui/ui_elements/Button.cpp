#include "Button.h"
#include "Loader.h"
#include "Audio.h"

Button::Button()
{
    labelColor = WHITE;
    labelNormalColor = WHITE;
    labelHoverColor = YELLOW;
}

void Button::Draw(Color normalColor, Color hoverColor)
{
    bool isHovering = CheckCollisionPointRec(GetMousePosition(), rect);
    if (isHovering)
    {
        labelColor = labelHoverColor;
        // Play sfx only on hover enter, not every frame
        if (!hovered)
        {
            hovered = true;
            Audio::PlaySFx(BUTTON_CLICKED);
        }
    }
    else
    {
        hovered = false;
        labelColor = labelNormalColor;
    }

    label.fontSize = 26.0f;

    // Center the label text within the button rectangle
    Vector2 textSize = MeasureTextEx(Loader::TitleFont, label.text.c_str(), label.fontSize, label.spacing);
    label.position = {rect.x + (rect.width - textSize.x) / 2, rect.y + (rect.height - textSize.y) / 2};
    label.Draw(labelColor);
}