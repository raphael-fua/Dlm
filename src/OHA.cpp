#include "OHA.h"
using namespace std;


OHA::OHA(deque<double> &v, double const& alpha, double const& nu):
    Cpd("sOHA", 
        deque<size_t> {1},
        deque<double> {v[0]},
        -2 * log(alpha / (1 + nu)) - log(2 * M_PI), 
        -1, 
        -1
    ),
    sHalf (0.0),
    alpha (alpha),
    nu (nu)
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
        
        if((2 * pow(abs(V) - 1, 2) > thresh) and (t == -1)) {
            t = idx[0];
            cp = t / 2;
        }
        
        double n = idx[0] / 2;
        thresh = -2 * log(alpha * ((n + 1) / (n + 1 + nu) - n / (n + nu))) - log(2 * M_PI);
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