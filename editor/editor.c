#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TILE_SIZE 32
#define MAP_WIDTH 500
#define MAP_HEIGHT 70
#define MAX_PATHS 50
#define MAX_NODES_PER_PATH 20

// Layers
static int collidingLayer[MAP_WIDTH * MAP_HEIGHT] = {0};     // top - blocks
static int interactablesLayer[MAP_WIDTH * MAP_HEIGHT] = {0}; // middle - interactables
static int nonCollidingLayer[MAP_WIDTH * MAP_HEIGHT] = {0};  // bottom - background/decor

// Enemy path data structure
typedef struct
{
    int nodeX[MAX_NODES_PER_PATH];
    int nodeY[MAX_NODES_PER_PATH];
    float pauseTime[MAX_NODES_PER_PATH];
    int nodeCount;
    int isLooping;
} EnemyPath;

static EnemyPath paths[MAX_PATHS] = {0};
static int pathCount = 0;

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

void SavePathsCSV(const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f)
    {
        printf("Failed to save paths: %s\n", filename);
        return;
    }

    // First line: number of paths
    fprintf(f, "%d\n", pathCount);

    // Each path: pathIndex,nodeCount,isLooping,nodeX1,nodeY1,pauseTime1,nodeX2,nodeY2,pauseTime2,...
    for (int p = 0; p < pathCount; p++)
    {
        EnemyPath *path = &paths[p];
        fprintf(f, "%d,%d,%d", p, path->nodeCount, path->isLooping);

        for (int n = 0; n < path->nodeCount; n++)
        {
            fprintf(f, ",%d,%d,%.1f", path->nodeX[n], path->nodeY[n], path->pauseTime[n]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Saved paths to %s\n", filename);
}

void LoadPathsCSV(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("No existing path file: %s (creating new)\n", filename);
        pathCount = 0;
        return;
    }

    char line[65536];

    // Read number of paths
    if (fgets(line, sizeof(line), file))
    {
        pathCount = atoi(line);
    }

    // Read each path
    for (int p = 0; p < pathCount && p < MAX_PATHS; p++)
    {
        if (fgets(line, sizeof(line), file))
        {
            EnemyPath *path = &paths[p];
            int pathIndex;
            int nodeCount;
            int isLooping;

            // Parse first three values
            int parsed = sscanf(line, "%d,%d,%d", &pathIndex, &nodeCount, &isLooping);
            path->nodeCount = nodeCount;
            path->isLooping = isLooping;

            // Parse remaining values (coordinates and pause times)
            char *ptr = line;
            int commaCount = 0;
            while (*ptr && commaCount < 3)
            {
                if (*ptr == ',')
                    commaCount++;
                ptr++;
            }

            // Parse nodes
            for (int n = 0; n < nodeCount && n < MAX_NODES_PER_PATH; n++)
            {
                int x, y;
                float pauseTime;
                int result = sscanf(ptr, "%d,%d,%f", &x, &y, &pauseTime);
                if (result == 3)
                {
                    path->nodeX[n] = x;
                    path->nodeY[n] = y;
                    path->pauseTime[n] = pauseTime;

                    // Skip to next triplet
                    while (*ptr && *ptr != ',')
                        ptr++;
                    if (*ptr)
                        ptr++; // skip comma
                    while (*ptr && *ptr != ',')
                        ptr++;
                    if (*ptr)
                        ptr++; // skip comma
                    while (*ptr && *ptr != ',')
                        ptr++;
                    if (*ptr)
                        ptr++; // skip comma
                }
            }
        }
    }

    fclose(file);
    printf("Loaded %d paths from %s\n", pathCount, filename);
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
    int activeLayer = 1; // 1=Colliding, 2=Interactables, 3=Non-colliding, 4=Enemy Paths
    Vector2 cameraOffset = {0, 0};
    int lastSavedTile = 0;    // Track which tile was last saved
    int saveDisplayTimer = 0; // Timer to show save message

    // Path editing variables
    int selectedPath = 0;  // Currently editing which path (0-based)
    int editingPath = 0;   // Whether we're in path editing mode
    int pathPauseTime = 1; // Default pause time for new nodes

    // Load CSVs at startup
    LoadCSV("../assets/maps/map.csv", collidingLayer);
    LoadCSV("../assets/maps/interactables.csv", interactablesLayer);
    LoadCSV("../assets/maps/non_colliding.csv", nonCollidingLayer);
    LoadPathsCSV("../assets/maps/enemy_paths.csv");

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

        // Switch layers: 1=Colliding, 2=Interactables, 3=Non-colliding, 4=Enemy Paths
        if (IsKeyPressed(KEY_ONE))
            activeLayer = 1;
        if (IsKeyPressed(KEY_TWO))
            activeLayer = 2;
        if (IsKeyPressed(KEY_THREE))
            activeLayer = 3;
        if (IsKeyPressed(KEY_FOUR))
            activeLayer = 4;

        // Reload CSVs
        if (IsKeyPressed(KEY_R))
        {
            LoadCSV("../assets/maps/map.csv", collidingLayer);
            LoadCSV("../assets/maps/interactables.csv", interactablesLayer);
            LoadCSV("../assets/maps/non_colliding.csv", nonCollidingLayer);
            LoadPathsCSV("../assets/maps/enemy_paths.csv");
            printf("Reloaded all CSV files and paths.\n");
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
        if (IsKeyPressed(KEY_P))
        {
            SavePathsCSV("../assets/maps/enemy_paths.csv");
            lastSavedTile = 4; // Mark as paths saved
            saveDisplayTimer = 120;
        }

        // Path editing controls
        if (activeLayer == 4)
        {
            // Create new path with SPACE
            if (IsKeyPressed(KEY_SPACE) && pathCount < MAX_PATHS)
            {
                selectedPath = pathCount;
                paths[pathCount].nodeCount = 0;
                paths[pathCount].isLooping = 1;
                pathCount++;
                printf("Created new path %d\n", selectedPath);
            }

            // Switch between paths with UP/DOWN arrows
            if (IsKeyPressed(KEY_UP) && selectedPath > 0)
                selectedPath--;
            if (IsKeyPressed(KEY_DOWN) && selectedPath < pathCount - 1)
                selectedPath++;

            // Toggle looping with L
            if (IsKeyPressed(KEY_L) && selectedPath < pathCount)
            {
                paths[selectedPath].isLooping = !paths[selectedPath].isLooping;
                printf("Path %d looping: %s\n", selectedPath, paths[selectedPath].isLooping ? "ON" : "OFF");
            }

            // Increase/decrease pause time with +/-
            if (IsKeyPressed(KEY_EQUAL))
                pathPauseTime = (int)pathPauseTime + 1;
            if (IsKeyPressed(KEY_MINUS))
                pathPauseTime = (int)pathPauseTime > 0 ? pathPauseTime - 1 : 0;

            // Delete last node with D
            if (IsKeyPressed(KEY_D) && selectedPath < pathCount && paths[selectedPath].nodeCount > 0)
            {
                paths[selectedPath].nodeCount--;
                printf("Deleted node from path %d\n", selectedPath);
            }

            // Clear all nodes with BACKSPACE
            if (IsKeyPressed(KEY_BACKSPACE) && selectedPath < pathCount)
            {
                paths[selectedPath].nodeCount = 0;
                printf("Cleared path %d\n", selectedPath);
            }
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

                // Path editing (layer 4)
                if (activeLayer == 4)
                {
                    if (selectedPath < pathCount)
                    {
                        EnemyPath *curPath = &paths[selectedPath];
                        // Left click to add node
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && curPath->nodeCount < MAX_NODES_PER_PATH)
                        {
                            curPath->nodeX[curPath->nodeCount] = tileX;
                            curPath->nodeY[curPath->nodeCount] = tileY;
                            curPath->pauseTime[curPath->nodeCount] = pathPauseTime;
                            curPath->nodeCount++;
                            printf("Added node %d to path %d at (%d,%d) with pause %.1f\n",
                                   curPath->nodeCount - 1, selectedPath, tileX, tileY, pathPauseTime);
                        }
                    }
                }
                // Tile editing (layers 1-3)
                else
                {
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                    {
                        if (activeLayer == 1)
                            collidingLayer[idx] = selectedTile;
                        else if (activeLayer == 2)
                            interactablesLayer[idx] = selectedTile;
                        else if (activeLayer == 3)
                            nonCollidingLayer[idx] = selectedTile;
                    }
                    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
                    {
                        if (activeLayer == 1)
                            collidingLayer[idx] = 0;
                        else if (activeLayer == 2)
                            interactablesLayer[idx] = 0;
                        else if (activeLayer == 3)
                            nonCollidingLayer[idx] = 0;
                    }
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

        // Draw all enemy paths
        for (int p = 0; p < pathCount; p++)
        {
            EnemyPath *path = &paths[p];
            Color pathColor = (p == selectedPath) ? YELLOW : BLUE;
            Color nodeColor = (p == selectedPath) ? ORANGE : DARKBLUE;

            // Draw path lines connecting nodes
            for (int n = 0; n < path->nodeCount - 1; n++)
            {
                Vector2 node1 = {path->nodeX[n] * TILE_SIZE + TILE_SIZE / 2 + cameraOffset.x,
                                 path->nodeY[n] * TILE_SIZE + TILE_SIZE / 2 + cameraOffset.y};
                Vector2 node2 = {path->nodeX[n + 1] * TILE_SIZE + TILE_SIZE / 2 + cameraOffset.x,
                                 path->nodeY[n + 1] * TILE_SIZE + TILE_SIZE / 2 + cameraOffset.y};
                DrawLineEx(node1, node2, 2.0f, pathColor);
            }

            // Draw waypoint circles
            for (int n = 0; n < path->nodeCount; n++)
            {
                Vector2 nodePos = {path->nodeX[n] * TILE_SIZE + TILE_SIZE / 2 + cameraOffset.x,
                                   path->nodeY[n] * TILE_SIZE + TILE_SIZE / 2 + cameraOffset.y};
                DrawCircle(nodePos.x, nodePos.y, 6.0f, nodeColor);
                DrawCircleLines(nodePos.x, nodePos.y, 6.0f, pathColor);

                // Draw node index
                DrawText(TextFormat("%d", n), nodePos.x - 4, nodePos.y - 4, 8, BLACK);
            }

            // Draw looping indicator
            if (path->isLooping && path->nodeCount > 1)
            {
                Vector2 lastNode = {path->nodeX[path->nodeCount - 1] * TILE_SIZE + TILE_SIZE / 2 + cameraOffset.x,
                                    path->nodeY[path->nodeCount - 1] * TILE_SIZE + TILE_SIZE / 2 + cameraOffset.y};
                Vector2 firstNode = {path->nodeX[0] * TILE_SIZE + TILE_SIZE / 2 + cameraOffset.x,
                                     path->nodeY[0] * TILE_SIZE + TILE_SIZE / 2 + cameraOffset.y};
                DrawLineEx(lastNode, firstNode, 1.5f, Fade(pathColor, 0.5f));
            }
        }

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
        DrawText("S=Save Colliding, I=Interactables, N=Non-Colliding, P=Paths", 10, 10, 20, BLACK);
        DrawText("1=Colliding, 2=Interactables, 3=Non-Colliding, 4=Enemy Paths", 10, 40, 20, BLACK);
        DrawText("Paths: SPACE=New, UP/DOWN=Select, L=Toggle Loop, +/-=PauseTime, D=DelNode, BKSP=Clear", 10, 70, 16, BLACK);
        DrawText("R=Reload all CSVs", 10, 100, 20, BLACK);
        const char *layerName = (activeLayer == 1) ? "COLLIDING" : (activeLayer == 2) ? "INTERACTABLES"
                                                               : (activeLayer == 3)   ? "NON-COLLIDING"
                                                                                      : "ENEMY PATHS";
        DrawText(TextFormat("Active Layer: %s", layerName), 10, 100, 20, MAROON);

        // Draw selected tile indicator button
        Rectangle tileButtonRect = {10, 130, 200, 50};
        DrawRectangleRec(tileButtonRect, BLUE);
        DrawRectangleLinesEx(tileButtonRect, 2, DARKBLUE);
        if (activeLayer == 4)
        {
            DrawText(TextFormat("Path %d: %d nodes | Pause: %.1f", selectedPath,
                                selectedPath < pathCount ? paths[selectedPath].nodeCount : 0,
                                pathPauseTime),
                     20, 140, 16, BLACK);
        }
        else
        {
            DrawText(TextFormat("Selected Tile: %d", selectedTile), 20, 140, 20, BLACK);
        }

        // Draw save status button - appears when something was just saved
        if (saveDisplayTimer > 0)
        {
            Rectangle saveButtonRect = {220, 130, 250, 50};
            Color saveColor = (saveDisplayTimer > 60) ? LIME : YELLOW;
            DrawRectangleRec(saveButtonRect, saveColor);
            DrawRectangleLinesEx(saveButtonRect, 2, BLACK);
            const char *savedLayerName = (lastSavedTile == 1) ? "COLLIDING" : (lastSavedTile == 2) ? "INTERACTABLES"
                                                                          : (lastSavedTile == 3)   ? "NON-COLLIDING"
                                                                                                   : "PATHS";
            DrawText(TextFormat("SAVED: %s", savedLayerName), 230, 140, 20, BLACK);
        }

        EndDrawing();
    }

    UnloadTexture(tileset);
    CloseWindow();
    return 0;
}
