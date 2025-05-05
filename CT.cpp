#include "CT.h"
#include <iostream>

CT::CT() : Player(), hasDefuseKit(false), hasDefusedBomb(false) {}

CT::CT(const std::string& name, bool isAI, float initialMoney)
    : Player(name, isAI, initialMoney), hasDefuseKit(false), hasDefusedBomb(false) {}

CT::CT(const CT& other)
    : Player(other), hasDefuseKit(other.hasDefuseKit), hasDefusedBomb(other.hasDefusedBomb) {}

std::string CT::getTeam() const {
    return "Counter-Terrorist";
}
void CT::defuseBomb() {
    if (hasDefuseKit && isAlive) {
        hasDefusedBomb = true;
        std::cout << name << " has defused the bomb!\n";
    }
}

void CT::setDefuseKit(bool status) {
    if (isAlive) {
        hasDefuseKit = status;
        if (status) {
            std::cout << name << " acquired a defuse kit.\n";
        }
    }
}

void CT::displayInfo() const {
    Player::displayInfo();
    std::cout << "Defuse Kit: " << (hasDefuseKit ? "Yes" : "No") << "\n"
        << "Bomb Defused: " << (hasDefusedBomb ? "Yes" : "No") << std::endl;
}

float CT::calculatePower() const {
    float basePower = Player::calculatePower();
    if (hasDefuseKit) basePower += 10;
    if (hasDefusedBomb) basePower += 20;
    return basePower;
}
