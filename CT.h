

// CT.h
//#pragma once
//#include "Player.h"
//
//class CT : public Player {
//private:
//    bool hasDefuseKit;
//    bool hasDefusedBomb;
//
//public:
//    CT();
//    CT(const CT& other);
//    CT(std::string name, bool isAI, float initialMoney);
//
//    void defuseBomb();
//    void setDefuseKit(bool status);
//    bool getDefuseKitStatus() const;
//    bool getBombDefuseStatus() const;
//
// #pragma once
#include "Player.h"

class CT : public Player {
private:
    bool hasDefuseKit;
    bool hasDefusedBomb;

public:
    CT();
    CT(const std::string& name, bool isAI, float initialMoney);
    CT(const CT& other);

    void defuseBomb();
    void setDefuseKit(bool status);
    bool getDefuseKitStatus() const { return hasDefuseKit; }
    bool getBombDefuseStatus() const { return hasDefusedBomb; }

    std::string getTeam() const override { return "CT"; }
    void displayInfo() const override;
};

inline CT::CT() : Player(), hasDefuseKit(false), hasDefusedBomb(false) {}

inline CT::CT(const std::string& name, bool isAI, float initialMoney)
    : Player(name, isAI, initialMoney), hasDefuseKit(false), hasDefusedBomb(false) {}

inline CT::CT(const CT& other)
    : Player(other), hasDefuseKit(other.hasDefuseKit), hasDefusedBomb(other.hasDefusedBomb) {}

inline void CT::defuseBomb() {
    if (hasDefuseKit && isAlive) {
        hasDefusedBomb = true;
    }
}

inline void CT::setDefuseKit(bool status) {
    if (isAlive) {
        hasDefuseKit = status;
    }
}

inline void CT::displayInfo() const {
    Player::displayInfo();
    std::cout << "Defuse Kit: " << (hasDefuseKit ? "Yes" : "No") << "\n"
        << "Bomb Defused: " << (hasDefusedBomb ? "Yes" : "No") << std::endl;
}