#pragma once
#include "Cpd.h"


class OHA : public virtual Cpd {
public:
    double sHalf;
    double alpha;
    double nu;

    OHA(std::deque<double> &v, double const& alpha, double const& nu);
    void print() const;
    virtual void update(double const& new_data) override;
};