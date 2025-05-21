#include "wallet.h"
#include <sstream>

Wallet::Wallet(std::string id, std::string owner, int bal)
    : walletId(id), ownerUsername(owner), balance(bal) {}

std::string Wallet::serialize() const {
    std::ostringstream oss;
    oss << walletId << "|" << ownerUsername << "|" << balance;
    return oss.str();
}

Wallet Wallet::deserialize(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    Wallet wallet;
    std::getline(iss, wallet.walletId, '|');
    std::getline(iss, wallet.ownerUsername, '|');
    std::getline(iss, token, '|');
    wallet.balance = std::stoi(token);
    return wallet;
}
