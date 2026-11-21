from datetime import date

nombre_x = input("Nombre del jugador X: ")
nombre_o = input("Nombre del jugador O: ")

tablero = [["", "", ""],
           ["", "", ""],
           ["", "", ""]]

jugadas = 0
ganador = ""
pila = []

while jugadas < 9 and ganador == "":
    if jugadas % 2 == 0:
        turno = "X"
    else:
        turno = "O"

    for f in tablero:
        print(f)

    if turno == "X":
        print("Turno de", nombre_x)
    else:
        print("Turno de", nombre_o)

    fila = int(input("Fila (0-2) o 9 para deshacer: "))

    if fila == 9:
        if len(pila) == 0:
            print("No hay jugadas para deshacer")
        else:
            ultima = pila.pop()
            tablero[ultima[0]][ultima[1]] = ""
            jugadas = jugadas - 1
        continue

    columna = int(input("Columna (0-2): "))

    if fila < 0 or fila > 2 or columna < 0 or columna > 2:
        print("Esa casilla no existe")
    elif tablero[fila][columna] != "":
        print("Casilla ocupada")
    else:
        tablero[fila][columna] = turno
        jugadas = jugadas + 1
        pila.append([fila, columna, turno])

        # Revisar las 3 filas
        for i in range(3):
            if tablero[i][0] == turno and tablero[i][1] == turno and tablero[i][2] == turno:
                ganador = turno

        # Revisar las 3 columnas
        for j in range(3):
            if tablero[0][j] == turno and tablero[1][j] == turno and tablero[2][j] == turno:
                ganador = turno

        # Revisar la diagonal principal: (0,0) (1,1) (2,2)
        if tablero[0][0] == turno and tablero[1][1] == turno and tablero[2][2] == turno:
            ganador = turno

        # Revisar la diagonal secundaria: (0,2) (1,1) (2,0)
        if tablero[0][2] == turno and tablero[1][1] == turno and tablero[2][0] == turno:
            ganador = turno

for f in tablero:
    print(f)
if ganador != "":
    if ganador == "X":
        print("Ganó", nombre_x)
    else:
        print("Ganó", nombre_o)
    resultado = ganador
else:
    print("¡Empate!")
    resultado = "EMPATE"


# ---------- Guardar la partida en historial.csv ----------
archivo = open("historial.csv", "r", encoding="utf-8")
lineas = archivo.readlines()
archivo.close()
id_partida = len(lineas)                   # la 1ª línea es el encabezado

archivo = open("historial.csv", "a", encoding="utf-8")
archivo.write(str(id_partida) + "," + nombre_x + "," + nombre_o + "," + resultado + "," + str(date.today()) + "\n")
archivo.close()

print("Partida", id_partida, "guardada en historial.csv")