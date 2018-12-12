#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <random>

using namespace std;

struct Cond {
    int x = 0;
    int y = 0;
    int look = 0;
    int aut_cond = 0;
};

int N = 6;
int n = 60;
int k = 266;
int m = 20;
int food = 0;
int maxim = 0;

vector<string> field = {".****......*........",
                        "....*......*........",
                        "....*......*........",
                        "*****.....*.......**",
                        "......***........*..",
                        "..****...........*..",
                        "**................**",
                        "....................",
                        "...**.**..**....*...",
                        ".*..............*...",
                        ".*....*.*.*.....*...",
                        ".....*.....*.....*..",
                        ".*...*.....*......*.",
                        ".*...*....*......*..",
                        ".*..*.....*.....*...",
                        "..**.......*.....*..",
                        "...........*......*.",
                        "............*....*..",
                        "............*.......",
                        "...........*........"};

vector<vector<int>> population;

void count_food() {
    for (auto &i : field) {
        for (char j : i) {
            if (j == '*') {
                food++;
            }
        }
    }
}

void out(vector<int> ptr) {
    for (int i = 0; i < N; ++i) {
        cout << ptr[i * 4] + 1 << " " << ptr[i * 4 + 2] + 1 << " ";
        switch (ptr[i * 4 + 1]) {
            case 0: {
                cout << 'L';
                break;
            }
            case 1: {
                cout << 'R';
                break;
            }
            default: {
                cout << 'M';
                break;
            }
        }
        cout << " ";
        switch (ptr[i * 4 + 3]) {
            case 0: {
                cout << 'L';
                break;
            }
            case 1: {
                cout << 'R';
                break;
            }
            default: {
                cout << 'M';
                break;
            }
        }
        cout << "\n";
    }
}

int get_ans(vector<int> &ptr) {
    Cond c = Cond();
    int coun = 0;
    for (int i = 0; i < k; ++i) {
        int x, y;

        switch (c.look) {
            case 0: {
                x = (c.x + 1) % m;
                y = c.y;
                break;
            }
            case 2: {
                x = c.x - 1;
                if (x == -1) {
                    x = m - 1;
                }
                y = c.y;
                break;
            }
            case 1: {
                x = c.x;
                y = c.y - 1;
                if (y == -1) {
                    y = m - 1;
                }
                break;
            }
            default: {
                x = c.x;
                y = (c.y + 1) % m;
                break;
            }
        }

        if (field[y][x] == '*') {
            switch (ptr[c.aut_cond * 4 + 3]) {
                case 0: {
                    c.look = (c.look + 1) % 4;
                    c.aut_cond = ptr[c.aut_cond * 4 + 2];
                    break;
                }
                case 1: {
                    c.look = c.look - 1;
                    if (c.look == -1) {
                        c.look = 3;
                    }
                    c.aut_cond = ptr[c.aut_cond * 4 + 2];
                    break;
                }
                default: {
                    c.x = x;
                    c.y = y;
                    c.aut_cond = ptr[c.aut_cond * 4 + 2];
                    coun++;
                    field[y][x] = '#';
                    break;
                }
            }
        } else {
            switch (ptr[c.aut_cond * 4 + 1]) {
                case 0: {
                    c.look = (c.look + 1) % 4;
                    c.aut_cond = ptr[c.aut_cond * 4];
                    break;
                }
                case 1: {
                    c.look = c.look - 1;
                    if (c.look == -1) {
                        c.look = 3;
                    }
                    c.aut_cond = ptr[c.aut_cond * 4];
                    break;
                }
                default: {
                    c.x = x;
                    c.y = y;
                    c.aut_cond = ptr[c.aut_cond * 4];
                    break;
                }
            }
        }
    }

    for (auto &i : field) {
        for (char &j : i) {
            if (j == '#') {
                j = '*';
            }
        }
    }
    return coun;
}

int main() {
    count_food();
    default_random_engine gen;
    uniform_int_distribution vertex(0, N - 1);
    uniform_int_distribution letter(0, 2);

    population.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < N; ++j) {
            population[i].push_back(vertex(gen));
            population[i].push_back(letter(gen));
            population[i].push_back(vertex(gen));
            population[i].push_back(letter(gen));
        }
    }

    uniform_int_distribution get(0, n - 1);
    uniform_int_distribution P(1, 100);
    for (;;) {
        for (int j = 0; j < n; ++j) {
            int C = get(gen);
            while (C == j) {
                C = get(gen);
            }
            int A = get(gen);
            while (A == C || A == j) {
                A = get(gen);
            }
            int B = get(gen);
            while (B == C || B == A || B == j) {
                B = get(gen);
            }

            vector<int> son;
            for (int k = 0; k < N; ++k) {
                son.push_back((population[C][k * 4] + abs(population[A][k * 4] - population[B][k * 4])) % N);
                son.push_back(
                        (population[C][k * 4 + 1] + abs(population[A][k * 4 + 1] - population[B][k * 4 + 1])) % 3);
                son.push_back(
                        (population[C][k * 4 + 2] + abs(population[A][k * 4 + 2] - population[B][k * 4 + 2])) % N);
                son.push_back(
                        (population[C][k * 4 + 3] + abs(population[A][k * 4 + 3] - population[B][k * 4 + 3])) % 3);

                if (P(gen) > 30) {
                    son[k * 4] = population[j][k * 4];
                }
                if (P(gen) > 30) {
                    son[k * 4 + 1] = population[j][k * 4 + 1];
                }
                if (P(gen) > 30) {
                    son[k * 4 + 2] = population[j][k * 4 + 2];
                }
                if (P(gen) > 30) {
                    son[k * 4 + 3] = population[j][k * 4 + 3];
                }
            }

            int creat = get_ans(population[j]);
            int new_cr = get_ans(son);

            if (new_cr == food) {
                out(son);
                return 0;
            }

            if (new_cr > creat) {
                if (new_cr > maxim) {
                    cout << new_cr << "\n";
                    maxim = new_cr;
                }
                for (int i = 0; i < N * 4; ++i) {
                    population[j][i] = son[i];
                }
                continue;
            }

            if(new_cr == creat) {
                j--;
            }
        }
    }
}