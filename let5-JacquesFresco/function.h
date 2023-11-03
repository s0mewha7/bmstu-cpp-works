#ifndef PASSWORD_GENERATOR_H
#define PASSWORD_GENERATOR_H

#include <iostream>
#include <fstream>
#include <string> 

std::string charset = "1234567890AaBbCcDdEeFfHhGgXxYyZz";
const size_t passwordLength = 5;

void generated_password();

#endif // PASSWORD_GENERATOR_H
