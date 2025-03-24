//Arquivo de implementações

#include <stdio.h>
#include "matriz.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

vertex cc[1000];
long long int pa[1000];
long long int pre[1000];

typedef struct {
   long long int items[1000];
   long long int front, rear;
} Queue;

Queue queue;

void QUEUEinit(long long int n) {
   queue.front = queue.rear = 0;
}

void QUEUEput(long long int v) {
   queue.items[queue.rear++] = v;
}

long long int QUEUEget() {
   return queue.items[queue.front++];
}

long long int QUEUEempty() {
   return queue.front == queue.rear;
}

void QUEUEfree() {
   queue.front = queue.rear = 0;
}


static long long int **MATRIXint( long long int r, long long int c, long long int val) { 
   long long int **m = malloc ( r * sizeof (long long int *) ); 
   for ( vertex i = 0; i < r; ++i) 
      m[i] = malloc ( c * sizeof (long long int) ); 
   for ( vertex i = 0; i < r; ++i) 
      for ( vertex j = 0; j < c; ++j) 
         m[i][j] = val; 
   return m; 
}

Graph GRAPHinit(long long int V) {
   Graph G = malloc ( sizeof *G);
   G->V = V; 
   G->A = 0; 
   G->adj = MATRIXint( V, V, 0);
   return G; 
}

void GRAPHinsertArc( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1; 
      G->A++; 
   } 
}

void GRAPHremoveArc( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0; 
      G->A--; 
   } 
} 

void GRAPHshow( Graph G) { 
   for ( vertex v = 0; v < G->V; ++v) { 
      printf ( "%2d:" , v); 
      for ( vertex w = 0; w < G->V; ++w)  
        if (G->adj[v][w] == 1) 
          printf ( " %2d" , w); 
        else 
          printf("   ");
      printf("\n"); 
      } 
}

vertex randV( Graph G) { 
   double r;
   r = rand( ) / (RAND_MAX + 1.0);
   return r * G->V;
}

Graph GRAPHrand( long long int V, long long int A) { 
   Graph G = GRAPHinit( V);
   srand(time(NULL));
   while (G->A < A) {
      vertex v = randV( G);
      vertex w = randV( G);
      if (v != w) 
         GRAPHinsertArc( G, v, w);
   }
   return G;
}
/* A função randV() devolve um vértice aleatório do grafo G. Vamos supor que G->V <= RAND_MAX. */

long long int GRAPHoutdeg(Graph G, vertex V) {
   long long int cont = 0;
   for (long long int i = 0; i < G->V; i++)
      if (G->adj[V][i] == 1)
         cont++;
      
   return cont;
}

long long int GRAPHindeg(Graph G, vertex V) {
   long long int cont = 0;
   for (long long int i = 0; i < G->V; i++)
      if (G->adj[i][V] == 1)
         cont++;
         
   return cont;
}

bool isSink(Graph G,vertex v) {
   if (GRAPHoutdeg(G, v) == 0)
      return true;
   return false;
}

bool isSource(Graph G, vertex v) {
   if (GRAPHindeg(G, v) == 0)
      return true;
   return false;
}

bool GRAPHisUndirected(Graph G) {
   for (long long int i = 0; i < G->A; i++)
   {
      for (long long int j = 0; j < G->A; j++)
      {
         if (G->adj[i][j] != G->adj[j][i])
            return false;
      }
   }
   return true;
}

void UGRAPHdegrees(Graph G, vertex *vs) {
   for (long long int i = 0; i < G->V; ++i)
   {
      vs[i] = GRAPHindeg(G, i);
   }
}

void GRAPHbfs(Graph G, long long int s, long long int *num) {
   long long int cnt = 0;
   for (long long int v = 0; v < G->V; ++v)
       num[v] = -1;  

   QUEUEinit(G->V);
   num[s] = cnt++;   
   QUEUEput(s);

   while (!QUEUEempty()) {
       long long int v = QUEUEget();
       for (long long int w = 0; w < G->V; w++) {
           if (G->adj[v][w] == 1 && num[w] == -1) {  
               num[w] = cnt++;
               QUEUEput(w);
           }
       }
   }
   QUEUEfree();
}

void GRAPHbfsPA(Graph G, long long int s, long long int *pa) {
   for (long long int v = 0; v < G->V; ++v)
       pa[v] = -1;  

   QUEUEinit(G->V);
   pa[s] = s;  
   QUEUEput(s);

   while (!QUEUEempty()) {
       long long int v = QUEUEget();
       for (long long int w = 0; w < G->V; w++) {
           if (G->adj[v][w] == 1 && pa[w] == -1) {  
               pa[w] = v;  
               QUEUEput(w);
           }
       }
   }
   QUEUEfree();
}

void GRAPHspt(Graph G, long long int s, long long int *dist) {
   const long long int INFINITY = G->V;  

   // Inicializa distâncias e pais
   for (long long int v = 0; v < G->V; ++v)
       dist[v] = INFINITY, pa[v] = -1;
   
   dist[s] = 0, pa[s] = s;
   
   QUEUEinit(G->V);
   QUEUEput(s);

   while (!QUEUEempty()) {
       long long int v = QUEUEget();
       for (long long int w = 0; w < G->V; w++) {
           if (G->adj[v][w] == 1 && dist[w] == INFINITY) {  
               dist[w] = dist[v] + 1;
               pa[w] = v;
               QUEUEput(w);
           }
       }
   }

   QUEUEfree();
}

void dfsRconComps(Graph G, vertex v, long long int id, vertex *cc) {
  cc[v] = id;
  for (vertex w = 0; w < G->A; ++w) {
    if (G->adj[v][w] == 1 && cc[w] == -1) {
      dfsRconComps(G, w, id, cc);
    }
  }
}

long long int UGRAPHconComps(Graph G) {
  long long int id = 0;
  for (vertex v = 0; v < G->V; ++v) 
    cc[v] = -1;
  for (vertex v = 0; v < G->V; ++v) {
    if (cc[v] == -1)
      dfsRconComps(G, v, id++, cc);
  }
  return id;
}

void GRAPHprintPath(Graph G, long long int s, long long int t) {
   if (pa[t] == -1) {
       printf("Nenhum caminho encontrado de %d para %d\n", s, t);
       return;
   }

   long long int path[G->V];
   long long int pathIndex = 0;
   long long int current = t;

   while (current != s) {
       path[pathIndex++] = current;
       current = pa[current];
   }
   path[pathIndex++] = s;

   printf("Caminho de %d para %d: ", s, t);
   for (long long int i = pathIndex - 1; i >= 0; i--) {
       printf("%d", path[i]);
       if (i > 0) {
           printf(" -> ");
       }
   }
   printf("\n");
}

bool isCircuit(Graph G, int seq[], int k) {
   if (k < 2) {
       return false; // Um circuito precisa de pelo menos 3 vértices
   }

   if (seq[0] != seq[k]) {
       return false; // O primeiro e o último vértice devem ser os mesmos
   }

   for (int i = 0; i < k; i++) {
       int v1 = seq[i];
       int v2 = seq[(i + 1) % (k + 1)]; // Próximo vértice na sequência

       if (G->adj[v1][v2] == 0 && G->adj[v2][v1] == 0) {
           return false; // Não há aresta entre os vértices consecutivos
       }
   }

   return true;
}
