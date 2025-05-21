#pragma once
#include <string>

class Utils {
public:
    static bool backupFile(const std::string& source, const std::string& dest);
    static std::string getCurrentTimestamp();
};
