#include "AuthSystem.h"
#include "GameManager.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

AuthSystem::AuthSystem() : currentUser(nullptr) {
    loadUsers();
}

void AuthSystem::loadUsers() {
    users.clear();

    if (!fs::exists("users")) {
        fs::create_directory("users");
    }

    for (const auto& entry : fs::directory_iterator("users")) {
        if (entry.path().extension() == ".usr") {
            std::string username = entry.path().stem().string();
            users.push_back(User::loadFromFile(username));
        }
    }
}

void AuthSystem::saveUsers() const {
    for (const auto& user : users) {
        user.saveToFile();
    }
}

bool AuthSystem::registerUser(const std::string& username, const std::string& nickname,
    const std::string& password, const std::string& team) {
    // Check if username exists
    for (const auto& user : users) {
        if (user.getUsername() == username) {
            return false;
        }
    }

    // Create and save new user
    User newUser(username, nickname, password, team);
    users.push_back(newUser);
    saveUsers();
    return true;
}

bool AuthSystem::login(const std::string& username, const std::string& password) {
    for (auto& user : users) {
        if (user.getUsername() == username && user.authenticate(password)) {
            currentUser = &user;

            // Update GameManager with logged in user
            auto gameManager = GameManager::getInstance();
            gameManager->setLoggedInUserId(username);

            return true;
        }
    }
    return false;
}

void AuthSystem::logout() {
    currentUser = nullptr;

    // Update GameManager
    auto gameManager = GameManager::getInstance();
    gameManager->setLoggedInUserId("");
}

void AuthSystem::updateCurrentUser(const std::string& newNickname,
    const std::string& newPassword,
    const std::string& newTeam) {
    if (currentUser) {
        currentUser->setNickname(newNickname);
        if (!newPassword.empty()) {
            currentUser->setPassword(newPassword);
        }
        if (!newTeam.empty()) {
            currentUser->setTeamPreference(newTeam);
        }
        saveUsers();
    }
}