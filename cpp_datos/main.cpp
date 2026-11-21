#include <iostream>   // cout
#include <fstream>    // leer archivos
#include <sstream>    // cortar líneas en pedazos
#include <string>     // texto
#include "nodo.h"
using namespace std;

int main() {
    // ---------- 1. LEER EL HISTORIAL (lista enlazada de partidas) ----------
    ifstream archivo("../../python_juego/historial.csv");
    string linea;
    Nodo* primera_partida = nullptr;                    // la lista empieza vacía

    getline(archivo, linea);                            // salta los títulos de las columnas

    while (getline(archivo, linea)) {                   // una vuelta por cada partida
        if (linea.empty()) {                            // si la línea está vacía, la salta
            continue;
        }

        stringstream pedazos(linea);
        string id_texto;
        Nodo* partida_nueva = new Nodo;                 // nodo nuevo para esta partida

        getline(pedazos, id_texto, ',');                // corta la línea por comas
        getline(pedazos, partida_nueva->jugador_x, ',');
        getline(pedazos, partida_nueva->jugador_o, ',');
        getline(pedazos, partida_nueva->resultado, ',');
        getline(pedazos, partida_nueva->fecha, ',');

        partida_nueva->id_partida = stoi(id_texto);     // pasa el id de texto a número
        partida_nueva->siguiente = primera_partida;     // lo pone al inicio de la lista
        primera_partida = partida_nueva;
    }
    archivo.close();

    // ---------- 2. CALCULAR PUNTOS (lista enlazada de jugadores) ----------
    JugadorRanking* primer_jugador = nullptr;           // la lista empieza vacía
    Nodo* partida = primera_partida;

    while (partida != nullptr) {                        // recorre las partidas una por una
        int puntos_x = 0;                               // puntos de X en esta partida
        int puntos_o = 0;                               // puntos de O en esta partida
        if (partida->resultado == "X") {
            puntos_x = 3;                               // victoria = 3
        } else if (partida->resultado == "O") {
            puntos_o = 3;
        } else {
            puntos_x = 1;                               // empate = 1 para cada uno
            puntos_o = 1;
        }

        // Este for da 2 vueltas: en la vuelta 0 trabaja con el jugador X y en la vuelta 1 con el jugador O
        for (int turno = 0; turno < 2; turno++) {       // turno 0 = jugador X, turno 1 = jugador O
            string nombre = partida->jugador_x;
            int puntos = puntos_x;
            if (turno == 1) {
                nombre = partida->jugador_o;
                puntos = puntos_o;
            }

            JugadorRanking* jugador_encontrado = primer_jugador;
            while (jugador_encontrado != nullptr &&
                   jugador_encontrado->nombre != nombre) {   // busca al jugador en la lista
                jugador_encontrado = jugador_encontrado->siguiente;
            }

            if (jugador_encontrado == nullptr) {        // si no estaba, crea su nodo
                JugadorRanking* jugador_nuevo = new JugadorRanking;
                jugador_nuevo->nombre = nombre;
                jugador_nuevo->puntos = 0;
                jugador_nuevo->siguiente = primer_jugador;
                primer_jugador = jugador_nuevo;
                jugador_encontrado = jugador_nuevo;
            }

            jugador_encontrado->puntos = jugador_encontrado->puntos + puntos;   // suma sus puntos
        }

        partida = partida->siguiente;                   // pasa a la siguiente partida
    }

    // ---------- 3. ORDENAR: de más a menos puntos ----------
    bool hubo_cambio = true;
    while (hubo_cambio) {                               // repite mientras siga habiendo cambios
        hubo_cambio = false;

        JugadorRanking* jugador_a_comparar = primer_jugador;
        while (jugador_a_comparar != nullptr &&
               jugador_a_comparar->siguiente != nullptr) {

            JugadorRanking* siguiente_jugador = jugador_a_comparar->siguiente;

            if (jugador_a_comparar->puntos < siguiente_jugador->puntos) {   // el de adelante tiene menos
                string nombre_temporal = jugador_a_comparar->nombre;        // los intercambia
                jugador_a_comparar->nombre = siguiente_jugador->nombre;
                siguiente_jugador->nombre = nombre_temporal;

                int puntos_temporal = jugador_a_comparar->puntos;
                jugador_a_comparar->puntos = siguiente_jugador->puntos;
                siguiente_jugador->puntos = puntos_temporal;

                hubo_cambio = true;                     // avisa que se movió algo
            }
            jugador_a_comparar = siguiente_jugador;     // avanza al siguiente
        }
    }

    // ---------- 4. MOSTRAR EL RANKING ----------
    int puesto = 1;                                     // posición en el ranking
    JugadorRanking* jugador = primer_jugador;
    while (jugador != nullptr) {                        // recorre la lista ya ordenada
        cout << puesto << ". " << jugador->nombre << " - " << jugador->puntos << " puntos" << endl;
        puesto++;
        jugador = jugador->siguiente;
    }

    return 0;
}