#pragma once
#include "Cpd.h"
#include <Rcpp.h>



class GDLM : public virtual Cpd {
public:
    int q; // should be >= 1
    Rcpp::IntegerMatrix mIdx;
    Rcpp::NumericVector mSums;
    std::vector<int> tmpIdx;
    std::vector<int> tmpSums;
    std::vector<int> k;

    GDLM(int const& q,
         std::string const& stat_name,
         std::deque<double> &v,
         double const& thresh
    );

    void print() const;
    virtual void update(double const& new_data) override;

};

