#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <gtest/gtest.h>
#include <iostream>
#include <set>
#include "array_checker.h"

TEST(correctness, simple_test) {
    EXPECT_EQ(intersection({1, 2, 3}, {2, 3, 4}), 2);
    EXPECT_EQ(intersection({1, -2, 3, 5, 10, 4, -100, 259, 71, 99, -322}, {2, -3, 4}), 1);
}

TEST(correctness, simple2_test) {
    EXPECT_EQ(intersection({1}, {1}), 1);
    EXPECT_EQ(intersection({1}, {-1}), 0);
    EXPECT_EQ(intersection({1000000000}, {1000000000}), 1);
    EXPECT_EQ(intersection({0, 13, 27, 30}, {30, 0, 13, 40}), 3);
}

TEST(correctness, min_test) {
    EXPECT_EQ(intersection({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, {12}), 0);
    EXPECT_EQ(intersection({1}, {4, 5, 3, 1, 2}), 1);
}

TEST(correctness, empty_test) {
    EXPECT_EQ(intersection({1, 2, 3, 5, 10, 15}, {}), 0);
    EXPECT_EQ(intersection({}, {1, 5, 10, 40, 3}), 0);
}

namespace {
    void generator(vector<int> &res, const int max_size = 300) {
        int size = rand() % max_size + 1;
        res.resize(size);
        for (int i = 0; i < size; ++i) {
            res[i] = rand() % (max_size + 1) - max_size / 2;
        }
        std::set<int> s(res.begin(), res.end());
        res.assign(s.begin(), s.end());
    }

    size_t simple_intersection(const vector<int> &lhs, const vector<int> &rhs) {
        size_t res = 0;
        for (int l_value : lhs) {
            for (int r_value : rhs) {
                res += (size_t) (l_value == r_value);
            }
        }
        return res;
    }

    size_t set_intersection(const vector<int> &lhs, const vector<int> &rhs) {
        size_t res = 0;
        std::set<int> s(lhs.begin(), lhs.end());
        for (int value : rhs) {
            s.insert(value);
        }
        return lhs.size() + rhs.size() - s.size();
    }
}

TEST(correctness, random_mutable_test) {
    vector<int> lhs, rhs;
    for (int times = 0; times < 50; ++times) {
        generator(lhs, 50);
        generator(rhs, 50);
        size_t res = simple_intersection(lhs, rhs);
        EXPECT_EQ(intersection(lhs, rhs), res);
        EXPECT_EQ(intersection(rhs, lhs), res);
    }
}

TEST(correctness, random_tiny_test) {
    vector<int> lhs, rhs;
    for (int times = 0; times < 1000; ++times) {
        generator(lhs, 10);
        generator(rhs, 10);
        size_t res = simple_intersection(lhs, rhs);
        EXPECT_EQ(intersection(lhs, rhs), res);
    }
}

TEST(correctness, random_small_test) {
    vector<int> lhs, rhs;
    for (int times = 0; times < 100; ++times) {
        generator(lhs);
        generator(rhs);
        size_t res = set_intersection(lhs, rhs);
        EXPECT_EQ(intersection(lhs, rhs), res);
    }
}

TEST(correctness, random_medium_test) {
    vector<int> lhs, rhs;
    auto size = (size_t) 2e4;
    for (int times = 0; times < 10; ++times) {
        std::cout << "TEST " << times + 1 << ".\n";
        generator(lhs, size);
        generator(rhs, size);
        size_t res = set_intersection(lhs, rhs);
        EXPECT_EQ(intersection(lhs, rhs), res);
    }
}

TEST(correctness, random_large_test) {
    vector<int> lhs, rhs;
    auto size = (size_t) 1e5;
    for (int times = 0; times < 3; ++times) {
        std::cout << "TEST " << times + 1 << ".\n";
        generator(lhs, size);
        generator(rhs, size);
        size_t res = set_intersection(lhs, rhs);
        EXPECT_EQ(intersection(lhs, rhs), res);
    }
}

