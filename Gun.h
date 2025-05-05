#pragma once
#include <string>
#include <iostream>

enum class GunType { AK47, M4A1, AWP, DEAGLE, GLOCK, UNKNOWN };

class Gun {
private:
    int bulletCount;
    float price;
    int gunId;
    GunType type;
    float damagePerBullet;
    static int totalGunsCreated;

    void validateValues() const;

public:
    // Constructors
    Gun();
    Gun(int bullets, float price, GunType type, float damage);
    Gun(const Gun& other);

    // CRUD Operations
    static Gun createGun(int bullets, float price, GunType type, float damage);
    void readGunInfo() const;
    void updateGun(int bullets, float price, float damage);
    void deleteGun();

    // Getters
    int getBulletCount() const;
    float getPrice() const;
    GunType getType() const;
    float getDamagePerBullet() const;
    int getId() const;
    static int getTotalGunsCreated();
    std::string getTypeAsString() const;

    // Operators
    Gun& operator=(const Gun& other);
    bool operator==(const Gun& other) const;
    bool operator!=(const Gun& other) const;
};
