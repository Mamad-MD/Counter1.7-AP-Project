#include "GameManager.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <random>

std::shared_ptr<GameManager> GameManager::instance = nullptr;

std::shared_ptr<GameManager> GameManager::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<GameManager>(new GameManager());
    }
    return instance;
}

GameManager::GameManager() : matchName("Unnamed Match"), result("No result yet") {}

void GameManager::setupMatch(const std::string& mapName, int terroristCount, int ctCount, float initialMoney) {
    resetGame();
    matchName = mapName;

    // Create terrorist team
    for (int i = 0; i < terroristCount; i++) {
        std::string name = "Terrorist_" + std::to_string(i + 1);
        terrorists.push_back(std::make_shared<Terrorist>(name, true, initialMoney));
    }

    // Create CT team
    for (int i = 0; i < ctCount; i++) {
        std::string name = "CT_" + std::to_string(i + 1);
        cts.push_back(std::make_shared<CT>(name, true, initialMoney));
    }

    // Randomly select a bomb carrier
    if (!terrorists.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, terrorists.size() - 1);
        terrorists[dis(gen)]->setBombCarrier(true);
    }
}

void GameManager::startGame() {
    if (terrorists.empty() || cts.empty()) {
        result = "Cannot start game - one or both teams are empty";
        return;
    }

    auto terroristIt = terrorists.begin();
    auto ctIt = cts.begin();
    int round = 1;

    while (true) {
        // Check if any team has no alive players
        bool terroristsAlive = std::any_of(terrorists.begin(), terrorists.end(),
            [](const std::shared_ptr<Terrorist>& t) { return t->isPlayerAlive(); });

        bool ctsAlive = std::any_of(cts.begin(), cts.end(),
            [](const std::shared_ptr<CT>& ct) { return ct->isPlayerAlive(); });

        if (!terroristsAlive || !ctsAlive) {
            result = terroristsAlive ? "Terrorists Win!" : "CTs Win!";
            break;
        }

        // Find next alive players if current ones are dead
        while (terroristIt != terrorists.end() && !(*terroristIt)->isPlayerAlive()) {
            ++terroristIt;
        }
        while (ctIt != cts.end() && !(*ctIt)->isPlayerAlive()) {
            ++ctIt;
        }

        // Wrap around if reached end
        if (terroristIt == terrorists.end()) {
            terroristIt = std::find_if(terrorists.begin(), terrorists.end(),
                [](const std::shared_ptr<Terrorist>& t) { return t->isPlayerAlive(); });
        }
        if (ctIt == cts.end()) {
            ctIt = std::find_if(cts.begin(), cts.end(),
                [](const std::shared_ptr<CT>& ct) { return ct->isPlayerAlive(); });
        }

        // Compare current players
        float tPower = (*terroristIt)->calculatePower();
        float ctPower = (*ctIt)->calculatePower();

        std::cout << "Round " << round++ << ": "
            << (*terroristIt)->getName() << " vs " << (*ctIt)->getName() << "\n";

        if (tPower > ctPower) {
            float damage = tPower - ctPower;
            (*ctIt)->takeDamage(damage);
            std::cout << (*terroristIt)->getName() << " damaged "
                << (*ctIt)->getName() << " for " << damage << "\n";

            if (!(*ctIt)->isPlayerAlive()) {
                std::cout << (*ctIt)->getName() << " was defeated!\n";
                ++ctIt;
            }
        }
        else if (ctPower > tPower) {
            float damage = ctPower - tPower;
            (*terroristIt)->takeDamage(damage);
            std::cout << (*ctIt)->getName() << " damaged "
                << (*terroristIt)->getName() << " for " << damage << "\n";

            if (!(*terroristIt)->isPlayerAlive()) {
                std::cout << (*terroristIt)->getName() << " was defeated!\n";
                ++terroristIt;
            }
        }
        else {
            // Equal power - both take damage
            (*terroristIt)->takeDamage(10.0f);
            (*ctIt)->takeDamage(10.0f);
            std::cout << "Both players damaged each other!\n";

            if (!(*terroristIt)->isPlayerAlive()) ++terroristIt;
            if (!(*ctIt)->isPlayerAlive()) ++ctIt;
        }

        // Add delay for simulation (500ms as per requirements)
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    saveGameResult();
}

void GameManager::endGame(const std::string& result) {
    this->result = result;
    saveGameResult();
}

void GameManager::saveGameResult() {
    std::ofstream historyFile("game_history.txt", std::ios::app);
    if (historyFile.is_open()) {
        historyFile << (result.find("Terrorists") != std::string::npos ? "1" : "0") << "\n";
        historyFile.close();
    }
}

std::vector<std::string> GameManager::getGameHistory() const {
    std::vector<std::string> history;
    std::ifstream historyFile("game_history.txt");
    int round = 1;
    std::string line;

    while (std::getline(historyFile, line)) {
        if (line.empty()) continue;

        std::string entry = "Round " + std::to_string(round++) + ": ";
        entry += (line == "1" ? "winner: Terrorist" : "winner: CT");
        history.push_back(entry);
    }

    return history;
}

void GameManager::addTerrorist(const std::shared_ptr<Terrorist>& terrorist) {
    terrorists.push_back(terrorist);
}

void GameManager::addCT(const std::shared_ptr<CT>& ct) {
    cts.push_back(ct);
}

void GameManager::removeTerrorist(const std::string& playerId) {
    terrorists.erase(std::remove_if(terrorists.begin(), terrorists.end(),
        [&playerId](const std::shared_ptr<Terrorist>& t) {
            return t->getId() == playerId;
        }), terrorists.end());
}

void GameManager::removeCT(const std::string& playerId) {
    cts.erase(std::remove_if(cts.begin(), cts.end(),
        [&playerId](const std::shared_ptr<CT>& ct) {
            return ct->getId() == playerId;
        }), cts.end());
}

void GameManager::displayMatchInfo() const {
    std::cout << "Match Name: " << matchName << "\n"
        << "Terrorists: " << terrorists.size() << " players\n"
        << "CTs: " << cts.size() << " players\n"
        << "Current Result: " << result << std::endl;

    if (currentMap) {
        currentMap->displayMapInfo();
    }
}

void GameManager::resetGame() {
    terrorists.clear();
    cts.clear();
    result = "No result yet";
    currentMap.reset();
}