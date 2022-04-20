#pragma once
#include <Rcpp.h>
#include <vector>

Rcpp::List OneStepSearch(Rcpp::NumericMatrix &S, int shift, Rcpp::String method);
Rcpp::List AdvancedOS(Rcpp::NumericMatrix &S, int shift);
Rcpp::List NaiveOS(Rcpp::NumericMatrix &S, int shift, int l, int s,int r, double stat_s);
double EvalStatL2(Rcpp::NumericMatrix &S, int s, int t);

// [[Rcpp::export]]
int runtimeAOS(Rcpp::NumericMatrix &S, double const& thresh);

// [[Rcpp::export]]
std::vector<double> scoresAOS(Rcpp::NumericMatrix &S); 
