#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Map.h"
#include "stack.h"

typedef struct{
    char nombre[20];
    int puntos; 
    char **items;
    int cantItems;
    Stack *funcionesAnteriores;
    int funcionesAnt;

} Jugador;

int is_equal_string(void * key1, void * key2) 
{
    if (strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

int lower_than_string(void * key1, void * key2) {
    if (strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

const char *get_csv_field (char * tmp, int k) 
{
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while (tmp[i+1]!='\0'){

        if (tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if (open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if (tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if (k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

Jugador *copiarJugador(Jugador *j)
{
    Jugador *nuevoJugador = (Jugador*)malloc(sizeof(Jugador));

    strcpy(nuevoJugador->nombre, j->nombre);
    nuevoJugador->puntos = j->puntos;
    nuevoJugador->cantItems = j->cantItems;
    nuevoJugador->items = (char**)malloc(sizeof(char*) * (nuevoJugador->cantItems + 1));

    for (int i = 0; i < nuevoJugador->cantItems; i++) 
    {
        nuevoJugador->items[i] = (char*)malloc(sizeof(char) * strlen(j->items[i]) + 1);
        strcpy(nuevoJugador->items[i], j->items[i]);
    }

    nuevoJugador->items[nuevoJugador->cantItems] = NULL;
    nuevoJugador->funcionesAnt = j->funcionesAnt;
    nuevoJugador->funcionesAnteriores = j->funcionesAnteriores;

    return nuevoJugador;
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

    while (1)
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
    j->funcionesAnteriores = stack_create();
    j->funcionesAnt = 0;
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
    printf("Items:%d\n", j->cantItems);

	int i;
    for ( i = 0; i < j->cantItems; i++)
    {
        printf("%s", j->items[i]);

        if (j -> items[i + 1] == NULL)
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

    if (j == NULL)
    {
        printf("No se encontro el jugador\n");
        return;
    }

    printf("Ingrese el item que desea agregar: ");
    char item[30];

    j->funcionesAnt++;
    Jugador *jAnt = copiarJugador(j);

    stack_push(j->funcionesAnteriores, jAnt);

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
    
    return;
}

void eliminarItem(char *nombre, Map *jugadoresPorNombre)
{
    Jugador *j = searchMap(jugadoresPorNombre, nombre);

    if (j == NULL)
    {
        printf("No se encontro el jugador\n");
        sleep(1);
        return;
    }

    printf("Ingrese el item que desea eliminar: ");
    char item[30];

    j->funcionesAnt++;
    Jugador *jAnt = copiarJugador(j);
    stack_push(j->funcionesAnteriores, jAnt);

    fflush(stdin);
    fgets(item, 30, stdin);
    item[strcspn(item, "\r\n")] = 0;

    for (int i = 0; i < j->cantItems; i++)
    {
        if (strcmp(j->items[i], item) == 0)
        {
            for (int k = i; k < j->cantItems; k++)
                j->items[k] = j->items[k+1];
            
            j->cantItems--;
            printf("Item eliminado con éxito!\n");
            
            sleep(1);
            return;
        }
    }

    printf("No se encontro el item\n");

    sleep(1);
    return;

}

void agregarPuntos(char *nombre, Map *jugadoresPorNombre)
{
    Jugador *j = searchMap(jugadoresPorNombre, nombre);

    if(j == NULL)
    {
        printf("No se encontro el jugador\n");
        return;
    }

    printf("Ingrese los puntos que desea agregar: ");
    int puntos;

    j->funcionesAnt++;
    Jugador *jAnt = copiarJugador(j);
    stack_push(j->funcionesAnteriores, jAnt);

    scanf("%d", &puntos);
    
    j->puntos += puntos;

    sleep(1);
    
    return;
}

void buscarItem(char *item, Map *jugadoresPorNombre, int cantJugadores)
{
    Jugador *j = firstMap(jugadoresPorNombre);

    int cont = 0;

    while (cont != cantJugadores)
    {
        for (int i = 0; i < j->cantItems; i++)
        {
            if (strcmp(j->items[i], item) == 0)
            {
                printf("Jugador: %s\n", j->nombre);
                printf("Puntos: %d\n", j->puntos);
                printf("Items:\n");

                for (int i = 0; i < j->cantItems; i++)
                {
                    printf("%s", j->items[i]);

                    if (j -> items[i + 1] == NULL)
                    {
                        printf("\n");
                        break;
                    }
                    else printf(", ");
                }
                sleep(1);
            }
        }

        j = nextMap(jugadoresPorNombre);
        cont++;
    }

    sleep(1);
    return;

}

void deshacer(char *nombre, Map *jugadoresPorNombre)
{
    Jugador *j = searchMap(jugadoresPorNombre, nombre);

    if (j == NULL)
    {
        printf("No se encontro el jugador\n");
        sleep(1);
        return;
    }

    if (j->funcionesAnt == 0)
    {
        printf("No hay acciones para deshacer\n");
        sleep(1);
        return;
    }

    Jugador *k = stack_pop(j->funcionesAnteriores);
    
    j->cantItems = k->cantItems;
    j->funcionesAnt = k->funcionesAnt;
    j->items = k->items;
    j->puntos = k->puntos;

    printf("Accion deshecha\n");
    j->funcionesAnt--;
    sleep(1);

}

void exportarJugador(Map *jugadoresPorNombre, int cantJugadores)
{
    Jugador *j = firstMap(jugadoresPorNombre);

    char nombreArchivo[30];
    printf("Ingrese el nombre del archivo .csv: ");
    scanf("%s", nombreArchivo);
    strcat(nombreArchivo, ".csv");
    FILE *fp = fopen(nombreArchivo, "a");
    int cont = 0;
    while (cont != cantJugadores)
    {
        fputs(j->nombre, fp);
        fputs("," , fp);

        char stringPuntos[10];
        sprintf(stringPuntos, "%d", j->puntos);
        fputs(stringPuntos, fp);
        fputs("," , fp);

        char stringCantItems[10];
        sprintf(stringCantItems, "%d", j->cantItems);
        fputs(stringCantItems, fp);

        int i;
        
        for ( i = 0; i < j->cantItems; i++)
        {
            fputs("," , fp);
            fputs(j->items[i], fp);
        }

        j = nextMap(jugadoresPorNombre);
        fputs("\n", fp);
        cont++;
    }

    fclose(fp);

    return;
}

void importarJugador()
{
    char nombreArchivo[30];
    int cantJugadores;
    printf("Ingrese el nombre del archivo .csv: ");
    scanf("%s", nombreArchivo);
    printf("\n");
    strcat(nombreArchivo, ".csv");
    FILE *fp = fopen(nombreArchivo, "r");
    
    char linea[1024];

    int k = 0;
    int contItems;
    while (fgets(linea, 1023, fp) != NULL)
    {
    	int i;
        for ( i = 0; i < 3; i++) 
        {
            const char *aux = get_csv_field(linea, i);

            switch (i) 
            {
                case 0:
                    printf("Nombre: %s\n", aux);
                    break;
                case 1:
                    printf("Puntos de habilidad: %s\n", aux);
                    break;
                case 2:
                    printf("Numero de items: %s\n", aux);
                    contItems = (int) strtol(aux, NULL, 10);
                    int j ;
                    for (j = 0 ; j < contItems ; j++)
                    {
                        const char *item = get_csv_field(linea, (j + 3) );
                        printf("%s", item);
                        if(j < (contItems - 1) ) printf(", "); 
                    }
                    printf("\n");
                    break;
            }
        }
        printf("\n");
        sleep(1);
    }
    fclose(fp);
} 

int main()
{
    int opcion = 0; 
    int contJugadores = 0;
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
        printf("6. Mostrar Jugadores Con Item Especifico\n");
        printf("7. Deshacer Ultima Accion De Jugador\n");
        printf("8. Exportar Datos De Jugador a archivo .csv\n");
        printf("9. Importar Datos De Jugador desde archivo .csv\n");
        printf("0. Salir\n");

        scanf("%d", &opcion);

        switch (opcion)
        {
        case 0:
            printf("Saliendo...\n");
            break;

        case 1:
            j = crearJugador();
            contJugadores++;
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
        	agregarPuntos(nombre, jugadoresPorNombre);
        	break;
        case 6:
            printf("Ingrese el item que desea buscar: ");
            char item[30];
            scanf("%s", item);
            buscarItem(item, jugadoresPorNombre, contJugadores);
            break;
        case 7:
            printf("Ingrese el nombre del jugador: ");
            scanf("%s", nombre);
            deshacer(nombre, jugadoresPorNombre);
            break;
        case 8:
            exportarJugador(jugadoresPorNombre, contJugadores);
            break;
        case 9:
            importarJugador();
	    break;
        default:
            printf("Opcion invalida\n");
            sleep(1);
            break;
        }

    } while (opcion != 0);
    
    free(jugadoresPorNombre);
    return EXIT_SUCCESS;
}
