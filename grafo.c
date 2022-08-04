#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//------------------------------------------------------------------------------
grafo le_grafo(void) {

  return agread(stdin, NULL); 
}
//------------------------------------------------------------------------------
int destroi_grafo(grafo g) {
  if(!g){
    fprintf(stderr, "%s", "Erro ao destruir grafo. Grafo não alocado!\n");
    return -1;
  }
  free(g);
  return 1;
}
//------------------------------------------------------------------------------
grafo escreve_grafo(grafo g) {
  if(!g){
    fprintf(stderr, "%s", "Erro ao escrever grafo. Grafo não alocado!\n");
    return NULL;
  }
  if(agwrite(g, stdout)){
    fprintf(stderr, "%s", "Erro ao escrever grafo.\n");
  }
  return g;
}

// -----------------------------------------------------------------------------
int n_vertices(grafo g) {
  if (g)
    return agnnodes(g);
  return 0;
}

// -----------------------------------------------------------------------------
int n_arestas(grafo g) {
  if (g)
    return agnedges(g);
  return 0;
}

// -----------------------------------------------------------------------------
int grau(vertice v, grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int grau_maximo(grafo g)  {
  
  return 0;
}

// -----------------------------------------------------------------------------
int grau_minimo(grafo g)  {
  
  return 0;
}

// -----------------------------------------------------------------------------
int grau_medio(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int regular(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int completo(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int conexo(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int n_triangulos(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int **matriz_adjacencia(grafo g) {
  
  return NULL;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
  
  return NULL;
}

