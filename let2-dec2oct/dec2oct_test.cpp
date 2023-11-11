#include <gtest/gtest.h>
#include "fromdec2oct.h"

TEST(ConvertToOctalStringTest, PositiveNumber)
{
    int num1 = 666;
    char *result1 = convertToOctalString(num1);
    EXPECT_STREQ(result1, "0o1232");
    delete[] result1;
}

TEST(ConvertToOctalStringTest, NegativeNumber)
{
    int num2 = -666;
    char *result2 = convertToOctalString(num2);
    EXPECT_STREQ(result2, "-0o1232");
    delete[] result2;
}

TEST(ConvertToOctalStringTest, Zero)
{
    int num3 = 0;
    char *result3 = convertToOctalString(num3);
    EXPECT_STREQ(result3, "0o0");
    delete[] result3;
}
