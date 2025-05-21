#pragma once
#include <string>
#include "user.h"

class Auth {
public:
    static std::string hashPassword(const std::string& password);
    static bool verifyPassword(const std::string& password, const std::string& hash);
    static std::string generateRandomPassword(int length = 10);
    static bool changePassword(User& user, const std::string& oldPassword, const std::string& newPassword);
};