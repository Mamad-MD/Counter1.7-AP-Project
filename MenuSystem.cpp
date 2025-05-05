#include "MenuSystem.h"
#include <iostream>
#include <limits>
#include <thread>

MenuSystem::MenuSystem(std::shared_ptr<GameManager> gm, std::shared_ptr<AuthSystem> as)
    : gameManager(gm), authSystem(as), settingsConfigured(false) {
    initializeMaps();
}

void MenuSystem::initializeMaps() {
    availableMaps.clear();

    // Create some default maps
    auto dust2 = std::make_shared<GameMap>("Dust II", "Dave Johnston", false);
    float siteA[3] = { 100.0f, 200.0f, 0.0f };
    float siteB[3] = { 300.0f, 400.0f, 0.0f };
    dust2->setBombSites(siteA, siteB);
    dust2->setSpawnPoints(5, 5);
    availableMaps.push_back(dust2);

    auto mirage = std::make_shared<GameMap>("Mirage", "Valve", false);
    availableMaps.push_back(mirage);

    auto inferno = std::make_shared<GameMap>("Inferno", "Valve", true);
    availableMaps.push_back(inferno);

    auto nuke = std::make_shared<GameMap>("Nuke", "Valve", false);
    availableMaps.push_back(nuke);

    auto overpass = std::make_shared<GameMap>("Overpass", "Valve", true);
    availableMaps.push_back(overpass);
}

void MenuSystem::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void MenuSystem::waitForInput() const {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void MenuSystem::showLoginMenu() {
    clearScreen();
    std::cout << "=== Login ===\n";

    std::string username, password;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    if (authSystem->login(username, password)) {
        std::cout << "Login successful!\n";
    }
    else {
        std::cout << "Invalid username or password!\n";
    }
    waitForInput();
}

void MenuSystem::showRegisterMenu() {
    clearScreen();
    std::cout << "=== Register ===\n";

    std::string username, nickname, password, team;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Nickname: ";
    std::cin >> nickname;
    std::cout << "Password: ";
    std::cin >> password;
    std::cout << "Team Preference (T/CT): ";
    std::cin >> team;

    std::string fullTeam = (team == "T" || team == "t") ? "Terrorist" : "CT";

    if (authSystem->registerUser(username, nickname, password, fullTeam)) {
        std::cout << "Registration successful!\n";
    }
    else {
        std::cout << "Username already exists!\n";
    }
    waitForInput();
}

void MenuSystem::showMainMenu() {
    while (true) {
        clearScreen();
        std::cout << "=== Counter 1.7 Main Menu ===\n";

        if (authSystem->getCurrentUser()) {
            std::cout << "Logged in as: " << authSystem->getCurrentUser()->getNickname()
                << " (" << authSystem->getCurrentUser()->getWinsCount() << " wins)\n\n";

            std::cout << "1. Start Game\n"
                << "2. Game Settings\n"
                << "3. Game History\n"
                << "4. User Profile\n"
                << "5. Logout\n"
                << "0. Exit\n\n"
                << "Select an option: ";

            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1: startGameMenu(); break;
            case 2: gameSettingsMenu(); break;
            case 3: gameHistoryMenu(); break;
            case 4: userProfileMenu(); break;
            case 5: authSystem->logout(); break;
            case 0: return;
            default: std::cout << "Invalid choice!\n"; waitForInput();
            }
        }
        else {
            std::cout << "1. Login\n"
                << "2. Register\n"
                << "0. Exit\n\n"
                << "Select an option: ";

            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1: showLoginMenu(); break;
            case 2: showRegisterMenu(); break;
            case 0: return;
            default: std::cout << "Invalid choice!\n"; waitForInput();
            }
        }
    }
}

void MenuSystem::startGameMenu() {
    if (!settingsConfigured) {
        clearScreen();
        std::cout << "Please configure game settings first!\n";
        waitForInput();
        return;
    }

    clearScreen();
    std::cout << "=== Starting Game ===\n";
    gameManager->displayMatchInfo();
    std::cout << "\nStarting game...\n";

    // Simulate game loading
    for (int i = 0; i < 3; i++) {
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\n";

    gameManager->startGame();
    waitForInput();
}

void MenuSystem::gameSettingsMenu() {
    while (true) {
        clearScreen();
        std::cout << "=== Game Settings ===\n";
        std::cout << "1. Select Map\n"
            << "2. Set Teams\n"
            << "3. Set Initial Money\n"
            << "0. Back to Main Menu\n\n"
            << "Select an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: selectMapMenu(); break;
        case 2: setTeamsMenu(); break;
        case 3: setInitialMoneyMenu(); break;
        case 0: return;
        default: std::cout << "Invalid choice!\n"; waitForInput();
        }

        // Check if all settings are configured
        if (gameManager->getCurrentMap() &&
            !gameManager->getTerrorists().empty() &&
            !gameManager->getCTs().empty()) {
            settingsConfigured = true;
        }
    }
}

void MenuSystem::selectMapMenu() {
    clearScreen();
    std::cout << "=== Select Map ===\n";

    for (size_t i = 0; i < availableMaps.size(); i++) {
        std::cout << i + 1 << ". " << availableMaps[i]->getMapName() << "\n";
    }

    std::cout << "\nSelect a map: ";
    int choice;
    std::cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(availableMaps.size())) {
        gameManager->setCurrentMap(availableMaps[choice - 1]);
        std::cout << "Map selected: " << availableMaps[choice - 1]->getMapName() << "\n";
    }
    else {
        std::cout << "Invalid selection!\n";
    }
    waitForInput();
}

void MenuSystem::setTeamsMenu() {
    clearScreen();
    std::cout << "=== Set Teams ===\n";

    int terroristCount, ctCount;
    std::cout << "Number of Terrorists (1-5): ";
    std::cin >> terroristCount;
    std::cout << "Number of CTs (1-5): ";
    std::cin >> ctCount;

    if (terroristCount < 1 || terroristCount > 5 || ctCount < 1 || ctCount > 5) {
        std::cout << "Invalid team sizes! Must be between 1 and 5.\n";
    }
    else {
        float initialMoney = 800.0f; // Default
        if (gameManager->getCurrentMap()) {
            gameManager->setupMatch(gameManager->getCurrentMap()->getMapName(),
                terroristCount, ctCount, initialMoney);
            std::cout << "Teams configured!\n";
            settingsConfigured = true;
        }
        else {
            std::cout << "Please select a map first!\n";
        }
    }
    waitForInput();
}

void MenuSystem::setInitialMoneyMenu() {
    clearScreen();
    std::cout << "=== Set Initial Money ===\n";

    float money;
    std::cout << "Enter initial money for players: $";
    std::cin >> money;

    if (money >= 0) {
        // Update money for all players
        for (auto& terrorist : gameManager->getTerrorists()) {
            terrorist->setMoney(money);
        }
        for (auto& ct : gameManager->getCTs()) {
            ct->setMoney(money);
        }
        std::cout << "Initial money set to $" << money << "\n";
    }
    else {
        std::cout << "Invalid amount! Must be positive.\n";
    }
    waitForInput();
}

void MenuSystem::gameHistoryMenu() {
    clearScreen();
    std::cout << "=== Game History ===\n";

    auto history = gameManager->getGameHistory();
    if (history.empty()) {
        std::cout << "No game history available.\n";
    }
    else {
        for (const auto& entry : history) {
            std::cout << entry << "\n";
        }
    }
    waitForInput();
}

void MenuSystem::userProfileMenu() {
    while (true) {
        clearScreen();
        auto user = authSystem->getCurrentUser();
        std::cout << "=== User Profile ===\n";
        std::cout << "Username: " << user->getUsername() << "\n"
            << "Nickname: " << user->getNickname() << "\n"
            << "Wins: " << user->getWinsCount() << "\n"
            << "Team Preference: " << user->getTeamPreference() << "\n\n"
            << "1. Change Nickname\n"
            << "2. Change Password\n"
            << "3. Change Team Preference\n"
            << "0. Back to Main Menu\n\n"
            << "Select an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string newNickname;
            std::cout << "Enter new nickname: ";
            std::cin >> newNickname;
            authSystem->updateCurrentUser(newNickname);
            std::cout << "Nickname updated!\n";
            waitForInput();
            break;
        }
        case 2: {
            std::string newPassword;
            std::cout << "Enter new password: ";
            std::cin >> newPassword;
            authSystem->updateCurrentUser("", newPassword);
            std::cout << "Password updated!\n";
            waitForInput();
            break;
        }
        case 3: {
            std::string newTeam;
            std::cout << "Enter new team preference (T/CT): ";
            std::cin >> newTeam;
            std::string fullTeam = (newTeam == "T" || newTeam == "t") ? "Terrorist" : "CT";
            authSystem->updateCurrentUser("", "", fullTeam);
            std::cout << "Team preference updated!\n";
            waitForInput();
            break;
        }
        case 0: return;
        default: std::cout << "Invalid choice!\n"; waitForInput();
        }
    }
}