// GameProgress.cpp
#include "GameProgress.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Initialize static members
std::string GameProgress::username = "Player";
int GameProgress::points = 0;
Vector2 GameProgress::mapPosition = {0.0f, 0.0f};
int GameProgress::currentLevel = 1;
bool GameProgress::dataLoaded = false;
int GameProgress::currentSlot = 0;
int GameProgress::characterID = 1;

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

    saveFile.close();

    std::cout << "Progress saved to slot " << slot << " successfully!" << std::endl;
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
        std::cout << "No save file found in slot " << slot << ". Starting fresh." << std::endl;
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

    saveFile.close();
    dataLoaded = true;
    currentSlot = slot;

    std::cout << "Progress loaded from slot " << slot << " successfully!" << std::endl;
    std::cout << "Welcome back, " << username << "!" << std::endl;
    return true;
}

// Reset all progress to defaults
void GameProgress::ResetProgress()
{
    username = "Player";
    points = 0;
    mapPosition = {0.0f, 0.0f};
    currentLevel = 1;
    dataLoaded = false;

    std::cout << "Progress reset to defaults." << std::endl;
}

// Check if save data exists
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
    if (HasSaveData())
    {
        std::cout << "Save data found. Can load from main menu." << std::endl;
    }
    else
    {
        std::cout << "No existing save found. Starting new game." << std::endl;
    }
}