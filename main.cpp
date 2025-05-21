#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "user.h"
#include "wallet.h"
#include "auth.h"
#include "otp.h"
#include "utils.h"

using namespace std;

// Danh sách người dùng và ví
vector<User> users;
vector<Wallet> wallets;

// Hàm tìm người dùng theo tên đăng nhập
User* findUser(const string& username) {
    for (auto& user : users) {
        if (user.username == username) {
            return &user;
        }
    }
    return nullptr;
}

// Hàm tìm ví theo ID
Wallet* findWallet(const string& walletId) {
    for (auto& wallet : wallets) {
        if (wallet.walletId == walletId) {
            return &wallet;
        }
    }
    return nullptr;
}

// Hàm lưu danh sách người dùng vào tệp
void saveUsers() {
    ofstream outFile("data/users.txt");
    for (const auto& user : users) {
        outFile << user.serialize() << endl;
    }
    outFile.close();
}

// Hàm tải danh sách người dùng từ tệp
void loadUsers() {
    ifstream inFile("data/users.txt");
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            users.push_back(User::deserialize(line));
        }
    }
    inFile.close();
}

// Hàm lưu danh sách ví vào tệp
void saveWallets() {
    ofstream outFile("data/wallets.txt");
    for (const auto& wallet : wallets) {
        outFile << wallet.serialize() << endl;
    }
    outFile.close();
}

// Hàm tải danh sách ví từ tệp
void loadWallets() {
    ifstream inFile("data/wallets.txt");
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            wallets.push_back(Wallet::deserialize(line));
        }
    }
    inFile.close();
}

// Hàm ghi log giao dịch
void logTransaction(const string& sender, const string& receiver, int amount) {
    ofstream logFile("data/transactions.txt", ios::app);
    logFile << Utils::getCurrentTimestamp() << " | "
            << "From: " << sender << " | "
            << "To: " << receiver << " | "
            << "Amount: " << amount << endl;
    logFile.close();
}

// Hàm đăng ký người dùng mới
void registerUser() {
    string username, password, fullName, email;
    cout << "Nhap ten dang nhap: ";
    cin >> username;
    if (findUser(username)) {
        cout << "Ten dang nhap da ton tai.\n";
        return;
    }
    cout << "Nhap mat khau: ";
    cin >> password;
    cout << "Nhap ho ten: ";
    cin.ignore();
    getline(cin, fullName);
    cout << "Nhap email: ";
    cin >> email;

    string hashedPwd = Auth::hashPassword(password);
    User newUser(username, hashedPwd, fullName, email, Role::USER, false);
    users.push_back(newUser);

    // Tao vi cho nguoi dung
    string walletId = "W" + to_string(rand() % 10000 + 1);
    Wallet newWallet(walletId, username, 0);
    wallets.push_back(newWallet);

    cout << "Dang ky thanh cong. Vi cua ban co ID: " << walletId << "\n";
}

// Hàm đăng nhập
User* loginUser() {
    string username, password;
    cout << "Ten dang nhap: ";
    cin >> username;
    cout << "Mat khau: ";
    cin >> password;

    User* user = findUser(username);
    if (user && Auth::verifyPassword(password, user->password_hash)) {
        cout << "Dang nhap thanh cong.\n";
        return user;
    } else {
        cout << "Ten dang nhap hoac mat khau khong dung.\n";
        return nullptr;
    }
}

// Hàm hiển thị số dư ví
void viewBalance(User* user) {
    for (const auto& wallet : wallets) {
        if (wallet.ownerUsername == user->username) {
            cout << "So du vi (" << wallet.walletId << "): " << wallet.balance << " diem\n";
            return;
        }
    }
    cout << "Khong tim thay vi.\n";
}

// Hàm chuyển điểm giữa các ví
void transferPoints(User* user) {
    string targetWalletId;
    int amount;
    cout << "Nhap ID vi dich: ";
    cin >> targetWalletId;
    cout << "Nhap so diem can chuyen: ";
    cin >> amount;

    Wallet* senderWallet = nullptr;
    Wallet* receiverWallet = findWallet(targetWalletId);

    for (auto& wallet : wallets) {
        if (wallet.ownerUsername == user->username) {
            senderWallet = &wallet;
            break;
        }
    }

    if (!senderWallet) {
        cout << "Khong tim thay vi cua ban.\n";
        return;
    }

    if (!receiverWallet) {
        cout << "Vi dich khong ton tai.\n";
        return;
    }

    if (senderWallet->balance < amount) {
        cout << "So du khong du de thuc hien giao dich.\n";
        return;
    }

    // Xac thuc OTP
    string otp = OTP::generateOTP();
    cout << "Ma OTP cua ban: " << otp << "\n";
    string inputOtp;
    cout << "Nhap ma OTP: ";
    cin >> inputOtp;

    if (!OTP::validateOTP(inputOtp, otp)) {
        cout << "Ma OTP khong hop le.\n";
        return;
    }

    // Thuc hien giao dich
    senderWallet->balance -= amount;
    receiverWallet->balance += amount;
    cout << "Chuyen diem thanh cong.\n";

    // Ghi log giao dich
    logTransaction(senderWallet->walletId, receiverWallet->walletId, amount);
}

// Hàm chính
int main() {
    srand(time(0));

    // Tải dữ liệu từ tệp
    loadUsers();
    loadWallets();

    int choice;
    User* currentUser = nullptr;

    while (true) {
        cout << "\n===== HE THONG QUAN LY VI DIEM THUONG =====\n";
        cout << "1. Dang ky\n";
        cout << "2. Dang nhap\n";
        cout << "3. Thoat\n";
        cout << "Lua chon: ";
        cin >> choice;

        if (choice == 1) {
            registerUser();
            saveUsers();
            saveWallets();
        } else if (choice == 2) {
            currentUser = loginUser();
            if (currentUser) {
                int userChoice;
                while (true) {
                    cout << "\n===== MENU NGUOI DUNG =====\n";
                    cout << "1. Xem so du vi\n";
                    cout << "2. Chuyen diem\n";
                    cout << "3. Dang xuat\n";
                    cout << "Lua chon: ";
                    cin >> userChoice;

                    if (userChoice == 1) {
                        viewBalance(currentUser);
                    } else if (userChoice == 2) {
                        transferPoints(currentUser);
                        saveWallets();
                    } else if (userChoice == 3) {
                        currentUser = nullptr;
                        break;
                    } else {
                        cout << "Lua chon khong hop le.\n";
                    }
                }
            }
        } else if (choice == 3) {
            cout << "Thoat chuong trinh.\n";
            break;
        } else {
            cout << "Lua chon khong hop le.\n";
        }
    }

    // Lưu dữ liệu trước khi thoát
    saveUsers();
    saveWallets();

    return 0;
}
