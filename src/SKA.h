#pragma once
#include "Cpd.h"

class SKA: public virtual Cpd {
public:
    deque<deque<double>> layers;

    SKA(std::string const& stat_name,
        std::deque<double> &v,
        double const& thresh
    );
    //void print() const;
    virtual void update(double const& new_data) override;
};
