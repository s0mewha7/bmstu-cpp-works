#include "function.h"

void generatePasswords(const std::string &charset, int length, std::string currentPassword)
{
    if (length == 0)
    {
        std::cout << currentPassword << std::endl;
        return;
    }
    for (const auto &c : charset)
    {
        generatePasswords(charset, length - 1, currentPassword + c);
    }
}

void generated_password()
{
    std::ofstream outputFile("passwords.txt");

    if (outputFile.is_open())
    {
        generatePasswords(charset, passwordLength, "");

        outputFile.close();
    }
    else
    {
        std::cerr << "File doesn't exists" << std::endl;
    }
}