#pragma once
#include "functions.h"

class Cpd {
public:
    std::string stat_name;
    std::deque<size_t> idx;
    std::deque<double> sums;
    double thresh;
    int t;
    int cp;

    Cpd(std::string const& stat_name,
        std::deque<size_t> const& idx,
        std::deque<double> const& sums,
        double const& thresh,
        int const& t,
        int const& cp
    );


    std::deque<double> stat() const;
    void update_tcp();
    void print() const;

    virtual void update(double const& new_data) = 0;
    virtual void update(std::deque<double> const& v);
        // must be called this way: obj.Cpd::uptade
        // why: because Class::update(double) shadows
        // Cpd::update(deque<double>) where obj is of type Class
        // Remember, if a virtual method is redefined, it masks everything above
        // it independently of the parameters received by the method!

};












