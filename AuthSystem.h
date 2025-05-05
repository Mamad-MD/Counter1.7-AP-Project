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