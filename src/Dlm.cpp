#include "Dlm.h"
using namespace std;

Dlm::Dlm(deque<std::size_t> const& checkpts, size_t const& p):
    Cpd("default_name", {0}, {0}, 0, 0, 0),
    checkpts (checkpts),
    p (p)
{}

Dlm::Dlm(string const& stat_name, deque<double> &v, double const& thresh):
    Cpd(stat_name, {1}, {v[0]}, thresh, -1, -1),

    checkpts ({0, 0}),
    p (0)
{
    double tmp = v.front();
    v.pop_front();
    Cpd::update(v);
    v.push_front(tmp);
}

void Dlm::print() const {
    Cpd::print();
    Rcpp::Rcout << "** checkpts: " << checkpts[0] << " " << checkpts[1] << endl;
    Rcpp::Rcout << "** p: " << p << endl;
}

size_t Dlm::peaks() const {
    double n = idx.back() - checkpts[0];
    double len = 3 * pow(2, p);

    int i = 0;
    while (true) {
        if (isWhole(n / len * (3 * pow(2, i)))) {
            break;
        }
        i++;
    }
    size_t res = -2 * i + 5 + 2 * p;
    return(res);
}

void Dlm::update(const double &new_data) {

    size_t t = idx.back() + 1;
    idx.push_back(t);
    sums.push_back(sums.back() + new_data);

    if(t > 8) {
        if (t == checkpts[1]) {
            p++;
            checkpts[0] = checkpts[1];
            checkpts[1] = checkpts[0] + 3 * pow(2, p);
            idx.push_front(0);
            sums.push_front(NAN);
        } else {
             if(idx.size() <= peaks()){
                 cerr << "idx.size() should be greater than peaks()" << endl;
             }
             size_t k = idx.size() - peaks();
             idx.erase(idx.begin() + k - 1); // erase the kth element
             sums.erase(sums.begin() + k - 1);
        }
    } else {
        if ((t == 4) || (t == 7)) {
            idx.push_front(0);
            sums.push_front(NAN);
        } else if ((t == 5) || (t == 6)) {
            idx.pop_front();
            sums.pop_front();
        } else if (t == 8) {
            idx.erase(idx.begin() + 2);
            sums.erase(sums.begin() + 2);
            checkpts = {7, 13};
            p = 1;
        }
    }
    update_tcp();
}
