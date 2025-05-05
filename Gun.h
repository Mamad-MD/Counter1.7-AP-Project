//#pragma once
//#include <string>
//#include <vector>
//
//enum class GunType { AK47, M4A1, AWP, DEAGLE, GLOCK };
//
//class Gun {
//private:
//    int bulletCount;
//    float price;
//    int gunId;
//    GunType type;
//    float damagePerBullet;
//    static int totalGunsCreated;
//
//public:
//    Gun();
//    Gun(const Gun& other);
//    Gun(int bullets, float price, GunType type, float damage);
//    ~Gun();
//
//    // CRUD operations
//    static Gun createGun(int bullets, float price, GunType type, float damage);
//    void readGunInfo() const;
//    void updateGun(int bullets, float price, float damage);
//    void deleteGun();
//
//    // Getters and setters
//    int getBulletCount() const;
//    float getPrice() const;
//    GunType getType() const;
//    float getDamagePerBullet() const;
//    std::string getTypeAsString() const;
//    static int getTotalGunsCreated();
//
//    // Operator overloads
//    Gun& operator=(const Gun& other);
//    bool operator==(const Gun& other) const;
//    bool operator!=(const Gun& other) const;
//};
#pragma once
#include <string>
#include <stdexcept>

enum class GunType { AK47, M4A1, AWP, DEAGLE, GLOCK, UNKNOWN };

class Gun {
private:
    int bulletCount;
    float price;
    int gunId;
    GunType type;
    float damagePerBullet;
    static int totalGunsCreated;

    void validateValues() const {
        if (bulletCount < 0 || price < 0 || damagePerBullet < 0) {
            throw std::invalid_argument("Negative values are not allowed");
        }
    }

public:
    // Constructors
    Gun() : bulletCount(0), price(0), gunId(++totalGunsCreated), type(GunType::UNKNOWN), damagePerBullet(0) {}

    Gun(int bullets, float price, GunType type, float damage)
        : bulletCount(bullets), price(price), gunId(++totalGunsCreated),
        type(type), damagePerBullet(damage) {
        validateValues();
    }

    Gun(const Gun& other)
        : bulletCount(other.bulletCount), price(other.price),
        gunId(++totalGunsCreated), type(other.type),
        damagePerBullet(other.damagePerBullet) {}

    // CRUD Operations
    static Gun createGun(int bullets, float price, GunType type, float damage) {
        return Gun(bullets, price, type, damage);
    }

    void readGunInfo() const {
        std::cout << "Gun ID: " << gunId << "\n"
            << "Type: " << getTypeAsString() << "\n"
            << "Bullets: " << bulletCount << "\n"
            << "Damage per bullet: " << damagePerBullet << "\n"
            << "Price: $" << price << std::endl;
    }

    void updateGun(int bullets, float price, float damage) {
        bulletCount = bullets;
        this->price = price;
        damagePerBullet = damage;
        validateValues();
    }

    void deleteGun() {
        bulletCount = 0;
        price = 0;
        damagePerBullet = 0;
        type = GunType::UNKNOWN;
    }

    // Getters
    int getBulletCount() const { return bulletCount; }
    float getPrice() const { return price; }
    GunType getType() const { return type; }
    float getDamagePerBullet() const { return damagePerBullet; }
    int getId() const { return gunId; }
    static int getTotalGunsCreated() { return totalGunsCreated; }

    std::string getTypeAsString() const {
        switch (type) {
        case GunType::AK47: return "AK-47";
        case GunType::M4A1: return "M4A1";
        case GunType::AWP: return "AWP";
        case GunType::DEAGLE: return "Desert Eagle";
        case GunType::GLOCK: return "Glock-18";
        default: return "Unknown";
        }
    }

    // Operator Overloads
    Gun& operator=(const Gun& other) {
        if (this != &other) {
            bulletCount = other.bulletCount;
            price = other.price;
            type = other.type;
            damagePerBullet = other.damagePerBullet;
        }
        return *this;
    }

    bool operator==(const Gun& other) const {
        return (bulletCount == other.bulletCount &&
            price == other.price &&
            type == other.type &&
            damagePerBullet == other.damagePerBullet);
    }

    bool operator!=(const Gun& other) const {
        return !(*this == other);
    }
};

int Gun::totalGunsCreated = 0;