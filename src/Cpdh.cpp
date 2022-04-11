#include "Cpdh.h"
using namespace std;

Cpdh::Cpdh(deque<double> const& maxs):
    Cpd("default_name", {0}, {0}, 0, 0, 0),
    maxs (maxs)
{}

void Cpdh::print() const {
    Cpd::print();
    cout << "** maxs: ";
    for(auto const& elt : maxs) {
        cout << elt << " ";
    }
    cout << endl;
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
