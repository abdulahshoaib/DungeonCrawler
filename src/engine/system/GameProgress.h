#pragma once

#include <string>
#include <raylib.h>

class GameProgress
{
private:
    // Private constructor to prevent instantiation
    GameProgress() = delete;
    ~GameProgress() = delete;
    GameProgress(const GameProgress&) = delete;
    GameProgress& operator=(const GameProgress&) = delete;

    // Internal data storage
    static std::string username;
    static int points;
    static Vector2 mapPosition;
    static int currentLevel;
    static bool dataLoaded;

    // Helper functions for file operations
    static std::string GetSaveFilePath();
    static bool FileExists(const std::string& filepath);

public:
    // Setters
    static void SetUsername(const std::string& name);
    static void SetPoints(int newPoints);
    static void AddPoints(int pointsToAdd);
    static void SetMapPosition(Vector2 position);
    static void SetMapPosition(float x, float y);
    static void SetCurrentLevel(int level);

    // Getters
    static std::string GetUsername();
    static int GetPoints();
    static Vector2 GetMapPosition();
    static int GetCurrentLevel();

    // Save/Load operations
    static bool SaveProgress();
    static bool LoadProgress();
    static void ResetProgress();

    // Utility
    static bool HasSaveData();
    static void Initialize();
};
