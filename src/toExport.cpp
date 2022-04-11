#include "toExport.h"

void sayHi () {
    std::cout << "hello cruel world" << std::endl;
}

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


//std::vector<double> g() {
//    std::vector<double> res = {0.0, 1.0};
//    return res;
//}



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