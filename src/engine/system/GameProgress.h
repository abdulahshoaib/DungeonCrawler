#pragma once

#include <string>
#include <raylib.h>
#include <vector>

class GameProgress
{
private:
    // Private constructor to prevent instantiation
    GameProgress() = delete;
    ~GameProgress() = delete;
    GameProgress(const GameProgress &) = delete;
    GameProgress &operator=(const GameProgress &) = delete;

    // Internal data storage
    static std::string username;
    static int points;
    static Vector2 mapPosition;
    static int currentLevel;
    static bool dataLoaded;
    static int currentSlot;
    static int characterID;
    static int coinsCollected;
    // Remaining coins positions saved with the progress
    static std::vector<Vector2> remainingCoins;

    // Helper functions for file operations
    static std::string GetSaveFilePath(int slot = -1);
    static bool FileExists(const std::string &filepath);

public:
    // Setters
    static void SetUsername(const std::string &name);
    static void SetPoints(int newPoints);
    static void AddPoints(int pointsToAdd);
    static void SetMapPosition(Vector2 position);
    static void SetMapPosition(float x, float y);
    static void SetCurrentLevel(int level);
    static void SetCurrentSlot(int slot);
    static void SetCharacterID(int id);
    static void AddCoins(int coinsToAdd);

    // Getters
    static std::string GetUsername();
    static int GetPoints();
    static Vector2 GetMapPosition();
    static int GetCurrentLevel();
    static int GetCurrentSlot();
    static int GetCharacterID();
    static int GetCoinsCollected();

    // Save/Load operations
    static bool SaveProgress(int slot = -1);
    static bool LoadProgress(int slot = -1);
    // Remaining coins accessors
    static void SetRemainingCoins(const std::vector<Vector2> &coins);
    static const std::vector<Vector2> &GetRemainingCoins();
    static void ResetProgress();

    // Utility
    static bool HasSaveData();
    static bool HasSaveDataInSlot(int slot);
    static void Initialize();
    static bool IsDataLoaded();
};
