#include "Progressbar.h"

Progressbar::Progressbar()
    : value(0.0f), rect({0, 0, 200, 20}), maxValue(100.0f),
      fillColor({50, 200, 50, 255}), backgroundColor({30, 30, 30, 255})
{
}

Progressbar::~Progressbar()
{
}

void Progressbar::Setup(Rectangle bounds, Color fill, Color bg)
{
    rect = bounds;
    fillColor = fill;
    backgroundColor = bg;
    value = 0.0f;
}

void Progressbar::SetValue(float newValue)
{
    value = newValue;
    if (value > maxValue)
        value = maxValue;
    if (value < 0.0f)
        value = 0.0f;
}

void Progressbar::Draw()
{
    // Draw background
    DrawRectangleRec(rect, backgroundColor);

    // Draw filled portion
    if (value > 0.0f)
    {
        float fillWidth = (value / maxValue) * rect.width;
        Rectangle fillRect = {rect.x, rect.y, fillWidth, rect.height};
        DrawRectangleRec(fillRect, fillColor);
    }

    // Draw border
    DrawRectangleLinesEx(rect, 2, {100, 100, 100, 255});
}