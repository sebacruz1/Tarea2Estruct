#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Map.h"
#include "Map.c"

typedef struct{
    char nombre[20];
    int puntos; 
    char **items;
    int cantItems;
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

    printf("Ingrese los items del jugador (para finalizar dejar vacio): ");

    char item[30];
    int i = 0;
    j->items = (char**)malloc(sizeof(char*));
    j->cantItems = 0;

    while(1)
    {
        fflush(stdin);
        fgets(item, 30, stdin);
        item[strcspn(item, "\r\n")] = 0;

        if (strlen(item) == 0)
        {
            printf("Finalizando ingreso de items...\n");
            break;
        }
        
        j->cantItems++;
        j->items[i] = (char*)malloc(sizeof(char) * 30);
        strcpy(j->items[i], item);

        i++;
        
        j->items = (char**)realloc(j->items, (i+1) * sizeof(char*));
        
    }

    j->items[i] = NULL; 
    sleep(2);
    return j;
} 

void mostrarJugador(char *nombre, Map *jugadoresPorNombre)
{
    Jugador *j = searchMap(jugadoresPorNombre, nombre);

    if(j == NULL)
    {
        printf("No se encontro el jugador\n");
        return;
    }

    printf("Nombre: %s\n", j->nombre);
    printf("Puntos: %d\n", j->puntos);
    printf("Items:\n");

    for(int k = 0 ; k < j->cantItems ; k++)
    {
        printf("%s", j -> items[k]);

        if(j -> items[k] == NULL)
        {
            printf("\n");
            break;
        }
    }

    sleep(2);

}


void ingresarItem(char *nombre, Map *jugadoresPorNombre)
{
    Jugador *j = searchMap(jugadoresPorNombre, nombre);

    if(j == NULL)
    {
        printf("No se encontro el jugador\n");
        return;
    }

    printf("Ingrese el item que desea agregar: ");
    char item[30];

    while(1)
    {
        fflush(stdin);
        fgets(item, 30, stdin);
        item[strcspn(item, "\r\n")] = 0;

        if (strlen(item) == 0)
        {
            printf("Finalizando ingreso de items...\n");
            break;
        }

        j->items = (char**)realloc(j->items, (j->cantItems + 1) * sizeof(char*));
        j->items[j->cantItems] = (char*)malloc(sizeof(char) * 30);
        strcpy(j->items[j->cantItems], item);
        j->cantItems++;

    }
    
    sleep(2);
}

void AgregarPuntos(char *nombre, Map *jugadoresPorNombre)
{
    Jugador *j = searchMap(jugadoresPorNombre, nombre);

    if(j == NULL)
    {
        printf("No se encontro el jugador\n");
        return;
    }

    printf("Ingrese los puntos que desea agregar: ");
    int puntos;

    scanf("%d", &puntos);
    
    j->puntos += puntos;
    
}

int main()
{
    int opcion = 0; 
    Jugador* j;  

    Map *jugadoresPorNombre = createMap(is_equal_string);
    setSortFunction(jugadoresPorNombre, lower_than_string);

    do 
    {
        printf("Seleccione una opcion:\n"); 
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
        case 2:
            printf("Ingrese el nombre del jugador: ");
            char nombre[20];
            scanf("%s", nombre);
            mostrarJugador(nombre, jugadoresPorNombre);
            break;
        case 3:
        	printf("\n");
        	printf("Ingrese el nombre del jugador: ");
            scanf("%s", nombre);
        	ingresarItem(nombre, jugadoresPorNombre);
        	break;
        case 5:
        	printf("\n");
        	printf("Ingrese el nombre del jugador: ");
            scanf("%s", nombre);
        	AgregarPuntos(nombre, jugadoresPorNombre);
        	break;
        


        default:
            printf("Opcion inválida\n");
            break;
        }

    } while (opcion != 0);
    

    return EXIT_SUCCESS;
}
