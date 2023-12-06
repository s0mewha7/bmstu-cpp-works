#include <gtest/gtest.h>
#include "basic_optional.h"

class TS {
public:
    TS() noexcept {
        ++default_constr;
    }

    TS(const TS &other) noexcept {
        other.update();
        ++copy_constr;
    }

    TS(TS &&other) noexcept {
        std::move(other).update();
        ++move_constr;
    }

    TS &operator=(const TS &other) noexcept {
        if (this != &other) {
            other.update();
            ++copy_assign;
        }
        return *this;
    }

    TS &operator=(TS &&other) noexcept {
        if (this != &other) {
            std::move(other).update();
            ++move_assign;
        }
        return *this;
    }

    ~TS() {
        ++destruct;
    }

    void update() & {
        ++lvalue_call_count;
    }

    void update() const & {
        ++const_lvalue_call_count;
    }

    void update() && {
        ++rvalue_call_count;
    }

    static size_t instance_count() {
        return default_constr + copy_constr + move_constr - destruct;
    }

    static void reset() {
        default_constr = 0;
        copy_constr = 0;
        move_constr = 0;
        copy_assign = 0;
        move_assign = 0;
        destruct = 0;
        lvalue_call_count = 0;
        const_lvalue_call_count = 0;
        rvalue_call_count = 0;
    }

    inline static size_t default_constr = 0;
    inline static size_t copy_constr = 0;
    inline static size_t move_constr = 0;
    inline static size_t copy_assign = 0;
    inline static size_t move_assign = 0;
    inline static size_t destruct = 0;
    inline static size_t lvalue_call_count = 0;
    inline static size_t const_lvalue_call_count = 0;
    inline static size_t rvalue_call_count = 0;
};

TEST(OptionalTest, HasValueTest) {
    bmstu::optional<int> opt;
    ASSERT_FALSE(opt.has_value());
    bmstu::optional<int> opt2(3);
    ASSERT_TRUE(opt2.has_value());
}

TEST(OptionalTest, CopyValue) {
    bmstu::optional<int> opt_1(123);
    ASSERT_TRUE(opt_1.has_value());
    ASSERT_EQ(opt_1.value(), 123);
    int a = 321;
    bmstu::optional<int> opt_2(a);
    ASSERT_TRUE(opt_2.has_value());
    ASSERT_EQ(opt_2.value(), a);
}

TEST(OptionalTest, MoveValue) {
    int a = 321;
    bmstu::optional<int> opt(std::move(a));
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(opt.value(), 321);
}

TEST(OptionalTest, CopyOptional) {
    bmstu::optional<int> opt_1;
    bmstu::optional<int> opt_2(opt_1);
    ASSERT_FALSE(opt_1.has_value());
    ASSERT_FALSE(opt_2.has_value());
}

TEST(OptionalTest, CopyOptionalWithValue) {
    bmstu::optional<int> opt_1(123);
    bmstu::optional<int> opt_2(opt_1);
    ASSERT_TRUE(opt_1.has_value());
    ASSERT_TRUE(opt_2.has_value());
    ASSERT_EQ(opt_2.value(), 123);
}

TEST(OptionalTest, MoveEmptyOptional) {
    bmstu::optional<int> opt_1;
    bmstu::optional<int> opt_2(std::move(opt_1));
    ASSERT_FALSE(opt_1.has_value());
    ASSERT_FALSE(opt_2.has_value());
}

TEST(OptionalTest, MoveOptionalWithValue) {
    bmstu::optional<int> opt_1(123);
    bmstu::optional<int> opt_2(opt_1);
    ASSERT_TRUE(opt_1.has_value());
    ASSERT_TRUE(opt_2.has_value());
    ASSERT_EQ(opt_2.value(), 123);
}

TEST(OptionalTest, ChangeOptionalValue) {
    bmstu::optional<int> opt;
    opt = 123;
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(opt.value(), 123);
    opt = 321;
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(opt.value(), 321);
}

TEST(OptionalTest, MoveOptionalValue) {
    bmstu::optional<int> opt;
    int a = 123;
    int b = 321;
    opt = std::move(a);
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(opt.value(), 123);
    opt = std::move(b);
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(opt.value(), 321);
}

TEST(OptionalTest, DefaultM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        bmstu::optional<TS> opt;
        ASSERT_FALSE(opt.has_value());
        ASSERT_EQ(TS::instance_count(), 0);
        ASSERT_EQ(TS::default_constr, 0);
        ASSERT_EQ(TS::copy_constr, 0);
        ASSERT_EQ(TS::move_constr, 0);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 0);
        ASSERT_EQ(TS::rvalue_call_count, 0);
    }
}

TEST(OptionalTest, CopyValueM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable;
        bmstu::optional<TS> opt(variable);
        ASSERT_TRUE(opt.has_value());
        ASSERT_EQ(TS::instance_count(), 2);
        ASSERT_EQ(TS::default_constr, 1);
        ASSERT_EQ(TS::copy_constr, 1);
        ASSERT_EQ(TS::move_constr, 0);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 1);
        ASSERT_EQ(TS::rvalue_call_count, 0);
    }
    ASSERT_EQ(TS::default_constr, 1);
    ASSERT_EQ(TS::copy_constr, 1);
    ASSERT_EQ(TS::destruct, 2);
    ASSERT_EQ(TS::instance_count(), 0);
}

TEST(OptionalTest, CopyOperatorValueM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable;
        bmstu::optional<TS> opt;
        opt = variable;
        ASSERT_TRUE(opt.has_value());
        ASSERT_EQ(TS::instance_count(), 2);
        ASSERT_EQ(TS::default_constr, 1);
        ASSERT_EQ(TS::copy_constr, 1);
        ASSERT_EQ(TS::move_constr, 0);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 1);
        ASSERT_EQ(TS::rvalue_call_count, 0);
    }
    ASSERT_EQ(TS::default_constr, 1);
    ASSERT_EQ(TS::copy_constr, 1);
    ASSERT_EQ(TS::destruct, 2);
    ASSERT_EQ(TS::instance_count(), 0);
}

TEST(OptionalTest, CopyOperatorFromOneToAnotherM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable_1;
        TS variable_2;
        bmstu::optional<TS> opt(variable_1);
        opt = variable_2;
        ASSERT_TRUE(opt.has_value());
        ASSERT_EQ(TS::instance_count(), 3);
        ASSERT_EQ(TS::default_constr, 2);
        ASSERT_EQ(TS::copy_constr, 1);
        ASSERT_EQ(TS::move_constr, 0);
        ASSERT_EQ(TS::copy_assign, 1);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 2);
        ASSERT_EQ(TS::rvalue_call_count, 0);
    }
    ASSERT_EQ(TS::default_constr, 2);
    ASSERT_EQ(TS::copy_constr, 1);
    ASSERT_EQ(TS::copy_assign, 1);
    ASSERT_EQ(TS::destruct, 3);
    ASSERT_EQ(TS::instance_count(), 0);
}

TEST(OptionalTest, MoveValueM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable;
        bmstu::optional<TS> opt(std::move(variable));
        ASSERT_TRUE(opt.has_value());
        ASSERT_EQ(TS::instance_count(), 2);
        ASSERT_EQ(TS::default_constr, 1);
        ASSERT_EQ(TS::copy_constr, 0);
        ASSERT_EQ(TS::move_constr, 1);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 0);
        ASSERT_EQ(TS::rvalue_call_count, 1);
    }
    ASSERT_EQ(TS::default_constr, 1);
    ASSERT_EQ(TS::move_constr, 1);
    ASSERT_EQ(TS::destruct, 2);
    ASSERT_EQ(TS::instance_count(), 0);
}

TEST(OptionalTest, MoveOperatorValueM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable;
        bmstu::optional<TS> opt;
        opt = std::move(variable);
        ASSERT_TRUE(opt.has_value());
        ASSERT_EQ(TS::instance_count(), 2);
        ASSERT_EQ(TS::default_constr, 1);
        ASSERT_EQ(TS::copy_constr, 0);
        ASSERT_EQ(TS::move_constr, 1);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 0);
        ASSERT_EQ(TS::rvalue_call_count, 1);
    }
    ASSERT_EQ(TS::default_constr, 1);
    ASSERT_EQ(TS::move_constr, 1);
    ASSERT_EQ(TS::destruct, 2);
    ASSERT_EQ(TS::instance_count(), 0);
}

TEST(OptionalTest, MoveOperatorFromOneToAnotherM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable_1;
        TS variable_2;
        bmstu::optional<TS> opt(variable_1);
        opt = std::move(variable_2);
        ASSERT_TRUE(opt.has_value());
        ASSERT_EQ(TS::instance_count(), 3);
        ASSERT_EQ(TS::default_constr, 2);
        ASSERT_EQ(TS::copy_constr, 1);
        ASSERT_EQ(TS::move_constr, 0);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 1);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 1);
        ASSERT_EQ(TS::rvalue_call_count, 1);
    }
    ASSERT_EQ(TS::default_constr, 2);
    ASSERT_EQ(TS::copy_constr, 1);
    ASSERT_EQ(TS::move_assign, 1);
    ASSERT_EQ(TS::destruct, 3);
    ASSERT_EQ(TS::instance_count(), 0);
}

TEST(OptionalTest, CopyEmptyOptionalM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        bmstu::optional<TS> opt_1;
        bmstu::optional<TS> opt_2(opt_1);
        ASSERT_FALSE(opt_1.has_value());
        ASSERT_FALSE(opt_2.has_value());
        ASSERT_EQ(TS::instance_count(), 0);
        ASSERT_EQ(TS::default_constr, 0);
        ASSERT_EQ(TS::copy_constr, 0);
        ASSERT_EQ(TS::move_constr, 0);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 0);
        ASSERT_EQ(TS::rvalue_call_count, 0);
    }
}

TEST(OptionalTest, CopyOptionalWithValueM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable;
        bmstu::optional<TS> opt_1(variable);
        bmstu::optional<TS> opt_2(opt_1);
        ASSERT_TRUE(opt_1.has_value());
        ASSERT_TRUE(opt_2.has_value());
        ASSERT_EQ(TS::instance_count(), 3);
        ASSERT_EQ(TS::default_constr, 1);
        ASSERT_EQ(TS::copy_constr, 2);
        ASSERT_EQ(TS::move_constr, 0);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 2);
        ASSERT_EQ(TS::rvalue_call_count, 0);
    }
    ASSERT_EQ(TS::default_constr, 1);
    ASSERT_EQ(TS::copy_constr, 2);
    ASSERT_EQ(TS::destruct, 3);
    ASSERT_EQ(TS::instance_count(), 0);
}

TEST(OptionalTest, MoveEmptyOptionalM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        bmstu::optional<TS> opt_1;
        bmstu::optional<TS> opt_2(std::move(opt_1));
        ASSERT_FALSE(opt_1.has_value());
        ASSERT_FALSE(opt_2.has_value());
        ASSERT_EQ(TS::instance_count(), 0);
        ASSERT_EQ(TS::default_constr, 0);
        ASSERT_EQ(TS::copy_constr, 0);
        ASSERT_EQ(TS::move_constr, 0);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 0);
        ASSERT_EQ(TS::rvalue_call_count, 0);
    }
}

TEST(OptionalTest, MoveOptionalWithValueM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable;
        bmstu::optional<TS> opt_1(variable);
        bmstu::optional<TS> opt_2(std::move(opt_1));
        ASSERT_TRUE(opt_2.has_value());
        ASSERT_EQ(TS::instance_count(), 3);
        ASSERT_EQ(TS::default_constr, 1);
        ASSERT_EQ(TS::copy_constr, 1);
        ASSERT_EQ(TS::move_constr, 1);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 1);
        ASSERT_EQ(TS::rvalue_call_count, 1);
    }
    ASSERT_EQ(TS::default_constr, 1);
    ASSERT_EQ(TS::copy_constr, 1);
    ASSERT_EQ(TS::move_constr, 1);
    ASSERT_EQ(TS::destruct, 3);
    ASSERT_EQ(TS::instance_count(), 0);
}

TEST(OptionalTest, CopyOptionalFromValueToAnotherValueOperatorM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable_1;
        TS variable_2;
        bmstu::optional<TS> opt_1(variable_1);
        bmstu::optional<TS> opt_2(variable_2);
        opt_2 = opt_1;
        ASSERT_TRUE(opt_1.has_value());
        ASSERT_TRUE(opt_2.has_value());
        ASSERT_EQ(TS::instance_count(), 4);
        ASSERT_EQ(TS::default_constr, 2);
        ASSERT_EQ(TS::copy_constr, 2);
        ASSERT_EQ(TS::move_constr, 0);
        ASSERT_EQ(TS::copy_assign, 1);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 3);
        ASSERT_EQ(TS::rvalue_call_count, 0);
    }
    ASSERT_EQ(TS::default_constr, 2);
    ASSERT_EQ(TS::copy_constr, 2);
    ASSERT_EQ(TS::copy_assign, 1);
    ASSERT_EQ(TS::destruct, 4);
    ASSERT_EQ(TS::instance_count(), 0);
}

TEST(OptionalTest, CopyOptionalFromEmptyToValueOperatorM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable_1;
        bmstu::optional<TS> opt_1(variable_1);
        bmstu::optional<TS> opt_2;
        opt_2 = opt_1;
        ASSERT_TRUE(opt_1.has_value());
        ASSERT_TRUE(opt_2.has_value());
        ASSERT_EQ(TS::instance_count(), 3);
        ASSERT_EQ(TS::default_constr, 1);
        ASSERT_EQ(TS::copy_constr, 2);
        ASSERT_EQ(TS::move_constr, 0);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 2);
        ASSERT_EQ(TS::rvalue_call_count, 0);
    }
    ASSERT_EQ(TS::default_constr, 1);
    ASSERT_EQ(TS::copy_constr, 2);
    ASSERT_EQ(TS::destruct, 3);
    ASSERT_EQ(TS::instance_count(), 0);
}

TEST(OptionalTest, CopyOptionalFromValueToEmptyM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable_1;
        bmstu::optional<TS> opt_1(variable_1);
        bmstu::optional<TS> opt_2;
        opt_1 = opt_2;
        ASSERT_FALSE(opt_1.has_value());
        ASSERT_FALSE(opt_2.has_value());
        ASSERT_EQ(TS::instance_count(), 1);
        ASSERT_EQ(TS::default_constr, 1);
        ASSERT_EQ(TS::copy_constr, 1);
        ASSERT_EQ(TS::move_constr, 0);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 1);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 1);
        ASSERT_EQ(TS::rvalue_call_count, 0);
    }
    ASSERT_EQ(TS::default_constr, 1);
    ASSERT_EQ(TS::copy_constr, 1);
    ASSERT_EQ(TS::destruct, 2);
    ASSERT_EQ(TS::instance_count(), 0);
}

TEST(OptionalTest, MoveOptionalOperatorM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable_1;
        TS variable_2;
        bmstu::optional<TS> opt_1(variable_1);
        bmstu::optional<TS> opt_2(variable_2);
        opt_2 = std::move(opt_1);
        ASSERT_TRUE(opt_2.has_value());
        ASSERT_EQ(TS::instance_count(), 4);
        ASSERT_EQ(TS::default_constr, 2);
        ASSERT_EQ(TS::copy_constr, 2);
        ASSERT_EQ(TS::move_constr, 0);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 1);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 2);
        ASSERT_EQ(TS::rvalue_call_count, 1);
    }
    ASSERT_EQ(TS::default_constr, 2);
    ASSERT_EQ(TS::copy_constr, 2);
    ASSERT_EQ(TS::move_assign, 1);
    ASSERT_EQ(TS::destruct, 4);
    ASSERT_EQ(TS::instance_count(), 0);
}

TEST(OptionalTest, MoveOptionalFromEmptyToValueOperatorM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable_1;
        bmstu::optional<TS> opt_1(variable_1);
        bmstu::optional<TS> opt_2;
        opt_2 = std::move(opt_1);
        ASSERT_TRUE(opt_2.has_value());
        ASSERT_EQ(TS::instance_count(), 3);
        ASSERT_EQ(TS::default_constr, 1);
        ASSERT_EQ(TS::copy_constr, 1);
        ASSERT_EQ(TS::move_constr, 1);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 0);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 1);
        ASSERT_EQ(TS::rvalue_call_count, 1);
    }
    ASSERT_EQ(TS::default_constr, 1);
    ASSERT_EQ(TS::copy_constr, 1);
    ASSERT_EQ(TS::destruct, 3);
    ASSERT_EQ(TS::instance_count(), 0);
}

TEST(OptionalTest, MoveOptionalOperatorFromValueToEmptyM) {
    TS::reset();
    ASSERT_EQ(TS::instance_count(), 0);
    {
        TS variable_1;
        bmstu::optional<TS> opt_1(variable_1);
        bmstu::optional<TS> opt_2;
        opt_1 = std::move(opt_2);
        ASSERT_FALSE(opt_1.has_value());
        ASSERT_FALSE(opt_2.has_value());
        ASSERT_EQ(TS::instance_count(), 1);
        ASSERT_EQ(TS::default_constr, 1);
        ASSERT_EQ(TS::copy_constr, 1);
        ASSERT_EQ(TS::move_constr, 0);
        ASSERT_EQ(TS::copy_assign, 0);
        ASSERT_EQ(TS::move_assign, 0);
        ASSERT_EQ(TS::destruct, 1);
        ASSERT_EQ(TS::lvalue_call_count, 0);
        ASSERT_EQ(TS::const_lvalue_call_count, 1);
        ASSERT_EQ(TS::rvalue_call_count, 0);
    }
    ASSERT_EQ(TS::default_constr, 1);
    ASSERT_EQ(TS::copy_constr, 1);
    ASSERT_EQ(TS::destruct, 2);
    ASSERT_EQ(TS::instance_count(), 0);
}
