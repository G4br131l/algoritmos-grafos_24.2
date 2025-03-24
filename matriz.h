//Arquivo de assinaturas

#define vertex long long int

struct graph {
	long long int V;
	long long int A;
	long long int **adj; 
};

typedef struct graph *Graph;

static long long int **MATRIXint(long long int r,long long int c,long long int val); 
Graph GRAPHinit(long long int V);
void GRAPHinsertArc( Graph G, vertex v, vertex w); 
void GRAPHremoveArc( Graph G, vertex v, vertex w);
void GRAPHshow( Graph G);
Graph GRAPHrand(long long int V,long long int A);