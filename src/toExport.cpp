#include "toExport.h"

double time_dlm(std::deque<double> data){
    std::cout << "emy coeur" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    Dlm dlm("cusum", data, 10);
    dlm.print();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    
    double res = duration.count();
    return res;
}

std::deque<double> scores(std::string stat_name, 
                          std::deque<double> data, 
                          double thresh) {
    Dlmh dlmh(stat_name, data, thresh);
    return dlmh.maxs;
}

int runtime(std::string stat_name, 
            std::deque<double> data, 
            double thresh) {
    Dlmh dlm(stat_name, data, thresh);
    return dlm.t;
}

int runtimeOHA(std::deque<double> &data, double const& alpha, double const& nu) {
    OHA oha(data, alpha, nu);
    return oha.t;
}

void test_OHA_constr2 (std::deque<double> &v, double const& alpha, double const& nu) {
    OHA oha(v, alpha, nu);
    oha.print();
}
    
    
    