#include "functions.h"
using namespace std;

bool isZero(double x) {
    return abs(x) < 1e-10;
}

bool isWhole(double x) {
    return isZero(x - floor(x));
}
