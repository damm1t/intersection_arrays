#pragma once

#include <vector>

class Storage {
public:
    const int count;

private:
    std::vector<int> M;

public:
    Storage() : count(0) {};

    explicit Storage(int count);

    ~Storage() = default;

    static int get_bits(int count);

    static int get_size(int count);

    virtual int get(int position);

    virtual bool update(int position, int value);
};
