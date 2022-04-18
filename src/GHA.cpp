#include "GHA.h"
using namespace std;

GHA::GHA(deque<double> &v, double const& thresh):
    Cpd("sGHA",
        deque<size_t> {1},
        deque<double> {v[0]},
        thresh, -1, -1
    ),
    v_i({1}),
    v_pi({0.5}),
    v_k({0}),
    v_ski({0.0}),
    v_vki({0.0}),
    v_vvki({0.0}),
    v_cvki({0.0}),
    Z(0.0)
{
    double tmp = v.front();
    v.pop_front();
    Cpd::update(v);
    v.push_front(tmp);
}

void GHA::update(const double &new_data) {
    size_t& T = idx[0];
    double& ST = sums[0];
    ++T;
    ST += new_data;
    
    for(int j = 0; j < v_i.size(); ++j) {   
        
        const int& i = v_i[j];
        const double& pi = v_pi[j];
        
        int& k = v_k[j];
        double& ski = v_ski[j];
        double& vki = v_vki[j];
        double& vvki = v_vvki[j];
        double& cvki = v_cvki[j];
    
        if (T % int(pow(2, i)) == 0) {
            ++k;
            ski += pi * ST / k;
            if(k != 1) {
                vki = sqrt(T) * (ski / (pi * T) - ST / T);
                vvki = double(k) / (double(k) + 1) * (vvki + 1 / (double(k) + 1));
                cvki = vki / sqrt(vvki);
            }
        }
    }
    Z = 0;
    int i = 0;
    int k = 0;
    for(int j = 0; j < v_i.size(); ++j) {
        double candidate = pow(v_cvki[j], 2);
        if(candidate > Z) {
            Z = candidate;
            i = v_i[j];
            k = v_k[j];
        }
    }
    
    if((Z > thresh) and (t == -1)) {
        t = T;
        cp = (pow(2, i) - 1) * k;
    }
    
    int imax = v_i.back();
    if(T % int(pow(2, imax + 1)) == 0) {
        v_i.push_back(imax + 1);
        v_pi.push_back(1 - 1 / pow(imax + 1, 2));
        v_k.push_back(1);
        v_ski.push_back(v_pi.back() * ST / v_k.back()); // (1.2.0.2)
        v_vki.push_back(0.0);
        v_vvki.push_back(0.0);
        v_cvki.push_back(0.0);
    }
}
void GHA::print() const {
    Cpd::print();
    
    Rcpp::Rcout << "** v_i: ";
    for(auto e:v_i) {
        Rcpp::Rcout << e << " ";
    }
    Rcpp::Rcout << endl;
    
    Rcpp::Rcout << "** v_pi: ";
    for(auto e:v_pi) {
        Rcpp::Rcout << e << " ";
    }
    Rcpp::Rcout << endl;
     
    Rcpp::Rcout << "** v_k: ";
    for(auto e:v_k) {
        Rcpp::Rcout << e << " ";
    }
    Rcpp::Rcout << endl;
        
    Rcpp::Rcout << "** v_ski: ";
    for(auto e:v_ski) {
        Rcpp::Rcout << e << " ";
    }
    Rcpp::Rcout << endl;
        
    Rcpp::Rcout << "** v_vki: ";
    for(auto e:v_vki) {
        Rcpp::Rcout << e << " ";
    }
    Rcpp::Rcout << endl;
 
    Rcpp::Rcout << "** v_vvki: ";
    for(auto e:v_vvki) {
        Rcpp::Rcout << e << " ";
    }
    Rcpp::Rcout << endl;
    
    Rcpp::Rcout << "** v_cvki: ";
    for(auto e:v_cvki) {
        Rcpp::Rcout << e << " ";
    }
    Rcpp::Rcout << endl;
}