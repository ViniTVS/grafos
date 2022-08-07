#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void)
{
  vertice v, vizinho;
  grafo g = le_grafo();
  // for (v = agfstnode(g); v; v = agnxtnode(g, v)){
  //   printf("Vizinhos de %s: \n\t", agnameof(v));
  //   for ( vizinho = obtem_vizinho(g, v, NULL); vizinho; vizinho = obtem_vizinho(g, v, vizinho)){
  //     printf("%s\n\t", agnameof(vizinho));
  //   }
  //   printf("\n");
  // }
  printf("É bipartido? %d \n", bipartido(g));

  return 0;
}
