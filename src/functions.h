#pragma once
#include <iostream> // needed for Rcpp::Rcout in void print(...)
#include <cmath> // needed for floor in bool isWhole(...)
#include <deque> // otherwise, the compiler does not understand std::deque
#include <string>
#include <Rcpp.h>

// [[Rcpp::export]]
bool isZero(double x);

// [[Rcpp::export]]
bool isWhole(double x);

template <typename T>
void print(const std::deque<T> &v) {
    for(auto const& elt:v) {
        Rcpp::Rcout << elt << " ";
    }
}


