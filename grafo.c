#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


// obtém o vértice vizinho de u no grafo g a partir do vértice v
// Ex:
// for (vertice vizinho = obtem_vizinho(g, u, NULL); vizinho; vizinho = obtem_vizinho(g, u, vizinho)){
  // faz coisas
// }

vertice obtem_vizinho(grafo g, vertice u, vertice v){
  // vértice auxiliar p/ verificar se é vizinho
  vertice aux;
  // se v é NULL, v passa a ser o primeiro vértice
  if (!v)
    aux = agfstnode(g);
  else if (v == aglstnode(g)) // se v é o último, então já verificamos todos
    return NULL;
  else
    aux = agnxtnode(g, v);
  // percorre os demais vértices até encontrar o prox. vizinho ...
  while (aux) {
    if(agedge(g, u, aux, NULL, 0)){
      return aux;
    }
    aux = agnxtnode(g, aux);
  }
  // ou não ter mais viziho
  return NULL;
}

//------------------------------------------------------------------------------
grafo le_grafo(void) {
  grafo g = agread(stdin, NULL);
  if(!g){
    fprintf(stderr, "%s", "Erro ao ler grafo. Grafo não alocado!\n");
    exit(1);
  }
  return g; 
}
//------------------------------------------------------------------------------
int destroi_grafo(grafo g) {
  if(!g){
    return 1;
  }
  free(g);
  return 0;
}
//------------------------------------------------------------------------------
grafo escreve_grafo(grafo g) {
  if(agwrite(g, stdout)){
    fprintf(stderr, "%s", "Erro ao escrever grafo.\n");
  }
  return g;
}

// -----------------------------------------------------------------------------
int n_vertices(grafo g) {
  return agnnodes(g);
}

// -----------------------------------------------------------------------------
int n_arestas(grafo g) {
  return agnedges(g);
}

// -----------------------------------------------------------------------------
int grau(vertice v, grafo g) {
  if(v)
    return agdegree(g, v, TRUE, TRUE);

  return -1;
}

// -----------------------------------------------------------------------------
int grau_maximo(grafo g)  {
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
float grau_medio(grafo g) {
  int n_vertice, soma_graus = 0;
  // a soma dos graus de todos os vértices = 2|E(G)|
  for (vertice v = agfstnode(g); v; v = agnxtnode(g, v)){
    n_vertice++;
    soma_graus += grau(v, g);
  }

  return ((float)soma_graus / (float)n_vertice);
}

// -----------------------------------------------------------------------------
int regular(grafo g) {
  // regular = todos os vértices de mesmo grau
  vertice v = agfstnode(g);
  if (!v) // grafo não tem vértice
    return -1;

  int grau_v = grau(v, g);
  // percorre todos os demais vértices
  for (; v; v = agnxtnode(g, v)){
    if (grau_v != grau(v,g))
      return 0; // não é regular
  }

  return 1; // é regular
}

// -----------------------------------------------------------------------------
int completo(grafo g) {
  int n = n_vertices(g);
  int m = n_arestas(g);
  // como só temos grafos não direcionados, |A(G)| = n(n-1)/2 em grafos completos
  //! também podemos verificar o grau 1 a 1 para ver se o grafo não foi "mal montado" 
  return (m == n*(n-1)/2);
}

// -----------------------------------------------------------------------------
int conexo(grafo g) {
  vertice u,v;
  int saida;
  Agedge_t *e;
  // v será um vértice fixo. Se existir caminho dele para todos os demais, temos
  // um grafo conexo
  v = agfstnode(g);
  if (!v)
    return 0;
  for (e = agfstout(g,v); e; e = agnxtout(g,e)){

  }
  // cnt++;
  // agnxtnode();
  
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
  int vertices = n_vertices(g);

  // Aloca memoria para a matriz
  int **matriz = malloc(vertices * sizeof(int*));
  for (int i=0; i<vertices; i++){
    matriz[i] = calloc(vertices, sizeof(int));
  }

  vertice v1, v2;
  int i, j;
  i = 0;

  // Percorre vertices 2 a 2
  for (v1 = agfstnode(g); v1; v1 = agnxtnode(g,v1)){
    j = 0; // reinicia indice 2
    for (v2 = agfstnode(g); v2; v2 = agnxtnode(g,v2)){
      if (agedge(g, v1, v2, NULL, 0)){ // 0 = flag para criar se nao existir
        matriz[i][j] = 1;
      }
      // printf("%d  ", matriz[i][j]);
      j++;
    }
    // printf("\n");
    i++;
  }

  return matriz;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
  
  return NULL;
}

