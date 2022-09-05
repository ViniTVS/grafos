#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void)
{
  vertice v, vizinho;
  grafo g = le_grafo();
  decompoe(g);
  destroi_grafo(g);

  return 0;
}
