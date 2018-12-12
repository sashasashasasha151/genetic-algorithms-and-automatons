#include <random>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int n, m;
vector<vector<bool>> ss;
vector<int> prefix, suffix;
vector<vector<int>> mid;
vector<int> midc;

int main() {
    ifstream cin("crossover.in");
    ofstream cout("crossover.out");

    cin >> n >> m;

    ss.resize(n + 1);
    prefix.assign(n, 0);
    suffix.assign(n, 0);
    mid.resize(n);
    midc.assign(m, 0);
    for (int i = 0; i < n; ++i) {
        mid[i].assign(m, 0);
    }

    for (int i = 0; i < n + 1; ++i) {
        string s;
        cin >> s;
        for (char c : s) {
            ss[i].push_back(c != '0');
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ss[i][j] = ss[i][j] ^ ss[n][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!ss[i][j]) {
                prefix[i]++;
            } else {
                break;
            }
        }

        for (int j = m - 1; j >= 0; --j) {
            if (!ss[i][j]) {
                suffix[i]++;
            } else {
                break;
            }
        }
    }

    int pm = 0, sm = 0;
    for (int i = 0; i < n; ++i) {
        if (prefix[i] > pm) {
            pm = prefix[i];
        }
        if (suffix[i] > sm) {
            sm = suffix[i];
        }
    }

    if (pm + sm >= m) {
        cout << "YES\n" << "YES\n" << "YES";
        return 0;
    } else {
        cout << "NO\n";
    }

    for (int i = 0; i < n; ++i) {
        int start = 0;
        int count = 0;
        for (int j = 0; j < m; ++j) {
            if (!ss[i][j]) {
                count++;
            } else {
                if (count != 0) {
                    for (; start < j; ++start) {
                        mid[i][start] = count--;
                    }
                }
                    start++;
            }
        }
        if (count != 0) {
            for (; start < m; ++start) {
                mid[i][start] = count--;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mid[j][i] > midc[i]) {
                midc[i] = mid[j][i];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (prefix[i] + midc[prefix[i]] + suffix[i] >= m) {
            cout << "YES\n" << "YES";
            return 0;
        }
    }

    cout << "NO\n";

    shuffle(ss.begin(), ss.begin()+n, std::mt19937(std::random_device()()));

    int ii = 0;

    for (int i = n-1; i >=0; --i) {
        for (int j = i-1; j >=0; --j) {
            bool is = true;
            for (int k = m/4; k < m; ++k) {
                if (ss[i][k] && ss[j][k]) {
                    is = false;
                    break;
                }
                ii++;
            }
            for (int k = 0; k < m/4; ++k) {
                if (ss[i][k] && ss[j][k]) {
                    is = false;
                    break;
                }
                ii++;
            }
            if (is) {
                cout << "YES";
                return 0;
            }
            if(ii>200000) {
                break;
            }
        }
        if(ii>200000) {
            break;
        }
    }

    cout << "NO";

    return 0;
}

/*
2 4
0000
1111
0101

2 4
0011
1100
1111

2 4
0101
1010
1111

3 3
100
001
010
111
*/