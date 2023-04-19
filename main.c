#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_punto
{
    float x, y;
} PUNTO;


typedef struct s_puntos
{
    PUNTO punto; 
    struct s_puntos* siguiente;
} *PUNTOS;
typedef struct s_figura{
PUNTOS puntos;
int totalpuntos;
} POLIGONO;

typedef struct s_poligonos{
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
void test_verPoligonos();
void test_AgregarPunto();

void test_verPuntos();
void test_cargarDatos();

int main(int argc, char const *argv[])
{
    cargarDatos();
	return 0;
}



PUNTO crearPunto(float px, float py)
{ 
    PUNTO punto1;
    punto1.x = px;
    punto1.y = py;
    return punto1;
    
}

LISTA_POLIGONOS agregarPoligono(LISTA_POLIGONOS poligonos, POLIGONO p) {
    LISTA_POLIGONOS nuevo_poligono = malloc(sizeof(LISTA_POLIGONOS));
    nuevo_poligono->p = p;
    nuevo_poligono->siguiente = NULL;
    if (poligonos == NULL) {
        poligonos = nuevo_poligono;
    } else {
        LISTA_POLIGONOS actual = nuevo_poligono;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo_poligono;
    }
    
    return poligonos;
}

POLIGONO crearPoligono(){
    POLIGONO p;
    p.puntos = NULL;
    p.totalpuntos = 0;
    return p;
}

// Esta función recibe un polígono y un punto, y le agrega el punto al polígono.
// Si el polígono no tiene puntos, el punto que recibe es el primero del polígono.
// Si el polígono ya tiene puntos, el punto que recibe es el último.
// Esta función devuelve el polígono con el punto agregado.

POLIGONO agregarPunto(POLIGONO p, PUNTO px) {
    PUNTOS nuevo_punto = malloc(sizeof(PUNTOS));
    nuevo_punto->punto = px;
    nuevo_punto->siguiente = NULL;
    if (p.puntos == NULL) {
        p.puntos = nuevo_punto;
        
    } else {
        PUNTOS actual = p.puntos;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo_punto;
        
    }
    p.totalpuntos++;
    return p;
}


double distancia(PUNTO p, PUNTO q) {
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}


float perimetro(POLIGONO p) {
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

void verPuntos(POLIGONO p) {
    PUNTOS puntoActual = p.puntos;
    while (puntoActual != NULL)
    {
        printf("Punto: (%f, %f)\n", puntoActual->punto.x, puntoActual->punto.y);
        puntoActual = puntoActual->siguiente;
    }
}



LISTA_POLIGONOS cargarDatos() { 
    FILE *archivo; // puntero de tipo FILE
    int numeroPuntos = 0; // defino el numero de puntos inicial del poligono
    char buffer[255]; // cantidad maxima de caracteres por linea al leer el archivo
    float x, y; // x e y del punto
    int flag = 1; // bool para salir del while
    short count = 0; 
    archivo = fopen("poligonos.txt", "r"); // abro el archivo en modo lectura
    if (archivo == NULL) { 
        printf("Error al abrir el archivo\n"); // si el archivo no existe, imprimo error
        exit(1);
    }
    LISTA_POLIGONOS listaPoligono = NULL; // creo la lista de poligonos en null ya qeu no hay ninguno
    fscanf(archivo, "%d", &numeroPuntos); // leo el primer numero del archivo, que es la cantidad de puntos del primer poligono
    
    while (!feof(archivo))
    {   
        LISTA_POLIGONOS listaPoligono = malloc(sizeof(struct s_poligonos)); // reservo la memoria de la lista para agregar el poligono "poligono"
        POLIGONO poligono = crearPoligono();                                // y declarar el siguiente como null
        listaPoligono-> p = poligono;
        listaPoligono->siguiente = NULL;
        int firstTime = 1;
        printf("Numero de puntos: %d\n", numeroPuntos);
        while (count < numeroPuntos) // leo los puntos del archivo y los agrego al poligono
        {   
            if (firstTime)
            {
                fgets(buffer, 255, archivo); // si es la primera vez que leem que lea el 0.0,0.0 pero no se guarda
                firstTime = 0;
            }
            
            
            fgets(buffer, 255, archivo);
            sscanf(buffer, "%f,%f", &x, &y); 
            agregarPunto(poligono,crearPunto(x,y));
            printf("Punto: (%f, %f)\n", x, y); // debug el punto para ver si lo lee correctamente
            count++;
        }
        agregarPoligono(listaPoligono, poligono);
        fscanf(archivo, "%d", &numeroPuntos); // leo el numero de puntos del siguiente poligono
        count = 0; // reseteo el contador de puntos
    }
    fclose(archivo); // cierro el archivo
    return listaPoligono;
}
POLIGONO mayorPerimetro(LISTA_POLIGONOS lista) {
    POLIGONO pMayorPerimetro = lista->p;
    LISTA_POLIGONOS actual = lista->siguiente;
    while (lista->siguiente == NULL)
    {
        if (perimetro(pMayorPerimetro) <= perimetro(actual->p))
        {
            pMayorPerimetro = actual->p;
        }
        actual = actual->siguiente;
        
    }
    return pMayorPerimetro;
}


void verPoligonos(LISTA_POLIGONOS lista) {
    int count = 1;
    LISTA_POLIGONOS actual = lista;
    while (actual != NULL) {
        printf("Poligono %d:\n", count);
        verPuntos(actual->p);
        actual = actual->siguiente;
        count++;
    }
    
}
// genera un test para la funcion cargarDatos();
void test_cargarDatos() {
    LISTA_POLIGONOS lista = cargarDatos();
    verPoligonos(lista);
}
// genera un test para la funcion verPuntos();
void test_verPuntos() {
    POLIGONO p = crearPoligono();
    p = agregarPunto(p, crearPunto(1, 1));
    p = agregarPunto(p, crearPunto(2, 2));
    p = agregarPunto(p, crearPunto(3, 3));
    verPuntos(p);
}
// genera un test para testear la funcion verPoligono();
void test_verPoligonos() {
    LISTA_POLIGONOS lista = NULL;
    PUNTO p1 = crearPunto(1, 12);
    PUNTO p2 = crearPunto(2, 23);
    PUNTO p3 = crearPunto(3, 35);
    PUNTO p4 = crearPunto(4, 40);
    PUNTO p5 = crearPunto(5, 66);
    PUNTO p6 = crearPunto(6, 63);
    PUNTO p7 = crearPunto(7, 71);
    PUNTO p8 = crearPunto(8, 82);
    PUNTO p9 = crearPunto(9, 95);
    //verPoligonos(lista);
    POLIGONO poli1 = crearPoligono();
    poli1 = agregarPunto(poli1, p1);
    poli1 = agregarPunto(poli1, p2);
    poli1 = agregarPunto(poli1, p3);
    POLIGONO poli2 = crearPoligono();
    poli2 = agregarPunto(poli2, p4);
    poli2 = agregarPunto(poli2, p5);
    poli2 = agregarPunto(poli2, p6);
    lista = agregarPoligono(lista, poli1);
    lista = agregarPoligono(lista, poli2);
    verPoligonos(lista);
    POLIGONO poli3 = crearPoligono();
    poli3 = agregarPunto(poli3, p7);
    poli3 = agregarPunto(poli3, p8);
    poli3 = agregarPunto(poli3, p9);
    
    lista = agregarPoligono(lista, poli2);
    lista = agregarPoligono(lista, poli3);
    //verPoligonos(lista);
    
}
