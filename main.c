#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define TAM_MAXIMO 100


/*
 * ALMACENAMIENTO DE TODAS LAS TAREAS PENDIENTES (LISTA)
 */
typedef struct nodo {
    int dato;
    char descripcionTarea[TAM_MAXIMO];
    struct nodo *nodoSiguiente;
} nodo;

typedef struct lista {
    struct nodo *inicio;
    struct nodo *fin;

} lista;

lista *crearLista() {
    struct lista *nuevaLista = malloc(sizeof(lista));
    nuevaLista->inicio = NULL;
    nuevaLista->fin = NULL;
    return nuevaLista;
};

nodo *crearNodo(int dato, char *descripcionTarea[TAM_MAXIMO]) {

    struct nodo *nuevoNodo = malloc(sizeof(nodo));
    strcpy(nuevoNodo->descripcionTarea, (const char *) descripcionTarea);
    nuevoNodo->dato = dato;
    nuevoNodo->nodoSiguiente = NULL;
    return nuevoNodo;
}

void eliminarNodoMemoria(nodo *nodo) {
    nodo->nodoSiguiente = NULL;
    free(nodo);
}

void agregarOrdenado(lista *lista, nodo *nuevoNodo) {
    if (lista->inicio != NULL) {
        nodo *nodoTemporal = lista->inicio;
        while (nodoTemporal != NULL) {
            if (nodoTemporal->dato >= nuevoNodo->dato) {
                nuevoNodo->nodoSiguiente = lista->inicio;
                lista->inicio = nuevoNodo;
                break;
            } else if (nodoTemporal->nodoSiguiente == NULL && nodoTemporal->dato <= nuevoNodo->dato) {
                nodoTemporal->nodoSiguiente = nuevoNodo;
                lista->fin = nuevoNodo;
                break;
            } else if (nodoTemporal->dato <= nuevoNodo->dato && nodoTemporal->nodoSiguiente->dato >= nuevoNodo->dato) {
                nuevoNodo->nodoSiguiente = nodoTemporal->nodoSiguiente;
                nodoTemporal->nodoSiguiente = nuevoNodo;
                break;
            } else {
                nodoTemporal = nodoTemporal->nodoSiguiente;
            }
        }
    } else {
        lista->inicio = nuevoNodo;
        lista->fin = nuevoNodo;
    }
}

void eliminarNodo(lista *lista, int datoEliminar) {
    if (lista->inicio != NULL) {
        nodo *nodoTemporal = lista->inicio;
        while (nodoTemporal != NULL) {
            if ((nodoTemporal->dato == datoEliminar) && (nodoTemporal == lista->inicio)) {
                lista->inicio = nodoTemporal->nodoSiguiente;
                eliminarNodoMemoria(nodoTemporal);
                if (lista->inicio == NULL) {
                    lista->fin = NULL;
                }
                break;
            } else if ((nodoTemporal->nodoSiguiente == lista->fin) &&
                       (nodoTemporal->nodoSiguiente->dato == datoEliminar)) {
                eliminarNodoMemoria(nodoTemporal->nodoSiguiente);
                nodoTemporal->nodoSiguiente = NULL;
                lista->fin = nodoTemporal;
                break;
            } else if (nodoTemporal->nodoSiguiente->dato == datoEliminar) {
                struct nodo *nodoEliminar = nodoTemporal->nodoSiguiente;
                nodoTemporal->nodoSiguiente = nodoEliminar->nodoSiguiente;
                eliminarNodoMemoria(nodoEliminar);
                break;
            } else {
                nodoTemporal = nodoTemporal->nodoSiguiente;
            }
        }
    }
}

/*
 * ALMACENAMIENTO DE TODAS LAS TAREAS REALIZADAS (PILA)
 */
typedef struct nodoCola {
    int datoCola;
    char descripcionTareaCola[TAM_MAXIMO];
    struct nodoCola *siguienteNodoCola;
} nodoCola;

typedef struct cola {
    struct nodoCola *inicioCola;
    struct nodoCola *finCola;
} cola;

nodoCola *crearNodoCola(int numeroCola,char *descripcionTarea[TAM_MAXIMO]) {
    struct nodoCola *nuevoNodoCola = malloc(sizeof(nodo));
    strcpy(nuevoNodoCola->descripcionTareaCola, (const char *) descripcionTarea);
    nuevoNodoCola->datoCola = numeroCola;
    nuevoNodoCola->siguienteNodoCola = NULL;
    return nuevoNodoCola;
}

cola *crearCola() {
    struct cola *nuevaCola = malloc(sizeof(nodo));
    nuevaCola->inicioCola = NULL;
    nuevaCola->finCola = NULL;
    return nuevaCola;
}

void encolar(cola *cola, struct nodoCola* nuevoNodoCola) {
    if (cola->inicioCola == NULL) {
        cola->inicioCola = nuevoNodoCola;
        cola->finCola = nuevoNodoCola;
    } else {
        cola->finCola->siguienteNodoCola = nuevoNodoCola;
        cola->finCola = nuevoNodoCola;
    }
}

void eliminarNodoMemoriaCola(nodoCola *nodoCola) {
    nodoCola->siguienteNodoCola = NULL;
    free(nodoCola);
}

void descolar(cola *cola) {
    if (cola->inicioCola != NULL) {
        nodoCola *nodoEliminarCola = cola->inicioCola;
        cola->inicioCola = cola->inicioCola->siguienteNodoCola;
        eliminarNodoMemoriaCola(nodoEliminarCola);

    } else {
        printf("LA COLA ESTA VACIA");
    }
}


int main() {
    int dato;
    int opcion = 0;
    struct lista *lista = crearLista();
    struct cola *cola = crearCola();

    do {
        printf("Selccione: \n 1. Agregar tarea pendiente \n 2. Realizar tarea \n 3. Ver tareas pendientes \n 4. Ver treas realizadas \n 5. Restaurar tareas \n 6. Salir \n");
        scanf("%i", &opcion);

        if (opcion == 1) {
        dato =1;
        char descripcionTarea[TAM_MAXIMO];

            printf("Ingrese la prioridad de la tarea a crear: \n 1-Urgente \n 2-Mesurado \n 3-Ordinario \n");
            scanf("%i", &dato);
            printf("Asigne un nommbre a la tarea: \n");
            scanf("%s",&descripcionTarea);

            if (dato <= 3 && dato > 0) {
               struct nodo *nuevoNodo = crearNodo(dato,descripcionTarea);
                agregarOrdenado(lista, nuevoNodo);
            } else {
                printf("DIGITE UN VALOR CORRECT0\n");
            }

        } else if (opcion == 2) {
            dato=0;
            char descripcionTarea[TAM_MAXIMO];
            printf("Ingrese el grado de prioridad de la tarea a realizar: \n");
            scanf("%i",&dato);
            printf("Ingrese en nombre de la tarea a realizar: \n");
            scanf("%s",descripcionTarea);
            nodoCola* nuevoNodoCola = crearNodoCola(dato,descripcionTarea);
            encolar(cola,nuevoNodoCola);
            eliminarNodo(lista,dato);

        }
        else if(opcion==3){
            nodo* nodoTemporal = lista->inicio;
            printf("Tareas pendientes: \n");
            while (nodoTemporal!= NULL){
                printf("%i | %s \n",nodoTemporal->dato,nodoTemporal->descripcionTarea);
                nodoTemporal = nodoTemporal->nodoSiguiente;
            }
        } else if(opcion==4){
            nodoCola * nodoTemporal = cola->inicioCola;
            printf("Tareas realizadas: \n");
            while (nodoTemporal!=NULL){
                printf("%i | %s \n",nodoTemporal->datoCola,nodoTemporal->descripcionTareaCola);
                nodoTemporal = nodoTemporal->siguienteNodoCola;
            }

        } else if(opcion==5){
            nodoCola* nodoTemporalCola = cola->inicioCola;
            nodo* nuevoNodo = crearNodo(nodoTemporalCola->datoCola,nodoTemporalCola->descripcionTareaCola);
            cola->inicioCola=cola->inicioCola->siguienteNodoCola;
            eliminarNodoMemoriaCola(nodoTemporalCola);
            agregarOrdenado(lista,nuevoNodo);
        }

    } while (opcion != 6);
    return 0;
}
