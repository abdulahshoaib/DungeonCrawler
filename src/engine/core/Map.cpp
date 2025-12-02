#include "Map.h"
#include "Loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Map::Map() : width(0), height(0), tileset({0}), tileSize(32)
{
    tileset = LoadTexture("assets/maps/map.png");
}

void Map::LoadMap(const char *filename)
{
    tiles.clear();
    width = height = 0;

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open map file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        std::vector<int> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ','))
        {
            // trim spaces (optional)
            size_t start = cell.find_first_not_of(" \t\r\n");
            size_t end = cell.find_last_not_of(" \t\r\n");
            if (start == std::string::npos)
                cell = "";
            else
                cell = cell.substr(start, end - start + 1);

            if (cell.empty())
            {
                row.push_back(0);
            }
            else
            {
                try
                {
                    row.push_back(std::stoi(cell));
                }
                catch (...)
                {
                    row.push_back(0);
                }
            }
        }
        if (!row.empty())
        {
            if (width == 0)
                width = (int)row.size();
            tiles.push_back(row);
        }
    }

    height = (int)tiles.size();
    file.close();
}

void Map::DrawMap()
{
    const int h = height;
    const int w = width;
    if (w == 0 || h == 0)
        return;

    if (tileset.id != 0)
    {
        int tilesetCols = tileset.width / tileSize;
        for (int y = 0; y < h; ++y)
        {
            for (int x = 0; x < (int)tiles[y].size(); ++x)
            {
                int id = tiles[y][x];
                if (id <= 0)
                    continue;
                int tileIndex = id - 1; // editor uses 1-based tile ids
                Rectangle src = {
                    (float)((tileIndex % tilesetCols) * tileSize),
                    (float)((tileIndex / tilesetCols) * tileSize),
                    (float)tileSize, (float)tileSize};
                Vector2 dest = {(float)(x * tileSize), (float)(y * tileSize)};
                DrawTextureRec(tileset, src, dest, WHITE);
            }
        }
    }
    else
    {
        // fallback: draw colored rects for tile indices
        for (int y = 0; y < h; ++y)
        {
            for (int x = 0; x < (int)tiles[y].size(); ++x)
            {
                int id = tiles[y][x];
                if (id <= 0)
                    continue;
                Color color = (id % 3 == 0) ? GRAY : (id % 3 == 1) ? DARKGREEN
                                                                   : BROWN;
                DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, color);
            }
        }
    }
}