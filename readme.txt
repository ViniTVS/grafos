Dupla:
Fernanda Yukari Kawasaki - fyk18
Vinícius Teixeira Vieira dos Santos - vtvs18

Foram utilizados para testes somente grafos não direcionados e viáveis. Porém, a biblioteca graphviz aceita a criação de grafos onde o vértice das pontas de uma aresta pode se o mesmo, como:
graph "Exemplo de grafo inválido" {
    a -- a;
} 
Casos de grafos como o de acima não foram validados.

Caso a entrada contendo o arquivo .dot esteja mal formatada, o programa é finalizado.

Segue abaixo a lógica usada para alguns dos algoritmos feitos:

int grau_medio(grafo g);
Para calcular o grau médio do grafo, optamos como grau médio o piso da soma do grau de cara vértice dividido pelo número de vértices, já que o resultado é necessariamente inteiro.

int completo(grafo g);
Sendo m o número de arestas do grafo e n o número de vértices, para verificar se o grafo é completo, foi somente verificado se m é igual a n(n-1)/2.

int conexo(grafo g);
É utilizado um algoritmo que “visita” os vértices vizinhos a partir de um vértice qualquer do grafo g.
Caso todos os vértices de g sejam visitados, o grafo é conexo. 

int bipartido(grafo g);
O algoritmo percorre todos os vértices de cada componente de g, colorindo um vértice de uma cor e seus vizinhos de outra. Caso sejam encontrados dois vértices vizinhos de mesma cor, o grafo não pode ser colorido por 2 cores e, portanto, não é bipartido. 

int n_triangulos(grafo g);
Seja A a matriz de adjacência do grafo g. Podemos utilizar a matriz de adjacência para determinar o número de passeios distintos. Ao calcular A^n, obtemos o número de passeios de tamanho n entre os vértices. Logo, (A[i][j])^n possui o número de passeios de i a j com tamanho n.

Como queremos encontrar os triângulos, n = 3. E como queremos começar e terminar no mesmo vértice, então i = j, ou seja, contaremos apenas os valores da diagonal principal.

No entanto, é preciso tomar cuidado, pois este valor não é a quantidade de triângulos no grafo. Tomando como exemplo um grafo K3 com vértices a, b e c. Utilizando o cálculo acima, teríamos o resultado 6. Isso porque contamos o mesmo triângulo partindo de cada um dos 3 vértices e, para cada vértice, existem dois passeios. Por exemplo, partindo do vértice a, temos a – b – c – a e também a – c – b – a. Logo, é preciso dividir essa soma por 3 x 2 = 6 para obter o número de triângulos do grafo.
