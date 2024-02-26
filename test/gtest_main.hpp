#pragma once

#include <gtest/gtest.h>

#define ADD_GTEST_MAIN                          \
    int main(int argc, char** argv) {           \
        ::testing::InitGoogleTest(&argc, argv); \
        return RUN_ALL_TESTS();                 \
    }
    
ADD_GTEST_MAIN;