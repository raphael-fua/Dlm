/*
// #include "tobias.h"
// using namespace Rcpp;
// using namespace std;
// 
// // L2 CUSUM STATISTIC
// // [[Rcpp::export]]
// double EvalStatL2(NumericMatrix &S, int s, int t){
//   const int T = S.ncol()-1;
//   int n = S.nrow();
//   if(s==t)
//     stop("Statistic cannot be evaluated for s=t");
//   if(s>t){ 
//     // swap s,t
//     int temp = s;
//     s = t;
//     t = temp;
//   }
//   double res = 0;
//   for(int i : Range(0,n-1)){
//     double inner = pow(S(i,t)-S(i,s),2)/(t-s);
//     double outer = pow(S(i,T)-S(i,t)+S(i,s),2)/(T-t+s);
//     res += -pow(S(i,T),2)/T + inner  + outer;
//   }
//   if(res<0) // Avoid rounding error in noiseless case
//     res=0;
//   return(sqrt(res));
// }
// 
// // ONE STEP SEARCH
// // [[Rcpp::export]]
// List OneStepSearch(NumericMatrix &S, int shift=0, String method="advanced"){
//   int T = S.ncol()-1;
//   if(shift+3>=T)
//     stop("shift exceeds allowed area");
//   if(method == "full"){
//     double max = 0;
//     int ind = shift;
//     for(int t=shift+2; t<=T-1; t++){
//       double stat = EvalStatL2(S, shift, t);
//       if(stat > max){
//         max = stat;
//         ind = t;
//       }
//     }
//     return(List::create(Named("ind") = ind, Named("stat") = max));
//   }
//   if(method == "naive"){
//     return(NaiveOS(S, shift,-1, -1, -1, -1));
//   }
//   
//   if(method == "advanced"){
//     return(AdvancedOS(S, shift));
//   }
//   if(method == "combined"){
//     List naive = NaiveOS(S, shift, -1, -1, -1, -1);
//     List advanced = AdvancedOS(S, shift);
//     double naive_stat = naive["stat"];
//     double advanced_stat = advanced["stat"];
//     if(naive_stat > advanced_stat)
//       return(naive);
//     else
//       return(advanced);
//   }
//   stop("Choose method from 'full', 'naive', 'advanced', 'combined'");
//   return 0;
// }
// 
// 
// // NAIVE OPTIMISTIC SEARCH
// // [[Rcpp::export]]
// List NaiveOS(NumericMatrix &S, int shift=0, int l=-1, int s=-1,int r=-1, double stat_s=-1){
//   double step_size=0.5;
//   if(l==-1) l = shift;
//   if(r==-1) r = S.length()-1;
//   if(r-l <= 5){
//     // Full Search on the Interval l:r
//     int ind = l+2;
//     double max = 0;
//     for (int t=l+2; t<=r-1; t++){
//       double stat = EvalStatL2(S, shift, t);
//       if(stat>max){
//         max = stat;
//         ind = t;
//       }
//     }
//     return(List::create(Named("ind") = ind, Named("stat") = max));
//   }
//   // Initialization: In first iteration, s and stat_s not defined
//   if(s==-1) s = floor((l+step_size*r)/(1+step_size));
//   if(stat_s==-1) stat_s = EvalStatL2(S, shift, s);
//   
//   if(r-s>s-l){
//     // We define w such that l<s<w<r
//     int w = ceil(r-(r-s)*step_size);
//     double stat_w = EvalStatL2(S, shift, w);
//     if(stat_w > stat_s){
//       // We continue searching on s<w<r
//       return(NaiveOS(S, shift, s, w, r, stat_w));
//     }
//     // Else we continue searching on r<s<w
//     return(NaiveOS(S, shift, l, s, w, stat_s));
//   }
//   // Else we define w such that l<w<s<r
//   int w = floor(l+(s-l)*step_size);
//   double stat_w = EvalStatL2(S, shift, w);
//   if(stat_w > stat_s){
//     // We continue searching on l<w<s
//     return(NaiveOS(S, shift, l, w, s, stat_w));
//   }
//   // Else we continue searching on w<s<r
//   return(NaiveOS(S, shift, w, s, r, stat_s));
// }
// 
// // ADVANCED OPTIMISTIC SEARCH
// //[[Rcpp::export]]
// List AdvancedOS(NumericMatrix &S, int shift){
//   int T = S.ncol()-1;
//   if(T-shift < 32)
//     return(OneStepSearch(S, shift, "full"));
//   
//   // Prepare locations
//   int m = floor(log2((T-shift)/2));
//   IntegerVector location(2*m);
//   for(int i=0;i<m; i++){
//     location[i] = shift + pow(2,i);
//     location[2*m-(i+1)] = T - pow(2,i);
//   }
//   double mid = (shift+T)/2;
//   if(mid - pow(2,m) > pow(2,(m-1))){
//     // Middle segment too big: Add 3 points
//     location.push_back(mid);
//     location.push_back(T-pow(2,m));
//     location.push_back(shift+pow(2,m));
//   } else if((T-pow(2,m)) - (shift+pow(2,m)) < pow(2,m-1)){
//     // Middle segment too small: Only add middle point
//     location.push_back(mid);
//   } else{
//     // Middle segment okay: Add the 2 usual points
//     location.push_back(T-pow(2,m));
//     location.push_back(shift+pow(2,m));
//   }
//   sort(location.begin(), location.end());
//   
//   // Find maximum in locations
//   int ind = 1;
//   double max = 0;
//   double stat;
//   for (int l=1; l<location.length()-1;l++){
//     stat = EvalStatL2(S, shift, location[l]);
//     if(stat >= max){
//       max = stat;
//       ind = l;
//     }
//   }
//   // Search in the neighborhood of the maximum
//   return(NaiveOS(S, shift, location[ind-1], location[ind], location[ind+1], max));
// }
// 
// 
// 
// int runtimeAOS(Rcpp::NumericMatrix &S, double const& thresh) {
//     int t = -1;
//     int i = 4; // cannot call OneStepSearch if SS has too few columns
//     while((t == -1) and (i < S.ncol())) {
//         NumericMatrix SS = S(Range(0, 0), Range(0, i));
//         // Copying the row (0 to 1) and column (2 to 3) to the matrix m2
//         // NumericMatrix m2 = m( Range(0,1) , Range(2,3) );
//         List L = OneStepSearch(SS, 0, "combined");
//         double s = L["stat"];
//         Rcout << s << endl;
// 
//         if(s > thresh) {
//             t = L["ind"];
//         }
//         ++i;
//     }
//     return t;
// }
// 
// // std::vector<double> scoresAOS(Rcpp::NumericMatrix &S) {
// //     std::vector<double> maxs = {0.0};
// //     int i = 4; // cannot call OneStepSearch if SS has too few columns
// //     while(i < S.ncol()) {
// //         NumericMatrix SS = S(Range(0, 0), Range(0, i));
// //         List L = OneStepSearch(SS, 0, "combined");
// //         double s = L["stat"];
// //         maxs.push_back(s);
// //         ++i;
// //     }
// //     return maxs;
// // }
// 
// 
// std::vector<double> scoresAOS(Rcpp::NumericMatrix &S) {
//     std::vector<double> maxs = {0.0};
//     int i = 4; // cannot call OneStepSearch if SS has too few columns
//     while(i < S.ncol()) {
//         NumericMatrix SS = S(Range(0, 0), Range(0, i));
//         List L = OneStepSearch(SS, 0, "combined");
//         double s = L["stat"];
//         maxs.push_back(s);
//         ++i;
//     }
//     return maxs;
// }
// 
// 
// 
*/

#include "tobias.h"
using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
double EvalStatL2(NumericMatrix &S, int s, int t){
    const int T = S.ncol()-1;
    int n = S.nrow();
    if(s==t)
        stop("Statistic cannot be evaluated for s=t");
    if(s>t){ 
        // swap s,t
        int temp = s;
        s = t;
        t = temp;
    }
    double res = 0;
    for(int i : Range(0,n-1)){
        double inner = pow(S(i,t)-S(i,s),2)/(t-s);
        double outer = pow(S(i,T)-S(i,t)+S(i,s),2)/(T-t+s);
        res += -pow(S(i,T),2)/T + inner  + outer;
    }
    if(res<0) // Avoid rounding error in noiseless case
        res=0;
    return(sqrt(res));
}

// [[Rcpp::export]]
List OneStepSearch(NumericMatrix &S, int shift=0, String method="advanced"){
    int T = S.ncol()-1;
    if(shift+3>=T)
        stop("shift exceeds allowed area");
    if(method == "full"){
        double max = 0;
        int ind = shift;
        for(int t=shift+2; t<=T-1; t++){
            double stat = EvalStatL2(S, shift, t);
            if(stat > max){
                max = stat;
                ind = t;
            }
        }
        return(List::create(Named("ind") = ind, Named("stat") = max));
    }
    if(method == "naive"){
        return(NaiveOS(S, shift,-1, -1, -1, -1));
    }
    
    if(method == "advanced"){
        return(AdvancedOS(S, shift));
    }
    if(method == "combined"){
        List naive = NaiveOS(S, shift, -1, -1, -1, -1);
        List advanced = AdvancedOS(S, shift);
        double naive_stat = naive["stat"];
        double advanced_stat = advanced["stat"];
        if(naive_stat > advanced_stat)
            return(naive);
        else
            return(advanced);
    }
    stop("Choose method from 'full', 'naive', 'advanced', 'combined'");
    return 0;
}

// [[Rcpp::export]]
List NaiveOS(NumericMatrix &S, int shift=0, int l=-1, int s=-1,int r=-1, double stat_s=-1){
    double step_size=0.5;
    if(l==-1) l = shift;
    if(r==-1) r = S.length()-1;
    if(r-l <= 5){
        // Full Search on the Interval l:r
        int ind = l+2;
        double max = 0;
        for (int t=l+2; t<=r-1; t++){
            double stat = EvalStatL2(S, shift, t);
            if(stat>max){
                max = stat;
                ind = t;
            }
        }
        return(List::create(Named("ind") = ind, Named("stat") = max));
    }
    // Initialization: In first iteration, s and stat_s not defined
    if(s==-1) s = floor((l+step_size*r)/(1+step_size));
    if(stat_s==-1) stat_s = EvalStatL2(S, shift, s);
    
    if(r-s>s-l){
        // We define w such that l<s<w<r
        int w = ceil(r-(r-s)*step_size);
        double stat_w = EvalStatL2(S, shift, w);
        if(stat_w > stat_s){
            // We continue searching on s<w<r
            return(NaiveOS(S, shift, s, w, r, stat_w));
        }
        // Else we continue searching on r<s<w
        return(NaiveOS(S, shift, l, s, w, stat_s));
    }
    // Else we define w such that l<w<s<r
    int w = floor(l+(s-l)*step_size);
    double stat_w = EvalStatL2(S, shift, w);
    if(stat_w > stat_s){
        // We continue searching on l<w<s
        return(NaiveOS(S, shift, l, w, s, stat_w));
    }
    // Else we continue searching on w<s<r
    return(NaiveOS(S, shift, w, s, r, stat_s));
}

//[[Rcpp::export]]
List AdvancedOS(NumericMatrix &S, int shift){
    int T = S.ncol()-1;
    if(T-shift < 32)
        return(OneStepSearch(S, shift, "full"));
    
    // Prepare locations
    int m = floor(log2((T-shift)/2));
    IntegerVector location(2*m);
    for(int i=0;i<m; i++){
        location[i] = shift + pow(2,i);
        location[2*m-(i+1)] = T - pow(2,i);
    }
    double mid = (shift+T)/2;
    if(mid - pow(2,m) > pow(2,(m-1))){
        // Middle segment too big: Add 3 points
        location.push_back(mid);
        location.push_back(T-pow(2,m));
        location.push_back(shift+pow(2,m));
    } else if((T-pow(2,m)) - (shift+pow(2,m)) < pow(2,m-1)){
        // Middle segment too small: Only add middle point
        location.push_back(mid);
    } else{
        // Middle segment okay: Add the 2 usual points
        location.push_back(T-pow(2,m));
        location.push_back(shift+pow(2,m));
    }
    sort(location.begin(), location.end());
    
    // Find maximum in locations
    int ind = 1;
    double max = 0;
    double stat;
    for (int l=1; l<location.length()-1;l++){
        stat = EvalStatL2(S, shift, location[l]);
        if(stat >= max){
            max = stat;
            ind = l;
        }
    }
    // Search in the neighborhood of the maximum
    return(NaiveOS(S, shift, location[ind-1], location[ind], location[ind+1], max));
}

int runtimeAOS(Rcpp::NumericMatrix &S, double const& thresh) {
    int t = -1;
    int i = 4; // cannot call OneStepSearch if SS has too few columns
    while((t == -1) and (i < S.ncol())) {
        NumericMatrix SS = S(Range(0, 0), Range(0, i));
        // Copying the row (0 to 1) and column (2 to 3) to the matrix m2
        // NumericMatrix m2 = m( Range(0,1) , Range(2,3) );
        List L = OneStepSearch(SS, 0, "combined");
        double s = L["stat"];
        if(s > thresh) {
            t = i; // L["ind"] would be estimated change point
        }
        ++i;
    }
    return t;
}

std::vector<double> scoresAOS(Rcpp::NumericMatrix &S) {
    std::vector<double> maxs = {0.0};
    int i = 4; // cannot call OneStepSearch if SS has too few columns
    while(i < S.ncol()) {
        NumericMatrix SS = S(Range(0, 0), Range(0, i));
        List L = OneStepSearch(SS, 0, "combined");
        double s = L["stat"];
        maxs.push_back(s);
        ++i;
    }
    return maxs;
}

// NumericVector test(NumericVector &S){
//     NumericVector maxs = {};
//     int T = S.length();
//     int i = 1; // cannot call OneStepSearch if S has too few columns
//     while(i < T){
//         List L = OneStepSearch(S, "combined", i);
//         double s = L["stat"];
//         maxs.push_back(s);
//         ++i;
//     }
//     return maxs;
// }





