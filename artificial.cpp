#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("artificial.in");
    ofstream cout("artificial.out");

    int n;
    cin >> n;
    switch (n) {
        case 1: {
            cout << "1 2 R M\n"
                    "2 4 R M\n"
                    "1 1 L M\n"
                    "1 3 M M\n";
            break;
        }
        case 2: {
            cout << "1 1 L M\n";
            break;
        }
        case 3: {
            cout << "2 3 R M\n"
                    "3 2 L M\n"
                    "1 2 M R\n";
            break;
        }
        case 4: {
            cout << "4 1 M M\n"
                    "1 2 L M\n"
                    "1 3 R M\n"
                    "3 2 M M\n";
            break;
        }
        case 5: {
            cout << "2 3 M M\n"
                    "3 2 M L\n"
                    "1 1 R M\n";
            break;
        }
        case 6: {
            cout << "3 3 L M\n"
                    "3 4 R M\n"
                    "1 5 M M\n"
                    "2 3 M M\n"
                    "1 4 M M\n";
            break;
        }
        case 7: {
            cout << "2 3 R M\n"
                    "2 4 L M\n"
                    "1 4 M M\n"
                    "2 3 M M\n";
            break;
        }
        case 8: {
            cout << "2 5 M M\n"
                    "5 5 L M\n"
                    "4 2 R M\n"
                    "2 1 L M\n"
                    "3 5 M M\n";
            break;
        }
        case 9: {
            cout << "2 6 R M\n"
                    "5 5 L M\n"
                    "4 1 R M\n"
                    "1 6 M M\n"
                    "3 4 L M\n"
                    "3 5 M M\n";
            break;
        }
        case 10: {
            cout << "4 4 M M\n"
                    "1 6 L M\n"
                    "2 3 R M\n"
                    "5 3 R M\n"
                    "2 2 L M\n"
                    "5 4 L M\n";
            break;
        }
        default:{
            break;
        }
    }
    return 0;
}