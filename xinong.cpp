// ...existing code...
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

using namespace std;

/*
  Find a real root of an odd-degree polynomial using the bisection method.
  Input: degree n (assumed odd and < 50) and n+1 coefficients an ... a0
         coefficients are provided in descending order (an first).
  Returns a value within 1e-4 of a real root.
  Approach:
    - Evaluate polynomial via Horner's method.
    - Find initial interval [L,R] by expanding L=-1,R=1 (doubling magnitude)
      until f(L) and f(R) have opposite signs (or an endpoint is a root).
    - Apply bisection until interval width <= 1e-4.
  Assumptions:
    - There exists at least one real root (n is odd).
    - Coefficients fit in double.
*/

double eval_poly(const vector<double>& a, double x) {
    // Horner's method; a[0] = an (highest degree)
    double res = 0.0;
    for (double coef : a) {
        res = res * x + coef;
    }
    return res;
}

double poly_root(int n, const vector<double>& coeffs) {
    const double eps_interval = 1e-4;
    const double eps_value = 1e-14;
    double L = -1.0, R = 1.0;
    double fL = eval_poly(coeffs, L);
    double fR = eval_poly(coeffs, R);

    if (fabs(fL) < eps_value) return L;
    if (fabs(fR) < eps_value) return R;

    // Expand interval until signs differ (or reach large bound)
    int iter = 0;
    while (fL * fR > 0.0 && iter < 200) {
        L *= 2.0;
        R *= 2.0;
        fL = eval_poly(coeffs, L);
        fR = eval_poly(coeffs, R);
        if (fabs(fL) < eps_value) return L;
        if (fabs(fR) < eps_value) return R;
        ++iter;
    }
    // As a fallback (shouldn't happen for odd degree), try asymmetric expansion
    iter = 0;
    while (fL * fR > 0.0 && iter < 200) {
        L *= 2.0;
        fL = eval_poly(coeffs, L);
        if (fabs(fL) < eps_value) return L;
        ++iter;
    }

    // Now we have fL * fR <= 0 (or we exhausted attempts)
    // Bisection
    double mid = 0.0;
    while (R - L > eps_interval) {
        mid = 0.5 * (L + R);
        double fm = eval_poly(coeffs, mid);
        if (fabs(fm) < eps_value) return mid;
        if (fL * fm <= 0.0) {
            R = mid;
            fR = fm;
        } else {
            L = mid;
            fL = fm;
        }
    }
    return 0.5 * (L + R);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<double> coeffs(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> coeffs[i]; // input order: an, a{n-1}, ..., a0
    }

    double root = poly_root(n, coeffs);
    // print with enough precision so result is within 1e-4
    cout << fixed << setprecision(7) << root << "\n";
    return 0;
}
// ...existing code...