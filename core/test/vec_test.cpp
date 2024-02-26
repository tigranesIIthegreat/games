#include <core/vec.hpp>
#include <gtest_main.hpp>

using namespace core;

TEST(Core, VecAddition) {
    Vec2 vec1{1.1, 2.2};
    Vec2 vec2{3.3, 4.4};
    EXPECT_TRUE((vec1 + vec2).equalsWithEpsilon(Vec2{4.4, 6.6}));
}

TEST(Engine, VecSubtraction) {
    Vec2 vec1{1.1, 2.2};
    Vec2 vec2{3.3, 4.4};
    EXPECT_TRUE((vec1 - vec2).equalsWithEpsilon(Vec2{-2.2, -2.2}));
}

TEST(Engine, VecMultiplication) {
    Vec2 vec1{1.1, 2.2};
    Vec2 vec2{3.3, 4.4};
    EXPECT_TRUE((vec1 * vec2).equalsWithEpsilon(Vec2{3.63, 9.68}));
}

TEST(Engine, VecDivision) {
    Vec2 vec1{3.3, 4.4};
    Vec2 vec2{1.1, 2.2};
    EXPECT_TRUE((vec1 / vec2).equalsWithEpsilon(Vec2{3, 2}));
}

TEST(Engine, VecNormalization) {
    Vec2 vec1{3.0, 4.0};
    EXPECT_FLOAT_EQ(vec1[0], 3.0);
    EXPECT_FLOAT_EQ(vec1[1], 4.0);
    EXPECT_THROW(vec1[2], std::runtime_error);

    EXPECT_TRUE(vec1.size() == 2);
    EXPECT_TRUE(vec1.length() == 5.0);

    auto normalized1 = vec1.normalized();
    EXPECT_TRUE(normalized1.equalsWithEpsilon(Vec2{0.6, 0.8}));
}