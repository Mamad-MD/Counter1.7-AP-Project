// =================== IntegrationTests.cpp ===================
#include "GameManager.h"
#include "Gun.h"
#include "Terrorist.h"
#include "CT.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <fstream>

// تست ایجاد بازی و تیم‌ها
void testGameSetup() {
    std::cout << "Running testGameSetup... ";
    auto gameManager = GameManager::getInstance();
    gameManager->resetGame();

    gameManager->setupMatch("Dust2", 5, 5, 800.0f);
    assert(gameManager->getTerrorists().size() == 5);
    assert(gameManager->getCTs().size() == 5);
    assert(gameManager->getMatchName() == "Dust2");

    bool hasBombCarrier = false;
    for (const auto& terrorist : gameManager->getTerrorists()) {
        if (terrorist->getBombCarrierStatus()) {
            hasBombCarrier = true;
            break;
        }
    }
    assert(hasBombCarrier);
    std::cout << "Passed!\n";
}

// تست مبارزه میان دو بازیکن
void testGameCombat() {
    std::cout << "Running testGameCombat... ";
    auto gameManager = GameManager::getInstance();
    gameManager->resetGame();

    gameManager->setupMatch("Dust2", 1, 1, 800.0f);
    auto ak47 = std::make_shared<Gun>(30, 2700.0f, GunType::AK47, 36.0f);
    auto m4a1 = std::make_shared<Gun>(30, 3100.0f, GunType::M4A1, 33.0f);

    gameManager->getTerrorists()[0]->buyGun(ak47);
    gameManager->getCTs()[0]->buyGun(m4a1);

    auto terrorist = gameManager->getTerrorists()[0];
    auto ct = gameManager->getCTs()[0];

    float initialTHealth = terrorist->getHealth();
    float initialCTHealth = ct->getHealth();

    gameManager->startGame();

    assert(!ct->isPlayerAlive());
    assert(terrorist->isPlayerAlive());
    assert(terrorist->getHealth() < initialTHealth);
    std::cout << "Passed!\n";
}

// تست ثبت تاریخچه بازی‌ها
void testGameHistory() {
    std::cout << "Running testGameHistory... ";
    auto gameManager = GameManager::getInstance();
    gameManager->resetGame();

    std::ofstream clearFile("game_history.txt", std::ios::trunc);
    clearFile.close();

    gameManager->endGame("CTs Win!");
    gameManager->endGame("Terrorists Win!");
    gameManager->endGame("CTs Win!");

    auto history = gameManager->getGameHistory();
    assert(history.size() == 3);
    assert(history[0].find("CT") != std::string::npos);
    assert(history[1].find("Terrorist") != std::string::npos);
    assert(history[2].find("CT") != std::string::npos);
    std::cout << "Passed!\n";
}

void runAllIntegrationTests() {
    std::cout << "\n=== Running Integration Tests ===\n";
    testGameSetup();
    testGameCombat();
    testGameHistory();
    std::cout << "=== All Integration Tests Passed! ===\n\n";
}
