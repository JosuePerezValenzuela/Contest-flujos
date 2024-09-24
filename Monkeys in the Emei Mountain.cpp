#include <bits/stdc++.h>

using namespace std;

int inicio[101], fin[101], lista[101], lista2[501];
vector<pair<int, int>> vec[101];

vector<pair<int, int>> auxM(vector<pair<int, int>> otro) {
    vector<pair<int, int>> resp;
    for (int i = 0; i < otro.size(); i++) {
        pair<int, int> aux = otro[i];
        while (i + 1 < otro.size() && otro[i + 1].first == aux.second) {
            aux.second = otro[i + 1].second;
            i++;
        }
        resp.push_back(aux);
    }
    return resp;
}

int main() {
    int n, m, caso = 1;
    while (cin >> n && n) {
        cin >> m;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            cin >> lista[i] >> inicio[i] >> fin[i];
            lista2[cnt++] = inicio[i];
            lista2[cnt++] = fin[i];
            vec[i].clear();
        }
        sort(lista2, lista2 + cnt);
        cnt = unique(lista2, lista2 + cnt) - lista2;
        int now = lista2[0], then, ansed = true, j = 0;
        while (now < lista2[cnt - 1] && ansed) {
            then = INT_MAX;
            for (int i = 0; i < cnt; i++) {
                if (lista2[i] > now) {
                    if (lista2[i] < then) {
                        then = lista2[i];
                    }
                }
            }
            vector<pair<int, int>> v;
            for (int i = 0; i < n; i++) {
                if (inicio[i] <= now && lista[i] > 0) {
                    v.push_back(make_pair(fin[i], i));
                    if (fin[i] - now < lista[i]) {
                        ansed = false;
                    }
                }
            }
            if (ansed == false) {
                break;
            }
            sort(v.begin(), v.end());
            for (int i = 0; i < v.size(); i++) {
                int j = v[i].second;
                if (now + lista[j] < then) {
                    then = now + lista[j];
                }
            }
            int k = min(m, (int)v.size());
            for (int i = 0; i < k; i++) {
                int j = v[i].second;
                vec[j].push_back(make_pair(now, then));
                lista[j] -= then - now;
            }
            now = then;
        }
        for (int i = 0; i < n; i++) {
            if (lista[i] > 0) {
                ansed = false;
            }
        }
        cout << "Case " << caso++ << ": ";
        if (ansed == false) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
            for (int i = 0; i < n; i++) {
                vec[i] = auxM(vec[i]);
                cout << vec[i].size();
                for (int j = 0; j < vec[i].size(); j++) {
                    cout << " (" << vec[i][j].first << "," << vec[i][j].second << ")";
                }
                cout << endl;
            }
        }
    }
    return 0;
}
