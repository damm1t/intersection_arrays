//
// Created by damm1t on 5/18/19.
//
#include "HyperLogLog.h"
#include "Storage.h"
#include "utils/MurmurHash.h"

using MurmurHash = utils::MurmurHash;

void HyperLogLog::validate(int sz_bites) {
    if (sz_bites < 0 || sz_bites > 30) {
        throw std::invalid_argument("sz_bites argument is outside the range [0, 30]");
    }
}

HyperLogLog::HyperLogLog(int sz_bites) : HyperLogLog(sz_bites, new Storage(1 << sz_bites)) {}

HyperLogLog::HyperLogLog(int sz_bites, Storage *registerSet) : storage(registerSet), sz_bites(sz_bites) {
    validate(sz_bites);
    int m = 1 << this->sz_bites;
    alpha = get_alpha(sz_bites, m);
}

bool HyperLogLog::add_hash(long long hashedValue) {
    int j = static_cast<int>(static_cast<unsigned int>(hashedValue) >> (32 - sz_bites));
    int r = __builtin_clz(static_cast<unsigned int>(static_cast<unsigned int>(hashedValue) << this->sz_bites) |
                          (1 << (this->sz_bites - 1)) + 1) + 1;
    return storage->update(j, r);
}

bool HyperLogLog::add(int val) {
    long long x = MurmurHash::hash(val);
    return add_hash(x);
}

long long HyperLogLog::cardinality() const {
    double registerSum = 0;
    int count = storage->count;
    double zeros = 0.0;
    for (int j = 0; j < storage->count; j++) {
        int val = storage->get(j);
        registerSum += 1.0 / (1 << val);
        if (val == 0) {
            zeros++;
        }
    }

    double estimate = alpha * (1 / registerSum);

    if (estimate <= (5.0 / 2.0) * count) {
        return static_cast<long long>(std::round(linear_counting(count, zeros)));
    } else {
        return static_cast<long long>(std::round(estimate));
    }
}

double HyperLogLog::get_alpha(int const bites, int const size) {
    switch (bites) {
        case 4:
            return 0.673 * size * size;
        case 5:
            return 0.697 * size * size;
        case 6:
            return 0.709 * size * size;
        default:
            return (0.7213 / (1 + 1.079 / size)) * size * size;
    }
}

double HyperLogLog::linear_counting(int m, double V) {
    return m * std::log(m / V);
}
