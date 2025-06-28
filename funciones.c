#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"
 
void leerCadena(char *cadena, int num) {
    while (getchar() != '\n'); // Limpiar buffer
    fgets(cadena, num, stdin);
    int len = strlen(cadena);
    if (len > 0 && cadena[len - 1] == '\n') {
        cadena[len - 1] = '\0';
    }
}
 
void guardarJugador(struct Jugador *jugador) {
    FILE *f = fopen("Jugadores.dat", "ab");
    if (f != NULL) {
        fwrite(jugador, sizeof(struct Jugador), 1, f);
        fclose(f);
    }
}
 
int leerJugadores(struct Jugador jugadores[MAX_JUGADORES]) {
    FILE *f = fopen("Jugadores.dat", "rb");
    int count = 0;
   
    if (f == NULL) {
        printf("No se encontraron jugadores registrados.\n");
        return 0;
    }
   
    while (count < MAX_JUGADORES &&
           fread(&jugadores[count], sizeof(struct Jugador), 1, f) == 1) {
        count++;
    }
   
    fclose(f);
    return count;
}
 
void guardarEquipo(struct Equipo *equipo) {
    FILE *f = fopen("Equipos.dat", "ab");
    if (f != NULL) {
        fwrite(equipo, sizeof(struct Equipo), 1, f);
        fclose(f);
    }
}
 
int leerEquipos(struct Equipo equipos[MAX_EQUIPOS]) {
    FILE *f = fopen("Equipos.dat", "rb");
    int count = 0;
   
    if (f == NULL) {
        printf("No se encontraron equipos registrados.\n");
        return 0;
    }
   
    while (count < MAX_EQUIPOS &&
           fread(&equipos[count], sizeof(struct Equipo), 1, f) == 1) {
        count++;
    }
   
    fclose(f);
    return count;
}
 
void guardarPartido(struct Partido *partido) {
    FILE *f = fopen("Partidos.dat", "ab");
    if (f != NULL) {
        fwrite(partido, sizeof(struct Partido), 1, f);
        fclose(f);
    }
}
 
int leerPartidos(struct Partido partidos[MAX_PARTIDOS]) {
    FILE *f = fopen("Partidos.dat", "rb");
    int count = 0;
   
    if (f == NULL) {
        printf("No se encontraron partidos registrados.\n");
        return 0;
    }
   
    while (count < MAX_PARTIDOS &&
           fread(&partidos[count], sizeof(struct Partido), 1, f) == 1) {
        count++;
    }
   
    fclose(f);
    return count;
}
 
void inicializarDatos() {
    // Limpiar archivos existentes
    remove("Equipos.dat");
    remove("Jugadores.dat");
    remove("Partidos.dat");
   
    // Inicializar equipos básicos
    struct Equipo equipos[5] = {
        {"Barcelona SC", 0, 0, 0, 0, 0, 0, 0},
        {"Emelec", 0, 0, 0, 0, 0, 0, 0},
        {"Independiente", 0, 0, 0, 0, 0, 0, 0},
        {"LDU Quito", 0, 0, 0, 0, 0, 0, 0},
        {"Universidad Catolica", 0, 0, 0, 0, 0, 0, 0}
    };
 
    for (int i = 0; i < 5; i++) {
        guardarEquipo(&equipos[i]);
    }
 
    // Inicializar algunos jugadores
    struct Jugador jugadores[5] = {
        {"Fidel Martinez", "Barcelona SC", 0},
        {"Gonzalo Mastriani", "Emelec", 0},
        {"Luis Chicaiza", "Independiente", 0},
        {"Cristian Martinez", "LDU Quito", 0},
        {"Joffre Escobar", "Universidad Catolica", 0}
    };
 
    for (int i = 0; i < 5; i++) {
        guardarJugador(&jugadores[i]);
    }
}
 
void imprimirJugadores(struct Jugador jugadores[MAX_JUGADORES], int numJugadores) {
    if (numJugadores == 0) {
        printf("No hay jugadores registrados.\n");
        return;
    }
   
    printf("\nLista de Goleadores:\n");
    printf("%-25s %-20s %s\n", "Nombre", "Equipo", "Goles");
    printf("----------------------------------------------------------\n");
   
    // Ordenar por goles (burbuja simple)
    for (int i = 0; i < numJugadores - 1; i++) {
        for (int j = 0; j < numJugadores - i - 1; j++) {
            if (jugadores[j].goles < jugadores[j + 1].goles) {
                struct Jugador temp = jugadores[j];
                jugadores[j] = jugadores[j + 1];
                jugadores[j + 1] = temp;
            }
        }
    }
   
    for (int i = 0; i < numJugadores; i++) {
        printf("%-25s %-20s %d\n", jugadores[i].nombre, jugadores[i].equipo, jugadores[i].goles);
    }
}
 
void imprimirEquipos(struct Equipo equipos[MAX_EQUIPOS], int numEquipos) {
    if (numEquipos == 0) {
        printf("No hay equipos registrados.\n");
        return;
    }
   
    printf("\nTabla de Posiciones:\n");
    printf("%-20s %s %s %s %s %s %s %s %s\n", "Equipo", "PJ", "PG", "PE", "PP", "GF", "GC", "DG", "Pts");
    printf("---------------------------------------------------------------------------------\n");
   
    // Ordenar por puntos
    for (int i = 0; i < numEquipos - 1; i++) {
        for (int j = 0; j < numEquipos - i - 1; j++) {
            if (equipos[j].puntos < equipos[j + 1].puntos) {
                struct Equipo temp = equipos[j];
                equipos[j] = equipos[j + 1];
                equipos[j + 1] = temp;
            }
        }
    }
   
    for (int i = 0; i < numEquipos; i++) {
        int diferencia = equipos[i].golesFavor - equipos[i].golesContra;
        printf("%-20s %2d %2d %2d %2d %2d %2d %+3d %3d\n",
               equipos[i].nombre, equipos[i].partidosJugados,
               equipos[i].partidosGanados, equipos[i].partidosEmpatados,
               equipos[i].partidosPerdidos, equipos[i].golesFavor,
               equipos[i].golesContra, diferencia, equipos[i].puntos);
    }
}
 
void imprimirPartidos(struct Partido partidos[MAX_PARTIDOS], int numPartidos) {
    if (numPartidos == 0) {
        printf("No hay partidos registrados.\n");
        return;
    }
   
    printf("\nHistorial de Partidos:\n");
    printf("%-20s %-20s %-10s %-12s %s\n", "Equipo Local", "Equipo Visitante", "Resultado", "Fecha", "Estado");
    printf("------------------------------------------------------------------------------\n");
   
    for (int i = 0; i < numPartidos; i++) {
        char resultado[10];
        char estado[15];
       
        if (partidos[i].finalizado) {
            sprintf(resultado, "%d - %d", partidos[i].golesLocal, partidos[i].golesVisitante);
            strcpy(estado, "Finalizado");
        } else {
            strcpy(resultado, "- - -");
            strcpy(estado, "Programado");
        }
       
        printf("%-20s %-20s %-10s %-12s %s\n",
               partidos[i].equipoLocal, partidos[i].equipoVisitante,
               resultado, partidos[i].fecha, estado);
    }
}
 
int buscarEquipo(struct Equipo equipos[MAX_EQUIPOS], int numEquipos, char *nombreEquipo) {
    for (int i = 0; i < numEquipos; i++) {
        if (strcmp(equipos[i].nombre, nombreEquipo) == 0) {
            return i;
        }
    }
    return -1;
}
 
int buscarJugador(struct Jugador jugadores[MAX_JUGADORES], int numJugadores,
                  char *nombreJugador, char *nombreEquipo) {
    for (int i = 0; i < numJugadores; i++) {
        if (strcmp(jugadores[i].nombre, nombreJugador) == 0 &&
            strcmp(jugadores[i].equipo, nombreEquipo) == 0) {
            return i;
        }
    }
    return -1;
}
 
void registrarGol(struct Jugador jugadores[MAX_JUGADORES], int *numJugadores,
                  struct Partido partidos[MAX_PARTIDOS], int numPartidos,
                  struct Equipo equipos[MAX_EQUIPOS], int numEquipos) {
    char nombreJugador[MAX_NOMBRE];
    char equipo[MAX_NOMBRE];
    int partidoIndex;
   
    if (numPartidos == 0) {
        printf("No hay partidos registrados.\n");
        return;
    }
   
    // Mostrar partidos disponibles
    printf("\nPartidos disponibles:\n");
    for (int i = 0; i < numPartidos; i++) {
        if (!partidos[i].finalizado) {
            printf("%d. %s vs %s (%s)\n", i, partidos[i].equipoLocal,
                   partidos[i].equipoVisitante, partidos[i].fecha);
        }
    }
   
    printf("Ingrese el numero del partido: ");
    scanf("%d", &partidoIndex);
   
    if (partidoIndex < 0 || partidoIndex >= numPartidos || partidos[partidoIndex].finalizado) {
        printf("Partido no válido o ya finalizado.\n");
        return;
    }
   
    printf("Ingrese el nombre del jugador que anoto: ");
    leerCadena(nombreJugador, MAX_NOMBRE);
   
    printf("Ingrese el equipo del jugador: ");
    leerCadena(equipo, MAX_NOMBRE);
   
    // Verificar que el equipo participe en el partido
    if (strcmp(equipo, partidos[partidoIndex].equipoLocal) != 0 &&
        strcmp(equipo, partidos[partidoIndex].equipoVisitante) != 0) {
        printf("El equipo no participa en este partido.\n");
        return;
    }
   
    // Buscar jugador existente
    int jugadorIndex = buscarJugador(jugadores, *numJugadores, nombreJugador, equipo);
   
    if (jugadorIndex == -1) {
        // Crear nuevo jugador
        if (*numJugadores >= MAX_JUGADORES) {
            printf("No se pueden registrar más jugadores.\n");
            return;
        }
       
        strcpy(jugadores[*numJugadores].nombre, nombreJugador);
        strcpy(jugadores[*numJugadores].equipo, equipo);
        jugadores[*numJugadores].goles = 1;
        (*numJugadores)++;
        printf("Nuevo jugador registrado y gol anotado.\n");
    } else {
        // Actualizar jugador existente
        jugadores[jugadorIndex].goles++;
        printf("Gol registrado para %s.\n", nombreJugador);
    }
   
    // Actualizar partido
    if (strcmp(partidos[partidoIndex].equipoLocal, equipo) == 0) {
        partidos[partidoIndex].golesLocal++;
    } else {
        partidos[partidoIndex].golesVisitante++;
    }
}
 
void finalizarPartido(struct Partido partidos[MAX_PARTIDOS], int numPartidos,
                     struct Equipo equipos[MAX_EQUIPOS], int numEquipos) {
    int partidoIndex;
   
    printf("\nPartidos pendientes:\n");
    int hayPendientes = 0;
    for (int i = 0; i < numPartidos; i++) {
        if (!partidos[i].finalizado) {
            printf("%d. %s %d - %d %s\n", i, partidos[i].equipoLocal,
                   partidos[i].golesLocal, partidos[i].golesVisitante,
                   partidos[i].equipoVisitante);
            hayPendientes = 1;
        }
    }
   
    if (!hayPendientes) {
        printf("No hay partidos pendientes.\n");
        return;
    }
   
    printf("Ingrese el numero del partido a finalizar: ");
    scanf("%d", &partidoIndex);
   
    if (partidoIndex < 0 || partidoIndex >= numPartidos || partidos[partidoIndex].finalizado) {
        printf("Partido no válido.\n");
        return;
    }
   
    partidos[partidoIndex].finalizado = 1;
   
    // Actualizar estadísticas de equipos
    int indexLocal = buscarEquipo(equipos, numEquipos, partidos[partidoIndex].equipoLocal);
    int indexVisitante = buscarEquipo(equipos, numEquipos, partidos[partidoIndex].equipoVisitante);
   
    if (indexLocal != -1 && indexVisitante != -1) {
        equipos[indexLocal].partidosJugados++;
        equipos[indexVisitante].partidosJugados++;
       
        equipos[indexLocal].golesFavor += partidos[partidoIndex].golesLocal;
        equipos[indexLocal].golesContra += partidos[partidoIndex].golesVisitante;
        equipos[indexVisitante].golesFavor += partidos[partidoIndex].golesVisitante;
        equipos[indexVisitante].golesContra += partidos[partidoIndex].golesLocal;
       
        if (partidos[partidoIndex].golesLocal > partidos[partidoIndex].golesVisitante) {
            // Gana local
            equipos[indexLocal].partidosGanados++;
            equipos[indexLocal].puntos += 3;
            equipos[indexVisitante].partidosPerdidos++;
        } else if (partidos[partidoIndex].golesLocal < partidos[partidoIndex].golesVisitante) {
            // Gana visitante
            equipos[indexVisitante].partidosGanados++;
            equipos[indexVisitante].puntos += 3;
            equipos[indexLocal].partidosPerdidos++;
        } else {
            // Empate
            equipos[indexLocal].partidosEmpatados++;
            equipos[indexLocal].puntos += 1;
            equipos[indexVisitante].partidosEmpatados++;
            equipos[indexVisitante].puntos += 1;
        }
    }
   
    printf("Partido finalizado correctamente.\n");
}
 
void guardarTodosLosDatos(struct Jugador jugadores[MAX_JUGADORES], int numJugadores,
                         struct Equipo equipos[MAX_EQUIPOS], int numEquipos,
                         struct Partido partidos[MAX_PARTIDOS], int numPartidos) {
    // Limpiar archivos
    remove("Jugadores.dat");
    remove("Equipos.dat");
    remove("Partidos.dat");
   
    // Guardar jugadores
    FILE *f = fopen("Jugadores.dat", "wb");
    if (f != NULL) {
        fwrite(jugadores, sizeof(struct Jugador), numJugadores, f);
        fclose(f);
    }
   
    // Guardar equipos
    f = fopen("Equipos.dat", "wb");
    if (f != NULL) {
        fwrite(equipos, sizeof(struct Equipo), numEquipos, f);
        fclose(f);
    }
   
    // Guardar partidos
    f = fopen("Partidos.dat", "wb");
    if (f != NULL) {
        fwrite(partidos, sizeof(struct Partido), numPartidos, f);
        fclose(f);
    }
}