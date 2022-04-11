#pragma once
#include "Dlmh.h"
#include <chrono>
//#include <vector>
// [[Rcpp::plugins("cpp11")]]

// [[Rcpp::export]]
void sayHi();

// [[Rcpp::export]]
double time_dlm(std::deque<double> data);

// // [[Rcpp::export]]
//std::vector<double> g();

// [[Rcpp::export]]
std::deque<double> scores(std::string stat_name, 
                          std::deque<double> data, 
                          double thresh
); 

// [[Rcpp::export]]
int runtime(std::string stat_name, 
            std::deque<double> data, 
            double thresh
);