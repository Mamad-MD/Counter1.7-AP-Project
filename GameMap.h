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
    std::string getMapName() const;
    std::string getDesignerName() const;
    bool getIsNight() const;

    // Setters
    void setMapName(const std::string& name);
    void setDesignerName(const std::string& designer);
    void setIsNight(bool night);

    void setSpawnPoints(int ct, int t);
    void setBombSites(float a[3], float b[3]);

    void displayMapInfo() const;
};
