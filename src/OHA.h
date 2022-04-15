#pragma once
#include "Cpd.h"


class OHA : public virtual Cpd {
public:
    double sHalf;
    

    OHA(std::string const& stat_name, double const& thresh);
    void print() const;
    virtual void update(double const& new_data) override;
    
    // ↓ does not modify v
    //Dlm(std::string const& stat_name,
    //    std::deque<double> &v,
    //    double const& thresh
    //);

};

