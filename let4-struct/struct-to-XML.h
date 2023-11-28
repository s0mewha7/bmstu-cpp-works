#ifndef LET4_STRUCT_STRUCT_TO_XML_H_
#define LET4_STRUCT_STRUCT_TO_XML_H_
#include "struct.h"

void printMobilePhone(std::istream &is, std::ostream &os) {
  size_t length;
  is >> length;
  if (!is) {
    os << "Invalid input format for length." << std::endl;
    return;
  }

  auto *array = new MobilePhone[length];

  for (size_t i = 0; i < length; ++i) {
    double weight;
    bool is_broken;
    double price;

    if (!(is >> weight >> is_broken >> price)) {
      os << "Invalid input format for mobile phone " << i << "." << std::endl;
      delete[] array;  //  Delete the allocated array
      return;
    }

    array[i] = MobilePhone{weight, is_broken, price};
  }

  os << "<MobilePhones>" << std::endl;
  for (size_t i = 0; i < length; ++i) {
    os << "\t<MobilePhone id=\"" << i << "\" weight=\"" << array[i].weight
       << "\" is_broken=\"" << std::boolalpha << array[i].is_broken
       << std::noboolalpha << "\" price=\"" << array[i].price << "\"/>"
       << std::endl;
  }
  os << "</MobilePhones>" << std::endl;

  delete[] array;
}
#endif  // LET4_STRUCT_STRUCT_TO_XML_H_
