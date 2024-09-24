#include <bits/stdc++.h>

using namespace std;

struct Solver {
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    string s;

    void inicio(int n) {
        adj.assign(n + 1, vector<int>());
        dp.assign(n + 1, vector<int>(3, 0));
    }

    void add(int parent, int child) {
        adj[parent].emplace_back(child);
    }

    void aux(const string& str) {
        s = "0" + str;
    }

    void dfs(int u) {
        for (int v : adj[u]) {
            dfs(v);
            dp[u][1] += min(dp[v][1], dp[v][2] + 1);
            dp[u][2] += min(dp[v][1] + 1, dp[v][2]);
        }

        if (s[u] == 'P') {
            dp[u][2] = 1e6;
        }
        if (s[u] == 'S') {
            dp[u][1] = 1e6;
        }
    }

    int resp() {
        dfs(1);
        return min(dp[1][1], dp[1][2]);
    }
};

void solve_case() {
    int n;
    cin >> n;

    Solver solver;
    solver.inicio(n);

    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        solver.add(p, i);
    }
    string s;
    cin >> s;
    solver.aux(s);
    cout << solver.resp() << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        solve_case();
    }
    return 0;
}