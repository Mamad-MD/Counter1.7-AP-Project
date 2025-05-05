#include "Gun.h"
#include <stdexcept>

int Gun::totalGunsCreated = 0;

Gun::Gun() : bulletCount(0), price(0), gunId(++totalGunsCreated),
type(GunType::UNKNOWN), damagePerBullet(0) {}

Gun::Gun(int bullets, float price, GunType type, float damage)
    : bulletCount(bullets), price(price), gunId(++totalGunsCreated),
    type(type), damagePerBullet(damage) {
    validateValues();
}

Gun::Gun(const Gun& other)
    : bulletCount(other.bulletCount), price(other.price),
    gunId(++totalGunsCreated), type(other.type),
    damagePerBullet(other.damagePerBullet) {}

void Gun::validateValues() const {
    if (bulletCount < 0 || price < 0 || damagePerBullet < 0) {
        throw std::invalid_argument("Negative values are not allowed for Gun attributes");
    }
}

void Gun::updateGun(int bullets, float price, float damage) {
    bulletCount = bullets;
    this->price = price;
    damagePerBullet = damage;
    validateValues();
}

void Gun::deleteGun() {
    bulletCount = 0;
    price = 0;
    damagePerBullet = 0;
    type = GunType::UNKNOWN;
}

std::string Gun::getTypeAsString() const {
    switch (type) {
    case GunType::AK47: return "AK-47";
    case GunType::M4A1: return "M4A1";
    case GunType::AWP: return "AWP";
    case GunType::DEAGLE: return "Desert Eagle";
    case GunType::GLOCK: return "Glock-18";
    default: return "Unknown";
    }
}

void Gun::readGunInfo() const {
    std::cout << "Gun ID: " << gunId << "\n"
        << "Type: " << getTypeAsString() << "\n"
        << "Bullets: " << bulletCount << "\n"
        << "Damage per bullet: " << damagePerBullet << "\n"
        << "Price: $" << price << std::endl;
}

Gun Gun::createGun(int bullets, float price, GunType type, float damage) {
    return Gun(bullets, price, type, damage);
}

int Gun::getBulletCount() const { return bulletCount; }
float Gun::getPrice() const { return price; }
GunType Gun::getType() const { return type; }
float Gun::getDamagePerBullet() const { return damagePerBullet; }
int Gun::getId() const { return gunId; }
int Gun::getTotalGunsCreated() { return totalGunsCreated; }

Gun& Gun::operator=(const Gun& other) {
    if (this != &other) {
        bulletCount = other.bulletCount;
        price = other.price;
        type = other.type;
        damagePerBullet = other.damagePerBullet;
    }
    return *this;
}

bool Gun::operator==(const Gun& other) const {
    return (bulletCount == other.bulletCount &&
        price == other.price &&
        type == other.type &&
        damagePerBullet == other.damagePerBullet);
}

bool Gun::operator!=(const Gun& other) const {
    return !(*this == other);
}
