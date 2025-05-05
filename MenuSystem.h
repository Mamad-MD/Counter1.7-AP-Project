//// MenuSystem.h
//#pragma once
//#include "GameManager.h"
//#include <vector>
//
//class MenuSystem {
//private:
//    GameManager* gameManager;
//    bool settingsConfigured;
//    std::vector<GameMap> availableMaps;
//
//public:
//    MenuSystem();
//    void showMainMenu();
//    void showGameSettings();
//    void showGameHistory();
//    void showUserProfile();
//
//private:
//    void initializeMaps();
//    void startGameMenu();
//    void gameSettingsMenu();
//    void gameHistoryMenu();
//    void userProfileMenu();
//};
#pragma once
#include <vector>
#include <memory>
#include "GameManager.h"
#include "AuthSystem.h"

class MenuSystem {
private:
    std::shared_ptr<GameManager> gameManager;
    std::shared_ptr<AuthSystem> authSystem;
    bool settingsConfigured;
    std::vector<std::shared_ptr<GameMap>> availableMaps;

    void initializeMaps();
    void clearScreen() const;
    void waitForInput() const;

    // Authentication menus
    void showLoginMenu();
    void showRegisterMenu();

    // Main menu options
    void startGameMenu();
    void gameSettingsMenu();
    void gameHistoryMenu();
    void userProfileMenu();

    // Settings submenus
    void selectMapMenu();
    void setTeamsMenu();
    void setInitialMoneyMenu();

public:
    MenuSystem(std::shared_ptr<GameManager> gm, std::shared_ptr<AuthSystem> as);
    void showMainMenu();
};