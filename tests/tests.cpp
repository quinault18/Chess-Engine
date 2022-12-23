#include <gtest/gtest.h>
#include <iostream>
#include "square.h"



TEST(Simple, out) {
    Square s(1, 2);
    std::tuple<int, int> loc = s.getLocation();

    EXPECT_EQ(std::get<0>(loc), 1);
    EXPECT_EQ(std::get<1>(loc), 2);
}