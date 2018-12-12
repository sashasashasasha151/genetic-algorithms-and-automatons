#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Vertex {
    int to0;
    int to1;
    int ind0;
    int ind1;
};

vector<Vertex> aut;
vector<vector<long double>> sys;

int main() {
//    ifstream cin("continuous.in");
//    ofstream cout("continuous.out");

    int n, m;
    cin >> n >> m;

    sys.resize(n * 2);
    for (int i = 0; i < n * 2; ++i) {
        sys[i].assign(n * 2 + 1, 0.0);
    }

    for (int i = 0; i < n; ++i) {
        int f, s;
        cin >> f >> s;
        aut.push_back({f - 1, s - 1, i * 2, i * 2 + 1});
    }

    for (int i = 0; i < m; ++i) {
        int len;
        cin >> len;
        string in;
        cin >> in;
        vector<long double> temp;
        temp.assign(n * 2, 0.0);
        int cur = 0;
        for (int j = 0; j < len; ++j) {
            long double d;
            cin >> d;
            if (in[j] == '0') {
                temp[aut[cur].ind0] += 1;
                cur = aut[cur].to0;
            } else {
                temp[aut[cur].ind1] += 1;
                cur = aut[cur].to1;
            }

            for (int k = 0; k < n * 2; ++k) {
                if (temp[k] != 0) {
                    for (int l = 0; l < n * 2; ++l) {
                        sys[k][l] += (temp[k]*temp[l] ) / len;
                    }
                    sys[k][n * 2] += (temp[k]*d ) / len;
                }
            }
        }
    }

    for (int i = 0; i < n * 2; ++i) {
        long double max = abs(sys[i][i]);
        int index = i;
        for (int j = i + 1; j < n * 2; ++j) {
            if (abs(sys[i][j]) > max) {
                max = abs(sys[i][j]);
                index = j;
            }
        }

        if (max == 0.0) {
            continue;
        }

        swap(sys[i], sys[index]);

        for (int j = i; j < n * 2; ++j) {
            long double left = sys[j][i];
            if (left == 0.0) {
                continue;
            }

            for (int k = i; k < n * 2 + 1; ++k) {
                sys[j][k] /= left;
            }
        }

        for (int j = i + 1; j < n * 2; ++j) {
            if (sys[j][i] == 0.0) {
                continue;
            }

            for (int k = i; k < n * 2 + 1; ++k) {
                sys[j][k] -= sys[i][k];
            }
        }
    }

    vector<long double> ans;
    ans.push_back(sys[n*2-1][n*2]);

    for (int i = n*2 - 2; i >= 0; --i) {
        long double d = sys[i][n*2];
        for (int j = 0; j < ans.size(); ++j) {
            d-=ans[j]*sys[i][n*2-1-j];
        }
        ans.push_back(d);
    }

    reverse(ans.begin(),ans.end());

    for (int i = 0; i < n*2; i += 2) {
        cout << fixed << setprecision(7) << ans[i] << " ";
        cout << fixed << setprecision(7) << ans[i + 1] << "\n";
    }

    return 0;
}
/*
2 2
1 2
2 1
6 011011 1 2 3 4 5 6
6 010101 1 2 3 4 5 6

2 2
1 2
2 1
6 011011 -1 -2 -3 -4 -5 -6
6 010101 -1 -2 -3 -4 -5 -6

2 2
1 2
2 1
6 011011 1 0 1 0 1 0
6 010101 1 0 1 0 1 0

10 10
1 2
2 1
1 2
2 1
1 2
2 1
1 2
2 1
1 2
2 1
5 10101 0 2 3 4 5
*/