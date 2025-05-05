//#include <iostream>
//#include <memory>
//#include <direct.h> 
//#include <cassert>
//#include <sys/stat.h>
//#include "GameManager.h"
//#include "AuthSystem.h"
//#include "MenuSystem.h"
//
//void runTests() {
//    std::cout << "=== Running Unit Tests ===\n";
//
//    // Test Gun class
//    Gun ak47(30, 2700.0f, GunType::AK47, 36.0f);
//    assert(ak47.getBulletCount() == 30);
//    assert(ak47.getTypeAsString() == "AK-47");
//
//    // Test Player damage
//    CT player("TestPlayer", false, 1000.0f);
//    player.takeDamage(50.0f);
//    assert(player.isPlayerAlive());
//    player.takeDamage(60.0f);
//    assert(!player.isPlayerAlive());
//
//    std::cout << "All tests passed!\n\n";
//}
//
//int main() {
//    struct stat info;
//    if (stat("users", &info) != 0) {
//        _mkdir("users");
//    }
//    // Initialize systems
//    auto gameManager = GameManager::getInstance();
//    auto authSystem = std::make_shared<AuthSystem>();
//    auto menuSystem = std::make_shared<MenuSystem>(gameManager, authSystem);
//
//    // Run tests
//    runTests();
//
//    // Start main menu
//    menuSystem->showMainMenu();
//
//    std::cout << "Thanks for playing Counter 1.7!\n";
//    return 0;
//}
#include <iostream>
#include <memory>
#include <direct.h>
#include <cassert>
#include "GameManager.h"
#include "AuthSystem.h"
#include "MenuSystem.h"
#include "User.h" // برای تست‌های مربوط به یوزر

void runTests() {
    std::cout << "=== Running Unit Tests ===\n";

    // Test Gun class
    Gun ak47(30, 2700.0f, GunType::AK47, 36.0f);
    assert(ak47.getBulletCount() == 30);
    assert(ak47.getTypeAsString() == "AK-47");
    std::cout << "[TEST] Gun class - PASSED\n";

    // Test Player damage
    CT player("TestPlayer", false, 1000.0f);
    player.takeDamage(50.0f);
    assert(player.isPlayerAlive());
    player.takeDamage(60.0f);
    assert(!player.isPlayerAlive());
    std::cout << "[TEST] Player class - PASSED\n";

    // Test User hashing and authentication
    User testUser("testuser", "Tester", "secure123", "CT");
    assert(testUser.authenticate("secure123"));
    assert(!testUser.authenticate("wrongpass"));
    testUser.saveToFile();
    User loadedUser = User::loadFromFile("testuser");
    assert(loadedUser.getNickname() == "Tester");
    std::cout << "[TEST] User class - PASSED\n";

    std::cout << "All tests passed!\n\n";
}

int main() {
    // Create "users" directory if it doesn't exist
    _mkdir("users");

    // Initialize systems
    auto gameManager = GameManager::getInstance();
    auto authSystem = std::make_shared<AuthSystem>();
    auto menuSystem = std::make_shared<MenuSystem>(gameManager, authSystem);

    // Run tests (can be disabled later)
    runTests();

    // Start main menu
    menuSystem->showMainMenu();

    std::cout << "Thanks for playing Counter 1.7!\n";
    return 0;
}
