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
    sleep(1);
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
        printf("%s", j->items[k]);

        if (j -> items[k + 1] == NULL)
        {
            printf("\n");
            break;
        }
        else printf(", ");
    }

    sleep(1);

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

    fflush(stdin);
    fgets(item, 30, stdin);
    item[strcspn(item, "\r\n")] = 0;

    j->cantItems++;
    j->items = (char**)realloc(j->items, (j->cantItems + 1) * sizeof(char*));
    j->items[j->cantItems - 1] = (char*)malloc(sizeof(char) * 30);
    strcpy(j->items[j->cantItems - 1], item);
    j->items[j->cantItems] = NULL;

    printf("Item agregado con éxito!\n");

    
    sleep(1);
}

void eliminarItem(char *nombre, Map *jugadoresPorNombre)
{
    Jugador *j = searchMap(jugadoresPorNombre, nombre);

    if(j == NULL)
    {
        printf("No se encontro el jugador\n");
        sleep(1);
        return;
    }

    printf("Ingrese el item que desea eliminar: ");
    char item[30];

    fflush(stdin);
    fgets(item, 30, stdin);
    item[strcspn(item, "\r\n")] = 0;

    for(int k = 0 ; k < j->cantItems ; k++)
    {
        if (strcmp(j->items[k], item) == 0)
        {
            for (int i = k; i < j->cantItems; i++)
            {
                j->items[i] = j->items[i + 1];
            }
            j->cantItems--;
            printf("Item eliminado\n");
            
            sleep(1);
            return;
        }
    }

    printf("No se encontro el item\n");

    sleep(1);
    return;

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
        printf("3. Agregar Item A Jugador\n");
        printf("4. Eliminar Item De Jugador\n");
        printf("5. Agregar Puntos De Habilidad A Jugador\n");
        printf("6. Deshacer Ultima Accion De Jugador\n");
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
        case 4:
            printf("\n");
        	printf("Ingrese el nombre del jugador: ");
            scanf("%s", nombre);
        	eliminarItem(nombre, jugadoresPorNombre);
        	break;
        case 5:
        	printf("\n");
        	printf("Ingrese el nombre del jugador: ");
            scanf("%s", nombre);
        	AgregarPuntos(nombre, jugadoresPorNombre);
        	break;
        


        default:
            printf("Opcion invalida\n");
            break;
        }

    } while (opcion != 0);
    

    return EXIT_SUCCESS;
}
