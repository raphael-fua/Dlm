#include "OHA.h"
using namespace std;

OHA::OHA(string const& stat_name, double const& thresh):
    Cpd(stat_name, deque<size_t> {0}, deque<double> {0.0}, thresh, -1, -1),
    sHalf (0)
{}



void OHA::print() const {
    Cpd::print();
    cout << "* sHalf: " << sHalf << endl;
}



void OHA::update(const double &new_data) {

    ++idx[0];
    sums[0] += new_data;
    
    if (idx[0] % 2 == 0) {
        sHalf += sums[0] / idx[0];
    }
    
    // !! Still need to implement t & cp update update_tcp() !!
}



//OHA::OHA(string const& stat_name, deque<double> &v, double const& thresh):
//    Cpd(stat_name, {1}, {v[0]}, thresh, -1, -1),
//    
//    checkpts ({0, 0}),
//    p (0)
//{
//    double tmp = v.front();
//    v.pop_front();
//    Cpd::update(v);
//    v.push_front(tmp);
//}