#include "SKA.h"

SKA(std::string const& stat_name, std::deque<double> &v, double const& thresh):
    Cpd(stat_name, {1}, {v[0]}, thresh, -1, -1),

{
    double tmp = v.front();
    v.pop_front();
    Cpd::update(v);
    v.push_front(tmp);
}


void SKA::update(const double &new_data) {
    size_t t = idx.back() + 1;
    idx.push_back(t);
    sums.push_back(sums.back() + new_data);

    //
    //

    update_tcp();
}
