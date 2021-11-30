#include <stdio.h>
#include <malloc.h>

/*
 * ALMACENAMIENTO DE TODAS LAS TAREAS PENDIENTES (LISTA)
 */
typedef struct nodo {
    int dato;
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

nodo *crearNodo(int dato) {
    struct nodo *nuevoNodo = malloc(sizeof(nodo));
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
typedef struct nodoPila {
    int datoPila;
    struct nodoPila *nodoArribaPila;
} nodoPila;

typedef struct pila {
    struct nodoPila *base;
    struct nodoPila *cima;
} pila;

pila *crarPila() {
    struct pila *nuevaPila = malloc(sizeof(nodo));
    nuevaPila->base = NULL;
    nuevaPila->cima = NULL;
    return nuevaPila;
}

nodoPila *crearNodoPila(int datoPila) {
    struct nodoPila *nuevoNodo = malloc(sizeof(nodo));
    nuevoNodo->datoPila = datoPila;
    nuevoNodo->nodoArribaPila = NULL;
    return nuevoNodo;
}

void elmiminarNodoMemoria(nodoPila *nodo) {
    nodo->nodoArribaPila = NULL;
    free(nodo);
}

void apilar(pila *pila, struct nodoPila *nuevoNodo) {
    if (pila->base == NULL) {
        pila->base = nuevoNodo;
        pila->cima = nuevoNodo;
    } else {
        pila->cima->nodoArribaPila = nuevoNodo;
        pila->cima = nuevoNodo;
    }
}

nodo *encontrarCima(pila *pila, struct nodoPila *nodoEliminar) {
    nodoPila *nodoTemporal = pila->base;
    while (nodoTemporal != NULL) {
        if (nodoTemporal->nodoArribaPila == nodoEliminar) {
            return nodoTemporal;
        }
    }

}

void desapilar(pila *pila) {
    if (pila->cima != NULL) {
        nodoPila *nodoELiminar = pila->cima;
        nodoPila *nodoCima = encontrarCima(pila, nodoELiminar);
        nodoCima->nodoArribaPila;
        pila->cima = nodoCima;
    }
}

int cimaPila(pila *pila) {
    int cima = 0;
    if (pila->cima == 0) {
        return 0;
    } else {
        cima = (int) pila->cima;
        printf("%i", cima);
    }
    return cima;
}

int main() {
    int dato;
    int opcion = 0;
    struct lista *lista = crearLista();
    struct pila *pila = crarPila();

    do {
        printf("Selccione: \n 1. Agregar tarea pendiente \n 2. Realizar tarea \n 3. Ver tareas pendientes \n 4. Ver treas realizadas \n 5. Restaurar tareas \n 6. Salir \n");
        scanf("%i", &opcion);

        if (opcion == 1) {
        dato =0;


            printf("Ingrese la prioridad de la tarea a crear: \n 1-Urgente \n 2-Mesurado \n 3-Ordinario \n");
            scanf("%i", &dato);

            if (dato <= 3 && dato > 0) {
                nodo *nuevoNodo = crearNodo(dato);
                agregarOrdenado(lista, nuevoNodo);
            } else {
                printf("DIGITE UN VALOR CORRECT0\n");
            }

        } else if (opcion == 2) {
            dato=1;
            printf("Ingrese el grado de prioridad de la tarea a realizar: \n");
            scanf("%i",&dato);
            nodoPila* nuevoNodoPila = crearNodoPila(dato);
            apilar(pila,nuevoNodoPila);
            eliminarNodo(lista,dato);
        }
        else if(opcion==3){
            nodo* nodoTemporal = lista->inicio;
            while (nodoTemporal!= NULL){
                printf("Tareas pendientes: %i \n",nodoTemporal->dato);
                nodoTemporal = nodoTemporal->nodoSiguiente;
            }
        } else if(opcion==4){
            nodoPila* nodoTemporal = pila->base;
            while (nodoTemporal!=NULL){
                printf("Tareas realizadas: %i \n",nodoTemporal->datoPila);
                nodoTemporal = nodoTemporal->nodoArribaPila;
            }
        } else if(opcion==5){
            nodoPila* nodoTemporal = pila->cima;
            nodo* nuevoNodo = crearNodo((int) nodoTemporal);
            agregarOrdenado(lista,nuevoNodo);
        }

    } while (opcion != 6);
    return 0;
}
