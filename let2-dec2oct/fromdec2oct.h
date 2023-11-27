#ifndef LET2_DEC2OCT_FROMDEC2OCT_H_
#define LET2_DEC2OCT_FROMDEC2OCT_H_

#include <iostream>

char *convertToOctalString(int param_number) {
    char *octalcstring = new char[12];

    if (octalcstring == nullptr) {
        return nullptr;
    }
    int index = 0;

    if (param_number < 0) {
        octalcstring[index++] = '-';
        param_number = -param_number;
    }

    octalcstring[index++] = '0';
    octalcstring[index++] = 'o';

    size_t octalIndex = 0;
    auto *octalDigits = new int[11];

    if (param_number == 0) {
        octalDigits[octalIndex++] = 0;
    } else {
        while (param_number > 0) {
            octalDigits[octalIndex++] = param_number % 8;
            param_number /= 8;
        }
    }

    for (int i = octalIndex - 1; i >= 0; i--) {
        octalcstring[index++] = '0' + octalDigits[i];
    }
    octalcstring[index] = '\0';
    delete[] octalDigits;
    return octalcstring;
}

#endif  // LET2_DEC2OCT_FROMDEC2OCT_H_
