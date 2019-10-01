//
// Created by Maxim on 01.10.2019.
//

const int EPS = 1e-9;

double abs(double a) {
    if (a < 0)
        return -1*a;
    else
        return a;
}

double ln(double a) {
    double x = (a - 1) / (a + 1);
    double ans = x, sans = 0.0, pow = x * x * x, nn = 3;
    for (; abs(ans - sans) > EPS; sans = ans, ans += pow / nn, pow *= x * x, nn += 2);
    return ans;
}

double log(double a, double b) { // log b osn a
    if (a <= 0 || b <= 0 || a == 1) {
        throw "Logarithm is not defined in this values";
    }
    return ln(b) / ln(a);
}

double sin(double a) {
    double div = 1.0, mult = a, ans = 0.0, sans = -1.0, sign = 1.0, cnt = 2.0;
    for (; abs(sans - ans) > EPS; sans = ans, ans += sign * mult/div, div *= cnt * (cnt + 1), mult *= a * a, sign *= -1.0, cnt += 2.0);
    if (abs(ans) < EPS) return 0;
    return ans;
}

double cos(double a) {
    double div = 1.0, mult = 1.0, ans = 0.0, sans = -1.0, sign = 1.0, cnt = 1.0;
    for (; abs(sans - ans) > EPS; sans = ans, ans += sign * mult/div, div *= cnt * (cnt + 1), mult *= a * a, sign *= -1.0, cnt += 2.0);
    return ans;
}

double exp(double a) {
    double ans = 0.0, sans = -1.0, mult = 1.0, div = 1.0, cnt = 1.0;
    for (; abs(sans - ans) > EPS; sans = ans, ans += mult/div, mult *= a, div *= cnt, cnt += 1.0);
    return ans;
}

double pow(double a, double b) {
    return exp(ln(a) * b);
}

double pow(double a, int b) {
    double ans = 1.0;
    while (b) {
        if (b & 1) {
            ans *= a;
            b--;
        } else {
            a *= a;
            b >>= 1;
        }
    }
    return ans;
}