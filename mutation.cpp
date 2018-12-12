#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    ifstream cin("mutation.in");
    ofstream cout("mutation.out");
    
    int n,m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        string s1,s2;
        cin >> s1 >> s2;
        long double d=1;
        for (int j = 0; j < n; ++j) {
            if(s1[j] == s2[j]) {
                d*=1-1.0/n;
            } else {
                d*=1.0/n;
            }
        }
        cout << fixed << setprecision(10) << d << "\n";
    }
    return 0;
}