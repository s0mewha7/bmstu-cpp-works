#include <iostream>
#include <string>
#include <vector>

void generatePasswords(size_t length, const std::string &charset, const std::string &currentPassword) {
    if (length == 0) {
        std::cout << currentPassword << std::endl;
        return;
    }

    for (const auto &chr : charset) {
        generatePasswords(length - 1, charset, currentPassword + chr);
    }
}

int main8(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <password_length>" << std::endl;
        return 1;
    }
    auto passwordLength = std::stoi(argv[1]);
    if (passwordLength <= 0) {
        std::cerr << "Password length should be a positive integer." << std::endl;
        return 1;
    }

    std::string charset = "1234567890AaBbCcDdEeFfGgHhXxYyZz";
    generatePasswords(passwordLength, charset, "");

    return 0;
}
