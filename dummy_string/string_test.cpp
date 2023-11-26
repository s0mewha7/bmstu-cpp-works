#include "basic_string.h"   // Заголовочные файлы текущего проекта
#include <gtest/gtest.h>    // Заголовочные файлы Google Test
#include <cstddef>           // Заголовочные файлы стандартной библиотеки C
#include <iostream>          // Заголовочные файлы стандартной библиотеки C++


// ALL TEST FOR TEMPLATE STRING IMPLEMENTATION
TEST(StringTest, DefaultConstructor) {
    bmstu::string str;
    ASSERT_STREQ(str.c_str(), "");
    ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, DefaultConstructorW) {
    bmstu::wstring str;
    ASSERT_STREQ(str.c_str(), L"");
    ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, InitializerListConstructorW) {
    bmstu::wstring str{};
    ASSERT_STREQ(str.c_str(), L"");
    ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, InitializerListConstructor) {
    bmstu::wstring str{};
    ASSERT_STREQ(str.c_str(), L"");
    ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, InitializerListConstructorNonEmpty) {
    bmstu::wstring str{L'С', L'Л', L'О', L'В', L'О'};
    ASSERT_STREQ(str.c_str(), L"СЛОВО");
    ASSERT_EQ(str.size(), 5);
}

TEST(StringTest, ConstructorSizeW) {
    bmstu::wstring str(10);
    ASSERT_STREQ(str.c_str(), L"          ");
    ASSERT_EQ(str.size(), 10);
}

TEST(StringTest, ConstructorSize) {
    bmstu::string str(10);
    ASSERT_STREQ(str.c_str(), "          ");
    ASSERT_EQ(str.size(), 10);
}

TEST(StringTest, ConstructorSizeOne) {
    bmstu::wstring str(1);
    ASSERT_STREQ(str.c_str(), L" ");
    ASSERT_EQ(str.size(), 1);
}

TEST(StringTest, FromCStr) {
    bmstu::string str("str\n");
    ASSERT_STREQ(str.c_str(), "str\n");
    ASSERT_EQ(str.size(), 4);
}

TEST(StringTest, FromWCStr) {
    bmstu::wstring str(L"おはよう");
    ASSERT_STREQ(str.c_str(), L"おはよう");
    ASSERT_EQ(str.size(), 4);
}

TEST(StringTest, FromWCStrSymbol) {
    bmstu::wstring str(L"おはよう");
    ASSERT_STREQ(str.c_str(), L"おはよう");
    wchar_t c = L'お';
    ASSERT_EQ(str[0], c);
}

TEST(StringTest, USymbolsW) {
    bmstu::wstring str(L"お");
    ASSERT_STREQ(str.c_str(), L"お");
    wchar_t c = L'お';
    ASSERT_EQ(str.size(), 1);
}

TEST(StringTest, USymbol) {
    bmstu::string str("\xe3\x81\x8a\x00");
    ASSERT_STREQ(str.c_str(), "お");
    ASSERT_EQ(str.size(), 3);
}

TEST(StringTest, USymbols) {
    bmstu::string str("おはよう");
    ASSERT_STREQ(str.c_str(), "おはよう");
    ASSERT_EQ(str.size() + 1, sizeof("おはよう"));
}

TEST(StringTest, Empty) {
    bmstu::string empty;
    ASSERT_EQ(empty.size(), 0);
    ASSERT_STREQ(empty.c_str(), "");
}

TEST(StringTest, EmptyW) {
    bmstu::wstring empty;
    ASSERT_EQ(empty.size(), 0);
    ASSERT_STREQ(empty.c_str(), L"");
}

TEST(StringTest, CopyAssignW) {
    bmstu::wstring empty(L"Non Empty строка");
    bmstu::wstring nonempty = empty;
    ASSERT_STREQ(nonempty.c_str(), L"Non Empty строка");
    ASSERT_EQ(nonempty.size(), 16);
}

TEST(StringTest, CopyConstructor) {
    bmstu::string empty("Non Empty строка");
    bmstu::string nonempty = empty;
    ASSERT_STREQ(nonempty.c_str(), "Non Empty строка");
    ASSERT_EQ(nonempty.size(), sizeof("Non Empty строка") - 1);
}

TEST(StringTest, CopyAssignConstructor) {
    bmstu::string *str = new bmstu::string("str");
    bmstu::string *nonempty = new bmstu::string;
    *nonempty = *str;
    ASSERT_STREQ(nonempty->c_str(), "str");
    ASSERT_EQ(nonempty->size(), sizeof("str") - 1);
    delete str;
    delete nonempty;
}

TEST(StringTest, MoveAssignConstructor) {
    bmstu::string str("str");
    bmstu::string str2("other");
    ASSERT_STREQ(str.c_str(), "str");
    ASSERT_EQ(str.size(), sizeof("str") - 1);
    ASSERT_STREQ(str2.c_str(), "other");
    ASSERT_EQ(str2.size(), sizeof("other") - 1);
    str2 = std::move(str);
    ASSERT_STREQ(str2.c_str(), "str");
    ASSERT_EQ(str2.size(), sizeof("str") - 1);
    ASSERT_STREQ(str.c_str(), "");
    ASSERT_EQ(str.size(), 0);
}


TEST(StringTest, MoveAssignConstructor2) {
    bmstu::string str("str");
    bmstu::string str2("other");
    str2 = std::move(str);
    ASSERT_STREQ(str2.c_str(), "str");
    ASSERT_EQ(str2.size(), sizeof("str") - 1);

    ASSERT_STREQ(str.c_str(), "");
    ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, CopyAssignConstructor2) {
    bmstu::string str("str");
    bmstu::string str2(bmstu::string("other"));
    str2 = std::move(str);
    ASSERT_STREQ(str2.c_str(), "str");
    ASSERT_EQ(str2.size(), sizeof("str") - 1);

    ASSERT_STREQ(str.c_str(), "");
    ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, MoveAssignConstructorW) {
    bmstu::wstring str2(std::move(bmstu::wstring(L"other")));
    ASSERT_STREQ(str2.c_str(), L"other");
    ASSERT_EQ(str2.size(), (sizeof(L"other") / sizeof(wchar_t)) - 1);
}

TEST(StringTest, CStrCopyAssign) {
    const char *str = "Simple Str";
    bmstu::string b_str;
    b_str = str;
    ASSERT_STREQ(b_str.c_str(), str);
}

TEST(StringTest, CStrCopyAssignW) {
    const wchar_t *str = L"Простая строка";
    bmstu::wstring b_str;
    b_str = str;
    ASSERT_STREQ(b_str.c_str(), str);
}

TEST(StringTest, AssignCStr) {
    bmstu::wstring str(L"123456789");
    ASSERT_STREQ(str.c_str(), L"123456789");
}

TEST(StringTest, ConcatOpW) {
    bmstu::wstring a_str(L"right");
    bmstu::wstring b_str(L"_left");
    auto c_str = a_str + b_str;
    ASSERT_STREQ(c_str.c_str(), L"right_left");
}

TEST(StringTest, ConcatOp) {
    bmstu::string a_str("right");
    bmstu::string b_str("_left");
    auto c_str = a_str + b_str;
    ASSERT_STREQ(c_str.c_str(), "right_left");
}

TEST(StringTest, OStream) {
    bmstu::string a_str("String value");
    std::stringstream ss;
    ss << a_str;
    ASSERT_STREQ(ss.str().c_str(), "String value");
}

TEST(StringTest, OStreamW) {
    bmstu::wstring a_str(L"String значение");
    std::wstringstream ss;
    ss << a_str;
    ASSERT_STREQ(ss.str().c_str(), L"String значение");
}

TEST(StringTest, IStream) {
    std::stringstream ss;
    ss.str("Value of\nstring");
    bmstu::string a_str;
    ss >> a_str;
    ASSERT_STREQ(a_str.c_str(), "Value");
    ss >> a_str;
    ASSERT_STREQ(a_str.c_str(), "of");
}

TEST(StringTest, IStreamW) {
    std::wstringstream ss;
    ss.str(L"Value of\nстрока");
    bmstu::wstring a_str;
    ss >> a_str;
    ASSERT_STREQ(a_str.c_str(), L"Value");
    ss >> a_str;  // Дополнительное чтение для второго слова
    ASSERT_STREQ(a_str.c_str(), L"of");
}

TEST(StringTest, IStreamWNewLine) {
    std::wstringstream ss;
    ss.str(L"Value of\nstring");
    bmstu::wstring a_str;
    ss >> a_str;
    ASSERT_STREQ(ss.str().c_str(), L"Value of\nstring");
}

TEST(StringTest, ConcatSymbol) {
    bmstu::wstring a_str;
    a_str += L'S';
    ASSERT_STREQ(a_str.c_str(), L"S");
    a_str += L'т';
    ASSERT_STREQ(a_str.c_str(), L"Sт");
    a_str += L'р';
    ASSERT_STREQ(a_str.c_str(), L"Sтр");
    ASSERT_EQ(a_str.size(), 3);
}

TEST(StringTest, Item) {
    bmstu::wstring a_str(L"СТРОКААГ");
    ASSERT_EQ(a_str[0], L'С');
    ASSERT_EQ(a_str[1], L'Т');
    ASSERT_EQ(a_str[a_str.size() - 1], L'Г');
}

/// ALL MY TESTS
/*
using namespace bmstu;
 TEST(StringTest, DefaultConstructor) {
     string str;
     ASSERT_STREQ(str.c_str(), "");
     ASSERT_EQ(str.size(), 0);
 }
 TEST(StringTest, CStrConstructor) {
     const char *c_str = "Hello, Ershov!";
     string str(c_str);
     size_t expected_size = 0;
     while (c_str[expected_size] != '\0') {
         expected_size++;
     }
     ASSERT_EQ(str.size(), expected_size);

     for (size_t i = 0; i < expected_size; ++i) {
         ASSERT_EQ(str.c_str()[i], c_str[i]);
     }

     ASSERT_STREQ(str.c_str(), c_str);
 }
 TEST(StringTest, CopyConstructor) {
     const char *original_cstr = "Hello, Ershov!";
     string original(original_cstr);
     string copy(original);

     ASSERT_EQ(copy.size(), original.size());
     ASSERT_STREQ(copy.c_str(), original.c_str());
 }
 TEST(StringTest, MoveConstructor) {
     const char *original_cstr = "Hello, World!";
     string original(original_cstr);
     string moved(std::move(original));

     ASSERT_EQ(original.size(), 0);

     // Проверяем, что копия содержит те же данные, что и исходный объект
     ASSERT_EQ(moved.size(), strlen(original_cstr));
     ASSERT_STREQ(moved.c_str(), original_cstr);
 }
 TEST(StringTest, CStrGetter){
     string str("Ershov");
     ASSERT_STREQ(str.c_str(), "Ershov");
 }
 TEST(StringTest, SizeGetter){
     string str("Ershov");
     EXPECT_EQ(str.size(), 6);
 }
 TEST(StringTest, CopyAssignmentOperator) {
     const char *original_cstr = "Hello, Ershov!";
     string original(original_cstr);
     const char *other_cstr = "Hello, Vandyshev!";
     string other(other_cstr);
     // Присваиваем значения с использованием оператора копирующего присваивания
     other = original;
     EXPECT_EQ(other.size(), original.size());
     EXPECT_STREQ(other.c_str(), original.c_str());
 }
 TEST(StringTest, MoveAssignmentOperator) {
     const char *original_cstr = "Hello, Ershov!";
     string original(original_cstr);
     const char *other_cstr = "Hello, Vandyshev!";
     string other(other_cstr);
     // Присваиваем значения с использованием оператора копирующего присваивания
     other = std::move(original);
     EXPECT_EQ(other.size(), strlen(original_cstr));
     EXPECT_EQ(original.size(), 0);
 }
 TEST(StringTest, AssignmentOperatorWithCString) {
     string str;
     const char *c_str = "Hello, Ershov!";
     str = c_str;
     // Проверяем, что размер и содержимое строки совпадают с C-строкой
     EXPECT_EQ(str.size(), strlen(c_str));
     EXPECT_STREQ(str.c_str(), c_str);
 }
 TEST(StringTest, ConcatenationOperator) {
     string str1("Hello, ");
     string str2("Ershov!");
     string result = str1 + str2;
     const char *expected_result_cstr = "Hello, Ershov!";
     EXPECT_EQ(result.size(), strlen(expected_result_cstr));
     EXPECT_STREQ(result.c_str(), expected_result_cstr);
 }
 TEST(StringTest, IndexOperator){

     string str("Ershov");
     // Проверяем доступ к символам по индексу
     EXPECT_EQ(str[0], 'E');
     EXPECT_EQ(str[1], 'r');
     EXPECT_EQ(str[2], 's');
     EXPECT_EQ(str[3], 'h');
     EXPECT_EQ(str[4], 'o');
     EXPECT_EQ(str[5], 'v');

     // Попытка доступа за пределы строки
     EXPECT_EQ(str[10], '\0'); // Должен вернуть нулевой символ
     EXPECT_EQ(str[25], '\0'); // Должен вернуть нулевой символ
 }
 TEST(StringTest, OutputOperator){
     string str("Hello, Ershov!");
     // Создаем поток для записи вывода
     std::stringstream ss;
     ss << str;
     // Проверяем, что содержимое потока соответствует ожидаемой строке
     const std::string expected_output = "Hello, Ershov!";
     EXPECT_EQ(ss.str(), expected_output);
 }
 TEST(OtherTest, ConcatenationOperator) {
     string str1("Hello, ");
     string str2("Ershov!");
     str1 += str2;
     const char *expected_result_cstr = "Hello, Ershov!";
     EXPECT_EQ(str1.size(), strlen(expected_result_cstr));
     EXPECT_STREQ(str1.c_str(), expected_result_cstr);
 }
 TEST(OtherTest, CharAdditionOperator) {
     string str("Ershov");
     str += '!';
     const char *expected_result_cstr = "Ershov!";
     EXPECT_EQ(str.size(), strlen(expected_result_cstr));
     EXPECT_STREQ(str.c_str(), expected_result_cstr);
 }
 TEST(StringTest, InputOperator) {
     string str;
     std::istringstream input_stream("Hello World!");
     input_stream >> str;
     const char *expected_result_cstr = "Hello";
     EXPECT_EQ(str.size(), strlen(expected_result_cstr));
     EXPECT_STREQ(str.c_str(), expected_result_cstr);
 }
*/


