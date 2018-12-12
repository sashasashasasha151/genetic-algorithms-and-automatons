#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;

int N;
int n;
double F = 0.8;

vector<vector<double>> population;

int main() {
    default_random_engine generator;
    uniform_int_distribution distribution(-10, 10);
    cin >> N;
    n = N * 10;
    population.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < N; ++j) {
            population[i].push_back((double) distribution(generator));
        }
    }

    uniform_int_distribution gen(0, n - 1);
    uniform_int_distribution P(1, 100);
    for (;;) {
        for (int j = 0; j < n; ++j) {
            int C = gen(generator);
            while (C == j) {
                C = gen(generator);
            }
            int A = gen(generator);
            while (A == C || A == j) {
                A = gen(generator);
            }
            int B = gen(generator);
            while (B == C || B == A || B == j) {
                B = gen(generator);
            }

            vector<double> son;
            for (int k = 0; k < N; ++k) {
                son.push_back(population[C][k] + F * (population[A][k] - population[B][k]));
                while (abs(son[k]) > 10) {
                    son[k] /= 2;
                }
                if (P(generator)>10) {
                    son[k] = population[j][k];
                }
            }

            cout << population[j][0];
            for (int k = 1; k < N; ++k) {
                cout << " " << population[j][k];
            }
            cout << endl;

            string s1;
            cin >> s1;

            if(s1 == "Bingo") {
                return 0;
            }

            cout << son[0];
            for (int k = 1; k < N; ++k) {
                cout << " " << son[k];
            }
            cout << endl;

            string s2;
            cin >> s2;

            if(s2 == "Bingo") {
                return 0;
            }

            double d1 = stod(s1);
            double d2 = stod(s2);

            if(d2<d1) {
                for (int k = 0; k < N; ++k) {
                    population[j][k] = son[k];
                }
            }
        }
    }
}