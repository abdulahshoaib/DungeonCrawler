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
    // How many pixels from the top of a tile to ignore for collision.
    int collisionTopMargin;

public:
    Map();

    // load CSV of integers
    void LoadMap(const char *filename);

    void DrawMap();

    int GetTileSize() const { return tileSize; }
    bool IsSolidTile(int tx, int ty) const;
    bool CheckCollisionRect(const Rectangle &rect) const;

    bool GetFirstCollisionTile(const Rectangle &rect, int &tx, int &ty) const;
    void SetCollisionTopMargin(int margin) { collisionTopMargin = margin; }
    int GetCollisionTopMargin() const { return collisionTopMargin; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    int GetTile(int x, int y) const;      // return tile ID at (x, y)
    void SetTile(int x, int y, int value); // set tile ID at (x, y)
};