#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void)
{
  vertice v, vizinho;
  grafo g = le_grafo();
  printf("É conexo? %d \n", conexo(g));

  return 0;
}
