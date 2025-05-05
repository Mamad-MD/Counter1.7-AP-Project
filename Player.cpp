#include "Player.h"
#include <ctime>
#include <random>
#include <sstream>
#include <iomanip>

void Player::generatePlayerId() {
    std::time_t now = std::time(nullptr);
    std::stringstream ss;
    ss << std::hex << now;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);

    playerId = name + "_" + ss.str() + "_" + std::to_string(dis(gen));
}

Player::Player() : health(100), armor(0), isAlive(true), isAI(false),
money(0), xPosition(0), yPosition(0), zPosition(0) {
    generatePlayerId();
}

Player::Player(const std::string& name, bool isAI, float initialMoney)
    : name(name), isAI(isAI), health(100), armor(0), isAlive(true),
    money(initialMoney), xPosition(0), yPosition(0), zPosition(0) {
    generatePlayerId();
}

Player::Player(const Player& other)
    : playerId(other.playerId), name(other.name), currentGun(other.currentGun),
    health(other.health), armor(other.armor), isAlive(other.isAlive),
    isAI(other.isAI), money(other.money),
    xPosition(other.xPosition), yPosition(other.yPosition), zPosition(other.zPosition) {}

void Player::initialize(const std::string& name, bool isAI, float initialMoney) {
    this->name = name;
    this->isAI = isAI;
    this->money = initialMoney;
    generatePlayerId();
}

void Player::displayInfo() const {
    std::cout << "Player ID: " << playerId << "\n"
        << "Name: " << name << "\n"
        << "Team: " << getTeam() << "\n"
        << "Health: " << health << "\n"
        << "Armor: " << armor << "\n"
        << "Money: $" << money << "\n"
        << "Status: " << (isAlive ? "Alive" : "Dead") << "\n";

    if (currentGun) {
        std::cout << "Current Gun: ";
        currentGun->readGunInfo();
    }
    else {
        std::cout << "No gun equipped\n";
    }
}

void Player::updatePlayer(const std::string& newName, float newMoney) {
    name = newName;
    money = newMoney;
}

void Player::reset() {
    health = 100;
    armor = 0;
    isAlive = true;
    currentGun.reset();
}

void Player::takeDamage(float amount) {
    float damageToArmor = std::min(armor, amount * 0.5f);
    float damageToHealth = amount - damageToArmor;

    armor -= damageToArmor;
    health -= damageToHealth;

    if (health <= 0) {
        health = 0;
        isAlive = false;
    }
}

void Player::heal(float amount) {
    if (isAlive) {
        health = std::min(100.0f, health + amount);
    }
}

void Player::buyArmor(float amount) {
    if (money >= amount && isAlive) {
        armor = std::min(100.0f, armor + amount);
        money -= amount;
    }
}

void Player::buyGun(std::shared_ptr<Gun> gun) {
    if (money >= gun->getPrice() && isAlive) {
        currentGun = gun;
        money -= gun->getPrice();
    }
}

float Player::calculatePower() const {
    if (!currentGun || !isAlive) return 0;
    return currentGun->getBulletCount() * currentGun->getDamagePerBullet();
}