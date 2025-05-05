//#include "Player.h"
//#include "Terrorist.h"
//#include "CT.h"
//#include "GameMap.h"
//#include <cassert>
//#include <iostream>
//#include <memory>
//
//void testPlayerCreation() {
//    std::cout << "Running testPlayerCreation... ";
//    Player player("TestPlayer", false, 1000.0f);
//    assert(player.getName() == "TestPlayer");
//    assert(player.getIsAI() == false);
//    assert(player.getMoney() == 1000.0f);
//    assert(player.isPlayerAlive());
//    std::cout << "Passed!\n";
//}
//
//void testPlayerDamage() {
//    std::cout << "Running testPlayerDamage... ";
//    Player player("TestPlayer", false, 1000.0f);
//
//    // Test normal damage
//    player.takeDamage(50.0f);
//    assert(player.getHealth() == 50.0f);
//    assert(player.isPlayerAlive());
//
//    // Test lethal damage
//    player.takeDamage(60.0f);
//    assert(player.getHealth() == 0.0f);
//    assert(!player.isPlayerAlive());
//    std::cout << "Passed!\n";
//}
//
//void testPlayerArmor() {
//    std::cout << "Running testPlayerArmor... ";
//    Player CT("TestPlayer", false, 1000.0f);
//    player.buyArmor(50.0f);
//    assert(player.getArmor() == 50.0f);
//
//    // Damage should be split between armor and health
//    player.takeDamage(60.0f);
//    assert(player.getArmor() == 20.0f); // 50 - (60*0.5) = 20
//    assert(player.getHealth() == 70.0f); // 100 - (60 - 30) = 70
//    std::cout << "Passed!\n";
//}
//
//void testTerroristClass() {
//    std::cout << "Running testTerroristClass... ";
//    Terrorist terrorist("TestTerrorist", false, 800.0f);
//    assert(terrorist.getTeam() == "Terrorist");
//
//    terrorist.setBombCarrier(true);
//    assert(terrorist.getBombCarrierStatus());
//
//    terrorist.plantBomb();
//    assert(!terrorist.getBombCarrierStatus());
//    assert(terrorist.getBombPlantStatus());
//    std::cout << "Passed!\n";
//}
//
//void testCTClass() {
//    std::cout << "Running testCTClass... ";
//    CT ct("TestCT", false, 800.0f);
//    assert(ct.getTeam() == "CT");
//
//    ct.setDefuseKit(true);
//    assert(ct.getDefuseKitStatus());
//
//    ct.defuseBomb();
//    assert(ct.getBombDefuseStatus());
//    std::cout << "Passed!\n";
//}
//
//void testGameMap() {
//    std::cout << "Running testGameMap... ";
//    GameMap map("Dust2", "Valve", false);
//    assert(map.getMapName() == "Dust2");
//    assert(map.getDesignerName() == "Valve");
//    assert(!map.getIsNight());
//
//    float siteA[3] = { 100.0f, 200.0f, 0.0f };
//    float siteB[3] = { 300.0f, 400.0f, 0.0f };
//    map.setBombSites(siteA, siteB);
//    map.setSpawnPoints(5, 5);
//    std::cout << "Passed!\n";
//}
//
//void runAllUnitTests() {
//    std::cout << "\n=== Running Unit Tests ===\n";
//    testPlayerCreation();
//    testPlayerDamage();
//    testPlayerArmor();
//    testTerroristClass();
//    testCTClass();
//    testGameMap();
//    std::cout << "=== All Unit Tests Passed! ===\n\n";
//}