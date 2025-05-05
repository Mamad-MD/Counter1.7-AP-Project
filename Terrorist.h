//// Terrorist.h
//#pragma once
//#include "Player.h"
//
//class Terrorist : public Player {
//private:
//    bool isBombCarrier;
//    bool hasPlantedBomb;
//
//public:
//    Terrorist();
//    Terrorist(const Terrorist& other);
//    Terrorist(std::string name, bool isAI, float initialMoney);
//
//    void plantBomb();
//    void setBombCarrier(bool status);
//    bool getBombCarrierStatus() const;
//    bool getBombPlantStatus() const;
//};
#pragma once
#include "Player.h"

class Terrorist : public Player {
private:
    bool isBombCarrier;
    bool hasPlantedBomb;

public:
    Terrorist();
    Terrorist(const std::string& name, bool isAI, float initialMoney);
    Terrorist(const Terrorist& other);

    void plantBomb();
    void setBombCarrier(bool status);
    bool getBombCarrierStatus() const { return isBombCarrier; }
    bool getBombPlantStatus() const { return hasPlantedBomb; }

    std::string getTeam() const override { return "Terrorist"; }
    void displayInfo() const override;
};

inline Terrorist::Terrorist() : Player(), isBombCarrier(false), hasPlantedBomb(false) {}

inline Terrorist::Terrorist(const std::string& name, bool isAI, float initialMoney)
    : Player(name, isAI, initialMoney), isBombCarrier(false), hasPlantedBomb(false) {}

inline Terrorist::Terrorist(const Terrorist& other)
    : Player(other), isBombCarrier(other.isBombCarrier), hasPlantedBomb(other.hasPlantedBomb) {}

inline void Terrorist::plantBomb() {
    if (isBombCarrier && isAlive) {
        hasPlantedBomb = true;
        isBombCarrier = false;
    }
}

inline void Terrorist::setBombCarrier(bool status) {
    if (isAlive) {
        isBombCarrier = status;
    }
}

inline void Terrorist::displayInfo() const {
    Player::displayInfo();
    std::cout << "Bomb Carrier: " << (isBombCarrier ? "Yes" : "No") << "\n"
        << "Bomb Planted: " << (hasPlantedBomb ? "Yes" : "No") << std::endl;
}