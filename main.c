#include <stdio.h>
#include <string.h>
#include "funciones.h"
 
int main() {
    struct Jugador jugadores[MAX_JUGADORES];
    struct Equipo equipos[MAX_EQUIPOS];
    struct Partido partidos[MAX_PARTIDOS];
   

    memset(jugadores, 0, sizeof(jugadores));
    memset(equipos, 0, sizeof(equipos));
    memset(partidos, 0, sizeof(partidos));
   
    // Cargar datos existentes
    int numJugadores = leerJugadores(jugadores);
    int numEquipos = leerEquipos(equipos);
    int numPartidos = leerPartidos(partidos);
   
    // Menu principal
    int opcion;
    do {
        printf("\n=== Sistema de Gestion de Futbol - FEF ===\n");
        printf("1. Registrar nuevo partido\n");
        printf("2. Registrar gol\n");
        printf("3. Finalizar partido\n");
        printf("4. Mostrar tabla de posiciones\n");
        printf("5. Mostrar goleadores\n");
        printf("6. Mostrar historial de partidos\n");
        printf("7. Registrar nuevo jugador\n");
        printf("8. Inicializar datos (solo primera vez)\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
       
        switch(opcion) {
            case 1: {
                if (numPartidos >= MAX_PARTIDOS) {
                    printf("No se pueden registrar más partidos.\n");
                    break;
                }
               
                struct Partido nuevoPartido;
                memset(&nuevoPartido, 0, sizeof(nuevoPartido));
               
                printf("Equipo local: ");
                leerCadena(nuevoPartido.equipoLocal, MAX_NOMBRE);
                printf("Equipo visitante: ");
                leerCadena(nuevoPartido.equipoVisitante, MAX_NOMBRE);
                printf("Fecha (YYYY-MM-DD): ");
                leerCadena(nuevoPartido.fecha, 11);
               
                nuevoPartido.golesLocal = 0;
                nuevoPartido.golesVisitante = 0;
                nuevoPartido.finalizado = 0;
               
                // Verificar que los equipos existan
                int equipoLocalExiste = buscarEquipo(equipos, numEquipos, nuevoPartido.equipoLocal);
                int equipoVisitanteExiste = buscarEquipo(equipos, numEquipos, nuevoPartido.equipoVisitante);
               
                if (equipoLocalExiste == -1 || equipoVisitanteExiste == -1) {
                    printf("Uno o ambos equipos no están registrados.\n");
                    break;
                }
               
                partidos[numPartidos] = nuevoPartido;
                numPartidos++;
                printf("Partido registrado con éxito.\n");
                break;
            }
            case 2:
                registrarGol(jugadores, &numJugadores, partidos, numPartidos, equipos, numEquipos);
                break;
            case 3:
                finalizarPartido(partidos, numPartidos, equipos, numEquipos);
                break;
            case 4:
                imprimirEquipos(equipos, numEquipos);
                break;
            case 5:
                imprimirJugadores(jugadores, numJugadores);
                break;
            case 6:
                imprimirPartidos(partidos, numPartidos);
                break;
            case 7: {
                if (numJugadores >= MAX_JUGADORES) {
                    printf("No se pueden registrar más jugadores.\n");
                    break;
                }
               
                struct Jugador nuevoJugador;
                memset(&nuevoJugador, 0, sizeof(nuevoJugador));
               
                printf("Nombre del jugador: ");
                leerCadena(nuevoJugador.nombre, MAX_NOMBRE);
                printf("Equipo: ");
                leerCadena(nuevoJugador.equipo, MAX_NOMBRE);
                nuevoJugador.goles = 0;
               
                // Verificar que el equipo exista
                if (buscarEquipo(equipos, numEquipos, nuevoJugador.equipo) == -1) {
                    printf("El equipo no está registrado.\n");
                    break;
                }
               
                jugadores[numJugadores] = nuevoJugador;
                numJugadores++;
                printf("Jugador registrado con éxito.\n");
                break;
            }
            case 8:
                inicializarDatos();
                numJugadores = leerJugadores(jugadores);
                numEquipos = leerEquipos(equipos);
                numPartidos = leerPartidos(partidos);
                printf("Datos inicializados correctamente.\n");
                break;
            case 0:
                // Guardar todos los datos antes de salir
                guardarTodosLosDatos(jugadores, numJugadores, equipos, numEquipos, partidos, numPartidos);
                printf("Datos guardados. Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion no válida.\n");
        }
    } while(opcion != 0);
   
    return 0;
}