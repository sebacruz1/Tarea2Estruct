#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "Map.c"

typedef struct{
    char nombre[20];
    int puntos; 
    char **items;
} Jugador;

int is_equal_string(void * key1, void * key2) 
{
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

Jugador *crearJugador()
{
    char nombre[20];
    int puntos;

    Jugador *j = (Jugador*)malloc(sizeof(Jugador));

    printf("Ingrese el nombre del jugador: ");
    scanf("%s", nombre);
    strcpy(j->nombre, nombre);

    printf("Ingrese los puntos de habilidad del jugador: ");
    scanf("%d", &puntos);
    j->puntos = puntos;

    printf("Ingrese los items del jugador: ");

    char items[30];
    int i = 0;

    while (1)
    {
        j->items = (char**)realloc(j->items, (i+1)*sizeof(char*));
        j->items[i] = (char*)malloc(30*sizeof(char));

        scanf("%s[^\n]", j->items[i]);
        if (j->items[i][0] != '\0')
        {
            free(j->items[i]);
            break;
        }
        
        i++;
        
    }

    return j;
}

int main()
{
    int opcion = 0; 
    Jugador* j;  

    Map *jugadoresPorNombre = createMap(is_equal_string);
    setSortFunction(jugadoresPorNombre, lower_than_string);

    do 
    {
        printf("Seleccione una opción:\n"); 
        printf("1. Crear Perfil De Jugador\n");
        printf("2. Mostrar Perfil De Jugador\n");
        printf("3. Agregar Ítem A Jugador\n");
        printf("4. Eliminar Item De Jugador\n");
        printf("5. Agregar Puntos De Habilidad A Jugador\n");
        printf("6. Deshacer Última Acción De Jugador\n");
        printf("7. Exportar Datos De Jugador a archivo .csv\n");
        printf("8. Importar Datos De Jugador desde archivo .csv\n");
        printf("0. Salir\n");

        scanf("%d", &opcion);

        switch (opcion)
        {
        case 0:
            printf("Saliendo...\n");
            break;

        case 1:
            j = crearJugador();
            insertMap(jugadoresPorNombre, j->nombre, j);
            insertMap(jugadoresPorNombre, &j->puntos, j);
            insertMap(jugadoresPorNombre, j->items, j);
            break;

        default:
            printf("Opción inválida\n");
            break;
        }

    } while (opcion != 0);
    

    return EXIT_SUCCESS;
}