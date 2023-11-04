#include <gtest/gtest.h>
#include "vector_template.h"
#include "array_bundle.h"
#include <numeric>
#include <functional>


TEST(JustTest, DefaultConstructor){
    bmstu::vector<int> vec;
    ASSERT_EQ(vec.size(), 0);
    ASSERT_EQ(vec.capacity(), 0);
}

