#pragma once
#include "Cpd.h"

class GHA : public virtual Cpd {
public:
    std::deque<int> v_i;
    std::deque<double> v_pi;
    std::deque<int> v_k;
    std::deque<double> v_ski;
    std::deque<double> v_vki;
    std::deque<double> v_vvki;
    std::deque<double> v_cvki;
    double Z; // max_i (cvki)^2 =>
              // 	[if (argmax(cvk . )^2 = j = v_i[s]) and (Z > thre),
              //    [then cp = v_k[s] 2^v_i[s] "=" k_j 2^j ]

    GHA(std::deque<double> &v, double const& thresh);
    void print() const;
    virtual void update(double const& new_data) override;
};
