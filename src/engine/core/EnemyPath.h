#pragma once

#include <raylib.h>
#include <vector>

// Represents a path waypoint that enemies will follow
struct PathNode
{
    Vector2 pos;
    float pauseTime = 0.0f; // Time to pause at this node (optional)
};

// Manages enemy patrol paths
class EnemyPath
{
private:
    std::vector<PathNode> nodes;
    bool isLooping = true;

public:
    EnemyPath() = default;

    void AddNode(Vector2 pos, float pauseTime = 0.0f)
    {
        nodes.push_back({pos, pauseTime});
    }

    void SetLooping(bool loop) { isLooping = loop; }
    bool IsLooping() const { return isLooping; }

    const std::vector<PathNode> &GetNodes() const { return nodes; }
    size_t GetNodeCount() const { return nodes.size(); }

    Vector2 GetNode(size_t index) const
    {
        if (index >= nodes.size())
            return {0, 0};
        return nodes[index].pos;
    }

    float GetPauseTime(size_t index) const
    {
        if (index >= nodes.size())
            return 0.0f;
        return nodes[index].pauseTime;
    }

    bool IsValid() const { return nodes.size() > 0; }

    void Clear() { nodes.clear(); }
};
