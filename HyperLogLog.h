#pragma once

#include <cmath>
#include <stdexcept>
#include <optional>
#include "Storage.h"

class HyperLogLog {

private:
    Storage *const storage;
    int sz_bites;
    double alpha;

public:

    ~HyperLogLog() {
        delete storage;
    }

private:

    static void validate(int log2m);

public:
    explicit HyperLogLog(int sz_bites);

    HyperLogLog(int sz_bites, Storage *registerSet);

    bool add_hash(long long hashedValue);

    bool add(int val);


    long long cardinality() const;

private:
    static double get_alpha(int bites, int size);

    static double linear_counting(int m, double V);
};
