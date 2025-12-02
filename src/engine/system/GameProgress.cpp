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

// Setters
void GameProgress::SetUsername(const std::string& name)
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

// Helper functions
std::string GameProgress::GetSaveFilePath()
{
    return "savegame.dat";
}

bool GameProgress::FileExists(const std::string& filepath)
{
    std::ifstream file(filepath);
    return file.good();
}

// Save progress to file
bool GameProgress::SaveProgress()
{
    std::ofstream saveFile(GetSaveFilePath());
    
    if (!saveFile.is_open())
    {
        std::cerr << "Failed to open save file for writing!" << std::endl;
        return false;
    }

    // Write data in a structured format
    saveFile << username << std::endl;
    saveFile << points << std::endl;
    saveFile << mapPosition.x << " " << mapPosition.y << std::endl;
    saveFile << currentLevel << std::endl;

    saveFile.close();
    
    std::cout << "Progress saved successfully!" << std::endl;
    return true;
}

// Load progress from file
bool GameProgress::LoadProgress()
{
    if (!FileExists(GetSaveFilePath()))
    {
        std::cout << "No save file found. Starting fresh." << std::endl;
        return false;
    }

    std::ifstream saveFile(GetSaveFilePath());
    
    if (!saveFile.is_open())
    {
        std::cerr << "Failed to open save file for reading!" << std::endl;
        return false;
    }

    // Read data
    std::getline(saveFile, username);
    saveFile >> points;
    saveFile >> mapPosition.x >> mapPosition.y;
    saveFile >> currentLevel;

    saveFile.close();
    dataLoaded = true;
    
    std::cout << "Progress loaded successfully!" << std::endl;
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
    return FileExists(GetSaveFilePath());
}

// Initialize the system (call at game start)
void GameProgress::Initialize()
{
    if (HasSaveData())
    {
        LoadProgress();
    }
    else
    {
        std::cout << "No existing save found. Starting new game." << std::endl;
    }
}