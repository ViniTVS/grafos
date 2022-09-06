#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

// Struct auxiliar para verificar se o grafo é conexo/bipartido
typedef struct {
  int visitado;   // 0 = não visitado, 1 = visitando vizinhos, 2 = visitei todos os vizinhos
  int cor;        // 0 = sem cor, 1 = roxo, 2 = azul
  vertice v; 
  vertice pai;
  int pre;
  int pos;
  int componente;
} s_auxiliar;

typedef Agedge_t *arco;

// prototypes das funcoes que criamos
vertice obtem_vizinho(grafo g, vertice u, vertice v);
int get_visitado(s_auxiliar *lista, vertice v);
void set_visitado(s_auxiliar *lista, vertice v, int status);
int get_cor(s_auxiliar *lista, vertice v);
void set_cor(s_auxiliar *lista, vertice v, int status);
vertice get_pai(s_auxiliar *lista, vertice v);
void set_pai(s_auxiliar *lista, vertice v, vertice pai);
void print_auxiliar(s_auxiliar *lista, int tam);

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

// função auxiliar para saber se o vértice foi visitado
int get_visitado(s_auxiliar *lista, vertice v){
  for(int i = 0; ; i++){
    if (lista[i].v == v)
      return lista[i].visitado;
  }

  return 0;
}

void set_visitado(s_auxiliar *lista, vertice v, int status){
  for(int i = 0; ; i++){
    if (lista[i].v == v){
      lista[i].visitado = status;
      return;
    }
  }
}

// função auxiliar para saber se o vértice foi visitado
int get_cor(s_auxiliar *lista, vertice v){
  for(int i = 0; ; i++){
    if (lista[i].v == v)
      return lista[i].cor;
  }

  return 0;
}

void set_cor(s_auxiliar *lista, vertice v, int status){
  for(int i = 0; ; i++){
    if (lista[i].v == v){
      lista[i].cor = status;
      return;
    }
  }
}

vertice get_pai(s_auxiliar *lista, vertice v){
  for(int i = 0; ; i++){
    if (lista[i].v == v){
      return lista[i].pai;
    }
  }
  return v;
}

void set_pai(s_auxiliar *lista, vertice v, vertice pai){
  for(int i = 0; ; i++){
    if (lista[i].v == v){
      lista[i].pai = pai;
      return;
    }
  }
}

void print_auxiliar(s_auxiliar *lista, int tam){
  printf("Auxiliar: \n\t");
  printf("v pai vis cor\n\t");
  for(int i = 0; i < tam; i++){
    if (lista[i].pai)
      printf("%s %s %d %d\n\t", agnameof(lista[i].v), agnameof(lista[i].pai), lista[i].visitado, lista[i].cor);
    else
      printf("%s NULL %d %d\n\t", agnameof(lista[i].v), lista[i].visitado, lista[i].cor);
  }
  printf("\n");
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
void destroi_grafo(grafo g) {
  agclose(g);
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

  return 0;
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
int grau_medio(grafo g) {
  int n_vertice, soma_graus = 0;
  vertice v = agfstnode(g);
  if(!v)
    return 0;
  // a soma dos graus de todos os vértices = 2|E(G)|
  for (; v; v = agnxtnode(g, v)){
    n_vertice++;
    soma_graus += grau(v, g);
  }

  return (soma_graus / n_vertice);
}

// -----------------------------------------------------------------------------
int regular(grafo g) {
  // regular = todos os vértices de mesmo grau
  vertice v = agfstnode(g);
  if (!v) // grafo não tem vértice
    return 0;

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
  if (n == 0)
    return 0;
  // como só temos grafos não direcionados, |A(G)| = n(n-1)/2 em grafos completos
  //! também podemos verificar o grau 1 a 1 para ver se o grafo não foi "mal montado" 
  return (m == n*(n-1)/2);
}

// -----------------------------------------------------------------------------
int conexo(grafo g) {
  vertice u,v;
  int num_vertices = n_vertices(g);
  int i = 0;
  // aloca em memória o array contendo as visitas 
  s_auxiliar *lista_visitas = calloc( num_vertices, sizeof(s_auxiliar));
  for (v = agfstnode(g); v; v = agnxtnode(g, v), i++){
    lista_visitas[i].visitado = 0;
    lista_visitas[i].v = v;
  }

  // u será um vértice "fixo". Se existir caminho dele para todos os demais, temos
  // um grafo conexo
  u = agfstnode(g);
  if (!u)
    return 0;
  // estou visitando os vértices vizinhos de u
  set_visitado(lista_visitas, u, 1);
  set_pai(lista_visitas, u, NULL);

  while (u){
    v = obtem_vizinho(g, u, NULL);
    while (v){
      // visito quem ainda não foi visitado
      if(get_visitado(lista_visitas, v) == 0){
        set_pai(lista_visitas, v, u); // atualizo o pai
        set_visitado(lista_visitas, v, 1); // vou percorrer o novo vizinho
        // altero u para v
        u = v;
        v = NULL;
      }
      // v recebe o prox. vizinho
      v = obtem_vizinho(g, u, v);
    }
    set_visitado(lista_visitas, u, 2); // visitei todos os vizinhos
    u = get_pai(lista_visitas, u);
  }

  // verifica se todos são 2
  for (i = 0; i < num_vertices; i++){
    if(lista_visitas[i].visitado != 2){
      free(lista_visitas);
      return 0;
    }
  }
  
  free(lista_visitas);
  return 1;
}

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
  // se g é bipartido, podemos pintar seu vértices com 2 cores. Então:
  // se u é de uma cor, todos os seus vizinhos devem ser de outra cor
  int num_vertices = n_vertices(g);
  // grafos vazio e trivial nunca serão bipartidos
  if (num_vertices < 2)
    return 0;
  vertice u, v;
  int i = 0;
  // aloca em memória o array contendo as cores
  // O visitado da struct passa a indicar as cores dos vértices  
  // 0 = não pintado 
  // 1 = pintado de roxo
  // 2 = pintado de azul
  s_auxiliar *lista_visitas = calloc( num_vertices, sizeof(s_auxiliar));
  for (v = agfstnode(g); v; v = agnxtnode(g, v), i++){
    lista_visitas[i].visitado = 0;
    lista_visitas[i].v = v;
  }
  // indica qual cor devo pintar o próximo vértice com base na cor atual
  int cor[3] = {0, 2, 1};

  // semelhante ao conexo, começo com o vértice de um componente
  u = agfstnode(g);
  set_visitado(lista_visitas, u, 1);
  set_cor(lista_visitas, u, 1);
  set_pai(lista_visitas, u, NULL);

  while (u){
    v = obtem_vizinho(g, u, NULL);

    while (v){
      // visito quem ainda não foi visitado
      if(get_visitado(lista_visitas, v) == 0){
        set_pai(lista_visitas, v, u); // atualizo o pai
        set_visitado(lista_visitas, v, 1); // vou percorrer o novo vizinho
        set_cor(lista_visitas, v, cor[get_cor(lista_visitas, u)]); // pinto com a outra cor
        // altero u para v
        u = v;
        v = NULL;
      } else {
        // se o vizinho tem a mesma cor do atual, este grafo não é bipartido
        if(get_cor(lista_visitas, v) == get_cor(lista_visitas, u)){
          free(lista_visitas);          
          return 0;
        }
      }
      // v recebe o prox. vizinho
      v = obtem_vizinho(g, u, v);
    }
    set_visitado(lista_visitas, u, 2); // visitei todos os vizinhos de u

    // acabo este componente, preciso buscar um vertice de outro componente que não colori 
    if (!get_pai(lista_visitas, u)){
      // suponho que não acho outro componente
      u = NULL;
      for (i = 0; i < num_vertices; i++){
        if(lista_visitas[i].cor == 0){
          // acho outro componente e faço seu "setup"
          u = lista_visitas[i].v;
          set_visitado(lista_visitas, u, 1);
          set_cor(lista_visitas, u, 1);
          set_pai(lista_visitas, u, NULL);
          break;
        }
      } 
    } else {
      u = get_pai(lista_visitas, u);
    }
  }
  // se cheguei a este ponto, pintei todos os vértices e não tive vizinhos de mesma cor
  free(lista_visitas);
  return 1;
}


int **multiplica_matriz(int **matriz, int **aux_matriz, int tamanho){
  int aux;
  int **resultado = malloc(tamanho * sizeof(int*));
  for (int i = 0; i < tamanho; i++){
    resultado[i] = calloc(tamanho, sizeof(int));
  }

  for (int i = 0; i < tamanho; i++){
    for (int j = 0; j < tamanho; j++){
      aux = 0; // reseta auxiliar
      for (int k = 0; k < tamanho; k++){
        aux += matriz[i][k] * aux_matriz[k][j]; // multiplica linha i por coluna j
      }
      resultado[i][j] = aux;
    }
  }
  return resultado;
}


int soma_diagonal_principal(int **matriz, int tamanho){
  int soma = 0;
  for (int i = 0; i < tamanho; i++){
    soma += matriz[i][i];
  }
  return soma;
}


void print_matriz(int **matriz, int tamanho){
  for (int i = 0; i < tamanho; i++){
    for (int j = 0; j < tamanho; j++)
      printf("%d ", matriz[i][j]);
    printf("\n");
  }
}


// -----------------------------------------------------------------------------
int n_triangulos(grafo g){

  // Obtem a matriz de adjacencia
  int **matriz = matriz_adjacencia(g);
  int tamanho = n_vertices(g);

  // Eleva matriz ao cubo
  int **resultado_quadrado = multiplica_matriz(matriz, matriz, tamanho); // matriz ao quadrado
  int **resultado_cubo = multiplica_matriz(resultado_quadrado, matriz, tamanho); // matriz ao cubo

  // print_matriz(resultado_cubo, tamanho);

  // Calcula a soma da diagonal da matriz ao cubo
  int soma_diagonal = soma_diagonal_principal(resultado_cubo, tamanho);
  return(soma_diagonal / 6);
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
      j++;
    }
    i++;
  }

  return matriz;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
  int vertices = n_vertices(g);

  // Novo grafo com mesmo tipo de g
  grafo g_barra = agopen("g_barra", g->desc, NULL); // complemento

  vertice v1, v2, v1_barra, v2_barra;;
  int i, j;
  i = 0;

  // Copia os vertices
  for (v1 = agfstnode(g); v1; v1 = agnxtnode(g, v1)){
    agnode(g_barra, agnameof(v1), TRUE);
  }

  // Cria arestas
  // Percorre vertices 2 a 2
  for (v1 = agfstnode(g); v1; v1 = agnxtnode(g, v1)){
    j = 0; // reinicia indice 2
    for (v2 = agfstnode(g); v2; v2 = agnxtnode(g, v2)){

      // se nao existe aresta no original
      // FALSE = flag para nao criar se nao existir
      if (!agedge(g, v1, v2, NULL, FALSE)){
        if (agnameof(v1) != agnameof(v2)){
          // encontra os vertices correspondentes em g_barra
          v1_barra = agnode(g_barra, agnameof(v1), FALSE);
          v2_barra = agnode(g_barra, agnameof(v2), FALSE);

          // adiciona aresta
          agedge(g_barra, v1_barra, v2_barra, NULL, 1);
        }
      }
      j++;
    }
    i++;
  }

  // matriz_adjacencia(g);
  // matriz_adjacencia(g_barra);
  return g_barra;
}

// -----------------------------------------------------------------------------
// cria o grafo transposto como um subgrafo de g
grafo transposto(grafo g){
  grafo g_trans = agopen("G transposto", Agdirected, NULL);
  if (!g_trans)
    return NULL;
  
  vertice v, vizinho_saida;
  arco a;
  // Adiciona cada vértice de g no transposto 
  for (v = agfstnode(g); v; v = agnxtnode(g,v)) {
    agnode(g_trans, agnameof(v), TRUE);
  }
  // Adiciona cada arco de g no transposto 
  for (v = agfstnode(g); v; v = agnxtnode(g,v)) {
    for (a = agfstout(g,v); a; a = agnxtout(g,a)) {
      vizinho_saida = aghead(a);
      // adiciona arco no transposto
      agedge(g_trans, agnode(g_trans, agnameof(vizinho_saida), FALSE), agnode(g_trans, agnameof(v), FALSE), NULL, TRUE);
    }
  }
  return g_trans;
}


// Inicializa struct auxiliar e seta valores iniciais de estado e componente
s_auxiliar *init_s_aux_componentes(grafo g){
  vertice v;
  int num_vertices = n_vertices(g);
  int i = 0;

  // aloca em memória o array contendo as visitas 
  s_auxiliar *lista_visitas = calloc(num_vertices, sizeof(s_auxiliar));
  for (v = agfstnode(g); v; v = agnxtnode(g, v), i++){
    lista_visitas[i].cor = 0;  // estado
    lista_visitas[i].componente = 0;
  }

  return lista_visitas;
}


// Retorna pointer para o vertice dentro da estrutura
s_auxiliar *busca_vertice(s_auxiliar *grafo_auxiliar, int n, vertice v){
  for (int i = 0; i < n; i++){
    if (grafo_auxiliar[i].v == v)
      return &(grafo_auxiliar[i]);
  }
  return NULL;
}


grafo decompoe_vertice(grafo g, s_auxiliar *grafo_auxiliar, s_auxiliar *r, int *c){
  s_auxiliar *vizinho, *u;
  Agedge_t *e;

  int num_vertices = n_vertices(g);
  r->cor = 1;
  u = r;

  // Vizinhos de saida
  for (e = agfstout(g, u->v); e; e = agnxtout(g, e)){
    vizinho = busca_vertice(grafo_auxiliar, num_vertices, e->node);
    if (vizinho->cor == 0){
      *c += 1;
      decompoe_vertice(g, grafo_auxiliar, vizinho, c);
    }
  }

  r->componente = *c;
  r->cor = 2;
}


// Percorre com DFS o grafo auxiliar transposto e retorna o reverso da pos ordem
s_auxiliar *pos_ordem_dfs_reverso(s_auxiliar *grafo_auxiliar_trans){
  // DFS

  // Reverso

  return NULL;
}


// -----------------------------------------------------------------------------
grafo decompoe(grafo g){
  // se não for direcionado, retorna g
  if (!agisdirected(g))
    return g;

  int num_vertices = n_vertices(g);


  s_auxiliar *grafo_auxiliar = init_s_aux_componentes(g);

  // REVERSO DA POS ORDEM DE UMA DFS EM G^T
  // acrescenta à lista de subgrafos de g cada um de seus componentes fortes
  // vide agsubg(), agfstsubg(), agnxtsubg()
  grafo g_trans = transposto(g);

  // estrutura auxiliar de grafo que contem estado e componente
  // basicamente, uma lista de vertices e seus atributos
  s_auxiliar *grafo_auxiliar_trans = init_s_aux_componentes(g_trans);
  // reverso da pos ordem resultante de uma busca em profundidade no grafo transposto
  s_auxiliar *pos_ordem_reverso = pos_ordem_dfs_reverso(grafo_auxiliar_trans);


  // Inicializa c
  int c = 0;  // componentes

  s_auxiliar v;
  for (int i = 0; i < num_vertices; i++){
    v = pos_ordem_reverso[i];
    if (v.cor == 0){
      c++;
      decompoe_vertice(g, grafo_auxiliar, &v, &c);
    }
  }

  agclose(g_trans); // não precisamos mais do transposto
  return g;
}