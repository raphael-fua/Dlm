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
// test_OHA_constr2
void test_OHA_constr2(std::deque<double>& v, double const& alpha, double const& nu);
RcppExport SEXP _Dlm_test_OHA_constr2(SEXP vSEXP, SEXP alphaSEXP, SEXP nuSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::deque<double>& >::type v(vSEXP);
    Rcpp::traits::input_parameter< double const& >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< double const& >::type nu(nuSEXP);
    test_OHA_constr2(v, alpha, nu);
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

static const R_CallMethodDef CallEntries[] = {
    {"_Dlm_isZero", (DL_FUNC) &_Dlm_isZero, 1},
    {"_Dlm_isWhole", (DL_FUNC) &_Dlm_isWhole, 1},
    {"_Dlm_time_dlm", (DL_FUNC) &_Dlm_time_dlm, 1},
    {"_Dlm_scores", (DL_FUNC) &_Dlm_scores, 3},
    {"_Dlm_runtime", (DL_FUNC) &_Dlm_runtime, 3},
    {"_Dlm_runtimeOHA", (DL_FUNC) &_Dlm_runtimeOHA, 3},
    {"_Dlm_test_OHA_constr2", (DL_FUNC) &_Dlm_test_OHA_constr2, 3},
    {"_Dlm_test_MHA_constr2", (DL_FUNC) &_Dlm_test_MHA_constr2, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_Dlm(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
