// GunTests.cpp
#include "Gun.h"
#include <cassert>

void testGunCreation() {
    Gun ak47(30, 2700.0f, GunType::AK47, 36.0f);
    assert(ak47.getBulletCount() == 30);
    assert(ak47.getPrice() == 2700.0f);
    assert(ak47.getType() == GunType::AK47);
    assert(ak47.getDamagePerBullet() == 36.0f);
    assert(ak47.getTypeAsString() == "AK47");
}

void testGunEdgeCases() {
    // Test with zero bullets
    Gun emptyGun(0, 100.0f, GunType::GLOCK, 15.0f);
    assert(emptyGun.getBulletCount() == 0);

    // Test negative values (should throw exception)
    try {
        Gun invalidGun(-5, -100.0f, GunType::DEAGLE, -10.0f);
        assert(false); // Should not reach here
    }
    catch (...) {
        assert(true);
    }
}

void testPlayerDamage() {
    Player player("TestPlayer", false, 1000.0f);
    player.takeDamage(50.0f);
    assert(player.isPlayerAlive() == true);
    player.takeDamage(60.0f);
    assert(player.isPlayerAlive() == false);
}

void runAllUnitTests() {
    testGunCreation();
    testGunEdgeCases();
    testPlayerDamage();
    // Add more tests for other classes
    std::cout << "All unit tests passed!" << std::endl;
}