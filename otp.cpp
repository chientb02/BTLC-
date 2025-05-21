#include "otp.h"
#include <random>
#include <chrono>

std::string OTP::generateOTP() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    std::string otp;
    for (int i = 0; i < 6; ++i)
        otp += std::to_string(dis(gen));
    return otp;
}

bool OTP::validateOTP(const std::string& input, const std::string& otp) {
    return input == otp;
}
