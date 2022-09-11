Dupla:
Fernanda Yukari Kawasaki - fyk18
Vinícius Teixeira Vieira dos Santos - vtvs18

Foram utilizados para testes somente grafos direcionados teste.

Funções feitas durante o desenvolvimento do trabalho 1 não foram refatoradas para que sejam utilizadas com grafos direcionados.

A função decompoe foi feita com base no algoritmo passado em aula, o Algoritmo de Kosaraju. Sua lógica é a seguinte:

    Ao receber um grafo G, inverta a direção de cada arco, obtendo assim o grafo transposto GT.  
    Em seguida, é feita uma busca em profundidade em GT para ordenar uma lista de seus vértices em pós-ordem (de GT).
    Percorrendo a ordem reversa da lista de vértices em pós-ordem de GT, é feita uma busca em profundidade em cada vértice. 
    Em cada etapa da busca, o conjunto dos vértices descobertos induz uma componente forte de G. 
