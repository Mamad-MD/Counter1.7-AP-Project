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
    bool getBombCarrierStatus() const;
    bool getBombPlantStatus() const;

    std::string getTeam() const override;
    void displayInfo() const override;
    float calculatePower() const override;
};
