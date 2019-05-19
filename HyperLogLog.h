#pragma once

#include <cmath>
#include <stdexcept>
#include <optional>
#include "Storage.h"

// publication: http://algo.inria.fr/flajolet/Publications/FlFuGaMe07.pdf
class HyperLogLog {

private:
    Storage *const storage;
    int sz_bites;
    double alpha;

public:
    explicit HyperLogLog(int sz_bites);

    HyperLogLog(int sz_bites, Storage *data);

    ~HyperLogLog();

    bool add_hash(long long hashedValue);

    bool add(int val);

    long long cardinality() const;

private:
    static double get_alpha(int bites, int size);

    static void validate(int sz_bites);

    static double linear_counting(int m, double V);
};
