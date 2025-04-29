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
Nodo * CrearNodo(Tarea *tarea);
void InsertarNodo(Nodo **Start, Nodo* nodo);
Nodo * QuitarNodo(Nodo **Start, int dato);
void MostrarLista(Nodo *start);
void BuscarListaID(Nodo **Start, int dato);
void BuscarListaP(Nodo **Start, char* palabra);

int main(){
    char buff[100];
    char *palabraClave;
    int num = 1;
    int ID = 1000;
    int IDCambio, IDbusca;
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
        InsertarNodo(&StartPendiente,CrearNodo(tarea));

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

    printf("Ingrese el ID de la tarea que quiere buscar: \n");
    scanf("%d",&IDbusca);
    printf("Lista de Pendientes\n");
    BuscarListaID(&StartPendiente,IDbusca);
    printf("Lista de Realizadas\n");
    BuscarListaID(&StartRealizada,IDbusca);

    printf("Ingrese la palabra clave con la que quiere buscar la tarea: \n");
    fflush(stdin);
    gets(buff);
    palabraClave = (char*)malloc(sizeof(char)*(strlen(buff)+1));
    strcpy(palabraClave, buff);

    printf("La palabra clave de busqueda es: \n");
    puts(palabraClave);

    printf("Lista de Pendientes\n");
    BuscarListaP(&StartPendiente,palabraClave);
    printf("Lista de Realizadas\n");
    BuscarListaP(&StartRealizada,palabraClave);

    return 0;
}

Nodo * CrearListaVacia(){
    return NULL;
}

Nodo * CrearNodo(Tarea *tarea){

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
            (*Start) = nodoAux->Siguiente;
        }
        else
        {
            nodoAnt->Siguiente = nodoAux->Siguiente;
        }
            nodoAux->Siguiente = NULL;
    }
    return (nodoAux);
}

void BuscarListaID(Nodo **Start, int dato){

    Nodo *aux = *Start;

    while (aux != NULL && aux->T.TareaID != dato)
    {
        aux = aux->Siguiente;
    }
    
    if (aux != NULL)
    {   
        printf("    --Se encuentra en esta lista--\n");
        printf("La tarea encontrada es la siguiente: \n");
        printf("ID de la tarea: %d\n",aux->T.TareaID);
        printf("Descripcion de tarea : \n");
        puts(aux->T.Descripcion);
        printf("Duracion de la tarea: %d\n",aux->T.Duracion);
    }else{
        printf("Tarea no encontrada en esta lista\n");
    }
}

void BuscarListaP(Nodo **Start, char* palabra){

    Nodo *aux = *Start;

    while (aux != NULL && strstr(aux->T.Descripcion,palabra) == NULL)
    {
        aux = aux->Siguiente;
    }
    
    if (aux != NULL)
    {   
        printf("    --Se encuentra en esta lista--\n");
        printf("La tarea encontrada es la siguiente: \n");
        printf("ID de la tarea: %d\n",aux->T.TareaID);
        printf("Descripcion de tarea : \n");
        puts(aux->T.Descripcion);
        printf("Duracion de la tarea: %d\n",aux->T.Duracion);
    }else{
        printf("Tarea no encontrada en esta lista\n");
    }
}

void MostrarLista(Nodo *start){
    Nodo *aux;
    aux = start;

    while (aux)
    {
        printf("ID de la tarea: %d\n",aux->T.TareaID);
        printf("Descripcion de tarea : \n");
        puts(aux->T.Descripcion);
        printf("Duracion de la tarea: %d\n",aux->T.Duracion);

        aux = aux->Siguiente;
    }

}