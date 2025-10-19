#include <iostream>     // Librer�a est�ndar para entrada y salida
#include <iomanip>      // Para formatear la salida (usar setw)
using namespace std;

#define INF 99999       // Valor muy grande que representa "infinito" (sin conexi�n)
#define V 4             // N�mero de v�rtices del grafo (puedes cambiarlo)

// Funci�n que aplica el algoritmo de Floyd�Warshall
void floydWarshall(int graph[V][V]) {
    int dist[V][V];     // Matriz de distancias que se ir� actualizando

    // Copiamos la matriz original del grafo a la matriz dist
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];   // Inicialmente, la distancia es la del grafo original
        }
    }

    // Triple bucle: el coraz�n del algoritmo de Floyd�Warshall
    for (int k = 0; k < V; k++) {           // k es el v�rtice intermedio
        for (int i = 0; i < V; i++) {       // i es el v�rtice de origen
            for (int j = 0; j < V; j++) {   // j es el v�rtice de destino
                // Si el camino i?k?j es m�s corto que el actual i?j, se actualiza
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Mostrar los resultados finales
    cout << "Matriz de distancias m�s cortas entre cada par de v�rtices:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)          // Si no hay camino, se muestra INF
                cout << setw(7) << "INF";
            else
                cout << setw(7) << dist[i][j];  // Si hay distancia, se muestra el valor
        }
        cout << endl;                        // Salto de l�nea al final de cada fila
    }
}

int main() {
    // Matriz de adyacencia del grafo (puedes modificar los valores)
    // INF indica que no hay conexi�n directa entre esos nodos
    int graph[V][V] = {
        {0,   5,  INF, 10},   // Distancias desde el v�rtice 0 hacia otros
        {INF, 0,   3,  INF},   // Desde el v�rtice 1
        {INF, INF, 0,   1},    // Desde el v�rtice 2
        {INF, INF, INF, 0}     // Desde el v�rtice 3
    };

    // Llamamos a la funci�n que ejecuta el algoritmo
    floydWarshall(graph);

    return 0;  // Fin del programa
}

