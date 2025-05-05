#include "User.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/evp.h>
#include <iostream>  // اضافه کردن هدر iostream برای استفاده از std::cerr
#include <iostream>  // برای استفاده از std::cerr

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
    // Create a context for hashing
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_sha256();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;

    if (mdctx == nullptr) {
        std::cerr << "Error creating EVP context\n";
        return "";
    }

    // Initialize the hash context
    if (EVP_DigestInit_ex(mdctx, md, nullptr) != 1) {
        std::cerr << "Error initializing digest\n";
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    // Update the context with the password data
    if (EVP_DigestUpdate(mdctx, password.c_str(), password.size()) != 1) {
        std::cerr << "Error updating digest\n";
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    // Finalize the hash computation
    if (EVP_DigestFinal_ex(mdctx, hash, &hashLen) != 1) {
        std::cerr << "Error finalizing digest\n";
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    // Convert the hash to a hex string
    std::stringstream ss;
    for (unsigned int i = 0; i < hashLen; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    // Clean up
    EVP_MD_CTX_free(mdctx);

    return ss.str();
}
