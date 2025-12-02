#include "Button.h"
#include "Loader.h"
#include "Audio.h"

Button::Button()
{
    labelColor = WHITE;
    labelNormalColor = (Color){235, 220, 195, 255}; // Aged parchment color
    labelHoverColor = (Color){255, 200, 100, 255}; // Glowing amber
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

    // Draw retro dungeon-style button background
    
    // Outer shadow for depth
    DrawRectangleRec((Rectangle){rect.x + 4, rect.y + 4, rect.width, rect.height}, 
                     (Color){20, 15, 10, 180});
    
    // Main stone border (dark weathered stone)
    DrawRectangleRec(rect, (Color){45, 38, 32, 255});
    
    // Inner darker groove
    DrawRectangleRec((Rectangle){rect.x + 3, rect.y + 3, rect.width - 6, rect.height - 6}, 
                     (Color){28, 22, 18, 255});
    
    // Actual button interior (changes slightly on hover)
    Color interiorColor = isHovering ? (Color){75, 65, 55, 255} : (Color){65, 55, 45, 255};
    DrawRectangleRec((Rectangle){rect.x + 6, rect.y + 6, rect.width - 12, rect.height - 12}, 
                     interiorColor);
    
    // Top highlight edge (simulates worn stone catching light)
    DrawRectangle(rect.x + 6, rect.y + 6, rect.width - 12, 2, 
                  (Color){85, 75, 60, 120});
    
    // Bottom shadow groove (depth effect)
    DrawRectangle(rect.x + 6, rect.y + rect.height - 8, rect.width - 12, 2, 
                  (Color){20, 15, 10, 160});
    
    // Corner accent stones (left top and right bottom)
    DrawRectangle(rect.x, rect.y, 8, 8, (Color){60, 50, 40, 255});
    DrawRectangle(rect.x + rect.width - 8, rect.y + rect.height - 8, 8, 8, 
                  (Color){35, 28, 22, 255});
    
    // Decorative rivets/bolts in corners
    DrawCircle(rect.x + 10, rect.y + 10, 3, (Color){40, 35, 30, 255});
    DrawCircle(rect.x + 10, rect.y + 10, 2, (Color){55, 48, 40, 255});
    
    DrawCircle(rect.x + rect.width - 10, rect.y + 10, 3, (Color){40, 35, 30, 255});
    DrawCircle(rect.x + rect.width - 10, rect.y + 10, 2, (Color){55, 48, 40, 255});
    
    DrawCircle(rect.x + 10, rect.y + rect.height - 10, 3, (Color){40, 35, 30, 255});
    DrawCircle(rect.x + 10, rect.y + rect.height - 10, 2, (Color){55, 48, 40, 255});
    
    DrawCircle(rect.x + rect.width - 10, rect.y + rect.height - 10, 3, (Color){40, 35, 30, 255});
    DrawCircle(rect.x + rect.width - 10, rect.y + rect.height - 10, 2, (Color){55, 48, 40, 255});
    
    // Optional: Add subtle glow effect on hover
    if (isHovering)
    {
        // Inner glow
        DrawRectangleLinesEx((Rectangle){rect.x + 5, rect.y + 5, rect.width - 10, rect.height - 10}, 
                            1, (Color){255, 200, 100, 80});
    }

    label.fontSize = 26.0f;

    // Center the label text within the button rectangle
    Vector2 textSize = MeasureTextEx(Loader::TitleFont, label.text.c_str(), label.fontSize, label.spacing);
    label.position = {rect.x + (rect.width - textSize.x) / 2, rect.y + (rect.height - textSize.y) / 2};
    
    // Draw text shadow for depth
    DrawTextEx(Loader::TitleFont, label.text.c_str(), 
               {label.position.x + 2, label.position.y + 2}, 
               label.fontSize, label.spacing, 
               (Color){20, 15, 10, 180});
    
    // Draw main text
    label.Draw(labelColor);
}