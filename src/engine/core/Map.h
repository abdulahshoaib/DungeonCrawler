#pragma once
#include <vector>
#include <string>
#include <raylib.h>

class Map
{
private:
    // store numeric tile indices per row/column
    std::vector<std::vector<int>> tiles;
    int width, height;

    // optional tileset for rendering
    Texture2D tileset;
    int tileSize;

public:
    Map();
    ~Map();

    // load CSV of integers (comma separated)
    void LoadMap(const char *filename);

    // optional: set/load tileset used by DrawMap
    void LoadTileset(const char *tilesetPath, int tileSize = 32);
    void UnloadTileset();

    void DrawMap();
};