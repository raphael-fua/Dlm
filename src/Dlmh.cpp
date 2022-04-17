#include "Dlmh.h"
using namespace std;


Dlmh::Dlmh(string const& stat_name, deque<double> &v, double const& thresh):
    Cpd(stat_name, {1}, {v[0]}, thresh, -1, -1),
    Dlm({0, 0}, 0),
    Cpdh({0.0})
{
    double tmp = v.front();
    v.pop_front();
    Cpd::update(v);
    v.push_front(tmp);
}

void Dlmh::print() const {
    Cpd::print();

    //Line below shows protection offered par la virtualité de la classe Cpd
    //Rcpp::Rcout << Dlmh::cp << Cpd::cp << Dlm::cp << Cpdh::cp << endl;

    Rcpp::Rcout << "** checkpts: " << checkpts[0] << " " << checkpts[1] << endl;
    Rcpp::Rcout << "** p: " << p << endl;
    Rcpp::Rcout << "** maxs: ";
    for(auto const& elt : maxs) {
        Rcpp::Rcout << elt << " ";
    }
    Rcpp::Rcout << endl;
}

void Dlmh::update(double const& new_data) {
    int tmp = t;
    Dlm::update(new_data);
    if(tmp == -1) {
        update_maxs();
    }
}




