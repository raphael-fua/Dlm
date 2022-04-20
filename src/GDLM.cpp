#include "GDLM.h"
using namespace std;

GDLM::GDLM(int const& q,
           string const& stat_name,
           deque<double> &v,
           double const& thresh):
    Cpd(stat_name, {1}, {v[0]}, thresh, -1, -1),
    q (q),
    mIdx (1),
    mSums (1),
    tmpIdx ({-1}),
    tmpSums ({NAN}),
    k ({1})
{
    std::vector<int> v1 (q, -1);
    IntegerMatrix toCopy1(q, 1, v1.begin());
    mIdx = toCopy1;

    std::vector<double> v2 (q, NAN);
    NumericMatrix toCopy2(q, 1, v2.begin());
    mSums = toCopy2;


    double tmp = v.front();
    v.pop_front();
    Cpd::update(v);
    v.push_front(tmp);
}

void GDLM::print() const {
    Cpd::print();
    Rcpp::Rcout << "** q: " << q << endl;
    Rcpp::Rcout << "** mIdx:" << endl;
    for (auto a:mIdx){
        for(auto e:a){
            Rcpp::Rcout << e << " ";
        }
        Rcpp::Rcout << endl;
    }
    Rcpp::Rcout << "** mSums:" << endl;
    for (auto a:mSums){
        for(auto e:a){
            Rcpp::Rcout << e << " ";
        }
        Rcpp::Rcout << endl;
    }
    Rcpp::Rcout << "** tmpIdx: ";
    for (auto e:tmpIdx) {
        Rcpp::Rcout << e << " ";
    }
    Rcpp::Rcout << endl;

    Rcpp::Rcout << "** tmpSums: ";
    for (auto e:tmpSums) {
        Rcpp::Rcout << e << " ";
    }
    Rcpp::Rcout << endl;

    Rcpp::Rcout << "** k: ";
    for (auto e:k) {
        Rcpp::Rcout << e << " ";
    }
    Rcpp::Rcout << endl;
}

void GDLM::update(const double &new_data) {
    tmpIdx[0] = mIdx(0, 0);
    tmpSums[0]= mSums(0, 0);

    mIdx(1, 0) = mIdx(0, 0);
    mSums(1, 0) = mSums(0, 0);

    ++mIdx(0, 0);
    mSums(0, 0) += new_data;

    bool b_noZero = true;
    int zeroIDX = -1;
    for(int z = 0; z < k.size(); ++z) {
        if (k[z] == 0) {
            b_noZero = false;
            zeroIDX = z;
        }
    }

    if (b_noZero) {
        k.push_back(0);
        zeroIDX = k.size();

        std::vector<int> v1 (q, -1);
        IntegerMatrix toAdd1(q, 1, v1.begin());
        mIdx = cbind(mIdx, toAdd1);

        std::vector<double> v2 (q, NAN);
        NumericMatrix toAdd2(q, 1, v2.begin());
        mSums = cbind(mSums, toAdd1);

        tmpIdx.push_back(-1);
        tmpSums.push_back(NAN);
    }

    for (int i = 1; i < zeroIDX; ++i) {
        tmpIdx[i] = mIdx(0, i);
        tmpSums[i] = mSums(0, i);

        IntegerVector roIDX = mIdx( _ , i);
        roIDX.pop_back();
        roIDX.push_front(tmpIdx[i - 1]);
        mIdx(_, i) = roIDX;

        NumericVector roS = mSums( _ , i);
        roS.pop_back();
        roS.push_front(tmpSums[i - 1]);
        mIdx(_, i) = roS;

        if (k[i] == 0) {
            k[i] = 1;
        } else {
            k[i] = 0;
        }
    }
}














