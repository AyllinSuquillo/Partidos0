#ifndef FUNCIONES_H
#define FUNCIONES_H
 
#define MAX_NOMBRE 50
#define MAX_JUGADORES 100
#define MAX_EQUIPOS 20
#define MAX_PARTIDOS 100
 
struct Jugador {
    char nombre[MAX_NOMBRE];
    char equipo[MAX_NOMBRE];
    int goles;
};
 
struct Equipo {
    char nombre[MAX_NOMBRE];
    int puntos;
    int golesFavor;
    int golesContra;
    int partidosJugados;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
};
 
struct Partido {
    char equipoLocal[MAX_NOMBRE];
    char equipoVisitante[MAX_NOMBRE];
    int golesLocal;
    int golesVisitante;
    char fecha[11]; // Formato: YYYY-MM-DD
    int finalizado; // 0 = no finalizado, 1 = finalizado
};
 
// Declaraciones de funciones
void leerCadena(char *cadena, int num);
void guardarJugador(struct Jugador *jugador);
int leerJugadores(struct Jugador jugadores[MAX_JUGADORES]);
void guardarEquipo(struct Equipo *equipo);
int leerEquipos(struct Equipo equipos[MAX_EQUIPOS]);
void guardarPartido(struct Partido *partido);
int leerPartidos(struct Partido partidos[MAX_PARTIDOS]);
void inicializarDatos();
void imprimirJugadores(struct Jugador jugadores[MAX_JUGADORES], int numJugadores);
void imprimirEquipos(struct Equipo equipos[MAX_EQUIPOS], int numEquipos);
void imprimirPartidos(struct Partido partidos[MAX_PARTIDOS], int numPartidos);
void registrarGol(struct Jugador jugadores[MAX_JUGADORES], int *numJugadores,
                  struct Partido partidos[MAX_PARTIDOS], int numPartidos,
                  struct Equipo equipos[MAX_EQUIPOS], int numEquipos);
void actualizarTablaPosiciones(struct Equipo equipos[MAX_EQUIPOS], int numEquipos,
                              struct Partido partidos[MAX_PARTIDOS], int numPartidos);
void finalizarPartido(struct Partido partidos[MAX_PARTIDOS], int numPartidos,
                     struct Equipo equipos[MAX_EQUIPOS], int numEquipos);
void guardarTodosLosDatos(struct Jugador jugadores[MAX_JUGADORES], int numJugadores,
                         struct Equipo equipos[MAX_EQUIPOS], int numEquipos,
                         struct Partido partidos[MAX_PARTIDOS], int numPartidos);
int buscarEquipo(struct Equipo equipos[MAX_EQUIPOS], int numEquipos, char *nombreEquipo);
int buscarJugador(struct Jugador jugadores[MAX_JUGADORES], int numJugadores,
                  char *nombreJugador, char *nombreEquipo);
 
#endif