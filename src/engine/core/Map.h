#pragma once

class Map
{
private:
    // TODO(demon_slayer): Add a array to load the map data onto
    // NOTE(demon_slayer): There are 2 layers of the map - the platform layer and the interactables layer
public:
    Map();
    ~Map();

    void LoadMap(const char *filename);
    void DrawMap();
};