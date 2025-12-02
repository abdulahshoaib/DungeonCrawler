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

    // load CSV of integers
    void LoadMap(const char *filename);

    void DrawMap();
};