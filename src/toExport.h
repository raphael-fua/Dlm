#pragma once
#include "Dlmh.h"
#include "OHA.h"
#include <chrono>
#include <string>
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

// [[Rcpp::export]]
double get_sHalf(std::string const& stat_name, double const& thresh);

// [[Rcpp::export]]
void test_update(std::string const& stat_name, 
             double const& thresh, 
             std::deque<double>& data
);