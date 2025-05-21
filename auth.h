#pragma once
#include <string>
#include "user.h"

class Auth {
public:
    static std::string hashPassword(const std::string& password);
    static bool verifyPassword(const std::string& password, const std::string& hash);
    static std::string generateRandomPassword(int length = 10);
};
