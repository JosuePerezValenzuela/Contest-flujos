#include <bits/stdc++.h>

using namespace std;
int m, n, total, caso;
int s = 0;
int t = 36;
vector <int> adj[40];
int capacidad[40][40];
int parent[40];
int stickers[16][26];

void addedge(int u, int v, int val){
    if(!capacidad[u][v] && !capacidad[v][u]){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    capacidad[u][v] += val;
}

int bAmplitud(int s, int t){
    memset(parent, -1, sizeof parent);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT32_MAX});

    while(!q.empty()){
        int actual = q.front().first;
        int flujo = q.front().second;
        q.pop();
        for(int next : adj[actual]){
            if(parent[next] == -1 && capacidad[actual][next]){
                parent[next] = actual;
                int flujoNuevo = min(flujo, capacidad[actual][next]);
                if(next == t){
                    return flujoNuevo;
                }
                q.push({next, flujoNuevo});
            }
        }
    }
    return 0;
}

int flujoMax(){
    int flujo = 0;
    int flujoNuevo;
    while(flujoNuevo = bAmplitud(s, t)){
        flujo += flujoNuevo;
        int actual = t;
        while (actual != s){
            int prev = parent[actual];
            capacidad[prev][actual] -= flujoNuevo;
            capacidad[actual][prev] += flujoNuevo;
            actual = prev;
        }
    }
    return flujo;
}

int main(){
    int tc, n, m, x, y, respuesta;
    cin >> tc;
    while(tc--){
        for(int i = 0; i < 40; i++){
            adj[i].clear();
        }
        memset(stickers, 0, sizeof stickers);
        memset(capacidad, 0, sizeof capacidad);
        cin >> n >> m;
        for (int i = 1; i <= n; i++){
            cin >> x;
            for(int j = 0; j < x; j++){
                cin >> y;
                stickers[i][y]++;
            }
        }
        for(int i = 1; i <= m; i++){
            addedge(s, i+n, stickers[1][i]);
            addedge(i+n, t, 1);
        }
        for(int i = 2; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(stickers[i][j] == 1){
                    continue;
                }
                if(stickers[i][j] > 1){
                    addedge(i, j + n, stickers[i][j]-1);
                }else{
                    addedge(j + n, i, 1);
                }
            }
        }
        respuesta = flujoMax();
        cout << "Case #" << ++caso << ": " << respuesta << endl;
    }
    return 0;
}