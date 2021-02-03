#include <stdlib.h>
#include "../headers/TADListaDoblementeLigadaInt.h"
//Operaciones de construcción
void Initialize(lista *l)
{
	(*l).frente=NULL;
	l->final=NULL;
	l->tam=0;
	return;
}

void Destroy(lista *l)
{
	nodo *aux;
	while(l->frente!=NULL)
	{
		aux=l->frente->atras;
		free(l->frente);
		l->frente=aux;
	}
	l->final=NULL;
	l->tam=0;
	return;
}

//Operación de consulta
elemento Position(lista *l, posicion p)
{
	if(ValidatePosition(l,p)==TRUE)
	{
		return p->e;
	}
	else
	{
		exit(1);
	}
	return;
}

elemento Element(lista *l, unsigned long n)
{
	nodo *aux;
	unsigned long i;
	
	aux=l->frente;
	
	if(aux!=NULL&&n>0&&n<=Size(l))
	{
		for(i=1;i<n&&aux!=NULL;i++)
		{
			aux=aux->atras;
		}		
		
		return aux->e;
	}
	else
	{
		exit(1);
	}
}

unsigned long Size(lista *l)
{
	return l->tam;	
}


boolean Empty(lista *l)
{
	if(l->frente==NULL && l->final==NULL && l->tam==0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

boolean ValidatePosition(lista *l, posicion p)
{
	nodo *aux;
	
	aux=l->frente;
	while(aux!=p&&aux!=NULL)
	{
		aux=aux->atras;
	}
	
	if(aux==NULL)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//Operaciones de modificación
void Insert(lista *l, elemento e, posicion p,boolean b)
{
	nodo* aux;
	//Crear al nodo
	aux=malloc(sizeof(nodo));
	aux->e=e;

	//Validar la posicion
	if(ValidatePosition(l,p)==TRUE)
	{			
		//Atras de P
		if(b==TRUE)
		{
			//Si P es el final de la lista
			if(l->final==p)
			{
				l->final=aux;
			}
			
			aux->atras=p->atras;
			p->atras=aux;
			aux->adelante=p;
			aux->atras->adelante=aux; //*(aux->atras).adelante=aux;
		}
		else
		{
			//Si P es el frente de la lista
			if(l->frente==p)
			{
				l->frente=aux;
			}
			
			aux->adelante=p->adelante;
			aux->atras=p;
			p->adelante=aux;
			aux->adelante->atras=aux;
			
		}
	}		
	else
	{
		//Insertar al frente de la lista
		//Si es vacia
		if(l->frente==NULL&&l->final==NULL)
		{
			aux->atras=NULL;
			aux->adelante=NULL;
			l->frente=aux;
			l->final=aux;		
		}
		//Si no es vacia
		else
		{
			aux->adelante=NULL;
			aux->atras=l->frente;
			l->frente->adelante=aux;
			l->frente=aux;
		}
	}
	
	l->tam++;
	return;
}
void Add(lista *l,elemento e)
{
	nodo* aux;
	//Crear al nodo
	aux=malloc(sizeof(nodo));
	aux->e=e;

	//Insertar al final de la lista
	//Si es vacia
	if(l->frente==NULL&&l->final==NULL)
	{
		aux->atras=NULL;
		aux->adelante=NULL;
		l->frente=aux;
		l->final=aux;		
	}
	//Si no es vacia agregar al final
	else
	{
		aux->atras=NULL;
		aux->adelante=l->final;
		l->final->atras=aux;
		l->final=aux;
	}
	
	l->tam++;
	return;
}
void Remove(lista *l,posicion p)
{
	//Validar la posicion
	if(ValidatePosition(l,p)==TRUE)
	{
		//Si P es el frente
		if(p==l->frente)
		{
			l->frente=p->atras;
			p->atras->adelante=NULL;
			free(p);
		}
		//Si P es el ultimo nodo
		else if(p==l->final)
		{
			l->final=p->adelante;
			p->adelante->atras=NULL;
			free(p);			
		}
		else
		{
			p->adelante->atras=p->atras;
			p->atras->adelante=p->adelante;
			free(p);			
		}
		//Actualizar el numero de nodos
		l->tam--;	
	}
	else
	{
		exit(1);
	}
}

void Replace(lista *l,posicion p, elemento e)
{
	//Validar la posicion
	if(ValidatePosition(l,p)==TRUE)
	{
		p->e=e;
	}
	else
	{
		exit(1);
	}	
}

//Operaciones de posicionamiento y busqueda
posicion Final(lista *l)
{
	return l->final;
}

posicion First(lista *l)
{
	return l->frente;
}

posicion Following(lista *l, posicion p)
{
	if(ValidatePosition(l,p)==TRUE)
	{
		return p->atras;
	}	
	else
	{
		exit(1);
	}
}

posicion Previous(lista *l, posicion p)
{
	if(ValidatePosition(l,p)==TRUE)
	{
		return p->adelante;
	}	
	else
	{
		exit(1);
	}	
}

posicion Search(lista *l, elemento e)
{
	nodo *aux;
	aux=l->frente;
	while(aux!=NULL)
	{
		if(memcmp(&((*aux).e),&e,sizeof(elemento))==0) //memcmp(&aux->e,&e,sizeof(elemento)==0)
		{
			return aux;
		}
		aux=aux->atras;
	}
	return NULL;
}






















