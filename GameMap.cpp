#include "GameMap.h"
#include <iostream>

GameMap::GameMap()
    : mapName("Unknown"), designerName("Unknown"), isNight(false), spawnPointsCT(0), spawnPointsT(0) {
    bombSiteA[0] = bombSiteA[1] = bombSiteA[2] = 0;
    bombSiteB[0] = bombSiteB[1] = bombSiteB[2] = 0;
}

GameMap::GameMap(const std::string& name, const std::string& designer, bool night)
    : mapName(name), designerName(designer), isNight(night), spawnPointsCT(0), spawnPointsT(0) {
    bombSiteA[0] = bombSiteA[1] = bombSiteA[2] = 0;
    bombSiteB[0] = bombSiteB[1] = bombSiteB[2] = 0;
}

GameMap::GameMap(const GameMap& other)
    : mapName(other.mapName), designerName(other.designerName),
    isNight(other.isNight), spawnPointsCT(other.spawnPointsCT), spawnPointsT(other.spawnPointsT) {
    for (int i = 0; i < 3; i++) {
        bombSiteA[i] = other.bombSiteA[i];
        bombSiteB[i] = other.bombSiteB[i];
    }
}

// Getters
std::string GameMap::getMapName() const { return mapName; }
std::string GameMap::getDesignerName() const { return designerName; }
bool GameMap::getIsNight() const { return isNight; }

// Setters
void GameMap::setMapName(const std::string& name) { mapName = name; }
void GameMap::setDesignerName(const std::string& designer) { designerName = designer; }
void GameMap::setIsNight(bool night) { isNight = night; }

void GameMap::setSpawnPoints(int ct, int t) {
    spawnPointsCT = ct;
    spawnPointsT = t;
}

void GameMap::setBombSites(float a[3], float b[3]) {
    for (int i = 0; i < 3; i++) {
        bombSiteA[i] = a[i];
        bombSiteB[i] = b[i];
    }
}

void GameMap::displayMapInfo() const {
    std::cout << "=== Map Information ===\n"
        << "Name: " << mapName << "\n"
        << "Designer: " << designerName << "\n"
        << "Time: " << (isNight ? "Night" : "Day") << "\n"
        << "CT Spawn Points: " << spawnPointsCT << "\n"
        << "T Spawn Points: " << spawnPointsT << "\n"
        << "Bomb Site A: (" << bombSiteA[0] << ", " << bombSiteA[1] << ", " << bombSiteA[2] << ")\n"
        << "Bomb Site B: (" << bombSiteB[0] << ", " << bombSiteB[1] << ", " << bombSiteB[2] << ")\n";
}
