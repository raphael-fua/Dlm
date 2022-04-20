#pragma once
#include "Dlmh.h"
#include "OHA.h"
#include "MHA.h"
#include "GHA.h"
#include <chrono>
#include <string>
// [[Rcpp::plugins("cpp11")]]

// [[Rcpp::export]]
double time_dlm(std::deque<double> data);

// [[Rcpp::export]]
std::deque<double> scores(std::string stat_name, std::deque<double> data, double thresh); 

// [[Rcpp::export]]
int runtime(std::string stat_name, std::deque<double> data, double thresh);

// [[Rcpp::export]]
int runtimeOHA(std::deque<double> &data, double const& alpha, double const& nu);


void test_OHA_constr2 (std::deque<double> &v, double const& alpha, double const& nu);

// [[Rcpp::export]]
void test_MHA_constr2 (std::deque<double> &v, double const& alpha, double const& nu, int const& i);

// [[Rcpp::export]]
bool test_MHA_fpr (std::deque<double> &v, double const& alpha, double const& nu, int const& i);

// [[Rcpp::export]]
void test_GHA_constr2 (std::deque<double> &v, double const& thresh);

// [[Rcpp::export]]
int runtimeMHA(std::deque<double> &data, double const& alpha, double const& nu, int const& i);

// [[Rcpp::export]]
int runtimeGHA(std::deque<double> &v, double const& thresh);

// [[Rcpp::export]]
void compare_OHAvMHA1(std::deque<double> &data, double const& alpha, double const& nu);

// [[Rcpp::export]]
void test_GDLM_constr(int const& q, std::deque<double> &v, double const& thresh);













