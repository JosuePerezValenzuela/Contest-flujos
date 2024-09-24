#include <bits/stdc++.h>

using namespace std;

struct Arista {
    int destino, rev;
    long long flujo, capacidad, costo;
};
//Prueba con clases
class FlujoCostoMinimo {
public:
    FlujoCostoMinimo(int n) : n(n), prio(n), flujoActual(n), aristaAnterior(n), nodoAnterior(n), potencial(n), grafo(n) {}

    void agregarArista(int fuente, int destino, long long capacidad, long long costo) {
        grafo[fuente].push_back({destino, static_cast<int>(grafo[destino].size()), 0, capacidad, costo});
        grafo[destino].push_back({fuente, static_cast<int>(grafo[fuente].size()) - 1, 0, 0, -costo});
    }

    pair<long long, long long> obtenerFlujo(int fuente, int destino) {
        long long flujoTotal = 0, costoTotal = 0;
        while (true) {
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
            pq.push({0, fuente});
            fill(prio.begin(), prio.end(), 1e5);
            prio[fuente] = 0;
            flujoActual[fuente] = 1e5;
            
            while (!pq.empty()) {
                auto actual = pq.top();
                pq.pop();
                long long distancia = actual.first;
                int u = actual.second;

                if (distancia != prio[u]) {
                    continue;
                }

                for (int i = 0; i < grafo[u].size(); ++i) {
                    Arista &e = grafo[u][i];
                    int v = e.destino;

                    if (e.capacidad <= e.flujo) {
                        continue;
                    }
                    long long nuevaPrio = prio[u] + e.costo + potencial[u] - potencial[v];
                    if (prio[v] > nuevaPrio) {
                        prio[v] = nuevaPrio;
                        pq.push({nuevaPrio, v});
                        nodoAnterior[v] = u;
                        aristaAnterior[v] = i;
                        flujoActual[v] = min(flujoActual[u], e.capacidad - e.flujo);
                    }
                }
            }

            if (prio[destino] == 1e5) {
                break;
            }

            for (int i = 0; i < n; ++i) {
                potencial[i] += prio[i];
            }
            long long flujoMinimo = 1e5;
            long long deltaFlujo = min(flujoActual[destino], flujoMinimo - flujoTotal);
            flujoTotal += deltaFlujo;

            for (int v = destino; v != fuente; v = nodoAnterior[v]) {
                Arista &e = grafo[nodoAnterior[v]][aristaAnterior[v]];
                e.flujo += deltaFlujo;
                grafo[v][e.rev].flujo -= deltaFlujo;
                costoTotal += deltaFlujo * e.costo;
            }
        }
        return {flujoTotal, costoTotal};
    }

private:
    int n;
    vector<long long> prio, potencial, flujoActual;
    vector<int> aristaAnterior, nodoAnterior;
    vector<vector<Arista>> grafo;
};

int main() {
    int filas, columnas;
    cin >> filas >> columnas;

    vector<vector<int>> matriz(filas, vector<int>(columnas));
    int totalUnos = 0;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cin >> matriz[i][j];
            totalUnos += matriz[i][j];
        }
    }

    FlujoCostoMinimo flujo((filas * columnas) + filas + columnas + 2);
    int fuente = filas * columnas + filas + columnas;
    int sumidero = fuente + 1;

    vector<int> unosFilas(filas), unosColumnas(columnas);
    for (int i = 0; i < filas; ++i) {
        cin >> unosFilas[i];
        int nodo = filas * columnas + i;
        flujo.agregarArista(fuente, nodo, unosFilas[i], 0);

        for (int j = 0; j < columnas; ++j) {
            flujo.agregarArista(nodo, i * columnas + j, 1, 1 ^ matriz[i][j]);
        }
    }

    for (int i = 0; i < columnas; ++i) {
        cin >> unosColumnas[i];
        int nodo = filas * columnas + filas + i;
        flujo.agregarArista(nodo, sumidero, unosColumnas[i], 0);

        for (int j = 0; j < filas; ++j) {
            flujo.agregarArista(j * columnas + i, nodo, 1, 0);
        }
    }

    if (accumulate(unosFilas.begin(), unosFilas.end(), 0) == accumulate(unosColumnas.begin(), unosColumnas.end(), 0)) {
        auto resultado = flujo.obtenerFlujo(fuente, sumidero);
        if (resultado.first == accumulate(unosColumnas.begin(), unosColumnas.end(), 0)) {
            cout << totalUnos + resultado.second - accumulate(unosColumnas.begin(), unosColumnas.end(), 0) + resultado.second << '\n';
            return 0;
        }
    }
    cout << "-1\n";
    return 0;
}
