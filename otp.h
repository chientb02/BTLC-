#pragma once
#include <string>

class OTP {
public:
    static std::string generateOTP();
    static bool validateOTP(const std::string& input, const std::string& otp);
};
