#pragma once

#include <vector>

constexpr int INT_SIZE = 32;

class Storage {
public:
    const int count;

private:
    std::vector<int> data;

public:
    Storage() : count(0) {};

    explicit Storage(int count);

    ~Storage() = default;

    static int get_bits(int count);

    static int get_size(int count);

    int get(int position);

    bool update(int position, int value);
};
