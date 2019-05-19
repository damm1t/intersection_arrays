//
// Created by damm1t on 5/18/19.
//
#include "MurmurHash.h"

namespace utils {

    long long MurmurHash::hash(int val) {
        long long data = val;
        long long m = 0x5bd1e995;
        int r = 24;

        int h = 0;

        int k = data * m;
        k ^= static_cast<int>(static_cast<unsigned int>(k) >> r);
        h ^= k * m;

        k = static_cast<int>(data >> 32) * m;
        k ^= static_cast<int>(static_cast<unsigned int>(k) >> r);
        h *= m;
        h ^= k * m;

        h ^= static_cast<int>(static_cast<unsigned int>(h) >> 13);
        h *= m;
        h ^= static_cast<int>(static_cast<unsigned int>(h) >> 15);

        return h;
    }
}
