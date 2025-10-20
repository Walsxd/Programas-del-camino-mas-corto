// ALGORITMO DE BELLMAN-FORD

function bellmanFord(numVertices, origen, aristas) {
    if(origen > numVertices - 1 || origen < 0 || numVertices < 0 || aristas.length === 0){
        return [];
    }
    if(numVertices === 1){
        return [0];
    }

    const distancias = Array(numVertices).fill(Infinity);
    distancias[origen] = 0;

    let cambio = true;
    let iteraciones = 0;    

    while (cambio && iteraciones < numVertices - 1) {
        cambio = false;

        // "Relajamos" las aristas buscando si hay un camino mas corto.
        for (const { inicio, destino, peso } of aristas) {
          if (distancias[inicio] !== Infinity && distancias[inicio] + peso < distancias[destino]) {
            distancias[destino] = distancias[inicio] + peso;
            cambio = true;
          }
        }

        // Si no hay cambios se detiene
        if (!cambio) {
          break;
        }
        iteraciones ++;
    }

    // Verificar ciclos negativos
    for (const { inicio, destino, peso } of aristas) {
      if (distancias[inicio] !== Infinity && distancias[inicio] + peso < distancias[destino]) {
        return null;
      }
    }

    return distancias;
}



function agregarArista(inicio, destino, peso, aristas) {
  aristas.push({ inicio, destino, peso });
}
function letraPorNumero(num){
    let letra = '';
    num++;
    while (num > 0) {
        num--;
        letra = String.fromCharCode(65 + (num % 26)) + letra;
        num = Math.floor(num / 26);
    }
    return letra;
}
let listaAristas = [];
const A = 0, B = 1, C = 2, D = 3;
agregarArista(A, B, 3, listaAristas);   // A → B: 3
agregarArista(A, D, 6, listaAristas);   // A → D: 6
agregarArista(B, C, 2, listaAristas);   // B → C: 2
agregarArista(C, D, 3, listaAristas);   // C → D: 3
agregarArista(D, B, -4, listaAristas);  // D → B: -4

const origen = 0;
const originLetter = letraPorNumero(origen);
const numVertices = Math.max(...listaAristas.flatMap(e => [e.inicio, e.destino])) + 1;
const result = bellmanFord(numVertices, origen, listaAristas);

console.log("Distancias más cortas desde el vértice " + originLetter + ": ");
if(result === null){
    console.log("El grafo tiene un ciclo negativo.");
} else if(result.length === 0){
    console.log("Origen inválido.");
} else {
    for(let i = 0; i < result.length; i++){
        console.log("De " + originLetter + " a " + letraPorNumero(i) + " : " + (result[i] !== Infinity ? result[i] : "∞"));
    }
}