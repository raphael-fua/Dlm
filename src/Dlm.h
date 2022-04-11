#pragma once
#include "Cpd.h"


class Dlm : public virtual Cpd {
public:
    std::deque<std::size_t> checkpts;
    std::size_t p;

    Dlm(std::deque<std::size_t> const& checkpts, std::size_t const& p);
    // does not modify v
    Dlm(std::string const& stat_name,
        std::deque<double> &v,
        double const& thresh
    );

    void print() const;
    size_t peaks() const;
    virtual void update(double const& new_data) override;
};

