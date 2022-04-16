#pragma once
#include "Dlmh.h"
#include "OHA.h"
#include <chrono>
#include <string>
// [[Rcpp::plugins("cpp11")]]


// [[Rcpp::export]]
double time_dlm(std::deque<double> data);

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
int runtimeOHA(std::deque<double> &data, double const& alpha, double const& nu);

// [[Rcpp::export]]
void test_OHA_constr2 (std::deque<double> &v, double const& alpha, double const& nu);



