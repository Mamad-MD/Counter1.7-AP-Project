//#include "User.h"
//#include <fstream>
//#include <sstream>
//#include <iomanip>
////#include <openssl/evp.h>
//#include <iostream>  // اضافه کردن هدر iostream برای استفاده از std::cerr
//#include <iostream>  // برای استفاده از std::cerr
//User::User() : username(""), nickname(""), passwordHash(""), winsCount(0), teamPreference("") {}
//
//User::User(const std::string& username, const std::string& nickname,
//    const std::string& password, const std::string& team)
//    : username(username), nickname(nickname),
//    passwordHash(hashPassword(password)), winsCount(0), teamPreference(team) {}
//
//bool User::authenticate(const std::string& password) const {
//    return passwordHash == hashPassword(password);
//}
//
//void User::saveToFile() const {
//    std::ofstream userFile("users/" + username + ".usr");
//    if (userFile.is_open()) {
//        userFile << username << "\n"
//            << nickname << "\n"
//            << passwordHash << "\n"
//            << winsCount << "\n"
//            << teamPreference << "\n";
//        userFile.close();
//    }
//}
//
//User User::loadFromFile(const std::string& username) {
//    std::ifstream userFile("users/" + username + ".usr");
//    User user;
//
//    if (userFile.is_open()) {
//        std::getline(userFile, user.username);
//        std::getline(userFile, user.nickname);
//        std::getline(userFile, user.passwordHash);
//
//        std::string winsStr;
//        std::getline(userFile, winsStr);
//        user.winsCount = std::stoi(winsStr);
//
//        std::getline(userFile, user.teamPreference);
//        userFile.close();
//    }
//
//    return user;
//}
//
//std::vector<User> User::loadAllUsers() {
//    std::vector<User> users;
//    // Implementation would iterate through all user files in users/ directory
//    return users;
//}
//
//void User::setPassword(const std::string& newPassword) {
//    passwordHash = hashPassword(newPassword);
//}
//
//std::string User::hashPassword(const std::string& password) {
//    // Create a context for hashing
//    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
//    const EVP_MD* md = EVP_sha256();
//    unsigned char hash[EVP_MAX_MD_SIZE];
//    unsigned int hashLen;
//
//    if (mdctx == nullptr) {
//        std::cerr << "Error creating EVP context\n";
//        return "";
//    }
//
//    // Initialize the hash context
//    if (EVP_DigestInit_ex(mdctx, md, nullptr) != 1) {
//        std::cerr << "Error initializing digest\n";
//        EVP_MD_CTX_free(mdctx);
//        return "";
//    }
//
//    // Update the context with the password data
//    if (EVP_DigestUpdate(mdctx, password.c_str(), password.size()) != 1) {
//        std::cerr << "Error updating digest\n";
//        EVP_MD_CTX_free(mdctx);
//        return "";
//    }
//
//    // Finalize the hash computation
//    if (EVP_DigestFinal_ex(mdctx, hash, &hashLen) != 1) {
//        std::cerr << "Error finalizing digest\n";
//        EVP_MD_CTX_free(mdctx);
//        return "";
//    }
//
//    // Convert the hash to a hex string
//    std::stringstream ss;
//    for (unsigned int i = 0; i < hashLen; i++) {
//        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
//    }
//
//    // Clean up
//    EVP_MD_CTX_free(mdctx);
//
//    return ss.str();
//}


#include "User.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <array>
using namespace std;

// سازنده‌ها
User::User() : username(""), nickname(""), passwordHash(""), winsCount(0), teamPreference("") {}

User::User(const string& username, const string& nickname,
    const string& password, const string& team)
    : username(username), nickname(nickname),
    passwordHash(hashPassword(password)), winsCount(0), teamPreference(team) {}

// بررسی لاگین
bool User::authenticate(const string& password) const {
    return passwordHash == hashPassword(password);
}

// ذخیره در فایل
void User::saveToFile() const {
    std::filesystem::create_directory("users");
    ofstream file("users/" + username + ".usr");
    if (file.is_open()) {
        file << username << "\n"
            << nickname << "\n"
            << passwordHash << "\n"
            << winsCount << "\n"
            << teamPreference << "\n";
        file.close();
    }
    else {
        cerr << "خطا در ذخیره کاربر: " << username << endl;
    }
}

// بارگذاری از فایل
User User::loadFromFile(const string& username) {
    ifstream file("users/" + username + ".usr");
    User user;

    if (file.is_open()) {
        getline(file, user.username);
        getline(file, user.nickname);
        getline(file, user.passwordHash);

        string wins;
        getline(file, wins);
        user.winsCount = stoi(wins);

        getline(file, user.teamPreference);
        file.close();
    }
    else {
        cerr << "فایل کاربر یافت نشد: " << username << endl;
    }

    return user;
}

// بارگذاری تمام کاربران
vector<User> User::loadAllUsers() {
    vector<User> users;
    for (const auto& entry : filesystem::directory_iterator("users")) {
        if (entry.path().extension() == ".usr") {
            string uname = entry.path().stem().string();
            users.push_back(loadFromFile(uname));
        }
    }
    return users;
}

// تغییر پسورد
void User::setPassword(const string& newPassword) {
    passwordHash = hashPassword(newPassword);
}

// تابع هش (جایگزین OpenSSL)
string User::hashPassword(const string& password) {
    array<unsigned char, 32> hash = {};
    for (size_t i = 0; i < password.size(); ++i) {
        hash[i % 32] ^= password[i] ^ (i * 31);
    }

    stringstream ss;
    for (unsigned char b : hash) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(b);
    }

    return ss.str();
}
