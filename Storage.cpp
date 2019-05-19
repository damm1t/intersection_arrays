//
// Created by damm1t on 5/18/19.
//
#include "Storage.h"

constexpr int LOG2_BITS = 6;
constexpr int REG_SIZE = 5;

Storage::Storage(int count) : count(count), data(std::vector<int>(get_size(count))) {}

int Storage::get_bits(int count) {
    return count / LOG2_BITS;
}

int Storage::get_size(int count) {
    int bits = get_bits(count);
    if (bits == 0) {
        return 1;
    } else if (bits % INT_SIZE == 0) {
        return bits;
    } else {
        return bits + 1;
    }
}

int Storage::get(int position) {
    int bucket_index = position / LOG2_BITS;
    int shift = REG_SIZE * (position - (bucket_index * LOG2_BITS));
    return static_cast<int>(
            static_cast<unsigned int>((this->data[bucket_index] & (0x1f << shift))) >> shift);
}

bool Storage::update(int position, int value) {
    int bucket = position / LOG2_BITS;
    int shift = REG_SIZE * (position - (bucket * LOG2_BITS));
    int mask = 0x1f << shift;

    long long cur_val = this->data[bucket] & mask;
    long long new_val = value << shift;
    if (cur_val < new_val) {
        this->data[bucket] = static_cast<int>((this->data[bucket] & ~mask) | new_val);
        return true;
    } else {
        return false;
    }
}
