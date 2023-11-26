#include <gtest/gtest.h>
#include <vector>
#include "array_bundle.h"
#include "vector_template.h"
#include <numeric>
#include <functional>

TEST(Constructor, Default) {
    bmstu::dummy_vector<int> my_vec;
    ASSERT_EQ(my_vec.size(), 0);
    ASSERT_EQ(my_vec.capacity(), 0);
}

TEST(Constructor, InList) {
    bmstu::dummy_vector my_vec({0, 1, 2});
    ASSERT_EQ(my_vec.size(), 3);
    ASSERT_EQ(my_vec.capacity(), 3);
    for (size_t i = 0; i < my_vec.size(); ++i) {
        ASSERT_EQ(my_vec[i], i);
        ASSERT_EQ(my_vec.at(i), i);
    }
}

TEST(Constructor, Parametr) {
    bmstu::dummy_vector my_vec(4, 20);
    ASSERT_EQ(my_vec.size(), 4);
    ASSERT_EQ(my_vec.capacity(), 4);
    for (size_t i = 0; i < my_vec.size(); ++i) {
        ASSERT_EQ(my_vec[i], 20);
        ASSERT_EQ(my_vec.at(i), 20);

    }
}

TEST(Constructor, Copy) {
    bmstu::dummy_vector my_vec1(4, 20);
    bmstu::dummy_vector my_vec2(my_vec1);
    ASSERT_EQ(my_vec1.size(), 4);
    ASSERT_EQ(my_vec1.capacity(), 4);
    ASSERT_EQ(my_vec2.size(), my_vec1.size());
    ASSERT_EQ(my_vec2.capacity(), my_vec1.capacity());
    for (size_t i = 0; i < my_vec1.size(); ++i) {
        ASSERT_EQ(my_vec1[i], 20);
        ASSERT_EQ(my_vec1.at(i), 20);
        ASSERT_EQ(my_vec2[i], 20);
        ASSERT_EQ(my_vec2.at(i), 20);
    }
}

TEST(Constructor, Move) {
    bmstu::dummy_vector my_vec1(4, 20);
    bmstu::dummy_vector my_vec2(std::move(my_vec1));
    ASSERT_EQ(my_vec1.size(), 0);
    ASSERT_EQ(my_vec1.capacity(), 0);
    ASSERT_EQ(my_vec2.size(), 4);
    ASSERT_EQ(my_vec2.capacity(), 4);
    for (size_t i = 0; i < my_vec1.size(); ++i) {
        ASSERT_EQ(my_vec2[i], 20);
        ASSERT_EQ(my_vec2.at(i), 20);
    }
}

TEST(Operator, Copy) {
    bmstu::dummy_vector my_vec1(4, 20);
    bmstu::dummy_vector my_vec2 = my_vec1;
    ASSERT_EQ(my_vec1.size(), 4);
    ASSERT_EQ(my_vec1.capacity(), 4);
    ASSERT_EQ(my_vec2.size(), my_vec1.size());
    ASSERT_EQ(my_vec2.capacity(), my_vec1.capacity());
    for (size_t i = 0; i < my_vec1.size(); ++i) {
        ASSERT_EQ(my_vec1[i], 20);
        ASSERT_EQ(my_vec1.at(i), 20);
        ASSERT_EQ(my_vec2[i], 20);
        ASSERT_EQ(my_vec2.at(i), 20);
    }
}

TEST(Operator, Move) {
    bmstu::dummy_vector my_vec1(4, 20);
    bmstu::dummy_vector my_vec2 = std::move(my_vec1);
    ASSERT_EQ(my_vec1.size(), 0);
    ASSERT_EQ(my_vec1.capacity(), 0);
    ASSERT_EQ(my_vec2.size(), 4);
    ASSERT_EQ(my_vec2.capacity(), 4);
    for (size_t i = 0; i < my_vec1.size(); ++i) {
        ASSERT_EQ(my_vec2[i], 20);
        ASSERT_EQ(my_vec2.at(i), 20);
    }
}

TEST(Iterator, BeginAndEnd) {
    bmstu::dummy_vector my_vec({0, 1, 2, 3, 4, 5});
    bmstu::dummy_vector<int>::iterator itb = my_vec.begin();
    bmstu::dummy_vector<int>::iterator ite = my_vec.end();
    size_t n = 0;
    for (;itb != ite; ++itb) {
        ASSERT_EQ(*itb, n);
        n+=1;
    }
}

TEST(Method, Empty) {
    bmstu::dummy_vector<int> my_vec1;
    bmstu::dummy_vector my_vec2({1, 2, 3});
    ASSERT_TRUE(my_vec1.empty());
    ASSERT_FALSE(my_vec2.empty());
}

TEST(Method, clear) {
    bmstu::dummy_vector my_vec({1, 2, 3});
    my_vec.clear();
    ASSERT_EQ(my_vec.size(),0);
    ASSERT_EQ(my_vec.capacity(),3);
}

TEST(Method, SwapV1) {
    bmstu::dummy_vector my_vec1(4, 20);
    bmstu::dummy_vector my_vec2(13, 3);
    my_vec1.swap(my_vec2);
    ASSERT_EQ(my_vec1.size(), 13);
    ASSERT_EQ(my_vec1.capacity(), 13);
    ASSERT_EQ(my_vec2.size(), 4);
    ASSERT_EQ(my_vec2.capacity(), 4);
    for (size_t i = 0; i < my_vec1.size(); ++i) {
        ASSERT_EQ(my_vec1[i], 3);
    }
    for (size_t i = 0; i < my_vec2.size(); ++i) {
        ASSERT_EQ(my_vec2[i], 20);
    }
}

TEST(Method, SwapV2) {
    bmstu::dummy_vector my_vec1(4, 20);
    bmstu::dummy_vector my_vec2(13, 3);
    swap(my_vec1, my_vec2);
    ASSERT_EQ(my_vec1.size(), 13);
    ASSERT_EQ(my_vec1.capacity(), 13);
    ASSERT_EQ(my_vec2.size(), 4);
    ASSERT_EQ(my_vec2.capacity(), 4);
    for (size_t i = 0; i < my_vec1.size(); ++i) {
        ASSERT_EQ(my_vec1[i], 3);
    }
    for (size_t i = 0; i < my_vec2.size(); ++i) {
        ASSERT_EQ(my_vec2[i], 20);
    }
}

TEST(Method, resize) {
    bmstu::dummy_vector my_vec(5, 20);
    my_vec.resize(4);
    ASSERT_EQ(my_vec.size(), 4);
    ASSERT_EQ(my_vec.capacity(), 5);

    my_vec.resize(7);
    ASSERT_EQ(my_vec.size(), 7);
    ASSERT_EQ(my_vec.capacity(), 10);

    my_vec.resize(21);
    ASSERT_EQ(my_vec.size(), 21);
    ASSERT_EQ(my_vec.capacity(), 21);
}

TEST(Method, reserve){
    bmstu::dummy_vector my_vec(5, 20);
    my_vec.reserve(21);
    ASSERT_EQ(my_vec.size(), 5);
    ASSERT_EQ(my_vec.capacity(), 21);
}

TEST(Method, Insert){
    bmstu::dummy_vector my_vec = {0, 1, 2, 4, 5, 6};
    bmstu::dummy_vector<int>::iterator it = my_vec.begin() + 3;
    my_vec.insert(it,3);
    ASSERT_EQ(my_vec.size(), 7);
    ASSERT_EQ(my_vec.capacity(), 12);
    for (size_t i = 0; i < my_vec.size(); ++i) {
        ASSERT_EQ(my_vec[i], i);
    }
}

TEST(Method, Push_Pop_back){
    bmstu::dummy_vector my_vec = {0, 1, 2, 3, 4, 5, 6};
    my_vec.push_back(7);
    ASSERT_EQ(my_vec.size(), 8);
    ASSERT_EQ(my_vec.capacity(), 14);
    for (size_t i = 0; i < my_vec.size(); ++i) {
        ASSERT_EQ(my_vec[i], i);
    }
    my_vec.pop_back();
    ASSERT_EQ(my_vec.size(), 7);
    ASSERT_EQ(my_vec.capacity(), 14);
    for (size_t i = 0; i < my_vec.size(); ++i) {
        ASSERT_EQ(my_vec[i], i);
    }
}

TEST(Operator, EQs){
    bmstu::dummy_vector my_vec1 = {0, 1, 2, 3, 4, 5, 6};
    bmstu::dummy_vector my_vec2 = {0, 1, 2, 3, 4, 5, 6};
    bmstu::dummy_vector my_vec3 = {0, 1, 2, 3, 4, 5, 7};
    bmstu::dummy_vector my_vec4 = {1, 2, 3, 4, 5, 7, 8};
    bmstu::dummy_vector my_vec5 = {1, 1, 2, 3, 4, 5, 7};
    ASSERT_TRUE(my_vec1 == my_vec2);
    ASSERT_FALSE(my_vec1 == my_vec3);
    ASSERT_TRUE(my_vec1 != my_vec3);
    ASSERT_FALSE(my_vec1 != my_vec2);
    ASSERT_TRUE(my_vec1 < my_vec4);
    ASSERT_TRUE(my_vec4 > my_vec1);
    ASSERT_TRUE(my_vec1 <= my_vec5);
    ASSERT_TRUE(my_vec5 >= my_vec1);
}

TEST(DummyVector, one) {
    bmstu::dummy_vector<int> v;
    ASSERT_EQ(v.size(), 0u);
    ASSERT_TRUE(v.empty());
    ASSERT_EQ(v.capacity(), 0u);
}
//
//
TEST(DummyVector, Init) {
    // Инициализация вектора указанного размера
    bmstu::dummy_vector<int> v(5);
    ASSERT_EQ(v.size(), 5u);
    ASSERT_EQ(v.capacity(), 5u);
    ASSERT_TRUE(!v.empty());
    for (size_t i = 0; i < v.size(); ++i) {
        ASSERT_EQ(v[i], 0);
    }
}

TEST(DummyVector, Init2) {
    bmstu::dummy_vector<int> v(3, 42);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v.capacity(), 3);
    for (size_t i = 0; i < v.size(); ++i) {
        ASSERT_EQ(v[i], 42);
    }
}
//
TEST(DummyVector, InitList) {
    bmstu::dummy_vector<int> v{1, 2, 3};
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v.capacity(), 3);
    ASSERT_EQ(v[2], 3);
}
//
TEST(DummyVector, At) {
    bmstu::dummy_vector<int> v(3);
    ASSERT_EQ(&v.at(2), &v[2]);
    try {
        v.at(3);
    } catch (std::out_of_range const &err) {
        EXPECT_EQ(err.what(), std::string("Invalid index"));
    }
}
//
TEST(DummyVector, Clear) {

    bmstu::dummy_vector<int> v(10);
    const size_t old_capacity = v.capacity();
    v.clear();
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), old_capacity);
}
//
TEST(DummyVector, Resize) {
    // Изменение размера
    {
        bmstu::dummy_vector<int> v(3);
        v[2] = 17;
        v.resize(7);
        ASSERT_EQ(v.size(), 7);
        ASSERT_TRUE(v.capacity() >= v.size());
        ASSERT_EQ(v[2], 17);
        ASSERT_EQ(v[3], 0);
    }
}
//
TEST(DummyVector, Resize1) {
    {
        bmstu::dummy_vector<int> v(3);
        v[0] = 42;
        v[1] = 55;
        const size_t old_capacity = v.capacity();
        v.resize(2);
        ASSERT_EQ(v.size(), 2);
        ASSERT_EQ(v.capacity(), old_capacity);
        ASSERT_EQ(v[0], 42);
        ASSERT_EQ(v[1], 55);
    }
}
//
TEST(DummyVector, Resize2) {
    const size_t old_size = 3;
    bmstu::dummy_vector<int> v(3);
    v.resize(old_size + 5);
    v[3] = 42;
    v.resize(old_size);
    ASSERT_EQ(v[2], 0);
    v.resize(old_size + 3);
    ASSERT_EQ(v[3], 0);
}
//
TEST(DummyVector, Constructors) {
    {

        bmstu::dummy_vector<int> v(5);
        v[0] = 1;
        v[1] = 2;
        v[2] = 3;
        v[3] = 4;
        v[4] = 5;
        bmstu::dummy_vector<int> c(v);
        ASSERT_EQ(v[2], v[2]);
    }
    {

        bmstu::dummy_vector<int> v(5);
        v[0] = 1;
        v[1] = 2;
        v[2] = 3;
        v[3] = 4;
        v[4] = 5;
        bmstu::dummy_vector<int> c(v);
        ASSERT_EQ(v[2], v[2]);
    }
    {

        bmstu::dummy_vector<int> v(1);
        v.push_back(1);
        ASSERT_EQ(v[0], 0);
        ASSERT_EQ(*(v.begin()) + 1, 1);
    }
}

TEST(DummyVector, Push) {
    bmstu::dummy_vector<int> v(1);
    v.push_back(42);
    ASSERT_EQ(v.size(), 2);
    ASSERT_TRUE(v.capacity() >= v.size());
    ASSERT_EQ(v[0], 0);
    ASSERT_EQ(v[1], 42);
}

TEST(DummyVector, CopyConstruct)
// Конструктор копирования
{
    bmstu::dummy_vector<int> numbers{1, 2};
    auto numbers_copy(numbers);
    ASSERT_TRUE(&numbers_copy[0] != &numbers[0]);
    ASSERT_EQ(numbers_copy.size(), numbers.size());
    for (size_t i = 0; i < numbers.size(); ++i) {
        ASSERT_EQ(numbers_copy[i], numbers[i]);
        ASSERT_TRUE(&numbers_copy[i] != &numbers[i]);
    }
}

TEST(DummyVector, PopBack) {
    // PopBack
    {
        bmstu::dummy_vector<int> v{0, 1, 2, 3};
        const size_t old_capacity = v.capacity();
        const auto old_begin = v.begin();
        v.pop_back();
        ASSERT_EQ(v.capacity(), old_capacity);
        ASSERT_EQ(v.begin(), old_begin);
        ASSERT_EQ(v, (bmstu::dummy_vector<int>{0, 1, 2}));
    }
}

TEST(DummyVector, Capacity) {

    bmstu::dummy_vector<int> v(2);
    v.resize(1);
    const size_t old_capacity = v.capacity();
    v.push_back(123);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v.capacity(), old_capacity);
}

TEST(DummyVector, Iterate) {
    {
        {
            bmstu::dummy_vector<int> v;
            ASSERT_EQ(v.begin(), nullptr);
            ASSERT_EQ(v.end(), nullptr);
        }

        {
            bmstu::dummy_vector<int> v(10, 42);
            ASSERT_EQ(*v.begin(), 42);
            ASSERT_EQ(v.end(), v.begin() + v.size());
        }
    }
}

TEST(DummyVector, Compare) {
    {
        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} == bmstu::dummy_vector{1, 2, 3}));
        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} != bmstu::dummy_vector{1, 2, 2}));

        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} < bmstu::dummy_vector{1, 2, 3, 1}));
        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} > bmstu::dummy_vector{1, 2, 2, 1}));

        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} >= bmstu::dummy_vector{1, 2, 3}));
        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 4} >= bmstu::dummy_vector{1, 2, 3}));
        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} <= bmstu::dummy_vector{1, 2, 3}));
        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} <= bmstu::dummy_vector{1, 2, 4}));
    }
}

TEST(DummyVector, Pushback2) {
    bmstu::dummy_vector<int> v2;
    v2.push_back(0);
    v2.push_back(1);
    v2.push_back(2);
    ASSERT_EQ(v2, (bmstu::dummy_vector<int>{0, 1, 2}));
}

TEST(DummyVector, Swap) {
    // Обмен значений векторов
    {
        bmstu::dummy_vector<int> v1{42, 666};
        bmstu::dummy_vector<int> v2;
        v2.push_back(0);
        v2.push_back(1);
        v2.push_back(2);
        const int *const begin1 = &v1[0];
        const int *const begin2 = &v2[0];

        const size_t capacity1 = v1.capacity();
        const size_t capacity2 = v2.capacity();

        const size_t size1 = v1.size();
        const size_t size2 = v2.size();

        v1.swap(v2);
        ASSERT_TRUE(&v2[0] == begin1);
        ASSERT_TRUE(&v1[0] == begin2);
        ASSERT_TRUE(v1.size() == size2);
        ASSERT_TRUE(v2.size() == size1);
        ASSERT_TRUE(v1.capacity() == capacity2);
        ASSERT_TRUE(v2.capacity() == capacity1);
    }
}

TEST(DummyVector, Test1) {
    {
        bmstu::dummy_vector<int> src_vector{1, 2, 3, 4};
        bmstu::dummy_vector<int> dst_vector{1, 2, 3, 4, 5, 6};
        dst_vector = src_vector;
        ASSERT_EQ(dst_vector, src_vector);
    }
}

TEST(DummyVector, Insert) {
    {
        bmstu::dummy_vector<int> v{1, 2, 3, 4};
        auto vit = v.begin() + 3;
        v.insert(v.begin() + 2, 42);
        ASSERT_EQ(v, (bmstu::dummy_vector<int>{1, 2, 42, 3, 4}));
    }
}

TEST(DummyVector, Insert2) {
    // Вставка элементов
    bmstu::dummy_vector<int> v;
    v.insert(v.begin(), 42);
    ASSERT_EQ(v, (bmstu::dummy_vector<int>{42}));
}

TEST(DummyVector, Erase) {
    {
        bmstu::dummy_vector<int> v{1, 2, 3, 4};
        v.erase(v.begin() + 2);

        ASSERT_EQ(v, (bmstu::dummy_vector<int>{1, 2, 4}));
    }
}

TEST(DummyVector, Reserve) {

    {
        bmstu::dummy_vector<int> v(5);
        ASSERT_EQ(v.capacity(), 5);
        ASSERT_FALSE(v.empty());
    }

    {
        bmstu::dummy_vector<int> v;
        v.reserve(5);
        ASSERT_EQ(v.capacity(), 5);
        ASSERT_TRUE(v.empty());
        v.reserve(1);
        ASSERT_EQ(v.capacity(), 5);
        for (int i = 0; i < 10; ++i) {
            v.push_back(i);
        }
        ASSERT_EQ(v.size(), 10);
        v.reserve(100);
        ASSERT_EQ(v.size(), 10);
        ASSERT_EQ(v.capacity(), 100);
        for (int i = 0; i < 10; ++i) {
            ASSERT_EQ(v[i], i);
        }
    }
}
