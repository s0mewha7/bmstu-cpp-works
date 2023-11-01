#pragma once

#include <iostream>

char* convertToOctalString(int number) {
    const int maxLength = 12; // Максимальная длина строки для int в восьмеричной системе счисления (-2147483648 включает 11 цифр и знак '-')
    char* result = new char[maxLength];
    int index = 0;

    if (result == nullptr) {
        return nullptr; // Ошибка выделения памяти
    }

    // Если число отрицательное, добавляем минус и смещаем индекс
    if (number < 0) {
        result[index] = '-';
        number = -number;
        index++;
    }

    // Добавляем "0o" в начало строки
    result[index++] = '0';
    result[index++] = 'o';

    // Преобразуем число в восьмеричную систему и добавляем его в строку
    int octalDigits[11];
    int octalIndex = 0;

    if (number == 0) {
        octalDigits[octalIndex] = 0;
        octalIndex++;
    }
    else {
        while (number > 0) {
            octalDigits[octalIndex] = number % 8;
            number /= 8;
            octalIndex++;
        }
    }

    for (int i = octalIndex - 1; i >= 0; i--) {
        result[index] = '0' + octalDigits[i];
        index++;
    }
    return result;
}