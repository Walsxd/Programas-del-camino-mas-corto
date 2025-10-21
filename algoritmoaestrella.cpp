#include <iostream>
#include <vector>
using namespace std;

struct node {
    int id;
    double costodesdeinicio;
    double ponderacion;
    double costomasponderacion;
    int padre;
    node(int _id) : id(_id), costodesdeinicio(0), ponderacion(0), costomasponderacion(0), padre(-1) {}
};

// Función para obtener el nodo en open con menor F
int nodoConMenorF(vector<node>& nodos, vector<bool>& open) {
    int indiceMin = -1;
    double minF = 1e9; // "infinito" inicial

    for (int i = 0; i < nodos.size(); i++) {
        if (open[i] && nodos[i].costomasponderacion < minF) {
            minF = nodos[i].costomasponderacion;
            indiceMin = i;
        }
    }
    return indiceMin;
}

// Función para verificar si aún hay nodos en open
bool aunhaynodos(vector<bool>& open) {
    for (bool estado : open) {
        if (estado) return true;
    }
    return false;
}

int main() {
    int n = 5;
    vector<node> nodos;
    for (int i = 0; i < n; i++) {
        nodos.push_back(node(i));
    }

    double matriz[5][5] = {
        {0, 10, 0, 30, 100},
        {10, 0, 50, 0, 0},
        {0, 50, 0, 20, 10},
        {30, 0, 20, 0, 60},
        {100, 0, 10, 60, 0}
    };

    int inicio = 0;
    int end = 4;

    vector<bool> open(n, false);
    vector<bool> closed(n, false);

    open[inicio] = true;

    while (aunhaynodos(open)) {
        int actual = nodoConMenorF(nodos, open);
        if (actual == end) break;

        open[actual] = false;
        closed[actual] = true;

        for (int i = 0; i < n; i++) {
            if (matriz[actual][i] != 0 && !closed[i]) {
                double g_nuevo = nodos[actual].costodesdeinicio + matriz[actual][i];
                double h_nuevo = 0; // heurística
                double f_nuevo = g_nuevo + h_nuevo;

                if (!open[i] || f_nuevo < nodos[i].costomasponderacion) {
                    nodos[i].costodesdeinicio = g_nuevo;
                    nodos[i].ponderacion = h_nuevo;
                    nodos[i].costomasponderacion = f_nuevo;
                    nodos[i].padre = actual;
                    open[i] = true;
                }
            }
        }
    }

    // Reconstruir camino
    vector<int> caminofinal;
    int actual = end;
    while (actual != -1) {
        caminofinal.push_back(actual);
        actual = nodos[actual].padre;
    }

    cout << "Camino encontrado:\n";
    for (int i = caminofinal.size() - 1; i >= 0; i--) {
        int id = caminofinal[i];
        cout << "Nodo: " << id 
             << ", Costo desde inicio: " << nodos[id].costodesdeinicio 
             << endl;
    }

    return 0;
}
