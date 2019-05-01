//
// Created by damm1t on 4/30/19.
//
#include <vector>
#include <iostream>
#include <unordered_map>
#include <assert.h>
#include <algorithm>
#include "array_checker.h"

namespace {

    struct item_holder {

        item_holder() = default;

        void add(int value) {
            cnt_small[value]++;
        }

        bool find(int value) {
            if (cnt_small.find(value) == cnt_small.end()) {
                return false;
            }
            return (cnt_small[value] != 0);
        }

        bool remove(int value) {
            if (find(value)) {
                cnt_small[value]--;
                return true;
            }
            return false;
        }

    private:
        std::unordered_map<int, size_t> cnt_small;
    };

    // solve without optimization on borders
    size_t small_intersection(const vector<int> &small, const vector<int> &large) {
        size_t res = 0;
        auto sorted_small = small;
        sort(sorted_small.begin(), sorted_small.end());
        for (int value : large) {
            auto find = std::lower_bound(sorted_small.begin(), sorted_small.end(), value);
            if (find != sorted_small.end() && *find == value) {
                res++;
            }
        }
        return res;
    }

    size_t intersection_impl(const vector<int> &small, const vector<int> &large) {
        if (large.empty()) {
            return 0;
        }

        if (small.size() <= SMALL_SIZE) {
            return small_intersection(small, large);
        }

        int lower_bound = large[0];
        int upper_bound = large[0];
        for (int value : large) { // find lower and upper bounds of large array
            lower_bound = std::min(lower_bound, value);
            upper_bound = std::max(upper_bound, value);
        }
        item_holder holder;
        // search for a pair from a large array to a small
        for (int value : small) { // add elements of small array to map with borders
            if (lower_bound <= value && value <= upper_bound) {
                holder.add(value);
            }
        }
        size_t cnt = 0;
        for (int value : large) {
            cnt += (size_t) holder.remove(value);
        }
        return cnt;
    }
}

size_t intersection(const vector<int> &lhs, const vector<int> &rhs) {
    if (lhs.size() > rhs.size()) {
        return intersection_impl(rhs, lhs);
    } else {
        return intersection_impl(lhs, rhs);
    }
}