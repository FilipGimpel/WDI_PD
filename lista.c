
#include <stdlib.h>
#include <stdio.h>

#include "drawlist.h"
#include "postscript.h"

#define DANE  "dane.txt"
#define WYNIK "lista.ps"

pelem lista;

elem *ListaZPliku(const char *fn){
  elem *pocz, *kon, *p;
  int i;
  FILE *f;

  pocz = kon = NULL;

  f = fopen(fn, "r" );

  if (!f) {
    fprintf(stderr, "Nie udało się otworzyć pliku %s\n", fn);
    return NULL;
  }

  while (fscanf(f, " %d", &i) == 1) {
    p = malloc(sizeof(elem));
    if (!p) break;
    p->value = i;
    p->next = NULL;
    if (!pocz) pocz = kon = p;
    else { kon->next = p; kon = p; }
  }

  lista = pocz;

  for(;pocz;pocz=pocz->next){
    printf("%d ", pocz->value);
  }
  printf("\n");

  return NULL;
}

void destroy(pelem first){
  pelem current;

  while(first){
    current = first;
    first = first->next;
    free(current);
  }
}

int main ( void )
{
  FILE    *df;
  int     k;
  int     d;
  char    c;

  ListaZPliku(DANE);
  DrawList(WYNIK, lista);

  destroy(lista);
  exit ( 0 );
}

