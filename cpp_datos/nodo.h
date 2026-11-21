#include <string>
using namespace std;

// Una partida del historial (lista enlazada de partidas)
struct Nodo {
    int id_partida;
    string jugador_x;
    string jugador_o;
    string resultado;     // "X", "O" o "EMPATE"
    string fecha;
    Nodo* siguiente;      // nullptr si es el último
};

// Un jugador del ranking (lista enlazada de jugadores únicos)
struct JugadorRanking {
    string nombre;
    int puntos;
    JugadorRanking* siguiente;
};