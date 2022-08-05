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
  if(v && g)
    return agdegree(g, v, TRUE, TRUE);

  return -1;
}

// -----------------------------------------------------------------------------
int grau_maximo(grafo g)  {
  if(!g)
    return -1;

  int maior_grau = 0;
  vertice v;
  // percorre todos os vértices
  for (v = agfstnode(g); v; v = agnxtnode(g, v)){
    if (maior_grau < grau(v, g)){
      maior_grau = grau(v, g);
    }
  }

  return maior_grau;
}

// -----------------------------------------------------------------------------
int grau_minimo(grafo g)  {
  if(!g)
    return -1;
  
  // considera o grau do primeiro vertice como o menor
  vertice v = agfstnode(g);
  if(!v) // não existe vértice no grafo, então retorna 0
    return 0;

  int menor_grau = grau(v, g);
  // percorre todos os demais vértices
  for (; v; v = agnxtnode(g, v)){
    if (menor_grau > grau(v, g)){
      menor_grau = grau(v, g);
    }
  }

  return menor_grau;
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

