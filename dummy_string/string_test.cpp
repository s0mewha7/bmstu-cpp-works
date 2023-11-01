#include <gtest/gtest.h>
#include "basic_string.h"
#include <string>

// ALL TEST FOR TEMPLATE STRING IMPLEMENTATION

TEST(StringTest, DefaultConstructor) {
    bmstu::string<char> str;
    ASSERT_STREQ(str.c_str(), "");
    ASSERT_EQ(str.size(), 0);
}
TEST(StringTest, CStrConstructor) {
    const char *c_str = "Hello, Ershov!";
    bmstu::string<char> str(c_str);
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
    bmstu::string<char> original(original_cstr);
    bmstu::string<char> copy(original);

    ASSERT_EQ(copy.size(), original.size());
    ASSERT_STREQ(copy.c_str(), original.c_str());
}
TEST(StringTest, MoveConstructor) {
    const char *original_cstr = "Hello, World!";
    bmstu::string<char> original(original_cstr);
    bmstu::string<char> moved(std::move(original));

    ASSERT_EQ(original.size(), 0);

    // Проверяем, что копия содержит те же данные, что и исходный объект
    ASSERT_EQ(moved.size(), strlen(original_cstr));
    ASSERT_STREQ(moved.c_str(), original_cstr);
}
TEST(StringTest, CStrGetter){
    bmstu::string <char> str("Ershov");
    ASSERT_STREQ(str.c_str(), "Ershov");
}
TEST(StringTest, SizeGetter){
    bmstu::string<char> str("Ershov");
    EXPECT_EQ(str.size(), 6);
}
TEST(StringTest, CopyAssignmentOperator) {
    const char *original_cstr = "Hello, Ershov!";
    bmstu::string<char> original(original_cstr);
    const char *other_cstr = "Hello, Vandyshev!";
    bmstu::string<char> other(other_cstr);
    // Присваиваем значения с использованием оператора копирующего присваивания
    other = original;
    EXPECT_EQ(other.size(), original.size());
    EXPECT_STREQ(other.c_str(), original.c_str());
}
TEST(StringTest, MoveAssignmentOperator) {
    const char *original_cstr = "Hello, Ershov!";
    bmstu::string<char> original(original_cstr);
    const char *other_cstr = "Hello, Vandyshev!";
    bmstu::string<char> other(other_cstr);
    // Присваиваем значения с использованием оператора копирующего присваивания
    other = std::move(original);
    EXPECT_EQ(other.size(), strlen(original_cstr));
    EXPECT_EQ(original.size(), 0);
}
TEST(StringTest, AssignmentOperatorWithCString) {
    bmstu::string<char> str;
    const char *c_str = "Hello, Ershov!";
    str = c_str;
    // Проверяем, что размер и содержимое строки совпадают с C-строкой
    EXPECT_EQ(str.size(), strlen(c_str));
    EXPECT_STREQ(str.c_str(), c_str);
}
TEST(StringTest, ConcatenationOperator) {
    bmstu::string<char> str1("Hello, ");
    bmstu::string<char> str2("Ershov!");
    bmstu::string<char> result = str1 + str2;
    const char *expected_result_cstr = "Hello, Ershov!";
    EXPECT_EQ(result.size(), strlen(expected_result_cstr));
    EXPECT_STREQ(result.c_str(), expected_result_cstr);
}
TEST(StringTest, IndexOperator){
    
    bmstu::string<char> str("Ershov");
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
    bmstu::string<char> str("Hello, Ershov!");
    // Создаем поток для записи вывода
    std::stringstream ss;
    ss << str;
    // Проверяем, что содержимое потока соответствует ожидаемой строке
    const std::string expected_output = "Hello, Ershov!";
    EXPECT_EQ(ss.str(), expected_output);
}
TEST(OtherTest, ConcatenationOperator) {
    bmstu::string<char> str1("Hello, ");
    bmstu::string<char> str2("Ershov!");
    str1 += str2;
    const char *expected_result_cstr = "Hello, Ershov!";
    EXPECT_EQ(str1.size(), strlen(expected_result_cstr));
    EXPECT_STREQ(str1.c_str(), expected_result_cstr);
}
TEST(OtherTest, CharAdditionOperator) {
    bmstu::string<char> str("Ershov");
    str += '!';
    const char *expected_result_cstr = "Ershov!";
    EXPECT_EQ(str.size(), strlen(expected_result_cstr));
    EXPECT_STREQ(str.c_str(), expected_result_cstr);
}
TEST(StringTest, InputOperator) {
    bmstu::string<char> str;
    std::istringstream input_stream("Hello World!");
    input_stream >> str;
    const char *expected_result_cstr = "Hello";
    EXPECT_EQ(str.size(), strlen(expected_result_cstr));
    EXPECT_STREQ(str.c_str(), expected_result_cstr);
}


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}