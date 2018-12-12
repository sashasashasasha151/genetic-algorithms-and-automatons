#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int n;

double out(int k, double v) {
    if (k != 0) {
        cout << 0;
    } else {
        cout << v;
    }

    for (int i = 1; i < n; ++i) {
        if (i != k) {
            cout << " " << 0;
        } else {
            cout << " " << v;
        }
    }
    cout << endl << flush;

    double d;
    cin >> d;
    return d;
}

double tern(int k, double l, double r) {
    for (int i = 0; i < 40; ++i) {
        double ll = (l * 2 + r) / 3;
        double rr = (l + r * 2) / 3;
        if (out(k, ll) < out(k, rr)) {
            r = rr;
        } else {
            l = ll;
        }
    }
    return (l + r) / 2;
}

double min_l_r(int k, double x1, double x2) {
    double x3 = (x1 + x2) / 2;
    double y1 = out(k, x1);
    double y2 = out(k, x2);
    double y3 = out(k, x3);

    double y3_line = (x2 * y1 - x1 * y2 - (y1 - y2) * x3) / (x2 - x1);

    if (y3 < y3_line) {
        return tern(k, x1, x2);
    } else {
        if(y1<y2) {
            return x1;
        } else {
            return x2;
        }
    }
}

double get_min(int k) {
    double min = min_l_r(k, 0.0, 1.0 / 20);
    for (int i = 1; i < 20; ++i) {
        double m = min_l_r(k, (double) i / 20, (i + 1.0) / 20);
        if (out(k,m) < out(k,min)) {
            min = m;
        }
    }
    return min;
}

int main() {
    cin >> n;
    vector<double> ans;
    for (int i = 0; i < n; ++i) {
        ans.push_back(get_min(i));
    }

    for (int i = 0; i < n - 1; ++i) {
        cout << ans[i] << " ";
    }
    cout << ans[n - 1] << endl << flush;

    double d;
    cin >> d;
    cout << "minimum " << d << endl << flush;
    return 0;
}