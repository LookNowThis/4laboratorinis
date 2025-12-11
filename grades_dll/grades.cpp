#define GRADES_DLL_EXPORTS
#include "grades.h"
#include <algorithm>

double grades_vidurkis(const std::vector<int>& v) {
    if (v.empty()) return 0.0;
    double s = 0.0;
    for (int x : v) s += x;
    return s / v.size();
}

double grades_mediana(const std::vector<int>& v) {
    if (v.empty()) return 0.0;
    std::vector<int> t = v;
    std::sort(t.begin(), t.end());
    const int n = static_cast<int>(t.size());
    if (n % 2 == 0) return (t[n/2 - 1] + t[n/2]) / 2.0;
    return static_cast<double>(t[n/2]);
}
//pabandau
