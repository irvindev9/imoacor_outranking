
/*
EL CODIGO QUE IMPLEMENTA LAS FUNCIONES ES EL ARCHIVO: TADListaDoblementeLigada.c
*/
#define TRUE	1
#define FALSE	0

#define ADELANTE	1
#define ATRAS		0

//Estructura elemento (Modificable por el usuario)
typedef struct elemento
{
	int value;
}elemento;

//Tipo de dato boolean (Modelado con un char)
typedef char boolean;

//Estructura de un NODO DOBLEMENTE LIGADO(No modificar)
typedef struct nodo
{
	elemento e;	
	struct nodo *adelante;	
	struct nodo* atras;

}nodo;

//Estructura de una LISTA(No modificar)
typedef struct lista
{
	nodo *frente;
	nodo *final;
	unsigned long tam;
}lista;

typedef nodo* posicion;

//Operaciones de construcción
void Initialize(lista *l);
void Destroy(lista *l);
//Operaciones de posicionamiento y busqueda
posicion Final(lista *l);
posicion First(lista *l);
posicion Following(lista *l, posicion p);
posicion Previous(lista *l, posicion p);
posicion Search(lista *l, elemento e);
//Operación de consulta
elemento Position(lista *l, posicion p);
elemento Element(lista *l, unsigned long n);
unsigned long Size(lista *l);
boolean Empty(lista *l);
boolean ValidatePosition(lista *l, posicion p);
//Operaciones de modificación
void Insert(lista *l, elemento e, posicion p,boolean b);
void Add(lista *l,elemento e);
void Remove(lista *l,posicion p);
void Replace(lista *l,posicion p, elemento e);
