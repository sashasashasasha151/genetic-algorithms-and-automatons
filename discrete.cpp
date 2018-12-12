#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Vertex {
    int to0;
    int to1;
    vector<double> to0_out = vector<double>(26);
    vector<double> to1_out = vector<double>(26);
};

vector<Vertex> aut;

int main() {
    ifstream cin("discrete.in");
    ofstream cout("discrete.out");

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        int f, s;
        cin >> f >> s;
        aut.push_back({f - 1, s - 1});
    }

    for (int j = 0; j < m; ++j) {
        int cur = 0;
        int len;
        cin >> len;
        string in, out;
        cin >> in >> out;
        for (int i = 0; i < len; ++i) {
            if (in[i] == '0') {
                aut[cur].to0_out[out[i] - 'a'] += 1.0 / len;
                cur = aut[cur].to0;
            } else {
                aut[cur].to1_out[out[i] - 'a'] += 1.0 / len;
                cur = aut[cur].to1;
            }
        }
    }

    double max = 0;
    int ans = 0;
    for (int k = 0; k < n; ++k) {
        max = 0;
        ans = 0;
        for (int i = 0; i < aut[k].to0_out.size(); ++i) {
            if (aut[k].to0_out[i] > max) {
                max = aut[k].to0_out[i];
                ans = i;
            }
        }
        cout << (char) (ans + 'a') << " ";

        max = 0;
        ans = 0;
        for (int i = 0; i < aut[k].to1_out.size(); ++i) {
            if (aut[k].to1_out[i] > max) {
                max = aut[k].to1_out[i];
                ans = i;
            }
        }
        cout << (char) (ans + 'a') << "\n";
    }
    return 0;
}