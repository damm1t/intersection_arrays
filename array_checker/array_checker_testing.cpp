#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <gtest/gtest.h>
#include <iostream>
#include <set>
#include "array_checker/array_checker.h"

TEST(correctness, simple_test) {
    EXPECT_EQ(intersection({1, 2, 3}, {2, 3, 4}), 2);
    EXPECT_EQ(intersection({1, -2, 3, 5, 10, 4, -100, 259, 71, 99, -322}, {2, -3, 4}), 1);
}

TEST(correctness, simple2_test) {
    EXPECT_EQ(intersection({1}, {1}), 1);
    EXPECT_EQ(intersection({1}, {-1}), 0);
    EXPECT_EQ(intersection({INT32_MAX}, {2147483647}), 1);
    EXPECT_EQ(intersection({INT32_MIN}, {-2147483647 - 1}), 1);
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
    void generator(vector<int> &res, const int max_size = 32) {
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
    for (int times = 0; times < 700; ++times) {
        generator(lhs, 10);
        generator(rhs, 10);
        size_t res = simple_intersection(lhs, rhs);
        EXPECT_EQ(intersection(lhs, rhs), res);
    }
}

TEST(correctness, random_small_test) {
    vector<int> lhs, rhs;
    for (int times = 0; times < 200; ++times) {
        generator(lhs);
        generator(rhs);
        size_t res = set_intersection(lhs, rhs);
        EXPECT_EQ(intersection(lhs, rhs), res);
    }
}

TEST(correctness, random_medium_test) {
    vector<int> lhs, rhs;
    auto size = 300;
    for (int times = 0; times < 100; ++times) {
        generator(lhs, size);
        generator(rhs, size);
        size_t res = set_intersection(lhs, rhs);
        EXPECT_EQ(intersection(lhs, rhs), res);
    }
}

TEST(correctness, random_large_test) {
    vector<int> lhs, rhs;
    auto size = 2000;
    for (int times = 0; times < 6; ++times) {
        generator(lhs, (times + 1) * size);
        generator(rhs, (times + 1) * size);
        size_t res = set_intersection(lhs, rhs);
        EXPECT_EQ(intersection(lhs, rhs), res);
    }
}

