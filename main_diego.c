#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

typedef struct s_punto
{
    float x, y;
} PUNTO;

typedef struct s_puntos
{
    PUNTO punto;
    struct s_puntos *siguiente;
} *PUNTOS;
typedef struct s_figura
{
    PUNTOS puntos;
    int totalpuntos;
} POLIGONO;

typedef struct s_poligonos
{
    POLIGONO p;
    struct s_poligonos *siguiente;
} *LISTA_POLIGONOS;

PUNTO crearPunto(float px, float py);
double distancia(PUNTO p, PUNTO q);
POLIGONO agregarPunto(POLIGONO p, PUNTO px);
LISTA_POLIGONOS agregarPoligono(LISTA_POLIGONOS poligonos, POLIGONO poligono);
POLIGONO crearPoligono();
POLIGONO agregarPunto(POLIGONO p, PUNTO px);
float perimetro(POLIGONO p);
void verPuntos(POLIGONO p);
LISTA_POLIGONOS cargarDatos();
POLIGONO mayorPerimetro(LISTA_POLIGONOS lista);
void verPoligonos(LISTA_POLIGONOS lista);
LISTA_POLIGONOS eliminaPoligono(LISTA_POLIGONOS lista, int ubicacion);
void menu();
POLIGONO mostrarPoligono(LISTA_POLIGONOS lista, int ubicacion);
void angulosPoligono(LISTA_POLIGONOS lista, int n);

// test section
void test_perimetro();
void test_angulosPoligonos();

int main(int argc, char const *argv[])
{

    menu();
    return 0;
}

PUNTO crearPunto(float px, float py)
{
    PUNTO punto1;
    punto1.x = px;
    punto1.y = py;
    return punto1;
}

LISTA_POLIGONOS agregarPoligono(LISTA_POLIGONOS poligonos, POLIGONO p)
{
    // LISTA_POLIGONOS nuevo_poligono = malloc(sizeof(LISTA_POLIGONOS));
    LISTA_POLIGONOS nuevo_poligono = (LISTA_POLIGONOS)malloc(sizeof(struct s_poligonos));
    nuevo_poligono->p = p;
    nuevo_poligono->siguiente = NULL;
    if (poligonos == NULL)
    {
        poligonos = nuevo_poligono;
    }
    else
    {
        // LISTA_POLIGONOS actual = nuevo_poligono; // NO PUEDE SER EL NODO NUEVO, debe ser al que viene como argumento
        LISTA_POLIGONOS actual = poligonos;
        while (actual->siguiente != NULL)
        {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo_poligono;
    }

    return poligonos;
}

POLIGONO crearPoligono()
{
    POLIGONO p;
    p.puntos = NULL;
    p.totalpuntos = 0;
    return p;
}

// Esta función recibe un polígono y un punto, y le agrega el punto al polígono.
// Si el polígono no tiene puntos, el punto que recibe es el primero del polígono.
// Si el polígono ya tiene puntos, el punto que recibe es el último.
// Esta función devuelve el polígono con el punto agregado.

POLIGONO agregarPunto(POLIGONO p, PUNTO px)
{
    PUNTOS nuevo_punto = (PUNTOS)malloc(sizeof(struct s_puntos));
    nuevo_punto->punto = px;
    nuevo_punto->siguiente = NULL;
    if (p.puntos == NULL)
    {
        p.puntos = nuevo_punto;
    }
    else
    {
        PUNTOS actual = p.puntos;
        while (actual->siguiente != NULL)
        {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo_punto;
    }
    p.totalpuntos++;
    return p;
}

double distancia(PUNTO p, PUNTO q)
{
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

float perimetro(POLIGONO p)
{
    float perimetro = 0;
    PUNTOS puntoActual = p.puntos;
    while (puntoActual->siguiente != NULL)
    {
        perimetro += distancia(puntoActual->punto, puntoActual->siguiente->punto);
        puntoActual = puntoActual->siguiente;
    }
    perimetro += distancia(puntoActual->punto, p.puntos->punto);

    return perimetro;
}

void verPuntos(POLIGONO p)
{
    PUNTOS puntoActual = p.puntos;
    while (puntoActual != NULL)
    {
        printf("Punto: (%f, %f)\n", puntoActual->punto.x, puntoActual->punto.y);
        puntoActual = puntoActual->siguiente;
    }
}

LISTA_POLIGONOS cargarDatos()
{
    FILE *archivo;        // puntero de tipo FILE
    int numeroPuntos = 0; // defino el numero de puntos inicial del poligono
    char buffer[255];     // cantidad maxima de caracteres por linea al leer el archivo
    float x, y;           // x e y del punto
    int flag = 1;         // bool para salir del while
    short count = 0;
    archivo = fopen("poligonos.txt", "r"); // abro el archivo en modo lectura
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n"); // si el archivo no existe, imprimo error
        exit(1);
    }
    LISTA_POLIGONOS listaPoligono = NULL; // creo la lista de poligonos en null ya qeu no hay ninguno
    fscanf(archivo, "%d", &numeroPuntos); // leo el primer numero del archivo, que es la cantidad de puntos del primer poligono

    while (!feof(archivo))
    {
        POLIGONO poligono = crearPoligono();
        int firstTime = 1;
        while (count < numeroPuntos) // leo los puntos del archivo y los agrego al poligono
        {
            if (firstTime)
            {
                fgets(buffer, 255, archivo); // si es la primera vez que leem que lea el 0.0,0.0 pero no se guarda
                firstTime = 0;
            }
            fgets(buffer, 255, archivo);
            sscanf(buffer, "%f,%f", &x, &y);
            poligono = agregarPunto(poligono, crearPunto(x, y));
            count++;
        }
        listaPoligono = agregarPoligono(listaPoligono, poligono);
        fscanf(archivo, "%d", &numeroPuntos); // leo el numero de puntos del siguiente poligono
        count = 0;                            // reseteo el contador de puntos
    }
    fclose(archivo); // cierro el archivo
    return listaPoligono;
}
POLIGONO mayorPerimetro(LISTA_POLIGONOS lista)
{
    LISTA_POLIGONOS actual = lista;
    POLIGONO pMayorPerimetro = actual->p;
    while (actual != NULL)
    {
        if (perimetro(actual->p) > perimetro(pMayorPerimetro))
        {
            pMayorPerimetro = actual->p;
        }
        actual = actual->siguiente;
    }

    return pMayorPerimetro;
}

void verPoligonos(LISTA_POLIGONOS lista)
{
    int count = 1;
    LISTA_POLIGONOS actual = lista;
    while (actual != NULL)
    {
        printf("Poligono %d:\n", count);
        verPuntos(actual->p);
        actual = actual->siguiente;
        count++;
    }
}

LISTA_POLIGONOS eliminaPoligono(LISTA_POLIGONOS lista, int ubicacion)
{
    LISTA_POLIGONOS actual = lista;  // Puntero que recorre la lista
    LISTA_POLIGONOS anterior = NULL; // Puntero que queda atras de actual
    int count = 1;                   // Contador que lleva la posicion
    while (actual != NULL)
    {
        if (count == ubicacion)
        { // Si se encuentra en la posicion indicada
            if (anterior == NULL)
            {                              // Si es el primer poligono de la lista (no hay anterior)
                lista = actual->siguiente; // Se salta el poligono actual y se actualiza la lista (el primer poligono)
            }
            else
            {
                anterior->siguiente = actual->siguiente; // Se salta el poligono actual y se actualiza el puntero siguiente del anterior
            }
            free(actual); // Se libera el poligono actual
            return lista;
        }
        anterior = actual;          // Se actualiza el puntero anterior
        actual = actual->siguiente; // Se actualiza el puntero actual
        count++;                    // Se actualiza el contador
    }
    return lista;
}

// crear una funcion para contar los poligonos de una lista

int contadorPoligonos(LISTA_POLIGONOS lista)
{
    int count = 0;
    LISTA_POLIGONOS actual = lista;
    while (actual != NULL)
    {
        count++;
        actual = actual->siguiente;
    }
    return count;
}

void menu()
{
    int counted = 0, opcion = 0;
    LISTA_POLIGONOS lista = NULL;
    int countPoligonos = 0;
    while (opcion != 7)
    {
        if (counted)
        {
            countPoligonos = contadorPoligonos(lista);
        }
        printf("Cantidad de poligonos: %d\n", countPoligonos);
        int ubicacion;
        printf("1. Cargar datos\n");
        printf("2. Ver poligonos\n");
        printf("3. Mostrar poligono en x posición\n");
        printf("4. Poligono con el mayor perimetro\n");
        printf("5. Elimina un poligono\n");
        printf("6. Angulos interiores de un poligono\n");
        printf("7. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            lista = cargarDatos();
            printf("DATOS CARGADOS\n\n");
            counted = 1;
            sleep(2);
            break;
        case 2:
            if (!counted)
            {
                printf("Primero debe cargar los datos con la opcion 1!\n");
                sleep(2);
                break;
            }
            verPoligonos(lista);
            sleep(2);
            break;
        case 3:
            if (!counted)
            {
                printf("Primero debe cargar los datos con la opcion 1!\n");
                sleep(2);
                break;
            }
            do
            {
                printf("Ingrese la ubicacion del poligono a mostrar: ");
                int ubicacion;
                scanf("%d", &ubicacion);
                POLIGONO p = mostrarPoligono(lista, ubicacion);
                printf("Poligono %d:\n", ubicacion);
                if (ubicacion > countPoligonos || ubicacion < 1)
                {
                    printf("Ingrese un valor valido entre 1 y %d\n", countPoligonos);
                }
            } while (ubicacion > countPoligonos || ubicacion < 1);
            
            sleep(2);
            break;
        case 4:
            if (!counted)
            {
                printf("Primero debe cargar los datos con la opcion 1!\n");
                sleep(2);
                break;
            }
            printf("Poligono con mayor perimetro: \n");
            POLIGONO pMayorPerimetro = mayorPerimetro(lista);
            printf("Perimetro: %f\n", perimetro(pMayorPerimetro));
            verPuntos(pMayorPerimetro);
            sleep(2);
            break;
        case 5:
            if (!counted)
            {
                printf("Primero debe cargar los datos con la opcion 1!\n");
                sleep(2);
                break;
            }
            do
            {
                printf("Ingrese la ubicacion del poligono a eliminar: ");
                scanf("%d", &ubicacion);
                lista = eliminaPoligono(lista, ubicacion);
                if (ubicacion > countPoligonos || ubicacion < 1)
                {
                    printf("Ingrese un valor valido entre 1 y %d\n", countPoligonos);
                }
                
            } while (ubicacion > countPoligonos || ubicacion < 1);
            sleep(2);
            break;
        case 6:
            if (!counted)
            {
                printf("Primero debe cargar los datos con la opcion 1!\n");
                sleep(2);
                break;
            }
            // funcion de los angulos
            break;
        case 7:
            printf("Hasta luego!\n");
            sleep(2);
            break;
        default:
            printf("Opcion invalida\n");
            sleep(2);
            break;
        }
    }
}

// crear una funcion para mostrar el poligono n de la lista
POLIGONO mostrarPoligono(LISTA_POLIGONOS lista, int ubicacion)
{
    LISTA_POLIGONOS actual = lista;
    POLIGONO pNULL;
    int count = 1;
    while (actual != NULL)
    {
        if (count == ubicacion)
        {
            verPuntos(actual->p);
            printf("\n");
            return actual->p;
        }
        actual = actual->siguiente;
        count++;
    }

    return pNULL;
}

void test_perimetro()
{

    LISTA_POLIGONOS lista = cargarDatos();
    printf("Perimetro: %f\n", perimetro(lista->p));
    printf("Perimetro: %f\n", perimetro(lista->siguiente->p));
}

// crear test ma

void angulosPoligono(LISTA_POLIGONOS lista, int n)
{
    LISTA_POLIGONOS actual = lista;
    int count = 1;
    while (actual != NULL && count != n)
    {
        actual = actual->siguiente;
        count++;
    }
    float x1, x2, x3, y1, y2, y3, a1, a2, b1, b2;
    int i = 1;
    for (i = 1; i <= actual->p.totalpuntos; i++)
    {
        if (i == 1)
        {
            x1 = actual->p.puntos->punto.x;
            y1 = actual->p.puntos->punto.y;
            a1 = x1;
            b1 = y1;
            actual->p.puntos = actual->p.puntos->siguiente;
            x2 = actual->p.puntos->punto.x;
            y2 = actual->p.puntos->punto.y;
            a2 = x2;
            b2 = y2;
            actual->p.puntos = actual->p.puntos->siguiente;
            x3 = actual->p.puntos->punto.x;
            y3 = actual->p.puntos->punto.y;
        }
        else
        {
            if (i == actual->p.totalpuntos)
            {
                x1 = x2;
                y1 = y2;
                x2 = a1;
                y2 = b1;
                x3 = a2;
                y3 = b2;
            }
            else
            {
                x1 = x2;
                y1 = y2;
                x2 = x3;
                y2 = y3;
                actual->p.puntos = actual->p.puntos->siguiente;
                x3 = actual->p.puntos->punto.x;
                y3 = actual->p.puntos->punto.y;
            }
        }
        float vx1 = x1 - x2;
        float vy1 = y1 - y2;
        float vx2 = x2 - x3;
        float vy2 = y2 - y3;
        double prod = vx1 * vx2 + vy1 * vy2;
        double norm = sqrt(vx1 * vx1 + vy1 * vy1) * sqrt(vx2 * vx2 + vy2 * vy2);
        float angulorad = acos(prod / norm);
        float angulograd = (angulorad * 180) / 3.141592;
        printf("esto lo estoy corriendo por %d vez", i);
        printf("angulo %d : %d radianes, %d°\n", i, angulorad, angulograd);
    }
}

// crear un test para la funcion angulosPoligonos()
void test_angulosPoligonos()
{
    LISTA_POLIGONOS lista = cargarDatos();
    angulosPoligono(lista, 1);
    angulosPoligono(lista, 2);
}