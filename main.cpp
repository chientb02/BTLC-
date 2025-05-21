#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include "user.h"
#include "auth.h"

using namespace std;

vector<User> users;

// Ham tim nguoi dung theo ten dang nhap
User* findUser(const string& username) {
    for (auto& user : users) {
        if (user.username == username) {
            return &user;
        }
    }
    return nullptr;
}

// Ham kiem tra do manh cua mat khau
bool isStrongPassword(const string& password) {
    if (password.length() < 8) return false;
    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        if (islower(c)) hasLower = true;
        if (isdigit(c)) hasDigit = true;
    }
    return hasUpper && hasLower && hasDigit;
}

// Ham kiem tra email hop le
bool isValidEmail(const string& email) {
    size_t at = email.find('@');
    size_t dot = email.find('.', at);
    return at != string::npos && dot != string::npos && dot > at + 1;
}

// Ham dang ky nguoi dung moi
void registerUser() {
    string username, password, fullName, email;
    
    cout << "Nhap ten dang nhap (3-20 ky tu): ";
    cin >> username;
    if (username.length() < 3 || username.length() > 20) {
        cout << "Ten dang nhap phai tu 3-20 ky tu.\n";
        return;
    }
    
    if (findUser(username)) {
        cout << "Ten dang nhap da ton tai.\n";
        return;
    }

    cout << "Nhap mat khau (it nhat 8 ky tu, bao gom chu hoa, chu thuong va so): ";
    cin >> password;
    if (!isStrongPassword(password)) {
        cout << "Mat khau khong du manh.\n";
        return;
    }

    cout << "Nhap ho ten: ";
    cin.ignore();
    getline(cin, fullName);

    cout << "Nhap email: ";
    cin >> email;
    if (!isValidEmail(email)) {
        cout << "Email khong hop le.\n";
        return;
    }

    string hashedPwd = Auth::hashPassword(password);
    User newUser(username, hashedPwd, fullName, email, Role::USER, false);
    users.push_back(newUser);

    cout << "Dang ky thanh cong!\n";
}

// Ham dang nhap
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

// Ham chinh
int main() {
    srand(time(0));
    int choice;
    User* currentUser = nullptr;

    while (true) {
        cout << "\n===== HE THONG QUAN LY VI DIEM THUONG =====\n";
        if (currentUser) {
            cout << "Xin chao, " << currentUser->fullName << "!\n";
            cout << "1. Dang xuat\n";
            cout << "2. Thoat\n";
        } else {
            cout << "1. Dang ky\n";
            cout << "2. Dang nhap\n";
            cout << "3. Thoat\n";
        }
        cout << "Lua chon: ";
        cin >> choice;

        if (currentUser) {
            if (choice == 1) {
                currentUser = nullptr;
                cout << "Da dang xuat.\n";
            } else if (choice == 2) {
                cout << "Thoat chuong trinh.\n";
                break;
            }
        } else {
            if (choice == 1) {
                registerUser();
            } else if (choice == 2) {
                currentUser = loginUser();
            } else if (choice == 3) {
                cout << "Thoat chuong trinh.\n";
                break;
            } else {
                cout << "Lua chon khong hop le.\n";
            }
        }
    }

    return 0;
}
