#include "GameManager.h"
#include <chrono>
#include <iostream>
#include <memory>

void testGamePerformanceSmall() {
    auto gameManager = GameManager::getInstance();
    gameManager->resetGame();

    auto start = std::chrono::high_resolution_clock::now();

    gameManager->setupMatch("Dust2", 5, 5, 800.0f);
    gameManager->startGame();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Small game (5v5) completed in " << duration.count() << "ms\n";
}

void testGamePerformanceMedium() {
    auto gameManager = GameManager::getInstance();
    gameManager->resetGame();

    auto start = std::chrono::high_resolution_clock::now();

    gameManager->setupMatch("Dust2", 10, 10, 16000.0f);
    gameManager->startGame();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Medium game (10v10) completed in " << duration.count() << "ms\n";
}

void testGamePerformanceLarge() {
    auto gameManager = GameManager::getInstance();
    gameManager->resetGame();

    auto start = std::chrono::high_resolution_clock::now();

    gameManager->setupMatch("Dust2", 20, 20, 32000.0f);
    gameManager->startGame();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Large game (20v20) completed in " << duration.count() << "ms\n";
}

void runAllPerformanceTests() {
    std::cout << "\n=== Running Performance Tests ===\n";
    testGamePerformanceSmall();
    testGamePerformanceMedium();
    testGamePerformanceLarge();
    std::cout << "=== Performance Tests Completed ===\n\n";
}   