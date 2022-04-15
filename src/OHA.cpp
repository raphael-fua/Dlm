#include "OHA.h"
using namespace std;

//OHA::OHA(string const& stat_name, double const& thresh):
//    Cpd(stat_name, deque<size_t> {0}, deque<double> {0.0}, thresh, -1, -1),
//    sHalf (0)
//{}

OHA::OHA(deque<double> &v, double const& alpha):
    Cpd("sOHA", 
        deque<size_t> {1},
        deque<double> {v[0]},
        -2 * log(alpha) - log(2 * M_PI), 
        -1, 
        -1
    ),
    sHalf (0.0)
{
    double tmp = v.front();
    v.pop_front();
    Cpd::update(v);
    v.push_front(tmp);
}

    
    

void OHA::print() const {
    Cpd::print();
    cout << "* sHalf: " << sHalf << endl;
}



void OHA::update(const double &new_data) {

    ++idx[0];
    sums[0] += new_data;
    
    if (idx[0] % 2 == 0) {
        sHalf += sums[0] / idx[0];
        double V = sqrt(idx[0]) * (sHalf / (idx[0] / 2) - sums[0] / idx[0]);
        if(2 * pow(abs(V) - 1, 2) > thresh) {
            t = idx[0];
            cp = t / 2;
        }
    }
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