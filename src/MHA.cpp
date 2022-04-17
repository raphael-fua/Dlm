#include "MHA.h"
using namespace std;


MHA::MHA(deque<double> &v, double const& alpha, double const& nu, int const& i): 
    Cpd("sMHA", 
        deque<size_t> {1}, 
        deque<double> {v[0]}, 
        0, -1, -1
    ),
    i(i), 
    pi(1 - 1 / pow(2, i)),
    k(0),
    ski(0.0),
    vki(0.0),
    vvki(0.0),
    cvki(0.0),
    alpha(alpha),
    nu(nu) 
{
    double tmp = v.front();
    v.pop_front();
    Cpd::update(v);
    v.push_front(tmp);
}


void MHA::update(const double &new_data) {
    size_t& T = idx[0];
    double& ST = sums[0];
    ++T;
    ST += new_data;
    
    if (T % int(pow(2, i)) == 0) {
        ++k;
        ski += pi * ST / k;
        if(k == 1) {
            vki = 0.0;
            vvki = 0.0;
            cvki = 0.0;
        } else {
            vki = sqrt(T) * (ski / (pi * T) - ST / T);
            vvki = double(k) / (double(k) + 1) * (vvki + 1 / (double(k) + 1));
            cvki = vki / sqrt(vvki);
            
            if((2 * pow(abs(cvki) - 1, 2) > thresh) and (t == -1)) {
                t = T;
                cp = (pow(2, i) - 1) * k;
            }
        }
        thresh = -2 * log(alpha * ((double(k) + 1) / (double(k) + 1 + nu) - double(k) / (double(k) + nu))) - log(2 * M_PI);
    }
    Rcpp::Rcout << "~new_data: " << new_data << endl;
    print();
    Rcpp::Rcout << endl;
}



void MHA::print() const {
    Cpd::print();
    Rcpp::Rcout << "** i: " << i << endl;
    Rcpp::Rcout << "** k: " << k << endl;
    Rcpp::Rcout << "** ski: " << ski << endl;
    Rcpp::Rcout << "** vki: " << vki << endl;
    Rcpp::Rcout << "** vvki: " << vvki << endl;
    Rcpp::Rcout << "** cvki: " << cvki << endl;
    Rcpp::Rcout << "** alpha: " << alpha << endl;
    Rcpp::Rcout << "** nu: " << nu << endl;
}
