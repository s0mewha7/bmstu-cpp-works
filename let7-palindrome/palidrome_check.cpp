#include <iostream>
#include <sstream>
#include <fstream>
#include <ostream>
#include <algorithm>
#include <cctype>

std::string read_file_from_path(const std::string &path) {
    std::ifstream f(path);
    std::string result;
    if (f) {
        std::ostringstream ss;
        ss << f.rdbuf();
        return ss.str();
    } else {
        return {};
    }
}

bool is_palindrome(const std::string &basicString) {
    for (size_t i = 0; i != (basicString.length() / 2); ++i) {
        if (std::tolower(basicString[i]) != std::tolower(basicString[basicString.length() - i - 1])) {
            return false;
        }
    }
    return true;
}

std::string selection_string(std::string &from, std::string &to) {
    size_t i = 0;
    while (from[i] != '\n') {
        to.push_back(from[i]);
        i++;
    }
    from.erase(0, i + 1);
    return to;
}


void finding_palindromes(std::string file, size_t size_of_palindromes = 0) {
    size_t quantity = std::count(file.begin(), file.end(), '\n');
    auto *arr = new std::string[quantity];
    for (size_t i = 0; i != quantity; ++i) {
        arr[i] = selection_string(file, arr[i]);
    }
    for (size_t s = 0; s != quantity; ++s) {
        if (is_palindrome(arr[s]) == true) {
            size_of_palindromes++;
        }
    }
    size_t i = 0;
    auto *palindromes = new std::string[size_of_palindromes];
    for (size_t s = 0; s != quantity; ++s) {
        if (is_palindrome(arr[s]) == true) {
            palindromes[i] = arr[s];
            ++i;
        }
    }

    std::cout  << "\"count_palindromes\": "<< size_of_palindromes << ',' << std::endl << "palindromes\": [";
    for (size_t s = 0; s != size_of_palindromes; ++s) {
        if (s == size_of_palindromes - 1) {
            std::cout << '\"' << palindromes[s] << '\"';
        } else {
            std::cout << '\"' << palindromes[s] << '\"' << ',' << " ";
        }
    }
    std::cout << ']';
    delete[] arr;
    delete[] palindromes;
}


int mainFunc7(int argc, char **argv) {
    std::string file = read_file_from_path(argv[1]);
    finding_palindromes(file);
    return 0;
}