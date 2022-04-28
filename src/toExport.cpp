#include "toExport.h"



std::deque<size_t> GetLastIndex(int n) {
    std::deque<double> v(n, 0);
    Dlm dlm("cusum", v, INFINITY);
    return dlm.idx;
}


void printIndex(int n) {
    Dlm dlm({5, 6}, 7);
    for(auto e:dlm.idx) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < n; ++i) {
        dlm.update(0);
        for(auto e:dlm.idx) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
}


double time_dlm(std::deque<double> data){
    Rcpp::Rcout << "emy coeur" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    Dlm dlm("cusum", data, 10);
    dlm.print();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    
    double res = duration.count();
    return res;
}
std::deque<double> scores(std::string stat_name, std::deque<double> data, double thresh) {
    Dlmh dlmh(stat_name, data, thresh);
    return dlmh.maxs;
}


int runtime(std::string stat_name, std::deque<double> data, double thresh) {
    Dlm dlm(stat_name, data, thresh);
    return dlm.t;
}

int runtimeOHA(std::deque<double> &data, double const& alpha, double const& nu) {
    OHA oha(data, alpha, nu);
    return oha.t;
}
//void test_OHA_constr2 (std::deque<double> &v, double const& alpha, double const& nu) {
void test_OHA_constr2 (std::deque<double> &v, double const& alpha, double const& nu) {
    OHA oha(v, alpha, nu);
    oha.print();
}
    
// below: only makes sense if I call print in MHA::update(double)    
void test_MHA_constr2 (std::deque<double> &v, double const& alpha, double const& nu, int const & i) {
    MHA mha(v, alpha, nu, i);
    mha.print();
}
bool test_MHA_fpr (std::deque<double> &v, double const& alpha, double const& nu, int const & i) {
    MHA mha(v, alpha, nu, i);
    return(mha.t == -1);
}

void test_GHA_constr2 (std::deque<double> &v, double const& thresh) {
    GHA gha(v, thresh);
    gha.print();
}

int runtimeMHA(std::deque<double> &data, double const& alpha, double const& nu, int const& i) {
    MHA mha(data, alpha, nu, i);
    return mha.t;
}

int runtimeGHA(std::deque<double> &v, double const& thresh) {
    GHA gha(v, thresh);
    return gha.t;
}

std::deque<double> scoresGHA(std::deque<double> &v) {
    std::deque<double> maxs = {0.0};
    std::deque<double> tmp = {v[0]};
    GHA gha(tmp, INFINITY);
    maxs.push_back(gha.Z);
    for(int i = 1; i < v.size(); ++i) {
        gha.update(v[i]);
        maxs.push_back(gha.Z);
    }
    return maxs;
}



void compare_OHAvMHA1(std::deque<double> &data, double const& alpha, double const& nu) {
    OHA oha(data, alpha, nu);
    MHA mha(data, alpha, nu, 1);

    oha.print();
    Rcpp::Rcout << "------------------------------" << std::endl;
    mha.print();
}