// datastorage.h
#pragma once
#include "user.h"
#include "wallet.h"
#include <vector>

class DataStorage {
public:
    static bool saveUsers(const std::string& path, const std::vector<User>& users);
    static std::vector<User> loadUsers(const std::string& path);

    static bool saveWallets(const std::string& path, const std::vector<Wallet>& wallets);
    static std::vector<Wallet> loadWallets(const std::string& path);

    static void writeLog(const std::string& path, const std::string& message);
};
 