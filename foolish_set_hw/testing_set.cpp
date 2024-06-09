#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

#include "search_tree.h"
#include "foolish_set.h"

TEST(SearchTreeTest, EmptyTree) {
    bmstu::search_tree<int> tree;
    ASSERT_EQ(tree.size(), 0);
    std::stringstream os;
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "");
}

TEST(SearchTreeTest, BasicInsert) {
    bmstu::search_tree<int> tree;
    tree.insert(2);
    ASSERT_EQ(tree.size(), 1);
    std::stringstream os;
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "2 ");
    tree.insert(1);
    ASSERT_EQ(tree.size(), 2);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "2 1 ");
    tree.insert(3);
    ASSERT_EQ(tree.size(), 3);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "2 1 3 ");
    tree.insert(3);
    ASSERT_EQ(tree.size(), 3);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "2 1 3 ");
}

TEST(SearchTreeTest, BasicContains) {
    bmstu::search_tree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    ASSERT_TRUE(tree.contains(1));
    ASSERT_TRUE(tree.contains(2));
    ASSERT_FALSE(tree.contains(5));
}

TEST(SearchTreeTest, BasicRemove) {
    bmstu::search_tree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    ASSERT_EQ(tree.size(), 3);
    std::stringstream os;
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "2 1 3 ");
    tree.remove(3);
    ASSERT_EQ(tree.size(), 2);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "2 1 ");
    tree.remove(2);
    ASSERT_EQ(tree.size(), 1);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "1 ");
    tree.remove(1);
    ASSERT_EQ(tree.size(), 0);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "");
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.remove(2);
    ASSERT_EQ(tree.size(), 2);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "3 1 ");
    tree.remove(10);
    ASSERT_EQ(tree.size(), 2);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "3 1 ");
}

TEST(SearchTreeTest, BasicSize) {
    bmstu::search_tree<int> tree;
    tree.insert(2);
    ASSERT_EQ(tree.size(), 1);
    tree.insert(1);
    ASSERT_EQ(tree.size(), 2);
    tree.insert(3);
    ASSERT_EQ(tree.size(), 3);
    tree.remove(1);
    ASSERT_EQ(tree.size(), 2);
    tree.remove(2);
    ASSERT_EQ(tree.size(), 1);
    tree.remove(3);
    ASSERT_EQ(tree.size(), 0);
}

TEST(SearchTreeTest, BasicHeight) {
    bmstu::search_tree<int> tree;
    ASSERT_EQ(tree.height(), 0);
    tree.insert(2);
    ASSERT_EQ(tree.size(), 1);
    ASSERT_EQ(tree.height(), 1);
    tree.insert(1);
    ASSERT_EQ(tree.size(), 2);
    ASSERT_EQ(tree.height(), 2);
    tree.insert(3);
    ASSERT_EQ(tree.size(), 3);
    ASSERT_EQ(tree.height(), 2);
    tree.remove(1);
    ASSERT_EQ(tree.size(), 2);
    ASSERT_EQ(tree.height(), 2);
    tree.remove(2);
    ASSERT_EQ(tree.size(), 1);
    ASSERT_EQ(tree.height(), 1);
    tree.remove(3);
    ASSERT_EQ(tree.size(), 0);
    ASSERT_EQ(tree.height(), 0);
}

TEST(SearchTreeTest, inorderTraversal) {
    bmstu::search_tree<int> tree;
    tree.insert(2);
    ASSERT_EQ(tree.size(), 1);
    std::stringstream os;
    tree.inorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "2 ");
    tree.insert(1);
    ASSERT_EQ(tree.size(), 2);
    os = {};
    tree.inorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "1 2 ");
    tree.insert(3);
    ASSERT_EQ(tree.size(), 3);
    os = {};
    tree.inorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "1 2 3 ");
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    ASSERT_EQ(tree.size(), 10);
    os = {};
    tree.inorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "1 2 3 4 5 6 7 8 9 10 ");
}

TEST(SearchTreeTest, preorderTraversal) {
    bmstu::search_tree<int> tree;
    tree.insert(2);
    ASSERT_EQ(tree.size(), 1);
    std::stringstream os;
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "2 ");
    tree.insert(1);
    ASSERT_EQ(tree.size(), 2);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "2 1 ");
    tree.insert(3);
    ASSERT_EQ(tree.size(), 3);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "2 1 3 ");
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    ASSERT_EQ(tree.size(), 10);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "4 2 1 3 8 6 5 7 9 10 ");
}

TEST(SearchTreeTest, postorderTraversal) {
    bmstu::search_tree<int> tree;
    tree.insert(2);
    ASSERT_EQ(tree.size(), 1);
    std::stringstream os;
    tree.postorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "2 ");
    tree.insert(1);
    ASSERT_EQ(tree.size(), 2);
    os = {};
    tree.postorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "1 2 ");
    tree.insert(3);
    ASSERT_EQ(tree.size(), 3);
    os = {};
    tree.postorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "1 3 2 ");
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    ASSERT_EQ(tree.size(), 10);
    os = {};
    tree.postorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "1 3 2 5 7 6 10 9 8 4 ");
}

TEST(SearchTreeTest,  RotateLeftSimpleCase) {
    bmstu::search_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    std::stringstream os;
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "1 2 ");
    tree.insert(3);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "2 1 3 ");
}

TEST(SearchTreeTest, RotateRightSimpleCase) {
    bmstu::search_tree<int> tree;
    tree.insert(3);
    tree.insert(2);
    std::stringstream os;
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "3 2 ");
    tree.insert(1);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "2 1 3 ");
}

TEST(SearchTreeTest, ComplexRotationCase) {
    bmstu::search_tree<int> tree;
    tree.insert(4);
    tree.insert(1);
    tree.insert(7);
    tree.insert(8);
    tree.insert(6);
    std::stringstream os;
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "4 1 7 6 8 ");
    tree.insert(5);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "6 4 1 5 7 8 ");
}

TEST(SearchTreeTest, AnotherComplexRotationCase) {
    bmstu::search_tree<int> tree;
    tree.insert(6);
    tree.insert(7);
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    std::stringstream os;
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "6 3 2 4 7 ");
    tree.insert(5);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "4 3 2 6 5 7 ");
}

TEST(SearchTreeTest, LargeTreeBalancedRotation) {
    bmstu::search_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    std::stringstream os;
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "4 2 1 3 8 6 5 7 9 10 ");
}

TEST(SearchTreeTest, VeryLargeTreeBalancedRotation) {
    bmstu::search_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    tree.insert(11);
    tree.insert(12);
    tree.insert(13);
    tree.insert(14);
    tree.insert(15);
    tree.insert(16);
    tree.insert(17);
    tree.insert(18);
    tree.insert(19);
    tree.insert(20);
    tree.insert(21);
    tree.insert(22);
    tree.insert(23);
    tree.insert(24);
    tree.insert(25);
    tree.insert(26);
    tree.insert(27);
    tree.insert(28);
    tree.insert(29);
    tree.insert(30);
    tree.insert(31);
    std::stringstream os;
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(),
                 "16 8 4 2 1 3 6 5 7 12 10 9 11 14 13 15 24 20 18 17 19 22 21 23 "
                 "28 26 25 27 30 29 31 ");
}

TEST(SearchTreeTest, DescendingOrderInsertionRotation) {
    bmstu::search_tree<int> tree;
    tree.insert(1300);
    tree.insert(1200);
    tree.insert(1100);
    tree.insert(1000);
    tree.insert(900);
    tree.insert(800);
    tree.insert(700);
    tree.insert(600);
    tree.insert(500);
    tree.insert(400);
    tree.insert(300);
    tree.insert(200);
    tree.insert(100);
    std::stringstream os;
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(),
                 "600 400 200 100 300 500 1000 800 700 900 1200 1100 1300 ");
}

TEST(SearchTreeTest, RotationAfterRemovals) {
    bmstu::search_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    std::stringstream os;
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "4 2 1 3 8 6 5 7 9 10 ");
    tree.remove(4);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "5 2 1 3 8 6 7 9 10 ");
    tree.remove(7);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "5 2 1 3 8 6 9 10 ");
    tree.remove(6);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "5 2 1 3 9 8 10 ");
    tree.remove(8);
    os = {};
    tree.preorderTraversal(os);
    ASSERT_STREQ(os.str().c_str(), "5 2 1 3 9 10 ");
}

TEST(FoolishSetTest, СonstructEmpty) {
    bmstu::set<int> set;
    ASSERT_TRUE(set.empty());
}

TEST(FoolishSetTest, Insert) {
    bmstu::set<int> set;
    ASSERT_TRUE(set.empty());
    set.insert(1);
    ASSERT_EQ(set.size(), 1);
    set.insert(5);
    ASSERT_EQ(set.size(), 2);
    set.insert(5);
    ASSERT_EQ(set.size(), 2);
    set.insert(3);
    set.insert(4);
    set.insert(8);
    ASSERT_EQ(set.size(), 5);
    ASSERT_EQ(set.find(1)->data, 1);
    ASSERT_EQ(set.find(5)->data, 5);
    ASSERT_EQ(set.find(3)->data, 3);
    ASSERT_EQ(set.find(4)->data, 4);
    ASSERT_EQ(set.find(8)->data, 8);
}

TEST(FoolishSetTest, Erase) {
    bmstu::set<int> set;
    ASSERT_TRUE(set.empty());
    set.insert(1);
    set.insert(2);
    set.insert(5);
    set.insert(4);
    set.insert(3);
    ASSERT_EQ(set.size(), 5);
    ASSERT_EQ(set.find(3)->data, 3);
    set.erase(3);
    ASSERT_EQ(set.size(), 4);
    ASSERT_EQ(set.find(3), nullptr);
}

TEST(FoolishSetTest, Size) {
    bmstu::set<int> set;
    ASSERT_TRUE(set.empty());
    ASSERT_EQ(set.size(), 0);
    set.insert(1);
    ASSERT_EQ(set.size(), 1);
    set.insert(2);
    ASSERT_EQ(set.size(), 2);
    set.insert(5);
    ASSERT_EQ(set.size(), 3);
    set.insert(4);
    ASSERT_EQ(set.size(), 4);
    set.insert(3);
    ASSERT_EQ(set.size(), 5);
}

TEST(FoolishSetTest, Clear) {
    bmstu::set<int> set;
    ASSERT_TRUE(set.empty());
    set.insert(1);
    set.insert(2);
    set.insert(3);
    ASSERT_EQ(set.size(), 3);
    set.clear();
    ASSERT_TRUE(set.empty());
    ASSERT_EQ(set.size(), 0);
}

TEST(FoolishSetTest, Find) {
    bmstu::set<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    ASSERT_EQ(set.find(3)->data, 3);
    ASSERT_EQ(set.find(2)->data, 2);
    ASSERT_EQ(set.find(1)->data, 1);
    ASSERT_EQ(set.find(5), nullptr);
}

TEST(SearchTreeTest, printed1) {
    bmstu::search_tree<int> tree;
    tree.insert(4);
    tree.insert(1);
    tree.insert(6);
    tree.insert(7);
    tree.insert(5);
    tree.insert(8);
    tree.insert(9);
    tree.insert(-1);
    tree.insert(3);
    tree.print();
}

TEST(SearchTreeTest, printed2) {
    bmstu::search_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.print();
    tree.insert(3);
    tree.print();
}

TEST(SearchTreeTest, printed3) {
    bmstu::search_tree<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.print();
    tree.insert(1);
    tree.print();
}

TEST(SearchTreeTest, printed4) {
    bmstu::search_tree<int> tree;
    tree.insert(4);
    tree.insert(1);
    tree.insert(7);
    tree.insert(8);
    tree.insert(6);
    tree.print();
    tree.insert(5);
    tree.print();
}

TEST(SearchTreeTest, printed5) {
    bmstu::search_tree<int> tree;
    tree.insert(6);
    tree.insert(7);
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.print();
    tree.insert(5);
    tree.print();
}

TEST(SearchTreeTest, printed6) {
    bmstu::search_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    tree.print();
}

TEST(SearchTreeTest, printed7) {
    bmstu::search_tree<int> tree;
    tree.insert(100);
    tree.insert(200);
    tree.insert(300);
    tree.insert(400);
    tree.insert(500);
    tree.insert(600);
    tree.insert(700);
    tree.insert(800);
    tree.insert(900);
    tree.insert(1000);
    tree.insert(1100);
    tree.insert(1200);
    tree.insert(1300);
    tree.print();
}

TEST(SearchTreeTest, printed8) {
    bmstu::search_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    tree.print();
    tree.remove(4);
    tree.print();
    tree.remove(7);
    tree.print();
    tree.remove(6);
    tree.print();
    tree.remove(8);
    tree.print();
}

TEST(SearchTreeTest, printed9) {
    bmstu::search_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.remove(3);
    tree.print();
}

TEST(SearchTreeTest, printed10) {
    bmstu::search_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.print();
    tree.remove(1);
    tree.print();
}

TEST(SearchTreeTest, printed11) {
    bmstu::search_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    tree.print();
    tree.inorderTraversal(std::cout);
    std::cout << std::endl;
    tree.preorderTraversal(std::cout);
    std::cout << std::endl;
    tree.postorderTraversal(std::cout);
    std::cout << std::endl;
}

TEST(FoolishSetTest, printed1) {
    bmstu::set<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(8);
    set.insert(5);
    set.print();
}


TEST(FoolishSetTest, printed2) {
    std::set<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(8);
    set.insert(5);
    for (const auto & item : set) {
        std::cout << item << "\n";
    }
}

TEST(FoolishSetTest, printed11) {
    bmstu::set<int> norepeat;
    norepeat.insert(1);
    norepeat.insert(2);
    norepeat.insert(3);
    norepeat.insert(8);
    norepeat.insert(5);
    for (const auto & item : norepeat) {
        std::cout << item << "\n";
    }
} // NOLINT