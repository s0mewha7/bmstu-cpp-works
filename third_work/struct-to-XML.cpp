/*
INPUT:
3
1.3 1 1000.23
2.2 0 1123
1.0 1 100500

OUTPUT:
<MobilePhones>
    <MobilePhone id="0" weight="1.3" is_broken="true" price="1000.23"/>
    <MobilePhone id="1" weight="2.2" is_broken="false" price="1123"/>
    <MobilePhone id="2" weight="1.0" is_broken="true" price="100500"/>
</MobilePhones>
*/

#include <iostream>

#include <cinttypes>

namespace  {
    struct MobilePhone{
        double weight;
        bool is_broken;
        double price;
    };
};

// Функция вывода структуры MobilePhone в формате XML
void printMobilePhoneXML(const ::MobilePhone &phone, size_t id){
    std::cout << "  <<MobilePhone id=\"" << id << "\" weigth=\"" << phone.weight << "\" is_broken=\"" << (phone.is_broken ? "true" : "false") << "\" price=\"" << phone.price << "\"/>" << std::endl;
}

int main(int argc, char **argv){
    
    std::uint64_t mobile_phones;
    std::cin >> mobile_phones;

    auto *phones = new MobilePhone[mobile_phones]; //dynamic array

    for(size_t i = 0; i < mobile_phones; ++ i){
        ::MobilePhone phone;
        std::cin >> phone.weight >> phone.is_broken >> phone.price;
        phones[i] = phone;
    }
    std::cout << "<MobilePhones>" << std::endl;
    for(size_t i = 0; i < mobile_phones; ++i){
        printMobilePhoneXML(phones[i], i);
    }
    std::cout << "<MobilePhones>" << std::endl;

    delete[] phones; // освобождаем память 
    return 0;
}