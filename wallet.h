#pragma once
#include <string>

class Wallet {
public:
    std::string walletId;
    std::string ownerUsername;
    int balance;

    Wallet() = default;
    Wallet(std::string id, std::string owner, int bal);

    std::string serialize() const;
    static Wallet deserialize(const std::string& line);
};
 