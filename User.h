//// User.h
//#pragma once
//#include <string>
//
//class User {
//private:
//    std::string username;
//    std::string nickname;
//    std::string passwordHash;
//    int winsCount;
//
//public:
//    User();
//    User(std::string username, std::string nickname, std::string password);
//
//    bool authenticate(std::string password) const;
//    void incrementWins();
//    void saveToFile() const;
//    static User loadFromFile(std::string username);
//
//    // Getters
//    std::string getUsername() const;
//    std::string getNickname() const;
//    int getWinsCount() const;
//};
#pragma once
#include <string>
#include <vector>

class User {
private:
    std::string username;
    std::string nickname;
    std::string passwordHash;
    int winsCount;
    std::string teamPreference; // "Terrorist" or "CT"

public:
    User();
    User(const std::string& username, const std::string& nickname,
        const std::string& password, const std::string& team = "");

    bool authenticate(const std::string& password) const;
    void incrementWins() { winsCount++; }
    void saveToFile() const;
    static User loadFromFile(const std::string& username);
    static std::vector<User> loadAllUsers();

    // Getters
    std::string getUsername() const { return username; }
    std::string getNickname() const { return nickname; }
    int getWinsCount() const { return winsCount; }
    std::string getTeamPreference() const { return teamPreference; }

    // Setters
    void setNickname(const std::string& newNickname) { nickname = newNickname; }
    void setPassword(const std::string& newPassword);
    void setTeamPreference(const std::string& team) { teamPreference = team; }

private:
    static std::string hashPassword(const std::string& password);
};