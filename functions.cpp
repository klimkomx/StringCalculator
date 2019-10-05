//
// Created by Maxim on 01.10.2019.
//

const double EPS_M = 1e-9;

double abs(double a) {
    if (a < 0)
        return -1*a;
    else
        return a;
}

int abs(int a) {
    if (a < 0)
        return -1*a;
    else
        return a;
}

double ln(double a) {
    double x = (a - 1) / (a + 1);
    double ans = x, sans = 0.0, pow = x * x * x, nn = 3;
    for (; abs(ans - sans) > EPS_M; sans = ans, ans += pow / nn, pow *= x * x, nn += 2);
    return 2*ans;
}

double log(double a, double b) { // log b osn a
    if (a <= 0 || b <= 0 || a == 1.0) {
        throw "Logarithm is not defined in this values";
    }
    return ln(b) / ln(a);
}

double sin(double a) {
    double div = 1.0, mult = a, ans = 0.0, sans = -1.0, sign = 1.0, cnt = 2.0;
    for (; abs(sans - ans) > EPS_M; sans = ans, ans += sign * mult/div, div *= cnt * (cnt + 1), mult *= a * a, sign *= -1.0, cnt += 2.0);
    if (abs(ans) < EPS_M) return 0;
    return ans;
}

double cos(double a) {
    double div = 1.0, mult = 1.0, ans = 0.0, sans = -1.0, sign = 1.0, cnt = 1.0;
    for (; abs(sans - ans) > EPS_M; sans = ans, ans += sign * mult/div, div *= cnt * (cnt + 1), mult *= a * a, sign *= -1.0, cnt += 2.0);
    return ans;
}

double exp(double a) {
    double ans = 0.0, sans = -1.0, mult = 1.0, div = 1.0, cnt = 1.0;
    for (; abs(sans - ans) > EPS_M; sans = ans, ans += mult/div, mult *= a, div *= cnt, cnt += 1.0);
    return ans;
}

double pow(double a, double b) {
    if (a == 0) {
        if (b == 0) return 1;
        else return 0;
    }
    if (b < 0)
        return exp(ln(a) * (-b));
    else
        return exp(ln(a) * b);
}

double pow(double a, int b) {
    double ans = 1.0;
    int bc = abs(b);
    while (bc) {
        if (bc & 1) {
            ans *= a;
            bc--;
        } else {
            a *= a;
            bc >>= 1;
        }
    }
    return (b >= 0) ? ans : 1/ans;
}
