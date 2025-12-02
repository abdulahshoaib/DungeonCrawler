#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TILE_SIZE 32
#define MAP_WIDTH 500
#define MAP_HEIGHT 70

// Layers
static int collidingLayer[MAP_WIDTH * MAP_HEIGHT] = {0};     // top - blocks
static int interactablesLayer[MAP_WIDTH * MAP_HEIGHT] = {0}; // middle - interactables
static int nonCollidingLayer[MAP_WIDTH * MAP_HEIGHT] = {0};  // bottom - background/decor

void SaveCSV(const char *filename, int *map)
{
    FILE *f = fopen(filename, "w");
    if (!f)
    {
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

void LoadCSV(const char *filename, int *map)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Failed to load: %s\n", filename);
        return;
    }

    char line[65536];
    int row = 0;

    while (fgets(line, sizeof(line), file) && row < MAP_HEIGHT)
    {
        int col = 0;
        char *token = strtok(line, ",");
        while (token && col < MAP_WIDTH)
        {
            while (*token == ' ' || *token == '\t')
                token++;
            map[row * MAP_WIDTH + col] = atoi(token);
            col++;
            token = strtok(NULL, ",");
        }
        while (col < MAP_WIDTH)
        {
            map[row * MAP_WIDTH + col] = 0;
            col++;
        }
        row++;
    }
    while (row < MAP_HEIGHT)
    {
        for (int col = 0; col < MAP_WIDTH; col++)
            map[row * MAP_WIDTH + col] = 0;
        row++;
    }
    fclose(file);
    printf("Loaded CSV: %s\n", filename);
}

int main()
{
    const int screenWidth = 1800;
    const int screenHeight = 800;
    SetConfigFlags(FLAG_WINDOW_MAXIMIZED);
    InitWindow(screenWidth, screenHeight, "Raylib Tilemap Editor - 3 Layers");

    int PALETTE_TILE_SIZE = 36;
    Texture2D tileset = LoadTexture("../assets/maps/map.png");
    if (tileset.id == 0)
        printf("Warning: failed to load tileset\n");

    int tilesetCols = (tileset.width > 0) ? tileset.width / TILE_SIZE : 1;
    int tilesetRows = (tileset.height > 0) ? tileset.height / TILE_SIZE : 1;
    int totalTiles = tilesetCols * tilesetRows;

    int selectedTile = 1;
    int activeLayer = 1; // 1=Colliding, 2=Interactables, 3=Non-colliding
    Vector2 cameraOffset = {0, 0};
    int lastSavedTile = 0;    // Track which tile was last saved
    int saveDisplayTimer = 0; // Timer to show save message

    // Load CSVs at startup
    LoadCSV("../assets/maps/map.csv", collidingLayer);
    LoadCSV("../assets/maps/interactables.csv", interactablesLayer);
    LoadCSV("../assets/maps/non_colliding.csv", nonCollidingLayer);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Camera movement
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

        // Switch layers: 1=Colliding, 2=Interactables, 3=Non-colliding
        if (IsKeyPressed(KEY_ONE))
            activeLayer = 1;
        if (IsKeyPressed(KEY_TWO))
            activeLayer = 2;
        if (IsKeyPressed(KEY_THREE))
            activeLayer = 3;

        // Reload CSVs
        if (IsKeyPressed(KEY_R))
        {
            LoadCSV("../assets/maps/map.csv", collidingLayer);
            LoadCSV("../assets/maps/interactables.csv", interactablesLayer);
            LoadCSV("../assets/maps/non_colliding.csv", nonCollidingLayer);
            printf("Reloaded all CSV files.\n");
        }

        // Save layers - track what was saved and show timer
        if (IsKeyPressed(KEY_S))
        {
            SaveCSV("../assets/maps/map.csv", collidingLayer);
            lastSavedTile = 1;      // Mark as colliding layer saved
            saveDisplayTimer = 120; // Show for 2 seconds at 60 FPS
        }
        if (IsKeyPressed(KEY_I))
        {
            SaveCSV("../assets/maps/interactables.csv", interactablesLayer);
            lastSavedTile = 2; // Mark as interactables layer saved
            saveDisplayTimer = 120;
        }
        if (IsKeyPressed(KEY_N))
        {
            SaveCSV("../assets/maps/non_colliding.csv", nonCollidingLayer);
            lastSavedTile = 3; // Mark as non-colliding layer saved
            saveDisplayTimer = 120;
        }

        // Decrement timer
        if (saveDisplayTimer > 0)
            saveDisplayTimer--;

        // Tile placement
        Vector2 mouse = GetMousePosition();
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
                        collidingLayer[idx] = selectedTile;
                    else if (activeLayer == 2)
                        interactablesLayer[idx] = selectedTile;
                    else
                        nonCollidingLayer[idx] = selectedTile;
                }
                if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
                {
                    if (activeLayer == 1)
                        collidingLayer[idx] = 0;
                    else if (activeLayer == 2)
                        interactablesLayer[idx] = 0;
                    else
                        nonCollidingLayer[idx] = 0;
                }
            }
        }

        // Tile palette selection
        if (mouse.x >= 750)
        {
            int px = (int)(mouse.x - 750);
            int py = (int)mouse.y;
            int pCols = tilesetCols;
            int pX = px / PALETTE_TILE_SIZE;
            int pY = py / PALETTE_TILE_SIZE;
            int index = pY * pCols + pX + 1;
            if (index >= 1 && index <= totalTiles && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                selectedTile = index;
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw layers: bottom → middle → top
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                int id = nonCollidingLayer[y * MAP_WIDTH + x];
                if (id > 0 && tileset.id != 0)
                {
                    int tileIndex = id - 1;
                    Rectangle src = {(tileIndex % tilesetCols) * TILE_SIZE, (tileIndex / tilesetCols) * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                    DrawTextureRec(tileset, src, (Vector2){x * TILE_SIZE + cameraOffset.x, y * TILE_SIZE + cameraOffset.y}, WHITE);
                }
                id = interactablesLayer[y * MAP_WIDTH + x];
                if (id > 0 && tileset.id != 0)
                {
                    int tileIndex = id - 1;
                    Rectangle src = {(tileIndex % tilesetCols) * TILE_SIZE, (tileIndex / tilesetCols) * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                    DrawTextureRec(tileset, src, (Vector2){x * TILE_SIZE + cameraOffset.x, y * TILE_SIZE + cameraOffset.y}, WHITE);
                }
                id = collidingLayer[y * MAP_WIDTH + x];
                if (id > 0 && tileset.id != 0)
                {
                    int tileIndex = id - 1;
                    Rectangle src = {(tileIndex % tilesetCols) * TILE_SIZE, (tileIndex / tilesetCols) * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                    DrawTextureRec(tileset, src, (Vector2){x * TILE_SIZE + cameraOffset.x, y * TILE_SIZE + cameraOffset.y}, WHITE);
                }
            }
        }

        // Draw tile numbers overlay for active layer
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                int *activeLayerData = (activeLayer == 1) ? collidingLayer : (activeLayer == 2) ? interactablesLayer
                                                                                                : nonCollidingLayer;
                int id = activeLayerData[y * MAP_WIDTH + x];

                if (id > 0)
                {
                    float drawX = x * TILE_SIZE + cameraOffset.x + 2;
                    float drawY = y * TILE_SIZE + cameraOffset.y + 2;
                    DrawText(TextFormat("%d", id), (int)drawX, (int)drawY, 10, BLACK);
                }
            }
        }

        // Draw grid
        for (int x = 0; x <= MAP_WIDTH; x++)
            DrawLine(x * TILE_SIZE + cameraOffset.x, cameraOffset.y, x * TILE_SIZE + cameraOffset.x, MAP_HEIGHT * TILE_SIZE + cameraOffset.y, Fade(LIGHTGRAY, 0.3f));
        for (int y = 0; y <= MAP_HEIGHT; y++)
            DrawLine(cameraOffset.x, y * TILE_SIZE + cameraOffset.y, MAP_WIDTH * TILE_SIZE + cameraOffset.x, y * TILE_SIZE + cameraOffset.y, Fade(LIGHTGRAY, 0.3f));

        // Palette background
        DrawRectangle(750, 0, screenWidth - 750, screenHeight, GRAY);

        for (int i = 0; i < totalTiles; i++)
        {
            Rectangle src = {(i % tilesetCols) * TILE_SIZE, (i / tilesetCols) * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            int px = i % tilesetCols;
            int py = i / tilesetCols;
            Rectangle dest = {750 + px * PALETTE_TILE_SIZE, py * PALETTE_TILE_SIZE, PALETTE_TILE_SIZE, PALETTE_TILE_SIZE};
            if (tileset.id != 0)
                DrawTexturePro(tileset, src, dest, (Vector2){0, 0}, 0, WHITE);
            if (i + 1 == selectedTile)
                DrawRectangleLines(dest.x, dest.y, dest.width, dest.height, YELLOW);
        }

        // HUD / instructions
        DrawText("Palette, + to Zoom In, - to Zoom Out", screenWidth - 200, 10, 20, WHITE);
        DrawText("S=Save Colliding, I=Save Interactables, N=Save Non-Colliding", 10, 10, 20, BLACK);
        DrawText("1=Colliding (top), 2=Interactables, 3=Non-Colliding", 10, 40, 20, BLACK);
        DrawText("R=Reload all CSVs", 10, 70, 20, BLACK);
        const char *layerName = (activeLayer == 1) ? "COLLIDING" : (activeLayer == 2) ? "INTERACTABLES"
                                                                                      : "NON-COLLIDING";
        DrawText(TextFormat("Active Layer: %s", layerName), 10, 100, 20, MAROON);

        // Draw selected tile indicator button
        Rectangle tileButtonRect = {10, 130, 200, 50};
        DrawRectangleRec(tileButtonRect, BLUE);
        DrawRectangleLinesEx(tileButtonRect, 2, DARKBLUE);
        DrawText(TextFormat("Selected Tile: %d", selectedTile), 20, 140, 20, BLACK);

        // Draw save status button - appears when something was just saved
        if (saveDisplayTimer > 0)
        {
            Rectangle saveButtonRect = {220, 130, 250, 50};
            Color saveColor = (saveDisplayTimer > 60) ? LIME : YELLOW;
            DrawRectangleRec(saveButtonRect, saveColor);
            DrawRectangleLinesEx(saveButtonRect, 2, BLACK);
            const char *savedLayerName = (lastSavedTile == 1) ? "COLLIDING" : (lastSavedTile == 2) ? "INTERACTABLES"
                                                                                                   : "NON-COLLIDING";
            DrawText(TextFormat("SAVED: %s", savedLayerName), 230, 140, 20, BLACK);
        }

        EndDrawing();
    }

    UnloadTexture(tileset);
    CloseWindow();
    return 0;
}
