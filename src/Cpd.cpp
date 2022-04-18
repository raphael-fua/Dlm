#include "Cpd.h"
using namespace std;

Cpd::Cpd(const string &stat_name,
         const std::deque<size_t> &idx,
         const std::deque<double> &sums,
         const double &thresh,
         const int &t,
         const int &cp
) :
    stat_name (stat_name),
    idx (idx),
    sums (sums),
    thresh (thresh),
    t (t),
    cp (cp)
{};

deque<double> Cpd::stat() const {
    deque<double> res (idx.size() - 1, 0);
    size_t len (idx.size());

    if (stat_name == "cusum") {
        for (size_t i (0); i < len -1; ++i) {
        res[i] =
                sqrt(
                    double (idx[len - 1]) / double (idx[i] * (idx[len - 1] - idx[i]))
                ) * abs(double (idx[i]) / double (idx[len - 1]) * sums[len -1] - sums[i]);
        }
    }  else {
        cerr << "invalid stat_name" << endl;
    }

    return res;
}
void Cpd::update_tcp() {
    int T (idx.back());
    if ((t < 0) & (T != 1)) {
        deque<double> const& v (stat());

        int tmp = 0;
        if (isnan(sums[0])) {
            tmp = 1;
        }

        int idx_idx =
                distance(
                    v.begin() + tmp, max_element(v.begin() + tmp, v.end())
                ) + tmp;

        if (v[idx_idx] > thresh) {
            t = T;
            cp = idx[idx_idx];
        }
    }
}

void Cpd::print() const {
   Rcpp::Rcout << "*stat_name: " << stat_name << endl;
   Rcpp::Rcout << "* idx, sums:" << endl;
   for(int i = 0; i < idx.size(); i++) {
       Rcpp::Rcout <<"  " << idx[i] << ", " << sums[i] << endl;
   }

   Rcpp::Rcout << "*threshold: " << thresh << endl;
   Rcpp::Rcout << "*t: " << t << endl;
   Rcpp::Rcout << "*cp: " << cp << endl;
}

void Cpd::update(const deque<double> &v) {
    for(int i = 0; i < v.size(); i++) {
        update(v[i]);
    }
}














