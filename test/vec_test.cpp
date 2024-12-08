#include <gtest_main.hpp>
#include <utils/vec.hpp>

using namespace core;

TEST(Core, VecArithmetic) {
    Point vec1{1.1, 2.2};
    Point vec2{3.3, 4.4};
    EXPECT_TRUE((vec1 + vec2).equalsWithEpsilon(Point{4.4, 6.6}));
    EXPECT_TRUE((vec1 - vec2).equalsWithEpsilon(Point{-2.2, -2.2}));
    EXPECT_TRUE((vec1 * vec2).equalsWithEpsilon(Point{3.63, 9.68}));
    EXPECT_TRUE((vec2 / vec1).equalsWithEpsilon(Point{3, 2}));
}

TEST(Engine, VecNormalization) {
    Point vec1{3.0, 4.0};
    EXPECT_FLOAT_EQ(vec1[0], 3.0);
    EXPECT_FLOAT_EQ(vec1[1], 4.0);
    EXPECT_THROW(vec1[2], std::runtime_error);

    EXPECT_TRUE(vec1.size() == 2);
    EXPECT_TRUE(vec1.length() == 5.0);

    auto normalized1 = vec1.normalized();
    EXPECT_TRUE(normalized1.equalsWithEpsilon(Point{0.6, 0.8}));
}