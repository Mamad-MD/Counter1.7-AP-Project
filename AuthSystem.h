//// AuthSystem.h
//#pragma once
//#include "User.h"
//#include <vector>
//
//class AuthSystem {
//private:
//    std::vector<User> users;
//    User* currentUser;
//
//public:
//    AuthSystem();
//    bool registerUser(std::string username, std::string nickname, std::string password);
//    bool login(std::string username, std::string password);
//    void logout();
//    User* getCurrentUser() const;
//
//private:
//    std::string hashPassword(std::string password) const;
//    void loadUsers();
//    void saveUsers() const;
//};
#pragma once
#include "User.h"
#include <vector>
#include <memory>

class AuthSystem {
private:
    std::vector<User> users;
    User* currentUser;

    void loadUsers();
    void saveUsers() const;

public:
    AuthSystem();

    bool registerUser(const std::string& username, const std::string& nickname,
        const std::string& password, const std::string& team = "");
    bool login(const std::string& username, const std::string& password);
    void logout();

    User* getCurrentUser() const { return currentUser; }
    const std::vector<User>& getAllUsers() const { return users; }

    void updateCurrentUser(const std::string& newNickname,
        const std::string& newPassword = "",
        const std::string& newTeam = "");
};