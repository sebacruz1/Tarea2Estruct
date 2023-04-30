# Tarea2Estruct
Tarea 2 del grupo carita feliz:) para estrucura de datos 

Integrantes: Daniel Cepeda, Joaquin Fuenzalida, Maximiliano Bustamante Y Sebastián Cruz 


1. Para compilar necesitamos tener todos los archivos en la misma carpeta y ocupar gcc. Particularmente nosotros como grupo utilizamos gcc y la extension "code runner" de vscode, para asi ejecutar el programa de forma correcta.

2. La funcion 9 de importarJugadores no supimos como hacerla ya que si bien logramos que lea datos desde un archivo cvs no pudimos meterla dentro del map para poder incluirlos en el juego. Nos daba un error de que no se podia ingresar un const char que estabamos ocupando con la funcion get_cvs… , asi que lo que hicimos fue que los lea y los imprima a través de la terminal.

3. Nombre Equipo: :)
   -Participación activa y equitativa: 20
   -Resolución de conflictos: 20
   -Colaboración: 15
   -Responsabilidad: 20
   -Comunicación:15
   -Pje Total: 90
   
   Aspectos a mejorar de nuestro trabajo en equipo:
   - Falta de comunicación en el grupo
   - En ocaciones separarnos trabajos y no hacerlo completamente en equipo
  
4.  Nombre:            Seba / Joaquin / Daniel / Maximiliano
    Participación:       20 /      20 /     20 /     20 
    Responsabilidad:     20 /      20 /     20 /     20 
    Comunicación:        15 /      15 /     15 /     15 
    Calidad del Trabajo: 20 /      20 /     20 /     20
    Trabajo en Equipo:   20 /      15 /     20 /     15 
   -------------------------------------------------------------
    Pje Total:           95 /      90 /     95 /     90 
   
   Los aspectos positivos y aspectos a mejorar individuales se lo adjuntaremos via telegram:)

5. La funcion lower_than_string: Esta función es una función de comparación que se utiliza en la estructura Map que ordena los elementos de acuerdo a un criterio de menor a mayor. Recibe dos parámetros key1 y key2 que son cadenas de caracteres (char*). Si la cadena key1 es menor que la cadena key2, devuelve 1, de lo contrario, devuelve 0.

6. la funcion get_csv_field: Esta función recibe una cadena de caracteres y un número entero y devuelve un puntero a una cadena de caracteres. La función se utiliza para obtener un campo específico de una línea de un archivo CSV. La cadena tmp representa una línea del archivo CSV y k representa el número de campo que se quiere obtener. La función separa la línea en campos utilizando la coma como separador y devuelve el campo que corresponde al número k. La función aloca memoria dinámica para la cadena de caracteres devuelta, por lo que es importante liberar esta memoria después de su uso.

7. CopiarJugador: Esta función recibe un puntero a una estructura Jugador y devuelve un puntero a una estructura Jugador. La función crea una nueva estructura Jugador y copia el contenido de la estructura Jugador original en la nueva estructura. Además, se asegura de que la nueva estructura tenga su propia copia de los elementos del jugador. La función utiliza memoria dinámica para asignar espacio para la nueva estructura y los elementos de la estructura.

8. CrearJugador: Esta función se encarga de crear un nuevo jugador. La función pide al usuario que ingrese el nombre del jugador, los puntos de habilidad del jugador y los items

9. La función ingresarItem agrega un nuevo item a la lista de items de un jugador y realiza un seguimiento del estado anterior del jugador para permitir operaciones de deshacer en el futuro.






