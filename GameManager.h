#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Player.h"
#include "Terrorist.h"
#include "CT.h"
#include "GameMap.h"

class GameManager {
private:
    static std::shared_ptr<GameManager> instance;

    std::vector<std::shared_ptr<Terrorist>> terrorists;
    std::vector<std::shared_ptr<CT>> cts;
    std::string matchName;
    std::string result;
    std::string loggedInUserId;
    std::shared_ptr<GameMap> currentMap;

    GameManager();
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

public:
    static std::shared_ptr<GameManager> getInstance();

    // Game Management
    void setupMatch(const std::string& mapName, int terroristCount, int ctCount, float initialMoney);
    void startGame();
    void endGame(const std::string& result);
    void saveGameResult();
    std::vector<std::string> getGameHistory() const;

    // Team Management
    void addTerrorist(const std::shared_ptr<Terrorist>& terrorist);
    void addCT(const std::shared_ptr<CT>& ct);
    void removeTerrorist(const std::string& playerId);
    void removeCT(const std::string& playerId);

    // Getters
    std::string getMatchName() const { return matchName; }
    std::string getResult() const { return result; }
    std::shared_ptr<GameMap> getCurrentMap() const { return currentMap; }
    const std::vector<std::shared_ptr<Terrorist>>& getTerrorists() const { return terrorists; }
    const std::vector<std::shared_ptr<CT>>& getCTs() const { return cts; }

    // Setters
    void setLoggedInUserId(const std::string& id) { loggedInUserId = id; }
    void setCurrentMap(const std::shared_ptr<GameMap>& map) { currentMap = map; }

    // Utility
    void displayMatchInfo() const;
    void resetGame();
};