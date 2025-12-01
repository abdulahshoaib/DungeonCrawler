#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TILE_SIZE 32
#define MAP_WIDTH 1000
#define MAP_HEIGHT 70

// Two layers: layer1 is drawn on top of layer2
// layer1: interactables / non-colliding objects (flags, pillars)
// layer2: platforms / collision layer
static int layer1[MAP_WIDTH * MAP_HEIGHT] = {0}; // top layer (interactables)
static int layer2[MAP_WIDTH * MAP_HEIGHT] = {0}; // bottom layer (platforms)

void SaveCSV(const char *filename, int *map)
{
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Failed to save: %s\n", filename);
        return;
    }

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            fprintf(f, "%d", map[y * MAP_WIDTH + x]);
            if (x < MAP_WIDTH - 1)
                fprintf(f, ",");
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Saved map to %s\n", filename);
}

void LoadCSV(const char *filename, int *map) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to load: %s\n", filename);
        return;
    }

    // Large buffer because MAP_WIDTH is large and a single line can be long
    char line[65536];
    int row = 0;

    while (fgets(line, sizeof(line), file) && row < MAP_HEIGHT) {
        int col = 0;
        // strtok modifies buffer; that's fine here
        char *token = strtok(line, ",");
        while (token && col < MAP_WIDTH) {
            // trim leading spaces (optional)
            while (*token == ' ' || *token == '\t') token++;
            map[row * MAP_WIDTH + col] = atoi(token);
            col++;
            token = strtok(NULL, ",");
        }

        // Fill missing columns with 0
        while (col < MAP_WIDTH) {
            map[row * MAP_WIDTH + col] = 0;
            col++;
        }

        row++;
    }

    // Fill extra rows with 0
    while (row < MAP_HEIGHT) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            map[row * MAP_WIDTH + col] = 0;
        }
        row++;
    }

    fclose(file);
    printf("Loaded CSV: %s\n", filename);
}

int main()
{
    const int screenWidth = 1800;
    const int screenHeight = 800;
    // (optional) maximize or omit
    SetConfigFlags(FLAG_WINDOW_MAXIMIZED);

    InitWindow(screenWidth, screenHeight, "Raylib Tilemap Editor - 2 Layers");

    int PALETTE_TILE_SIZE = 36;
    // Load sprite sheet
    Texture2D tileset = LoadTexture("../assets/maps/map.png");
    if (tileset.id == 0) {
        // Warn, but continue — textures may fail if path wrong.
        printf("Warning: failed to load tileset: ../assets/maps/map.png\n");
    }

    int tilesetCols = (tileset.width > 0) ? tileset.width / TILE_SIZE : 1;
    int tilesetRows = (tileset.height > 0) ? tileset.height / TILE_SIZE : 1;
    int totalTiles = tilesetCols * tilesetRows;

    int selectedTile = 1; // tile indexing starts at 1

    // Active editing layer: 1 = top (interactables), 2 = bottom (platforms)
    int activeLayer = 1;

    Vector2 cameraOffset = {0, 0};

    // --- Load previously-saved CSVs on startup ---
    LoadCSV("../assets/maps/map.csv", layer2);            // bottom/platforms
    LoadCSV("../assets/maps/interactables.csv", layer1); // top/interactables

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Input: Move canvas view
        if (IsKeyDown(KEY_RIGHT))
            cameraOffset.x -= 5;
        if (IsKeyDown(KEY_LEFT))
            cameraOffset.x += 5;
        if (IsKeyDown(KEY_DOWN))
            cameraOffset.y -= 5;
        if (IsKeyDown(KEY_UP))
            cameraOffset.y += 5;
        if (IsKeyDown(KEY_EQUAL))
            PALETTE_TILE_SIZE++;
        if (IsKeyDown(KEY_MINUS))
            PALETTE_TILE_SIZE--;

        // Switch active layer with keys 1 and 2
        if (IsKeyPressed(KEY_ONE))
            activeLayer = 1;
        if (IsKeyPressed(KEY_TWO))
            activeLayer = 2;

        // Reload CSVs at runtime (press R)
        if (IsKeyPressed(KEY_R)) {
            LoadCSV("../assets/maps/map.csv", layer2);
            LoadCSV("../assets/maps/interactables.csv", layer1);
            printf("Reloaded both CSV files.\n");
        }

        // Save
        if (IsKeyPressed(KEY_S))
        {
            // Save platforms (bottom layer) as map.csv to keep backwards compatibility
            SaveCSV("../assets/maps/map.csv", layer2);
        }

        if (IsKeyPressed(KEY_I))
        {
            // Save interactables (top layer)
            SaveCSV("../assets/maps/interactables.csv", layer1);
        }

        // Tile placement
        Vector2 mouse = GetMousePosition();

        // Editor canvas area (left 750px)
        if (mouse.x < 750)
        {
            int tileX = (int)((mouse.x - cameraOffset.x) / TILE_SIZE);
            int tileY = (int)((mouse.y - cameraOffset.y) / TILE_SIZE);

            if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT)
            {
                int idx = tileY * MAP_WIDTH + tileX;

                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                {
                    if (activeLayer == 1)
                        layer1[idx] = selectedTile;
                    else
                        layer2[idx] = selectedTile;
                }
                if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
                {
                    if (activeLayer == 1)
                        layer1[idx] = 0;
                    else
                        layer2[idx] = 0;
                }
            }
        }

        // Tile palette click
        if (mouse.x >= 750)
        {
            int px = (int)(mouse.x - 750);
            int py = (int)mouse.y;

            int pCols = tilesetCols;
            int pX = px / PALETTE_TILE_SIZE;
            int pY = py / PALETTE_TILE_SIZE;

            int index = pY * pCols + pX + 1;

            if (index >= 1 && index <= totalTiles)
            {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                {
                    selectedTile = index;
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw map canvas: draw bottom layer (platforms) first, then top layer (interactables)
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                int id2 = layer2[y * MAP_WIDTH + x];
                if (id2 > 0 && tileset.id != 0)
                {
                    int tileIndex = id2 - 1;
                    Rectangle src = { (tileIndex % tilesetCols) * TILE_SIZE,
                                      (tileIndex / tilesetCols) * TILE_SIZE,
                                      TILE_SIZE, TILE_SIZE };
                    DrawTextureRec(tileset, src,
                                   (Vector2){x * TILE_SIZE + cameraOffset.x,
                                             y * TILE_SIZE + cameraOffset.y},
                                   WHITE);
                }

                int id1 = layer1[y * MAP_WIDTH + x];
                if (id1 > 0 && tileset.id != 0)
                {
                    int tileIndex = id1 - 1;
                    Rectangle src = { (tileIndex % tilesetCols) * TILE_SIZE,
                                      (tileIndex / tilesetCols) * TILE_SIZE,
                                      TILE_SIZE, TILE_SIZE };
                    DrawTextureRec(tileset, src,
                                   (Vector2){x * TILE_SIZE + cameraOffset.x,
                                             y * TILE_SIZE + cameraOffset.y},
                                   WHITE);
                }
            }
        }

        // Draw grid (note: drawing 1000 vertical lines can be expensive; consider lowering MAP_WIDTH for editing)
        for (int x = 0; x <= MAP_WIDTH; x++)
        {
            DrawLine(x * TILE_SIZE + cameraOffset.x, cameraOffset.y,
                     x * TILE_SIZE + cameraOffset.x, MAP_HEIGHT * TILE_SIZE + cameraOffset.y,
                     Fade(LIGHTGRAY, 0.3f));
        }
        for (int y = 0; y <= MAP_HEIGHT; y++)
        {
            DrawLine(cameraOffset.x, y * TILE_SIZE + cameraOffset.y,
                     MAP_WIDTH * TILE_SIZE + cameraOffset.x, y * TILE_SIZE + cameraOffset.y,
                     Fade(LIGHTGRAY, 0.3f));
        }

        // Draw palette background (fill right side)
        DrawRectangle(750, 0, screenWidth - 750, screenHeight, GRAY);

        int total = totalTiles;
        for (int i = 0; i < total; i++)
        {
            Rectangle src = { (i % tilesetCols) * TILE_SIZE,
                              (i / tilesetCols) * TILE_SIZE,
                              TILE_SIZE, TILE_SIZE };

            int px = i % tilesetCols;
            int py = i / tilesetCols;

            Rectangle dest = { 750 + px * PALETTE_TILE_SIZE,
                                py * PALETTE_TILE_SIZE,
                                PALETTE_TILE_SIZE,
                                PALETTE_TILE_SIZE };

            if (tileset.id != 0) DrawTexturePro(tileset, src, dest, (Vector2){0, 0}, 0, WHITE);

            if (i + 1 == selectedTile)
            {
                DrawRectangleLines(dest.x, dest.y, dest.width, dest.height, YELLOW);
            }
        }

        // HUD / instructions
        DrawText("Palette, + to Zoom In, - to Zoom Out", screenWidth - 200, 10, 20, WHITE);
        DrawText("Press S to save platforms -> ../assets/maps/map.csv", 10, 10, 20, BLACK);
        DrawText("Press I to save interactables -> ../assets/maps/interactables.csv", 10, 40, 20, BLACK);
        DrawText("Press 1 for Interactables (top layer), 2 for Platforms (bottom layer)", 10, 70, 20, BLACK);
        DrawText("Press R to reload CSVs from disk", 10, 130, 20, BLACK);

        // Active layer indicator
        const char *layerName = (activeLayer == 1) ? "INTERACTABLES (Top)" : "PLATFORMS (Bottom)";
        DrawText(TextFormat("Active Layer: %s", layerName), 10, 100, 20, MAROON);

        EndDrawing();
    }

    UnloadTexture(tileset);
    CloseWindow();
    return 0;
}
