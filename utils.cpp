#include "utils.h"
#include <fstream>
#include <ctime>

bool Utils::backupFile(const std::string& source, const std::string& dest) {
    std::ifstream src(source, std::ios::binary);
    std::ofstream dst(dest, std::ios::binary);
    if (!src || !dst) return false;
    dst << src.rdbuf();
    return true;
}

std::string Utils::getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", std::localtime(&now));
    return std::string(buf);
}
