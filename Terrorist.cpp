#include "Terrorist.h"
#include <iostream>

Terrorist::Terrorist() : Player(), isBombCarrier(false), hasPlantedBomb(false) {}

Terrorist::Terrorist(const std::string& name, bool isAI, float initialMoney)
    : Player(name, isAI, initialMoney), isBombCarrier(false), hasPlantedBomb(false) {}

Terrorist::Terrorist(const Terrorist& other)
    : Player(other), isBombCarrier(other.isBombCarrier), hasPlantedBomb(other.hasPlantedBomb) {}

void Terrorist::plantBomb() {
    if (isBombCarrier && isAlive) {
        hasPlantedBomb = true;
        isBombCarrier = false;
        std::cout << name << " has planted the bomb!\n";
    }
}

void Terrorist::setBombCarrier(bool status) {
    if (isAlive) {
        isBombCarrier = status;
        if (status) {
            std::cout << name << " is now carrying the bomb.\n";
        }
    }
}

bool Terrorist::getBombCarrierStatus() const {
    return isBombCarrier;
}

bool Terrorist::getBombPlantStatus() const {
    return hasPlantedBomb;
}

std::string Terrorist::getTeam() const {
    return "Terrorist";
}

void Terrorist::displayInfo() const {
    Player::displayInfo();
    std::cout << "Bomb Carrier: " << (isBombCarrier ? "Yes" : "No") << "\n"
        << "Bomb Planted: " << (hasPlantedBomb ? "Yes" : "No") << std::endl;
}

float Terrorist::calculatePower() const {
    float basePower = Player::calculatePower();
    return isBombCarrier ? basePower * 1.15f : basePower;
}
