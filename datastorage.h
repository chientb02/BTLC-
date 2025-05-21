#pragma once
#include "user.h"
#include "wallet.h"
#include <vector>
#include <string>

class DataStorage {
public:
    static bool saveUsers(const std::string& path, const std::vector<User>& users);
    static std::vector<User> loadUsers(const std::string& path);
    static bool saveWallets(const std::string& path, const std::vector<Wallet>& wallets);
    static std::vector<Wallet> loadWallets(const std::string& path);
    static void writeLog(const std::string& path, const std::string& message);
    static bool backupData(const std::string& source, const std::string& backupPath);
    static bool restoreData(const std::string& backupPath, const std::string& destPath);
};