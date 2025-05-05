//// Player.h
//#pragma once
//#include <string>
//#include "Gun.h"
//
//class Player {
//protected:
//    std::string playerId;
//    std::string name;
//    int gunId;
//    std::string gunName;
//    float health;
//    float armor;
//    bool isAlive;
//    bool isAI;
//    float money;
//    float xPosition;
//    float yPosition;
//    float zPosition;
//
//public:
//    Player();
//    Player(const Player& other);
//    Player(std::string name, bool isAI, float initialMoney);
//    virtual ~Player();
//
//    // CRUD operations
//    // ... (implement similar to Gun class)
//
//    // Game actions
//    virtual void takeDamage(float amount);
//    void heal(float amount);
//    void buyArmor(float amount);
//    void buyGun(const Gun& gun);
//    bool isPlayerAlive() const;
//    float calculatePower() const;
//
//    // Getters and setters
//    // ... (implement for all attributes)
//};
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Gun.h"

class Player {
protected:
    std::string playerId;
    std::string name;
    std::shared_ptr<Gun> currentGun;
    float health;
    float armor;
    bool isAlive;
    bool isAI;
    float money;
    float xPosition;
    float yPosition;
    float zPosition;

    virtual void generatePlayerId();

public:
    Player();
    Player(const std::string& name, bool isAI, float initialMoney);
    Player(const Player& other);
    virtual ~Player() = default;

    // CRUD Operations
    virtual void initialize(const std::string& name, bool isAI, float initialMoney);
    virtual void displayInfo() const;
    virtual void updatePlayer(const std::string& newName, float newMoney);
    virtual void reset();

    // Game Actions
    virtual void takeDamage(float amount);
    void heal(float amount);
    void buyArmor(float amount);
    void buyGun(std::shared_ptr<Gun> gun);
    bool isPlayerAlive() const { return isAlive; }
    virtual float calculatePower() const;

    // Getters
    std::string getId() const { return playerId; }
    std::string getName() const { return name; }
    std::shared_ptr<Gun> getCurrentGun() const { return currentGun; }
    float getHealth() const { return health; }
    float getArmor() const { return armor; }
    bool getIsAI() const { return isAI; }
    float getMoney() const { return money; }
    virtual std::string getTeam() const = 0;

    // Setters
    void setName(const std::string& newName) { name = newName; }
    void setMoney(float newMoney) { money = newMoney; }
    void setPosition(float x, float y, float z) {
        xPosition = x;
        yPosition = y;
        zPosition = z;
    }

    // Operator Overloads
    bool operator==(const Player& other) const {
        return playerId == other.playerId;
    }

    bool operator!=(const Player& other) const {
        return !(*this == other);
    }
};