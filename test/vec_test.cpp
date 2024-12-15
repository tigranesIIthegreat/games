#include <gtest_main.hpp>
#include <utils/vec.hpp>

using namespace core;

TEST(Core, VecArithmetic) {
    Point vec1{11, 22};
    Point vec2{33, 44};
    EXPECT_TRUE((vec1 + vec2).equalsWithEpsilon(Point{44, 6}));
    EXPECT_TRUE((vec1 - vec2).equalsWithEpsilon(Point{-22, -22}));
    EXPECT_TRUE((vec1 * vec2).equalsWithEpsilon(Point{363, 968}));
    EXPECT_TRUE((vec2 / vec1).equalsWithEpsilon(Point{3, 2}));
}

TEST(Engine, VecNormalization) {
    Point vec1{30, 40};
    EXPECT_FLOAT_EQ(vec1[0], 30);
    EXPECT_FLOAT_EQ(vec1[1], 40);
    EXPECT_THROW(vec1[2], std::runtime_error);

    EXPECT_TRUE(vec1.size() == 2);
    EXPECT_TRUE(vec1.length() == 50);

    auto normalized1 = vec1.normalized();
    EXPECT_TRUE(normalized1.equalsWithEpsilon(Point{6, 8}));
}