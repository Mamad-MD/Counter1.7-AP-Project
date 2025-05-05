//// GameMap.h
//#pragma once
//#include <string>
//
//class GameMap {
//private:
//    std::string mapName;
//    std::string designerName;
//    bool isNight;
//
//public:
//    GameMap();
//    GameMap(const GameMap& other);
//    GameMap(std::string name, std::string designer, bool night);
//
//    // CRUD operations
//    // ... (implement similar to previous classes)
//};
#pragma once
#include <string>

class GameMap {
private:
    std::string mapName;
    std::string designerName;
    bool isNight;
    int spawnPointsCT;
    int spawnPointsT;
    float bombSiteA[3];
    float bombSiteB[3];

public:
    GameMap();
    GameMap(const std::string& name, const std::string& designer, bool night);
    GameMap(const GameMap& other);

    // Getters
    std::string getMapName() const { return mapName; }
    std::string getDesignerName() const { return designerName; }
    bool getIsNight() const { return isNight; }

    // Setters
    void setMapName(const std::string& name) { mapName = name; }
    void setDesignerName(const std::string& designer) { designerName = designer; }
    void setIsNight(bool night) { isNight = night; }

    void setSpawnPoints(int ct, int t) {
        spawnPointsCT = ct;
        spawnPointsT = t;
    }

    void setBombSites(float a[3], float b[3]) {
        for (int i = 0; i < 3; i++) {
            bombSiteA[i] = a[i];
            bombSiteB[i] = b[i];
        }
    }

    void displayMapInfo() const;
};

inline GameMap::GameMap() : mapName("Unknown"), designerName("Unknown"),
isNight(false), spawnPointsCT(0), spawnPointsT(0) {
    bombSiteA[0] = bombSiteA[1] = bombSiteA[2] = 0;
    bombSiteB[0] = bombSiteB[1] = bombSiteB[2] = 0;
}

inline GameMap::GameMap(const std::string& name, const std::string& designer, bool night)
    : mapName(name), designerName(designer), isNight(night),
    spawnPointsCT(0), spawnPointsT(0) {
    bombSiteA[0] = bombSiteA[1] = bombSiteA[2] = 0;
    bombSiteB[0] = bombSiteB[1] = bombSiteB[2] = 0;
}

inline GameMap::GameMap(const GameMap& other)
    : mapName(other.mapName), designerName(other.designerName),
    isNight(other.isNight), spawnPointsCT(other.spawnPointsCT),
    spawnPointsT(other.spawnPointsT) {
    for (int i = 0; i < 3; i++) {
        bombSiteA[i] = other.bombSiteA[i];
        bombSiteB[i] = other.bombSiteB[i];
    }
}

inline void GameMap::displayMapInfo() const {
    std::cout << "Map Name: " << mapName << "\n"
        << "Designer: " << designerName << "\n"
        << "Time: " << (isNight ? "Night" : "Day") << "\n"
        << "CT Spawn Points: " << spawnPointsCT << "\n"
        << "T Spawn Points: " << spawnPointsT << std::endl;
}