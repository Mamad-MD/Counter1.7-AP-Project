#pragma once
#include "Player.h"

class CT : public Player {
private:
    bool hasDefuseKit;
    bool hasDefusedBomb;

public:
    CT();
    CT(const std::string& name, bool isAI, float initialMoney);
    CT(const CT& other);
    std::string getTeam() const;
    void setDefuseKit(bool status);
    void defuseBomb();
    bool getDefuseKitStatus() const { return hasDefuseKit; }
    bool getBombDefuseStatus() const { return hasDefusedBomb; }

    void displayInfo() const override;
    float calculatePower() const override;
};
