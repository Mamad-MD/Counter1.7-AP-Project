//// PerformanceTests.cpp
//#include <iostream>
//#include <chrono>
//#include <vector>
//#include <string>
//#include <cstdlib>
//#include "Game.h" // فرض بر این است که این فایل کلاس‌های Player, Weapon, Game و Team را شامل می‌شود
//
//using namespace std;
//using namespace std::chrono;
//
//void loadTest(Game& game) {
//    cout << "\n[Load Test] Adding 1000 players...\n";
//    for (int i = 0; i < 1000; ++i) {
//        game.addPlayer(new Player("Player" + to_string(i), rand() % 3));
//    }
//    game.startMatch();
//}
//
//void stressTest(Game& game) {
//    cout << "\n[Stress Test] Simulating 1000 battles...\n";
//    for (int i = 0; i < 1000; ++i) {
//        game.simulateBattle();
//    }
//}
//
//void timeProfiling(Game& game) {
//    cout << "\n[Time Profiling] Measuring battle simulation time...\n";
//    auto start = high_resolution_clock::now();
//    game.simulateBattle();
//    auto end = high_resolution_clock::now();
//    cout << "Battle Time: " << duration_cast<microseconds>(end - start).count() << " us\n";
//}
//
//void weaponBalanceTest(Game& game) {
//    cout << "\n[Weapon Balance Test] AK vs M4 (1000 rounds)...\n";
//    int akWins = 0, m4Wins = 0;
//    for (int i = 0; i < 1000; ++i) {
//        Team akTeam("AK", Weapon::AK47);
//        Team m4Team("M4", Weapon::M4);
//        Team* winner = game.fight(akTeam, m4Team);
//        if (winner->getName() == "AK") akWins++;
//        else m4Wins++;
//    }
//    cout << "AK Win Rate: " << (akWins / 1000.0) * 100 << "%\n";
//    cout << "M4 Win Rate: " << (m4Wins / 1000.0) * 100 << "%\n";
//}
//
//void dynamicWeaponChangeTest(Player* player) {
//    cout << "\n[Dynamic Weapon Change Test] Changing weapon during battle...\n";
//    player->changeWeapon(Weapon::Sniper);
//    player->shoot();
//}
//
//int main() {
//    Game game;
//
//    loadTest(game);
//    stressTest(game);
//    timeProfiling(game);
//    weaponBalanceTest(game);
//
//    // Create a test player for weapon switch test
//    Player* testPlayer = new Player("TestPlayer", 0);
//    dynamicWeaponChangeTest(testPlayer);
//    delete testPlayer;
//
//    cout << "\nPerformance Tests Completed.\n";
//    return 0;
//}
