<h1>Bài tập lớn môn c++</h1>
# Hệ Thống Quản Lý Ví Điểm Thưởng 🚀

![C++](https://img.shields.io/badge/C++-11-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Status](https://img.shields.io/badge/status-complete-success.svg)

Hệ thống Quản Lý Ví Điểm Thưởng là một ứng dụng console C++ cho phép quản lý tài khoản người dùng và ví điểm thưởng. Người dùng có thể đăng ký, đăng nhập, chuyển điểm, xem số dư, cập nhật thông tin, và đổi mật khẩu. Quản trị viên (Admin) có quyền quản lý danh sách người dùng, tạo tài khoản mới, và sửa thông tin. Dữ liệu được lưu trữ trong file văn bản, với cơ chế sao lưu và xác thực OTP để đảm bảo an toàn.

---

## 📋 Giới thiệu dự án

Ứng dụng cung cấp giao diện console thân thiện với các tính năng:
- **Người dùng thường (User)**: Quản lý ví cá nhân, chuyển điểm, cập nhật thông tin.
- **Quản trị viên (Admin)**: Quản lý toàn bộ người dùng trong hệ thống.
- **Bảo mật**: Mã hóa mật khẩu, xác thực OTP cho các thao tác nhạy cảm.
- **Lưu trữ**: Dữ liệu được lưu vào file với sao lưu tự động.

Dự án sử dụng thư viện chuẩn C++ và không phụ thuộc vào phần mềm bên thứ ba, phù hợp cho các hệ thống giáo dục hoặc quản lý điểm thưởng đơn giản.

---

## 👥 Thành viên tham gia

| Tên                  | Vai trò         | Nhiệm vụ                                                                           |
|----------------------|-----------------|------------------------------------------------------------------------------------|
| Dương Quang Duy      | Thành viên      | Phát triển `main.cpp`,`wallet`,`datastorage`                                       |
| Vũ Đức Chiến         | Thành viên      | Phát triển `user`,`auth`, `main.cpp`                                               |
| Đàm Công Trung       | Thành viên      | Phát triển `otp`, `utils`, `main.cpp`                                              |

---

## 📝 Phân tích và đặc tả chức năng

### Mục tiêu
- Quản lý ví điểm thưởng an toàn, dễ sử dụng.
- Phân quyền rõ ràng giữa User và Admin.
- Đảm bảo tính toàn vẹn dữ liệu với sao lưu và giao dịch atom.

### Đặc tả chức năng

Phân tích và đặc tả chức năng

=> Mục tiêu

Cung cấp hệ thống quản lý ví điểm thưởng an toàn, dễ sử dụng.

Hỗ trợ hai vai trò: User (người dùng thông thường) và Admin (quản trị viên).

Đảm bảo tính bảo mật với xác thực OTP cho các thao tác nhạy cảm.

Lưu trữ và sao lưu dữ liệu để tránh mất mát.

=> Đặc tả chức năng

- Đăng ký tài khoản:

Input: Tên đăng nhập, mật khẩu (hoặc tự sinh bởi Admin), họ tên, email, số điện thoại.

Output: Tài khoản mới với vai trò USER, ví mới với số dư 0.

Xử lý: Kiểm tra tên đăng nhập trùng lặp, mã hóa mật khẩu, lưu vào file data/users.txt và data/wallets.txt.

- Đăng nhập:

Input: Tên đăng nhập, mật khẩu.

Output: Truy cập menu người dùng nếu thành công, yêu cầu đổi mật khẩu nếu mật khẩu tự sinh.

Xử lý: Xác minh mật khẩu mã hóa, trả về con trỏ người dùng.

- Xem số dư ví:

Input: Không có (dựa trên người dùng hiện tại).

Output: ID ví và số dư (định dạng => [số dư] diem).

Xử lý: Tìm ví theo tên đăng nhập, hiển thị thông tin.

- Xem thông tin tài khoản:

Input: Không có.

Output: Hiển thị username, full_name, email, phone, role.

Xử lý: Lấy thông tin từ đối tượng người dùng hiện tại.

- Cập nhật thông tin cá nhân:

Input: Lựa chọn trường (họ tên, email, số điện thoại), giá trị mới, OTP.

Output: Cập nhật thông tin nếu OTP hợp lệ.

Xử lý: Xác thực OTP, cập nhật trường tương ứng, lưu vào file.

- Đổi mật khẩu:

Input: Mật khẩu cũ, mật khẩu mới, OTP.

Output: Đổi mật khẩu nếu mật khẩu cũ và OTP hợp lệ.

Xử lý: Xác minh mật khẩu cũ, mã hóa mật khẩu mới, lưu vào file.

- Chuyển điểm:

Input: ID ví đích, số điểm, OTP.

Output: Chuyển điểm nếu đủ số dư và OTP hợp lệ.

Xử lý: Kiểm tra số dư, thực hiện giao dịch atom, ghi log giao dịch.

- Quản lý người dùng (Admin):

Input: Lựa chọn (xem danh sách, tạo tài khoản, sửa thông tin), thông tin cần thiết.

Output: Danh sách người dùng, tài khoản mới, hoặc thông tin cập nhật.

Xử lý: Hiển thị danh sách, gọi registerUser để tạo tài khoản, hoặc cập nhật thông tin với OTP.

- Khôi phục từ sao lưu:

Input: Đường dẫn file sao lưu cho users.txt và wallets.txt.

Output: Dữ liệu được khôi phục nếu file hợp lệ.

Xử lý: Sao chép file sao lưu vào file chính, tải lại dữ liệu.

### Phân tích
- **Bảo mật**: Mật khẩu được băm, OTP yêu cầu cho các thao tác nhạy cảm.
- **Toàn vẹn**: Giao dịch atom (rollback nếu lưu thất bại), sao lưu tự động.
- **Hạn chế**: OTP chỉ hiển thị trên màn hình, chưa kiểm tra định dạng email/số điện thoại.
- **Mở rộng**: Dễ dàng thêm vai trò mới hoặc tích hợp gửi OTP qua email/SMS.

---

## 🛠️ Cài đặt
BAI TAP GIUA KY MON C++ Cài Đặt chương trình:

1.Tải Visual Studio Code

1.1 Truy cập Visual Studio Code.
1.2 Tải xuống và cài đặt phiên bản phù hợp với hệ điều hành của bạn.
2.Cài đặt Compiler C++(làm theo link sau) Windows:https://code.visualstudio.com/docs/cpp/config-mingw

3.Cài đặt git.

3.1. Truy cập vào https://git-scm.com/downloads/win, và tải 1 trong 2 bản "Standalone Installer" tương thích với máy.
3.2. Tạo tài khoản trên https://github.com, nếu chưa có.
4.Thiết lập hệ thống trên github.

4.1. Tạo 1 Repositories trên github(https://github.com)
4.2. Truy cập đường link https://github.com/chientb02/BTLC-, chọn mục "code" và chọn "download zip".
4.3. Truy vẫn vào Repositories vừa tạo ở bước 4.1 chọn "uploading an existing file" và chọn những file và folder ở trong folder(compressed zip) vừa tải xuống ở bước 4.2 kéo vào ô trước màn hình và chọn "commit changes".
5.Thiết lập chương trình kết nối với hệ thống.

5.1. Tạo 1 folder lưu trữ Repositories vừa tạo ở bước 4.
5.2. Cấu hình Git trên máy tính:
Gõ:
git config --global user.name "Tên của bạn"
git config --global user.email "email@gmail.com"
Thay "Tên của bạn" và "email@gmail.com" bằng tên và email của bạn đã dùng trên GitHub.
5.3. Thiết lập Bash làm terminal mặc định trong Visual Studio Code
5.3.1.Mở VS Code.
5.3.2.Truy cập File > Preferences > Settings (hoặc nhấn Ctrl + ,).
5.3.3.Tìm "Terminal Integrated Default Profile".
5.3.4.Chọn Git Bash (hoặc Bash) làm terminal mặc định.
5.4. Truy vậy vào folder vừa tạo ở bước 5.1, click chuột phải > Git Bash
Gõ:
git init
git branch -M main
git remote add origin "URL của remote repository vừa tạo ở bước 4.1"
git pull origin main
6.Để chạy chương trình vào folder vừa tạo ở bước 5.1 và double click vào run.bat để sử dụng.

### Cấu trúc thư mục
```
reward-wallet-system/
├── data/
│   ├── users.txt           # Lưu thông tin người dùng
│   ├── wallets.txt         # Lưu thông tin ví
│   ├── transactions.txt    # Log giao dịch
│   └── backup/             # File sao lưu
├── src/
│   ├── main.cpp            # Menu và luồng điều khiển
│   ├── user.h/cpp         # Quản lý người dùng
│   ├── wallet.h/cpp       # Quản lý ví
│   ├── auth.h/cpp         # Xác thực và mã hóa
│   ├── otp.h/cpp          # Tạo/xác thực OTP
│   ├── datastorage.h/cpp  # Lưu trữ dữ liệu
└── README.md              # Hướng dẫn
```

### Biên dịch
1. Tạo thư mục dữ liệu:
   ```bash
   mkdir -p data/backup
   ```
2. Biên dịch:
   ```bash
   g++ -std=c++11 src/main.cpp src/user.cpp src/wallet.cpp src/auth.cpp src/otp.cpp src/datastorage.cpp -o reward_wallet
   g++ main.cpp user.cpp wallet.cpp auth.cpp datastorage.cpp utils.cpp otp.cpp -lssl -lcrypto -o app
   ```

---

## ▶️ Chạy chương trình

### Lệnh chạy
- Linux/macOS:
  ```bash
  ./reward_wallet
  ```
- Windows:
  ```bash
  reward_wallet.exe
  ```

### Thao tác
1. **Menu chính**:
   ```plaintext
   ==================================================
   | HE THONG QUAN LY VI DIEM THUONG                |
   ==================================================
   | 1. Dang ky                                     |
   | 2. Dang nhap                                   |
   | 3. Khoi phuc tu sao luu                        |
   | 4. Thoat                                       |
   ==================================================
   Lua chon: 
   ```
   - **1**: Đăng ký tài khoản.
   - **2**: Đăng nhập.
   - **3**: Khôi phục dữ liệu.
   - **4**: Thoát.

2. **Ví dụ đăng ký**:
   ```plaintext
   Nhap ten dang nhap: duy
   Nhap mat khau: pass123
   Nhap ho ten: Nguyen Van Duy
   Nhap email: duy@example.com
   Nhap so dien thoai: 123456789
   Dang ky thanh cong!
   Vi cua ban co ID: W1234
   ```

3. **Ví dụ đăng nhập**:
   ```plaintext
   Ten dang nhap: duy
   Mat khau: pass123
   Dang nhap thanh cong!
   ```

4. **Menu người dùng (User)**:
   ```plaintext
   | 1. Xem so du vi                        |
   | 2. Chuyen diem                         |
   | 3. Xem thong tin tai khoan             |
   | 4. Cap nhat thong tin ca nhan          |
   | 5. Doi mat khau                        |
   | 6. Dang xuat                           |
   ```
   - **Admin** có thêm tùy chọn "6. Quan ly nguoi dung".

5. **Ví dụ xem số dư**:
   ```plaintext
   Vi ID: W1234
   So du: => 0 diem
   ```

6. **Ví dụ cập nhật email**:
   ```plaintext
   Lua chon: 2
   Nhap email moi: new@example.com
   Ma OTP (gui den duy@example.com): 123456
   Nhap ma OTP: 123456
   Cap nhat email thanh cong.
   ```

---

## 💻 Mã nguồn

### Tổng quan
- **main.cpp**: Điều khiển menu, gọi các hàm chức năng.
- **user.h/cpp**: Quản lý thông tin người dùng (username, full_name, email, v.v.).
- **wallet.h/cpp**: Quản lý ví (ID, số dư, chủ sở hữu).
- **auth.h/cpp**: Xác thực (băm mật khẩu, kiểm tra đăng nhập).
- **otp.h/cpp**: Tạo và xác thực OTP.
- **datastorage.h/cpp**: Lưu trữ và sao lưu dữ liệu.

### Trích đoạn mã (main.cpp)
```cpp
// In tiêu đề với viền
// Input: Chuỗi tiêu đề
// Output: Tiêu đề được căn giữa trong khung
void printTitle(const string& title) {
    printLine();
    cout << "| " << setw(46) << left << title << " |\n";
    printLine();
}

// Xem số dư ví
// Input: Con trỏ người dùng
// Output: ID ví, số dư (định dạng => [số dư] diem)
void viewBalance(User* user) {
    printTitle("SO DU VI");
    for (const auto& wallet : wallets) {
        if (wallet.ownerUsername == user->username) {
            cout << "Vi ID: " << wallet.walletId << "\n";
            cout << "So du: => " << wallet.balance << " diem\n";
            return;
        }
    }
    cout << "Khong tim thay vi.\n";
}
```

### Xử lý
- **Input**: Chuỗi (username, email), số (số điểm, lựa chọn), ký tự (y/n).
- **Output**: Thông báo console, file dữ liệu (`users.txt`, `wallets.txt`).
- **Thủ tục**: Kiểm tra đầu vào, xác thực OTP, lưu trữ atom, sao lưu tự động.

---

## 📚 Tài liệu tham khảo
- [C++ Reference](https://en.cppreference.com/w/) - Thư viện chuẩn C++.
- [Stack Overflow](https://stackoverflow.com/questions/25020129/cin-ignore-numeric-limitsstreamsizemax-n) - Xử lý bộ đệm `cin`.
- [GeeksforGeeks](https://www.geeksforgeeks.org/how-to-print-a-table-in-c/) - Thiết kế bảng console.
- [OWASP](https://owasp.org/www-community/password-hashing) - Mã hóa mật khẩu.

---

## ⚠️ Lưu ý
- Tạo thư mục `data/` và `data/backup/` trước khi chạy.
- OTP hiển thị trên màn hình; cần thư viện như `libcurl` để gửi email/SMS.
- Có thể thêm kiểm tra định dạng email (chứa `@`) hoặc số điện thoại (chỉ số).
