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

