//
// Created by TangXin on 2016/3/31.
//
#include "../BinaryTree.hpp"
#include "gtest/include/gtest/gtest.h"

TEST(TEST_BinaryTree, valid)
{
    BinaryTree<int> bt;
    bt.insert(2);
    bt.insert(1);
    bt.insert(3);
    EXPECT_EQ(true, bt.contains(1));
}

