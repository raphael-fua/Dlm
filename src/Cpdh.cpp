#include "Cpdh.h"
using namespace std;

Cpdh::Cpdh(deque<double> const& maxs):
    Cpd("default_name", {0}, {0}, 0, 0, 0),
    maxs (maxs)
{}

void Cpdh::print() const {
    Cpd::print();
    Rcpp::Rcout << "** maxs: ";
    for(auto const& elt : maxs) {
        Rcpp::Rcout << elt << " ";
    }
    Rcpp::Rcout << endl;
}

void Cpdh::update_maxs() {
    if (idx.size() == 1) {
        maxs = {0.0};
    } else {
        deque<double> const& v = stat();
        if (isnan(sums[0])) {
            maxs.push_back(*max_element(v.begin() + 1, v.end()));
        } else {
            maxs.push_back(*max_element(v.begin(), v.end()));
        }
    }
}
