#pragma once
#include "Cpd.h"

class Cpdh : public virtual Cpd {
public:
    std::deque<double> maxs;

    Cpdh(std::deque<double> const& maxs);

    void print() const;
    void update_maxs();
};

