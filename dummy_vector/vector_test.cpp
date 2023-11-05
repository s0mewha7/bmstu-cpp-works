#include <gtest/gtest.h>
#include "vector_template.h"
#include "array_bundle.h"
#include <numeric>
#include <functional>

/// ALL  TESTS FOR DUMMY_STRING

TEST(VectorСonstructor, Default){
    bmstu::vector<int> vct;
    ASSERT_EQ(vct.size(), 0);
    ASSERT_EQ(vct.capacity(), 0);
}

TEST(VectorConstructor, InList){
    bmstu::vector vct({0,1,2});
    ASSERT_EQ(vct.size(), 3);
    ASSERT_EQ(vct.capacity(), 3);

    for(std::size_t i = 0; i < vct.size(); ++ i){
        ASSERT_EQ(vct[i] , i);
        ASSERT_EQ(vct.at(i) , i);
    }
}

TEST(VectorConstructor, Parametr){
    bmstu::vector vct(5, 42);
    ASSERT_EQ(vct.size(), 5);
    ASSERT_EQ(vct.capacity(), 5);

    for(std::size_t i = 0; i < vct.size(); ++i){
        ASSERT_EQ(vct[i] , 42);
        ASSERT_EQ(vct.at(i) , 42);
    }
}

TEST(VectorConstructor, Copy){
    bmstu::vector my_vct1(5, 42);
    bmstu::vector my_vct2(my_vct1);
    ASSERT_EQ(my_vct1.size(), 5);
    ASSERT_EQ(my_vct1.capacity(), 5);
    ASSERT_EQ(my_vct2.size(), my_vct1.size());
    ASSERT_EQ(my_vct2.capacity(), my_vct1.capacity());

    for(std::size_t i = 0; i < my_vct1.size(); ++i){
        ASSERT_EQ(my_vct1[i] , 42);
        ASSERT_EQ(my_vct1.at(i), 42);
        ASSERT_EQ(my_vct2[i] , 42);
        ASSERT_EQ(my_vct2.at(i), 42);
    }
}

TEST(VectorConsturctor, Move){
    bmstu::vector my_vct1(5, 42);
    bmstu::vector my_vct2(std::move(my_vct1));
    ASSERT_EQ(my_vct1.size(), 0);
    ASSERT_EQ(my_vct1.capacity(),  0);
    ASSERT_EQ(my_vct2.size(), 5);
    ASSERT_EQ(my_vct2.capacity(),  5);

    for(std::size_t i = 0; i < my_vct1.size(); ++ i){
        ASSERT_EQ(my_vct2[i] , 42);
        ASSERT_EQ(my_vct2.at(i), 42);
    }
}

TEST(VectorOperator, Copy){
    bmstu::vector my_vct1(5, 42);
    bmstu::vector my_vct2 = my_vct1;
    ASSERT_EQ(my_vct1.size(), 5);
    ASSERT_EQ(my_vct1.capacity(), 5);
    ASSERT_EQ(my_vct2.size(), my_vct1.size());
    ASSERT_EQ(my_vct2.capacity(), my_vct1.capacity());

    for(std::size_t i = 0; i < my_vct1.size(); ++i){
        ASSERT_EQ(my_vct1[i] , 42);
        ASSERT_EQ(my_vct1.at(i), 42);
        ASSERT_EQ(my_vct2[i] , 42);
        ASSERT_EQ(my_vct2.at(i), 42);
    }
}

TEST(VectorOperator, Move){
    bmstu::vector my_vct1(5, 42);
    bmstu::vector my_vct2 = std::move(my_vct1);
    ASSERT_EQ(my_vct1.size(), 0);
    ASSERT_EQ(my_vct1.capacity(), 0);
    ASSERT_EQ(my_vct2.size(), 5);
    ASSERT_EQ(my_vct2.capacity(), 5);

    for(std::size_t i = 0; i < my_vct1.size(); ++i){
        ASSERT_EQ(my_vct2[i] , 42);
        ASSERT_EQ(my_vct2.at(i), 42);
    }
}

TEST(VectorIterator, BeginEnd){
    std::size_t number = 0;
    bmstu::vector vct({0, 1, 2, 3, 4, 5});
    bmstu::vector<int>::iterator itbegin = vct.begin();
    bmstu::vector<int>::iterator itend = vct.end();

    for(;itbegin != itend; ++itbegin){
        ASSERT_EQ(*itbegin, number);
        number++;
    }
}

TEST(VectorMethod, Empty){
    bmstu::vector<int> vct;
    bmstu::vector vct2({2,4,6});
    ASSERT_TRUE(vct.empty());
    ASSERT_FALSE(vct2.empty());
}

TEST(VectorMethod, Clear){
    bmstu::vector my_vector({2,4,6});
    my_vector.clear();
    ASSERT_EQ(my_vector.size(), 0);
    ASSERT_EQ(my_vector.capacity(), 3);
}

TEST(VectorMethod, Swap){
    bmstu::vector my_vct1(5, 42);
    bmstu::vector my_vct2(4 , 21);
    swap(my_vct1, my_vct2);
    ASSERT_EQ(my_vct1.size(), 4);
    ASSERT_EQ(my_vct1.capacity(), 4);
    ASSERT_EQ(my_vct2.size(), 5);
    ASSERT_EQ(my_vct2.capacity(), 5);

    for(std::size_t i = 0; i < my_vct1.size(); ++i){
        ASSERT_EQ(my_vct1[i], 21);
    }
    for(std::size_t i = 0; i < my_vct2.size(); ++i){
        ASSERT_EQ(my_vct2[i], 42);
    }
}

TEST(VectorMethod, SwapV2){
    bmstu::vector my_vct1(5, 42);
    bmstu::vector my_vct2(4 , 21);
    swap(my_vct1, my_vct2);
    ASSERT_EQ(my_vct1.size(), 4);
    ASSERT_EQ(my_vct1.capacity(), 4);
    ASSERT_EQ(my_vct2.size(), 5);
    ASSERT_EQ(my_vct2.capacity(), 5);

    for(std::size_t i = 0; i < my_vct1.size(); ++i){
        ASSERT_EQ(my_vct1[i], 21);
    }
    for(std::size_t i = 0; i < my_vct2.size(); ++i){
        ASSERT_EQ(my_vct2[i], 42);
    }
}

TEST(VectorMethod, Resize){
    bmstu::vector my_vct(5, 20);
    my_vct.resize(4);
    ASSERT_EQ(my_vct.size(), 4);
    ASSERT_EQ(my_vct.capacity(), 5);

    my_vct.resize(7);
    ASSERT_EQ(my_vct.size(), 7);
    ASSERT_EQ(my_vct.capacity(), 7);

    my_vct.resize(21);
    ASSERT_EQ(my_vct.size(), 21);
    ASSERT_EQ(my_vct.capacity(), 21);
}

TEST(VectorMethod, Reserve){
    bmstu::vector my_vct(5, 20);
    my_vct.reserve(21);
    ASSERT_EQ(my_vct.size() , 5);
    ASSERT_EQ(my_vct.capacity() , 21);
}

TEST(VectorMethod, Insert){
    bmstu::vector my_vec = {0, 1, 2, 4, 5, 6};
    bmstu::vector<int>::iterator it = my_vec.begin() + 3;
    my_vec.insert(it,3);
    ASSERT_EQ(my_vec.size(), 7);
    ASSERT_EQ(my_vec.capacity(), 12);
    for (size_t i = 0; i < my_vec.size(); ++i) {
        ASSERT_EQ(my_vec[i], i);
    }
}

TEST(VectorMethod, Push_back){
    bmstu::vector my_vec = {0, 1, 2, 3, 4, 5, 6};
    my_vec.push_back(7);
    ASSERT_EQ(my_vec.size(), 8);
    ASSERT_EQ(my_vec.capacity(), 14);
    for (size_t i = 0; i < my_vec.size(); ++i) {
        ASSERT_EQ(my_vec[i], i);
    }
}

TEST(VectorMethod, Pop_back){
    bmstu::vector my_vec = {0, 1, 2, 3, 4, 5, 6};
    my_vec.pop_back();
    ASSERT_EQ(my_vec.size(), 6);
    ASSERT_EQ(my_vec.capacity(), 7);
    for (size_t i = 0; i < my_vec.size(); ++i) {
        ASSERT_EQ(my_vec[i], i);
    }
}

TEST(Operator, All_EQs){
    bmstu::vector my_vec1 = {0, 1, 2, 3, 4, 5, 6};
    bmstu::vector my_vec2 = {0, 1, 2, 3, 4, 5, 6};
    bmstu::vector my_vec3 = {0, 1, 2, 3, 4, 5, 7};
    bmstu::vector my_vec4 = {1, 2, 3, 4, 5, 7, 8};
    bmstu::vector my_vec5 = {1, 1, 2, 3, 4, 5, 7};
    ASSERT_TRUE(my_vec1 == my_vec2);
    ASSERT_FALSE(my_vec1 == my_vec3);
    ASSERT_TRUE(my_vec1 != my_vec3);
    ASSERT_FALSE(my_vec1 != my_vec2);
    ASSERT_FALSE(my_vec1 < my_vec4);
    ASSERT_FALSE(my_vec4 > my_vec1);
    ASSERT_TRUE(my_vec1 <= my_vec5);
    ASSERT_TRUE(my_vec5 >= my_vec1);
}

TEST(DummyVector, one) {
    bmstu::vector<int> v;
    ASSERT_EQ(v.size(), 0u);
    ASSERT_TRUE(v.empty());
    ASSERT_EQ(v.capacity(), 0u);
}
//
//
TEST(DummyVector, Init) {
    // Инициализация вектора указанного размера
    bmstu::vector<int> v(5);
    ASSERT_EQ(v.size(), 5u);
    ASSERT_EQ(v.capacity(), 5u);
    ASSERT_TRUE(!v.empty());
    for (size_t i = 0; i < v.size(); ++i) {
        ASSERT_EQ(v[i], 0);
    }
}

TEST(DummyVector, Init2) {
    bmstu::vector<int> v(3, 42);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v.capacity(), 3);
    for (size_t i = 0; i < v.size(); ++i) {
        ASSERT_EQ(v[i], 42);
    }
}
//
TEST(DummyVector, InitList) {
    bmstu::vector<int> v{1, 2, 3};
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v.capacity(), 3);
    ASSERT_EQ(v[2], 3);
}
//
TEST(DummyVector, At) {
    bmstu::vector<int> v(3);
    ASSERT_EQ(&v.at(2), &v[2]);
    try {
        v.at(3);
    } catch (std::out_of_range const &err) {
        EXPECT_EQ(err.what(), std::string("Invalid index"));
    }
}
//
TEST(DummyVector, Clear) {

    bmstu::vector<int> v(10);
    const size_t old_capacity = v.capacity();
    v.clear();
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), old_capacity);
}
//
TEST(DummyVector, Resize) {
    // Изменение размера
    {
        bmstu::vector<int> v(3);
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
        bmstu::vector<int> v(3);
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
    bmstu::vector<int> v(3);
    v.resize(old_size + 5);
    v[3] = 42;
    v.resize(old_size);
    ASSERT_EQ(v[2], 0);
    v.resize(old_size + 3);
    ASSERT_EQ(v[3], 42);
}
//
TEST(DummyVector, Constructors) {
    {

        bmstu::vector<int> v(5);
        v[0] = 1;
        v[1] = 2;
        v[2] = 3;
        v[3] = 4;
        v[4] = 5;
        bmstu::vector<int> c(v);
        ASSERT_EQ(v[2], v[2]);
    }
    {

        bmstu::vector<int> v(5);
        v[0] = 1;
        v[1] = 2;
        v[2] = 3;
        v[3] = 4;
        v[4] = 5;
        bmstu::vector<int> c(v);
        ASSERT_EQ(v[2], v[2]);
    }
    {

        bmstu::vector<int> v(1);
        v.push_back(1);
        ASSERT_EQ(v[0], 0);
        ASSERT_EQ(*(v.begin()) + 1, 1);
    }
}

TEST(DummyVector, Push) {
    bmstu::vector<int> v(1);
    v.push_back(42);
    ASSERT_EQ(v.size(), 2);
    ASSERT_TRUE(v.capacity() >= v.size());
    ASSERT_EQ(v[0], 0);
    ASSERT_EQ(v[1], 42);
}

TEST(DummyVector, CopyConstruct)
// Конструктор копирования
{
    bmstu::vector<int> numbers{1, 2};
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
        bmstu::vector<int> v{0, 1, 2, 3};
        const size_t old_capacity = v.capacity();
        const auto old_begin = v.begin();
        v.pop_back();
        ASSERT_EQ(v.capacity(), old_capacity);
        ASSERT_EQ(v.begin(), old_begin);
        ASSERT_EQ(v, (bmstu::vector<int>{0, 1, 2}));
    }
}

TEST(DummyVector, Capacity) {

    bmstu::vector<int> v(2);
    v.resize(1);
    const size_t old_capacity = v.capacity();
    v.push_back(123);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v.capacity(), old_capacity);
}

TEST(DummyVector, Iterate) {
    {
        // Пустой вектор
        {
            bmstu::vector<int> v;
            ASSERT_EQ(v.begin(), nullptr);
            ASSERT_EQ(v.end(), nullptr);
        }

        // Непустой вектор
        {
            bmstu::vector<int> v(10, 42);
//            ASSERT_TRUE(v.begin());
            ASSERT_EQ(*v.begin(), 42);
            ASSERT_EQ(v.end(), v.begin() + v.size());
        }
    }
}

TEST(DummyVector, Compare) {
    {
        ASSERT_TRUE((bmstu::vector{1, 2, 3} == bmstu::vector{1, 2, 3}));
        ASSERT_TRUE((bmstu::vector{1, 2, 3} != bmstu::vector{1, 2, 2}));

        ASSERT_TRUE((bmstu::vector{1, 2, 3} < bmstu::vector{1, 2, 3, 1}));
        ASSERT_FALSE((bmstu::vector{1, 2, 3} > bmstu::vector{1, 2, 2, 1}));

        ASSERT_TRUE((bmstu::vector{1, 2, 3} >= bmstu::vector{1, 2, 3}));
        ASSERT_TRUE((bmstu::vector{1, 2, 4} >= bmstu::vector{1, 2, 3}));
        ASSERT_TRUE((bmstu::vector{1, 2, 3} <= bmstu::vector{1, 2, 3}));
        ASSERT_TRUE((bmstu::vector{1, 2, 3} <= bmstu::vector{1, 2, 4}));
    }
}

TEST(DummyVector, Pushback2) {
    bmstu::vector<int> v2;
    v2.push_back(0);
    v2.push_back(1);
    v2.push_back(2);
    ASSERT_EQ(v2, (bmstu::vector<int>{0, 1, 2}));
}

TEST(DummyVector, Swap) {
    // Обмен значений векторов
    {
        bmstu::vector<int> v1{42, 666};
        bmstu::vector<int> v2;
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
        bmstu::vector<int> src_vector{1, 2, 3, 4};
        bmstu::vector<int> dst_vector{1, 2, 3, 4, 5, 6};
        dst_vector = src_vector;
        ASSERT_EQ(dst_vector, src_vector);
    }
}

TEST(DummyVector, Insert) {
    // Вставка элементов
    {
        bmstu::vector<int> v{1, 2, 3, 4};
        auto vit = v.begin() + 3;
        v.insert(v.begin() + 2, 42);
        ASSERT_EQ(v, (bmstu::vector<int>{1, 2, 42, 3, 4}));
    }
}

TEST(DummyVector, Insert2) {
    // Вставка элементов

    bmstu::vector<int> v;
    v.insert(v.begin(), 42);
    ASSERT_EQ(v, (bmstu::vector<int>{42}));
}

TEST(DummyVector, Reserve) {

    {
        bmstu::vector<int> v(5);
        ASSERT_EQ(v.capacity(), 5);
        ASSERT_FALSE(v.empty());
    }

    {
        bmstu::vector<int> v;
        // зарезервируем 5 мест в векторе
        v.reserve(5);
        ASSERT_EQ(v.capacity(), 5);
        ASSERT_TRUE(v.empty());

        // попытаемся уменьшить capacity до 1
        v.reserve(1);
        // capacity должно остаться прежним
        ASSERT_EQ(v.capacity(), 5);
        // поместим 10 элементов в вектор
        for (int i = 0; i < 10; ++i) {
            v.push_back(i);
        }
        ASSERT_EQ(v.size(), 10);
        // увеличим capacity до 100
        v.reserve(100);
        // проверим, что размер не поменялся
        ASSERT_EQ(v.size(), 10);
        ASSERT_EQ(v.capacity(), 100);
        // проверим, что элементы на месте
        for (int i = 0; i < 10; ++i) {
            ASSERT_EQ(v[i], i);
        }
    }
}

