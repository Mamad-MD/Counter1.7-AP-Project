// IntegrationTests.cpp
#include "GameManager.h"
#include "Player.h"
#include "Gun.h"

void testFullGameScenario() {
    // Setup game
    GameManager* game = GameManager::getInstance();
    game->setupMatch("Dust2", 5, 5, 800.0f);

    // Simulate game rounds
    game->startGame();

    // Verify game results
    assert(game->getResult() != "");
    std::cout << "Game result: " << game->getResult() << std::endl;
}

void runIntegrationTests() {
    testFullGameScenario();
    std::cout << "All integration tests passed!" << std::endl;
}