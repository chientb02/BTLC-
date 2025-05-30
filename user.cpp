#include "user.h"
#include <sstream>

User::User(std::string user, std::string pwd_hash, std::string name, std::string email, std::string phone, Role r, bool isAutoPwd)
    : username(user), password_hash(pwd_hash), full_name(name), email(email), phone(phone), role(r), isAutoGeneratedPwd(isAutoPwd) {}

std::string User::serialize() const {
    std::ostringstream oss;
    oss << username << "|" << password_hash << "|" << full_name << "|" << email << "|" << phone << "|"
        << static_cast<int>(role) << "|" << isAutoGeneratedPwd;
    return oss.str();
}

User User::deserialize(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    User user;
    std::getline(iss, user.username, '|');
    std::getline(iss, user.password_hash, '|');
    std::getline(iss, user.full_name, '|');
    std::getline(iss, user.email, '|');
    std::getline(iss, user.phone, '|');
    std::getline(iss, token, '|');
    user.role = static_cast<Role>(std::stoi(token));
    std::getline(iss, token, '|');
    user.isAutoGeneratedPwd = (token == "1");
    return user;
}

bool User::updateInfo(const std::string& newFullName, const std::string& newEmail, const std::string& newPhone) {
    full_name = newFullName;
    email = newEmail;
    phone = newPhone;
    return true;
}