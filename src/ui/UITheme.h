#pragma once

#include <raylib.h>

/**
 * UITheme.h - Centralized theme colors and styles for consistent UI appearance
 * This header provides a single source of truth for all UI colors and styling
 */
namespace UITheme
{
    // Primary colors for dungeon aesthetic
    namespace Colors
    {
        // Text colors
        static constexpr ::Color TEXT_PRIMARY = {235, 220, 195, 255}; // Parchment (normal text)
        static constexpr ::Color TEXT_HOVER = {255, 200, 100, 255};   // Gold (interactive)
        static constexpr ::Color TEXT_TITLE = {255, 200, 100, 255};   // Gold (titles)
        static constexpr ::Color TEXT_WHITE = {255, 255, 255, 255};   // White (for emphasis)

        // Health/Status colors
        static constexpr ::Color HEALTH_GREEN = {50, 200, 50, 255}; // Full health
        static constexpr ::Color HEALTH_RED = {200, 50, 50, 255};   // Low health

        // Background colors
        static constexpr ::Color SHADOW = {20, 15, 10, 255};       // Deep shadow
        static constexpr ::Color STONE_DARK = {45, 38, 32, 255};   // Dark stone
        static constexpr ::Color STONE_DARKER = {28, 22, 18, 255}; // Darker stone
        static constexpr ::Color STONE_LIGHT = {65, 55, 45, 255};  // Light stone

        // Accent colors
        static constexpr ::Color ACCENT_GOLD = {255, 200, 100, 255};     // Gold accent
        static constexpr ::Color ACCENT_GOLD_GLOW = {255, 200, 100, 80}; // Gold with transparency
    }

    // Font sizes for consistency
    namespace FontSizes
    {
        static constexpr float TITLE_LARGE = 72.0f;
        static constexpr float TITLE_MEDIUM = 48.0f;
        static constexpr float HEADING = 32.0f;
        static constexpr float NORMAL = 24.0f;
        static constexpr float SMALL = 18.0f;
        static constexpr float TINY = 14.0f;
    }

    // Text rendering helpers
    namespace TextEffects
    {
        /**
         * Draw text with shadow for depth effect
         */
        inline void DrawTextWithShadow(Font font, const std::string &text, Vector2 pos,
                                       float fontSize, float spacing, ::Color color)
        {
            // Shadow
            DrawTextEx(font, text.c_str(), {pos.x + 2, pos.y + 2}, fontSize, spacing, Colors::SHADOW);
            // Main text
            DrawTextEx(font, text.c_str(), pos, fontSize, spacing, color);
        }

        /**
         * Draw text with glow effect for emphasis (titles)
         */
        inline void DrawTextGlow(Font font, const std::string &text, Vector2 pos,
                                 float fontSize, float spacing, ::Color glowColor)
        {
            // Glow layers
            for (int i = 2; i >= 1; i--)
            {
                ::Color glowLayer = {glowColor.r, glowColor.g, glowColor.b, (unsigned char)(50 / i)};
                DrawTextEx(font, text.c_str(), {pos.x - i, pos.y}, fontSize, spacing, glowLayer);
                DrawTextEx(font, text.c_str(), {pos.x + i, pos.y}, fontSize, spacing, glowLayer);
                DrawTextEx(font, text.c_str(), {pos.x, pos.y - i}, fontSize, spacing, glowLayer);
                DrawTextEx(font, text.c_str(), {pos.x, pos.y + i}, fontSize, spacing, glowLayer);
            }
            // Main text
            DrawTextEx(font, text.c_str(), pos, fontSize, spacing, glowColor);
        }
    }

    // Panel drawing helpers
    namespace Panels
    {
        /**
         * Draw a dungeon-style panel with border and shadow
         */
        inline void DrawPanel(Rectangle rect, bool highlighted = false)
        {
            // Outer shadow
            DrawRectangleRec({rect.x + 4, rect.y + 4, rect.width, rect.height}, Colors::SHADOW);

            // Main border
            DrawRectangleRec(rect, Colors::STONE_DARK);

            // Inner groove
            DrawRectangleRec({rect.x + 3, rect.y + 3, rect.width - 6, rect.height - 6}, Colors::STONE_DARKER);

            // Interior
            ::Color interior = highlighted ? (::Color){75, 65, 55, 255} : Colors::STONE_LIGHT;
            DrawRectangleRec({rect.x + 6, rect.y + 6, rect.width - 12, rect.height - 12}, interior);

            // Top highlight
            DrawRectangle(rect.x + 6, rect.y + 6, rect.width - 12, 2, (::Color){85, 75, 60, 120});
        }
    }
}
