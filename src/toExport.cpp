#include "toExport.h"

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



