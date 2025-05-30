#include "datastorage.h"
#include <fstream>
#include <sstream>
#include <ctime>

bool DataStorage::saveUsers(const std::string& path, const std::vector<User>& users) {
    std::ofstream ofs(path);
    if (!ofs) return false;
    for (const auto& user : users) {
        ofs << user.serialize() << '\n';
    }
    return true;
}

std::vector<User> DataStorage::loadUsers(const std::string& path) {
    std::ifstream ifs(path);
    std::vector<User> users;
    std::string line;
    while (std::getline(ifs, line)) {
        if (!line.empty()) {
            users.push_back(User::deserialize(line));
        }
    }
    return users;
}

bool DataStorage::saveWallets(const std::string& path, const std::vector<Wallet>& wallets) {
    std::ofstream ofs(path);
    if (!ofs) return false;
    for (const auto& wallet : wallets) {
        ofs << wallet.serialize() << '\n';
    }
    return true;
}

std::vector<Wallet> DataStorage::loadWallets(const std::string& path) {
    std::ifstream ifs(path);
    std::vector<Wallet> wallets;
    std::string line;
    while (std::getline(ifs, line)) {
        if (!line.empty()) {
            wallets.push_back(Wallet::deserialize(line));
        }
    }
    return wallets;
}

void DataStorage::writeLog(const std::string& path, const std::string& message) {
    std::ofstream ofs(path, std::ios::app);
    if (!ofs) return;
    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "[%Y-%m-%d %H:%M:%S] ", std::localtime(&now));
    ofs << buf << message << '\n';
}

bool DataStorage::backupData(const std::string& source, const std::string& backupPath) {
    std::ifstream src(source, std::ios::binary);
    std::ofstream dst(backupPath, std::ios::binary);
    if (!src || !dst) return false;
    dst << src.rdbuf();
    return true;
}

bool DataStorage::restoreData(const std::string& backupPath, const std::string& destPath) {
    return backupData(backupPath, destPath); // Reusing backup logic for restoration
}