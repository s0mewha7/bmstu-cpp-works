#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "advanced_vector.h"

struct nocopyconstructed {
    explicit nocopyconstructed(size_t value_) : value(value_) {}
    nocopyconstructed() = delete;
    ~nocopyconstructed() = default;
    nocopyconstructed(nocopyconstructed &other) = delete;  /// Copy constructor is not allowed

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

    nomoveconstructed(nomoveconstructed &other) = default; /// copy constructor in allowed
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
void element_checking(bmstu::advanced_vector<Type> &curr, const Type &value = Type{}) {
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
    using namespace std::literals;
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
    bmstu::advanced_vector<std::wstring> naga_siren{L"Мои ноги!", L"Я не чувствую своих ног."};
    naga_siren.reserve(10);
}