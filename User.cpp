#include "User.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

User::User() : username(""), nickname(""), passwordHash(""), winsCount(0), teamPreference("") {}

User::User(const std::string& username, const std::string& nickname,
    const std::string& password, const std::string& team)
    : username(username), nickname(nickname),
    passwordHash(hashPassword(password)), winsCount(0), teamPreference(team) {}

bool User::authenticate(const std::string& password) const {
    return passwordHash == hashPassword(password);
}

void User::saveToFile() const {
    std::ofstream userFile("users/" + username + ".usr");
    if (userFile.is_open()) {
        userFile << username << "\n"
            << nickname << "\n"
            << passwordHash << "\n"
            << winsCount << "\n"
            << teamPreference << "\n";
        userFile.close();
    }
}

User User::loadFromFile(const std::string& username) {
    std::ifstream userFile("users/" + username + ".usr");
    User user;

    if (userFile.is_open()) {
        std::getline(userFile, user.username);
        std::getline(userFile, user.nickname);
        std::getline(userFile, user.passwordHash);

        std::string winsStr;
        std::getline(userFile, winsStr);
        user.winsCount = std::stoi(winsStr);

        std::getline(userFile, user.teamPreference);
        userFile.close();
    }

    return user;
}

std::vector<User> User::loadAllUsers() {
    std::vector<User> users;
    // Implementation would iterate through all user files in users/ directory
    return users;
}

void User::setPassword(const std::string& newPassword) {
    passwordHash = hashPassword(newPassword);
}

std::string User::hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (unsigned char i : hash) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)i;
    }

    return ss.str();
}