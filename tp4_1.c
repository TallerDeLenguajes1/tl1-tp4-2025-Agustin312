#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Tarea
{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100 
}Tarea;

typedef struct Nodo
{
    struct Tarea T;
    struct Nodo *Siguiente;
}Nodo;

Nodo * CrearListaVacia();
Nodo * CraearNodo(Tarea *tarea);
void InsertarNodo(Nodo **Start, Nodo* nodo);
Nodo * QuitarNodo(Nodo **Start, int dato);
void MostrarLista(Nodo *start);
int main(){
    char buff[100];
    int num = 1;
    int ID = 1000;
    int IDCambio;
    Nodo * StartPendiente, *StartRealizada;

    StartPendiente = CrearListaVacia();
    StartRealizada = CrearListaVacia();

    printf("    ---- Carga de Tareas Pendientes ----\n");

    while(num != 0){

        Tarea * tarea = (Tarea*)malloc(sizeof(Tarea));

        printf("Ingrese la descripcion de la tarea:\n");
        fflush(stdin);
        gets(buff);
        tarea->Descripcion = (char*)malloc(sizeof(char)*(strlen(buff)+1));
        strcpy(tarea->Descripcion,buff);
        tarea->TareaID = ID;
        printf("Ingrese la duracion de la tarea entre 10 a 100: \n");
        scanf("%d",&tarea->Duracion);
        InsertarNodo(&StartPendiente,CraearNodo(tarea));

        printf("Si quiere seguir cargando tareas ingrese el valor 1 sino ingrese 0 \n");                
        scanf("%d",&num);

        ID++;
    }

    int i = 1;

    while (i != 0)
    {
        printf("Ingrese el ID de la tarea de la lista de pendientes que quiere mover a la lista de realizadas \n");
        scanf("%d",&IDCambio);

        InsertarNodo(&StartRealizada,QuitarNodo(&StartPendiente,IDCambio));

        printf("Si quiere seguir moviendo tareas ingrese el valor 1 sino ingrese 0 \n");                
        scanf("%d",&i);

    }
    
    printf("    --- Lista de Tareas Pendientes ---\n");
    MostrarLista(StartPendiente);

    printf("    --- Lista de Tareas Realizadas ---\n");
    MostrarLista(StartRealizada);

    return 0;
}

Nodo * CrearListaVacia(){
    return NULL;
}

Nodo * CraearNodo(Tarea *tarea){

    Nodo * NuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    NuevoNodo->T = *tarea;
    NuevoNodo->Siguiente = NULL;

    return NuevoNodo;
}

void InsertarNodo(Nodo **Start, Nodo* nodo){
    nodo->Siguiente = *Start;
    *Start = nodo;
}

Nodo * QuitarNodo(Nodo **Start, int dato){

    Nodo *nodoAux = (*Start);
    Nodo *nodoAnt = NULL;

    while (nodoAux != NULL && nodoAux->T.TareaID != dato)
    {
        nodoAnt = nodoAux;
        nodoAux = nodoAux->Siguiente;
    }
    if (nodoAux != NULL)
    {
        if (nodoAux == (*Start))
        {
            (*Start) = nodoAux->Siguiente;s
        }
        else
        {
            nodoAnt->Siguiente = nodoAux->Siguiente;
        }
            nodoAux->Siguiente = NULL;
    }
    return (nodoAux);
}

void MostrarLista(Nodo *start){
    Nodo *aux;
    aux = start;

    while (aux)
    {
        printf("ID de la tarea: %d\n",aux->T.TareaID);
        printf("Descripcion de tarea : \n");
        puts(aux->T.Descripcion);
        printf("Duracion de la tarea: %d",aux->T.Duracion);

        aux = aux->Siguiente;
    }

}