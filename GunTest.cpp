#include "Gun.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

void testGunCreation() {
    std::cout << "Running testGunCreation... ";
    Gun ak47(30, 2700.0f, GunType::AK47, 36.0f);
    assert(ak47.getBulletCount() == 30);
    assert(ak47.getPrice() == 2700.0f);
    assert(ak47.getType() == GunType::AK47);
    assert(ak47.getDamagePerBullet() == 36.0f);
    assert(ak47.getTypeAsString() == "AK-47");
    std::cout << "Passed!\n";
}

void testGunEdgeCases() {
    std::cout << "Running testGunEdgeCases... ";
    // Test with zero bullets
    Gun emptyGun(0, 100.0f, GunType::GLOCK, 15.0f);
    assert(emptyGun.getBulletCount() == 0);

    // Test negative values (should throw exception)
    try {
        Gun invalidGun(-5, -100.0f, GunType::DEAGLE, -10.0f);
        assert(false); // Should not reach here
    }
    catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Negative values are not allowed");
    }
    std::cout << "Passed!\n";
}

void testGunOperators() {
    std::cout << "Running testGunOperators... ";
    Gun gun1(30, 2700.0f, GunType::AK47, 36.0f);
    Gun gun2 = gun1;
    Gun gun3(20, 2000.0f, GunType::M4A1, 30.0f);

    assert(gun1 == gun2);
    assert(gun1 != gun3);

    gun2.updateGun(25, 2500.0f, 35.0f);
    assert(gun1 != gun2);
    std::cout << "Passed!\n";
}

void testGunStaticCounter() {
    std::cout << "Running testGunStaticCounter... ";
    int initialCount = Gun::getTotalGunsCreated();
    {
        Gun tempGun(10, 1000.0f, GunType::GLOCK, 15.0f);
        assert(Gun::getTotalGunsCreated() == initialCount + 1);
    }
    // Counter shouldn't decrease when gun is destroyed
    assert(Gun::getTotalGunsCreated() == initialCount + 1);
    std::cout << "Passed!\n";
}

void runAllGunTests() {
    std::cout << "\n=== Running Gun Tests ===\n";
    testGunCreation();
    testGunEdgeCases();
    testGunOperators();
    testGunStaticCounter();
    std::cout << "=== All Gun Tests Passed! ===\n\n";
}