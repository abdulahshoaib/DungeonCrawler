// GameProgress.cpp
#include "GameProgress.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// Initialize static members
std::string GameProgress::username = "Player";
int GameProgress::points = 0;
Vector2 GameProgress::mapPosition = {0.0f, 0.0f};
int GameProgress::currentLevel = 1;
bool GameProgress::dataLoaded = false;
int GameProgress::currentSlot = 0;
int GameProgress::characterID = 1;
int GameProgress::coinsCollected = 0;
// Remaining coins positions
std::vector<Vector2> GameProgress::remainingCoins = {};

// Setters
void GameProgress::SetUsername(const std::string &name)
{
    username = name;
}

void GameProgress::SetPoints(int newPoints)
{
    points = newPoints;
}

void GameProgress::AddPoints(int pointsToAdd)
{
    points += pointsToAdd;
}

void GameProgress::SetMapPosition(Vector2 position)
{
    mapPosition = position;
}

void GameProgress::SetMapPosition(float x, float y)
{
    mapPosition.x = x;
    mapPosition.y = y;
}

void GameProgress::SetCurrentLevel(int level)
{
    currentLevel = level;
}

void GameProgress::SetCurrentSlot(int slot)
{
    currentSlot = slot;
}

void GameProgress::SetCharacterID(int id)
{
    characterID = id;
}

void GameProgress::AddCoins(int coinsToAdd)
{
    coinsCollected += coinsToAdd;
}

// Getters
std::string GameProgress::GetUsername()
{
    return username;
}

int GameProgress::GetPoints()
{
    return points;
}

Vector2 GameProgress::GetMapPosition()
{
    return mapPosition;
}

int GameProgress::GetCurrentLevel()
{
    return currentLevel;
}

int GameProgress::GetCurrentSlot()
{
    return currentSlot;
}

int GameProgress::GetCharacterID()
{
    return characterID;
}

int GameProgress::GetCoinsCollected()
{
    return coinsCollected;
}

// Helper functions
std::string GameProgress::GetSaveFilePath(int slot)
{
    if (slot < 0)
        slot = currentSlot;
    return "savegame_slot" + std::to_string(slot) + ".dat";
}

bool GameProgress::FileExists(const std::string &filepath)
{
    std::ifstream file(filepath);
    return file.good();
}

// Save progress to file
bool GameProgress::SaveProgress(int slot)
{
    if (slot < 0)
        slot = currentSlot;

    std::string filepath = GetSaveFilePath(slot);
    std::ofstream saveFile(filepath);

    if (!saveFile.is_open())
    {
        std::cerr << "Failed to open save file for writing: " << filepath << std::endl;
        return false;
    }

    // Write data in a structured format
    saveFile << username << std::endl;
    saveFile << characterID << std::endl;
    saveFile << points << std::endl;
    saveFile << mapPosition.x << " " << mapPosition.y << std::endl;
    saveFile << currentLevel << std::endl;

    // Write remaining coins: first the count, then each x y on its own line
    saveFile << remainingCoins.size() << std::endl;
    for (const auto &cp : remainingCoins)
    {
        saveFile << cp.x << " " << cp.y << std::endl;
    }

    saveFile.close();

#ifdef DEBUG
    std::cout << "Progress saved to slot " << slot << " successfully!" << std::endl;
#endif
    return true;
}

// Load progress from file
bool GameProgress::LoadProgress(int slot)
{
    if (slot < 0)
        slot = currentSlot;

    std::string filepath = GetSaveFilePath(slot);

    if (!FileExists(filepath))
    {
#ifdef DEBUG
        std::cout << "No save file found in slot " << slot << ". Starting fresh." << std::endl;
#endif
        return false;
    }

    std::ifstream saveFile(filepath);

    if (!saveFile.is_open())
    {
        std::cerr << "Failed to open save file for reading: " << filepath << std::endl;
        return false;
    }

    // Read data
    std::getline(saveFile, username);
    saveFile >> characterID;
    saveFile >> points;
    saveFile >> mapPosition.x >> mapPosition.y;
    saveFile >> currentLevel;

    // Read remaining coins
    remainingCoins.clear();
    size_t coinCount = 0;
    if (saveFile >> coinCount)
    {
        for (size_t i = 0; i < coinCount; ++i)
        {
            Vector2 p = {0.0f, 0.0f};
            if (saveFile >> p.x >> p.y)
            {
                remainingCoins.push_back(p);
            }
        }
    }

    saveFile.close();
    dataLoaded = true;
    currentSlot = slot;

#ifdef DEBUG
    std::cout << "Progress loaded from slot " << slot << " successfully!" << std::endl;
    std::cout << "Welcome back, " << username << "!" << std::endl;
#endif
    return true;
}

// Reset all progress to defaults
void GameProgress::ResetProgress()
{
    // Reset remaining coins
    remainingCoins.clear();

    username = "Player";
    points = 0;
    mapPosition = {0.0f, 0.0f};
    currentLevel = 1;
    dataLoaded = false;

#ifdef DEBUG
    std::cout << "Progress reset to defaults." << std::endl;
#endif
}

// Check if save data exists
void GameProgress::SetRemainingCoins(const std::vector<Vector2> &coins)
{
    remainingCoins = coins;
}

const std::vector<Vector2> &GameProgress::GetRemainingCoins()
{
    return remainingCoins;
}

bool GameProgress::HasSaveData()
{
    for (int i = 0; i < 3; i++)
    {
        if (FileExists(GetSaveFilePath(i)))
            return true;
    }
    return false;
}

// Check if save data exists in specific slot
bool GameProgress::HasSaveDataInSlot(int slot)
{
    return FileExists(GetSaveFilePath(slot));
}

// Initialize the system (call at game start)
void GameProgress::Initialize()
{
#ifdef DEBUG
    if (HasSaveData())
    {
        std::cout << "Save data found. Can load from main menu." << std::endl;
    }
    else
    {
        std::cout << "No existing save found. Starting new game." << std::endl;
    }
#endif
}

bool GameProgress::IsDataLoaded()
{
    return dataLoaded;
}