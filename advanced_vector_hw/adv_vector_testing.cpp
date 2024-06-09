#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

#include "advanced_vector.h"

struct nocopyconstructed {
    explicit nocopyconstructed(size_t value_) : value(value_) {}
    nocopyconstructed() = delete;
    ~nocopyconstructed() = default;
    nocopyconstructed(nocopyconstructed &other) = delete;  // NOLINT

    /// move constructor is default
    nocopyconstructed &operator=(const nocopyconstructed &other) = default;
    nocopyconstructed &operator=(nocopyconstructed &&other) = default;

    friend bool operator==(nocopyconstructed right, nocopyconstructed left) {
        return left.value == right.value;
    }
    [[nodiscard]] size_t getvalue() const noexcept {
        return value;
    }
    size_t value;
};

struct nomoveconstructed {
    explicit nomoveconstructed(size_t value_) : value(value_) {}
    nomoveconstructed() = delete;
    ~nomoveconstructed() = default;

    nomoveconstructed(nomoveconstructed &other) = default; // NOLINT
    nomoveconstructed &operator=(const nomoveconstructed &other) = delete;
    nomoveconstructed &operator=(nomoveconstructed &&other) = delete;

    friend bool operator==(nomoveconstructed right, nomoveconstructed left) {
        return left.value == right.value;
    }

    [[nodiscard]] size_t getvalue() const noexcept {
        return value;
    }

    size_t value;
};

template <typename Type>
void element_checking(bmstu::advanced_vector<Type> &curr, const Type &value = Type{}) { //NOLINT
    for (size_t index = 0; index < curr.size(); ++index) {
        ASSERT_EQ(curr[index], value);
    }
}

// Without any Default Constructor
struct nodefaultconstructed {
    size_t value;
    explicit nodefaultconstructed(size_t value) : value(value) {}

    nodefaultconstructed() = delete;

    friend bool operator==(nodefaultconstructed left, nodefaultconstructed right) {
        return left.value == right.value;
    }

    ~nodefaultconstructed() = default;
    [[nodiscard]] size_t getvalue() const noexcept {
        return value;
    }
};

TEST(DefaultConstructor, WithoutDefaultConstruct) {
    bmstu::advanced_vector<nodefaultconstructed> vec;
    ASSERT_TRUE(vec.empty());
    ASSERT_EQ(vec.capacity(), 0);
}

TEST(DefaultConstructor, WSTRINGS) {
    bmstu::advanced_vector<std::wstring> vec;
    ASSERT_TRUE(vec.empty());
    ASSERT_EQ(vec.capacity(), 0);
}

TEST(ParamConstuctor, WithoutDefaultConstruct) {
    bmstu::advanced_vector<nodefaultconstructed> vec(10);
    ASSERT_EQ(vec.size(), 10);
}

TEST(ParamConstructor, INTEGER) {
    bmstu::advanced_vector<int> vec(10);
    ASSERT_EQ(vec.size(), 10);
    element_checking(vec, 0);
}

TEST(ParamConstructor, WSTRING) {
    bmstu::advanced_vector<std::wstring> vec(10);
    ASSERT_EQ(vec.size(), 10);
    for (size_t index = 0; index < vec.size(); ++index) {
        ASSERT_EQ(vec[index], L"");
    }
}

TEST(InitializerListConstruct, INTEGER) {
    bmstu::advanced_vector<int> ilist{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t index = 0; index < ilist.size(); ++index) {
        ASSERT_EQ(ilist[index], index + 1);
    }
}

TEST(InitializerListConstruct, WSTRINGS) {
    using namespace std::literals; // NOLINT
    bmstu::advanced_vector<std::wstring> juggernaut{L"Сундук для рун"s, L"рундук!"s};
    ASSERT_EQ(juggernaut[0], L"Сундук для рун"s);
    ASSERT_EQ(juggernaut[1], L"рундук!"s);
}

TEST(CopyConstruct, INTEGER) {
    bmstu::advanced_vector<int> vec{2, 2, 8, 8, 8};
    bmstu::advanced_vector<int> copied(vec);
    ASSERT_TRUE(vec == copied);
}

TEST(CopyConstruct, WSTRING) {
    bmstu::advanced_vector<std::wstring> naga_siren{L"Мои ноги!", L"Я не чувствую своих ног."};
    bmstu::advanced_vector<std::wstring> copied_replica = naga_siren;
    ASSERT_TRUE(naga_siren == copied_replica);
}

TEST(MoveConstructor, Integer) {
    bmstu::advanced_vector<int> vec{1, 1, 1, 1, 1};
    bmstu::advanced_vector<int> moved(std::move(vec));
    ASSERT_EQ(moved.size(), 5);
    element_checking(moved, 1);
}

TEST(MoveConstructor, string) {
    bmstu::advanced_vector<std::wstring> runduk{L"Рундук", L"Рундук", L"Рундук",
                                                L"Рундук", L"Рундук"};
    bmstu::advanced_vector<std::wstring> moved(std::move(runduk));
    std::wstring runduk_str = L"Рундук";
    ASSERT_EQ(runduk_str, runduk_str);
    element_checking(moved, runduk_str);
}

TEST(CopyAssignment, INTEGER) {
    bmstu::advanced_vector<int> numbers{1, 2, 3, 4, 5};
    bmstu::advanced_vector<int> copied = numbers;
    ASSERT_TRUE(numbers == copied);
}

TEST(CopyAssignment, WSTRING) {
    bmstu::advanced_vector<std::wstring> naga_siren{L"Мои ноги!", L"Я не чувствую своих ног."};
    bmstu::advanced_vector<std::wstring> copied = naga_siren;
    ASSERT_TRUE(naga_siren == copied);
}

TEST(MoveAssignment, INTEGER) {
    bmstu::advanced_vector<int> vec{1, 1, 1, 1, 1};
    bmstu::advanced_vector<int> move = std::move(vec);
    ASSERT_EQ(move.size(), 5);
    element_checking(move, 1);
}

TEST(MoveAssignment, WSTRING) {
    bmstu::advanced_vector<std::wstring> runduk{L"Рундук", L"Рундук", L"Рундук",
                                                L"Рундук", L"Рундук"};
    bmstu::advanced_vector<std::wstring> moved = std::move(runduk);
    ASSERT_EQ(moved.size(), 5);
    for (size_t i = 0; i < moved.size(); ++i) {
        ASSERT_EQ(moved[i], L"Рундук");
    }
}

TEST(Reserve, INTEGER) {
    bmstu::advanced_vector<int> vec{6, 6,6};
    vec.reserve(10);
    ASSERT_EQ(vec.size(), 3);
    ASSERT_EQ(vec.capacity(), 10);
    element_checking(vec, 6);
    vec.reserve(2);
    ASSERT_EQ(vec.size(), 3);
    element_checking(vec, 6);
}

TEST(Reserve, WSTRING) {
    bmstu::advanced_vector<std::wstring> runduk{L"Рундук", L"Нетворс", L"Тараска"};
    runduk.reserve(11);
    ASSERT_EQ(runduk.size(), 3);
    ASSERT_EQ(runduk.capacity(), 11);
    ASSERT_EQ(runduk[0], L"Рундук");
    ASSERT_EQ(runduk[1], L"Нетворс");
    ASSERT_EQ(runduk[2], L"Тараска");
    runduk.reserve(2);
    ASSERT_EQ(runduk.size(), 3);
    ASSERT_EQ(runduk.capacity(), 11);
    ASSERT_EQ(runduk[0], L"Рундук");
    ASSERT_EQ(runduk[1], L"Нетворс");
    ASSERT_EQ(runduk[2], L"Тараска");
}

TEST(Resize, INTEGER) {
    bmstu::advanced_vector<int> vec{322, 322, 322, 322, 322};
    vec.resize(1);
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec.capacity(), 5);
    ASSERT_EQ(vec[0], 322);
    element_checking(vec, 322);
    vec.resize(11);
    ASSERT_EQ(vec.size(), 11);
    ASSERT_EQ(vec.capacity(), 11);
    ASSERT_EQ(vec[0], 322);
    for (size_t index = 1; index < vec.size(); ++index) {
        ASSERT_EQ(vec[index], 0);
    }
}

TEST(Resize, WithoutDefaultConstruct) {
    bmstu::advanced_vector<nodefaultconstructed> vec{nodefaultconstructed(1), nodefaultconstructed(2)};
    vec.resize(3);
    ASSERT_EQ(vec.size(), 3);
    ASSERT_GE(vec.capacity(), 2);
    ASSERT_EQ(vec[0].getvalue(), 1);
    ASSERT_EQ(vec[1].getvalue(), 2);
    ASSERT_EQ(vec[2].getvalue(), 0);
    vec.resize(1);
    ASSERT_EQ(vec.size(), 1);
    // Capacity may still be larger than the size
    ASSERT_GE(vec.capacity(), 1);
    ASSERT_EQ(vec[0].getvalue(), 1);
}

TEST(PopBack, INTEGER) {
    bmstu::advanced_vector<int> vec{322, 322, 322};
    vec.pop_back();
    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec.capacity(), 3);
    element_checking(vec, 322);
}

TEST(PopBack, WSTRING) {
    bmstu::advanced_vector<std::wstring> heroes_dota{L"Monkey King", L"Primal Beast", L"Abaddon"};
    heroes_dota.pop_back();
    ASSERT_EQ(heroes_dota.size(), 2);
    ASSERT_EQ(heroes_dota.capacity(), 3);
    ASSERT_EQ(heroes_dota[0], L"Monkey King");
    ASSERT_EQ(heroes_dota[1], L"Primal Beast");
    // ASSERT_EQ(heroes_dota[2], L"Abaddon");
}

TEST(PushBack, WithoutDefaultConstruct) {
    bmstu::advanced_vector<nodefaultconstructed> vec{nodefaultconstructed(1), nodefaultconstructed(2),
                                                     nodefaultconstructed(3), nodefaultconstructed(4),
                                                     nodefaultconstructed(5)};
    vec.push_back(nodefaultconstructed(2));
    ASSERT_EQ(vec[5].getvalue(), 2);
}

TEST(PushBack, INTEGER) {
    bmstu::advanced_vector<int> vec{322, 322, 322};
    vec.push_back(322);
    ASSERT_EQ(vec[3], 322);
}

TEST(PushBack, Strings) {
    bmstu::advanced_vector<std::wstring> bad{L"Как", L"теперь", L"играть", L"на"};
    bad.push_back(L"тинкере");
    ASSERT_EQ(bad[4], L"тинкере");
}

TEST(Insert, INTEGER) {
    bmstu::advanced_vector<int> numbers{2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    numbers.insert(numbers.begin() + 3, 4);
    numbers.insert(numbers.end(), 2);
    ASSERT_EQ(numbers[3], 4);
    ASSERT_EQ(numbers[numbers.size() - 1], 2);
}

TEST(Insert, WSTRING) {
    bmstu::advanced_vector<std::wstring> vec{L"Как", L"теперь", L"играть", L"на"};
    vec.insert(vec.begin() + 1, L"вдота");
    vec.insert(vec.end(), L"тинкере?!!");
    ASSERT_EQ(vec[1], L"вдота");
    ASSERT_EQ(vec[vec.size() - 1], L"тинкере?!!");
}

TEST(Insert, WithoutDefaultConstruct) {
    bmstu::advanced_vector<nodefaultconstructed> vec{nodefaultconstructed(1), nodefaultconstructed(2)};
    vec.insert(vec.begin() + 1, nodefaultconstructed(3));
    ASSERT_EQ(vec[1].getvalue(), 3);
}

TEST(Equal, WithoutDefaultConstruct) {
    bmstu::advanced_vector<nodefaultconstructed> vec{nodefaultconstructed(1), nodefaultconstructed(2)};
    bmstu::advanced_vector<nodefaultconstructed> vec2{nodefaultconstructed(1), nodefaultconstructed(2)};
    ASSERT_TRUE(vec == vec2);
}

TEST(Equal, INTEGER) {
    bmstu::advanced_vector<int> vec{1, 2};
    bmstu::advanced_vector<int> vec2{1, 2};
    ASSERT_TRUE(vec == vec2);
}

TEST(Equal, WSTRING) {
    bmstu::advanced_vector<std::wstring> vec{L"Я", L"ничего", L"не", L"понимаю"};
    bmstu::advanced_vector<std::wstring> vec2{L"Я", L"ничего", L"не", L"понимаю"};
    ASSERT_TRUE(vec == vec2);
}

TEST(NotEqual, WithoutDefaultConstruct) {
    bmstu::advanced_vector<nodefaultconstructed> vec{nodefaultconstructed(1), nodefaultconstructed(2)};
    bmstu::advanced_vector<nodefaultconstructed> vec2{nodefaultconstructed(1), nodefaultconstructed(2)};
    ASSERT_FALSE(vec != vec2);
}

TEST(NotEqual, INTEGER) {
    bmstu::advanced_vector<int> vec{1, 2};
    bmstu::advanced_vector<int> vec2{1, 2};
    ASSERT_FALSE(vec != vec2);
}

TEST(NotEqual, WSTRING) {
    bmstu::advanced_vector<std::wstring> vec{L"Linus", L"Torvalds"};
    bmstu::advanced_vector<std::wstring> vec2{L"Linus", L"Torvalds"};
    ASSERT_FALSE(vec != vec2);
}

TEST(Output, INTEGER) {
    bmstu::advanced_vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    testing::internal::CaptureStdout();
    std::cout << vec;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("[1, 2, 3, 4, 5, 6, 7, 8, 9]", output);
}

TEST(Output, STRING) {
    bmstu::advanced_vector<std::string> vec{"All done, sir"};
    bmstu::advanced_vector<std::string> vec2{"All done, sir"};
    testing::internal::CaptureStdout();
    std::cout << vec;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("[All done, sir]", output);
}