#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void){
  // vertice v, vizinho;
  grafo g = le_grafo();
  printf("Grafo G:\n");
  escreve_grafo(g);
  decompoe(g);
  grafo h;
  for (h = agfstsubg(g); h; h = agnxtsubg(h)){
    escreve_grafo(h);
  }
  destroi_grafo(g);

  return 0;
}
