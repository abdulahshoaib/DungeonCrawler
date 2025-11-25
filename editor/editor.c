#include "raylib.h"
#include <stdio.h>

#define TILE_SIZE 32
#define MAP_WIDTH 100
#define MAP_HEIGHT 50

int map[MAP_WIDTH * MAP_HEIGHT] = {0}; // 0 = empty tile

void SaveCSV(const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f)
        return;

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

int main()
{
    const int screenWidth = 1800;
    const int screenHeight = 800;
    SetConfigFlags(FLAG_WINDOW_MAXIMIZED);

    InitWindow(screenWidth, screenHeight, "Raylib Tilemap Editor");

    int PALETTE_TILE_SIZE = 36;
    // Load sprite sheet
    Texture2D tileset = LoadTexture("../assets/maps/map.png");

    int tilesetCols = tileset.width / TILE_SIZE;
    int tilesetRows = tileset.height / TILE_SIZE;
    int totalTiles = tilesetCols * tilesetRows;

    int selectedTile = 1; // tile indexing starts at 1

    Vector2 cameraOffset = {0, 0};

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

        // Save
        if (IsKeyPressed(KEY_S))
        {
            SaveCSV("../assets/maps/map.csv");
        }

        if (IsKeyPressed(KEY_I))
        {
            SaveCSV("../assets/maps/interactables.csv");
        }

        // Tile placement
        Vector2 mouse = GetMousePosition();

        // Editor canvas area (left 750px)
        if (mouse.x < 750)
        {
            int tileX = (mouse.x - cameraOffset.x) / TILE_SIZE;
            int tileY = (mouse.y - cameraOffset.y) / TILE_SIZE;

            if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT)
            {
                int idx = tileY * MAP_WIDTH + tileX;

                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                {
                    map[idx] = selectedTile;
                }
                if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
                {
                    map[idx] = 0;
                }
            }
        }

        // Tile palette click
        if (mouse.x >= 750)
        {
            int px = mouse.x - 750;
            int py = mouse.y;

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

        // Draw map canvas
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                int id = map[y * MAP_WIDTH + x];
                if (id > 0)
                {
                    int tileIndex = id - 1;
                    Rectangle src = {
                        (tileIndex % tilesetCols) * TILE_SIZE,
                        (tileIndex / tilesetCols) * TILE_SIZE,
                        TILE_SIZE, TILE_SIZE};
                    DrawTextureRec(tileset, src,
                                   (Vector2){x * TILE_SIZE + cameraOffset.x,
                                             y * TILE_SIZE + cameraOffset.y},
                                   WHITE);
                }
            }
        }

        // Draw grid
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

        for (int i = 0; i < totalTiles; i++)
        {
            Rectangle src = {
                (i % tilesetCols) * TILE_SIZE,
                (i / tilesetCols) * TILE_SIZE,
                TILE_SIZE, TILE_SIZE};

            int px = i % tilesetCols;
            int py = i / tilesetCols;

            Rectangle dest = {
                750 + px * PALETTE_TILE_SIZE,
                py * PALETTE_TILE_SIZE,
                PALETTE_TILE_SIZE,
                PALETTE_TILE_SIZE};

            DrawTexturePro(tileset, src, dest, (Vector2){0, 0}, 0, WHITE);

            if (i + 1 == selectedTile)
            {
                DrawRectangleLines(dest.x, dest.y, dest.width, dest.height, YELLOW);
            }
        }

        DrawText("Palette, + to Zoom In, - to Zoom Out", screenWidth - 200, 10, 20, WHITE);
        DrawText("Press S to save map.csv", 10, 10, 20, BLACK);
        DrawText("Press I to save interactables.csv", 10, 40, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}