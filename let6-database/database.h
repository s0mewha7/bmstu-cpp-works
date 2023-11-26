//
// Created by somewhat on 25.11.23.
//

#ifndef BMSTU_WORKS_DATABASE_H
#define BMSTU_WORKS_DATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Student {
    std::string name;
    size_t age;
    float rating;

    // Конструктор для удобства создания объектов Student
    Student(const std::string& n, int a, int r) : name(n), age(a), rating(r) {}
};

bool compareByAge(const Student& a, const Student& b) {
    return a.age > b.age;
}

bool compareByName(const Student& a, const Student& b) {
    return a.name < b.name;
}

bool compareByRating(const Student& a, const Student& b) {
    return a.rating > b.rating;
}

bool compareByRatingAndName(const Student& a, const Student& b) {
    return a.rating == b.rating ? a.rating < b.rating : a.rating > b.rating;
}

std::vector<Student> readStudentsFromFile(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error opening file, do smth!: " + file_path);
    }

    size_t num_records;
    file.read(reinterpret_cast<char*>(&num_records), sizeof(num_records));

    std::vector<Student> students;

    for (int i = 0; i < num_records; ++i) {
        char name_buffer[256];
        file.read(name_buffer, sizeof(name_buffer));
        std::string name(name_buffer);

        int age, rating;
        file.read(reinterpret_cast<char*>(&age), sizeof(age));
        file.read(reinterpret_cast<char*>(&rating), sizeof(rating));

        students.emplace_back(name, age, rating);
    }

    file.close();

    return students;
}

int main6(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <file_path> <option>" << std::endl;
        return 1;
    }

    std::string file_path = argv[1];
    char option = argv[2][1];

    std::vector<Student> students;
    try {
        students = readStudentsFromFile(file_path);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    switch (option) {
        case 'a':
            std::cout << "TOP 15 oldest students:" << std::endl;
            std::sort(students.begin(), students.end(), compareByAge);
            break;
        case 'o':
            std::cout << "TOP 15 students with highest ratings in alphabetical order:" << std::endl;
            std::sort(students.begin(), students.end(), compareByName);
            std::sort(students.begin(), students.begin() + std::min(15, static_cast<int>(students.size())), compareByRating);
            break;
        case 'g':
            std::cout << "TOP 15 students with highest ratings on the department:" << std::endl;
            std::sort(students.begin(), students.end(), compareByRating);
            break;
        case 'r':
            std::cout << "TOP 15 students with highest ratings on the department in alphabetical order:" << std::endl;
            std::sort(students.begin(), students.end(), compareByName);
            std::sort(students.begin(), students.begin() + std::min(15, static_cast<int>(students.size())), compareByRatingAndName);
            break;
        default:
            std::cerr << "Invalid option: " << option << std::endl;
            return 1;
    }

    for (int i = 0; i < std::min(15, static_cast<int>(students.size())); ++i) {
        std::cout << students[i].name << " - Age: " << students[i].age << ", Rating: " << students[i].rating << std::endl;
    }

    return 0;
}

#endif //BMSTU_WORKS_DATABASE_H
