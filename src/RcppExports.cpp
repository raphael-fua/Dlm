// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// isZero
bool isZero(double x);
RcppExport SEXP _Dlm_isZero(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(isZero(x));
    return rcpp_result_gen;
END_RCPP
}
// isWhole
bool isWhole(double x);
RcppExport SEXP _Dlm_isWhole(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(isWhole(x));
    return rcpp_result_gen;
END_RCPP
}
// time_dlm
double time_dlm(std::deque<double> data);
RcppExport SEXP _Dlm_time_dlm(SEXP dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::deque<double> >::type data(dataSEXP);
    rcpp_result_gen = Rcpp::wrap(time_dlm(data));
    return rcpp_result_gen;
END_RCPP
}
// scores
std::deque<double> scores(std::string stat_name, std::deque<double> data, double thresh);
RcppExport SEXP _Dlm_scores(SEXP stat_nameSEXP, SEXP dataSEXP, SEXP threshSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type stat_name(stat_nameSEXP);
    Rcpp::traits::input_parameter< std::deque<double> >::type data(dataSEXP);
    Rcpp::traits::input_parameter< double >::type thresh(threshSEXP);
    rcpp_result_gen = Rcpp::wrap(scores(stat_name, data, thresh));
    return rcpp_result_gen;
END_RCPP
}
// runtime
int runtime(std::string stat_name, std::deque<double> data, double thresh);
RcppExport SEXP _Dlm_runtime(SEXP stat_nameSEXP, SEXP dataSEXP, SEXP threshSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type stat_name(stat_nameSEXP);
    Rcpp::traits::input_parameter< std::deque<double> >::type data(dataSEXP);
    Rcpp::traits::input_parameter< double >::type thresh(threshSEXP);
    rcpp_result_gen = Rcpp::wrap(runtime(stat_name, data, thresh));
    return rcpp_result_gen;
END_RCPP
}
// runtimeOHA
int runtimeOHA(std::deque<double>& data, double const& alpha, double const& nu);
RcppExport SEXP _Dlm_runtimeOHA(SEXP dataSEXP, SEXP alphaSEXP, SEXP nuSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::deque<double>& >::type data(dataSEXP);
    Rcpp::traits::input_parameter< double const& >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< double const& >::type nu(nuSEXP);
    rcpp_result_gen = Rcpp::wrap(runtimeOHA(data, alpha, nu));
    return rcpp_result_gen;
END_RCPP
}
// GetLastIndex
std::deque<size_t> GetLastIndex(int n);
RcppExport SEXP _Dlm_GetLastIndex(SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    rcpp_result_gen = Rcpp::wrap(GetLastIndex(n));
    return rcpp_result_gen;
END_RCPP
}
// printIndex
void printIndex(int n);
RcppExport SEXP _Dlm_printIndex(SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    printIndex(n);
    return R_NilValue;
END_RCPP
}
// test_MHA_constr2
void test_MHA_constr2(std::deque<double>& v, double const& alpha, double const& nu, int const& i);
RcppExport SEXP _Dlm_test_MHA_constr2(SEXP vSEXP, SEXP alphaSEXP, SEXP nuSEXP, SEXP iSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::deque<double>& >::type v(vSEXP);
    Rcpp::traits::input_parameter< double const& >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< double const& >::type nu(nuSEXP);
    Rcpp::traits::input_parameter< int const& >::type i(iSEXP);
    test_MHA_constr2(v, alpha, nu, i);
    return R_NilValue;
END_RCPP
}
// test_MHA_fpr
bool test_MHA_fpr(std::deque<double>& v, double const& alpha, double const& nu, int const& i);
RcppExport SEXP _Dlm_test_MHA_fpr(SEXP vSEXP, SEXP alphaSEXP, SEXP nuSEXP, SEXP iSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::deque<double>& >::type v(vSEXP);
    Rcpp::traits::input_parameter< double const& >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< double const& >::type nu(nuSEXP);
    Rcpp::traits::input_parameter< int const& >::type i(iSEXP);
    rcpp_result_gen = Rcpp::wrap(test_MHA_fpr(v, alpha, nu, i));
    return rcpp_result_gen;
END_RCPP
}
// test_GHA_constr2
void test_GHA_constr2(std::deque<double>& v, double const& thresh);
RcppExport SEXP _Dlm_test_GHA_constr2(SEXP vSEXP, SEXP threshSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::deque<double>& >::type v(vSEXP);
    Rcpp::traits::input_parameter< double const& >::type thresh(threshSEXP);
    test_GHA_constr2(v, thresh);
    return R_NilValue;
END_RCPP
}
// runtimeMHA
int runtimeMHA(std::deque<double>& data, double const& alpha, double const& nu, int const& i);
RcppExport SEXP _Dlm_runtimeMHA(SEXP dataSEXP, SEXP alphaSEXP, SEXP nuSEXP, SEXP iSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::deque<double>& >::type data(dataSEXP);
    Rcpp::traits::input_parameter< double const& >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< double const& >::type nu(nuSEXP);
    Rcpp::traits::input_parameter< int const& >::type i(iSEXP);
    rcpp_result_gen = Rcpp::wrap(runtimeMHA(data, alpha, nu, i));
    return rcpp_result_gen;
END_RCPP
}
// runtimeGHA
int runtimeGHA(std::deque<double>& v, double const& thresh);
RcppExport SEXP _Dlm_runtimeGHA(SEXP vSEXP, SEXP threshSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::deque<double>& >::type v(vSEXP);
    Rcpp::traits::input_parameter< double const& >::type thresh(threshSEXP);
    rcpp_result_gen = Rcpp::wrap(runtimeGHA(v, thresh));
    return rcpp_result_gen;
END_RCPP
}
// scoresGHA
std::deque<double> scoresGHA(std::deque<double>& v);
RcppExport SEXP _Dlm_scoresGHA(SEXP vSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::deque<double>& >::type v(vSEXP);
    rcpp_result_gen = Rcpp::wrap(scoresGHA(v));
    return rcpp_result_gen;
END_RCPP
}
// compare_OHAvMHA1
void compare_OHAvMHA1(std::deque<double>& data, double const& alpha, double const& nu);
RcppExport SEXP _Dlm_compare_OHAvMHA1(SEXP dataSEXP, SEXP alphaSEXP, SEXP nuSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::deque<double>& >::type data(dataSEXP);
    Rcpp::traits::input_parameter< double const& >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< double const& >::type nu(nuSEXP);
    compare_OHAvMHA1(data, alpha, nu);
    return R_NilValue;
END_RCPP
}
// EvalStatL2
double EvalStatL2(NumericMatrix& S, int s, int t);
RcppExport SEXP _Dlm_EvalStatL2(SEXP SSEXP, SEXP sSEXP, SEXP tSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix& >::type S(SSEXP);
    Rcpp::traits::input_parameter< int >::type s(sSEXP);
    Rcpp::traits::input_parameter< int >::type t(tSEXP);
    rcpp_result_gen = Rcpp::wrap(EvalStatL2(S, s, t));
    return rcpp_result_gen;
END_RCPP
}
// OneStepSearch
List OneStepSearch(NumericMatrix& S, int shift, String method);
RcppExport SEXP _Dlm_OneStepSearch(SEXP SSEXP, SEXP shiftSEXP, SEXP methodSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix& >::type S(SSEXP);
    Rcpp::traits::input_parameter< int >::type shift(shiftSEXP);
    Rcpp::traits::input_parameter< String >::type method(methodSEXP);
    rcpp_result_gen = Rcpp::wrap(OneStepSearch(S, shift, method));
    return rcpp_result_gen;
END_RCPP
}
// NaiveOS
List NaiveOS(NumericMatrix& S, int shift, int l, int s, int r, double stat_s);
RcppExport SEXP _Dlm_NaiveOS(SEXP SSEXP, SEXP shiftSEXP, SEXP lSEXP, SEXP sSEXP, SEXP rSEXP, SEXP stat_sSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix& >::type S(SSEXP);
    Rcpp::traits::input_parameter< int >::type shift(shiftSEXP);
    Rcpp::traits::input_parameter< int >::type l(lSEXP);
    Rcpp::traits::input_parameter< int >::type s(sSEXP);
    Rcpp::traits::input_parameter< int >::type r(rSEXP);
    Rcpp::traits::input_parameter< double >::type stat_s(stat_sSEXP);
    rcpp_result_gen = Rcpp::wrap(NaiveOS(S, shift, l, s, r, stat_s));
    return rcpp_result_gen;
END_RCPP
}
// AdvancedOS
List AdvancedOS(NumericMatrix& S, int shift);
RcppExport SEXP _Dlm_AdvancedOS(SEXP SSEXP, SEXP shiftSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix& >::type S(SSEXP);
    Rcpp::traits::input_parameter< int >::type shift(shiftSEXP);
    rcpp_result_gen = Rcpp::wrap(AdvancedOS(S, shift));
    return rcpp_result_gen;
END_RCPP
}
// runtimeAOS
int runtimeAOS(Rcpp::NumericMatrix& S, double const& thresh);
RcppExport SEXP _Dlm_runtimeAOS(SEXP SSEXP, SEXP threshSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix& >::type S(SSEXP);
    Rcpp::traits::input_parameter< double const& >::type thresh(threshSEXP);
    rcpp_result_gen = Rcpp::wrap(runtimeAOS(S, thresh));
    return rcpp_result_gen;
END_RCPP
}
// scoresAOS
std::vector<double> scoresAOS(Rcpp::NumericMatrix& S);
RcppExport SEXP _Dlm_scoresAOS(SEXP SSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix& >::type S(SSEXP);
    rcpp_result_gen = Rcpp::wrap(scoresAOS(S));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_Dlm_isZero", (DL_FUNC) &_Dlm_isZero, 1},
    {"_Dlm_isWhole", (DL_FUNC) &_Dlm_isWhole, 1},
    {"_Dlm_time_dlm", (DL_FUNC) &_Dlm_time_dlm, 1},
    {"_Dlm_scores", (DL_FUNC) &_Dlm_scores, 3},
    {"_Dlm_runtime", (DL_FUNC) &_Dlm_runtime, 3},
    {"_Dlm_runtimeOHA", (DL_FUNC) &_Dlm_runtimeOHA, 3},
    {"_Dlm_GetLastIndex", (DL_FUNC) &_Dlm_GetLastIndex, 1},
    {"_Dlm_printIndex", (DL_FUNC) &_Dlm_printIndex, 1},
    {"_Dlm_test_MHA_constr2", (DL_FUNC) &_Dlm_test_MHA_constr2, 4},
    {"_Dlm_test_MHA_fpr", (DL_FUNC) &_Dlm_test_MHA_fpr, 4},
    {"_Dlm_test_GHA_constr2", (DL_FUNC) &_Dlm_test_GHA_constr2, 2},
    {"_Dlm_runtimeMHA", (DL_FUNC) &_Dlm_runtimeMHA, 4},
    {"_Dlm_runtimeGHA", (DL_FUNC) &_Dlm_runtimeGHA, 2},
    {"_Dlm_scoresGHA", (DL_FUNC) &_Dlm_scoresGHA, 1},
    {"_Dlm_compare_OHAvMHA1", (DL_FUNC) &_Dlm_compare_OHAvMHA1, 3},
    {"_Dlm_EvalStatL2", (DL_FUNC) &_Dlm_EvalStatL2, 3},
    {"_Dlm_OneStepSearch", (DL_FUNC) &_Dlm_OneStepSearch, 3},
    {"_Dlm_NaiveOS", (DL_FUNC) &_Dlm_NaiveOS, 6},
    {"_Dlm_AdvancedOS", (DL_FUNC) &_Dlm_AdvancedOS, 2},
    {"_Dlm_runtimeAOS", (DL_FUNC) &_Dlm_runtimeAOS, 2},
    {"_Dlm_scoresAOS", (DL_FUNC) &_Dlm_scoresAOS, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_Dlm(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
