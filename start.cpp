#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

struct Vertex {
    int to0;
    int to1;
    char a;
};

int n, m;
vector<Vertex> ptr;
vector<bool> ans, temp;

int main() {
    ifstream cin("start.in");
    ofstream cout("start.out");

    cin >> m >> n;

    ans.assign(n, true);

    for (int i = 0; i < n; ++i) {
        int f, s;
        char c;
        cin >> f >> s >> c;
        ptr.push_back({f-1, s-1, c});
    }

    string s;
    cin >> s;

    for (int i = m-1; i >=0; --i) {
        temp.clear();
        temp.assign(n, false);
        for (int j = 0; j < n; ++j) {
            if ((ans[ptr[j].to1] && ptr[ptr[j].to1].a == s[i]) || (ans[ptr[j].to0] && ptr[ptr[j].to0].a == s[i])) {
                temp[j] = true;
            }
        }
        swap(ans,temp);
    }

    vector<int> answer;
    for (int i = 0; i < n; ++i) {
        if(ans[i]) {
            answer.push_back(i+1);
        }
    }

    cout << answer.size() << " ";
    for (int i : answer) {
        cout << i << " ";
    }
    return 0;
}