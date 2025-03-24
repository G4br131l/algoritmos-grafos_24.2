#include <stdio.h>
#include "lista.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int pa[1000];
int pre[1000];

static link NEWnode( vertex w, link next) {
   link a = malloc( sizeof (struct node));
   a->w = w;
   a->next = next;
   return a;
}


Graph GRAPHinit( int V) {
   Graph G = malloc( sizeof *G);
   G->V = V;
   G->A = 0;
   G->adj = malloc( V * sizeof (link));
   for (vertex v = 0; v < V; ++v)
      G->adj[v] = NULL;
   return G;
}


void GRAPHinsertArc( Graph G, vertex v, vertex w) {
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (a->w == w) 
         return;
      G->adj[v] = NEWnode( w, G->adj[v]);
      G->A++;
}


void GRAPHshow( Graph G) {
   vertex v;
   for (v = 0; v < G->V; ++v) {
      printf("%d: ", v);
      for (link a = G->adj[v]; a != NULL; a = a->next)
         printf("->%2d ", a->w);
      printf("\n");
   }
}

vertex randV( Graph G) { 
   double r;
   r = rand( ) / (RAND_MAX + 1.0);
   return r * G->V;
}

Graph GRAPHrand( int V, int A) { 
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

int GRAPHoutdeg(Graph G, vertex v) {
   int cont = 0;
   for (link i = G->adj[v]; i != NULL; i = i->next)      
      cont++;
      
   return cont;
}

int GRAPHindeg(Graph G, vertex v) {
   int cont = 0;
   for (int i = 0; i < G->V; i++)
      for (link j = G->adj[i]; j != NULL; j = j->next)
         if (j->w == v)
            cont++;

   return cont;
}

void GRAPH_entradaesaida(Graph G) {
   int cont_entrada[G->V];
   for (int i = 0; i < G->V; i++)
   {
      cont_entrada[i] = GRAPHindeg(G, i);
   }
   
}

void GRAPHdfs(Graph G) {
   int time = 0;
   for (vertex v = 0; v < G->V; ++v) {
       pa[v] = -1;
       pre[v] = -1;
   }

   void dfsR(Graph G, vertex v) {
       pre[v] = time++;
       for (link a = G->adj[v]; a != NULL; a = a->next) {
           vertex w = a->w;
           if (pre[w] == -1) {
               pa[w] = v;
               dfsR(G, w);
           }
       }
   }

   for (vertex v = 0; v < G->V; ++v) {
       if (pre[v] == -1) {
           dfsR(G, v);
       }
   }
}

bool UGRAPHcircuit0(Graph G) {
   GRAPHdfs( G); // calcula pre[] e pa[]
   for (vertex v = 0; v < G->V; ++v) {
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         vertex w = a->w;
         if (pre[w] < pre[v]) // v-w é de retorno
         if (w != pa[v]) return true;
      }
   }
   return false;
}