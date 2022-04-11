#pragma once
#include "Dlm.h"
#include "Cpdh.h"


class Dlmh: public Dlm, public Cpdh
{
public:
    // does not modify v
    Dlmh(std::string const& stat_name,
         std::deque<double> &v,
         double const& thresh
    );

    void print() const;

    virtual void update(double const& new_data) override;
};

