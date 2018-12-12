#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>

using namespace std;

struct Vertex {
    bool is_c = false;
    int a = -1;
    int p = -1;
    int l = -1;
    int r = -1;
    int id;
};

int n;
int index = 1;
vector<Vertex> G;
unordered_map<int, int> info;
ostringstream out;

void dfs(int k, int parent, bool left) {
    if (!G[k].is_c) {
        return;
    }
    if (info[G[k].p] != 0) {
        if (info[G[k].p] == 1) {
            if (left) {
                G[parent].l = G[k].l;
                dfs(G[k].l, parent, left);
            } else {
                G[parent].r = G[k].l;
                dfs(G[k].l, parent, left);
            }
        } else {
            if (left) {
                G[parent].l = G[k].r;
                dfs(G[k].r, parent, left);
            } else {
                G[parent].r = G[k].r;
                dfs(G[k].r, parent, left);
            }
        }
        return;
    } else {
        info[G[k].p] = 1;
        dfs(G[k].l, k, true);
        info[G[k].p] = 2;
        dfs(G[k].r, k, false);
        info[G[k].p] = 0;
        return;
    }
}

void dfs_out(int k) {
    if (!G[k].is_c) {
        G[k].id = index++;
    } else {
        G[k].id = index++;
        dfs_out(G[k].l);
        dfs_out(G[k].r);
    }
}

void dfs_p(int k) {
    if (!G[k].is_c) {
        out << "leaf " << G[k].a << "\n";
    } else {
        out << "choice " << G[k].p << " " << G[G[k].l].id << " " << G[G[k].r].id << "\n";
        dfs_p(G[k].l);
        dfs_p(G[k].r);
    }
}

int main() {
    ifstream cin("trees.in");
    ofstream cout("trees.out");
    cin >> n;

    G.resize(n);

    for (int i = 0; i < n; ++i) {
        string op;
        cin >> op;
        if (op == "leaf") {
            int d;
            cin >> d;
            G[i].a = d;
        } else {
            int d, dd, ddd;
            cin >> d >> dd >> ddd;
            G[i].is_c = true;
            G[i].p = d;
            G[i].l = dd - 1;
            G[i].r = ddd - 1;
            info[d] = 0;
        };
    }

    dfs(0, 0, true);

    dfs_out(0);

    out << index - 1 << "\n";
    dfs_p(0);
    cout << out.str();

    return 0;
}