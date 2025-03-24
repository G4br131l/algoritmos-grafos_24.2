#define vertex int


typedef struct graph *Graph;

typedef struct node *link;

struct node {
	vertex w;
	link next;
};


struct graph {
	int V;
	int A;
	link *adj;
};

static link NEWnode( vertex w, link next);
Graph GRAPHinit( int V);
void GRAPHinsertArc( Graph G, vertex v, vertex w);
void GRAPHshow( Graph G);
Graph GRAPHrand( int V, int A);